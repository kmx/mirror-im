/** \file
 * \brief Image Processing
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_PROCESS_H
#define __IM_PROCESS_H

#include "im_process_pnt.h"
#include "im_process_loc.h"
#include "im_process_glo.h"
#include "im_process_ana.h"

#if	defined(__cplusplus)
extern "C" {
#endif


/** \defgroup process Image Processing
 * \par
 * Several image processing functions based on the \ref imImage structure.
 * \par
 * You must link the application with "im_process.lib/.a/.so". 
 * In Lua call require"imlua_process". \n
 * Some complex operations use the \ref counter.\n
 * There is no check on the input/output image properties, 
 * check each function documentation before using it.
 * \par
 * To enable OpenMP support use the "im_process_omp.lib/.a/.so" libraries.
 * In Lua call require"imlua_process_omp". \n
 * Notice that multi-threading can be slower than single thread because of 
 * the overhead introduced by the threads configuration. \n
 * When using the "im_process_omp" library you can reduce that overhead 
 * by controling the minimum number of interaction to enable the use of multiple threads
 * using the \ref imOpenMPSetMinCount function. 
 * Default value is 10000, or an image with 100x100.
 * If set to -1 will set to single thread, but notice 
 * that this is not the same thing as using the library without support for OpenMP. \n
 * For more information on OpenMP: \n
 * http://www.openmp.org 
 */


#if defined(__cplusplus)
}
#endif

#endif
