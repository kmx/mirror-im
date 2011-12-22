PROJNAME = im
PNGSFX = 15
LIBNAME = png$(PNGSFX)

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
  # To be compatible with the existing DLLs of gnuwin32
  LIBNAME = libpng$(PNGSFX)
endif

ifneq ($(findstring gcc, $(TEC_UNAME)), )
  # To be compatible with the existing static libs of gnuwin32 and cygwin
  LIBNAME = png$(PNGSFX)
endif
ifneq ($(findstring mingw, $(TEC_UNAME)), )
  LIBNAME = png$(PNGSFX)
endif

ifneq ($(findstring cygw, $(TEC_UNAME)), )
  # To be compatible with the existing DLLs of cygwin
  LIBNAME = png$(PNGSFX)
endif

ifneq ($(findstring MacOS, $(TEC_UNAME)), )
  ifneq ($(TEC_SYSMINOR), 4)
    BUILD_DYLIB=Yes
  endif
endif
