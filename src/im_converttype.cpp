/** \file
 * \brief Image Data Type Conversion
 *
 * See Copyright Notice in im_lib.h
 */

#include "im.h"
#include "im_util.h"
#include "im_complex.h"
#include "im_image.h"
#include "im_convert.h"
#include "im_color.h"
#ifdef IM_PROCESS
#include "process/im_process_counter.h"
#include "im_process_pnt.h"
#else
#include "im_counter.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <memory.h>

#ifndef IM_PROCESS
#define IM_INT_PROCESSING     int processing = IM_ERR_NONE;
#define IM_BEGIN_PROCESSING   
#define IM_COUNT_PROCESSING   if (!imCounterInc(counter)) { processing = IM_ERR_COUNTER; break; }
#define IM_END_PROCESSING
#endif


/* IMPORTANT: leave template functions not "static" 
   because of some weird compiler bizarre errors. 
   Report on AIX C++.
*/
#ifdef AIX
#define IM_STATIC 
#else
#define IM_STATIC static
#endif

/* if gamma is applied then factor contains two conversions
   one for applying gamma,
   and other for normal destiny conversion to dst_min-dst_max range.
   because gamma(0) = 0
     For EXP: gamma(x) = (e^(g*x))-1       
     For LOG: gamma(x) = log((g*x)+1)      
   because gamma(1) = 1
     gfactor = exp(g)-1
     gfactor = log(g+1)
*/

inline float iGammaFactor(float range, float gamma)
{
  if (gamma == 0)
    return range;
  else if (gamma < 0)
    return range/float(log((-gamma) + 1));
  else
    return range/float(exp(gamma) - 1);
}

inline float iGammaFunc(float factor, float min, float gamma, float value)
{
  // Here  0<value<1   (always)
  if (gamma != 0)
  {
    if (gamma < 0)
      value = log(value*(-gamma) + 1);
    else
      value = exp(value*gamma) - 1;
  }

  return factor*value + min;
}

inline int iIntMin()
{
  return (int)(-8388608.0f);
}
inline int iIntMax()
{
  return (int)(+8388607.0f);
}

template <class T> 
inline void iDataTypeIntMax(T& max)
{
  int size_of = sizeof(T);
  int data_type = (size_of == 1)? IM_BYTE: (size_of == 2)? IM_USHORT: IM_INT;
  max = (T)imColorMax(data_type);
}

template <class SRCT, class DSTT> 
IM_STATIC int iCopy(int count, const SRCT *src_map, DSTT *dst_map)
{
#pragma omp parallel for if (IM_OMP_MINCOUNT(count))
  for (int i = 0; i < count; i++)
  {
    dst_map[i] = (DSTT)(src_map[i]);
  }

  return IM_ERR_NONE;
}
  
template <class SRCT, class DSTT> 
IM_STATIC int iCopyCrop(int count, const SRCT *src_map, DSTT *dst_map, int abssolute)
{
  DSTT dst_max;
  iDataTypeIntMax(dst_max);

#pragma omp parallel for if (IM_OMP_MINCOUNT(count))
  for (int i = 0; i < count; i++)
  {
    SRCT value;

    if (abssolute)
      value = imAbs(src_map[i]);
    else
      value = src_map[i];

    if (value > dst_max)
      value = (SRCT)dst_max;

    if (!(value >= 0))
      value = 0;

    dst_map[i] = (DSTT)(value);
  }

  return IM_ERR_NONE;
}

template <class SRCT> 
IM_STATIC int iPromote2Cpx(int count, const SRCT *src_map, imcfloat *dst_map)
{
#pragma omp parallel for if (IM_OMP_MINCOUNT(count))
  for (int i = 0; i < count; i++)
  {
    dst_map[i].real = (float)(src_map[i]);
  }

  return IM_ERR_NONE;
}

