//Addresses from GTAV.exe module
#include <cstdint>
#include "types.h"
#ifdef __SC_VERSION__
#define ADDRESS_WORLD					0x2328EC8		//42
#define ADDRESS_WAYPOINT				0x1F7F400		//wtb a (mini)map struct
#define ADDRESS_OBJECTIVE				0x1F7F4B0
#define ADDRESS_AMMO					0x0F706C5		//Ammo dec code; 41 2B D1 E8; 90 90 90 E8
#define ADDRESS_MAGAZINE				0x0F70680		//Magazine dec code; 41 2B C9 3B C8 0F; 90 90 90 3B C8 0F
#endif
#ifdef __STEAM_VERSION__
#define ADDRESS_WORLD					0x232BC00
#define ADDRESS_WAYPOINT				0x1F82460
#define ADDRESS_OBJECTIVE				0x1F82510
#define ADDRESS_AMMO					0x0F71C38
#define ADDRESS_MAGAZINE				0x0F71C7D
#endif

//offset from WORLD
#define OFFSET_PLAYER					0x08			//playerbase

//entity offsets
#define OFFSET_ENTITY_POSBASE			0x30			//base of a structure that contains entity coords
#define OFFSET_ENTITY_POSBASE_POS		0x50			//vector3
#define OFFSET_ENTITY_POS				0x90			//vector3
#define OFFSET_ENTITY_HEALTH			0x280			//entity health (except for vehicles); float cur, float max
#define OFFSET_ENTITY_HEALTH_MAX		0x2A0			//they moved this away from curHealth in 1.36 :(
#define OFFSET_ENTITY_ATTACKER			0x2A8			//base to a list of the last 3 entities that attacked the current entity
#define OFFSET_ENTITY_GOD				0x189			//godmode; on = 1, off = 0; byte

//player (entity) offsets
#define OFFSET_PLAYER_ARMOR						0x14B0			//armour
#define OFFSET_PLAYER_INFO						0x10C8			//playerInfo struct
#define OFFSET_PLAYER_INFO_WANTED_CAN_CHANGE	0x71C			//fWantedCanChange
#define OFFSET_PLAYER_INFO_WANTED				0x798			//wanted level; DWORD
#define	OFFSET_PLAYER_INFO_RUN_SPD				0xE8			//run speed; def 1; float
#define OFFSET_PLAYER_INFO_SWIM_SPD				0xE4			//swim speed; def 1; float
#define OFFSET_PLAYER_INFO_FRAMEFLAGS			0x190			//frame flags; DWORD
#define OFFSET_PLAYER_INFO_STAMINA				0xC00			//fStamina, fStaminaMax
#define OFFSET_PLAYER_VEHICLE					0xD30			//ptr to last used vehicle //old 0xD28 >> // new 0xD30
#define OFFSET_PLAYER_NAME						0x84
#define OFFSET_PLAYER_RAGDOLL					0x10A8			//byte; CPed.noRagdoll: 0x20 = off; 0x00/0x01 = on
#define OFFSET_PLAYER_SEATBELT					0x13EC			//byte; CPed.seatBelt: 0xC8 = off; 0xC9 = on
#define OFFSET_PLAYER_INVEHICLE					0x146B

//vehicle offsets
#define OFFSET_VEHICLE_HEALTH						0x84C			//vehicle health; 0.f-1000.f
#define OFFSET_VEHICLE_GRAVITY						0xB7C			//fGravity
#define OFFSET_VEHICLE_BULLETPROOF_TIRES			0x883			//btBulletproofTires;  (btBulletproofTires & 0x20) ? true : false
#define OFFSET_VEHICLE_HANDLING						0x878
#define OFFSET_VEHICLE_HANDLING_ACCELERATION		0x4C
#define OFFSET_VEHICLE_HANDLING_BRAKEFORCE			0x6C
#define OFFSET_VEHICLE_HANDLING_TRACTION_CURVE_MIN	0x90			//fTractionCurveMin
#define OFFSET_VEHICLE_HANDLING_DEFORM_MULTIPLIER	0xF8			//fDeformationDamageMult
#define OFFSET_VEHICLE_HANDLING_UPSHIFT				0x58
#define OFFSET_VEHICLE_HANDLING_SUSPENSION_FORCE	0xBC			//fSuspensionForce 

