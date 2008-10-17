# Microsoft Developer Studio Project File - Name="im" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=im - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "im.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "im.mak" CFG="im - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "im - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "im - x64 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "im - Win32 Debug"

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
# ADD BASE CPP /nologo /MT /I "../include" /I "../src" /I "../src/libtiff" /I "../src/libjpeg" /I "../src/zlib" /I "../src/libexif" /I "../src/libpng" /I "../src/liblzf" /Z7 /W4 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "PNG_NO_STDIO" /D "PNG_USE_PNGVCRD" /D "PNG_TIME_RFC1123_SUPPORTED" /D "_CRT_SECURE_NO_DEPRECATE" /D "USE_EXIF" /D "_MBCS" /Fp"..\lib/im.pch" /Fo"..\obj/" /Fd"..\lib/" /GZ /c /GX 
# ADD CPP /nologo /MT /I "../include" /I "../src" /I "../src/libtiff" /I "../src/libjpeg" /I "../src/zlib" /I "../src/libexif" /I "../src/libpng" /I "../src/liblzf" /Z7 /W4 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "PNG_NO_STDIO" /D "PNG_USE_PNGVCRD" /D "PNG_TIME_RFC1123_SUPPORTED" /D "_CRT_SECURE_NO_DEPRECATE" /D "USE_EXIF" /D "_MBCS" /Fp"..\lib/im.pch" /Fo"..\obj/" /Fd"..\lib/" /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1046 /d "_DEBUG" 
# ADD RSC /l 1046 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\im.lib" 
# ADD LIB32 /nologo /out:"..\lib\im.lib" 

!ELSEIF  "$(CFG)" == "im - x64 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "..\lib\x64"
# PROP BASE Intermediate_Dir "..\obj\x64"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib\x64"
# PROP Intermediate_Dir "..\obj\x64"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /I "../include" /I "../src" /I "../src/libtiff" /I "../src/libjpeg" /I "../src/zlib" /I "../src/libexif" /I "../src/libpng" /I "../src/liblzf" /Z7 /W4 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "PNG_NO_STDIO" /D "PNG_USE_PNGVCRD" /D "PNG_TIME_RFC1123_SUPPORTED" /D "_CRT_SECURE_NO_DEPRECATE" /D "USE_EXIF" /D "_MBCS" /Fp"..\lib\x64/im.pch" /Fo"..\obj\x64/" /Fd"..\lib\x64/" /GZ /c /GX 
# ADD CPP /nologo /MT /I "../include" /I "../src" /I "../src/libtiff" /I "../src/libjpeg" /I "../src/zlib" /I "../src/libexif" /I "../src/libpng" /I "../src/liblzf" /Z7 /W4 /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "PNG_NO_STDIO" /D "PNG_USE_PNGVCRD" /D "PNG_TIME_RFC1123_SUPPORTED" /D "_CRT_SECURE_NO_DEPRECATE" /D "USE_EXIF" /D "_MBCS" /Fp"..\lib\x64/im.pch" /Fo"..\obj\x64/" /Fd"..\lib\x64/" /GZ /c /GX 
# ADD BASE MTL /nologo /win32 
# ADD MTL /nologo /win32 
# ADD BASE RSC /l 1046 /d "_DEBUG" 
# ADD RSC /l 1046 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\lib\x64\im.lib" 
# ADD LIB32 /nologo /out:"..\lib\x64\im.lib" 

!ENDIF

# Begin Target

# Name "im - Win32 Debug"
# Name "im - x64 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\im_attrib.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_bin.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_binfile.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_colorhsi.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_colormode.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_colorutil.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_compress.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_convertbitmap.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_convertcolor.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_converttype.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_counter.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_datatype.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_dib.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_dibxbitmap.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_file.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_filebuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_fileraw.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_format.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_format_all.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_image.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_lib.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_palette.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_rgb2map.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_str.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_sysfile_win32.cpp
# End Source File
# Begin Source File

SOURCE=..\src\old_im.cpp
# End Source File
# Begin Source File

SOURCE=..\src\old_imcolor.c
# End Source File
# Begin Source File

SOURCE=..\src\old_imresize.c
# End Source File
# Begin Source File

