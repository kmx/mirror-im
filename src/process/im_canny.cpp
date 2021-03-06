/** \file
 * \brief Canny Edge Detector
 *
 * See Copyright Notice in im_lib.h
 */

#include <im.h>
#include <im_util.h>

#include "im_process_counter.h"
#include "im_process_loc.h"

#include <math.h>
#include <stdlib.h>
#include <memory.h>

/* Scale floating point magnitudes to 8 bits */
static float MAG_SCALE;

/* Biggest possible filter mask */
#define MAX_MASK_SIZE 100

static float ** f2d (int nr, int nc);
static float gauss(float x, float sigma);
static float dGauss (float x, float sigma);
static float meanGauss (float x, float sigma);
static void seperable_convolution (const imImage* im, float *gau, int width, float **smx, float **smy);
static void dxy_seperable_convolution (float** im, int nr, int nc, float *gau, int width, float **sm, int which);
static void nonmax_suppress (float **dx, float **dy, imImage* mag);

void imProcessCanny(const imImage* src_image, imImage* dst_image, float stddev)
{
  int width = 1;
  float **smx,**smy;
  float **dx,**dy;
  int i;
  float gau[MAX_MASK_SIZE], dgau[MAX_MASK_SIZE];

/* Create a Gaussian and a derivative of Gaussian filter mask */
  for(i=0; i<MAX_MASK_SIZE; i++)
  {
    gau[i] = meanGauss ((float)i, stddev);
    if (gau[i] < 0.005)
    {
      width = i;
      break;
    }
    dgau[i] = dGauss ((float)i, stddev);
  }

  smx = f2d (src_image->height, src_image->width);
  smy = f2d (src_image->height, src_image->width);

/* Convolution of source src_image with a Gaussian in X and Y directions  */
  seperable_convolution (src_image, gau, width, smx, smy);

  MAG_SCALE = 0;

/* Now convolve smoothed data with a derivative */
  dx = f2d (src_image->height, src_image->width);
  dxy_seperable_convolution (smx, src_image->height, src_image->width, dgau, width, dx, 1);
  free(smx[0]); free(smx);

  dy = f2d (src_image->height, src_image->width);
  dxy_seperable_convolution (smy, src_image->height, src_image->width, dgau, width, dy, 0);
  free(smy[0]); free(smy);

  if (MAG_SCALE)
    MAG_SCALE = 255.0f/(1.4142f*MAG_SCALE);

  /* Non-maximum suppression - edge pixels should be a local max */
  nonmax_suppress (dx, dy, dst_image);

  free(dx[0]); free(dx);
  free(dy[0]); free(dy);
}

static float norm (float x, float y)
{
  return (float) sqrt ( (double)(x*x + y*y) );
}

static float ** f2d (int nr, int nc)
{
  float **x, *y;
  int i;

  x = (float **)calloc ( nr, sizeof (float *) );
  if (!x)
    return NULL;

  y = (float *)calloc ( nr*nc, sizeof (float) );
  if (!y)
  {
    free(x);
    return NULL;
  }

  for (i=0; i<nr; i++)
  {  
    x[i] = y + i*nc;
  }

  return x;
}

/*      Gaussian        */
static float gauss(float x, float sigma)
{
  return (float)exp((double) ((-x*x)/(2*sigma*sigma)));
}

static float meanGauss (float x, float sigma)
{
  float z;
  z = (gauss(x,sigma)+gauss(x+0.5f,sigma)+gauss(x-0.5f,sigma))/3.0f;
//  z = z/(3.1415f*2.0f*sigma*sigma);
  return z;
}

/*      First derivative of Gaussian    */
static float dGauss (float x, float sigma)
{
//  return -x/(sigma*sigma) * gauss(x, sigma);
  return -x * gauss(x, sigma);
}

