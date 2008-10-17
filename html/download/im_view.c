/* IM 3 sample that shows an image.

  Needs "im.lib", "iup.lib", "cd.lib" and "cdiup.lib".

  Usage: im_view <file_name>

    Example: im_view test.tif

  Click on image to open another file.
*/

#include <iup.h>
#include <cd.h>
#include <cdiup.h>
#include <im.h>
#include <im_image.h>

#include <stdio.h>
#include <string.h>

static int disable_repaint = 0; /* used to optimize repaint, while opening a new file */

static void PrintError(int error)
{
  switch (error)
  {
  case IM_ERR_OPEN:
    printf("Error Opening File.\n");
    break;
  case IM_ERR_MEM:
    printf("Insuficient memory.\n");
    break;
  case IM_ERR_ACCESS:
    printf("Error Accessing File.\n");
    break;
  case IM_ERR_DATA:
    printf("Image type not Suported.\n");
    break;
  case IM_ERR_FORMAT:
    printf("Invalid Format.\n");
    break;
  case IM_ERR_COMPRESS:
    printf("Invalid or unsupported compression.\n");
    break;
  default:
    printf("Unknown Error.\n");
  }
}

static int cbRepaint(Ihandle* iup_canvas)
{
  cdCanvas* cd_canvas = (cdCanvas*)IupGetAttribute(iup_canvas, "cdCanvas");
  imImage* image = (imImage*)IupGetAttribute(iup_canvas, "imImage");

  if (!cd_canvas || disable_repaint)
    return IUP_DEFAULT;

  cdActivate(cd_canvas);
  cdClear();

  if (!image)
    return IUP_DEFAULT;

  imcdCanvasPutImage(cd_canvas, image, 0, 0, image->width, image->height, 0, 0, 0, 0);
  
  cdFlush();
  
  return IUP_DEFAULT;
}
                              
static void ShowImage(char* file_name, Ihandle* iup_dialog)
{
  int error;
  imImage* image = (imImage*)IupGetAttribute(iup_dialog, "imImage");
  if (image) imImageDestroy(image);
  IupSetAttribute(iup_dialog, "imImage", NULL);

  image = imFileImageLoadBitmap(file_name, 0, &error);
  if (!image) 
  {
    PrintError(error);
    return;
  }

  IupSetAttribute(iup_dialog, "imImage", (char*)image);
  IupStoreAttribute(iup_dialog, "TITLE", file_name);

  cbRepaint(iup_dialog); /* we can do this because canvas inherit attributes from the dialog */
}

static int cbButton(Ihandle* iup_canvas, int but, int pressed)
{
  char file_name[200] = "*.*";

  if (but != IUP_BUTTON1 || !pressed)
    return IUP_DEFAULT;
  
  disable_repaint = 1;
  if (IupGetFile(file_name) != 0)
  {
    disable_repaint = 0;
    return IUP_DEFAULT;
  }

  disable_repaint = 0;
  ShowImage(file_name, IupGetDialog(iup_canvas));
  
  return IUP_DEFAULT;
}

static int cbClose(Ihandle* iup_dialog)
{
  cdCanvas* cd_canvas = (cdCanvas*)IupGetAttribute(iup_dialog, "cdCanvas");
  imImage* image = (imImage*)IupGetAttribute(iup_dialog, "imImage");

  if (cd_canvas) cdKillCanvas(cd_canvas);
  if (image) imImageDestroy(image);

  return IUP_CLOSE;
}

static Ihandle* CreateDialog(void)
{
  Ihandle *iup_dialog;
  Ihandle *iup_canvas;
  cdCanvas* cd_canvas;

  iup_canvas = IupCanvas("do_nothing");
  IupSetAttribute(iup_canvas, IUP_BUTTON_CB, "cbButton");
  IupSetAttribute(iup_canvas, IUP_ACTION, "cbRepaint");
  
  iup_dialog = IupDialog(iup_canvas);
  IupSetAttribute(iup_dialog, IUP_CLOSE_CB, "cbClose");
  IupSetAttribute(iup_dialog, IUP_SIZE, "HALFxHALF");

  IupSetFunction("cbRepaint", (Icallback)cbRepaint);
  IupSetFunction("cbButton", (Icallback)cbButton);
  IupSetFunction("cbClose", (Icallback)cbClose);

  IupMap(iup_dialog);

  cd_canvas = cdCreateCanvas(CD_IUP, iup_canvas);
  IupSetAttribute(iup_dialog, "cdCanvas", (char*)cd_canvas);

  return iup_dialog;
}

int main(int argc, char* argv[])
{
  Ihandle* dlg;

  IupOpen();

  dlg = CreateDialog();

  IupShow(dlg);
  
  /* Try to get a file name from the command line. */
  if (argc > 1)
  {
    ShowImage(argv[1], dlg);
  }
  else   
  {
    char file_name[1024] = "*.*";
    if (IupGetFile(file_name) == 0)
    {
      ShowImage(file_name, dlg);
    }
  }
                                   
  IupMainLoop();
  IupDestroy(dlg);
  IupClose();

  return 1;
}
