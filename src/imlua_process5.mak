PROJNAME = im
LIBNAME = imlua_process

OPT = YES
SRC = lua5/imlua_process.c lua5/imlua_kernel.c lua5/imlua_convert.c
DEF_FILE = lua5/imlua_process.def
DEFINES += IM_PROCESS

SRCLUA = lua5/im_process.lua lua5/im_processconvert.lua
SRCLUADIR = lua5
NO_LUAOBJECT = Yes

ifdef NO_LUAOBJECT
  DEFINES += IMLUA_USELH
  USE_LH_SUBDIR = Yes
else
  DEFINES += IMLUA_USELOH
  USE_LOH_SUBDIR = Yes
endif

LIBS = im_process
INCLUDES = lua5

ifdef USE_OPENMP
  LIBNAME := $(LIBNAME)_omp
  LIBS := im_process_omp
endif

ifdef USE_LUA52
  LIBNAME := $(LIBNAME)52
  ifdef NO_LUAOBJECT
    LHDIR = lua5/lh
  else
    LOHDIR = lua5/loh52
  endif
else
  USE_LUA51 = Yes
  LIBNAME := $(LIBNAME)51
  ifdef NO_LUAOBJECT
    LHDIR = lua5/lh
  else
    LOHDIR = lua5/loh51
  endif
endif

USE_IMLUA = YES
NO_LUALINK = Yes
USE_BIN2C_LUA=Yes
IM = ..

ifneq ($(findstring MacOS, $(TEC_UNAME)), )
  USE_IMLUA:=
  INCLUDES += ../include
  LDIR = ../lib/$(TEC_UNAME)
endif
