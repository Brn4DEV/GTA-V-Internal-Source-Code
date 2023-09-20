#pragma once

enum SubMenus { //Add Sub Menus in here
	sub_main,
	sub_player_options,
	sub_online_players,
	sub_all_online_players,
	Sub_Miscellaneous,
	sub_teleport_options,
	sub_recovery_service,
	sub_vehicle_options,
	sub_weapon_options,
	sub_world_options,
	sub_protections,
	sub_settings,
	sub_selected_player,
};
extern enum SubMenus;

typedef struct VECTOR2 {
	float x, y;
};
typedef struct VECTOR2_2 {
	float w, h;
};
typedef struct RGBAF {
	int r, g, b, a, f;
};
typedef struct RGBA {
	int r, g, b, a;
};
typedef struct RGB {
	int r, g, b;
};
namespace UI {
	namespace Drawing {
		void Text(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
		void Title(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
		void Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size);
		void Text_Right(char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool left);
		void Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
	}
	namespace Settings {
		extern bool selectPressed;
		extern bool leftPressed;
		extern bool rightPressed;
		extern bool center;
		extern bool controllerinput;

		extern int maxVisOptions;
		extern int currentOption;
		extern int optionCount;

		extern SubMenus currentMenu;
		extern int menuLevel;
		extern int optionsArray[1000];
		extern SubMenus menusArray[1000];

		extern float menuX;
		extern float fontScale;
		extern float fontYPos;
		extern float subMenuArrowX;
		extern float scrollBar_Pos;
		extern float Scroller_changeY;
		extern float Scroller_destinationY;
		extern float Examplefloat1;
		extern float Examplefloat2;
		extern float Examplefloat3;
		extern float Examplefloat4;
		extern float Examplefloat5;
		extern float Examplefloat6;
		extern float Examplefloat7;
		extern float Examplefloat8;
		extern float Examplefloat9;
		extern float NewScrollerbarTOPx;
		extern float NewScrollerbarTOPy;
		extern float NewScrollerEndBar;
		extern float NewScrollerMidBARX;
		extern float NewScrollerMidBARY;
		extern RGBAF count;
		extern RGBAF titleText;
		extern RGBA titleRect;
		extern RGBAF breakText;
		extern RGBAF optionText;
		extern RGBA selectedText;
		extern RGBAF arrow;
		extern RGBA caixasetinhascroll;
		extern RGBAF arrow2;
		extern float ScrollerWidth;
		extern bool displayEnd;
		extern RGBAF integre;
		extern RGBA optionRect;
		extern RGBA optionRect22;
		extern RGBA scroller;
		extern RGBA scrollerCOLOR;
		extern RGBA line;
		extern RGBA primary;
		extern RGBA secondary;

		extern int keyPressDelay;
		extern int keyPressPreviousTick;
		extern int keyPressDelay2;
		extern int keyPressPreviousTick2;
		extern int keyPressDelay3;
		extern int keyPressPreviousTick3;
		extern int openKey;
		extern int backKey;
		extern int upKey;
		extern int downKey;
		extern int leftKey;
		extern int rightKey;
		extern int selectKey;
		extern int arrowupKey;
		extern int arrowdownKey;
		extern int arrowleftKey;
		extern int arrowrightKey;
		extern int enterKey;
		extern int deleteKey;
		extern int openpress;
		extern int downpress;
		extern int uppress;
		extern int backpress;
		extern int click;
		extern int leftpress;
		extern int rightpress;


	}
	namespace MenuLevelHandler {
		void MoveMenu(SubMenus menu);
		void BackMenu();
	}
	namespace Checks {
		void Controlls();
	}
	namespace Tools {
		char* StringToChar(std::string string);
	}
	namespace Files {
		void WriteStringToIni(std::string string, std::string file, std::string app, std::string key);
		std::string ReadStringFromIni(std::string file, std::string app, std::string key);
		void WriteIntToIni(int intValue, std::string file, std::string app, std::string key);
		int ReadIntFromIni(std::string file, std::string app, std::string key);
		void WriteFloatToIni(float floatValue, std::string file, std::string app, std::string key);
		float ReadFloatFromIni(std::string file, std::string app, std::string key);
		void WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key);
		bool ReadBoolFromIni(std::string file, std::string app, std::string key);
	}
	void ControllSmooth();
	void DrawBackground();
	void InterfaceAnimations();
	void Title(const char* title);
	bool Option(const char* option, bool info, const char* textInfo);
	bool Break(std::string option);
	bool Sub(const char* option, SubMenus newSub, bool info, const char* textInfo);
	bool Toggle(const char* option, bool& b00l, bool info, const char* textInfo);
	bool Toggle(const char* option, bool& b00l, std::function<void()> function, bool info, const char* textInfo);
	bool Int(const char* option, int& _int, int min, int max, int step, bool info, const char* textInfo);
	bool Float(const char* option, float& _float, int min, int max, float step, bool info, const char* textInfo);
	void End();//
	void MonitorMenu();
}
