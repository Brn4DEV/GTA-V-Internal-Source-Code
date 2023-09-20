#include "stdafx.h"
#include "pattern.h"

//class GtaThread : public rage::scrThread
//{
//public:
//	uint32_t m_script_hash;
//	char m_padding01[0x34];
//};
class GtaThread : public rage::scrThread
{
public:
	uint32_t m_script_hash;                // 0x120
	char m_padding3[0x14];                      // 0x124
	std::int32_t m_instance_id;                 // 0x138
	char m_padding4[0x04];                      // 0x13C
	std::uint8_t m_flag1;                       // 0x140
	bool m_safe_for_network_game;               // 0x141
	char m_padding5[0x02];                      // 0x142
	bool m_is_minigame_script;                  // 0x144
	char m_padding6[0x02];                      // 0x145
	bool m_can_be_paused;                       // 0x147
	bool m_can_remove_blips_from_other_scripts; // 0x148
	char m_padding7[0x0F];                      // 0x149
};

//static_assert(sizeof(GtaThread) == 0x160, "ss");

auto set_active_thread = [](GtaThread* thread) -> GtaThread*
{
	char* tls = *(char**)__readgsqword(0x58);
	GtaThread* og_thread = *(GtaThread**)(tls + 0x830);

	*(GtaThread**)(tls + 0x830) = thread;
	*(char*)(tls + 0x838) = thread != nullptr;

	return og_thread;
};


static_assert(sizeof(GtaThread) == 0x158);

typedef uint32_t(*scrThreadTick)(GtaThread* _this, uint32_t ops_to_execute);
scrThreadTick og_tick;

uint32_t hook_tick(GtaThread* _this, uint32_t ops_to_execute)
{
	if (_this->m_script_hash == 0x5700179C)
	{
		char* tls = *(char**)__readgsqword(0x58);

		GtaThread* og_thread = *(GtaThread**)(tls + 0x830);
		*(GtaThread**)(tls + 0x830) = _this;
		*(char*)(tls + 0x838) = _this != nullptr;

		Hooking::onTickInit(); //EXECUTE MAIN THREAD

		*(GtaThread**)(tls + 0x830) = og_thread;
		*(char*)(tls + 0x838) = og_thread != nullptr;
	}

	/*
	switch (_this->m_script_hash)
	{

	case 0x5f1459d7: // script hash
	{
		if (testBool)
			break;
		auto og_thread = set_active_thread(_this);
		 
		 //do anything inside of script

		set_active_thread(og_thread);
		break;
	}
	}*/


	return og_tick(_this, ops_to_execute);
}

PVOID gtaThreadTick{};

void EnableTLSContext()
{
	gtaThreadTick = Signature("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 80 B9 ? ? ? ? ? 8B FA 48 8B D9 74 05").Scan().As<PVOID>();

	if (gtaThreadTick != nullptr && MH_CreateHook(gtaThreadTick, &hook_tick, (void**)&og_tick) == MH_OK)
		MH_EnableHook(gtaThreadTick);
	CLog::Hook("TLS -> OK");
}

void DisableTLSContext()
{
	MH_DisableHook(gtaThreadTick);
}