//weapon offsets
#define OFFSET_WEAPON_MANAGER			0x10C8			//from playerbase
#define OFFSET_WEAPON_CURRENT			0x20			//from weapon manager
#define OFFSET_WEAPON_AMMOINFO			0x48			//from weaponbase
#define OFFSET_WEAPON_AMMOINFO_MAX		0x28			//ammoinfo
#define OFFSET_WEAPON_AMMOINFO_CUR_1	0x08			//ptr lvl 1, ptr 1
#define OFFSET_WEAPON_AMMOINFO_CUR_2	0x00			//ptr tr lvl 2, ptr 1
#define OFFSET_WEAPON_AMMOINFO_CURAMMO	0x18			//offset to cur ammo
#define OFFSET_WEAPON_AMMOINFO_TYPE		0x0C			//offset to projectile type?
#define OFFSET_WEAPON_SPREAD			0x5C			//float set to 0
#define OFFSET_WEAPON_BULLET_DMG		0x98			//float times 10 (so when 0, it will stay 0)
#define OFFSET_WEAPON_RELOAD_MULTIPLIER	0x114			//float times 10
#define OFFSET_WEAPON_RECOIL			0x2A4			//float set to 0
#define OFFSET_WEAPON_MODEL_HASH		0x14
#define OFFSET_WEAPON_NAME_HASH			0x10
#define OFFSET_WEAPON_RELOAD_VEHICLE	0x110
#define OFFSET_WEAPON_RANGE				0x25C
#define OFFSET_WEAPON_SPINUP			0x124
#define OFFSET_WEAPON_SPIN				0x128
#define OFFSET_WEAPON_BULLET_BATCH		0x100			//dwBulletInBatch
#define OFFSET_WEAPON_MUZZLE_VELOCITY	0xFC			//fMuzzleVelocity
#define OFFSET_WEAPON_BATCH_SPREAD		0x104			//fBatchSpread


#define OFFSET_ATTACKER_DISTANCE		0x18			//changed to 0x18, from 0x10

namespace rage
{
	class fwEntity
	{
	public:
		char pad_0000[32]; //0x0000
		class CBaseModelInfo* m_model_info; //0x0020
		int8_t m_invisible; //0x0028
		char pad_0029[7]; //0x0029
		class CNavigation* m_navigation; //0x0030
		char pad_0038[1]; //0x0038
		int8_t m_entity_type; //0x0039
		char pad_003A[150]; //0x003A
		class netObject* m_net_object; //0x00D0
		char pad_00D8[176]; //0x00D8
		uint32_t m_damage_bits; //0x0188

		bool is_invincible() { return(m_damage_bits & (1 << 8)); }
		void enable_invincible() { m_damage_bits |= (1 << 8); }
		void disable_invincible() { m_damage_bits &= ~(1 << 8); }
	};; //Size: 0x018C
	//static_assert(sizeof(fwEntity) == 0x18C, "fwEntity is not properly sized.");

	class CVehicle : public fwEntity
	{
	public:
		char pad_018C[2716]; //0x018C
							 //class CPed* m_driver; //0x0C28
							 //class CPed* m_occupants[8]; //0x0C30
	}; //Size: 0x018C

	class CNavigation
	{
	public:
		char pad_0000[32]; //0x0000
		float m_heading; //0x0020
		float m_heading2; //0x0024
		char pad_0028[8]; //0x0028
		Vector3 m_rotation; //0x0030
		char pad_003C[20]; //0x003C
		Vector3 m_position; //0x0050
	}; //Size: 0x005C

	//class CPed : public fwEntity
	//{
	//public:
	//	char pad_018C[2972]; //0x018C
	//	class CVehicle* m_last_vehicle; //0x0D28
	//	char pad_0D30[908]; //0x0D30
	//	int8_t m_decal_index; //0x10BC
	//	int8_t m_decal_info; //0x10BD
	//	char pad_10BE[10]; //0x10BE
	//	class CPlayerInfo* m_player_info; //0x10C8
	//};
	class CPed : public rage::fwEntity
	{
	public:
		uint8_t m_hostility; //0x018C
		char pad_018D[243]; //0x018D
		float m_health; //0x0280
		float m_maxhealth; //0x0284
		char pad_0288[152]; //0x0288
		//rage::fvector3 m_velocity; //0x0320
		char pad_032C[2532]; //0x032C
		class CAutomobile* m_vehicle; //0x0D10
		char pad_0D18[912]; //0x0D18
		class CPlayerInfo* m_player_info; //0x10A8
		char pad_10B0[8]; //0x10B0
		class CPedWeaponManager* m_weapon_manager; //0x10B8
		char pad_10C0[939]; //0x10C0
		uint8_t m_ped_task_flag; //0x146B
		char pad_146C[160]; //0x146C
		float m_armor; //0x150C
	}; //Size: 0x1510
//	static_assert(sizeof(CPed) == 0x1510, "");