template <class SRCT, class DSTT> 
IM_STATIC int iConvertInt2Int(int count, const SRCT *src_map, DSTT *dst_map, int abssolute, int cast_mode, int counter)
{
  SRCT min, max;

  if (cast_mode == IM_CAST_MINMAX)
  {
    imMinMax(src_map, count, min, max, abssolute);

    if (min == max)
    {
      max = min + 1;

      if (min != 0)
        min = min - 1;
    }
    if (min >= 0 && max <= 255)
    {
      min = 0;
      max = 255;
    }
  }
  else
  {
    min = 0;
    iDataTypeIntMax(max);
  }

  DSTT dst_max;
  iDataTypeIntMax(dst_max);

  float factor = ((float)dst_max + 1.0f) / ((float)max - (float)min + 1.0f);

  IM_INT_PROCESSING;

#pragma omp parallel for if (IM_OMP_MINCOUNT(count))
  for (int i = 0; i < count; i++)
  {
    #pragma omp flush (processing)
    IM_BEGIN_PROCESSING;

    SRCT value;
    if (abssolute)
      value = imAbs(src_map[i]);
    else
      value = src_map[i];

    if (value >= max)
      dst_map[i] = dst_max;
    else if (value <= min)
      dst_map[i] = 0;
    else
      dst_map[i] = (DSTT)imResample(value - min, factor);

    IM_COUNT_PROCESSING;
    #pragma omp flush (processing)
    IM_END_PROCESSING;
  }

  return processing;
}

template <class SRCT> 
IM_STATIC int iPromoteInt2Real(int count, const SRCT *src_map, float *dst_map, float gamma, int abssolute, int cast_mode, int counter)
{
  SRCT min, max;

  if (cast_mode == IM_CAST_MINMAX)
  {
    imMinMax(src_map, count, min, max, abssolute);

    if (min == max)
    {
      max = min + 1;

      if (min != 0)
        min = min - 1;
    }
    if (min >= 0 && max <= 255)
    {
      min = 0;
      max = 255;
    }
  }
  else
  {
    min = 0;
    iDataTypeIntMax(max);

    if (max == 16777215 && !abssolute)  /* IM_INT */
    {
      min = (SRCT)iIntMin();
      max = (SRCT)iIntMax();
    }
  }

  float range = float(max - min + 1);
  float dst_min = 0.0f;
  float dst_max = 1.0f;
  int size_of = sizeof(SRCT);
  if (size_of == 4 && !abssolute)
  {
    dst_min = -0.5f;
    dst_max = +0.5f;
  }

  gamma = -gamma; // gamma is inverted here, because we are promoting int2real
  float factor = iGammaFactor(1.0f, gamma);

  IM_INT_PROCESSING;

#pragma omp parallel for if (IM_OMP_MINCOUNT(count))
  for (int i = 0; i < count; i++)
  {
    #pragma omp flush (processing)
    IM_BEGIN_PROCESSING;

    float fvalue;
    if (abssolute)
      fvalue = (imAbs(src_map[i]) - min + 0.5f)/range; 
    else
      fvalue = (src_map[i] - min + 0.5f)/range; 

    // Now 0 <= value <= 1 (if min-max are correct)

    if (fvalue >= 1)
      dst_map[i] = dst_max;
    else if (fvalue <= 0)
      dst_map[i] = dst_min;
    else
      dst_map[i] = iGammaFunc(factor, dst_min, gamma, fvalue);

    IM_COUNT_PROCESSING;
    #pragma omp flush (processing)
    IM_END_PROCESSING;
  }

  return processing;
}

