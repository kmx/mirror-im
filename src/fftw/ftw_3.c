/*
 * Copyright (c) 1997-1999, 2003 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Mon Mar 24 02:07:31 EST 2003 */

#include "fftw-int.h"
#include "fftw.h"

/* Generated by: /homee/stevenj/cvs/fftw/gensrc/genfft -magic-alignment-check -magic-twiddle-load-all -magic-variables 4 -magic-loopi -twiddle 3 */

/*
 * This function contains 16 FP additions, 12 FP multiplications,
 * (or, 10 additions, 6 multiplications, 6 fused multiply/add),
 * 14 stack variables, and 12 memory accesses
 */
static const fftw_real K866025403 =
FFTW_KONST(+0.866025403784438646763723170752936183471402627);
static const fftw_real K500000000 =
FFTW_KONST(+0.500000000000000000000000000000000000000000000);

/*
 * Generator Id's : 
 * $Id$
 * $Id$
 * $Id$
 */

void fftw_twiddle_3(fftw_complex *A, const fftw_complex *W, int iostride,
		    int m, int dist)
{
     int i;
     fftw_complex *inout;
     inout = A;
     for (i = m; i > 0; i = i - 1, inout = inout + dist, W = W + 2) {
	  fftw_real tmp1;
	  fftw_real tmp18;
	  fftw_real tmp6;
	  fftw_real tmp14;
	  fftw_real tmp11;
	  fftw_real tmp15;
	  fftw_real tmp12;
	  fftw_real tmp17;
	  ASSERT_ALIGNED_DOUBLE;
	  tmp1 = c_re(inout[0]);
	  tmp18 = c_im(inout[0]);
	  {
	       fftw_real tmp3;
	       fftw_real tmp5;
	       fftw_real tmp2;
	       fftw_real tmp4;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp3 = c_re(inout[iostride]);
	       tmp5 = c_im(inout[iostride]);
	       tmp2 = c_re(W[0]);
	       tmp4 = c_im(W[0]);
	       tmp6 = (tmp2 * tmp3) - (tmp4 * tmp5);
	       tmp14 = (tmp4 * tmp3) + (tmp2 * tmp5);
	  }
	  {
	       fftw_real tmp8;
	       fftw_real tmp10;
	       fftw_real tmp7;
	       fftw_real tmp9;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp8 = c_re(inout[2 * iostride]);
	       tmp10 = c_im(inout[2 * iostride]);
	       tmp7 = c_re(W[1]);
	       tmp9 = c_im(W[1]);
	       tmp11 = (tmp7 * tmp8) - (tmp9 * tmp10);
	       tmp15 = (tmp9 * tmp8) + (tmp7 * tmp10);
	  }
	  tmp12 = tmp6 + tmp11;
	  tmp17 = tmp14 + tmp15;
	  {
	       fftw_real tmp13;
	       fftw_real tmp16;
	       fftw_real tmp19;
	       fftw_real tmp20;
	       ASSERT_ALIGNED_DOUBLE;
	       c_re(inout[0]) = tmp1 + tmp12;
	       tmp13 = tmp1 - (K500000000 * tmp12);
	       tmp16 = K866025403 * (tmp14 - tmp15);
	       c_re(inout[2 * iostride]) = tmp13 - tmp16;
	       c_re(inout[iostride]) = tmp13 + tmp16;
	       c_im(inout[0]) = tmp17 + tmp18;
	       tmp19 = K866025403 * (tmp11 - tmp6);
	       tmp20 = tmp18 - (K500000000 * tmp17);
	       c_im(inout[iostride]) = tmp19 + tmp20;
	       c_im(inout[2 * iostride]) = tmp20 - tmp19;
	  }
     }
}

static const int twiddle_order[] = { 1, 2 };
fftw_codelet_desc fftw_twiddle_3_desc = {
     "fftw_twiddle_3",
     (void (*)()) fftw_twiddle_3,
     3,
     FFTW_FORWARD,
     FFTW_TWIDDLE,
     66,
     2,
     twiddle_order,
};
