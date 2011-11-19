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

#ifdef _OPENMP
#include <omp.h>
#endif


template <class T1, class T2> 
static int DoUnaryPointOp(T1 *src_map, T2 *dst_map, int width, int height, int depth, imUnaryPointOpFunc func, float* params, int counter)
{
  int count = width * height;

#ifndef _OPENMP
  for (int d = 0; d < depth; d++)
  {
    int plane_offset = d*count;

    for(int y = 0; y < height; y++)
    {
      int line_offset = plane_offset + y * width;

      for(int x = 0; x < width; x++)
      {
        float dst_value;
        if (func((float)src_map[line_offset + x], &dst_value, params, x, y, d)) 
          dst_map[line_offset + x] = (T2)dst_value;
      }
    
      if (!imCounterInc(counter))
        return 0;
    }
  }
#else
  int size = count * depth;
  bool abort = false;

#pragma omp parallel for
  for(int i = 0; i < size; i++)
  {
    #pragma omp flush (abort)
    if (!abort) 
    {
      float dst_value;
      int d = i%count;
      int y = (i - d*count)%width;
      int x = i - d*count - y*width;

      if (func((float)src_map[i], &dst_value, params, x, y, d)) 
        dst_map[i] = (T2)dst_value;

      if (x == width-1 && imCounterHasCallback())
      {
        #pragma omp critical(CounterUpdate)
        if (!imCounterInc(counter))
        {
          abort = true;
          #pragma omp flush (abort)
        }
      }
    }
  }

  if (abort)
    return 0;
#endif

  return 1;
}