template <class DSTT> 
IM_STATIC int iDemoteReal2Int(int count, const float *src_map, DSTT *dst_map, float gamma, int abssolute, int cast_mode, int counter)
{
  float min, max;

  DSTT dst_min = 0, dst_max;
  iDataTypeIntMax(dst_max);
  if (dst_max == 16777215 && !abssolute)  /* IM_INT */
  {
    dst_min = (DSTT)iIntMin();
    dst_max = (DSTT)iIntMax();
  }

  if (cast_mode == IM_CAST_MINMAX)
  {
    imMinMax(src_map, count, min, max, abssolute);

    if (min == max)
    {
      max = min + 1;

      if (min != 0)
        min = min - 1;
    }
  }
  else
  {
    min = 0;
    max = 1;
  }

  int dst_range = dst_max - dst_min + 1;
  float range = max - min;

  float factor = iGammaFactor((float)dst_range, gamma);

  IM_INT_PROCESSING;

#pragma omp parallel for if (IM_OMP_MINCOUNT(count))
  for (int i = 0; i < count; i++)
  {
    #pragma omp flush (processing)
    IM_BEGIN_PROCESSING;

    float value;
    if (abssolute)
      value = ((float)imAbs(src_map[i]) - min)/range; 
    else
      value = (src_map[i] - min)/range; 

    // Now 0 <= value <= 1 (if min-max are correct)

    if (value >= 1)
      dst_map[i] = dst_max;
    else if (value <= 0)
      dst_map[i] = dst_min;
    else
    {
      value = iGammaFunc(factor, (float)dst_min, gamma, value);
      int ivalue = imRound(value);
      if (ivalue >= dst_max)
        dst_map[i] = dst_max;
      else if (ivalue <= dst_min)
        dst_map[i] = dst_min;
      else
        dst_map[i] = (DSTT)imRound(value - 0.5f);
    }

    IM_COUNT_PROCESSING;
    #pragma omp flush (processing)
    IM_END_PROCESSING;
  }

  return processing;
}

static int iDemoteCpx2Real(int count, const imcfloat* src_map, float *dst_map, int cpx2real)
{
  float (*CpxCnv)(const imcfloat& cpx) = NULL;

  switch(cpx2real)
  {
  case IM_CPX_REAL:  CpxCnv = cpxreal; break;
  case IM_CPX_IMAG:  CpxCnv = cpximag; break;
  case IM_CPX_MAG:   CpxCnv = cpxmag; break;
  case IM_CPX_PHASE: CpxCnv = cpxphase; break;
  }

#pragma omp parallel for if (IM_OMP_MINCOUNT(count))
  for (int i = 0; i < count; i++)
  {
    dst_map[i] = CpxCnv(src_map[i]);
  }

  return IM_ERR_NONE;
}
                                                                     
template <class DSTT> 
IM_STATIC int iDemoteCpx2Int(int count, const imcfloat* src_map, DSTT *dst_map, int cpx2real, float gamma, int abssolute, int cast_mode, int counter)
{
  float* real_map = (float*)malloc(count*sizeof(float));
  if (!real_map) return IM_ERR_MEM;

  iDemoteCpx2Real(count, src_map, real_map, cpx2real);

  if (iDemoteReal2Int(count, real_map, dst_map, gamma, abssolute, cast_mode, counter) != IM_ERR_NONE)
  {
    free(real_map);
    return IM_ERR_COUNTER;
  }

  free(real_map);
  return IM_ERR_NONE;
}

template <class SRCT> 
IM_STATIC int iPromoteInt2Cpx(int count, const SRCT* src_map, imcfloat *dst_map, float gamma, int abssolute, int cast_mode, int counter)
{
  float* real_map = (float*)malloc(count*sizeof(float));
  if (!real_map) return IM_ERR_MEM;

  if (iPromoteInt2Real(count, src_map, real_map, gamma, abssolute, cast_mode, counter) != IM_ERR_NONE)
  {
    free(real_map);
    return IM_ERR_COUNTER;
  }

  iPromote2Cpx(count, real_map, dst_map);

  free(real_map);
  return IM_ERR_NONE;
}

