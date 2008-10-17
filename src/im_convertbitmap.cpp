/** \file
 * \brief Image Conversion
 *
 * See Copyright Notice in im_lib.h
 * $Id$
 */

#include "im.h"
#include "im_util.h"
#include "im_complex.h"
#include "im_image.h"
#include "im_convert.h"
#include "im_counter.h"

#include <stdlib.h>
#include <assert.h>
#include <memory.h>

int imConvertToBitmap(const imImage* src_image, imImage* dst_image, int cpx2real, float gamma, int abssolute, int cast_mode)
{
  assert(src_image);
  assert(dst_image);

  if (!imImageMatchSize(src_image, dst_image) || !imImageIsBitmap(dst_image))
    return IM_ERR_DATA;

  int counter = imCounterBegin("Building Bitmap");

  int ret;
  if (src_image->data_type == IM_BYTE)
  {
    // NO data type conversion, only color mode conversion
    ret = imConvertColorSpace(src_image, dst_image);
  }
  else
  {
    if (src_image->color_space == IM_RGB || 
        src_image->color_space == IM_GRAY)
    {
      // data type conversion, but NO color mode conversion
      ret = imConvertDataType(src_image, dst_image, cpx2real, gamma, abssolute, cast_mode);
    }
    else
    {
      // data type conversion AND color mode conversion
      imImage* temp_image = imImageCreate(src_image->width, src_image->height, dst_image->color_space, src_image->data_type);
      if (!temp_image)
        ret = IM_ERR_MEM;
      else
      {
        // first convert color_mode in the bigger precision
        ret = imConvertColorSpace(src_image, temp_image);
        if (ret == IM_ERR_NONE)
        {
          // second just convert data type
          ret = imConvertDataType(temp_image, dst_image, cpx2real, gamma, abssolute, cast_mode);
        }
        imImageDestroy(temp_image);
      }
    }
  }

  imCounterEnd(counter);
  return ret;
}


template <class T>
void iDoChangePacking(const T* src_data, T* dst_data, int width, int height, int depth, 
                             int src_is_packed)
{
  int count = width*height;
  if (src_is_packed)
  {
    for (int i = 0; i < count; i++)
    {
      for (int d = 0; d < depth; d++)
      {
        *(dst_data + d*count) = *src_data++;
      }

      dst_data++;
    }
  }
  else
  {
    for (int i = 0; i < count; i++)
    {
      for (int d = 0; d < depth; d++)
      {
        *dst_data++ = *(src_data + d*count);
      }

      src_data++;
    }
  }
}

void imConvertPacking(const void* src_data, void* dst_data, int width, int height, int depth, 
                      int data_type, int src_is_packed)
{
  switch(data_type)
  {
  case IM_BYTE:
    iDoChangePacking((const imbyte*)src_data, (imbyte*)dst_data, width, height, depth, src_is_packed); 
    break;
  case IM_USHORT:
    iDoChangePacking((const imushort*)src_data, (imushort*)dst_data, width, height, depth, src_is_packed); 
    break;
  case IM_INT:
    iDoChangePacking((const int*)src_data, (int*)dst_data, width, height, depth, src_is_packed); 
    break;
  case IM_FLOAT:
    iDoChangePacking((const float*)src_data, (float*)dst_data, width, height, depth, src_is_packed); 
    break;
  case IM_CFLOAT:
    iDoChangePacking((const imcfloat*)src_data, (imcfloat*)dst_data, width, height, depth, src_is_packed); 
    break;
  }
}

