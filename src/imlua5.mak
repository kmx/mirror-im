PROJNAME = im
LIBNAME = imlua

OPT = YES
SRC = lua5/imlua.c lua5/imlua_aux.c lua5/imlua_convert.c lua5/imlua_file.c \
      lua5/imlua_image.c lua5/imlua_palette.c lua5/imlua_util.c
DEF_FILE = lua5/imlua.def

SRCLUA = lua5/im_image.lua lua5/im_convert.lua
SRCLUADIR = lua5
NO_LUAOBJECT = Yes

ifdef NO_LUAOBJECT
  DEFINES += IMLUA_USELH
  USE_LH_SUBDIR = Yes
else
  DEFINES += IMLUA_USELOH
  USE_LOH_SUBDIR = Yes
endif

INCLUDES = lua5

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

USE_IM = YES
NO_LUALINK = Yes
USE_BIN2C_LUA=Yes
IM = ..
