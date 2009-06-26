PROJNAME = im
LIBNAME = imlua51
DEF_FILE = imlua.def

OPT = YES

SRCDIR = lua5

SRC = imlua.c imlua_aux.c imlua_convert.c imlua_file.c imlua_image.c imlua_palette.c imlua_util.c

INCLUDES = lua5

USE_IM = YES
USE_LUA51 = YES
NO_LUALINK = Yes
IM = ..
