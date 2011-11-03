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
static void DoNDVI(T *nir_map, T *vis_map, float *new_map, int count)
{
  int i;
  for (i = 0; i < count; i++)
  {
    float num   = (float)(nir_map[i] - vis_map[i]);
    float denom = (float)(nir_map[i] + vis_map[i]);

    if (denom == 0) 
      new_map[i] = 0;
    else
      new_map[i] = num / denom;
  }
}

void imProcessNDVI(const imImage* nir_image, const imImage* vis_image, imImage* dst_image)
{
  int count = nir_image->count;

  switch(nir_image->data_type)
  {
  case IM_BYTE:
    DoNDVI((imbyte*)nir_image->data[0], (imbyte*)vis_image->data[0], (float*)dst_image->data[0], count);
    break;                                                                                
  case IM_USHORT:                                                                           
    DoNDVI((imushort*)nir_image->data[0], (imushort*)vis_image->data[0], (float*)dst_image->data[0], count);
    break;                                                                                
  case IM_INT:                                                                           
    DoNDVI((int*)nir_image->data[0], (int*)vis_image->data[0], (float*)dst_image->data[0], count);
    break;                                                                                
  case IM_FLOAT:                                                                           
    DoNDVI((float*)nir_image->data[0], (float*)vis_image->data[0], (float*)dst_image->data[0], count);
    break;                                                                                
  }
}
