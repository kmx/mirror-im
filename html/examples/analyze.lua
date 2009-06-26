require"imlua"
require"imlua_process"

local filename = "lena.jpg"

local image = im.FileImageLoad(filename)
local gray = im.ImageCreate(image:Width(), image:Height(), im.GRAY, image:DataType())
local binary = im.ImageCreate(image:Width(), image:Height(), im.BINARY, image:DataType())
local region = im.ImageCreate(image:Width(), image:Height(), im.GRAY, im.USHORT)

-- make it grayscale
im.ConvertColorSpace(image, gray)
gray:Save("lena_gray.jpg", "JPEG")

-- make it binary
im.ProcessSliceThreshold(gray, binary, 0, 128)
binary:Save("lena_binary.jpg", "JPEG")

local count = im.AnalyzeFindRegions(binary, region, 4, 1)
print("regions: ", count)

local region2 = im.ImageCreate(image:Width(), image:Height(), im.GRAY, im.BYTE)
im.ConvertDataType(region, region2, 0, 0, 0, 0)

local region3 = im.ImageCreate(image:Width(), image:Height(), im.MAP, im.BYTE)
im.ConvertColorSpace(region2, region3)
region3:SetPalette(im.PaletteHighContrast(), 256)
region3:Save("lena_region.gif", "GIF")
