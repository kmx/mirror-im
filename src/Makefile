ifeq ($(OS), Windows_NT)
  TECMAKE_CMD = $(MAKE) --no-print-directory -f ../tecmakewin.mak TEC_UNAME=$(TEC_UNAME)
  WINLIBS = im_avi im_wmv imlua_avi imlua_wmv im_capture imlua_capture5
else
  TECMAKE_CMD = $(MAKE) --no-print-directory -f ../tecmake.mak
endif

.PHONY: do_all im_zlib im im_jp2 im_process im_fftw imlua3 imlua5 imlua_jp2 imlua_process5 imlua_fftw5 $(WINLIBS)
#do_all: im im_jp2 im_process im_fftw imlua3 imlua5 imlua_jp2 imlua_process5 imlua_fftw5
do_all: im_zlib im im_jp2 im_process im_process_omp im_fftw imlua5 imlua_jp2 imlua_process5 imlua_process_omp5 imlua_fftw5 $(WINLIBS)

im_zlib:
	@$(TECMAKE_CMD) MF=im_zlib
im:
	@$(TECMAKE_CMD)
im_jp2:
	@$(TECMAKE_CMD) MF=im_jp2
im_avi:
	@$(TECMAKE_CMD) MF=im_avi
im_process:
	@$(TECMAKE_CMD) MF=im_process
im_process_omp:
	@$(TECMAKE_CMD) MF=im_process USE_OPENMP=Yes
im_fftw:
	@$(TECMAKE_CMD) MF=im_fftw

imlua5:
	@$(TECMAKE_CMD) MF=imlua5 USE_LUA51=Yes
	@$(TECMAKE_CMD) MF=imlua5 USE_LUA52=Yes
imlua_jp2:
	@$(TECMAKE_CMD) MF=imlua_jp2 USE_LUA51=Yes
	@$(TECMAKE_CMD) MF=imlua_jp2 USE_LUA52=Yes
imlua_avi:
	@$(TECMAKE_CMD) MF=imlua_avi USE_LUA51=Yes
	@$(TECMAKE_CMD) MF=imlua_avi USE_LUA52=Yes
imlua_process5:
	@$(TECMAKE_CMD) MF=imlua_process5 USE_LUA51=Yes
	@$(TECMAKE_CMD) MF=imlua_process5 USE_LUA52=Yes
imlua_process_omp5:
	@$(TECMAKE_CMD) MF=imlua_process5 USE_OPENMP=Yes USE_LUA51=Yes
	@$(TECMAKE_CMD) MF=imlua_process5 USE_OPENMP=Yes USE_LUA52=Yes
imlua_fftw5:
	@$(TECMAKE_CMD) MF=imlua_fftw5 USE_LUA51=Yes
	@$(TECMAKE_CMD) MF=imlua_fftw5 USE_LUA52=Yes
  
# WMV and Capture are NOT available in some compilers,
# so this may result in errors, just ignore them.
im_wmv:
	@$(TECMAKE_CMD) MF=im_wmv
imlua_wmv:
	@$(TECMAKE_CMD) MF=imlua_wmv USE_LUA51=Yes 
	@$(TECMAKE_CMD) MF=imlua_wmv USE_LUA52=Yes 
im_capture:
	@$(TECMAKE_CMD) MF=im_capture
imlua_capture5:
	@$(TECMAKE_CMD) MF=imlua_capture5 USE_LUA51=Yes 
	@$(TECMAKE_CMD) MF=imlua_capture5 USE_LUA52=Yes 

imlua3:
	@$(TECMAKE_CMD) MF=imlua3
