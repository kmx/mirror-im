PROJNAME = im
LIBNAME = imlua_jp2
DEF_FILE = imlua_jp2.def

OPT = YES

SRCDIR = lua5

SRC = imlua_jp2.c

LIBS = im_jp2

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

ifneq ($(findstring MacOS, $(TEC_UNAME)), )
  USE_IMLUA:=
  INCLUDES += ../include
  LDIR = ../lib/$(TEC_UNAME)
endif
