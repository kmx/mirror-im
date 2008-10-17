# Microsoft Developer Studio Project File - Name="im_fftw" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=im_fftw - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "im_fftw.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "im_fftw.mak" CFG="im_fftw - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "im_fftw - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "im_fftw - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\lib"
# PROP BASE Intermediate_Dir "..\obj\im_fftw"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "..\obj\im_fftw"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /I "../include" /I "../src" /I "../src/fftw" /Z7 /W4 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "FFTW_ENABLE_FLOAT" /D "_CRT_SECURE_NO_DEPRECATE" /D "_MBCS" /Fp"..\lib/im_fftw.pch" /Fo"..\obj\im_fftw/" /Fd"..\lib/" /GZ /c /GX 
# ADD CPP /nologo /MT /I "../include" /I "../src" /I "../src/fftw" /Z7 /W4 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "FFTW_ENABLE_FLOAT" /D "_CRT_SECURE_NO_DEPRECATE" /D "_MBCS" /Fp"..\lib/im_fftw.pch" /Fo"..\obj\im_fftw/" /Fd"..\lib/" /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1046 /d "_DEBUG" 
# ADD RSC /l 1046 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\im_fftw.lib" 
# ADD LIB32 /nologo /out:"..\lib\im_fftw.lib" 

!ENDIF

# Begin Target

# Name "im_fftw - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\process\im_fft.cpp
# End Source File
# Begin Group "FFTW"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\fftw\config.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\executor.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fftwnd.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_1.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_10.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_11.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_12.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_13.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_14.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_15.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_16.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_2.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_3.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_32.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_4.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_5.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_6.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_64.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_7.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_8.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fn_9.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_1.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_10.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_11.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_12.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_13.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_14.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_15.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_16.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_2.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_3.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_32.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_4.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_5.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_6.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_64.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_7.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_8.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fni_9.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftw_10.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftw_16.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftw_2.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftw_3.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftw_32.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftw_4.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftw_5.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftw_6.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftw_64.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftw_7.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftw_8.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftw_9.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftwi_10.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftwi_16.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftwi_2.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftwi_3.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftwi_32.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftwi_4.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftwi_5.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftwi_6.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftwi_64.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftwi_7.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftwi_8.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\ftwi_9.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\generic.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\malloc.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\planner.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\putils.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\rader.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\timer.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\twiddle.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\wisdom.c
# End Source File
# Begin Source File

SOURCE=..\src\fftw\wisdomio.c
# End Source File
# Begin Group "inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\fftw\config.h
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fftw-int.h
# End Source File
# Begin Source File

SOURCE=..\src\fftw\fftw.h
# End Source File
# End Group
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project

