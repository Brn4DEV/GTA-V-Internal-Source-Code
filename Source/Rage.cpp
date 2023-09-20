#include "stdafx.h"

CPattern PatternModelSpawn("\x48\x8B\xC8\xFF\x52\x30\x84\xC0\x74\x05\x48", "xxxxxxxxxxx");
auto ModelPattern = PatternModelSpawn.find(0).get(0).get<char>(8);
char* ObjectRestore[2];
void Rage::PatchObjects()
{
	memcpy_s(ObjectRestore, 2, ModelPattern, 2);
	memset(ModelPattern, 0x90, 2);
}
void Rage::RestoreObjects()
{
	memcpy_s(ModelPattern, 2, ObjectRestore, 2);
}
/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/