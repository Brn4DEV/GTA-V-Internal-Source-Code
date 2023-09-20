//Hooking.cpp
#pragma once
#include "stdafx.h"

//ScriptThread* (*GetActiveThread)() = nullptr;
HMODULE _hmoduleDLL;
HANDLE mainFiber;
DWORD wakeAt;

uint64_t* Hooking::m_frameCount;
static uint64_t m_worldPtr;
static BlipList* m_blipList;
static std::vector<LPVOID> m_hookedNative;
static uint64_t** m_globalPtr;
static std::vector<void*> EventPtr;
static const int EVENT_COUNT = 78;
static char EventRestore[EVENT_COUNT] = {};
static void* m_nativeTable;
static char object_spawn[24];
static char model_bypass[2];
static void* m_object_spawn;
static void* m_model_bypass;
static uint64_t m_player_list;
const char NOP = '\x90';
fpIsDLCPresent		                 	Hooking::is_DLC_present;

/* Start Hooking */
void Hooking::Start(HMODULE hmoduleDLL)
{
	_hmoduleDLL = hmoduleDLL;
	FindPatterns();
	if (!InitializeHooks())
		Cleanup();
}

BOOL Hooking::InitializeHooks()
{
	BOOL returnVal = TRUE;

	if (!iHook.Initialize()) {

		CLog::Error("Failed to initialize InputHook");
		returnVal = FALSE;
	}

	if (MH_Initialize() != MH_OK) {
		CLog::Error("MinHook failed to initialize");
		returnVal = FALSE;
	}

	if (!HookNatives()) {

		CLog::Error("Failed to initialize NativeHooks");
		returnVal = FALSE;
	}

	return returnVal;
}

Hooking::NativeHandler(*provideNative)(void* nativeTable, uint64_t nativeHash) = nullptr;
Hooking::NativeHandler Hooking::GetNativeHandler(uint64_t origHash)
{
	return provideNative(m_nativeTable, CrossMapping::MapNative(origHash));
}
/*never see it*/
bool rOckstardevelopper = true;
fpIsDLCPresent	OG_IS_DLC_PRESENT = nullptr;
BOOL __cdecl HK_IS_DLC_PRESENT(Hash dlchash)
{
	static uint64_t	last = 0;
	uint64_t		cur = *Hooking::m_frameCount;
	if (last != cur)
	{
		last = cur;
		Hooking::onTickInit();
	}
	if (rOckstardevelopper)
	{
		if (dlchash == 2532323046)return true;//2532323046 old
		else return OG_IS_DLC_PRESENT(dlchash);
	}
	else
		return OG_IS_DLC_PRESENT(dlchash);
}

bool Hooking::HookNatives()
{
	MH_STATUS Main_status = MH_CreateHook(Hooking::is_DLC_present, HK_IS_DLC_PRESENT, (void**)&OG_IS_DLC_PRESENT);
	if ((Main_status != MH_OK && Main_status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(Hooking::is_DLC_present) != MH_OK)
		return false;
	m_hookedNative.push_back(Hooking::is_DLC_present);
	//EnableTLSContext();
	return 1;
}

void __stdcall ScriptFunction(LPVOID lpParameter)
{
	try
	{
		ScriptMain();
	}
	catch (...)
	{
		CLog::Fatal("Failed scriptFiber");
	}
}


void Hooking::onTickInit()
{
	if (mainFiber == nullptr)
		mainFiber = ConvertThreadToFiber(nullptr);
	if (mainFiber == nullptr)
		mainFiber = GetCurrentFiber();
	if (timeGetTime() < wakeAt)
		return;
	static HANDLE scriptFiber;
	if (scriptFiber)
		SwitchToFiber(scriptFiber);
	else
		scriptFiber = CreateFiber(NULL, ScriptFunction, nullptr);
}


void Error(char* msg)
{
	CLog::Error(msg);
	Hooking::Cleanup();
}

void iterateBlips()
{
	uint64_t base = reinterpret_cast<uint64_t>(GetModuleHandleA(nullptr));
	BlipList* p = reinterpret_cast<BlipList*>(base + 0x20097A0);
	for (size_t i = 0; i < 1500; i++)
	{
		if (!p->m_Blips[i])
		{
			CLog::Msg("Help %d\n", i);
			continue;
		}
		CLog::Msg("%d x:%.2f y: %.2f\n", i, p->m_Blips[i]->coords.x, p->m_Blips[i]->coords.y);
	}

}

void	failPat(const char* name)
{
	CLog::Msg("Failed to find %s pattern.", name);
//	g_Running = false;
	exit(0);
}
template <typename T>
void	setFn
(
	const char* name,
	char* pat,
	char* mask,
	T* out,
	int			skip = 0
)
{
	char* ptr = nullptr;

	CPattern pattern(pat, mask);
	pattern.find(1 + skip);
	ptr = pattern.get(skip).get<char>(0);

	if (ptr == nullptr)
		failPat(name);

	*out = (T)ptr;
	return;
}
template <typename T>
void	setPat
(
	const char* name,
	char* pat,
	char* mask,
	T** out,
	bool		rel,
	int			offset = 0,
	int			deref = 0,
	int			skip = 0
)
{
	T* ptr = nullptr;

	CPattern pattern(pat, mask);
	pattern.find(1 + skip);
	if (rel)
		ptr = pattern.get(skip).get_rel<T>(offset);
	else
		ptr = pattern.get(skip).get<T>(offset);

	while (true)
	{
		if (ptr == nullptr)
			failPat(name);

		if (deref <= 0)
			break;
		ptr = *(T**)ptr;
		--deref;
	}

	*out = ptr;
	return;
}
int32_t maxVehicles;
int32_t maxPeds;
int32_t maxObjects;


void PrintddddText(char* text, int font, float x, float y, float scalex, float scaley, int r, int g, int b, int a, int position, bool outline)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_WRAP(0.0f, 1.0f);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	if (position == 0 || position == 1)
		UI::SET_TEXT_WRAP(0.0f, 1.0f);
	else
		UI::SET_TEXT_WRAP(0.0f, x);
	if (position == 1)
		UI::SET_TEXT_CENTRE(true);
	if (position == 2)
		UI::SET_TEXT_RIGHT_JUSTIFY(true);
	if (outline)
		UI::SET_TEXT_OUTLINE();
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(x, y);
}
	
