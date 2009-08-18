-- Based on a code from Stuart P. Bentley

require"imlua"
require"cdlua"
require"cdluaim"
require"iuplua"
require"iupluacd"
require"iupluaimglib"

images={}
frame=1

function print_error(err)
  local msg = {}
  msg[im.ERR_OPEN] = "Error Opening File."
  msg[im.ERR_MEM] = "Insuficient memory."
  msg[im.ERR_ACCESS] = "Error Accessing File."
  msg[im.ERR_DATA] = "Image type not Suported."
  msg[im.ERR_FORMAT] = "Invalid Format."
  msg[im.ERR_COMPRESS] = "Invalid or unsupported compression."
  
  if msg[err] then
    print(msg[err])
  else
    print("Unknown Error.")
  end
end

function load_frames(file_name)

  ifile, err=im.FileOpen(file_name)
  if not ifile then
      print_error(err)
      return
  end

  images={}
  images.delays={}
  images.disposal={}
  frame=1

  for i=1, select(3,ifile:GetInfo()) do
    images[i]=ifile:LoadBitmap(i-1)
    err, images[i] = im.ConvertColorSpaceNew(images[i], im.RGB, true)
    local delay=images[i]:GetAttribute("Delay") -- time to wait betweed frames in 1/100 of a second]
    if delay then
      images.delays[i]=delay[1]*10 -- timer in miliseconds
    else
      if (i == 1) then 
        images.delays[i]=100 
      else
        images.delays[i]=images.delays[i-1]
      end
    end
    images.disposal[i]=images[i]:GetAttribute("Disposal", true) --  [UNDEF, LEAVE, RBACK, RPREV]
  end

  ifile:Close()
  
  cnv.rastersize = images[1]:Width().."x"..images[1]:Height()
  dlg.size=nil
  iup.Refresh(cnv)
end

t = iup.timer{}

function start_timer()
  dlg.title = "Animated Gif"
  dlg.play_bt.image="IUP_MediaPause" dlg.play_bt.title="Pause"
  t.run = "NO"
  t.time = images.delays[frame]
  t.run = "YES"
  iup.Update(cnv)
end

function stop_timer()
  dlg.title = "Animated Gif "..frame.."/"..#images
  dlg.play_bt.image="IUP_MediaPlay" dlg.play_bt.title="Play" 
  t.run="NO"
  iup.Update(cnv)
end

function set_frame(f)
  frame = f
  if frame > #images then
    frame = #images
  end
  if frame < 1 then
    frame = 1
  end
  stop_timer()
end

function t:action_cb()
  frame = frame + 1
  if frame == #images+1 then
    frame = 1
  end
  
  start_timer()
end
    
cnv = iup.canvas{border = "NO"}

function cnv:map_cb()-- the CD canvas can only be created when the IUP canvas is mapped
  canvas = cd.CreateCanvas(cd.IUP, self)
  canvas:Activate()
  
  start_timer()
end

function cnv:action()-- called everytime the IUP canvas needs to be repainted
  canvas:Activate()
  if (images.disposal[frame] == "RBACK") then
    canvas:Clear()
  end
  images[frame]:cdCanvasPutImageRect(canvas, 0, 0, 0, 0, 0, 0, 0, 0) -- use default values
end

function cnv:resize_cb()
  canvas:Activate()
  canvas:Clear()
end

function cnv:button_cb(but, pressed)
  if (but == iup.BUTTON1 and pressed==1) then
    local file_name, error = iup.GetFile("*.*")
    if error ~= 0 then
      return
    end
    
    load_frames(file_name)  
    canvas:Activate()
    canvas:Clear()
    start_timer()
  end
end

buts = iup.hbox{
  iup.button{title="First", image="IUP_MediaGotoBegin", action=function(self) set_frame(1) end}, 
  iup.button{title="Previous", image="IUP_MediaRewind", action=function(self) set_frame(frame-1) end}, 
  iup.button{title="Pause", image="IUP_MediaPause", action=function(self) if (t.run=="YES") then stop_timer() else start_timer() end end}, 
  iup.button{title="Next", image="IUP_MediaForward", action=function(self) set_frame(frame+1) end}, 
  iup.button{title="Last", image="IUP_MediaGoToEnd", action=function(self) set_frame(#images) end}, 
  }
dlg = iup.dialog{iup.vbox{cnv, buts},title="Animated Gif", margin="5x5", gap=10}
dlg.play_bt = dlg[1][2][3]

function dlg:close_cb()
  iup.Destroy(t)
  images=nil --Destroys will be called by the garbage collector
  canvas:Kill()
  self:destroy()
  return iup.IGNORE -- because we destroy the dialog
end

load_frames(iup.GetFile("*.*"))

dlg:show()
iup.MainLoop()
