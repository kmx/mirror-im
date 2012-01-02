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
  DEFINES += LUA_COMPAT_MODULE
else
  USE_LUA51 = Yes
  LUASFX = 51
endif

LIBNAME := $(LIBNAME)$(LUASFX)

USE_IMLUA = Yes
IM = ..

ifneq ($(findstring gcc, $(TEC_UNAME)), )
  $(error No support for WMFSDK in Cygwin)
endif
ifneq ($(findstring mingw, $(TEC_UNAME)), )
  $(error No support for WMFSDK in MingW)
endif
ifneq ($(findstring cygw, $(TEC_UNAME)), )
  $(error No support for WMFSDK in Cygwin)
endif
ifneq ($(findstring dllw, $(TEC_UNAME)), )
  $(error No support for WMFSDK in MingW)
endif
ifneq ($(findstring dllg, $(TEC_UNAME)), )
  $(error No support for WMFSDK in Cygwin)
endif
ifneq ($(findstring owc, $(TEC_UNAME)), )
  $(error No support for WMFSDK in OpenWatcom)
endif
ifneq ($(findstring bc, $(TEC_UNAME)), )
  $(error No support for WMFSDK in BorlandC)
endif