SOURCE=..\src\tiff_binfile.c
# End Source File
# Begin Group "libTIFF"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\libtiff\tif_aux.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_close.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_codec.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_compress.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_dir.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_dirinfo.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_dirread.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_dirwrite.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_dumpmode.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_error.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_extension.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_fax3.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_fax3sm.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_flush.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_getimage.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_jpeg.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_luv.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_lzw.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_next.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_ojpeg.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_open.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_packbits.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_pixarlog.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_predict.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_print.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_read.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_strip.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_swab.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_thunder.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_tile.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_version.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_warning.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_write.c
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_zip.c
# End Source File
# Begin Group "inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\libtiff\t4.h
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_config.h
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_dir.h
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_fax3.h
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tif_predict.h
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tiff.h
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tiffio.h
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tiffiop.h
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\tiffvers.h
# End Source File
# Begin Source File

SOURCE=..\src\libtiff\uvcode.h
# End Source File
# End Group
# End Group
# Begin Group "libJPEG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\libjpeg\jcapimin.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jcapistd.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jccoefct.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jccolor.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jcdctmgr.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jchuff.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jcinit.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jcmainct.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jcmarker.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jcmaster.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jcomapi.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jcparam.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jcphuff.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jcprepct.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jcsample.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jctrans.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdapimin.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdapistd.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdatadst.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdatasrc.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdcoefct.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdcolor.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jddctmgr.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdhuff.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdinput.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdmainct.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdmarker.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdmaster.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdmerge.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdphuff.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdpostct.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdsample.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdtrans.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jerror.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jfdctflt.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jfdctfst.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jfdctint.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jidctflt.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jidctfst.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jidctint.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jidctred.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jmemmgr.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jmemnobs.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jquant1.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jquant2.c
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jutils.c
# End Source File
# Begin Group "inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\libjpeg\jchuff.h
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jconfig.h
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdct.h
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jdhuff.h
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jerror.h
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jinclude.h
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jmemsys.h
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jmorecfg.h
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jpegint.h
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jpeglib.h
# End Source File
# Begin Source File

SOURCE=..\src\libjpeg\jversion.h
# End Source File
# End Group
# End Group
# Begin Group "zlib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\zlib\adler32.c
# End Source File
# Begin Source File

SOURCE=..\src\zlib\compress.c
# End Source File
# Begin Source File

SOURCE=..\src\zlib\crc32.c
# End Source File
# Begin Source File

SOURCE=..\src\zlib\deflate.c
# End Source File
# Begin Source File

SOURCE=..\src\zlib\gzio.c
# End Source File
# Begin Source File

SOURCE=..\src\zlib\infback.c
# End Source File
# Begin Source File

SOURCE=..\src\zlib\inffast.c
# End Source File
# Begin Source File

SOURCE=..\src\zlib\inflate.c
# End Source File
# Begin Source File

SOURCE=..\src\zlib\inftrees.c
# End Source File
# Begin Source File

SOURCE=..\src\zlib\trees.c
# End Source File
# Begin Source File

SOURCE=..\src\zlib\uncompr.c
# End Source File
# Begin Source File

SOURCE=..\src\zlib\zutil.c
# End Source File
# End Group
# Begin Group "libEXIF"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\libexif\exif-byte-order.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-content.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-data.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-entry.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-format.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-ifd.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-loader.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-log.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-mem.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\canon\exif-mnote-data-canon.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\olympus\exif-mnote-data-olympus.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\pentax\exif-mnote-data-pentax.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-mnote-data.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-tag.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-utils.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\canon\mnote-canon-entry.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\canon\mnote-canon-tag.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\olympus\mnote-olympus-entry.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\olympus\mnote-olympus-tag.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\pentax\mnote-pentax-entry.c
# End Source File
# Begin Source File

SOURCE=..\src\libexif\pentax\mnote-pentax-tag.c
# End Source File
# Begin Group "inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\libexif\_stdint.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\config.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-byte-order.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-content.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-data.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-entry.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-format.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-ifd.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-loader.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-log.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-mem.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\canon\exif-mnote-data-canon.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\olympus\exif-mnote-data-olympus.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\pentax\exif-mnote-data-pentax.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-mnote-data-priv.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-mnote-data.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-tag.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif-utils.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\exif.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\i18n.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\canon\mnote-canon-entry.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\canon\mnote-canon-tag.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\olympus\mnote-olympus-entry.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\olympus\mnote-olympus-tag.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\pentax\mnote-pentax-entry.h
# End Source File
# Begin Source File