rage::CReplayInterface* m_Replay_Interface;
bool Features::ShowPools = true;
void Features::ShowPools1() //novo
{
	if (Features::ShowPools)
	{
		if (m_Replay_Interface->m_object_interface)
		{
			maxVehicles = m_Replay_Interface->m_vehicle_interface->m_max_vehicles;
			maxPeds = m_Replay_Interface->m_ped_interface->m_max_peds;
			maxObjects = m_Replay_Interface->m_object_interface->m_max_objects;
			for (int i = 0; i < m_Replay_Interface->m_object_interface->m_max_objects; i++)
			{
				rage::CObject* Object = m_Replay_Interface->m_object_interface->get_object(i);
				if (Object)
				{
					Features::ObjPoolCurr++;
				}
			}
			for (int i = 0; i < m_Replay_Interface->m_ped_interface->m_max_peds; i++) {
				rage::CPed* Ped = m_Replay_Interface->m_ped_interface->get_ped(i);
				if (Ped)
				{
					Features::PedPoolCurr++;
				}
			}
			for (int i = 0; i < m_Replay_Interface->m_vehicle_interface->m_max_vehicles; i++) {
				rage::CVehicle* Vehicles = m_Replay_Interface->m_vehicle_interface->get_vehicle(i);
				if (Vehicles)
				{
					Features::VehPoolCurr++;
				}
			}
		}
	}

	std::string ObjPool = std::to_string(Features::ObjPoolCurr) + "/" + std::to_string(maxObjects);
	std::string VehPool = std::to_string(Features::VehPoolCurr) + "/" + std::to_string(maxVehicles);
	std::string PedPool = std::to_string(Features::PedPoolCurr) + "/" + std::to_string(maxPeds);

	//Menu::Drawing::Texthehe
	// DRAW IT HERE

	char buffer[255];
	sprintf_s(buffer, "~w~Object Pool: ~c~%s", ObjPool);//object pools show
	PrintddddText(buffer, 4, 0.197f, 0.698f + (1 * 0.0247), 0.37f, 0.37f, 255, 255, 255, 255, 0, 1);

	sprintf_s(buffer, "~w~Vehicle Pool: ~c~%s", VehPool);//VehPool pools show
	PrintddddText(buffer, 4, 0.198f, 0.695f + (2 * 0.0247), 0.37f, 0.37f, 255, 255, 255, 255, 0, 1);

	sprintf_s(buffer, "~w~Ped Pool: ~c~%s", PedPool);//PedPool pools show
	PrintddddText(buffer, 4, 0.198f, 0.694f + (3 * 0.0247), 0.37f, 0.37f, 255, 255, 255, 255, 0, 1);

	Features::VehPoolCurr = 0;//0,
	Features::PedPoolCurr = 0;//0
	Features::ObjPoolCurr = 0;//0
}
void Hooking::FindPatterns()
{
	CLog::initialize("Nano Menu", "Hooking.log");

	char* ptr;

	setPat<rage::CReplayInterface>("replay interface", "\x48\x8D\x0D\x00\x00\x00\x00\x48\x8B\xD7\xE8\x00\x00\x00\x00\x48\x8D\x0D\x00\x00\x00\x00\x8A\xD8\xE8\x00\x00\x00\x00\x84\xDB\x75\x13\x48\x8D\x0D",
		"xxx????xxxx????xxx????xxx????xxxxxxx", &m_Replay_Interface, true, 3, 1);
	setFn<fpIsDLCPresent>("is_DLC_present",
		"\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x81\xF9\x00\x00\x00\x00",
		"xxxx?xxxxxxx???",
		&Hooking::is_DLC_present);
	CLog::Msg("Get Frame Count...");
	if (nullptr == (ptr = ptrScan("8B 15 ? ? ? ? 41 FF CF")))
		Error("Error in finding frame_count");
	Hooking::m_frameCount = rel<uint64_t*>(ptr, 2);

	CLog::Msg("Getting vector3 result fixer func...");
	if (nullptr == (scrNativeCallContext::SetVectorResults = ptrScan<void(*)(scrNativeCallContext*)>("83 79 18 00 48 8B D1 74 4A FF 4A 18")))
		Error("Error in finding SetVectorResults");

	CLog::Msg("Getting World Pointer...");
	if (nullptr == (ptr = ptrScan("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07")))
		Error("Error in finding the World Pointer");
	m_worldPtr = rel<uint64_t>(ptr);

	CLog::Msg("Getting Blip List...");
	if (nullptr == (ptr = ptrScan("4C 8D 05 ? ? ? ? 0F B7 C1")))
		Error("Error in finding the Bliplist");
	m_blipList = rel<BlipList*>(ptr);

	/*CLog::Msg("Getting active script thread...");
	if (nullptr == (ptr = ptrScan("E8 ? ? ? ? 48 8B 88 10 01 00 00")))
		Error("Error in finding the Active Script Thread");
	GetActiveThread = rel<ScriptThread* (*)()>(ptr, 1);*/

	CLog::Msg("Getting Player List Pointer...");
	if (nullptr == (ptr = ptrScan("48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 48 8B CF")))
		Error("Error in finding the Player List Function");
	m_player_list = *rel<uint64_t*>(ptr);

	CLog::Msg("Getting Global Pointer...");
	if (nullptr == (ptr = ptrScan("4C 8D 05 ? ? ? ? 4D 8B 08 4D 85 C9 74 11")))
		Error("Error in finding the Global Pointer");
	m_globalPtr = rel<uint64_t**>(ptr);//

	CLog::Msg("Getting Event Hooks...");
	if (nullptr == (ptr = ptrScan("48 83 EC 28 E8 ? ? ? ? 48 8B 0D ? ? ? ? 4C 8D 0D ? ? ? ? 4C 8D 05 ? ? ? ? BA 03")))
		Error("Error in getting the Event Hooks");
	for (int i = 0; i != EVENT_COUNT; ptr++, i++)
		EventPtr.push_back(rel(ptrScan("4C 8D 05", reinterpret_cast<uintptr_t>(ptr))));

	CLog::Msg("Initializing natives...");
	if (nullptr == (ptr = ptrScan("48 8D 0D ? ? ? ? 48 8B 14 FA")))
		Error("Error in Finding the Native Map");
	m_nativeTable = rel(ptr);
	provideNative = *rel<Hooking::NativeHandler(*)(void*, uint64_t)>(ptr, 12);
	CrossMapping::initNativeMap();

	CLog::Msg("GTA V ready!");
}

