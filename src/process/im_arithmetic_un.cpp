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

// Fake complex operations for real types
static inline imbyte conj_op(const imbyte& v) {return v;}
static inline imushort conj_op(const imushort& v) {return v;}
static inline int conj_op(const int& v) {return v;}
static inline float conj_op(const float& v) {return v;}
static inline imbyte cpxnorm_op(const imbyte& v) {return v;}
static inline imushort cpxnorm_op(const imushort& v) {return v;}
static inline int cpxnorm_op(const int& v) {return v;}
static inline float cpxnorm_op(const float& v) {return v;}

static inline imcfloat conj_op(const imcfloat& v)
{
  imcfloat r;
  r.real = v.real;
  r.imag = -v.imag;
  return r;
}

static inline imcfloat cpxnorm_op(const imcfloat& v)
{
  imcfloat r;
  float rmag = cpxmag(v);
  if (rmag != 0.0f)
  {
    r.real = v.real/rmag;
    r.imag = v.imag/rmag;
  }
  else
  {
    r.real = 0.0f;
    r.imag = 0.0f;
  }
  return r;
}

template <class T1, class T2> 
static void DoUnaryOp(T1 *map, T2 *new_map, int count, int op)
{
  int i;

  switch(op)
  {
  case IM_UN_ABS:
    for (i = 0; i < count; i++)
      new_map[i] = abs_op((T2)map[i]);
    break;
  case IM_UN_INV:
    for (i = 0; i < count; i++)
      new_map[i] = inv_op((T2)map[i]);
    break;
  case IM_UN_EQL:
    for (i = 0; i < count; i++)
      new_map[i] = (T2)map[i];
    break;
  case IM_UN_LESS:
    for (i = 0; i < count; i++)
      new_map[i] = less_op((T2)map[i]);
    break;
  case IM_UN_SQR:
    for (i = 0; i < count; i++)
      new_map[i] = sqr_op((T2)map[i]);
    break;
  case IM_UN_SQRT:
    for (i = 0; i < count; i++)
      new_map[i] = sqrt_op((T2)map[i]);
    break;
  case IM_UN_LOG:
    for (i = 0; i < count; i++)
      new_map[i] = log_op((T2)map[i]);
    break;
  case IM_UN_SIN:
    for (i = 0; i < count; i++)
      new_map[i] = sin_op((T2)map[i]);
    break;
  case IM_UN_COS:
    for (i = 0; i < count; i++)
      new_map[i] = cos_op((T2)map[i]);
    break;
  case IM_UN_EXP:
    for (i = 0; i < count; i++)
      new_map[i] = exp_op((T2)map[i]);
    break;
  case IM_UN_CONJ:
    for (i = 0; i < count; i++)
      new_map[i] = conj_op((T2)map[i]);
    break;
  case IM_UN_CPXNORM:
    for (i = 0; i < count; i++)
      new_map[i] = cpxnorm_op((T2)map[i]);
    break;
  }
}

template <class T1> 
static void DoUnaryOpByte(T1 *map, imbyte *new_map, int count, int op)
{
  int i;

  switch(op)
  {
  case IM_UN_ABS:
    for (i = 0; i < count; i++)
      new_map[i] = (imbyte)crop_byte(abs_op((int)map[i]));
    break;
  case IM_UN_INV:
    for (i = 0; i < count; i++)
      new_map[i] = (imbyte)crop_byte(inv_op((int)map[i]));   /* will always be 0 */
    break;
  case IM_UN_EQL:
    for (i = 0; i < count; i++)
      new_map[i] = (imbyte)crop_byte((int)map[i]);
    break;
  case IM_UN_LESS:
    for (i = 0; i < count; i++)
      new_map[i] = (imbyte)crop_byte(less_op((int)map[i]));
    break;
  case IM_UN_SQR:
    for (i = 0; i < count; i++)
      new_map[i] = (imbyte)crop_byte(sqr_op((int)map[i]));
    break;
  case IM_UN_SQRT:
    for (i = 0; i < count; i++)
      new_map[i] = (imbyte)crop_byte(sqrt_op((int)map[i]));
    break;
  case IM_UN_LOG:
    for (i = 0; i < count; i++)
      new_map[i] = (imbyte)crop_byte(log_op((int)map[i]));
    break;
  case IM_UN_SIN:
    for (i = 0; i < count; i++)
      new_map[i] = (imbyte)crop_byte(sin_op((int)map[i]));
    break;
  case IM_UN_COS:
    for (i = 0; i < count; i++)
      new_map[i] = (imbyte)crop_byte(cos_op((int)map[i]));
    break;
  case IM_UN_EXP:
    for (i = 0; i < count; i++)
      new_map[i] = (imbyte)crop_byte(exp_op((int)map[i]));
    break;
  }
}

