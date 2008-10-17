/** \file
 * \brief Library Management
 *
 * See Copyright Notice in im_lib.h
 * $Id$
 */

#include <stdlib.h>
#include <string.h>

#include "im_lib.h"

static char *iVersion = "TECVERID.str:IM:LIB:"IM_VERSION;

const char iIdent[] =
  "$IM: " IM_VERSION " " IM_COPYRIGHT " $\n"
  "$URL: www.tecgraf.puc-rio.br/im $\n";

const char* imVersion(void)
{                  
	 (void)iVersion;
	 (void)iIdent;
   return IM_VERSION;
}

const char* imVersionDate(void)
{
  return IM_VERSION_DATE;
}

int imVersionNumber(void)
{
  return IM_VERSION_NUMBER;
}
