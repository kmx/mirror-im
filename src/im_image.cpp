/** \file
 * \brief Image Manipulation
 *
 * See Copyright Notice in im_lib.h
 * $Id$
 */

#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <assert.h>

#include "im.h"
#include "im_image.h"
#include "im_util.h"
#include "im_attrib.h"
#include "im_file.h"
#include "im_convert.h"


int imImageCheckFormat(int color_mode, int data_type)
{
  if ((imColorModeSpace(color_mode) == IM_MAP || imColorModeSpace(color_mode) == IM_BINARY) &&
      (data_type != IM_BYTE))
    return 0;

  return 1;
}

int imImagePixelOffset(int is_packed, int width, int height, int depth, int col, int row, int plane)
{
  if (is_packed) 
    return row*width*depth + col*depth + plane;
  else           
    return plane*width*height + row*width + col;
}

int imImageDataSize(int width, int height, int color_mode, int data_type)
{
  return width * height * imColorModeDepth(color_mode) * imDataTypeSize(data_type);
}
                           
int imImageLineCount(int width, int color_mode)
{
  if (imColorModeIsPacked(color_mode))
    return width*imColorModeDepth(color_mode);
  else
    return width;
}

int imImageLineSize(int width, int color_mode, int data_type)
{
  return imImageLineCount(width, color_mode) * imDataTypeSize(data_type);
}

static void iImageInit(imImage* image, int width, int height, int color_space, int data_type, int has_alpha)
{
  assert(width>0);
  assert(height>0);
  assert(color_space >= IM_RGB && color_space <= IM_XYZ);
  assert(data_type >= IM_BYTE && data_type <= IM_CFLOAT);

  image->width = width;
  image->height = height;
  image->color_space = color_space;
  image->data_type = data_type;
  image->has_alpha = has_alpha;

  image->depth = imColorModeDepth(color_space);
  image->line_size = image->width * imDataTypeSize(data_type); 
  image->plane_size = image->line_size * image->height; 
  image->size = image->plane_size * image->depth;
  image->count = image->width * image->height; 

  int depth = image->depth+1;  // add room for an alpha plane pointer, even if does not have alpha now.

  if (image->data)
  {
    /* if reallocating, preserve the data buffer */
    void* data0 = image->data[0];

    free(image->data);
    image->data = (void**)malloc(depth * sizeof(void*));  

    image->data[0] = data0;
  }
  else
    image->data = (void**)malloc(depth * sizeof(void*));
}

imImage* imImageInit(int width, int height, int color_space, int data_type, void* data_buffer, long* palette, int palette_count)
{
  if (!imImageCheckFormat(color_space, data_type))
    return NULL;
                 
  imImage* image = (imImage*)malloc(sizeof(imImage));
  image->data = 0;
    
  iImageInit(image, width, height, color_space, data_type, 0);

  if (data_buffer)
  {
    for (int d = 0; d < image->depth; d++)
      image->data[d] = (imbyte*)data_buffer + d*image->plane_size;
  }

  if (imColorModeDepth(color_space) == 1)
  {
    image->palette = palette;
    image->palette_count = palette_count;
  }
  else
  {
    image->palette = NULL;
    image->palette_count = 0;
  }

  image->attrib_table = new imAttribTable(599);

  return image;
}

imImage* imImageCreate(int width, int height, int color_space, int data_type)
{
  imImage* image = imImageInit(width, height, color_space, data_type, NULL, NULL, 0);
  if (!image) return NULL;

  /* palette is available to BINARY, MAP and GRAY */
  if (imColorModeDepth(color_space) == 1)
  {
    image->palette = (long*)malloc(256*sizeof(long));

    if (image->color_space == IM_BINARY)
    {
      image->palette_count = 2;
      image->palette[0] = imColorEncode(0, 0, 0);
      image->palette[1] = imColorEncode(255, 255, 255);
    }
    else
    {
      image->palette_count = 256;
      for (int i = 0; i < 256; i++)
        image->palette[i] = imColorEncode((imbyte)i, (imbyte)i, (imbyte)i);
    }
  }
  
  /* allocate data buffer */
  image->data[0] = malloc(image->size);
  if (!image->data[0])
  {
    imImageDestroy(image);
    return NULL;
  }

  /* initialize data plane pointers */
  for (int d = 1; d < image->depth; d++)
    image->data[d] = (imbyte*)(image->data[0]) + d*image->plane_size;

  imImageClear(image);

  return image;
}

