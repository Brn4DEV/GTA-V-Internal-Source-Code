// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include <chrono>
#include <thread>
extern bool g_Running;
DWORD WINAPI ControlThread(LPVOID lpParam)
{
	Hooking::Start((HMODULE)lpParam);
	while (g_Running)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::this_thread::yield();
	}
	Hooking::Cleanup();
	FreeLibraryAndExitThread((HMODULE)lpParam, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ControlThread, hModule, NULL, NULL);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/