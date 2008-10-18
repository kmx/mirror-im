require"imlua"
require"cdlua"
require"cdluaim"
require"iuplua"
require"iupluacd"

function PrintError(func, error)
  local msg = {}
  msg[im.ERR_OPEN] = "Error Opening File."
  msg[im.ERR_MEM] = "Insuficient memory."
  msg[im.ERR_ACCESS] = "Error Accessing File."
  msg[im.ERR_DATA] = "Image type not Suported."
  msg[im.ERR_FORMAT] = "Invalid Format."
  msg[im.ERR_COMPRESS] = "Invalid or unsupported compression."
  
  if msg[error] then
    print(func..": "..msg[error])
  else
    print("Unknown Error.")
  end
end

function LoadImage(file_name)
  local image
  local ifile, error = im.FileOpen(file_name)
  if not ifile then
      PrintError("open", error)
      return
  end
  
  -- load the first image in the file.
  -- force the image to be converted to a bitmap
  image, error = ifile:LoadBitmap()
  if not image then
    PrintError("load", error)
    return
  end
    
  ifile:Close()
  return image
end


dlg = nil  -- only one dlg

function ShowImage(file_name)

  local image = LoadImage(file_name)
  if not image then
    return false
  end

  if dlg then
    local old_canvas = dlg.canvas
    local old_image = dlg.image

    if old_canvas ~= nil then old_canvas:Kill() end
    if old_image ~= nil then old_image:Destroy() end

    iup.Destroy(dlg)
  end

  cnv = iup.canvas{}
  
  function cnv:action()
    local canvas = dlg.canvas
    local image = dlg.image
    
    if (not canvas) then return end

    canvas:Activate()
    canvas:Clear()
    image:cdCanvasPutImageRect(canvas, 0, 0, image:Width(), image:Height(), 0, 0, 0, 0)
    canvas:Flush()
    
    return iup.DEFAULT
  end

  function cnv:button_cb()
    local file_name = "*.*"
    local error

    file_name, error = iup.GetFile(file_name)
    if error ~= 0 then
      return iup.DEFAULT
    end
    
    ShowImage(file_name)  
    return iup.DEFAULT
  end

  
  -- Set the Canvas inicial size (IUP will retain this value).
  cnv.rastersize = string.format("%dx%d", image:Width(), image:Height())
  
  dlg = iup.dialog{cnv}
  dlg.title = file_name
  
  function dlg:close_cb()
    local canvas = self.canvas
    local image = self.image

    if canvas then canvas:Kill() end
    if image then image:Destroy() end

    return iup.CLOSE
  end

  dlg:show()

  canvas = cd.CreateCanvas(cd.IUP, cnv)
  assert(canvas)

  dlg.canvas = canvas
  dlg.image = image

  cnv:action()
  
  return true
end

function main(arg)
  local file_name = "*.*"
  local error
  
  -- Try to get a file name from the command line.
  if (arg == nil or table.getn(arg) < 2) then
    file_name, error = iup.GetFile(file_name)
    if error ~= 0 then
      return true
    end
  else   
    file_name = arg[1]
  end
                                   
  if not ShowImage(file_name) then
    local Try = true
    -- If ShowImage returns an error I will try to read another image.
    -- I can give up on File Open dlg choosing "Cancel".
    while Try do
      file_name = "*.*"
      
          file_name, error = iup.GetFile(file_name)
      if error ~= 0 then
        return true
      end
      
      if ShowImage(file_name) then
        Try = false
      end
    end
  end
  
  iup.MainLoop()  
  return true
end

main(arg)
