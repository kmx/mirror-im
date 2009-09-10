/** \file
 * \brief RAW File Format
 *
 * See Copyright Notice in im_lib.h
 * $Id$
 */

#include "im_format.h"
#include "im_util.h"
#include "im_format_raw.h"
#include "im_counter.h"

#include "im_binfile.h"

#include <stdlib.h>
#include <string.h>

static const char* iRAWCompTable[1] = 
{
  "NONE"
};

class imFileFormatRAW: public imFileFormatBase
{
  imBinFile* handle;
  int padding;

  int iRawUpdateParam(int index);

public:
  imFileFormatRAW(const imFormat* _iformat): imFileFormatBase(_iformat) {}
  ~imFileFormatRAW() {}

  int Open(const char* file_name);
  int New(const char* file_name);
  void Close();
  void* Handle(int index);
  int ReadImageInfo(int index);
  int ReadImageData(void* data);
  int WriteImageInfo();
  int WriteImageData(void* data);
};

class imFormatRAW: public imFormat
{
public:
  imFormatRAW()
    :imFormat("RAW", 
              "RAW File Format", 
              "*.*;", 
              iRAWCompTable, 
              1, 
              1)
    {}
  ~imFormatRAW() {}

  imFileFormatBase* Create(void) const { return new imFileFormatRAW(this); }
  int CanWrite(const char* compression, int color_mode, int data_type) const;
};

static imFormat* raw_format = NULL;

void imFormatFinishRAW(void)
{
  if (raw_format)
  {
    delete raw_format;
    raw_format = NULL;
  }
}

imFormat* imFormatInitRAW(void)
{
  if (!raw_format)
    raw_format = new imFormatRAW();

  return raw_format;
}

int imFileFormatRAW::Open(const char* file_name)
{
  this->handle = imBinFileOpen(file_name);
  if (this->handle == NULL)
    return IM_ERR_OPEN;

  strcpy(this->compression, "NONE");

  this->image_count = 1;  /* at least one image */
  this->padding = 0;

  return IM_ERR_NONE;
}

int imFileFormatRAW::New(const char* file_name)
{
  this->handle = imBinFileNew(file_name);
  if (this->handle == NULL)
    return IM_ERR_OPEN;

  this->padding = 0;

  return IM_ERR_NONE;
}

void imFileFormatRAW::Close()
{
  imBinFileClose(this->handle);
}

void* imFileFormatRAW::Handle(int index)
{
  if (index == 0)
    return (void*)this->handle;
  else
    return NULL;
}

static int iCalcPad(int padding, int line_size)
{
  if (padding == 1)
    return 0;

  {
    int rest = line_size % padding;
    if (rest == 0)
      return 0;

    return padding - rest;
  }
}

int imFileFormatRAW::iRawUpdateParam(int index)
{
  (void)index;

  imAttribTable* attrib_table = AttribTable();

  // update image count
  int* icount = (int*)attrib_table->Get("ImageCount");
  if (icount)
    this->image_count = *icount;
  else
    this->image_count = 1;

  // update file byte order
  int* byte_order = (int*)attrib_table->Get("ByteOrder");
  if (byte_order)
    imBinFileByteOrder(this->handle, *byte_order);

  // position at start offset, the default is at 0
  int* start_offset = (int*)attrib_table->Get("StartOffset");
  if (!start_offset)
    imBinFileSeekOffset(this->handle, 0);
  else
    imBinFileSeekOffset(this->handle, *start_offset);

  if (imBinFileError(this->handle))
    return IM_ERR_ACCESS;

  int* stype = (int*)attrib_table->Get("SwitchType");
  if (stype)
    this->switch_type = *stype;

  // The following attributes MUST exist
  this->width = *(int*)attrib_table->Get("Width");
  this->height = *(int*)attrib_table->Get("Height");
  this->file_color_mode = *(int*)attrib_table->Get("ColorMode");
  this->file_data_type = *(int*)attrib_table->Get("DataType");

  int* pad = (int*)attrib_table->Get("Padding");
  if (pad)
  {
    int line_size = imImageLineSize(this->width, this->file_color_mode, this->file_data_type);
    if (this->switch_type && (this->file_data_type == IM_FLOAT || this->file_data_type == IM_CFLOAT))
      line_size *= 2;
    this->padding = iCalcPad(*pad, line_size);
  }

  return IM_ERR_NONE;
}

int imFileFormatRAW::ReadImageInfo(int index)
{
  return iRawUpdateParam(index);
}

int imFileFormatRAW::WriteImageInfo()
{
  this->file_color_mode = this->user_color_mode;
  this->file_data_type = this->user_data_type;

  return iRawUpdateParam(this->image_count);
}

static int iFileDataTypeSize(int file_data_type, int switch_type)
{
  int type_size = imDataTypeSize(file_data_type);
  if ((file_data_type == IM_FLOAT || file_data_type == IM_CFLOAT) && switch_type)
    type_size *= 2;
  return type_size;
}

int imFileFormatRAW::ReadImageData(void* data)
{
  int count = imFileLineBufferCount(this);
  int line_count = imImageLineCount(this->width, this->file_color_mode);
  int type_size = iFileDataTypeSize(this->file_data_type, this->switch_type);

  // treat complex as 2 real
  if (this->file_data_type == IM_CFLOAT) 
  {
    type_size /= 2;
    line_count *= 2;
  }

  imCounterTotal(this->counter, count, "Reading RAW...");

  int row = 0, plane = 0;
  for (int i = 0; i < count; i++)
  {
    imBinFileRead(this->handle, (imbyte*)this->line_buffer, line_count, type_size);

    if (imBinFileError(this->handle))
      return IM_ERR_ACCESS;

    imFileLineBufferRead(this, data, row, plane);

    if (!imCounterInc(this->counter))
      return IM_ERR_COUNTER;

    imFileLineBufferInc(this, &row, &plane);

    if (this->padding)
      imBinFileSeekOffset(this->handle, this->padding);
  }

  return IM_ERR_NONE;
}

int imFileFormatRAW::WriteImageData(void* data)
{
  int count = imFileLineBufferCount(this);
  int line_count = imImageLineCount(this->width, this->file_color_mode);
  int type_size = iFileDataTypeSize(this->file_data_type, this->switch_type);

  // treat complex as 2 real
  if (this->file_data_type == IM_CFLOAT) 
  {
    type_size /= 2;
    line_count *= 2;
  }

  imCounterTotal(this->counter, count, "Writing RAW...");

  int row = 0, plane = 0;
  for (int i = 0; i < count; i++)
  {
    imFileLineBufferWrite(this, data, row, plane);

    imBinFileWrite(this->handle, (imbyte*)this->line_buffer, line_count, type_size);

    if (imBinFileError(this->handle))
      return IM_ERR_ACCESS;

    if (!imCounterInc(this->counter))
      return IM_ERR_COUNTER;

    imFileLineBufferInc(this, &row, &plane);

    if (this->padding)
      imBinFileSeekOffset(this->handle, this->padding);
  }

  this->image_count++;
  return IM_ERR_NONE;
}

int imFormatRAW::CanWrite(const char* compression, int color_mode, int data_type) const
{
  (void)data_type;

  if (imColorSpace(color_mode) == IM_MAP)
    return IM_ERR_DATA;

  if (!compression || compression[0] == 0)
    return IM_ERR_NONE;

  if (!imStrEqual(compression, "NONE"))
    return IM_ERR_COMPRESS;

  return IM_ERR_NONE;
}
