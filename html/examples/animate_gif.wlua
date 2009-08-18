require"imlua"
require"cdlua"
require"cdluaim"
require"iuplua"
require"iupluacd"

gimgs={}
gimgs.delays={}

ggif=im.FileOpen(iup.GetFile("*.*"))

for i=1, select(3,ggif:GetInfo()) do
  gimgs[i]=ggif:LoadImage(i-1)
  err, gimgs[i] = im.ConvertColorSpaceNew(gimgs[i], im.RGB, true)
  local delay=gimgs[i]:GetAttribute "Delay"
  if delay then
    gimgs.delays[i]=delay[1]*10
  else
    gimgs.delays[i]=10
  end
end

ggif:Close()

function gifanimator(gimgs, behavior, start, final, runyn, initial)

  start=start or 1
  final=final or #gimgs
  local increment=1
  local frame=initial or start

  --hack to get data to canvas action
  anii=frame
  return iup.timer{
    time=gimgs.delays[frame],
    run=runyn or "YES",
    action_cb=function(self)
      self.run="NO"
      if frame==final then
        if behavior=="LOOP" then
          frame=start
        elseif behavior=="BOUNCE" then
          increment=-1
          frame=frame+increment
        else
          return nil
        end
      elseif frame==start and behavior=="BOUNCE" then
        increment=1
        frame=frame+increment
      else
        frame=frame+increment
      end
      self.time=gimgs.delays[frame]
      self.run="YES"

      --for the canvas redrawing function
      anii=frame
      --redraw the canvas. yeah, it's a bit of a hack.
      cnv.action()
    end}
end

anit=gifanimator(gimgs,"LOOP")--,"BOUNCE",3,20)

cnv = iup.canvas{rastersize = gimgs[1]:Width().."x"..gimgs[1]:Height(),
 border = "NO",
 expand = "YES"}

function cnv:map_cb()-- the CD canvas can only be created when the IUP canvas is mapped
  cdanvas = cd.CreateCanvas(cd.IUP, self)
end

function cnv:action()-- called everytime the IUP canvas needs to be repainted
  cdanvas:Activate()
  gimgs[anii]:cdCanvasPutImageRect(cdanvas, 0, 0, 0, 0, 0, 0, 0, 0) -- use default values
end

dlg = iup.dialog{cnv,title="Animated Gif Player"}

function dlg:close_cb()
  iup.Destroy(anit)
  gimgs=nil --Destroys will be called by the garbage collector
  cdanvas:Kill()
  self:destroy()
  return iup.IGNORE -- because we destroy the dialog
end

dlg:show()
iup.MainLoop()