static void seperable_convolution (const imImage* im, float *gau, int width, float **smx, float **smy)
{
  unsigned char* im_data = (unsigned char*)im->data[0];
  int nr = im->height;
  int nc = im->width;

#ifdef _OPENMP
#pragma omp parallel for if (IM_OMP_MINHEIGHT(nr))
#endif
  for (int i=0; i<nr; i++)
  {
    for (int j=0; j<nc; j++)
    {
      float x = gau[0] * im_data[i*im->width + j]; 
      float y = gau[0] * im_data[i*im->width + j];

      for (int k=1; k<width; k++)
      {
        int I1 = (i+k)%nr; 
        int I2 = (i-k+nr)%nr;
        y += gau[k]*im_data[I1*im->width + j] + gau[k]*im_data[I2*im->width + j];

        I1 = (j+k)%nc; 
        I2 = (j-k+nc)%nc;
        x += gau[k]*im_data[i*im->width + I1] + gau[k]*im_data[i*im->width + I2];
      }

      smx[i][j] = x; 
      smy[i][j] = y;
    }
  }
}

static void dxy_seperable_convolution (float** im, int nr, int nc,  float *gau, int width, float **sm, int which)
{
#ifdef _OPENMP
#pragma omp parallel for if (IM_OMP_MINHEIGHT(nr))
#endif
  for (int i=0; i<nr; i++)
  {
    for (int j=0; j<nc; j++)
    {
      float x = 0.0;
      for (int k=1; k<width; k++)
      {
        if (which == 0)
        {
          int I1 = (i+k)%nr; 
          int I2 = (i-k+nr)%nr;
          x += -gau[k]*im[I1][j] + gau[k]*im[I2][j];
        }
        else
        {
          int I1 = (j+k)%nc; 
          int I2 = (j-k+nc)%nc;
          x += -gau[k]*im[i][I1] + gau[k]*im[i][I2];
        }
      }
      sm[i][j] = x;

      if (x > MAG_SCALE)
        MAG_SCALE = x;
    }
  }
}

static unsigned char tobyte(float x)
{
  if (x > 255) return 255;
  return (unsigned char)x;
}

static void nonmax_suppress (float **dx, float **dy, imImage* mag)
{
  unsigned char* mag_data = (unsigned char*)mag->data[0];

#ifdef _OPENMP
#pragma omp parallel for if (IM_OMP_MINHEIGHT(mag->height))
#endif
  for (int i=1; i<mag->height-1; i++)
  {
    for (int j=1; j<mag->width-1; j++)
    {
      float xx, yy, g2, g1, g3, g4, g, xc, yc;

      /* Treat the x and y derivatives as components of a vector */
      xc = dx[i][j];
      yc = dy[i][j];
      if (fabs(xc)<0.01 && fabs(yc)<0.01) continue;

      g  = norm (xc, yc);

      /* Follow the gradient direction, as indicated by the direction of
        the vector (xc, yc); retain pixels that are a local maximum. */

      if (fabs(yc) > fabs(xc))
      {
        /* The Y component is biggest, so gradient direction is basically UP/DOWN */
        xx = (float)(fabs(xc)/fabs(yc));
        yy = 1.0;

        g2 = norm (dx[i-1][j], dy[i-1][j]);
        g4 = norm (dx[i+1][j], dy[i+1][j]);
        if (xc*yc > 0.0)
        {
          g3 = norm (dx[i+1][j+1], dy[i+1][j+1]);
          g1 = norm (dx[i-1][j-1], dy[i-1][j-1]);
        } 
        else
        {
          g3 = norm (dx[i+1][j-1], dy[i+1][j-1]);
          g1 = norm (dx[i-1][j+1], dy[i-1][j+1]);
        }

      } 
      else
      {
        /* The X component is biggest, so gradient direction is basically LEFT/RIGHT */
        xx = (float)(fabs(yc)/fabs(xc));
        yy = 1.0;

        g2 = norm (dx[i][j+1], dy[i][j+1]);
        g4 = norm (dx[i][j-1], dy[i][j-1]);
        if (xc*yc > 0.0)
        {
          g3 = norm (dx[i-1][j-1], dy[i-1][j-1]);
          g1 = norm (dx[i+1][j+1], dy[i+1][j+1]);
        }
        else
        {
          g1 = norm (dx[i-1][j+1], dy[i-1][j+1]);
          g3 = norm (dx[i+1][j-1], dy[i+1][j-1]);
        }
      }

      /* Compute the interpolated value of the gradient magnitude */
      if ( (g > (xx*g1 + (yy-xx)*g2)) && (g > (xx*g3 + (yy-xx)*g4)) )
      {
        mag_data[i*mag->width + j] = tobyte(g*MAG_SCALE);
      } 
    }
  }
}