void imProcessUnArithmeticOp(const imImage* src_image, imImage* dst_image, int op)
{
  int total_count = src_image->count * src_image->depth;

  switch(src_image->data_type)
  {
  case IM_BYTE:
    if (dst_image->data_type == IM_FLOAT)
      DoUnaryOp((imbyte*)src_image->data[0], (float*)dst_image->data[0], total_count, op);
    else if (dst_image->data_type == IM_INT)
      DoUnaryOp((imbyte*)src_image->data[0], (int*)dst_image->data[0], total_count, op);
    else if (dst_image->data_type == IM_USHORT)
      DoUnaryOp((imbyte*)src_image->data[0], (imushort*)dst_image->data[0], total_count, op);
    else
      DoUnaryOpByte((imbyte*)src_image->data[0], (imbyte*)dst_image->data[0], total_count, op);
    break;                                                                                
  case IM_USHORT:
    if (dst_image->data_type == IM_BYTE)
      DoUnaryOpByte((imushort*)src_image->data[0], (imbyte*)dst_image->data[0], total_count, op);
    else if (dst_image->data_type == IM_INT)
      DoUnaryOp((imushort*)src_image->data[0], (int*)dst_image->data[0], total_count, op);
    else if (dst_image->data_type == IM_FLOAT)
      DoUnaryOp((imushort*)src_image->data[0], (float*)dst_image->data[0], total_count, op);
    else
      DoUnaryOp((imushort*)src_image->data[0], (imushort*)dst_image->data[0], total_count, op);
    break;                                                                                
  case IM_INT:                                                                           
    if (dst_image->data_type == IM_BYTE)
      DoUnaryOpByte((int*)src_image->data[0], (imbyte*)dst_image->data[0], total_count, op);
    else if (dst_image->data_type == IM_USHORT)
      DoUnaryOp((int*)src_image->data[0], (imushort*)dst_image->data[0], total_count, op);
    else if (dst_image->data_type == IM_FLOAT)
      DoUnaryOp((int*)src_image->data[0], (float*)dst_image->data[0], total_count, op);
    else
      DoUnaryOp((int*)src_image->data[0], (int*)dst_image->data[0], total_count, op);
    break;                                                                                
  case IM_FLOAT:                                                                           
    DoUnaryOp((float*)src_image->data[0], (float*)dst_image->data[0], total_count, op);
    break;                                                                                
  case IM_CFLOAT:            
    DoUnaryOp((imcfloat*)src_image->data[0], (imcfloat*)dst_image->data[0], total_count, op);
    break;
  }
}

template <class T1, class T2> 
static int DoUnaryPontualOp(T1 *map, T2 *new_map, int width, int height, int d, imUnPontualOpFunc func, float* params, int counter)
{
  int offset, cond = 1;
  T2 Value;

  for(int y = 0; y < height; y++)
  {
    offset = y * width;

    for(int x = 0; x < width; x++)
    {
      Value = (T2)func(x, y, d, (float)map[offset + x], &cond, params);
      if (cond) 
        new_map[offset + x] = Value;
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
static int DoUnaryPontualColorOp(T1 **map, T2 **new_map, int width, int height, int src_depth, int dst_depth, imUnPontualColorOpFunc func, float* params, int counter)
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
        src_value[d] = (float)(map[d])[offset + x];

      if (func(x, y, src_value, dst_value, params))
      {
        for(d = 0; d < dst_depth; d++)
          (new_map[d])[offset + x] = (T2)dst_value[d];
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

void imProcessSplitComplex(const imImage* image, imImage* NewImage1, imImage* NewImage2, int polar)
{
  int total_count = image->count*image->depth;

  imcfloat* map = (imcfloat*)image->data[0];
  float* map1 = (float*)NewImage1->data[0];
  float* map2 = (float*)NewImage2->data[0];

  for (int i = 0; i < total_count; i++)
  {
    if (polar)
    {
      map1[i] = cpxmag(map[i]);
      map2[i] = cpxphase(map[i]);
    }
    else
    {
      map1[i] = map[i].real;
      map2[i] = map[i].imag;
    }
  }
}
                  
void imProcessMergeComplex(const imImage* image1, const imImage* image2, imImage* NewImage, int polar)
{
  int total_count = image1->count*image1->depth;

  imcfloat* map = (imcfloat*)NewImage->data[0];
  float* map1 = (float*)image1->data[0];
  float* map2 = (float*)image2->data[0];

  for (int i = 0; i < total_count; i++)
  {
    if (polar)
    {
      float phase = map2[i];
      if (phase > 180) phase -= 360;   
      phase /= 57.2957795f;

      map[i].real = (float)(map1[i] * cos(phase));
      map[i].imag = (float)(map1[i] * sin(phase));
    }
    else
    {
      map[i].real = map1[i];
      map[i].imag = map2[i];
    }
  }
}
