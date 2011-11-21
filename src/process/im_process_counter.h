/** \file
 * \brief Processing Counter
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_PROCESSING_COUNTER_H
#define __IM_PROCESSING_COUNTER_H

#include <im_counter.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#if	defined(__cplusplus)
extern "C" {
#endif

#define IM_INT_PROCESSING     int processing = 1;

#ifdef _OPENMP

#define IM_BEGIN_PROCESSING   if (processing) {
#define IM_COUNT_PROCESSING   if (!imProcessCounterInc(counter)) { processing = 0;
#define IM_END_PROCESSING     }}
#define IM_MAX_THREADS        omp_get_max_threads()
#define IM_THREAD_NUM         omp_get_thread_num()

int  imCounterBegin_OMP(const char* title);
void imCounterEnd_OMP(int counter);
int  imCounterInc_OMP(int counter);

#define imProcessCounterBegin imCounterBegin_OMP
#define imProcessCounterEnd   imCounterEnd_OMP
#define imProcessCounterInc   imCounterInc_OMP

#else

#define IM_BEGIN_PROCESSING   
#define IM_COUNT_PROCESSING   if (!imProcessCounterInc(counter)) { processing = 0; break; }
#define IM_END_PROCESSING

#define IM_MAX_THREADS 1
#define IM_THREAD_NUM  0

#define imProcessCounterBegin imCounterBegin
#define imProcessCounterEnd   imCounterEnd
#define imProcessCounterInc   imCounterInc

#endif


#if defined(__cplusplus)
}
#endif

#endif