imImage* imImageCreateBased(const imImage* image, int width, int height, int color_space, int data_type)
{
  assert(image);

  if (width <= 0) width = image->width;
  if (height <= 0) height = image->height;
  if (color_space < 0) color_space = image->color_space;
  if (data_type < 0) data_type = image->data_type;

  imImage* new_image = imImageCreate(width, height, color_space, data_type);
  imImageCopyAttributes(image, new_image);

  if (image->has_alpha)
    imImageAddAlpha(new_image);

  return new_image;
}

void imImageAddAlpha(imImage* image)
{
  assert(image);

  if (image->has_alpha)
    return;

  unsigned char* new_data = (unsigned char*)realloc(image->data[0], image->size+image->plane_size);
  if (!new_data)
    return;

 image->data[0] = new_data;
  for (int d = 1; d < image->depth+1; d++)
    image->data[d] = (imbyte*)(image->data[0]) + d*image->plane_size;

  memset(image->data[image->depth], 0, image->plane_size);

  image->has_alpha = IM_ALPHA;
}

void imImageReshape(imImage* image, int width, int height)
{
  assert(image);

  int old_size = image->size, 
      old_width = width, 
      old_height = height;

  iImageInit(image, width, height, image->color_space, image->data_type, image->has_alpha);

  if (old_size < image->size)
  {
    void* data0 = realloc(image->data[0], image->has_alpha? image->size+image->plane_size: image->size);
    if (!data0) // if failed restore the previous size
      iImageInit(image, old_width, old_height, image->color_space, image->data_type, image->has_alpha);
    else
      image->data[0] = data0;
  }

  /* initialize data plane pointers */
  int depth = image->has_alpha? image->depth+1: image->depth;
  for (int d = 1; d < depth; d++)
    image->data[d] = (imbyte*)image->data[0] + d*image->plane_size;
}

void imImageDestroy(imImage* image)
{
  assert(image);

  imAttribTable* attrib_table = (imAttribTable*)image->attrib_table;
  delete attrib_table;

  if (image->data[0])
    free(image->data[0]);

  if (image->palette)
    free(image->palette);

  free(image->data);

  // This will help detect invalid image usage after destroy.
  memset(image, 0, sizeof(imImage));

  free(image);
}

void imImageClear(imImage* image)
{
  assert(image);

  if ((image->color_space == IM_YCBCR || image->color_space == IM_LAB || image->color_space == IM_LUV) && 
      (image->data_type == IM_BYTE || image->data_type == IM_USHORT))
  {
    memset(image->data[0], 0, image->plane_size);

    if (image->data_type == IM_BYTE)
    {
      imbyte* usdata = (imbyte*)image->data[1];
      for (int i = 0; i < 2*image->count; i++)
        *usdata++ = 128;
    }
    else
    {
      imushort* usdata = (imushort*)image->data[1];
      for (int i = 0; i < 2*image->count; i++)
        *usdata++ = 32768;
    }
  }
  else
    memset(image->data[0], 0, image->size);

  if (image->has_alpha)
    memset(image->data[image->depth], 0, image->plane_size);
}

int imImageIsBitmap(const imImage* image)
{
  assert(image);
  return imColorModeIsBitmap(image->color_space, image->data_type);
}

void imImageCopy(const imImage* src_image, imImage* dst_image)
{
  assert(src_image);
  assert(dst_image);

  imImageCopyData(src_image, dst_image);

  if (dst_image != src_image)
    imImageCopyAttributes(src_image, dst_image);
}

void imImageCopyData(const imImage* src_image, imImage* dst_image)
{
  assert(src_image);
  assert(dst_image);
  assert(imImageMatch(src_image, dst_image));

  if (dst_image != src_image)
  {
    memcpy(dst_image->data[0], src_image->data[0], (src_image->has_alpha && dst_image->has_alpha)? src_image->size+src_image->plane_size: src_image->size);
  }
}

