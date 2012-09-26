APPNAME = im_copy
APPTYPE = CONSOLE
#LINKER = g++

SRC = im_copy.cpp

USE_IM = Yes

IM = ..

USE_STATIC = Yes

ifneq ($(findstring Win, $(TEC_SYSNAME)), )
  LIBS = im_wmv im_avi vfw32 wmvcore
endif
