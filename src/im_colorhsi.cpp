/** \file
 * \brief HSI Color Manipulation
 *
 * See Copyright Notice in im_lib.h
 * $Id$
 */


#include <math.h>

#include "im_colorhsi.h"
#include "im_color.h"

static const float rad60 =  1.0471975f;
static const float rad120 = 2.0943951f;
static const float rad180 = 3.1415926f;
static const float rad240 = 4.1887902f;
static const float rad300 = 5.2359877f;
static const float rad360 = 6.2831853f;
static const float sqrt3 = 1.7320508f;

/**********************************/               
/*         HSI MAX S              */
/**********************************/               
               
static void iSmax01(float h, float hr, float hb, float hg, float *h0, float *h1)
{
  if (h < rad60)
  {
    *h0 = hb;
    *h1 = hr;
  }
  else if (h < rad120)
  {
    *h0 = hb;
    *h1 = hg;
  }
  else if (h < rad180)
  {
    *h0 = hr;
    *h1 = hg;
  }
  else if (h < rad240)
  {
    *h0 = hr;
    *h1 = hb;
  }
  else if (h < rad300)
  {
    *h0 = hg;
    *h1 = hb;
  }
  else
  {
    *h0 = hg;
    *h1 = hr;
  }
}

float imColorHSI_Smax(float h, double cosh, double sinh, float i)
{
  float hr, hb, hg, imax, h0, h1;

  if (i == 0 || i == 1)
    return 0.0f;

  if (i == 1.0f/3.0f || i == 2.0f/3.0f)
    return 1.0f;

  hr = (float)(cosh / 1.5);
  hg = (float)((-cosh + sinh*sqrt3)/ 3.0);
  hb = (float)((-cosh - sinh*sqrt3)/ 3.0);

  /* at bottom */
  if (i < 1.0f/3.0f)
  {
    /* face B=0 */
    if (h < rad120)
      return -i/hb;

    /* face R=0 */
    if (h < rad240)
      return -i/hr;

    /* face G=0 */
    return -i/hg;
  }

  /* at top */
  if (i > 2.0f/3.0f)
  {
    /* face R=1 */
    if (h < rad60 || h > rad300)
      return (1-i)/hr;

    /* face G=1 */
    if (h < rad180)
      return (1-i)/hg;

    /* face B=1 */
    return (1-i)/hb;
  }

  /* in the middle */

  iSmax01(h, hr, hb, hg, &h0, &h1);

  if (h == 0 || h == rad120 || h == rad240)
    imax = 1.0f/3.0f;
  else if (h == rad60 || h == rad180 || h == rad300)
    imax = 2.0f/3.0f;
  else
    imax = h0 / (h0 - h1);

  if (i < imax) 
    return -i/h0;
  else
    return (1-i)/h1;
}

float imColorHSI_ImaxS(float h, double cosh, double sinh)
{
  float i, h0, h1;
  float hr, hb, hg;

  if (h == 0 || h == rad120 || h == rad240)
    return 1.0f/3.0f;

  if (h == rad60 || h == rad180 || h == rad300)
    return 2.0f/3.0f;

  hr = (float)(cosh / 1.5f);
  hg = (float)((-cosh + sinh*sqrt3)/ 3.0);
  hb = (float)((-cosh - sinh*sqrt3)/ 3.0);

  iSmax01(h, hr, hb, hg, &h0, &h1);

  i = h0 / (h0 - h1);

  return i;
}

/**********************************/               
/*         RGB 2 HSI              */
/**********************************/               

void imColorRGB2HSI(float r, float g, float b, float *h, float *s, float *i)
{            
  float v, u;
  double H;

  v = r - (g + b)/2;
  u = (g - b) * (sqrt3/2);

  *i = (r + g + b)/3;
  *s = (float)sqrt(v*v + u*u);
  
  if (*s == 0)
    *h = 360.0f;  /* by definition */
  else
  {
    H = atan2(u, v);
    if (H < 0.0f) H += rad360;
    *h = (float)(H * 57.2957795131);
  }
}

void imColorRGB2HSIbyte(unsigned char r, unsigned char g, unsigned char b, float *h, float *s, float *i)
{
  float fr = imColorReconstruct(r, (imbyte)255);
  float fg = imColorReconstruct(g, (imbyte)255);
  float fb = imColorReconstruct(b, (imbyte)255);
  
  imColorRGB2HSI(fr, fg, fb, h, s, i);
}

/**********************************/               
/*         HSI 2 RGB              */
/**********************************/               

void imColorHSI2RGB(float h, float s, float i, float *r, float *g, float *b)
{
  static int first = 1;
  static double _sqrt3;
  double cosh, sinh, H, v, u;

  if (first)
  {
    _sqrt3 = sqrt(3.0);
    first = 0;
  }

  if (s == 0.0f || i == 1.0f || i == 0.0f || (int)h == 360)
  {
    *r = i;
    *g = i;
    *b = i;
    return;
  }

  if (i < 0) i = 0;
  if (i > 1) i = 1;

  if (h > 360)  h = (float)fmod(h, 360);
  if (h < 0.0f) h += 360;

  H = h / 57.2957795131;

  cosh = cos(H);
  sinh = sin(H);
    
  {
    float smax = imColorHSI_Smax((float)H, cosh, sinh, i);
    if (s < 0) s = 0;
    if (s > smax) s = smax;
  }

  v = s * cosh;
  u = s * sinh * _sqrt3;

  *r = (float)(i + v/1.5);
  *g = (float)(i - (v - u)/3.0);
  *b = (float)(i - (v + u)/3.0);

  if (*r < 0) *r = -*r;
  if (*g < 0) *g = -*g;
  if (*b < 0) *b = -*b;

  if (*r > 1) *r = 1.0f;
  if (*g > 1) *g = 1.0f;
  if (*b > 1) *b = 1.0f;
}

void imColorHSI2RGBbyte(float h, float s, float i, unsigned char *r, unsigned char *g, unsigned char *b)
{
  float fr, fg, fb;
  
  imColorHSI2RGB(h, s, i, &fr, &fg, &fb);
  
  *r = imColorQuantize(fr, (imbyte)255);
  *g = imColorQuantize(fg, (imbyte)255);
  *b = imColorQuantize(fb, (imbyte)255);
}
