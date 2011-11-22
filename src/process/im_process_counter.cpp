/** \file
 * \brief Processing Counter
 *
 * See Copyright Notice in im_lib.h
 */

#include "im_process_counter.h"

#include <stdlib.h>
#include <memory.h>


#ifdef _OPENMP

int imCounterBegin_OMP(const char* title)
{
  if (!imCounterHasCallback()) 
    return -1;

  int counter = imCounterBegin(title);
  omp_lock_t lck;
  omp_init_lock(&lck);
  imCounterSetUserData(counter, lck);
  return counter;
}

void imCounterEnd_OMP(int counter)
{
  if (counter == -1 || !imCounterHasCallback()) 
    return;

  omp_lock_t lck = imCounterGetUserData(counter);
  omp_destroy_lock(&lck);
  imCounterEnd(counter);
}

int imCounterInc_OMP(int counter)
{
  int processing;

  if (counter == -1 || !imCounterHasCallback()) 
    return 1;

  omp_lock_t lck = imCounterGetUserData(counter);
  omp_set_lock(&lck);
  processing = imCounterInc(counter);
  omp_unset_lock(&lck);
    
  return processing;
}

#endif
