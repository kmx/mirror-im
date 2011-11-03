/** \file
 * \brief Generic Point Operations
 *
 * See Copyright Notice in im_lib.h
 */


#include <im.h>
#include <im_util.h>
#include <im_math.h>
#include <im_complex.h>
#include <im_counter.h>

#include "im_process_pnt.h"
#include "im_math_op.h"

#include <stdlib.h>
#include <memory.h>


template <class T1, class T2> 
static int DoUnaryPointOp(T1 *src_map, T2 *dst_map, int width, int height, int d, imUnaryPointOpFunc func, float* params, int counter)
{
  int offset;
  float dst_value;

  for(int y = 0; y < height; y++)
  {
    offset = y * width;

    for(int x = 0; x < width; x++)
    {
      if (func((float)src_map[offset + x], &dst_value, params, x, y, d)) 
        dst_map[offset + x] = (T2)dst_value;
    }
  
    if (!imCounterInc(counter))
      return 0;
  }

  return 1;
}

int imProcessUnaryPointOp(const imImage* src_image, imImage* dst_image, imUnaryPointOpFunc func, float* params, const char* op_name)
{
  int ret = 0;
  int depth = src_image->has_alpha? src_image->depth+1: src_image->depth;

  int counter = imCounterBegin(op_name? op_name: "UnaryPointOp");
  imCounterTotal(counter, src_image->depth*src_image->height, "Processing...");

  for (int d = 0; d < depth; d++)
  {
    switch(src_image->data_type)
    {
    case IM_BYTE:
      if (dst_image->data_type == IM_FLOAT)
        ret = DoUnaryPointOp((imbyte*)src_image->data[d], (float*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else if (dst_image->data_type == IM_INT)
        ret = DoUnaryPointOp((imbyte*)src_image->data[d], (int*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else if (dst_image->data_type == IM_USHORT)
        ret = DoUnaryPointOp((imbyte*)src_image->data[d], (imushort*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else
        ret = DoUnaryPointOp((imbyte*)src_image->data[d], (imbyte*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      break;                                                                                
    case IM_USHORT:
      if (dst_image->data_type == IM_BYTE)
        ret = DoUnaryPointOp((imushort*)src_image->data[d], (imbyte*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else if (dst_image->data_type == IM_INT)
        ret = DoUnaryPointOp((imushort*)src_image->data[d], (int*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else if (dst_image->data_type == IM_FLOAT)
        ret = DoUnaryPointOp((imushort*)src_image->data[d], (float*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else
        ret = DoUnaryPointOp((imushort*)src_image->data[d], (imushort*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      break;                                                                                
    case IM_INT:                                                                           
      if (dst_image->data_type == IM_BYTE)
        ret = DoUnaryPointOp((int*)src_image->data[d], (imbyte*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else if (dst_image->data_type == IM_USHORT)
        ret = DoUnaryPointOp((int*)src_image->data[d], (imushort*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else if (dst_image->data_type == IM_FLOAT)
        ret = DoUnaryPointOp((int*)src_image->data[d], (float*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else
        ret = DoUnaryPointOp((int*)src_image->data[d], (int*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      break;                                                                                
    case IM_FLOAT:                                                                           
      if (dst_image->data_type == IM_BYTE)
        ret = DoUnaryPointOp((float*)src_image->data[d], (imbyte*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else if (dst_image->data_type == IM_USHORT)
        ret = DoUnaryPointOp((float*)src_image->data[d], (imushort*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else if (dst_image->data_type == IM_INT)
        ret = DoUnaryPointOp((float*)src_image->data[d], (int*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      else
        ret = DoUnaryPointOp((float*)src_image->data[d], (float*)dst_image->data[d], src_image->width, src_image->height, d, func, params, counter);
      break;                                                                                
    }
  }

  imCounterEnd(counter);

  return ret;
}

template <class T1, class T2> 
static int DoUnaryPointColorOp(T1 **src_map, T2 **dst_map, int width, int height, int src_depth, int dst_depth, imUnaryPointColorOpFunc func, float* params, int counter)
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

      if (func(src_value, dst_value, params, x, y))
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

int imProcessUnaryPointColorOp(const imImage* src_image, imImage* dst_image, imUnaryPointColorOpFunc func, float* params, const char* op_name)
{
  int ret = 0;
  int src_depth = src_image->has_alpha? src_image->depth+1: src_image->depth;
  int dst_depth = dst_image->has_alpha? dst_image->depth+1: dst_image->depth;

  int counter = imCounterBegin(op_name? op_name: "UnaryPointColorOp");
  imCounterTotal(counter, src_image->depth*src_image->height, "Processing...");

  switch(src_image->data_type)
  {
  case IM_BYTE:
    if (dst_image->data_type == IM_FLOAT)
      ret = DoUnaryPointColorOp((imbyte**)src_image->data, (float**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoUnaryPointColorOp((imbyte**)src_image->data, (int**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoUnaryPointColorOp((imbyte**)src_image->data, (imushort**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else
      ret = DoUnaryPointColorOp((imbyte**)src_image->data, (imbyte**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    break;                                                                                
  case IM_USHORT:
    if (dst_image->data_type == IM_BYTE)
      ret = DoUnaryPointColorOp((imushort**)src_image->data, (imbyte**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoUnaryPointColorOp((imushort**)src_image->data, (int**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else if (dst_image->data_type == IM_FLOAT)
      ret = DoUnaryPointColorOp((imushort**)src_image->data, (float**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else
      ret = DoUnaryPointColorOp((imushort**)src_image->data, (imushort**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    break;                                                                                
  case IM_INT:                                                                           
    if (dst_image->data_type == IM_BYTE)
      ret = DoUnaryPointColorOp((int**)src_image->data, (imbyte**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoUnaryPointColorOp((int**)src_image->data, (imushort**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else if (dst_image->data_type == IM_FLOAT)
      ret = DoUnaryPointColorOp((int**)src_image->data, (float**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else
      ret = DoUnaryPointColorOp((int**)src_image->data, (int**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    break;                                                                                
  case IM_FLOAT:                                                                           
    if (dst_image->data_type == IM_BYTE)
      ret = DoUnaryPointColorOp((float**)src_image->data, (imbyte**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoUnaryPointColorOp((float**)src_image->data, (imushort**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoUnaryPointColorOp((float**)src_image->data, (int**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    else
      ret = DoUnaryPointColorOp((float**)src_image->data, (float**)dst_image->data, src_image->width, src_image->height, src_depth, dst_depth, func, params, counter);
    break;                                                                                
  }

  imCounterEnd(counter);

  return ret;
}

template <class T1, class T2> 
static int DoMultiPointOp(T1 **src_map, T2 *dst_map, int width, int height, int d, int src_count, imMultiPointOpFunc func, float* params, int counter)
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

      if (func(src_value, &dst_value, params, x, y, d))
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

int imProcessMultiPointOp(const imImage** src_image, int src_count, imImage* dst_image, imMultiPointOpFunc func, float* params, const char* op_name)
{
  int ret = 0;
  int depth = src_image[0]->has_alpha? src_image[0]->depth+1: src_image[0]->depth;
  void** src_map = new void* [src_count];

  int counter = imCounterBegin(op_name? op_name: "MultiPointOp");
  imCounterTotal(counter, src_image[0]->depth*src_image[0]->height, "Processing...");

  for (int d = 0; d < depth; d++)
  {
    for(int i = 0; i < src_count; i++)
      src_map[i] = src_image[i]->data[d];

    switch(src_image[0]->data_type)
    {
    case IM_BYTE:
      if (dst_image->data_type == IM_FLOAT)
        ret = DoMultiPointOp((imbyte**)src_map, (float*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else if (dst_image->data_type == IM_INT)
        ret = DoMultiPointOp((imbyte**)src_map, (int*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else if (dst_image->data_type == IM_USHORT)
        ret = DoMultiPointOp((imbyte**)src_map, (imushort*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else
        ret = DoMultiPointOp((imbyte**)src_map, (imbyte*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      break;                                                                                
    case IM_USHORT:
      if (dst_image->data_type == IM_BYTE)
        ret = DoMultiPointOp((imushort**)src_map, (imbyte*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else if (dst_image->data_type == IM_INT)
        ret = DoMultiPointOp((imushort**)src_map, (int*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else if (dst_image->data_type == IM_FLOAT)
        ret = DoMultiPointOp((imushort**)src_map, (float*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else
        ret = DoMultiPointOp((imushort**)src_map, (imushort*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      break;                                                                                
    case IM_INT:                                                                           
      if (dst_image->data_type == IM_BYTE)
        ret = DoMultiPointOp((int**)src_map, (imbyte*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else if (dst_image->data_type == IM_USHORT)
        ret = DoMultiPointOp((int**)src_map, (imushort*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else if (dst_image->data_type == IM_FLOAT)
        ret = DoMultiPointOp((int**)src_map, (float*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else
        ret = DoMultiPointOp((int**)src_map, (int*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      break;                                                                                
    case IM_FLOAT:                                                                           
      if (dst_image->data_type == IM_BYTE)
        ret = DoMultiPointOp((float**)src_map, (imbyte*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else if (dst_image->data_type == IM_USHORT)
        ret = DoMultiPointOp((float**)src_map, (imushort*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else if (dst_image->data_type == IM_INT)
        ret = DoMultiPointOp((float**)src_map, (int*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      else
        ret = DoMultiPointOp((float**)src_map, (float*)dst_image->data[d], src_image[0]->width, src_image[0]->height, d, src_count, func, params, counter);
      break;                                                                                
    }
  }

  delete [] src_map;

  imCounterEnd(counter);

  return ret;
}

template <class T1, class T2> 
static int DoMultiPointColorOp(T1 ***src_map, T2 **dst_map, int width, int height, int src_depth, int dst_depth, int src_count, imMultiPointColorOpFunc func, float* params, int counter)
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

      if (func(src_value, dst_value, params, x, y))
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

int imProcessMultiPointColorOp(const imImage** src_image, int src_count, imImage* dst_image, imMultiPointColorOpFunc func, float* params, const char* op_name)
{
  int ret = 0;
  int src_depth = src_image[0]->has_alpha? src_image[0]->depth+1: src_image[0]->depth;
  int dst_depth = dst_image->has_alpha? dst_image->depth+1: dst_image->depth;
  void*** src_map = new void** [src_count];

  int counter = imCounterBegin(op_name? op_name: "MultiPointColorOp");
  imCounterTotal(counter, src_image[0]->depth*src_image[0]->height, "Processing...");

  for(int i = 0; i < src_count; i++)
    src_map[i] = src_image[i]->data;

  switch(src_image[0]->data_type)
  {
  case IM_BYTE:
    if (dst_image->data_type == IM_FLOAT)
      ret = DoMultiPointColorOp((imbyte***)src_map, (float**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoMultiPointColorOp((imbyte***)src_map, (int**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoMultiPointColorOp((imbyte***)src_map, (imushort**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else
      ret = DoMultiPointColorOp((imbyte***)src_map, (imbyte**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    break;                                                                                
  case IM_USHORT:
    if (dst_image->data_type == IM_BYTE)
      ret = DoMultiPointColorOp((imushort***)src_map, (imbyte**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoMultiPointColorOp((imushort***)src_map, (int**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_FLOAT)
      ret = DoMultiPointColorOp((imushort***)src_map, (float**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else
      ret = DoMultiPointColorOp((imushort***)src_map, (imushort**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    break;                                                                                
  case IM_INT:                                                                           
    if (dst_image->data_type == IM_BYTE)
      ret = DoMultiPointColorOp((int***)src_map, (imbyte**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoMultiPointColorOp((int***)src_map, (imushort**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_FLOAT)
      ret = DoMultiPointColorOp((int***)src_map, (float**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else
      ret = DoMultiPointColorOp((int***)src_map, (int**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    break;                                                                                
  case IM_FLOAT:                                                                           
    if (dst_image->data_type == IM_BYTE)
      ret = DoMultiPointColorOp((float***)src_map, (imbyte**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoMultiPointColorOp((float***)src_map, (imushort**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoMultiPointColorOp((float***)src_map, (int**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    else
      ret = DoMultiPointColorOp((float***)src_map, (float**)dst_image->data, src_image[0]->width, src_image[0]->height, src_depth, dst_depth, src_count, func, params, counter);
    break;                                                                                
  }

  delete [] src_map;

  imCounterEnd(counter);

  return ret;
}

