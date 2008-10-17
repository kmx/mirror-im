/** \file
 * \brief KRN - IM Kernel File Format
 *
 * See Copyright Notice in im_lib.h
 * $Id$
 */

#include "im_format.h"
#include "im_format_all.h"
#include "im_util.h"
#include "im_counter.h"

#include "im_binfile.h"

#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>

static int iKRNReadNextInteger(imBinFile* handle, int *value)
{
  int c = 0, found = 0;
  static char buffer[10];

  while (!found)
  {
    imBinFileRead(handle, &buffer[c], 1, 1);

    /* if it's a number increments the number of characters readed */
    if ((buffer[c] >= (int)'0' && buffer[c] <= (int)'9') || buffer[c] == (int)'-')
      c++;
    else
    {
      /* if it's not a number and we readed some characters convert them to an integer */
      if (c > 0)
      {
        buffer[c] = 0;
        *value = atoi(buffer);
        found = 1;
      }
    }

    if (imBinFileError(handle) || c > 10)
      return 0;
  } 

  return 1;
}

static int iKRNReadNextReal(imBinFile* handle, float *value)
{
  int c = 0, found = 0;
  static char buffer[16];

  while (!found)
  {
    imBinFileRead(handle, &buffer[c], 1, 1);

    /* if it's a number increments the number of characters readed */
    if ((buffer[c] >= (int)'0' && buffer[c] <= (int)'9') || buffer[c] == (int)'-' || buffer[c] == (int)'.')
      c++;
    else
    {
      /* if it's not a number and we readed some characters convert them to an integer */
      if (c > 0)
      {
        buffer[c] = 0;
        *value = (float)atof(buffer);
        found = 1;
      }
    }

    if (imBinFileError(handle) || c > 16)
      return 0;
  } 

  return 1;
}

static int iKRNReadDescription(imBinFile* handle, char* comment, int *size)
{
  imbyte byte_value = 0;

  // find the first \n
  while(byte_value != '\n')
  {
    imBinFileRead(handle, &byte_value, 1, 1);
    if (imBinFileError(handle))
      return 0;
  }

  *size = 0;

  // Read up to the next \n

  imBinFileRead(handle, &byte_value, 1, 1);
  if (imBinFileError(handle))
    return 0;

  while(byte_value != '\n')
  {
    if (byte_value != '\r')
    {
      comment[*size] = byte_value;
      (*size)++;
    }

    imBinFileRead(handle, &byte_value, 1, 1);
    if (imBinFileError(handle))
      return 0;
  }

  if (*size != 0)
  {
    comment[*size] = 0;
    (*size)++;
  }

  return 1;
}

static const char* iKRNCompTable[1] = 
{
  "NONE"
};

class imFormatKRN: public imFormat
{
  imBinFile* handle;          /* the binary file handle */

public:
  imFormatKRN()
    :imFormat("KRN", 
              "IM Kernel File Format", 
              "*.krn;", 
              iKRNCompTable, 
              1, 
              0)
    {}
  ~imFormatKRN() {}

  int Open(const char* file_name);
  int New(const char* file_name);
  void Close();
  void* Handle(int index);
  int ReadImageInfo(int index);
  int ReadImageData(void* data);
  int WriteImageInfo();
  int WriteImageData(void* data);
  int CanWrite(const char* compression, int color_mode, int data_type) const;
};

void imFormatRegisterKRN(void)
{
  imFormatRegister(new imFormatKRN());
}

int imFormatKRN::Open(const char* file_name)
{
  char sig[9];

  /* opens the binary file for reading */
  handle = imBinFileOpen(file_name);
  if (!handle)
    return IM_ERR_OPEN;

  /* reads the KRN format identifier */
  imBinFileRead(handle, sig, 8, 1);
  if (imBinFileError(handle))
  {
    imBinFileClose(handle);
    return IM_ERR_ACCESS;
  }

  sig[8] = 0;

  if (!imStrEqual(sig, "IMKERNEL"))
  {
    imBinFileClose(handle);
    return IM_ERR_FORMAT;
  }

  this->image_count = 1;
  strcpy(this->compression, "NONE");

  return IM_ERR_NONE;
}

int imFormatKRN::New(const char* file_name)
{
  /* opens the binary file for writing */
  handle = imBinFileNew(file_name);
  if (!handle)
    return IM_ERR_OPEN;

  this->image_count = 1;  
  if (!imBinFileWrite(handle, (void*)"IMKERNEL\n", 9, 1))
  {
    imBinFileClose(handle);
    return IM_ERR_ACCESS;
  }

  return IM_ERR_NONE;
}

void imFormatKRN::Close()
{
  imBinFileClose(handle);
}

