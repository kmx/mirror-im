# Microsoft Developer Studio Project File - Name="im_ecw" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=im_ecw - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "im_ecw.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "im_ecw.mak" CFG="im_ecw - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "im_ecw - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "im_ecw - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\lib"
# PROP BASE Intermediate_Dir "..\obj"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "..\obj"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /I "../include" /I "../src" /I "d:\LNG\ecw_sdk\include" /Z7 /W4 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "_CRT_SECURE_NO_WARNINGS" /D "_MBCS" /Fp"..\lib/im_ecw.pch" /Fo"..\obj/" /Fd"..\lib/" /GZ /c /GX 
# ADD CPP /nologo /MT /I "../include" /I "../src" /I "d:\LNG\ecw_sdk\include" /Z7 /W4 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "_CRT_SECURE_NO_WARNINGS" /D "_MBCS" /Fp"..\lib/im_ecw.pch" /Fo"..\obj/" /Fd"..\lib/" /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1046 /d "_DEBUG" 
# ADD RSC /l 1046 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\im_ecw.lib" 
# ADD LIB32 /nologo /out:"..\lib\im_ecw.lib" 

!ENDIF

# Begin Target

# Name "im_ecw - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\im_format_ecw.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\im_format_ecw.h
# End Source File
# End Group
# End Target
# End Project

