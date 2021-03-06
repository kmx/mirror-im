PROJNAME = im
LIBNAME = imlua3
OPT = YES

SRC = im_lua3.c

USE_LUA = Yes
#Do NOT use USE_CD because we use no CD functions, only headers are used.
INCLUDES = $(CD)/include

USE_IM = Yes
IM = ..

ifneq ($(findstring MacOS, $(TEC_UNAME)), )
  ifneq ($(TEC_SYSMINOR), 4)
    BUILD_DYLIB=Yes
  endif
endif
