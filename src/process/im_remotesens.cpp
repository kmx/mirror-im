/** \file
 * \brief Remote Sensing Operations
 *
 * See Copyright Notice in im_lib.h
 */


#include <im.h>
#include <im_util.h>
#include <im_math.h>

#include "im_process_pnt.h"

#include <stdlib.h>
#include <memory.h>


template <class T> 
static void DoNormDiffRatio(T *map1, T *map2, float *new_map, int count)
{
  int i;
  for (i = 0; i < count; i++)
  {
    float num   = (float)(map1[i] - map2[i]);
    float denom = (float)(map1[i] + map2[i]);

    if (denom == 0) 
      new_map[i] = 0;
    else
      new_map[i] = num / denom;
  }
}

void imProcessNormDiffRatio(const imImage* image1, const imImage* image2, imImage* dst_image)
{
  int count = image1->count;

  switch(image1->data_type)
  {
  case IM_BYTE:
    DoNormDiffRatio((imbyte*)image1->data[0], (imbyte*)image2->data[0], (float*)dst_image->data[0], count);
    break;                                                                                
  case IM_USHORT:                                                                           
    DoNormDiffRatio((imushort*)image1->data[0], (imushort*)image2->data[0], (float*)dst_image->data[0], count);
    break;                                                                                
  case IM_INT:                                                                           
    DoNormDiffRatio((int*)image1->data[0], (int*)image2->data[0], (float*)dst_image->data[0], count);
    break;                                                                                
  case IM_FLOAT:                                                                           
    DoNormDiffRatio((float*)image1->data[0], (float*)image2->data[0], (float*)dst_image->data[0], count);
    break;                                                                                
  }
}