imImage* imImageDuplicate(const imImage* image)
{
  assert(image);

  imImage* new_image = imImageCreate(image->width, image->height, image->color_space, image->data_type);
  if (!new_image)
    return NULL;

  if (image->has_alpha)
    imImageAddAlpha(new_image);

  imImageCopy(image, new_image);

  return new_image;
}

imImage* imImageClone(const imImage* image)
{
  assert(image);

  imImage* new_image = imImageCreate(image->width, image->height, image->color_space, image->data_type);
  if (!new_image)
    return NULL;

  if (image->has_alpha)
    imImageAddAlpha(new_image);

  imImageCopyAttributes(image, new_image);

  return new_image;
}

static void iImageMakeGray(imbyte *map, int count, int step)
{
  for(int i = 0; i < count; i++)
  {
    if (*map)
      *map = 255;
    map += step;
  }
}

static void iImageCopyMapAlpha(imbyte *map, imbyte *gldata, int depth, int count)
{
  gldata += depth-1; /* position at first alpha */
  for(int i = 0; i < count; i++)
  {
    *gldata = *map;
    map++;
    gldata += depth;  /* skip to next alpha */
  }
}

static void iImageExpandTranspIndex(imbyte *map, imbyte *gldata, int depth, int count, imbyte index)
{
  gldata += depth-1; /* position at first alpha */
  for(int i = 0; i < count; i++)
  {
    if (*map == index)
      *gldata = 255;

    map++;
    gldata += depth;  /* skip to next alpha */
  }
}

/* To avoid including gl.h */
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_LUMINANCE                      0x1909
#define GL_LUMINANCE_ALPHA                0x190A

void* imImageGetOpenGLData(imImage* image, int *format)
{
  if (!imImageIsBitmap(image))
    return NULL;

  int transp_count;
  imbyte* transp_index = (imbyte*)imImageGetAttribute(image, "TransparencyIndex", NULL, &transp_count);

  int glformat;
  switch(image->color_space)
  {
  case IM_MAP:
    if (image->has_alpha || transp_index)
      glformat = GL_RGBA;
    else
      glformat = GL_RGB;
    break;
  case IM_RGB:
    if (image->has_alpha)
      glformat = GL_RGBA;
    else
      glformat = GL_RGB;
    break;
  case IM_BINARY:
  default: /* IM_GRAY */
    if (image->has_alpha || transp_index)
      glformat = GL_LUMINANCE_ALPHA;
    else
      glformat = GL_LUMINANCE;
    break;
  }

  int depth;
  switch (glformat)
  {
  case GL_RGB:
    depth = 3;
    break;
  case GL_RGBA:
    depth = 4;
    break;
  case GL_LUMINANCE_ALPHA:
    depth = 2;
    break;
  default: /* GL_LUMINANCE */
    depth = 1;
    break;
  }

  int size = image->count*depth;
  imImageSetAttribute(image, "GLDATA", IM_BYTE, size, NULL);
  imbyte* gldata = (imbyte*)imImageGetAttribute(image, "GLDATA", NULL, NULL);

  if (image->color_space == IM_RGB)
    imConvertPacking(image->data[0], gldata, image->width, image->height, depth, IM_BYTE, 0);
  else
  {
    memcpy(gldata, image->data[0], image->size);

    if (image->color_space == IM_MAP)
      imConvertMapToRGB(gldata, image->count, depth, 1, image->palette, image->palette_count);
    else if (image->color_space == IM_BINARY)
      iImageMakeGray(gldata, image->count, (glformat==GL_LUMINANCE_ALPHA)? 2: 1);

    if (image->has_alpha)
      iImageCopyMapAlpha((imbyte*)image->data[1], gldata, depth, image->count);
    else if (transp_index)
    {
      int i;
      for (i=0; i<transp_count; i++)
        iImageExpandTranspIndex((imbyte*)image->data[0], gldata, depth, image->count, transp_index[i]);
    }
  }

  if (format) *format = glformat;
  return gldata;
}

