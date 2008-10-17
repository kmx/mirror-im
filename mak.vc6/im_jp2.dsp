# Microsoft Developer Studio Project File - Name="im_jp2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=im_jp2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "im_jp2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "im_jp2.mak" CFG="im_jp2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "im_jp2 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "im_jp2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\lib"
# PROP BASE Intermediate_Dir "..\obj\im_jp2"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "..\obj\im_jp2"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /I "../include" /I "../src" /I "../src/libjasper" /Z7 /W4 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "EXCLUDE_JPG_SUPPORT" /D "EXCLUDE_MIF_SUPPORT" /D "EXCLUDE_PNM_SUPPORT" /D "EXCLUDE_RAS_SUPPORT" /D "EXCLUDE_BMP_SUPPORT" /D "EXCLUDE_PGX_SUPPORT" /D "EXCLUDE_TIFF_SUPPORT" /D "JAS_WIN_MSVC_BUILD" /D "JAS_TYPES" /D "_CRT_SECURE_NO_DEPRECATE" /D "JAS_GEO_OMIT_PRINTING_CODE" /D "_MBCS" /Fp"..\lib/im_jp2.pch" /Fo"..\obj\im_jp2/" /Fd"..\lib/" /GZ /c /GX 
# ADD CPP /nologo /MT /I "../include" /I "../src" /I "../src/libjasper" /Z7 /W4 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "EXCLUDE_JPG_SUPPORT" /D "EXCLUDE_MIF_SUPPORT" /D "EXCLUDE_PNM_SUPPORT" /D "EXCLUDE_RAS_SUPPORT" /D "EXCLUDE_BMP_SUPPORT" /D "EXCLUDE_PGX_SUPPORT" /D "EXCLUDE_TIFF_SUPPORT" /D "JAS_WIN_MSVC_BUILD" /D "JAS_TYPES" /D "_CRT_SECURE_NO_DEPRECATE" /D "JAS_GEO_OMIT_PRINTING_CODE" /D "_MBCS" /Fp"..\lib/im_jp2.pch" /Fo"..\obj\im_jp2/" /Fd"..\lib/" /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1046 /d "_DEBUG" 
# ADD RSC /l 1046 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\im_jp2.lib" 
# ADD LIB32 /nologo /out:"..\lib\im_jp2.lib" 

!ENDIF

# Begin Target

# Name "im_jp2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\im_format_jp2.cpp
# End Source File
# Begin Source File

SOURCE=..\src\jas_binfile.c
# End Source File
# Begin Group "libJasper"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\libjasper\base\jas_cm.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\base\jas_debug.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\base\jas_getopt.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\base\jas_icc.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\base\jas_iccdata.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\base\jas_image.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\base\jas_init.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\base\jas_malloc.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\base\jas_seq.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\base\jas_stream.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\base\jas_string.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\base\jas_tmr.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\base\jas_tvp.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\base\jas_version.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jp2\jp2_cod.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jp2\jp2_dec.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jp2\jp2_enc.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_bs.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_cs.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_dec.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_enc.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_math.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_mct.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_mqcod.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_mqdec.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_mqenc.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_qmfb.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_t1cod.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_t1dec.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_t1enc.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_t2cod.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_t2dec.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_t2enc.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_tagtree.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_tsfb.c
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_util.c
# End Source File
# Begin Group "inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\libjasper\jasper\jas_cm.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jasper\jas_config.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jasper\jas_debug.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jasper\jas_fix.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jasper\jas_getopt.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jasper\jas_icc.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jasper\jas_image.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jasper\jas_init.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jasper\jas_malloc.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jasper\jas_math.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jasper\jas_seq.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jasper\jas_stream.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jasper\jas_string.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jasper\jas_tmr.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jasper\jas_tvp.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jasper\jas_types.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jasper\jas_version.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jasper\jasper.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jp2\jp2_cod.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jp2\jp2_dec.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_bs.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_cod.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_cs.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_dec.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_enc.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_fix.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_flt.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_math.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_mct.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_mqcod.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_mqdec.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_mqenc.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_qmfb.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_t1cod.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_t1dec.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_t1enc.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_t2cod.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_t2dec.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_t2enc.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_tagtree.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_tsfb.h
# End Source File
# Begin Source File

SOURCE=..\src\libjasper\jpc\jpc_util.h
# End Source File
# End Group
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\im_format_jp2.h
# End Source File
# End Group
# End Target
# End Project

