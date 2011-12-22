PROJNAME = im
LIBNAME = libpng

OPT = YES

INCLUDES = libpng
                     
SRC = \
    png.c       pngget.c    pngread.c   pngrutil.c     pngwtran.c  \
    pngerror.c  pngmem.c    pngrio.c    pngset.c    pngwio.c    pngwutil.c  \
    pngpread.c  pngrtran.c  pngtrans.c  pngwrite.c
SRC  := $(addprefix libpng/, $(SRC))

ifneq ($(findstring dll, $(TEC_UNAME)), )
  SRC += libpng/pngwin.rc
  DEF_FILE = libpng/symbols.def
endif

ifneq ($(findstring Win, $(TEC_SYSNAME)), )
  # To be compatible with the existing DLLs
  LIBNAME = libpng15
endif

ifneq ($(findstring gcc, $(TEC_UNAME)), )
  LIBNAME = z
endif

ifneq ($(findstring cygw, $(TEC_UNAME)), )
  LIBNAME = z
endif

ifneq ($(findstring MacOS, $(TEC_UNAME)), )
  ifneq ($(TEC_SYSMINOR), 4)
    BUILD_DYLIB=Yes
  endif
endif