int imProcessUnaryPointOp(const imImage* src_image, imImage* dst_image, imUnaryPointOpFunc func, float* params, const char* op_name)
{
  int ret = 0;
  int depth = src_image->has_alpha? src_image->depth+1: src_image->depth;

  int counter = imCounterBegin(op_name? op_name: "UnaryPointOp");
  imCounterTotal(counter, depth*src_image->height, "Processing...");

  switch(src_image->data_type)
  {
  case IM_BYTE:
    if (dst_image->data_type == IM_FLOAT)
      ret = DoUnaryPointOp((imbyte*)src_image->data[0], (float*)dst_image->data[0], src_image->width, src_image->height, depth, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoUnaryPointOp((imbyte*)src_image->data[0], (int*)dst_image->data[0], src_image->width, src_image->height, depth, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoUnaryPointOp((imbyte*)src_image->data[0], (imushort*)dst_image->data[0], src_image->width, src_image->height, depth, func, params, counter);
    else
      ret = DoUnaryPointOp((imbyte*)src_image->data[0], (imbyte*)dst_image->data[0], src_image->width, src_image->height, depth, func, params, counter);
    break;                                                                                
  case IM_USHORT:
    if (dst_image->data_type == IM_BYTE)
      ret = DoUnaryPointOp((imushort*)src_image->data[0], (imbyte*)dst_image->data[0], src_image->width, src_image->height, depth, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoUnaryPointOp((imushort*)src_image->data[0], (int*)dst_image->data[0], src_image->width, src_image->height, depth, func, params, counter);
    else if (dst_image->data_type == IM_FLOAT)
      ret = DoUnaryPointOp((imushort*)src_image->data[0], (float*)dst_image->data[0], src_image->width, src_image->height, depth, func, params, counter);
    else
      ret = DoUnaryPointOp((imushort*)src_image->data[0], (imushort*)dst_image->data[0], src_image->width, src_image->height, depth, func, params, counter);
    break;                                                                                
  case IM_INT:                                                                           
    if (dst_image->data_type == IM_BYTE)
      ret = DoUnaryPointOp((int*)src_image->data[0], (imbyte*)dst_image->data[0], src_image->width, src_image->height, depth, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoUnaryPointOp((int*)src_image->data[0], (imushort*)dst_image->data[0], src_image->width, src_image->height, depth, func, params, counter);
    else if (dst_image->data_type == IM_FLOAT)
      ret = DoUnaryPointOp((int*)src_image->data[0], (float*)dst_image->data[0], src_image->width, src_image->height, depth, func, params, counter);
    else
      ret = DoUnaryPointOp((int*)src_image->data[0], (int*)dst_image->data[0], src_image->width, src_image->height, depth, func, params, counter);
    break;                                                                                
  case IM_FLOAT:                                                                           
    if (dst_image->data_type == IM_BYTE)
      ret = DoUnaryPointOp((float*)src_image->data[0], (imbyte*)dst_image->data[0], src_image->width, src_image->height, depth, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoUnaryPointOp((float*)src_image->data[0], (imushort*)dst_image->data[0], src_image->width, src_image->height, depth, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoUnaryPointOp((float*)src_image->data[0], (int*)dst_image->data[0], src_image->width, src_image->height, depth, func, params, counter);
    else
      ret = DoUnaryPointOp((float*)src_image->data[0], (float*)dst_image->data[0], src_image->width, src_image->height, depth, func, params, counter);
    break;                                                                                
  }

  imCounterEnd(counter);

  return ret;
}

template <class T1, class T2> 
static int DoUnaryPointColorOp(T1 **src_map, T2 **dst_map, int width, int height, int src_depth, int dst_depth, imUnaryPointColorOpFunc func, float* params, int counter)
{
#ifndef _OPENMP
  float src_value[IM_MAXDEPTH];
  float dst_value[IM_MAXDEPTH];

  for(int y = 0; y < height; y++)
  {
    int line_offset = y * width;

    for(int x = 0; x < width; x++)
    {
      int d;

      for(d = 0; d < src_depth; d++)
        src_value[d] = (float)(src_map[d])[line_offset + x];

      if (func(src_value, dst_value, params, x, y))
      {
        for(d = 0; d < dst_depth; d++)
          (dst_map[d])[line_offset + x] = (T2)dst_value[d];
      }
    }
  
    if (!imCounterInc(counter))
      return 0;
  }

#else
  int count = width * height;
  bool abort = false;

#pragma omp parallel for
  for(int i = 0; i < count; i++)
  {
    #pragma omp flush (abort)
    if (!abort) 
    {
      int y = i%width;
      int x = i - y*width;

      int d;
      float src_value[IM_MAXDEPTH];
      float dst_value[IM_MAXDEPTH];

      for(d = 0; d < src_depth; d++)
        src_value[d] = (float)(src_map[d])[i];

      if (func(src_value, dst_value, params, x, y))
      {
        for(d = 0; d < dst_depth; d++)
          (dst_map[d])[i] = (T2)dst_value[d];
      }

      if (x == width-1 && imCounterHasCallback())
      {
        #pragma omp critical(CounterUpdate)
        if (!imCounterInc(counter))
        {
          abort = true;
          #pragma omp flush (abort)
        }
      }
    }
  }

  if (abort)
    return 0;
#endif

  return 1;
}

int imProcessUnaryPointColorOp(const imImage* src_image, imImage* dst_image, imUnaryPointColorOpFunc func, float* params, const char* op_name)
{
  int ret = 0;
  int src_depth = src_image->has_alpha? src_image->depth+1: src_image->depth;
  int dst_depth = dst_image->has_alpha? dst_image->depth+1: dst_image->depth;

  int counter = imCounterBegin(op_name? op_name: "UnaryPointColorOp");
  imCounterTotal(counter, src_image->height, "Processing...");

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
static int DoMultiPointOp(T1 **src_map, T2 *dst_map, int width, int height, int depth, int src_count, imMultiPointOpFunc func, float* params, int counter)
{
  int count = width * height;

#ifndef _OPENMP
  float* src_value = new float [src_count];

  for (int d = 0; d < depth; d++)
  {
    int plane_offset = d*count;

    for(int y = 0; y < height; y++)
    {
      int line_offset = plane_offset + y * width;

      for(int x = 0; x < width; x++)
      {
        float dst_value;

        for(int i = 0; i < src_count; i++)
          src_value[i] = (float)(src_map[i])[line_offset + x];

        if (func(src_value, &dst_value, params, x, y, d))
          dst_map[line_offset + x] = (T2)dst_value;
      }
    
      if (!imCounterInc(counter))
      {
        delete[] src_value;
        return 0;
      }
    }
  }

#else
  int size = count * depth;
  int tcount = omp_get_max_threads();
  float* src_value = new float [src_count*tcount];
  bool abort = false;

#pragma omp parallel for
  for(int i = 0; i < size; i++)
  {
    #pragma omp flush (abort)
    if (!abort) 
    {
      float dst_value;
      int d = i%count;
      int y = (i - d*count)%width;
      int x = i - d*count - y*width;
      int tpos = omp_get_thread_num()*src_count;

      for(int j = 0; j < src_count; j++)
        src_value[tpos + j] = (float)(src_map[j])[i];

      if (func(src_value + tpos, &dst_value, params, x, y, d))
        dst_map[i] = (T2)dst_value;

      if (x == width-1 && imCounterHasCallback())
      {
        #pragma omp critical(CounterUpdate)
        if (!imCounterInc(counter))
        {
          abort = true;
          #pragma omp flush (abort)
        }
      }
    }
  }

  if (abort)
  {
    delete[] src_value;
    return 0;
  }
#endif

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

  for(int i = 0; i < src_count; i++)
    src_map[i] = src_image[i]->data[0];

  switch(src_image[0]->data_type)
  {
  case IM_BYTE:
    if (dst_image->data_type == IM_FLOAT)
      ret = DoMultiPointOp((imbyte**)src_map, (float*)dst_image->data[0], src_image[0]->width, src_image[0]->height, depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoMultiPointOp((imbyte**)src_map, (int*)dst_image->data[0], src_image[0]->width, src_image[0]->height, depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoMultiPointOp((imbyte**)src_map, (imushort*)dst_image->data[0], src_image[0]->width, src_image[0]->height, depth, src_count, func, params, counter);
    else
      ret = DoMultiPointOp((imbyte**)src_map, (imbyte*)dst_image->data[0], src_image[0]->width, src_image[0]->height, depth, src_count, func, params, counter);
    break;                                                                                
  case IM_USHORT:
    if (dst_image->data_type == IM_BYTE)
      ret = DoMultiPointOp((imushort**)src_map, (imbyte*)dst_image->data[0], src_image[0]->width, src_image[0]->height, depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoMultiPointOp((imushort**)src_map, (int*)dst_image->data[0], src_image[0]->width, src_image[0]->height, depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_FLOAT)
      ret = DoMultiPointOp((imushort**)src_map, (float*)dst_image->data[0], src_image[0]->width, src_image[0]->height, depth, src_count, func, params, counter);
    else
      ret = DoMultiPointOp((imushort**)src_map, (imushort*)dst_image->data[0], src_image[0]->width, src_image[0]->height, depth, src_count, func, params, counter);
    break;                                                                                
  case IM_INT:                                                                           
    if (dst_image->data_type == IM_BYTE)
      ret = DoMultiPointOp((int**)src_map, (imbyte*)dst_image->data[0], src_image[0]->width, src_image[0]->height, depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoMultiPointOp((int**)src_map, (imushort*)dst_image->data[0], src_image[0]->width, src_image[0]->height, depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_FLOAT)
      ret = DoMultiPointOp((int**)src_map, (float*)dst_image->data[0], src_image[0]->width, src_image[0]->height, depth, src_count, func, params, counter);
    else
      ret = DoMultiPointOp((int**)src_map, (int*)dst_image->data[0], src_image[0]->width, src_image[0]->height, depth, src_count, func, params, counter);
    break;                                                                                
  case IM_FLOAT:                                                                           
    if (dst_image->data_type == IM_BYTE)
      ret = DoMultiPointOp((float**)src_map, (imbyte*)dst_image->data[0], src_image[0]->width, src_image[0]->height, depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_USHORT)
      ret = DoMultiPointOp((float**)src_map, (imushort*)dst_image->data[0], src_image[0]->width, src_image[0]->height, depth, src_count, func, params, counter);
    else if (dst_image->data_type == IM_INT)
      ret = DoMultiPointOp((float**)src_map, (int*)dst_image->data[0], src_image[0]->width, src_image[0]->height, depth, src_count, func, params, counter);
    else
      ret = DoMultiPointOp((float**)src_map, (float*)dst_image->data[0], src_image[0]->width, src_image[0]->height, depth, src_count, func, params, counter);
    break;                                                                                
  }

  delete [] src_map;

  imCounterEnd(counter);

  return ret;
}

template <class T1, class T2> 
static int DoMultiPointColorOp(T1 ***src_map, T2 **dst_map, int width, int height, int src_depth, int dst_depth, int src_count, imMultiPointColorOpFunc func, float* params, int counter)
{
#ifndef _OPENMP
  float* src_value = new float [src_count*src_depth];

  for(int y = 0; y < height; y++)
  {
    int line_offset = y * width;

    for(int x = 0; x < width; x++)
    {
      float dst_value[IM_MAXDEPTH];

      for(int i = 0; i < src_count; i++)
      {
        for(int d = 0; d < src_depth; d++)
          src_value[i*src_depth + d] = (float)((src_map[i])[d])[line_offset + x];
      }

      if (func(src_value, dst_value, params, x, y))
      {
        for(int d = 0; d < dst_depth; d++)
          (dst_map[d])[line_offset + x] = (T2)dst_value[d];
      }
    }
  
    if (!imCounterInc(counter))
    {
      delete[] src_value;
      return 0;
    }
  }

#else
  int count = width * height;
  int tcount = omp_get_max_threads();
  float* src_value = new float [src_count*src_depth*tcount];
  bool abort = false;

#pragma omp parallel for
  for(int i = 0; i < count; i++)
  {
    #pragma omp flush (abort)
    if (!abort) 
    {
      float dst_value[IM_MAXDEPTH];
      int y = i%width;
      int x = i - y*width;
      int tpos = omp_get_thread_num()*src_count;

      for(int j = 0; j < src_count; j++)
      {
        for(int d = 0; d < src_depth; d++)
          src_value[tpos + j*src_depth + d] = (float)((src_map[j])[d])[i];
      }

      if (func(src_value + tpos, dst_value, params, x, y))
      {
        for(int d = 0; d < dst_depth; d++)
          (dst_map[d])[i] = (T2)dst_value[d];
      }

      if (x == width-1 && imCounterHasCallback())
      {
        #pragma omp critical(CounterUpdate)
        if (!imCounterInc(counter))
        {
          abort = true;
          #pragma omp flush (abort)
        }
      }
    }
  }

  if (abort)
  {
    delete[] src_value;
    return 0;
  }
#endif

  return 1;
}

int imProcessMultiPointColorOp(const imImage** src_image, int src_count, imImage* dst_image, imMultiPointColorOpFunc func, float* params, const char* op_name)
{
  int ret = 0;
  int src_depth = src_image[0]->has_alpha? src_image[0]->depth+1: src_image[0]->depth;
  int dst_depth = dst_image->has_alpha? dst_image->depth+1: dst_image->depth;
  void*** src_map = new void** [src_count];

  int counter = imCounterBegin(op_name? op_name: "MultiPointColorOp");
  imCounterTotal(counter, src_image[0]->height, "Processing...");

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

