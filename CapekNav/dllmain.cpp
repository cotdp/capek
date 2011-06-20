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

#include <windows.h>
#include <stdio.h>

extern "C"
{

	/*
	   [DllImport("CapekNav.dll")]
	   public static extern int FindStraightPath(WOWPOS start, WOWPOS end, WOWPOS *path, int size);
	 */
	int __declspec(dllexport) FindStraightPath(WOWPOS start, WOWPOS end, WOWPOS *path, int size)
	{
	   return CapekNav::GetInstance()->FindStraightPath(start, end, path, size);
	}

};


/**
 */
BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	CapekNav* nav = CapekNav::GetInstance();
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			{
				nav->Initialise();
				break;
			}
		case DLL_PROCESS_DETACH:
			{
				nav->Release();
				break;
			}
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
	}
	return TRUE;
}