	class CPlayerInfo
	{
	public:
		char pad_0000[52]; //0x0000
		uint32_t m_internal_ip; //0x0034
		uint16_t m_internal_port; //0x0038
		char pad_003A[2]; //0x003A
		uint32_t m_relay_ip; //0x003C
		uint16_t m_relay_port; //0x0040
		char pad_0042[2]; //0x0042
		uint32_t m_external_ip; //0x0044
		uint16_t m_external_port; //0x0048
		char pad_004A[30]; //0x004A
		uint64_t m_rockstar_id; //0x0068
		char pad_0070[12]; //0x0070
		char m_name[20]; //0x007C
		char pad_0090[184]; //0x0090
		float m_swim_speed; //0x0148
		float m_run_speed; //0x014C
		char pad_0150[81]; //0x0150
		bool m_is_rockstar_dev; //0x01A1
		char pad_01A2[1]; //0x01A2
		bool m_is_cheater; //0x01A3
		char pad_01A4[11]; //0x01A4
		bool m_is_online; //0x01AF
		char pad_01B0[24]; //0x01B0
		class CPed* m_ped; //0x01C8
		char pad_01D0[40]; //0x01D0
		uint32_t m_frame_flags; //0x01F8
		char pad_01FC[28]; //0x01FC
		uint32_t m_player_controls; //0x0218
		char pad_021C[1524]; //0x021C
		bool m_is_wanted; //0x0810
		char pad_0811[3]; //0x0811
		int32_t m_wanted_level_display; //0x0814
		int32_t m_wanted_level; //0x0818
	}; //Size: 0x081C

	class CObject : public fwEntity
	{
	public:
	}; //Size: 0x018C

	class CBaseModelInfo
	{
	public:
		char pad_0000[24]; //0x0000
		uint32_t m_model; //0x0018
	}; //Size: 0x001C

	class CPedFactory
	{
	public:
		virtual ~CPedFactory() = default;
		class CPed* m_local_ped; //0x0008
	}; //Size: 0x0010

	class CObjectHandle
	{
	public:
		class CObject* m_object; //0x0000
		int32_t m_handle; //0x0008
		char pad_000C[4]; //0x000C
	}; //Size: 0x0010
	static_assert(sizeof(CObjectHandle) == 0x10, "CObjectHandle is not properly sized");

	class CObjectList
	{
	public:
		class CObjectHandle m_objects[2300]; //0x0000
	}; //Size: 0x8FC0

	class CObjectInterface
	{
	public:
		char pad_0000[344]; //0x0000
		class CObjectList* m_object_list; //0x0158
		int32_t m_max_objects; //0x0160
		char pad_0164[4]; //0x0164
		int32_t m_cur_objects; //0x0168

		rage::CObject* get_object(const int& index)
		{
			if (index < m_max_objects)
				return m_object_list->m_objects[index].m_object;
			return nullptr;
		}
	}; //Size: 0x016C

	class CPedHandle
	{
	public:
		class CPed* m_ped; //0x0000
		int32_t m_handle; //0x0008
		char pad_000C[4]; //0x000C
	}; //Size: 0x0010
	static_assert(sizeof(CPedHandle) == 0x10, "CPedHandle is not properly sized");

	class CPedList
	{
	public:
		class CPedHandle m_peds[256]; //0x0000
	}; //Size: 0x1000

	class CPedInterface
	{
	public:
		char pad_0000[256]; //0x0000
		class CPedList* m_ped_list; //0x0100
		int32_t m_max_peds; //0x0108
		char pad_010C[4]; //0x010C
		int32_t m_cur_peds; //0x0110

		CPed* get_ped(const int& index)
		{
			if (index < m_max_peds)
				return m_ped_list->m_peds[index].m_ped;
			return nullptr;
		}
	}; //Size: 0x0114

	class CVehicleHandle
	{
	public:
		class CVehicle* m_vehicle; //0x0000
		int32_t m_handle; //0x0008
		char pad_000C[4]; //0x000C
	}; //Size: 0x0010
	static_assert(sizeof(CVehicleHandle) == 0x10, "CVehicleHandle is not properly sized");

	class CVehicleList
	{
	public:
		class CVehicleHandle m_vehicles[300]; //0x0000
	}; //Size: 0x12C0

	class CVehicleInterface
	{
	public:
		char pad_0000[384]; //0x0000
		class CVehicleList* m_vehicle_list; //0x0180
		int32_t m_max_vehicles; //0x0188
		char pad_018C[4]; //0x018C
		int32_t m_cur_vehicles; //0x0190

		CVehicle* get_vehicle(const int& index)
		{
			if (index < m_max_vehicles)
				return m_vehicle_list->m_vehicles[index].m_vehicle;
			return nullptr;
		}
	}; //Size: 0x0194


	class CReplayInterface
	{
	public:
		char pad_0000[16]; //0x0000
		class CVehicleInterface* m_vehicle_interface; //0x0010
		class CPedInterface* m_ped_interface; //0x0018
		char pad_0020[8]; //0x0020
		class CObjectInterface* m_object_interface; //0x0028
	}; //Size: 0x0030
}