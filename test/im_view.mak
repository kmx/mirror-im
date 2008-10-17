APPNAME = im_view

LINKER = g++

SRC = im_view.c

USE_CD = Yes
USE_IUPCONTROLS = Yes
USE_IUP = Yes
USE_IM = Yes

IM = ..
IMINC := $(IM)/include
IMLIB := $(IM)/lib/$(TEC_UNAME)

USE_STATIC = Yes
