/** \file
 * \brief Library Management
 *
 * See Copyright Notice in im_lib.h
 * $Id$
 */

#include <stdlib.h>
#include <string.h>

#include "im_lib.h"

/* This appears only here to avoid changing the iup.h header fo bug fixes */
#define IM_VERSION_FIX ""
#define IM_VERSION_FIX_NUMBER 0

static char *iVersion = "TECVERID.str:IM:LIB:" IM_VERSION IM_VERSION_FIX;

const char iIdent[] =
  "$IM: " IM_VERSION IM_VERSION_FIX " " IM_COPYRIGHT " $\n"
  "$URL: www.tecgraf.puc-rio.br/im $\n";

const char* imVersion(void)
{                  
	 (void)iVersion;
	 (void)iIdent;
   return IM_VERSION IM_VERSION_FIX;
}

const char* imVersionDate(void)
{
  return IM_VERSION_DATE;
}

int imVersionNumber(void)
{
  return IM_VERSION_NUMBER+IM_VERSION_FIX_NUMBER;
}