SOURCE=..\src\libexif\pentax\mnote-pentax-tag.h
# End Source File
# End Group
# End Group
# Begin Group "libPNG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\libpng\png.c
# End Source File
# Begin Source File

SOURCE=..\src\libpng\pngerror.c
# End Source File
# Begin Source File

SOURCE=..\src\libpng\pngget.c
# End Source File
# Begin Source File

SOURCE=..\src\libpng\pngmem.c
# End Source File
# Begin Source File

SOURCE=..\src\libpng\pngpread.c
# End Source File
# Begin Source File

SOURCE=..\src\libpng\pngread.c
# End Source File
# Begin Source File

SOURCE=..\src\libpng\pngrio.c
# End Source File
# Begin Source File

SOURCE=..\src\libpng\pngrtran.c
# End Source File
# Begin Source File

SOURCE=..\src\libpng\pngrutil.c
# End Source File
# Begin Source File

SOURCE=..\src\libpng\pngset.c
# End Source File
# Begin Source File

SOURCE=..\src\libpng\pngtrans.c
# End Source File
# Begin Source File

SOURCE=..\src\libpng\pngvcrd.c
# End Source File
# Begin Source File

SOURCE=..\src\libpng\pngwio.c
# End Source File
# Begin Source File

SOURCE=..\src\libpng\pngwrite.c
# End Source File
# Begin Source File

SOURCE=..\src\libpng\pngwtran.c
# End Source File
# Begin Source File

SOURCE=..\src\libpng\pngwutil.c
# End Source File
# Begin Group "inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\libpng\png.h
# End Source File
# Begin Source File

SOURCE=..\src\libpng\pngconf.h
# End Source File
# End Group
# End Group
# Begin Group "formats"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\im_format_bmp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_format_gif.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_format_ico.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_format_jpeg.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_format_krn.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_format_led.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_format_pcx.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_format_png.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_format_pnm.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_format_ras.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_format_raw.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_format_sgi.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_format_tga.cpp
# End Source File
# Begin Source File

SOURCE=..\src\im_format_tiff.cpp
# End Source File
# End Group
# Begin Group "libLZF"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\liblzf\lzf_c.c
# End Source File
# Begin Source File

SOURCE=..\src\liblzf\lzf_d.c
# End Source File
# Begin Group "inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\liblzf\lzf.h
# End Source File
# Begin Source File

SOURCE=..\src\liblzf\lzfP.h
# End Source File
# End Group
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\im.h
# End Source File
# Begin Source File

SOURCE=..\include\im_attrib.h
# End Source File
# Begin Source File

SOURCE=..\include\im_attrib_flat.h
# End Source File
# Begin Source File

SOURCE=..\include\im_binfile.h
# End Source File
# Begin Source File

SOURCE=..\include\im_color.h
# End Source File
# Begin Source File

SOURCE=..\include\im_colorhsi.h
# End Source File
# Begin Source File

SOURCE=..\include\im_complex.h
# End Source File
# Begin Source File

SOURCE=..\include\im_convert.h
# End Source File
# Begin Source File

SOURCE=..\include\im_counter.h
# End Source File
# Begin Source File

SOURCE=..\include\im_dib.h
# End Source File
# Begin Source File

SOURCE=..\include\im_file.h
# End Source File
# Begin Source File

SOURCE=..\include\im_format.h
# End Source File
# Begin Source File

SOURCE=..\include\im_format_all.h
# End Source File
# Begin Source File

SOURCE=..\include\im_format_raw.h
# End Source File
# Begin Source File

SOURCE=..\include\im_image.h
# End Source File
# Begin Source File

SOURCE=..\include\im_lib.h
# End Source File
# Begin Source File

SOURCE=..\include\im_math.h
# End Source File
# Begin Source File

SOURCE=..\include\im_math_op.h
# End Source File
# Begin Source File

SOURCE=..\include\im_palette.h
# End Source File
# Begin Source File

SOURCE=..\include\im_plus.h
# End Source File
# Begin Source File

SOURCE=..\include\im_raw.h
# End Source File
# Begin Source File

SOURCE=..\include\im_util.h
# End Source File
# Begin Source File

SOURCE=..\include\old_im.h
# End Source File
# End Group
# End Target
# End Project