uint64_t Hooking::getWorldPtr()
{
	return m_worldPtr;
}

void WAIT(DWORD ms)
{
	wakeAt = timeGetTime() + ms;
	SwitchToFiber(mainFiber);
}

void Hooking::Cleanup()
{
	iHook.keyboardHandlerUnregister(OnKeyboardMessage);
	DisableTLSContext();
	iHook.Remove();
	bool b = (MH_DisableHook(&ResetWriteWatch) != MH_OK && MH_RemoveHook(&ResetWriteWatch) != MH_OK);

	for (int i = 0; i < m_hookedNative.size(); i++)
		b = (MH_DisableHook(m_hookedNative[i]) != MH_OK && MH_RemoveHook(m_hookedNative[i]) != MH_OK);
	MH_Uninitialize();
	FreeLibraryAndExitThread(static_cast<HMODULE>(_hmoduleDLL), 1);
}

void Hooking::defuseEvent(RockstarEvent e, bool toggle)
{
	static const unsigned char retn = 0xC3;
	char* p = reinterpret_cast<char*>(EventPtr[e]);
	if (toggle)
	{
		if (EventRestore[e] == 0)
			EventRestore[e] = p[0];
		*p = retn;
	}
	else
	{
		if (EventRestore[e] != 0)
			*p = EventRestore[e];
	}
}

