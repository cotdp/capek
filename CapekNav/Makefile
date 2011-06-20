
RECAST = ../Contrib/recastnavigation
DETOUR_CFLAGS = -I$(RECAST)/Recast/Include -I$(RECAST)/Detour/Include
DETOUR_SOURCES = $(RECAST)/Detour/Source/DetourCommon.cpp $(RECAST)/Detour/Source/DetourNavMesh.cpp $(RECAST)/Detour/Source/DetourNavMeshBuilder.cpp $(RECAST)/Detour/Source/DetourNode.cpp

UTIL_SOURCES = ../Utils/File.cpp

all:  CapekNav.cpp  CapekNavTest.cpp
	g++  -m32 -g -I../Utils  $(DETOUR_CFLAGS) $(DETOUR_SOURCES) $(UTIL_SOURCES)  CapekNav.cpp  -o CapekNavTest  CapekNavTest.cpp
