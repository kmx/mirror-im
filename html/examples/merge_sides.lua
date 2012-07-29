-- lua5.1 merge_sides.lua *.jpg

require"imlua"
require"imlua_process"

filename1 = arg[1]
if (not filename1) then
  print("Must have the file name as parameter.")
  print("  Can have more than one file name as parameters and can use wildcards.")
  print("  Usage:")
  print("    lua merge_sides.lua filename1 filename2 ...")
  print("    lua merge_sides.lua *.jpg")
  return
end

print(">>> merge of multiple images into pairs of 2 images for printing <<<")
print("")

function Rotate90(image)
  local new_image = im.ImageCreateBased(image, image:Height(), image:Width())
  im.ProcessRotate90(image, new_image, true)
  image:Destroy()
  return new_image, new_image:Width(), new_image:Height()
end

function ReduceTo(image, new_w, new_h)
  local w = image:Width()
  local h = image:Height()
  if (new_w/new_h < w/h) then
    new_h = new_w * h/w
  else
    new_w = new_h * w/h
  end
  local new_image = im.ImageCreateBased(image, new_w, new_h)
  im.ProcessReduce(image, new_image, 1)
  image:Destroy()
  return new_image
end

function ProcessImageFile(file_name1, file_name2, index)
  print("Loading File1: "..file_name1)
  local image1, err = im.FileImageLoad(file_name1);
  if (err and err ~= im.ERR_NONE) then
    error(im.ErrorStr(err))
  end
  print("Loading File2: "..file_name2)
  local image2, err = im.FileImageLoad(file_name2);
  if (err and err ~= im.ERR_NONE) then
    error(im.ErrorStr(err))
  end
  
  local w1 = image1:Width()
  local h1 = image1:Height()
  if (h1 > w1) then 
    image1, w1, h1 = Rotate90(image1)
  end
  local w2 = image2:Width()
  local h2 = image2:Height()
  if (h2 > w2) then 
    image2, w2, h2 = Rotate90(image2)
  end
  
  local new_w = w1
  if (w2 > w1) then new_w = w2 end
  local new_h = h1
  if (h2 > h1) then new_h = h2 end
  new_h = new_h*2
 
  new_w = new_w/2
  new_h = new_h/2
  local new_image = im.ImageCreateBased(image1, new_w, new_h+10)
  
  image1 = ReduceTo(image1, new_w, new_h/2)
  image2 = ReduceTo(image2, new_w, new_h/2)

  im.ProcessInsert(new_image, image1, new_image, 0, 0)
  im.ProcessInsert(new_image, image2, new_image, 0, new_h/2+10)

  local file_name = "merge_"..index.."+"..(index+1)..".jpg"
  print("   Saving File: "..file_name)
  new_image:Save(file_name, "JPEG")

  new_image:Destroy()
  image1:Destroy()
  image2:Destroy()
  print("")
end

for index = 1, #arg, 2 do
  ProcessImageFile(arg[index], arg[index+1], index)
end

if (#arg > 1) then
  print("Processed "..(#arg/2).." Files.")
end
