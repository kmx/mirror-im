require("iuplua")
require("iupluagl")
require("luagl")
require("luaglu")
require("imlua")

--filename = [[C:\LUA\im-3.8.2_Win32_dllw4_lib\im-3.8.2_Examples\im\html\examples\flower.jpg]]
filename =[[flower.jpg]]
heightfac=math.sqrt(3)*0.5 -- ratio from height to side in equilateral triangle
iup.key_open()

texture = 0

cnv = iup.glcanvas{buffer="DOUBLE", rastersize = "640x480"}

function cnv:resize_cb(width, height)
  iup.GLMakeCurrent(self)
  gl.Viewport(0, 0, width, height)

  gl.MatrixMode('PROJECTION')   -- Select The Projection Matrix
  gl.LoadIdentity()             -- Reset The Projection Matrix

  if height == 0 then           -- Calculate The Aspect Ratio Of The Window
    height = 1
  end
 gl.Ortho(0, width, height,0, 0.0, 500);
  gl.MatrixMode('MODELVIEW')    -- Select The Model View Matrix
  gl.LoadIdentity()             -- Reset The Model View Matrix
end

function EQtriang(dummy,wi)
 gl.PushMatrix()
 gl.Scale(wi,wi,1)
  gl.Begin('TRIANGLES')          -- Drawing Using Triangles
 gl.TexCoord(0.5, 1) gl.Vertex( 0.5,  math.sqrt(3)*0.5, 0)         -- Top
 gl.TexCoord(0, 0) gl.Vertex(0, 0, 0)         -- Bottom Left
 gl.TexCoord(1, 0) gl.Vertex( 1, 0, 0)         -- Bottom Right
 gl.End()        -- Finished Drawing The Triangle
 gl.PopMatrix()
end

function TeselR(fun,wi,lev)
 local fu = lev > 0 and TeselR or fun
 local w = wi*(2^lev)

 gl.PushMatrix()
 fu(fun,wi,lev-1)
 gl.PopMatrix()

 gl.PushMatrix()
 gl.Translate(1.5*w,heightfac*w,0)
 gl.Rotate(120,0,0,1)
 fu(fun,wi,lev-1)

 gl.PopMatrix()

 gl.PushMatrix()
 --gl.LoadIdentity()             -- Reset The Current Modelview Matrix
 gl.Translate(1.5*w,heightfac*w,0)
 gl.Rotate(-120,0,0,1)
 fu(fun,wi,lev-1)

 gl.Rotate(180,1,0,0)
 fu(fun,wi,lev-1)

 gl.PopMatrix()

end

function cnv:action(x, y)
 --local timebegin = os.clock()
 --print((self.DRAWSIZE):match("(%d*)x(%d*)"))
 local w,h = (self.DRAWSIZE):match("(%d*)x(%d*)")
 local endwide = h*2/math.sqrt(3) + w
 local cellwide = math.max(10,mouseX)
 local iters = math.floor(math.log(endwide/cellwide)/math.log(2))
 --print(w,h,endwide,iters)
 iup.GLMakeCurrent(self)
 gl.Clear('COLOR_BUFFER_BIT,DEPTH_BUFFER_BIT') -- Clear Screen And Depth Buffer

 gl.LoadIdentity()             -- Reset The Current Modelview Matrix
 gl.Translate(-0.5*(endwide -w),0,-40)
 gl.BindTexture('TEXTURE_2D', texture[1])
 --TeselR(EQtriang,0)

 TeselR(EQtriang,cellwide,iters)

 iup.GLSwapBuffers(self)
 --print("drawtime",os.clock()-timebegin)
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

function cnv:k_any(c)
  if c == iup.K_q or c == iup.K_ESC then
    return iup.CLOSE
  elseif c == iup.K_F1 then
    if fullscreen then
      fullscreen = false
      dlg.fullscreen = "No"
    else
      fullscreen = true
      dlg.fullscreen = "Yes"
    end
    iup.SetFocus(cnv)
  end
end

function LoadImage(fileName)
  local image = im.FileImageLoadBitmap(fileName)
  if (not image) then
    print ("Unnable to open the file: " .. fileName)
    os.exit()
  end
  local gldata, glformat = image:GetOpenGLData()
  gl.PixelStore(gl.UNPACK_ALIGNMENT, 1)

  glu.Build2DMipmaps(image:Depth(), image:Width(), image:Height(), glformat, gl.UNSIGNED_BYTE, gldata)

  -- gldata will be destroyed when the image object is destroyed
  image:Destroy()
end

function cnv:map_cb()
  iup.GLMakeCurrent(self)
  gl.Enable('TEXTURE_2D')            -- Enable Texture Mapping ( NEW )

  texture = gl.GenTextures(1)  -- Create The Texture

  -- Typical Texture Generation Using Data From The Bitmap
  gl.BindTexture('TEXTURE_2D', texture[1])
  gl.TexParameter('TEXTURE_2D','TEXTURE_MIN_FILTER','LINEAR')
  gl.TexParameter('TEXTURE_2D','TEXTURE_MAG_FILTER','LINEAR')

  LoadImage(fileName)
end

if arg[1] ~= nil then
  fileName = arg[1]
else
  fileName = filename --[[C:\LUA\LuaGLsource\luagl\html\examples\luagl.tga]]
end

dlg = iup.dialog{cnv; title="LuaGL Image Texture Loader"}

dlg:show()
cnv.rastersize = nil -- reset minimum limitation

if (not iup.MainLoopLevel or iup.MainLoopLevel()==0) then
  iup.MainLoop()
end
