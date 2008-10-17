# Microsoft Developer Studio Project File - Name="im_process" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=im_process - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "im_process.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "im_process.mak" CFG="im_process - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "im_process - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "im_process - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\lib"
# PROP BASE Intermediate_Dir "..\obj\im_process"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "..\obj\im_process"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /I "../include" /I "../src" /Z7 /W4 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "_CRT_SECURE_NO_DEPRECATE" /D "_MBCS" /Fp"..\lib/im_process.pch" /Fo"..\obj\im_process/" /Fd"..\lib/" /GZ /c /GX 
# ADD CPP /nologo /MT /I "../include" /I "../src" /Z7 /W4 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "_CRT_SECURE_NO_DEPRECATE" /D "_MBCS" /Fp"..\lib/im_process.pch" /Fo"..\obj\im_process/" /Fd"..\lib/" /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1046 /d "_DEBUG" 
# ADD RSC /l 1046 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\im_process.lib" 
# ADD LIB32 /nologo /out:"..\lib\im_process.lib" 

!ENDIF

# Begin Target

# Name "im_process - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\process\im_analyze.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_arithmetic_bin.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_arithmetic_un.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_canny.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_color.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_convolve.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_convolve_rank.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_distance.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_effects.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_geometric.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_histogram.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_houghline.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_kernel.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_logic.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_morphology_bin.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_morphology_gray.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_quantize.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_render.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_resize.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_statistics.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_threshold.cpp
# End Source File
# Begin Source File

SOURCE=..\src\process\im_tonegamut.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\im_kernel.h
# End Source File
# Begin Source File

SOURCE=..\include\im_process.h
# End Source File
# Begin Source File

SOURCE=..\include\im_process_ana.h
# End Source File
# Begin Source File

SOURCE=..\include\im_process_glo.h
# End Source File
# Begin Source File

SOURCE=..\include\im_process_loc.h
# End Source File
# Begin Source File

SOURCE=..\include\im_process_pon.h
# End Source File
# End Group
# End Target
# End Project

