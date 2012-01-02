PROJNAME = im
LIBNAME = imlua_avi
DEF_FILE = imlua_avi.def

OPT = YES

SRCDIR = lua5

SRC = imlua_avi.c

LIBS = im_avi

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

ifneq ($(findstring cygw, $(TEC_UNAME)), )
  $(error No support for AVI in Cygwin when using Posix mode)
endif
