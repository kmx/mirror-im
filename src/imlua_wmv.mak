PROJNAME = im
LIBNAME = imlua_wmv
DEF_FILE = imlua_wmv.def

OPT = YES

SRCDIR = lua5

SRC = imlua_wmv.c

LIBS = im_wmv

INCLUDES = lua5

ifdef USE_LUA52
  LUASFX = 52
else
  USE_LUA51 = Yes
  LUASFX = 51
endif

LIBNAME := $(LIBNAME)$(LUASFX)

USE_IMLUA = Yes
IM = ..
