/** \file
 * \brief Image Statistics Calculations
 *
 * See Copyright Notice in im_lib.h
 */


#include <im.h>
#include <im_util.h>
#include <im_color.h>
#include <im_math_op.h>

#include "im_process_ana.h"

#include <stdlib.h>
#include <memory.h>
#include <math.h>

#include <stdio.h>

template <class T>
static void DoCalcHisto(T* map, int size, unsigned long* histo, int hcount, int cumulative)
{
  int i;

  memset(histo, 0, hcount * sizeof(unsigned long));

  for (i = 0; i < size; i++)
    histo[*map++]++;

  if (cumulative)
  {
    /* make cumulative histogram */
    for (i = 1; i < hcount; i++)
      histo[i] += histo[i-1];
  }
}

void imCalcHistogram(const imbyte* map, int size, unsigned long* histo, int cumulative)
{
  DoCalcHisto(map, size, histo, 256, cumulative);
}

void imCalcUShortHistogram(const imushort* map, int size, unsigned long* histo, int cumulative)
{
  DoCalcHisto(map, size, histo, 65536, cumulative);
}

void imCalcGrayHistogram(const imImage* image, unsigned long* histo, int cumulative)
{
  int hcount = 256;
  if (image->data_type == IM_USHORT)
    hcount = 65536;

  if (image->color_space == IM_GRAY)
  {
    if (image->data_type == IM_USHORT)
      DoCalcHisto((imushort*)image->data[0], image->count, histo, hcount, 0);
    else
      DoCalcHisto((imbyte*)image->data[0], image->count, histo, hcount, 0);
  }
  else 
  {
    int i;
    memset(histo, 0, hcount * sizeof(unsigned long));

    if (image->color_space == IM_MAP || image->color_space == IM_BINARY)
    {
      imbyte* map = (imbyte*)image->data[0];
      imbyte gray_map[256], r, g, b;

      for (i = 0; i < image->palette_count; i++)
      {
        imColorDecode(&r, &g, &b, image->palette[i]);
        gray_map[i] = imColorRGB2Luma(r, g, b);
      }

      for (i = 0; i < image->count; i++)
      {
        int index = *map++;
        histo[gray_map[index]]++;
      }
    }
    else
    {
      if (image->data_type == IM_USHORT)
      {
        imushort gray;
        imushort* r = (imushort*)image->data[0];
        imushort* g = (imushort*)image->data[1];
        imushort* b = (imushort*)image->data[2];
        for (i = 0; i < image->count; i++)
        {
          gray = imColorRGB2Luma(*r++, *g++, *b++);
          histo[gray]++;
        }
      }
      else
      {
        imbyte gray;
        imbyte* r = (imbyte*)image->data[0];
        imbyte* g = (imbyte*)image->data[1];
        imbyte* b = (imbyte*)image->data[2];
        for (i = 0; i < image->count; i++)
        {
          gray = imColorRGB2Luma(*r++, *g++, *b++);
          histo[gray]++;
        }
      }
    }

    if (cumulative)
    {
      /* make cumulative histogram */
      for (i = 1; i < hcount; i++)
        histo[i] += histo[i-1];
    }
  }
}

static unsigned long count_map(const imImage* image)
{
  int hcount = 256;
  if (image->data_type == IM_USHORT)
    hcount = 65536;

  unsigned long *histo = new unsigned long[hcount];

  if (image->data_type == IM_USHORT)
    DoCalcHisto((imushort*)image->data[0], image->count, histo, hcount, 0);
  else
    DoCalcHisto((imbyte*)image->data[0], image->count, histo, hcount, 0);

  unsigned long numcolor = 0;

  for (int i = 0; i < hcount; i++)
  {             
    if(histo[i] != 0)
      numcolor++;
  }

  delete [] histo;

  return numcolor;
}

// will count also all the 3 components color spaces
static unsigned long count_rgb(const imImage* image)
{
  imbyte *count = (imbyte*)calloc(sizeof(imbyte), 1 << 21); /* (2^24)/8=2^21 ~ 2Mb - using a bit array */
  if (!count)
    return (unsigned long)-1;

  imbyte *red = (imbyte*)image->data[0];
  imbyte *green = (imbyte*)image->data[1];
  imbyte *blue = (imbyte*)image->data[2];

  int index;
  unsigned long numcolor = 0;

  for(int i = 0; i < image->count; i++)
  {
    index = red[i] << 16 | green[i] << 8 | blue[i];

    if(imDataBitGet(count, index) == 0)
      numcolor++;

    imDataBitSet(count, index, 1);
  }

  free(count);

  return numcolor;
}

unsigned long imCalcCountColors(const imImage* image)
{
  if (imColorModeDepth(image->color_space) > 1)
    return count_rgb(image);
  else
    return count_map(image);
}

template <class T>
static void DoStats(T* data, int count, imStats* stats)
{
  double mean = 0, stddev = 0, dcount = (double)count;
  memset(stats, 0, sizeof(imStats));

  stats->min = (float)data[0];
  stats->max = (float)data[0];

  for (int i = 0; i < count; i++)
  {
		if (data[i] < stats->min)
		  stats->min = (float)data[i];

		if (data[i] > stats->max)
		  stats->max = (float)data[i];

    if (data[i] > 0)
      stats->positive++;

    if (data[i] < 0)
      stats->negative++;

    if (data[i] == 0)
      stats->zeros++;

    mean += (double)data[i];
    stddev += ((double)data[i])*((double)data[i]);
  }

  mean /= dcount;
  stddev = sqrt((stddev - dcount*mean*mean)/(dcount-1.0));

  stats->mean = (float)mean;
  stats->stddev = (float)stddev;
}

