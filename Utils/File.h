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

#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include "stdint.h"

#include <string>

class File
{
	public:
		//
		File(std::string *fn);
		//
		File(const char *fn);
		//
		virtual ~File();
		//
		bool Exists();
		//
		bool Open();
		//
		bool Close();
		//
		void Seek(uint32_t position);
		//
		void Skip(uint32_t offset);
		//
		long Size();
		//
		uint8_t ReadUInt8();
        //
        uint16_t ReadUInt16();
		//
		uint32_t ReadUInt32();
        //
        uint64_t ReadUInt64();
        //
        float ReadFloat();
        //
        int ReadInt();
		//
		uint32_t ReadBytes(uint8_t *dst, uint32_t offset, uint32_t length);

	private:
		//
		FILE* fileHandle;
		//
		std::string *fileName;
};

#endif /* FILE_H_ */
