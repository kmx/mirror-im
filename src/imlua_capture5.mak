PROJNAME = im
LIBNAME = imlua_capture
DEF_FILE = imlua_capture.def

OPT = YES

SRCDIR = lua5

SRC = imlua_capture.c

LIBS = im_capture

INCLUDES = lua5

ifdef USE_LUA52
  LUASFX = 52
  DEFINES += LUA_COMPAT_MODULE
else
  USE_LUA51 = Yes
  LUASFX = 51
endif

LIBNAME := $(LIBNAME)$(LUASFX)

USE_IMLUA = Yes
NO_LUALINK = Yes
IM = ..
