/** \file
 * \brief Histogram Based Operations
 *
 * See Copyright Notice in im_lib.h
 */


#include <im.h>
#include <im_util.h>
#include <im_math.h>

#include "im_process_pnt.h"
#include "im_process_ana.h"

#include <stdlib.h>
#include <memory.h>


template <class T>
static void DoExpandHistogram(T* src_map, T* dst_map, int size, int depth, int hcount, int low_level, int high_level)
{
  int i, value;

  T* re_map = new T [hcount];
  memset(re_map, 0, hcount*sizeof(T));

  int range = high_level-low_level+1;
  float factor = (float)hcount / (float)range;

  for (i = 0; i < hcount; i++)
  {             
    if (i < low_level)
      re_map[i] = 0;
    else if (i > high_level)
      re_map[i] = (T)(hcount-1);
    else
    {
      value = imResample(i - low_level, factor);
      re_map[i] = (T)IM_CROPMAX(value, hcount-1);
    }
  }

  int total_count = size*depth;
  for (i = 0; i < total_count; i++)
    dst_map[i] = re_map[src_map[i]];

  delete [] re_map;
}

void imProcessExpandHistogram(const imImage* src_image, imImage* dst_image, float percent)
{
  int low_level, high_level;
  imCalcPercentMinMax(src_image, percent, 0, &low_level, &high_level);

  int hcount = 256;
  if (src_image->data_type == IM_USHORT)
    hcount = 65536;

  if (src_image->data_type == IM_USHORT)
    DoExpandHistogram((imushort*)src_image->data[0], (imushort*)dst_image->data[0], src_image->count, src_image->depth, hcount, low_level, high_level);
  else
    DoExpandHistogram((imbyte*)src_image->data[0], (imbyte*)dst_image->data[0], src_image->count, src_image->depth, hcount, low_level, high_level);
}

template <class T>
static void DoEqualizeHistogram(T* src_map, T* dst_map, int size, int depth, int hcount, unsigned long* histo)
{
  int i, value;

  T* re_map = new T [hcount];
  memset(re_map, 0, hcount*sizeof(T));

  float factor = (float)hcount / (float)size;

  for (i = 0; i < hcount; i++)
  {             
    value = imResample(histo[i], factor);
    re_map[i] = (T)IM_CROPMAX(value, hcount-1);
  }

  int total_count = size*depth;
  for (i = 0; i < total_count; i++)
    dst_map[i] = re_map[src_map[i]];

  delete [] re_map;
}

void imProcessEqualizeHistogram(const imImage* src_image, imImage* dst_image)
{
  int hcount = 256;
  if (src_image->data_type == IM_USHORT)
    hcount = 65536;

  unsigned long* histo = new unsigned long[hcount];
  imCalcGrayHistogram(src_image, histo, 1);

  if (src_image->data_type == IM_USHORT)
    DoEqualizeHistogram((imushort*)src_image->data[0], (imushort*)dst_image->data[0], src_image->count, src_image->depth, hcount, histo);
  else
    DoEqualizeHistogram((imbyte*)src_image->data[0], (imbyte*)dst_image->data[0], src_image->count, src_image->depth, hcount, histo);

  delete [] histo;
}
