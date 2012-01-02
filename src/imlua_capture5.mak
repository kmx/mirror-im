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

ifneq ($(findstring gcc, $(TEC_UNAME)), )
  $(error No support for DirectX in Cygwin)
endif
#ifneq ($(findstring mingw, $(TEC_UNAME)), )
#  $(error No support for DirectX in MingW)
#endif
ifneq ($(findstring cygw, $(TEC_UNAME)), )
  $(error No support for DirectX in Cygwin)
endif
#ifneq ($(findstring dllw, $(TEC_UNAME)), )
#  $(error No support for DirectX in MingW)
#endif
ifneq ($(findstring dllg, $(TEC_UNAME)), )
  $(error No support for DirectX in Cygwin)
endif
ifneq ($(findstring owc, $(TEC_UNAME)), )
  $(error No support for DirectX in OpenWatcom)
endif
ifneq ($(findstring bc, $(TEC_UNAME)), )
  $(error No support for DirectX in BorlandC)
endif
