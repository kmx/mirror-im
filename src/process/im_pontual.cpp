/** \file
 * \brief Unary Arithmetic Operations
 *
 * See Copyright Notice in im_lib.h
 * $Id$
 */


#include <im.h>
#include <im_util.h>
#include <im_math.h>
#include <im_complex.h>
#include <im_counter.h>

#include "im_process_pon.h"
#include "im_math_op.h"

#include <stdlib.h>
#include <memory.h>


template <class T1, class T2> 
static int DoUnaryPontualOp(T1 *src_map, T2 *dst_map, int width, int height, int d, imUnPontualOpFunc func, float* params, int counter)
{
  int offset;
  float dst_value;

  for(int y = 0; y < height; y++)
  {
    offset = y * width;

    for(int x = 0; x < width; x++)
    {
      if (func(x, y, d, (float)src_map[offset + x], &dst_value, params)) 
        dst_map[offset + x] = (T2)dst_value;
    }
  
    if (!imCounterInc(counter))
      return 0;
  }

  return 1;
}

int imProcessUnPontualOp(const imImage* src_image, imImage* dst_image, imUnPontualOpFunc func, const char* op_name, float* params)
{
  int ret = 0;
  int depth = src_image->has_alpha? src_image->depth+1: src_image->depth;

  int counter = imCounterBegin(op_name);
  imCounterTotal(counter, src_image->depth*src_image->height, "Processing...");

  for (int d = 0; d < depth; d++)
  {
    switch(src_image->data_type)
    {
    case IM_BYTE:
      if (dst_image->data_type == IM_FLOAT)
        ret = DoUnaryPontualOp((imbyte*)src_image->data[d], (float*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else if (dst_image->data_type == IM_INT)
        ret = DoUnaryPontualOp((imbyte*)src_image->data[d], (int*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else if (dst_image->data_type == IM_USHORT)
        ret = DoUnaryPontualOp((imbyte*)src_image->data[d], (imushort*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else
        ret = DoUnaryPontualOp((imbyte*)src_image->data[d], (imbyte*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      break;                                                                                
    case IM_USHORT:
      if (dst_image->data_type == IM_BYTE)
        ret = DoUnaryPontualOp((imushort*)src_image->data[d], (imbyte*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else if (dst_image->data_type == IM_INT)
        ret = DoUnaryPontualOp((imushort*)src_image->data[d], (int*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else if (dst_image->data_type == IM_FLOAT)
        ret = DoUnaryPontualOp((imushort*)src_image->data[d], (float*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else
        ret = DoUnaryPontualOp((imushort*)src_image->data[d], (imushort*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      break;                                                                                
    case IM_INT:                                                                           
      if (dst_image->data_type == IM_BYTE)
        ret = DoUnaryPontualOp((int*)src_image->data[d], (imbyte*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else if (dst_image->data_type == IM_USHORT)
        ret = DoUnaryPontualOp((int*)src_image->data[d], (imushort*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else if (dst_image->data_type == IM_FLOAT)
        ret = DoUnaryPontualOp((int*)src_image->data[d], (float*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else
        ret = DoUnaryPontualOp((int*)src_image->data[d], (int*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      break;                                                                                
    case IM_FLOAT:                                                                           
      if (dst_image->data_type == IM_BYTE)
        ret = DoUnaryPontualOp((float*)src_image->data[d], (imbyte*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else if (dst_image->data_type == IM_USHORT)
        ret = DoUnaryPontualOp((float*)src_image->data[d], (imushort*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else if (dst_image->data_type == IM_INT)
        ret = DoUnaryPontualOp((float*)src_image->data[d], (int*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else
        ret = DoUnaryPontualOp((float*)src_image->data[d], (float*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      break;                                                                                
    }
  }

  imCounterEnd(counter);

  return ret;
}

template <class T1, class T2> 
static int DoUnaryPontualColorOp(T1 **src_map, T2 **dst_map, int width, int height, int src_depth, int dst_depth, imUnPontualColorOpFunc func, float* params, int counter)
{
  int offset, d;
  float* src_value = new float [src_depth];
  float* dst_value = new float [dst_depth];

  for(int y = 0; y < height; y++)
  {
    offset = y * width;

    for(int x = 0; x < width; x++)
    {
      for(d = 0; d < src_depth; d++)
        src_value[d] = (float)(src_map[d])[offset + x];

      if (func(x, y, src_value, dst_value, params))
      {
        for(d = 0; d < dst_depth; d++)
          (dst_map[d])[offset + x] = (T2)dst_value[d];
      }
    }
  
    if (!imCounterInc(counter))
    {
      delete[] src_value;
      delete[] dst_value;
      return 0;
    }
  }

  delete[] src_value;
  delete[] dst_value;
  return 1;
}

int imProcessUnPontualColorOp(const imImage* src_image, imImage* dst_image, imUnPontualColorOpFunc func, const char* op_name, float* params)
{
  int ret = 0;
  int src_depth = src_image->has_alpha? src_image->depth+1: src_image->depth;
  int dst_depth = dst_image->has_alpha? dst_image->depth+1: dst_image->depth;

  int counter = imCounterBegin(op_name);
  imCounterTotal(counter, src_image->depth*src_image->height, "Processing...");

  switch(src_image->data_type)
  {
  case IM_BYTE:
    if (dst_image->data_type == IM_FLOAT)
      ret = DoUnaryPontualColorOp((imbyte**)src_image->data, (float**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoUnaryPontualColorOp((imbyte**)src_image->data, (int**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoUnaryPontualColorOp((imbyte**)src_image->data, (imushort**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else
      ret = DoUnaryPontualColorOp((imbyte**)src_image->data, (imbyte**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    break;                                                                                
  case IM_USHORT:
    if (dst_image->data_type == IM_BYTE)
      ret = DoUnaryPontualColorOp((imushort**)src_image->data, (imbyte**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoUnaryPontualColorOp((imushort**)src_image->data, (int**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else if (dst_image->data_type == IM_FLOAT)
      ret = DoUnaryPontualColorOp((imushort**)src_image->data, (float**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else
      ret = DoUnaryPontualColorOp((imushort**)src_image->data, (imushort**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    break;                                                                                
  case IM_INT:                                                                           
    if (dst_image->data_type == IM_BYTE)
      ret = DoUnaryPontualColorOp((int**)src_image->data, (imbyte**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoUnaryPontualColorOp((int**)src_image->data, (imushort**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else if (dst_image->data_type == IM_FLOAT)
      ret = DoUnaryPontualColorOp((int**)src_image->data, (float**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else
      ret = DoUnaryPontualColorOp((int**)src_image->data, (int**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    break;                                                                                
  case IM_FLOAT:                                                                           
    if (dst_image->data_type == IM_BYTE)
      ret = DoUnaryPontualColorOp((float**)src_image->data, (imbyte**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoUnaryPontualColorOp((float**)src_image->data, (imushort**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoUnaryPontualColorOp((float**)src_image->data, (int**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else
      ret = DoUnaryPontualColorOp((float**)src_image->data, (float**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    break;                                                                                
  }

  imCounterEnd(counter);

  return ret;
}

template <class T1, class T2> 
static int DoMultiPontualOp(T1 **src_map, T2 *dst_map, int width, int height, int d, int src_count, imMultiPontualOpFunc func, float* params, int counter)
{
  int offset, i;
  float* src_value = new float [src_count];
  float dst_value;

  for(int y = 0; y < height; y++)
  {
    offset = y * width;

    for(int x = 0; x < width; x++)
    {
      for(i = 0; i < src_count; i++)
        src_value[i] = (float)(src_map[i])[offset + x];

      if (func(x, y, d, src_value, &dst_value, params))
        dst_map[offset + x] = (T2)dst_value;
    }
  
    if (!imCounterInc(counter))
    {
      delete[] src_value;
      return 0;
    }
  }

  delete[] src_value;
  return 1;
}

int imProcessMultiPontualOp(const imImage** src_image, int src_count, imImage* dst_image, imMultiPontualOpFunc func, const char* op_name, float* params)
{
  int ret = 0;
  int depth = src_image[0]->has_alpha? src_image[0]->depth+1: src_image[0]->depth;
  void** src_map = new void* [src_count];

  int counter = imCounterBegin(op_name);
  imCounterTotal(counter, src_image[0]->depth*src_image[0]->height, "Processing...");

  for (int d = 0; d < depth; d++)
  {
    for(int i = 0; i < src_count; i++)
      src_map[i] = src_image[i]->data[d];

    switch(src_image[0]->data_type)
    {
    case IM_BYTE:
      if (dst_image->data_type == IM_FLOAT)
        ret = DoMultiPontualOp((imbyte**)src_map, (float*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else if (dst_image->data_type == IM_INT)
        ret = DoMultiPontualOp((imbyte**)src_map, (int*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else if (dst_image->data_type == IM_USHORT)
        ret = DoMultiPontualOp((imbyte**)src_map, (imushort*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else
        ret = DoMultiPontualOp((imbyte**)src_map, (imbyte*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      break;                                                                                
    case IM_USHORT:
      if (dst_image->data_type == IM_BYTE)
        ret = DoMultiPontualOp((imushort**)src_map, (imbyte*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else if (dst_image->data_type == IM_INT)
        ret = DoMultiPontualOp((imushort**)src_map, (int*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else if (dst_image->data_type == IM_FLOAT)
        ret = DoMultiPontualOp((imushort**)src_map, (float*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else
        ret = DoMultiPontualOp((imushort**)src_map, (imushort*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      break;                                                                                
    case IM_INT:                                                                           
      if (dst_image->data_type == IM_BYTE)
        ret = DoMultiPontualOp((int**)src_map, (imbyte*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else if (dst_image->data_type == IM_USHORT)
        ret = DoMultiPontualOp((int**)src_map, (imushort*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else if (dst_image->data_type == IM_FLOAT)
        ret = DoMultiPontualOp((int**)src_map, (float*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else
        ret = DoMultiPontualOp((int**)src_map, (int*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      break;                                                                                
    case IM_FLOAT:                                                                           
      if (dst_image->data_type == IM_BYTE)
        ret = DoMultiPontualOp((float**)src_map, (imbyte*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else if (dst_image->data_type == IM_USHORT)
        ret = DoMultiPontualOp((float**)src_map, (imushort*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else if (dst_image->data_type == IM_INT)
        ret = DoMultiPontualOp((float**)src_map, (int*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else
        ret = DoMultiPontualOp((float**)src_map, (float*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      break;                                                                                
    }
  }

  delete [] src_map;

  imCounterEnd(counter);

  return ret;
}

template <class T1, class T2> 
static int DoMultiPontualColorOp(T1 ***src_map, T2 **dst_map, int width, int height, int src_depth, int dst_depth, int src_count, imMultiPontualColorOpFunc func, float* params, int counter)
{
  int offset, d, i;
  float** src_value = new float* [src_count];
  float* dst_value = new float [dst_depth];

  for(i = 0; i < src_count; i++)
    src_value[i] = new float [src_depth];

  for(int y = 0; y < height; y++)
  {
    offset = y * width;

    for(int x = 0; x < width; x++)
    {
      for(i = 0; i < src_count; i++)
      {
        for(d = 0; d < src_depth; d++)
          (src_value[i])[d] = (float)((src_map[i])[d])[offset + x];
      }

      if (func(x, y, src_value, dst_value, params))
      {
        for(d = 0; d < dst_depth; d++)
          (dst_map[d])[offset + x] = (T2)dst_value[d];
      }
    }
  
    if (!imCounterInc(counter))
    {
      for(i = 0; i < src_count; i++)
        delete[] src_value[i];
      delete[] src_value;
      delete[] dst_value;
      return 0;
    }
  }

  for(i = 0; i < src_count; i++)
    delete[] src_value[i];
  delete[] src_value;
  delete[] dst_value;
  return 1;
}

int imProcessMultiPontualColorOp(const imImage** src_image, int src_count, imImage* dst_image, imMultiPontualColorOpFunc func, const char* op_name, float* params)
{
  int ret = 0;
  int src_depth = src_image[0]->has_alpha? src_image[0]->depth+1: src_image[0]->depth;
  int dst_depth = dst_image->has_alpha? dst_image->depth+1: dst_image->depth;
  void*** src_map = new void** [src_count];

  int counter = imCounterBegin(op_name);
  imCounterTotal(counter, src_image[0]->depth*src_image[0]->height, "Processing...");

  for(int i = 0; i < src_count; i++)
    src_map[i] = src_image[i]->data;

  switch(src_image[0]->data_type)
  {
  case IM_BYTE:
    if (dst_image->data_type == IM_FLOAT)
      ret = DoMultiPontualColorOp((imbyte***)src_map, (float**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoMultiPontualColorOp((imbyte***)src_map, (int**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoMultiPontualColorOp((imbyte***)src_map, (imushort**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else
      ret = DoMultiPontualColorOp((imbyte***)src_map, (imbyte**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    break;                                                                                
  case IM_USHORT:
    if (dst_image->data_type == IM_BYTE)
      ret = DoMultiPontualColorOp((imushort***)src_map, (imbyte**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoMultiPontualColorOp((imushort***)src_map, (int**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_FLOAT)
      ret = DoMultiPontualColorOp((imushort***)src_map, (float**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else
      ret = DoMultiPontualColorOp((imushort***)src_map, (imushort**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    break;                                                                                
  case IM_INT:                                                                           
    if (dst_image->data_type == IM_BYTE)
      ret = DoMultiPontualColorOp((int***)src_map, (imbyte**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoMultiPontualColorOp((int***)src_map, (imushort**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_FLOAT)
      ret = DoMultiPontualColorOp((int***)src_map, (float**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else
      ret = DoMultiPontualColorOp((int***)src_map, (int**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    break;                                                                                
  case IM_FLOAT:                                                                           
    if (dst_image->data_type == IM_BYTE)
      ret = DoMultiPontualColorOp((float***)src_map, (imbyte**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoMultiPontualColorOp((float***)src_map, (imushort**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoMultiPontualColorOp((float***)src_map, (int**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else
      ret = DoMultiPontualColorOp((float***)src_map, (float**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    break;                                                                                
  }

  delete [] src_map;

  imCounterEnd(counter);

  return ret;
}

