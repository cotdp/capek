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

#include <iostream>

#include "CapekNav.h"


int main ( int argc, char** argv, char** env )
{
	CapekNav* nav = CapekNav::GetInstance();

	nav->Initialise();
	nav->AddTile("../Meshes/32_48.navmesh");

	WOWPOS start = { -8949.95f, -132.493f, 83.5312f };
	WOWPOS end = { -9046.507f, -45.71962f, 88.33186f };

	WOWPOS *path = new WOWPOS[MAX_PATH];
	int size = MAX_PATH;

	int pathSize = nav->FindStraightPath(start, end, path, size);

	std::cout << "FindStraightPath: returned " << pathSize << " points." << std::endl;
	for ( int i = 0; i < pathSize; i++ )
	{
		std::cout << "   ... X=" << path[i].x << ", Y=" << path[i].y << ", Z=" << path[i].z << std::endl;
	}

	nav->Release();

	return 0;
}
