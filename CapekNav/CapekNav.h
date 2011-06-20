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

#ifndef CAPEKNAV_H_
#define CAPEKNAV_H_

//
#include "DetourNavMesh.h"

//
typedef struct _WOWPOS { float x; float y; float z; } WOWPOS;

//
#define MAX_PATH 1024

//
class CapekNav
{
public:
	static const int ERROR = -1;
	static const int ERROR_NEARESTPOLY = -2;

public:
	//
	static CapekNav* GetInstance();
	//
	virtual	~CapekNav();
	//
	bool Initialise();
	//
	bool Release();
	//
	int FindStraightPath(WOWPOS start, WOWPOS end, WOWPOS* path, int size );
	//
	bool AddTile(const char* fn);

private:
	//
	dtNavMesh* m_navMesh;

	//
	CapekNav();
	//
	static CapekNav* s_singletonInstance;
};

#endif /* CAPEKNAV_H_ */