void imImageSetAttribute(imImage* image, const char* attrib, int data_type, int count, const void* data)
{
  assert(image);
  assert(attrib);
  imAttribTable* attrib_table = (imAttribTable*)image->attrib_table;
  if (data)
  {
    if (count == -1 && data_type == IM_BYTE) // Data is zero terminated like a string
      count = strlen((char*)data)+1;

    attrib_table->Set(attrib, data_type, count, data);
  }
  else
    attrib_table->UnSet(attrib);
}

const void* imImageGetAttribute(const imImage* image, const char* attrib, int *data_type, int *count)
{
  assert(image);
  assert(attrib);
  imAttribTable* attrib_table = (imAttribTable*)image->attrib_table;
  return attrib_table->Get(attrib, data_type, count);
}

static void iAttributeTableCopy(const void* src_attrib_table, void* dst_attrib_table)
{
  const imAttribTable* src_table = (const imAttribTable*)src_attrib_table;
  imAttribTable* dst_table = (imAttribTable*)dst_attrib_table;
  dst_table->CopyFrom(*src_table);
}

void imImageCopyAttributes(const imImage* src_image, imImage* dst_image)
{
  assert(src_image);
  assert(dst_image);

  if (src_image->palette && dst_image->palette &&
      src_image->color_space == dst_image->color_space)
  {
    memcpy(dst_image->palette, src_image->palette, 256*sizeof(long));
    dst_image->palette_count = src_image->palette_count;
  }

  iAttributeTableCopy(src_image->attrib_table, dst_image->attrib_table);
}

static int iAttribCB(void* user_data, int index, const char* name, int data_type, int count, const void* data)
{
  (void)data_type;
  (void)data;
  (void)count;
  char** attrib = (char**)user_data;
  attrib[index] = (char*)name;
  return 1;
}

void imImageGetAttributeList(const imImage* image, char** attrib, int *attrib_count)
{
  assert(image);
  assert(attrib_count);

  imAttribTable* attrib_table = (imAttribTable*)image->attrib_table;
  *attrib_count = attrib_table->Count();

  if (attrib) attrib_table->ForEach((void*)attrib, iAttribCB);
}

void imImageSetPalette(imImage* image, long* palette, int palette_count)
{
  assert(image);

  if (image->palette)
  {
    free(image->palette);
    image->palette = palette;
    image->palette_count = palette_count;
  }
}

int imImageMatchSize(const imImage* image1, const imImage* image2)
{
  assert(image1);
  assert(image2);

  return ((image1->width == image2->width) &&
          (image1->height == image2->height));
}

int imImageMatchColor(const imImage* image1, const imImage* image2)
{
  assert(image1);
  assert(image2);

  return (image1->data_type == image2->data_type &&
          image1->color_space == image2->color_space);
}

int imImageMatchDataType(const imImage* image1, const imImage* image2)
{
  assert(image1);
  assert(image2);

  return (image1->data_type == image2->data_type &&
          image1->width == image2->width &&
          image1->height == image2->height);
}

int imImageMatchColorSpace(const imImage* image1, const imImage* image2)
{
  assert(image1);
  assert(image2);

  return (image1->width == image2->width &&
          image1->height == image2->height &&
          image1->color_space == image2->color_space);
}

int imImageMatch(const imImage* image1, const imImage* image2)
{
  assert(image1);
  assert(image2);

  return (image1->data_type == image2->data_type &&
          image1->width == image2->width &&
          image1->height == image2->height &&
          image1->color_space == image2->color_space);
}

void imImageSetBinary(imImage* image)
{
  assert(image);

  if (image->palette)
  {
    image->color_space = IM_BINARY;
    image->palette_count = 2;
    image->palette[0] = imColorEncode(0, 0, 0);
    image->palette[1] = imColorEncode(255, 255, 255);
  }
}

void imImageMakeBinary(imImage *image)
{
  assert(image);

  imbyte *map = (imbyte*)image->data[0];
  for(int i = 0; i < image->count; i++)
  {
    if (*map)
      *map = 1;
    map++;
  }
}

void imImageMakeGray(imImage *image)
{
  assert(image);

  imbyte *map = (imbyte*)image->data[0];
  for(int i = 0; i < image->count; i++)
  {
    if (*map)
      *map = 255;
    map++;
  }
}

