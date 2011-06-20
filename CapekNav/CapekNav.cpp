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

#include "CapekNav.h"

#include <iostream>
#include <math.h>

#include "Recast.h"
#include "DetourNavMesh.h"
#include "File.h"

//
CapekNav* CapekNav::s_singletonInstance = NULL;

//
CapekNav::CapekNav()
{
}

//
CapekNav::~CapekNav()
{
}

//
CapekNav* CapekNav::GetInstance()
{
	if ( s_singletonInstance == NULL )
		s_singletonInstance = new CapekNav();
	return s_singletonInstance;
}

//
bool CapekNav::Initialise()
{
	m_navMesh = new dtNavMesh;
	if (!m_navMesh)
	{
		std::cerr << "Could not create Detour navmesh" << std::endl;
		return false;
	}
	return true;
}

//
bool CapekNav::Release()
{
	delete m_navMesh;
	return true;
}

//
bool CapekNav::AddTile(const char *fn)
{
	std::cerr << "CapekNav::AddTile(" << fn << ")" << std::endl;
	//
	unsigned char* navData = 0;
	int navDataSize = 0;

	//
	File *file = new File(fn);
	file->Open();
	navDataSize = file->Size();
	navData = new unsigned char[navDataSize];
	file->ReadBytes(navData, 0, navDataSize);
	file->Close();

	//
	if (!m_navMesh->init(navData, navDataSize, DT_TILE_FREE_DATA, 2048))
	{
		delete [] navData;
		std::cerr << "Could not init Detour navmesh" << std::endl;
		return false;
	}

	return true;
}

//
int CapekNav::FindStraightPath(WOWPOS start, WOWPOS end, WOWPOS *path, int size)
{
	//
	float m_spos[3];
	m_spos[0] = -1.0f * start.y;
	m_spos[1] = start.z;
	m_spos[2] = -1.0f * start.x;

	//
	float m_epos[3];
	m_epos[0] = -1.0f * end.y;
	m_epos[1] = end.z;
	m_epos[2] = -1.0f * end.x;

	//
	dtQueryFilter m_filter;
	m_filter.includeFlags = 0xffff;
	m_filter.excludeFlags = 0;

	//
	float m_polyPickExt[3];
	m_polyPickExt[0] = 2;
	m_polyPickExt[1] = 4;
	m_polyPickExt[2] = 2;

	//
	dtPolyRef m_startRef;
	dtPolyRef m_endRef;

	//
	m_startRef = m_navMesh->findNearestPoly(m_spos, m_polyPickExt, &m_filter, 0);
	m_endRef = m_navMesh->findNearestPoly(m_epos, m_polyPickExt, &m_filter, 0);

	//
	if ( !m_startRef || !m_endRef )
	{
		std::cerr << "Could not find any nearby poly's (" << m_startRef << "," << m_endRef << ")" << std::endl;
		return ERROR_NEARESTPOLY;
	}

	//
	static const int MAX_POLYS = 256;
	dtPolyRef m_polys[MAX_POLYS];
	int m_npolys;
	float m_straightPath[MAX_POLYS*3];
	unsigned char m_straightPathFlags[MAX_POLYS];
	dtPolyRef m_straightPathPolys[MAX_POLYS];
	int m_nstraightPath;

	//
	int pos = 0;

	//
	m_npolys = m_navMesh->findPath(m_startRef, m_endRef, m_spos, m_epos, &m_filter, m_polys, MAX_POLYS);
	m_nstraightPath = 0;
	if (m_npolys)
	{
		m_nstraightPath = m_navMesh->findStraightPath(m_spos, m_epos, m_polys, m_npolys, m_straightPath, m_straightPathFlags, m_straightPathPolys, MAX_POLYS);
		for ( int i = 0; i < m_nstraightPath*3; )
		{
			path[pos].y = -1.0f * m_straightPath[i++];
			path[pos].z = m_straightPath[i++];
			path[pos].x = -1.0f * m_straightPath[i++];
			pos++;
		}
		// append the end point
		path[pos].x = end.x;
		path[pos].y = end.y;
		path[pos].z = end.z;
		pos++;
	}

	return pos;
}



















