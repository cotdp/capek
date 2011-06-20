/*
 * Copyright 2011 Michael Cutler <m@cotdp.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "File.h"

#include <stdio.h>
#include <stdlib.h>

/**
 *
 */
File::File(std::string *fn)
{
   fileHandle = NULL;
   fileName = fn;
}

/**
 *
 */
File::File(const char *fn)
{
   fileHandle = NULL;
   fileName = new std::string(fn);
}

File::~File()
{
   Close();
}

void File::Seek(uint32_t position)
{
    if ( fileHandle )
       fseek(fileHandle, position, SEEK_SET);
}

void File::Skip(uint32_t offset)
{
    if ( fileHandle )
       fseek(fileHandle, offset, SEEK_CUR);
}

bool File::Open()
{
   if ( fileHandle = fopen(fileName->c_str(),"rb") )
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool File::Close()
{
   if ( fileHandle )
   {
      fclose(fileHandle);
      return true;
   }
   else
   {
      return false;
   }
}

bool File::Exists()
{
	return true;
}

int File::ReadInt()
{
   int value = 0;
   ReadBytes((uint8_t*)&value, 0, sizeof(int));
   return value;
}

long File::Size()
{
	long size = -1;
	if ( fileHandle )
	{
		long pos = ftell(fileHandle);
		fseek(fileHandle, 0L, SEEK_END);
		size = ftell(fileHandle);
		fseek(fileHandle, pos, SEEK_SET);
	}
	return size;
}

uint32_t File::ReadBytes(uint8_t *dst, uint32_t offset, uint32_t length)
{
   uint32_t bytesRead = 0;
   if ( fileHandle )
      bytesRead = fread(dst+offset, 1, length, fileHandle);
   return bytesRead;
}

uint8_t File::ReadUInt8()
{
   uint8_t value = 0;
   ReadBytes(&value, 0, sizeof(uint8_t));
   return value;
}

uint16_t File::ReadUInt16()
{
   uint16_t value = 0;
   ReadBytes((uint8_t*)&value, 0, sizeof(uint16_t));
   return value;
}

uint32_t File::ReadUInt32()
{
   uint32_t value = 0;
   ReadBytes((uint8_t*)&value, 0, sizeof(uint32_t));
   return value;
}

uint64_t File::ReadUInt64()
{
   uint64_t value = 0;
   ReadBytes((uint8_t*)&value, 0, sizeof(uint64_t));
   return value;
}

float File::ReadFloat()
{
   float value = 0;
   ReadBytes((uint8_t*)&value, 0, sizeof(float));
   return value;
}