static void iImageGrayCheckChange(imImage *image)
{
  int i, do_remap = 0;
  imbyte remap[256];
  imbyte r, g, b;

  for (i = 0; i < image->palette_count; i++)
  {
    imColorDecode(&r, &g, &b, image->palette[i]);

    if (r != g || g != b)
      return;

    remap[i] = r;

    if (r != i)
      do_remap = 1;
  }

  if (do_remap)
  {
    imbyte *map = (imbyte*)image->data[0];
    for(i = 0; i < image->count; i++)
    {
      *map = remap[*map];
      map++;
    }
  }

  image->color_space = IM_GRAY;
  image->palette_count = 256;

  for (i = 0; i < 256; i++)
    image->palette[i] = imColorEncode((imbyte)i, (imbyte)i, (imbyte)i);
}

static int iImageCheckBinary(const imImage* image)
{
  if (image->color_space == IM_MAP && image->palette_count == 2)
  {
    long black = imColorEncode(0, 0, 0);
    long white = imColorEncode(255, 255, 255);
    if ((image->palette[0] == black || image->palette[0] == white) &&
        (image->palette[1] == black || image->palette[1] == white))
    {
      return 1;
    }
  }

  if (image->color_space == IM_GRAY && image->data_type == IM_BYTE)
  {
    imbyte* map = (imbyte*)image->data[0];
    for (int i = 0; i < image->count; i++)
    {
      if (*map != 0 && *map != 255 && *map != 1) // allow 255 and 1
        return 0;

      map++;
    }

    return 1;
  }
  else
    return 0;
}

static void iLoadImageData(imFile* ifile, imImage* image, int *error, int bitmap)
{
  iAttributeTableCopy(ifile->attrib_table, image->attrib_table);

  *error = imFileReadImageData(ifile, image->data[0], bitmap, image->has_alpha);

  if (image->color_space == IM_MAP)
  {
    imFileGetPalette(ifile, image->palette, &image->palette_count);

    // convert to gray if all colors are grays
    iImageGrayCheckChange(image);
  }

  // since Binary is a special case of Gray, check this
  if (iImageCheckBinary(image))
  {
    imImageSetBinary(image);
    imImageMakeBinary(image);
  }
}

imImage* imFileLoadImage(imFile* ifile, int index, int *error)
{
  assert(ifile);

  int width, height, color_mode, data_type;
  *error = imFileReadImageInfo(ifile, index, &width, &height, &color_mode, &data_type);
  if (*error) return NULL; 
  
  imImage* image = imImageCreate(width, height, imColorModeSpace(color_mode), data_type);
  if (!image) 
  {
    *error = IM_ERR_MEM;
    return NULL;
  }

  if (imColorModeHasAlpha(color_mode))
    imImageAddAlpha(image);

  iLoadImageData(ifile, image, error, 0);

  return image;
}

void imFileLoadImageFrame(imFile* ifile, int index, imImage* image, int *error)
{
  assert(ifile);

  int width, height, color_mode, data_type;
  *error = imFileReadImageInfo(ifile, index, &width, &height, &color_mode, &data_type);
  if (*error) return; 
  
  // check if we can reuse the data
  if (image->width != width || 
      image->height != height ||
      image->depth != imColorModeDepth(imColorModeSpace(color_mode)) ||
      image->has_alpha != imColorModeHasAlpha(color_mode) ||
      image->data_type != data_type) 
  {
    *error = IM_ERR_DATA;
    return;
  }

  image->color_space = imColorModeSpace(color_mode);
  iLoadImageData(ifile, image, error, 0);
}

imImage* imFileLoadBitmap(imFile* ifile, int index, int *error)
{
  assert(ifile);

  int width, height, color_mode, data_type;
  *error = imFileReadImageInfo(ifile, index, &width, &height, &color_mode, &data_type);
  if (*error) return NULL; 
  
  imImage* image = imImageCreate(width, height, imColorModeToBitmap(color_mode), IM_BYTE);
  if (!image) 
  {
    *error = IM_ERR_MEM;
    return NULL;
  }

  if (imColorModeHasAlpha(color_mode))
    imImageAddAlpha(image);

  iLoadImageData(ifile, image, error, 1);

  return image;
}