uint64_t** Hooking::getGlobalPtr()
{
	return m_globalPtr;
}
// META DATA

uint64_t CMetaData::m_begin = 0;
uint64_t CMetaData::m_end = 0;
DWORD CMetaData::m_size = 0;

uint64_t CMetaData::begin()
{
	return m_begin;
}
uint64_t CMetaData::end()
{
	return m_end;
}
DWORD CMetaData::size()
{
	return m_size;
}

void CMetaData::init()
{
	if (m_begin && m_size)
		return;

	m_begin = (uint64_t)GetModuleHandleA(nullptr);
	const IMAGE_DOS_HEADER* headerDos = (const IMAGE_DOS_HEADER*)m_begin;
	const IMAGE_NT_HEADERS* headerNt = (const IMAGE_NT_HEADERS64*)((const BYTE*)headerDos + headerDos->e_lfanew);
	m_size = headerNt->OptionalHeader.SizeOfCode;
	m_end = m_begin + m_size;
	return;
}

// CPATTERN

CPatternResult::CPatternResult(void* pVoid) :
	m_pVoid(pVoid)
{}
CPatternResult::CPatternResult(void* pVoid, void* pBegin, void* pEnd) :
	m_pVoid(pVoid),
	m_pBegin(pBegin),
	m_pEnd(pEnd)
{}
CPatternResult::~CPatternResult() {}

CPattern::CPattern(char* szByte, char* szMask) :
	m_szByte(szByte),
	m_szMask(szMask),
	m_bSet(false)
{}
CPattern::~CPattern() {}

CPattern& CPattern::find(int i, uint64_t startAddress)
{
	match(i, startAddress, false);
	if (m_result.size() <= i)
		m_result.push_back(nullptr);
	return *this;
}

CPattern& CPattern::virtual_find(int i, uint64_t startAddress)
{
	match(i, startAddress, true);
	if (m_result.size() <= i)
		m_result.push_back(nullptr);
	return *this;
}

CPatternResult	CPattern::get(int i)
{
	if (m_result.size() > i)
		return m_result[i];
	return nullptr;
}

bool	CPattern::match(int i, uint64_t startAddress, bool virt)
{
	if (m_bSet)
		return false;
	uint64_t	begin = 0;
	uint64_t	end = 0;
	if (!virt)
	{
		CMetaData::init();
		begin = CMetaData::begin() + startAddress;
		end = CMetaData::end();
		if (begin >= end)
			return false;
	}
	int		j = 0;
	do
	{
		if (virt)
			begin = virtual_find_pattern(startAddress, (BYTE*)m_szByte, m_szMask) + 1;
		else
			begin = find_pattern(begin, end, (BYTE*)m_szByte, m_szMask) + 1;
		if (begin == NULL)
			break;
		j++;
	} while (j < i);

	m_bSet = true;
	return true;
}

bool	CPattern::byte_compare(const BYTE* pData, const BYTE* btMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++btMask)
		if (*szMask == 'x' && *pData != *btMask)
			break;
	if ((*szMask) != 0)
		return false;
	return true;
}

uint64_t	CPattern::find_pattern(uint64_t address, uint64_t end, BYTE* btMask, char* szMask)
{
	size_t len = strlen(szMask) + 1;
	for (uint64_t i = 0; i < (end - address - len); i++)
	{
		BYTE* ptr = (BYTE*)(address + i);
		if (byte_compare(ptr, btMask, szMask))
		{
			m_result.push_back(CPatternResult((void*)(address + i)));
			return address + i;
		}
	}
	return NULL;
}
/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/
uint64_t	CPattern::virtual_find_pattern(uint64_t address, BYTE* btMask, char* szMask)
{
	MEMORY_BASIC_INFORMATION mbi;
	char* pStart = nullptr;
	char* pEnd = nullptr;
	char* res = nullptr;
	size_t	maskLen = strlen(szMask);

	while (res == nullptr && sizeof(mbi) == VirtualQuery(pEnd, &mbi, sizeof(mbi)))
	{
		pStart = pEnd;
		pEnd += mbi.RegionSize;
		if (mbi.Protect != PAGE_READWRITE || mbi.State != MEM_COMMIT)
			continue;

		for (int i = 0; pStart < pEnd - maskLen && res == nullptr; ++pStart)
		{
			if (byte_compare((BYTE*)pStart, btMask, szMask))
			{
				m_result.push_back(CPatternResult((void*)pStart, mbi.BaseAddress, pEnd));
				res = pStart;
			}
		}

		mbi = {};
	}
	return (uint64_t)res;
}