void imCalcImageStatistics(const imImage* image, imStats* stats)
{
  for (int i = 0; i < image->depth; i++)
  {
    switch(image->data_type)
    {
    case IM_BYTE:
      DoStats((imbyte*)image->data[i], image->count, &stats[i]);
      break;                                                                                
    case IM_USHORT:                                                                           
      DoStats((imushort*)image->data[i], image->count, &stats[i]);
      break;                                                                                
    case IM_INT:                                                                           
      DoStats((int*)image->data[i], image->count, &stats[i]);
      break;                                                                                
    case IM_FLOAT:                                                                           
      DoStats((float*)image->data[i], image->count, &stats[i]);
      break;                                                                                
    }
  }
}

void imCalcHistogramStatistics(const imImage* image, imStats* stats)
{
  int hcount = 256;
  if (image->data_type == IM_USHORT)
    hcount = 65536;

  unsigned long *histo = new unsigned long[hcount];

  for (int d = 0; d < image->depth; d++)
  {
    if (image->data_type == IM_USHORT)
      DoCalcHisto((imushort*)image->data[d], image->count, histo, hcount, 0);
    else
      DoCalcHisto((imbyte*)image->data[d], image->count, histo, hcount, 0);
    DoStats((unsigned long*)histo, hcount, &stats[d]);
  }

  delete [] histo;
}

void imCalcHistoImageStatistics(const imImage* image, int* median, int* mode)
{
  int hcount = 256;
  if (image->data_type == IM_USHORT)
    hcount = 65536;

  unsigned long *histo = new unsigned long[hcount];

  for (int d = 0; d < image->depth; d++)
  {
    int i;
    imCalcHistogram((imbyte*)image->data[d], image->count, histo, 0);

    unsigned long half = image->count/2;
    unsigned long count = histo[0];
    for (i = 1; i < hcount; i++)
    {
      if (count > half)
      {
        median[d] = i-1;
        break;
      }

      count += histo[i];
    }

    unsigned long max = histo[0];
    for (i = 1; i < hcount; i++)
    {
      if (max < histo[i])
        max = histo[i];
    }

    int found_mode = 0;
    for (i = 0; i < hcount; i++)
    {
      if (histo[i] == max)
      {
        if (found_mode)
        {
          mode[d] = -1;
          break;
        }

        mode[d] = i;
        found_mode = 1;
      }
    }
  }

  delete [] histo;
}

void imCalcPercentMinMax(const imImage* image, float percent, int ignore_zero, int *min, int *max)
{
  int hcount = 256;
  if (image->data_type == IM_USHORT)
    hcount = 65536;

  unsigned long* histo = new unsigned long[hcount];
  imCalcGrayHistogram(image, histo, 0);

  unsigned long acum, cut = (unsigned long)((image->count * percent) / 100.0f);

  acum = 0;
  for ((*min = ignore_zero? 1: 0); *min < hcount; (*min)++)
  {  
    acum += histo[*min];
    if (acum > cut)
      break;
  }

  acum = 0;
  for (*max = hcount-1; *max > 0; (*max)--)
  {  
    acum += histo[*max];
    if (acum > cut)
      break;
  }

  if (*min >= *max)
  {
    *min = 0;
    *max = hcount-1;
  }

  delete [] histo;
}

float imCalcSNR(const imImage* image, const imImage* noise_image)
{
  imStats stats[3];
  imCalcImageStatistics((imImage*)image, stats);

  imStats noise_stats[3];
  imCalcImageStatistics((imImage*)noise_image, noise_stats);

  if (image->color_space == IM_RGB)
  {
    noise_stats[0].stddev += noise_stats[1].stddev;
    noise_stats[0].stddev += noise_stats[2].stddev;
    noise_stats[0].stddev /= 3;
    stats[0].stddev += stats[1].stddev;
    stats[0].stddev += stats[2].stddev;
    stats[0].stddev /= 3;
  }

  if (noise_stats[0].stddev == 0)
    return 0;

  return float(20.*log10(stats[0].stddev / noise_stats[0].stddev));
}

template <class T> 
static double DoRMSOp(T *map1, T *map2, int count)
{
  double rmserror = 0;
  double diff;

  for (int i = 0; i < count; i++)
  {
    diff = double(map1[i] - map2[i]);
    rmserror += diff * diff;
  }

  return rmserror;
}
  
float imCalcRMSError(const imImage* image1, const imImage* image2)
{
  double rmserror = 0;

  int count = image1->count*image1->depth;

  switch(image1->data_type)
  {
  case IM_BYTE:
    rmserror = DoRMSOp((imbyte*)image1->data[0], (imbyte*)image2->data[0], count);
    break;
  case IM_USHORT:
    rmserror = DoRMSOp((imushort*)image1->data[0], (imushort*)image2->data[0], count);
    break;
  case IM_INT:
    rmserror = DoRMSOp((int*)image1->data[0], (int*)image2->data[0], count);
    break;
  case IM_FLOAT:
    rmserror = DoRMSOp((float*)image1->data[0], (float*)image2->data[0], count);
    break;
  case IM_CFLOAT:
    rmserror = DoRMSOp((float*)image1->data[0], (float*)image2->data[0], 2*count);
    break;
  }

  rmserror = sqrt(rmserror / double((count * image1->depth)));

  return (float)rmserror;
}