#ifdef IM_PROCESS
int imProcessConvertDataType(const imImage* src_image, imImage* dst_image, int cpx2real, float gamma, int abssolute, int cast_mode)
#else
int imConvertDataType(const imImage* src_image, imImage* dst_image, int cpx2real, float gamma, int abssolute, int cast_mode)
#endif
{
  assert(src_image);
  assert(dst_image);

  if (!imImageMatchColorSpace(src_image, dst_image))
    return IM_ERR_DATA;

  if (src_image->data_type == dst_image->data_type)
    return IM_ERR_DATA;

  int total_count = src_image->depth * src_image->count;
  int ret = IM_ERR_DATA;
#ifdef IM_PROCESS
  int counter = imProcessCounterBegin("Convert Data Type");
#else
  int counter = imCounterBegin("Convert Data Type");
#endif
  char msg[50];
  sprintf(msg, "Converting to %s...", imDataTypeName(dst_image->data_type));
  imCounterTotal(counter, total_count, msg);

  switch(src_image->data_type)
  {
  case IM_BYTE:
    switch(dst_image->data_type)
    {
    case IM_USHORT:
      if (cast_mode == IM_CAST_DIRECT)
        ret = iCopy(total_count, (const imbyte*)src_image->data[0], (imushort*)dst_image->data[0]);
      else
        ret = iConvertInt2Int(total_count, (const imbyte*)src_image->data[0], (imushort*)dst_image->data[0], abssolute, cast_mode, counter);
      break;
    case IM_INT:
      if (cast_mode == IM_CAST_DIRECT)
        ret = iCopy(total_count, (const imbyte*)src_image->data[0], (int*)dst_image->data[0]);
      else
        ret = iConvertInt2Int(total_count, (const imbyte*)src_image->data[0], (int*)dst_image->data[0], abssolute, cast_mode, counter);
      break;
    case IM_FLOAT:
      if (cast_mode == IM_CAST_DIRECT)
        ret = iCopy(total_count, (const imbyte*)src_image->data[0], (float*)dst_image->data[0]);
      else
        ret = iPromoteInt2Real(total_count, (const imbyte*)src_image->data[0], (float*)dst_image->data[0], gamma, abssolute, cast_mode, counter);
      break;
    case IM_CFLOAT:
      if (cast_mode == IM_CAST_DIRECT)
        ret = iPromote2Cpx(total_count, (const imbyte*)src_image->data[0], (imcfloat*)dst_image->data[0]);
      else
        ret = iPromoteInt2Cpx(total_count, (const imbyte*)src_image->data[0], (imcfloat*)dst_image->data[0], gamma, abssolute, cast_mode, counter);
      break;
    }
    break;
  case IM_USHORT:
    switch(dst_image->data_type)
    {
    case IM_BYTE:
      if (cast_mode == IM_CAST_DIRECT)
        ret = iCopyCrop(total_count, (const imushort*)src_image->data[0], (imbyte*)dst_image->data[0], abssolute);
      else
        ret = iConvertInt2Int(total_count, (const imushort*)src_image->data[0], (imbyte*)dst_image->data[0], abssolute, cast_mode, counter);
      break;
    case IM_INT:
      if (cast_mode == IM_CAST_DIRECT)
        ret = iCopy(total_count, (const imushort*)src_image->data[0], (int*)dst_image->data[0]);
      else
        ret = iConvertInt2Int(total_count, (const imushort*)src_image->data[0], (int*)dst_image->data[0], abssolute, cast_mode, counter);
      break;
    case IM_FLOAT:
      if (cast_mode == IM_CAST_DIRECT)
        ret = iCopy(total_count, (const imushort*)src_image->data[0], (float*)dst_image->data[0]);
      else
        ret = iPromoteInt2Real(total_count, (const imushort*)src_image->data[0], (float*)dst_image->data[0], gamma, abssolute, cast_mode, counter);
      break;
    case IM_CFLOAT:
      if (cast_mode == IM_CAST_DIRECT)
        ret = iPromote2Cpx(total_count, (const imushort*)src_image->data[0], (imcfloat*)dst_image->data[0]);
      else
        ret = iPromoteInt2Cpx(total_count, (const imushort*)src_image->data[0], (imcfloat*)dst_image->data[0], gamma, abssolute, cast_mode, counter);
      break;
    }
    break;
  case IM_INT:
    switch(dst_image->data_type)
    {
    case IM_BYTE:
      if (cast_mode == IM_CAST_DIRECT)
        ret = iCopyCrop(total_count, (const int*)src_image->data[0], (imbyte*)dst_image->data[0], abssolute);
      else
        ret = iConvertInt2Int(total_count, (const int*)src_image->data[0], (imbyte*)dst_image->data[0], abssolute, cast_mode, counter);
      break;
    case IM_USHORT:
      if (cast_mode == IM_CAST_DIRECT)
        ret = iCopyCrop(total_count, (const int*)src_image->data[0], (imushort*)dst_image->data[0], abssolute);
      else
        ret = iConvertInt2Int(total_count, (const int*)src_image->data[0], (imushort*)dst_image->data[0], abssolute, cast_mode, counter);
      break;
    case IM_FLOAT:
      if (cast_mode == IM_CAST_DIRECT)
        ret = iCopy(total_count, (const int*)src_image->data[0], (float*)dst_image->data[0]);
      else
        ret = iPromoteInt2Real(total_count, (const int*)src_image->data[0], (float*)dst_image->data[0], gamma, abssolute, cast_mode, counter);
      break;
    case IM_CFLOAT:
      if (cast_mode == IM_CAST_DIRECT)
        ret = iPromote2Cpx(total_count, (const int*)src_image->data[0], (imcfloat*)dst_image->data[0]);
      else
        ret = iPromoteInt2Cpx(total_count, (const int*)src_image->data[0], (imcfloat*)dst_image->data[0], gamma, abssolute, cast_mode, counter);
      break;
    }
    break;
  case IM_FLOAT:
    switch(dst_image->data_type)
    {
    case IM_BYTE:
      if (cast_mode == IM_CAST_DIRECT)
        ret = iCopyCrop(total_count, (const float*)src_image->data[0], (imbyte*)dst_image->data[0], abssolute);
      else
        ret = iDemoteReal2Int(total_count, (const float*)src_image->data[0], (imbyte*)dst_image->data[0], gamma, abssolute, cast_mode, counter);
      break;
    case IM_USHORT:
      if (cast_mode == IM_CAST_DIRECT)
        ret = iCopyCrop(total_count, (const float*)src_image->data[0], (imushort*)dst_image->data[0], abssolute);
      else
        ret = iDemoteReal2Int(total_count, (const float*)src_image->data[0], (imushort*)dst_image->data[0], gamma, abssolute, cast_mode, counter);
      break;
    case IM_INT:
      if (cast_mode == IM_CAST_DIRECT)
        ret = iCopy(total_count, (const float*)src_image->data[0], (int*)dst_image->data[0]);
      else
        ret = iDemoteReal2Int(total_count, (const float*)src_image->data[0], (int*)dst_image->data[0], gamma, abssolute, cast_mode, counter);
      break;
    case IM_CFLOAT:
      ret = iPromote2Cpx(total_count, (const float*)src_image->data[0], (imcfloat*)dst_image->data[0]);
      break;
    }
    break;
  case IM_CFLOAT:
    switch(dst_image->data_type)                                                                       
    {
    case IM_BYTE:
      ret = iDemoteCpx2Int(total_count, (const imcfloat*)src_image->data[0], (imbyte*)dst_image->data[0], cpx2real, gamma, abssolute, cast_mode, counter);
      break;
    case IM_USHORT:
      ret = iDemoteCpx2Int(total_count, (const imcfloat*)src_image->data[0], (imushort*)dst_image->data[0], cpx2real, gamma, abssolute, cast_mode, counter);
      break;
    case IM_INT:
      ret = iDemoteCpx2Int(total_count, (const imcfloat*)src_image->data[0], (int*)dst_image->data[0], cpx2real, gamma, abssolute, cast_mode, counter);
      break;
    case IM_FLOAT:
      ret = iDemoteCpx2Real(total_count, (const imcfloat*)src_image->data[0], (float*)dst_image->data[0], cpx2real);
      break;
    }
    break;
  }

#ifdef IM_PROCESS
  imProcessCounterEnd(counter);
#else
  imCounterEnd(counter);
#endif
  return ret;
}
