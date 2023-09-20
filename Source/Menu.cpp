
/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/
/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/
#pragma once
#include "stdafx.h"

bool g_Running = true;
int g_selectedPlayer;

struct onlinePlayer {
	std::string name;
	int ID;
}; onlinePlayer g_player_info;

char* CharKeyboard(char* windowName = "", int maxInput = 21, char* defaultText = "") {
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "", "", defaultText, "", "", "", maxInput);
	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return "";
	return GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
}
int NumberKeyboard() {
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(1, "", "", "", "", "", "", 10);
	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return 0;
	return atof(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
}
void notifyleft(char* msg)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(msg);
	UI::_DRAW_NOTIFICATION(2000, 1);
}

Vector3 TPCoords;
void TPto(Vector3 Coords)
{
	int Handle = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
	{
		ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(Handle, false), Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
	}
	else
		ENTITY::SET_ENTITY_COORDS(Handle, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
}

int imhere;

bool exampleBool;
int exampleInt = 0;
float exampleFloat;
/* 

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/
/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/
/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/
/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/
void main() {
	notifyMap("Hello");
	UI::Settings::currentOption = 1;
	while (true) {
		UI::DrawBackground();
		UI::Checks::Controlls();
		Features::UpdateLoop();
		switch (UI::Settings::currentMenu) {

		case sub_main:
		{
			UI::Title("Web Base *_*");
			if (UI::Option("Random Outfits", NO_INFO, ""))
			{
				PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), true);
			}
			UI::Sub("Player options", sub_player_options, INFO, "Features for local player");
			UI::Sub("Online players", sub_online_players, INFO, "Options for Network Player");
			UI::Sub("All online players", sub_all_online_players, INFO, "Options for All Network Player");
			UI::Sub("Teleport options", sub_teleport_options, INFO, "Teleport options");
			UI::Sub("Recovery service", sub_recovery_service, INFO, "Recovery service");
			UI::Sub("Vehicle options", sub_vehicle_options, INFO, "Vehicle options");
			UI::Sub("Weapon options", sub_weapon_options, INFO, "Weapon options");
			UI::Sub("World options", sub_world_options, INFO, "World options");
			UI::Sub("Protections", sub_protections, INFO, "Protections options");
			UI::Sub("Miscellaneous", Sub_Miscellaneous, INFO, "Miscellaneous options");
			UI::Sub("Settings", sub_settings, INFO, "Settings options");
		}
		break;

		case sub_player_options:
		{
			UI::Title("Player");
			UI::Option("Submenu says hello!", NO_INFO, "");
		}
		break;

		case sub_online_players:
		{
			UI::Title("Online player");
			for (int i = 0; i < 32; i++) {
				Entity playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
				if (ENTITY::DOES_ENTITY_EXIST(playerPed))
				{
					g_player_info.name = NETWORK::NETWORK_PLAYER_GET_NAME(i);
					if (UI::Sub(g_player_info.name.c_str(), sub_selected_player, NO_INFO, ""))
						g_player_info.ID = i;
				}
				else {
					std::string g_emptySlot = "Empty slot [" + std::to_string(i) + "]";
					UI::Option(g_emptySlot.c_str(), NO_INFO, "");
				}
			}
		}
		break;		

		case sub_selected_player:
		{
			UI::Title(g_player_info.name.c_str());
			UI::Option("Submenu says hello!", NO_INFO, "");
		}
		break;
		
		case sub_all_online_players:
		{
			UI::Title("Lobby");
			UI::Option("Submenu says hello!", NO_INFO, "");
		}
		break;		
		
		case Sub_Miscellaneous:
		{
			UI::Title("Miscellaneous");
			//UI::Option("Submenu says hello!", NO_INFO, "");
			UI::Toggle("Pools", Features::ShowPools, INFO, "~g~Enable Pools");
		}
		break;		
		
		case sub_teleport_options:
		{
			UI::Title("Teleport");
			UI::Option("Submenu says hello!", NO_INFO, "");
		}
		break;		
		
		case sub_recovery_service:
		{
			UI::Title("Recovery");
			UI::Option("Submenu says hello!", NO_INFO, "");
		}
		break;		
		
		case sub_vehicle_options:
		{
			UI::Title("Vehicle");
			UI::Option("Submenu says hello!", NO_INFO, "");
		}
		break;		
		
		case sub_weapon_options:
		{
			UI::Title("Weapon");
			UI::Option("Submenu says hello!", NO_INFO, "");
		}
		break;		
		
		case sub_world_options:
		{
			UI::Title("World");
			UI::Option("Submenu says hello!", NO_INFO, "");
		}
		break;		
		
		case sub_protections:
		{
			UI::Title("Protections");
			UI::Option("Submenu says hello!", NO_INFO, "");
		}
		break;
		/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/
/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/
/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/
		case sub_settings:
		{
			UI::Title("Settings");
			UI::Int("Example int", exampleInt, 0, 10, 2, INFO, "Example int info");
			if (UI::Option("Unload menu", INFO, "Unload The Menu")) {
				FreeConsole();
				g_Running = false;
			}

		
			UI::Float("Example float 1", UI::Settings::Examplefloat1, 0.0f, 1.0f, 0.001f, INFO, "Example float info");
			UI::Break("example break");
			UI::Float("Example float 2", UI::Settings::Examplefloat2, 0.0f, 1.0f, 0.001f, INFO, "Example float info");
			UI::Float("Example float 3", UI::Settings::Examplefloat3, 0.0f, 1.0f, 0.001f, INFO, "Example float info");
			UI::Float("Example float 4", UI::Settings::Examplefloat4, 0.0f, 1.0f, 0.001f, INFO, "Example float info");
			UI::Float("Example float 5", UI::Settings::Examplefloat5, 0.0f, 1.0f, 0.001f, INFO, "Example float info");
			UI::Float("Example float 6", UI::Settings::Examplefloat6, 0.0f, 1.0f, 0.001f, INFO, "Example float info");
			UI::Break("example break");
			UI::Break("example break");
			UI::Float("Example float 7", UI::Settings::Examplefloat7, 0.0f, 1.0f, 0.001f, INFO, "Example float info");
			UI::Float("Example float 8", UI::Settings::Examplefloat8, 0.0f, 1.0f, 0.001f, INFO, "Example float info");

		    UI::Toggle("Example bool", exampleBool, INFO, "Example bool info");
			if (UI::Option("MenuX plus", NO_INFO, "")) {
				if (UI::Settings::menuX < 0.81f) UI::Settings::menuX += 0.01f;
			}
			UI::Break("example break");
			if (UI::Option("MenuX minus", NO_INFO, "")) {
				if (UI::Settings::menuX > 0.17f) UI::Settings::menuX -= 0.01f;
			}
		}
		break;
		}
		UI::MonitorMenu();
		UI::End();
		UI::ControllSmooth();
		UI::InterfaceAnimations();
		WAIT(0);
	}
}
/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/

/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/
/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/
void ScriptMain() {
	srand(GetTickCount());

	main();
}