void imFileLoadBitmapFrame(imFile* ifile, int index, imImage* image, int *error)
{
  assert(ifile);

  int width, height, color_mode, data_type;
  *error = imFileReadImageInfo(ifile, index, &width, &height, &color_mode, &data_type);
  if (*error) return; 
  
  // check if we can reuse the data
  if (image->width != width || 
      image->height != height ||
      image->depth != imColorModeDepth(imColorModeToBitmap(color_mode)) ||
      image->has_alpha != imColorModeHasAlpha(color_mode) ||
      image->data_type != IM_BYTE) 
  {
    *error = IM_ERR_DATA;
    return;
  }

  image->color_space = imColorModeToBitmap(color_mode);
  iLoadImageData(ifile, image, error, 1);
}

imImage* imFileLoadImageRegion(imFile* ifile, int index, int bitmap, int *error, 
                          int xmin, int xmax, int ymin, int ymax, int width, int height)
{
  assert(ifile);

  int color_mode, data_type;
  *error = imFileReadImageInfo(ifile, index, NULL, NULL, &color_mode, &data_type);
  if (*error) return NULL; 
  
  imImage* image = imImageCreate(width, height, 
                                 bitmap? imColorModeToBitmap(color_mode): imColorModeSpace(color_mode), 
                                 bitmap? IM_BYTE: data_type);
  if (!image) 
  {
    *error = IM_ERR_MEM;
    return NULL;
  }

  if (imColorModeHasAlpha(color_mode))
    imImageAddAlpha(image);

  imFileSetAttribute(ifile, "ViewXmin", IM_INT, 1, &xmin);
  imFileSetAttribute(ifile, "ViewXmax", IM_INT, 1, &xmax);
  imFileSetAttribute(ifile, "ViewYmin", IM_INT, 1, &ymin);
  imFileSetAttribute(ifile, "ViewYmax", IM_INT, 1, &ymax);
  imFileSetAttribute(ifile, "ViewWidth", IM_INT, 1, &width);
  imFileSetAttribute(ifile, "ViewHeight", IM_INT, 1, &height);

  iLoadImageData(ifile, image, error, bitmap);

  return image;
}

int imFileSaveImage(imFile* ifile, const imImage* image)
{
  assert(ifile);
  assert(image);

  if (image->color_space == IM_MAP)
    imFileSetPalette(ifile, image->palette, image->palette_count);

  iAttributeTableCopy(image->attrib_table, ifile->attrib_table);

  int color_mode = image->color_space;
  if (image->has_alpha)
    color_mode |= IM_ALPHA;

  int error = imFileWriteImageInfo(ifile, image->width, image->height, color_mode, image->data_type);
  if (error) return error;
  
  return imFileWriteImageData(ifile, image->data[0]);
}

imImage* imFileImageLoad(const char* file_name, int index, int *error)
{
  imFile* ifile = imFileOpen(file_name, error);
  if (!ifile) return NULL;
  imImage* image = imFileLoadImage(ifile, index, error);
  imFileClose(ifile);
  return image;
}

imImage* imFileImageLoadBitmap(const char* file_name, int index, int *error)
{
  imFile* ifile = imFileOpen(file_name, error);
  if (!ifile) return NULL;
  imImage* image = imFileLoadBitmap(ifile, index, error);
  imFileClose(ifile);
  return image;
}

imImage* imFileImageLoadRegion(const char* file_name, int index, int bitmap, int *error, 
                               int xmin, int xmax, int ymin, int ymax, int width, int height)
{
  imFile* ifile = imFileOpen(file_name, error);
  if (!ifile) return NULL;
  imImage* image = imFileLoadImageRegion(ifile, index, bitmap, error, xmin, xmax, ymin, ymax, width, height);
  imFileClose(ifile);
  return image;
}

int imFileImageSave(const char* file_name, const char* format, const imImage* image)
{
  int error;
  imFile* ifile = imFileNew(file_name, format, &error);
  if (!ifile) return error;
  error = imFileSaveImage(ifile, image);
  imFileClose(ifile);
  return error;
}
