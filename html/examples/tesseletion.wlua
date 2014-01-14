require"imlua"
require"cdlua"
require"cdluaim"
require"iuplua"
require"iupluacd"
require"imlua_process"

filename = "flower.jpg"
 --set your file

anchosc = 500 -- window width
heightfac = math.sqrt(3)*0.5;

image=im.FileImageLoad(filename)
cnv = iup.canvas{rastersize =  anchosc .."x".. anchosc*heightfac, border = "NO"}

function cnv:map_cb()       -- the CD canvas can only be created when the IUP canvas is mapped
  self.canvas = cd.CreateCanvas(cd.IUP, self)
  self.canvas:Background(cd.BLACK)
end

mouseX,mouseY=0,0
nostatus=(" "):rep(10)
function cnv:motion_cb(x,y,status)
 if status == nostatus then
  mouseX = x
  mouseY = y
  iup.Update(cnv)
 end
end

function EQTriangle(can,len,mode)
 mode = mode or cd.FILL
 can:Begin(mode)
 can:Vertex(0,0)
 can:Vertex(len,0)
 can:Vertex(len*0.5,0.5*len*math.sqrt(3))
 can:End()
end

function clip(val,mini,maxi)
 return math.max(mini,math.min(val,maxi))
end

function linearmap(v,s,e,ds,de)
 return ((de-ds)*(v-s)/(e-s)) + ds
end

function imResize(im1,w,h)
 local im2 = im.ImageCreateBased(im1,w,h)
 im.ProcessResize(im1,im2,3)
 return im2
end

function MaskTriang(img,size)
 local im2 = img:Clone()
 im2:AddAlpha()
 local imcv = im2:cdCreateCanvas()
 EQTriangle(imcv,size,cd.CLIP)
 imcv:Clip(cd.CLIPPOLYGON)
 img:cdCanvasPutImageRect(imcv, 0, 0, 0, 0, 0, 0, 0, 0)
 imcv:Kill()
 return im2
end

function Tesselate(img,size)
 local im2 = im.ImageCreateBased(img,size*2,size*2)
 local imcv = im2:cdCreateCanvas()
 img:cdCanvasPutImageRect(imcv, 0, 0, 0, 0, 0, 0, 0, 0)

 imcv:TransformTranslate(1.5*size, size*0.5*math.sqrt(3))
 imcv:TransformRotate(120)
 img:cdCanvasPutImageRect(imcv, 0, 0, 0, 0, 0, 0, 0, 0)

 imcv:Transform({1,0,0,1,0,0}) --reset identity
 imcv:TransformTranslate(1.5*size, size*0.5*math.sqrt(3))
 imcv:TransformRotate(-120)
 img:cdCanvasPutImageRect(imcv, 0, 0, 0, 0, 0, 0, 0, 0)

 imcv:TransformScale(1,-1)
 img:cdCanvasPutImageRect(imcv, 0, 0, 0, 0, 0, 0, 0, 0)

 imcv:Kill()
 img:Destroy()
 return im2
end

function EndTesselate(img,size)
 local im2 = im.ImageCreateBased(img,size*2,size*2)
 local imcv = im2:cdCreateCanvas()

 img:cdCanvasPutImageRect(imcv, 0, 0, 0, 0, 0, 0, 0, 0)

 imcv:TransformTranslate(1.5*size, size*0.5*math.sqrt(3))
 imcv:TransformRotate(-120)
 imcv:TransformScale(1,-1)
 img:cdCanvasPutImageRect(imcv, 0, 0, 0, 0, 0, 0, 0, 0)

 imcv:Transform({1,0,0,1,0,0}) --reset identity
 imcv:TransformRotate(120)
 imcv:TransformScale(1,-1)
 img:cdCanvasPutImageRect(imcv, 0, 0, 0, 0, 0, 0, 0, 0)

 imcv:Kill()
 img:Destroy()
 return im2
end

function cnv:action()

 local width = anchosc
 local lado = clip(mouseX,10,width)

 self.canvas:Activate()

 local size = lado
 local imm = imResize(image,size,size)
 local im2 = MaskTriang(imm,size)
 while size < width do
  im2 = Tesselate(im2,size)
  size = size * 2
 end
 im2 = EndTesselate(im2,size)
 im2:cdCanvasPutImageRect(self.canvas, 0, 0, 0, 0, 0, 0, 0, 0)

 imm:Destroy()
 im2:Destroy()
end

dlg = iup.dialog{cnv}

function dlg:close_cb()
  image:Destroy()
  cnv.canvas:Kill()
  self:destroy()
  return iup.IGNORE -- because we destroy the dialog
end

dlg:show()
iup.MainLoop()