void* imFormatKRN::Handle(int index)
{
  if (index == 0)
    return (void*)this->handle;
  else
    return NULL;
}

int imFormatKRN::ReadImageInfo(int index)
{
  (void)index;
  this->file_color_mode = IM_GRAY|IM_TOPDOWN;

  char desc[512];
  int desc_size;
  if (!iKRNReadDescription(handle, desc, &desc_size))
    return IM_ERR_ACCESS;

  imAttribTable* attrib_table = AttribTable();
  if (desc_size)
    attrib_table->Set("Description", IM_BYTE, desc_size, desc);

  if (!iKRNReadNextInteger(handle, &this->width))
    return IM_ERR_ACCESS;

  if (!iKRNReadNextInteger(handle, &this->height))
    return IM_ERR_ACCESS;

  int type;
  if (!iKRNReadNextInteger(handle, &type))
    return IM_ERR_ACCESS;

  if (type == 0)
    this->file_data_type = IM_INT;
  else
    this->file_data_type = IM_FLOAT;

  return IM_ERR_NONE;
}

int imFormatKRN::WriteImageInfo()
{
  this->file_data_type = this->user_data_type;
  this->file_color_mode = IM_GRAY|IM_TOPDOWN;

  imAttribTable* attrib_table = AttribTable();

  int attrib_size;
  const void* attrib_data = attrib_table->Get("Description", NULL, &attrib_size);
  if (attrib_data)
  {
    char* desc = (char*)attrib_data;
    int size = 0;
    while(size < (attrib_size-1) && (desc[size] != '\r' && desc[size] != '\n'))
      size++;

    imBinFileWrite(handle, desc, size, 1);
  }
  imBinFileWrite(handle, (void*)"\n", 1, 1);

  imBinFilePrintf(handle, "%d\n", this->width);
  imBinFilePrintf(handle, "%d\n", this->height);

  if (this->file_data_type == IM_INT)
    imBinFileWrite(handle, (void*)"0\n", 1, 1);
  else
    imBinFileWrite(handle, (void*)"1\n", 1, 1);
  
  /* tests if everything was ok */
  if (imBinFileError(handle))
    return IM_ERR_ACCESS;

  return IM_ERR_NONE;
}

int imFormatKRN::ReadImageData(void* data)
{
  imCounterTotal(this->counter, this->height, "Reading KRN...");

  for (int row = 0; row < this->height; row++)
  {
    for (int col = 0; col < this->width; col++)
    {
      if (this->file_data_type == IM_INT)
      {
        int value;
        if (!iKRNReadNextInteger(handle, &value))
          return IM_ERR_ACCESS;

        ((int*)this->line_buffer)[col] = value;
      }
      else
      {
        float value;
        if (!iKRNReadNextReal(handle, &value))
          return IM_ERR_ACCESS;

        ((float*)this->line_buffer)[col] = value;
      }
    }

    imFileLineBufferRead(this, data, row, 0);

    if (!imCounterInc(this->counter))
      return IM_ERR_COUNTER;
  }

  return IM_ERR_NONE;
}

int imFormatKRN::WriteImageData(void* data)
{
  imCounterTotal(this->counter, this->height, "Writing KRN...");

  for (int row = 0; row < this->height; row++)
  {
    imFileLineBufferWrite(this, data, row, 0);

    for (int col = 0; col < this->width; col++)
    {
      if (this->file_data_type == IM_INT)
      {
        int value = ((int*)this->line_buffer)[col];

        if (!imBinFilePrintf(handle, "%d ", value))
          return IM_ERR_ACCESS;
      }
      else
      {
        float value = ((float*)this->line_buffer)[col];

        if (!imBinFilePrintf(handle, "%f ", (double)value))
          return IM_ERR_ACCESS;
      }

      if (col == this->width-1)
        imBinFileWrite(handle, (void*)"\n", 1, 1);
    }

    if (imBinFileError(handle))
      return IM_ERR_ACCESS;     

    if (!imCounterInc(this->counter))
      return IM_ERR_COUNTER;
  }

  return IM_ERR_NONE;
}

int imFormatKRN::CanWrite(const char* compression, int color_mode, int data_type) const
{
  int color_space = imColorModeSpace(color_mode);

  if (color_space != IM_GRAY)
    return IM_ERR_DATA;                       
                                              
  if (data_type != IM_INT && data_type != IM_FLOAT)
    return IM_ERR_DATA;

  if (!compression || compression[0] == 0)
    return IM_ERR_NONE;

  if (!imStrEqual(compression, "NONE"))
    return IM_ERR_COMPRESS;

  return IM_ERR_NONE;
}
