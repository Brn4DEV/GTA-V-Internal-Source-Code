#include "stdafx.h"

int g_GlobalAlpha = 0;
bool g_OpenMenu;
int g_PressedKey;

/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/
void UI::Drawing::Text(const char * text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center)
{
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
	UI::SET_TEXT_FONT(rgbaf.f);
	UI::SET_TEXT_SCALE(size.w, size.h);
	//UI::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(1, 0, 0, 0, 0);
	//UI::SET_TEXT_OUTLINE();
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y);
}

void UI::Drawing::Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
	}
	else
	{
		GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a);
	}
}

void UI::Drawing::Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size)
{
	GRAPHICS::DRAW_RECT(position.x, position.y, size.w, size.h, rgba.r, rgba.g, rgba.b, rgba.a);
}

void UI::Drawing::Text_Right(char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool left)
{
	char opt[1000];
	UI::SET_TEXT_RIGHT_JUSTIFY(true);
	UI::SET_TEXT_WRAP(0, Settings::menuX + 0.098f);
	UI::SET_TEXT_FONT(rgbaf.f);
	UI::SET_TEXT_SCALE(size.w, size.h);
	if (Settings::currentOption == Settings::optionCount)
	{
		snprintf(opt, sizeof(opt), "%s", text);
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	}
	else
	{
		UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, g_GlobalAlpha);
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	}
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y);
}

float UI::Settings::NewScrollerbarTOPx = 0.114f;
float UI::Settings::NewScrollerbarTOPy = 0.146f;

float UI::Settings::NewScrollerEndBar = 0.132f;

float UI::Settings::NewScrollerMidBARX = 0.114f;
float UI::Settings::NewScrollerMidBARY = 0.139f;


bool UI::Settings::displayEnd = true;
float UI::Settings::ScrollerWidth = 0.011f;
RGBAF UI::Settings::arrow2{ 255, 255, 255, 255, 3 };
RGBAF UI::Settings::arrow{ 0, 0, 0, 255 };
RGBA UI::Settings::caixasetinhascroll{0, 0, 0, 220};

float UI::Settings::menuX = 0.17f;
bool UI::Settings::selectPressed = false;
bool UI::Settings::leftPressed = false;
bool UI::Settings::rightPressed = false;
bool firstopen = true;
int UI::Settings::maxVisOptions = 11;
int UI::Settings::currentOption = 0;
int UI::Settings::optionCount = 0;
SubMenus UI::Settings::currentMenu;
int UI::Settings::menuLevel = 0;
int UI::Settings::optionsArray[1000];
SubMenus UI::Settings::menusArray[1000];

RGBAF UI::Settings::titleText{ 255, 255, 255, 255, 7 };
RGBA UI::Settings::titleRect{ 35, 35, 35, 0 };
RGBAF UI::Settings::optionText{ 255, 255, 255, g_GlobalAlpha, 0 };
RGBAF UI::Settings::breakText{ 255, 255, 255, 0, 0 };
RGBA UI::Settings::optionRect{ 35, 35, 35, 0 };
RGBA UI::Settings::optionRect22{ 35, 35, 35, 255 };
RGBA UI::Settings::scroller{ 25, 25, 25, 0 };

RGBA UI::Settings::scrollerCOLOR{ 35, 35, 35, 0 };

float UI::Settings::fontScale = 0.25f;
float UI::Settings::fontYPos = 0.131f;
float UI::Settings::subMenuArrowX = 0.094f;



float getMovementPerTime(float startY, float endY, int timeTicks)
{
	float difY = endY - startY;
	return (float)(difY / timeTicks);
}
#define GTA_SCROLLOP 13
#define GTA_BETOP 0
#define GTA_MAXOP 13

float Maths_ABS(float value)
{
	if (value < 0)
		return value * -1;
	else
		return value;
}
float UI::Settings::scrollBar_Pos, UI::Settings::Scroller_changeY = 0, UI::Settings::Scroller_destinationY = 0;
void UI::ControllSmooth()
{
	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
	{
		UI::Settings::Scroller_destinationY = ((float)Settings::currentOption) * 0.036f + 0.16f;
		UI::Settings::Scroller_changeY = getMovementPerTime(UI::Settings::scrollBar_Pos, UI::Settings::Scroller_destinationY, 2);
		if (UI::Settings::Scroller_changeY != 0)
		{
			if (Maths_ABS(UI::Settings::scrollBar_Pos - UI::Settings::Scroller_destinationY) <= UI::Settings::Scroller_changeY + 0.00010)
			{
				UI::Settings::scrollBar_Pos = UI::Settings::Scroller_destinationY;
				UI::Settings::Scroller_changeY = 0;
			}
			else
				UI::Settings::scrollBar_Pos += UI::Settings::Scroller_changeY;

		}
	}
	else if (Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions) && Settings::optionCount <= Settings::currentOption)
		UI::Settings::scrollBar_Pos = (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.036f + 0.16f;
}

float Scroller_changeY = 0, Scroller_destinationY = 0, scrollBar_Pos2;
float scrollBar_Pos, Scroller_changeY2 = 0, Scroller_destinationY2 = 0, scrollBar_Pos22;
float Background_Pos, Background_changeY = 0, Background_destinationY = 0;
float Background_Height, Background_Height_changeY = 0, Background_Height_destinationY = 0;
float Footer_Pos, Footer_changeY = 0, Footer_destinationY = 0, Footer_destinationY2 = 0, Footer_changeY2 = 0, Footer_Pos2 = 0, Footer_destinationY3 = 0, Footer_changeY3 = 0, Footer_Pos3 = 0;
int totalop = 0;
void UI::InterfaceAnimations()
{
	int maxOptions = Settings::maxVisOptions;
	int optionCount = Settings::optionCount;
	int currentOption = Settings::currentOption;
	if (optionCount > maxOptions)
	{
		Background_Pos = ((maxOptions * 0.035f) / 2.0f) + 0.159f; //((maxOptions * 0.035f) / 2.0f) + 0.177f;
		Background_Height = (maxOptions * 0.035f);
		Footer_Pos = (Settings::maxVisOptions + 1) * 0.035f + 0.1375f;
	}
	else
	{
		/* BACKGROUND ANIMATION */
		Background_destinationY = (((float)optionCount * 0.035f) / 2.0f) + 0.159f; //((maxOptions * Features::BackgroudJump) / 2.0f) + Features::BackgroudPosY;
		Background_changeY = getMovementPerTime(Background_Pos, Background_destinationY, 2);
		if (Background_changeY != 0)
		{
			if (abs(Background_Pos - Background_destinationY) <= Background_changeY + 0.00010)
			{
				Background_Pos = Background_destinationY;
				Background_changeY = 0;
			}
			else
			{
				Background_Pos += Background_changeY;
			}
		}
		Background_Height_destinationY = ((float)optionCount * 0.035f);
		Background_Height_changeY = getMovementPerTime(Background_Height, Background_Height_destinationY, 2);
		if (Background_Height_changeY != 0)
		{
			if (abs(Background_Height - Background_Height_destinationY) <= Background_Height_changeY + 0.00010)
			{
				Background_Height = Background_Height_destinationY;
				Background_Height_changeY = 0;
			}
			else
			{
				Background_Height += Background_Height_changeY;
			}
		}
		/* FOOTER ANIMATION */

		Footer_destinationY = ((Settings::optionCount + 1) * 0.035f + 0.1375f);
		Footer_changeY = getMovementPerTime(Footer_Pos, Footer_destinationY, 2);
		if (Footer_changeY != 0)
		{
			if (abs(Footer_Pos - Footer_destinationY) <= Footer_changeY + 0.00010)
			{
				Footer_Pos = Footer_destinationY;
				Footer_changeY = 0;
			}
			else
			{
				Footer_Pos += Footer_changeY;
			}
		}

		Footer_destinationY2 = ((Settings::optionCount + 1) * 0.035f + 0.138f);
		Footer_changeY2 = getMovementPerTime(Footer_Pos2, Footer_destinationY2, 2);
		if (Footer_changeY2 != 0)
		{
			if (abs(Footer_Pos2 - Footer_destinationY2) <= Footer_changeY2 + 0.00010)
			{
				Footer_Pos2 = Footer_destinationY2;
				Footer_changeY2 = 0;
			}
			else
			{
				Footer_Pos2 += Footer_changeY2;
			}
		}

		Footer_destinationY3 = ((Settings::optionCount + 1) * 0.035f + 0.130f);
		Footer_changeY3 = getMovementPerTime(Footer_Pos3, Footer_destinationY3, 2);
		if (Footer_changeY3 != 0)
		{
			if (abs(Footer_Pos3 - Footer_destinationY3) <= Footer_changeY3 + 0.00010)
			{
				Footer_Pos3 = Footer_destinationY3;
				Footer_changeY3 = 0;
			}
			else
			{
				Footer_Pos3 += Footer_changeY3;
			}
		}
	}

	float Y_coord;

	if (currentOption > GTA_SCROLLOP && totalop > GTA_MAXOP)
	{
		Y_coord = GTA_SCROLLOP;
		if (currentOption > totalop - GTA_BETOP)
		{
			Y_coord = GTA_SCROLLOP + currentOption - totalop + GTA_BETOP;
		}
	}
	else
	{
		Y_coord = currentOption;
	}
	Y_coord = ((Y_coord) * 0.036f) + 0.16f;

	/* SCROLL BAR ANIMATION */
	if (Settings::currentOption <= Settings::maxVisOptions || Settings::optionCount <= Settings::maxVisOptions)
	{
		Scroller_destinationY = ((float)Settings::currentOption) * 0.035f + 0.1415f;
		Scroller_changeY = getMovementPerTime(scrollBar_Pos2, Scroller_destinationY, 2);
		if (Scroller_changeY != 0)
		{
			if (abs(scrollBar_Pos2 - Scroller_destinationY) <= Scroller_changeY + 0.00010)
			{
				scrollBar_Pos2 = Scroller_destinationY;
				Scroller_changeY = 0;
			}
			else
			{
				scrollBar_Pos2 += Scroller_changeY;
			}
		}
	}
	else if (Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions) && Settings::optionCount <= Settings::currentOption)
	{
		scrollBar_Pos2 = (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.1415f;
	}
}

void UI::DrawBackground() {
	Drawing::Rect(Settings::optionRect, { Settings::menuX, Background_Pos }, { 0.21f, Background_Height });
	Drawing::Rect(Settings::scroller, { Settings::menuX, scrollBar_Pos2 }, { 0.21f, 0.035f });
}


void UI::Title(const char * title)
{
	Drawing::Text(title, Settings::titleText, { Settings::menuX, 0.095f }, { 0.85f, 0.85f }, true);
	Drawing::Rect(Settings::titleRect, { Settings::menuX, 0.1175f }, { 0.21f, 0.085f });
	//Addon to scrollbar
	Drawing::Rect(Settings::caixasetinhascroll, { Settings::menuX + UI::Settings::NewScrollerbarTOPx, (Settings::optionCount) * 0.035f + UI::Settings::NewScrollerbarTOPy }, { 0.011f, 0.0180f });
	Drawing::Spriter("commonmenutu", "arrowleft", Settings::menuX + UI::Settings::NewScrollerbarTOPx, ((Settings::optionCount) * 0.035f + UI::Settings::NewScrollerbarTOPy), 0.008f, 0.012f, 90, Settings::arrow2.r, Settings::arrow2.g, Settings::arrow2.b, Settings::arrow2.a);
}
int optionCountInfo;

bool UI::Option(const char * option, bool info, const char* textInfo)
{
	Settings::optionCount++;
	int opcount = Settings::optionCount;
	int currop = Settings::currentOption;
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
	{
		Drawing::Text(option, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount) * 0.035f + Settings::fontYPos }, { Settings::fontScale, Settings::fontScale }, false);

		Drawing::Rect(Settings::optionRect, { Settings::menuX + UI::Settings::NewScrollerMidBARX, (Settings::optionCount) * 0.035f + UI::Settings::NewScrollerMidBARY }, { Settings::ScrollerWidth, 0.035f });//Scrollbar
		onThis ? Drawing::Rect(UI::Settings::scroller, { Settings::menuX + UI::Settings::NewScrollerMidBARX, (Settings::optionCount) * 0.035f + UI::Settings::NewScrollerMidBARY }, { 0.007f, 0.035f }) : NULL; //
	}
	else if (Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions) && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text(option, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + Settings::fontYPos }, { Settings::fontScale, Settings::fontScale }, false);
	
		Drawing::Rect(Settings::optionRect, { Settings::menuX + UI::Settings::NewScrollerMidBARX, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + UI::Settings::NewScrollerMidBARY }, { Settings::ScrollerWidth, 0.035f });//Scrollabr
		onThis ? Drawing::Rect(UI::Settings::scroller, { Settings::menuX + UI::Settings::NewScrollerMidBARX, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + UI::Settings::NewScrollerMidBARY }, { 0.007f, 0.035f }) : NULL;
	}
	if (info) {
		if (onThis) {
			if (optionCountInfo >= Settings::maxVisOptions) {
				Drawing::Rect(Settings::optionRect, { Settings::menuX, Footer_Pos }, { 0.21f, 0.031f });
				Drawing::Spriter("shared", "info_icon_32", Settings::menuX - 0.094f, Footer_Pos2, 0.016f, 0.026f, 0, 255, 255, 255, g_GlobalAlpha);
				Drawing::Text(textInfo, Settings::optionText, { Settings::menuX - 0.084f, Footer_Pos3 }, { 0.20f, 0.20f }, false);
			}
			else if (optionCountInfo < Settings::maxVisOptions) {
				Drawing::Rect(Settings::optionRect, { Settings::menuX, Footer_Pos }, { 0.21f, 0.031f });
				Drawing::Spriter("shared", "info_icon_32", Settings::menuX - 0.094f, Footer_Pos2, 0.016f, 0.026f, 0, 255, 255, 255, g_GlobalAlpha);
				Drawing::Text(textInfo, Settings::optionText, { Settings::menuX - 0.084f, Footer_Pos3 }, { 0.20f, 0.20f }, false);
			}
		}
	}
	else {
		if (onThis) {
			if (optionCountInfo >= Settings::maxVisOptions)
				Drawing::Rect(Settings::optionRect, { Settings::menuX, Footer_Pos }, { 0.21f, 0.031f });
			else if (optionCountInfo < Settings::maxVisOptions)
				Drawing::Rect(Settings::optionRect, { Settings::menuX, Footer_Pos }, { 0.21f, 0.031f });
		}
	}

	if (Settings::currentOption == Settings::optionCount)
	{
		if (Settings::selectPressed)
		{
			return true;
		}
	}
	return false;
}
/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/
float UI::Settings::Examplefloat1 = 0.2745f;
float UI::Settings::Examplefloat2 = 0.11f;
float UI::Settings::Examplefloat3 = 0.035f;
float  UI::Settings::Examplefloat4 = 0.0f;
float  UI::Settings::Examplefloat5 = 0.695f;
float  UI::Settings::Examplefloat6 = 0.0247;
float  UI::Settings::Examplefloat7 = 0.198f;
float  UI::Settings::Examplefloat8 = 0.694f;
float  UI::Settings::Examplefloat9 = 0.0247;
bool UI::Break(std::string option)
{
	std::string str1 = option;
	std::string left = "~r~[~m~ " + option + " ~r~]";
	const char* cstr1 = left.c_str();
	Settings::optionCount++;
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
	{
		Drawing::Text(cstr1, Settings::optionText, { Settings::menuX, (Settings::optionCount) * 0.035f + Settings::fontYPos }, { Settings::fontScale, Settings::fontScale }, true);
		Drawing::Rect(Settings::optionRect, { Settings::menuX + 0.114f, (Settings::optionCount) * 0.035f + 0.139f }, { 0.011f, 0.036f });
		if (onThis && Settings::currentOption == 1)
			Settings::currentOption += 1;
		else {
			if (onThis && g_PressedKey == 2)
				Settings::currentOption += 1;
			else if (onThis && g_PressedKey == 1)
				Settings::currentOption -= 1;
		}
	}
	else if (Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions) && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text(cstr1, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + Settings::fontYPos }, { Settings::fontScale, Settings::fontScale }, false);
		Drawing::Rect(Settings::optionRect, { Settings::menuX + 0.114f,  (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.139f }, { 0.011f, 0.036f });
		if (onThis && Settings::currentOption == 1)
			Settings::currentOption += 1;
		else {
			if (onThis && g_PressedKey == 2)
				Settings::currentOption += 1;
			else if (onThis && g_PressedKey == 1)
				Settings::currentOption -= 1;
		}
	}

	if (Settings::currentOption == Settings::optionCount)
	{
		if (Settings::selectPressed)
		{
			return true;
		}
	}
	return false;
}
bool UI::Sub(const char * option, SubMenus newSub, bool info, const char* textInfo)
{
	Option(option, info, textInfo);

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(">>", Settings::breakText, { Settings::menuX + Settings::subMenuArrowX, Settings::optionCount * 0.035f + Settings::fontYPos }, { Settings::fontScale, Settings::fontScale }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(">>", Settings::breakText, { Settings::menuX + Settings::subMenuArrowX, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions))*0.035f + Settings::fontYPos }, { Settings::fontScale, Settings::fontScale }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		MenuLevelHandler::MoveMenu(newSub);
		return true;
	}
	return false;
}
bool UI::Toggle(const char * option, bool & b00l, bool info, const char* textInfo)
{
	Option(option, info, textInfo);
	if (b00l)
	{
		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Spriter("crosstheline", b00l ? "timer_largetick_32" : "timer_largecross_32", Settings::menuX + 0.093f, (Settings::optionCount * 0.035f + 0.142f), 0.011f, 0.020f, 0, 255, 255, 255, g_GlobalAlpha);
		else if ((Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions)) && Settings::optionCount <= Settings::currentOption)
			Drawing::Spriter("crosstheline", b00l ? "timer_largetick_32" : "timer_largecross_32", Settings::menuX + 0.093f, ((Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.142f), 0.011f, 0.02f, 0, 255, 255, 255, g_GlobalAlpha);
	}
	else
	{
		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Spriter("crosstheline", b00l ? "timer_largetick_32" : "timer_largecross_32", Settings::menuX + 0.093f, (Settings::optionCount * 0.035f + 0.142f), 0.011f, 0.020f, 0, 255, 255, 255, g_GlobalAlpha);
		else if ((Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions)) && Settings::optionCount <= Settings::currentOption)
			Drawing::Spriter("crosstheline", b00l ? "timer_largetick_32" : "timer_largecross_32", Settings::menuX + 0.093f, ((Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.142f), 0.011f, 0.02f, 0, 255, 255, 255, g_GlobalAlpha);
	}
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		b00l ^= 1;
		return true;
	}
	return false;
}


bool UI::Toggle(const char* option, bool& b00l, std::function<void()> function, bool info, const char* textInfo)
{
	Option(option, info, textInfo);
	if (b00l)
	{
		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Spriter("crosstheline", b00l ? "timer_largetick_32" : "timer_largecross_32", Settings::menuX + 0.093f, (Settings::optionCount * 0.035f + 0.142f), 0.011f, 0.020f, 0, 255, 255, 255, g_GlobalAlpha);
		else if ((Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions)) && Settings::optionCount <= Settings::currentOption)
			Drawing::Spriter("crosstheline", b00l ? "timer_largetick_32" : "timer_largecross_32", Settings::menuX + 0.093f, ((Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.142f), 0.011f, 0.02f, 0, 255, 255, 255, g_GlobalAlpha);
	}
	else
	{
		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Spriter("crosstheline", b00l ? "timer_largetick_32" : "timer_largecross_32", Settings::menuX + 0.093f, (Settings::optionCount * 0.035f + 0.142f), 0.011f, 0.020f, 0, 255, 255, 255, g_GlobalAlpha);
		else if ((Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions)) && Settings::optionCount <= Settings::currentOption)
			Drawing::Spriter("crosstheline", b00l ? "timer_largetick_32" : "timer_largecross_32", Settings::menuX + 0.093f, ((Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.142f), 0.011f, 0.02f, 0, 255, 255, 255, g_GlobalAlpha);
	}
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		b00l ^= 1;
		function();
		return true;
	}
	return false;
}

bool UI::Int(const char * option, int & _int, int min, int max, int step, bool info, const char* textInfo)
{
	Option(option, info, textInfo);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::rightPressed) {
			_int > min ? _int -= step : _int = max;
		}
		if (Settings::leftPressed) {
			_int < max ? _int += step : _int = min;
		}
	}
	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text_Right(Tools::StringToChar("<" + std::to_string(_int) + ">"), Settings::optionText, { Settings::menuX + 0.098f, (Settings::optionCount) * 0.035f + Settings::fontYPos }, { Settings::fontScale, Settings::fontScale }, 0);
	else if ((Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions)) && Settings::optionCount <= Settings::currentOption)
		Drawing::Text_Right(Tools::StringToChar("<" + std::to_string(_int) + ">"), Settings::optionText, { Settings::menuX + 0.098f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + Settings::fontYPos }, { Settings::fontScale, Settings::fontScale }, 0);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool UI::Float(const char * option, float & _float, int min, int max, float step, bool info, const char* textInfo)
{
	Option(option, info, textInfo);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::rightPressed) {
			_float <= min ? _float = max : _float -= step;
		}
		if (Settings::leftPressed) {
			_float >= max ? _float = min : _float += step;
		}
	}

	char buf[300];
	_snprintf_s(buf, sizeof(buf), "%.3f", _float);
	std::string flt = buf;

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text_Right(Tools::StringToChar("<" + flt + ">"), Settings::optionText, { Settings::menuX, (Settings::optionCount) * 0.035f + Settings::fontYPos }, { Settings::fontScale, Settings::fontScale }, 0);
	else if ((Settings::optionCount > (Settings::currentOption - Settings::maxVisOptions)) && Settings::optionCount <= Settings::currentOption)
		Drawing::Text_Right(Tools::StringToChar("<" + flt + ">"), Settings::optionText, { Settings::menuX, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + Settings::fontYPos }, { Settings::fontScale, Settings::fontScale }, 0);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}


void UI::End()
{
	if (UI::Settings::displayEnd)
	{
		optionCountInfo = Settings::optionCount;
		if (optionCountInfo >= 11)
		{
			//Scrollbar Addon
			Drawing::Rect(Settings::caixasetinhascroll, { Settings::menuX + UI::Settings::NewScrollerbarTOPx, 12 * 0.035f + UI::Settings::NewScrollerEndBar }, { 0.011f, 0.017f });//-------
			Drawing::Spriter("commonmenutu", "arrowleft", Settings::menuX + UI::Settings::NewScrollerbarTOPx, 12 * 0.035f + UI::Settings::NewScrollerEndBar, 0.008f, 0.012f, -90, Settings::arrow2.r, Settings::arrow2.g, Settings::arrow2.b, Settings::arrow2.a);
			//Scrollbar Addon
		}

		else if (optionCountInfo > 0)
		{
			//Scrollbar Addon
			Drawing::Rect(Settings::caixasetinhascroll, { Settings::menuX + UI::Settings::NewScrollerbarTOPx, ((Settings::optionCount + 1) * 0.035f + UI::Settings::NewScrollerEndBar) }, { 0.011f, 0.017f });//--------
			Drawing::Spriter("commonmenutu", "arrowleft", Settings::menuX + UI::Settings::NewScrollerbarTOPx, ((Settings::optionCount + 1) * 0.035f + UI::Settings::NewScrollerEndBar), 0.008f, 0.012f, -90, Settings::arrow2.r, Settings::arrow2.g, Settings::arrow2.b, Settings::arrow2.a);
			//Scrollbar Addon
		}
	}
}

int UI::Settings::keyPressDelay = 200;
int UI::Settings::keyPressPreviousTick = GetTickCount();
int UI::Settings::keyPressDelay2 = 200;
int UI::Settings::keyPressPreviousTick2 = GetTickCount();
int UI::Settings::keyPressDelay3 = 200;
int UI::Settings::keyPressPreviousTick3 = GetTickCount();
int UI::Settings::openKey = VK_MULTIPLY;
int UI::Settings::backKey = VK_NUMPAD0;
int UI::Settings::upKey = VK_NUMPAD8;
int UI::Settings::downKey = VK_NUMPAD2;
int UI::Settings::leftKey = VK_NUMPAD4;
int UI::Settings::rightKey = VK_NUMPAD6;
int UI::Settings::selectKey = VK_NUMPAD5;
int UI::Settings::arrowupKey = VK_UP;
int UI::Settings::arrowdownKey = VK_DOWN;
int UI::Settings::arrowleftKey = VK_LEFT;
int UI::Settings::arrowrightKey = VK_RIGHT;
int UI::Settings::enterKey = VK_RETURN;
int UI::Settings::deleteKey = VK_BACK;

#pragma endregion

bool UI::Settings::controllerinput = true;
void UI::Checks::Controlls()
{
	Settings::selectPressed = false;
	Settings::leftPressed = false;
	Settings::rightPressed = false;
	if (GetTickCount() - Settings::keyPressPreviousTick > Settings::keyPressDelay) {
	if (GetTickCount() - Settings::keyPressPreviousTick2 > Settings::keyPressDelay2) {
		if (GetTickCount() - Settings::keyPressPreviousTick3 > Settings::keyPressDelay3) {
			if (g_OpenMenu) {
				if (IsKeyPressed(VK_MULTIPLY) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlScriptRB) && CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && Settings::controllerinput) {
					Settings::menuLevel == 0 ? MenuLevelHandler::MoveMenu(SubMenus::sub_main) : Settings::menuLevel == 1 ? MenuLevelHandler::BackMenu() : NULL;
					Settings::keyPressPreviousTick = GetTickCount();
				}
				else if (IsKeyPressed(VK_NUMPAD0) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendCancel) && Settings::controllerinput) {
					Settings::menuLevel > 0 ? MenuLevelHandler::BackMenu() : NULL;
					Settings::keyPressPreviousTick = GetTickCount();
				}
				else if (IsKeyPressed(VK_NUMPAD8) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendUp) && Settings::controllerinput) {
					Settings::currentOption > 1 ? Settings::currentOption-- : Settings::currentOption = Settings::optionCount;
					g_PressedKey = 1;
					Settings::keyPressPreviousTick2 = GetTickCount();
				}
				else if (IsKeyPressed(VK_NUMPAD2) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendDown) && Settings::controllerinput) {
					Settings::currentOption < Settings::optionCount ? Settings::currentOption++ : Settings::currentOption = 1;
					g_PressedKey = 2;
					Settings::keyPressPreviousTick2 = GetTickCount();
				}
				else if (IsKeyPressed(VK_NUMPAD6) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && Settings::controllerinput) {
					Settings::leftPressed = true;
					Settings::keyPressPreviousTick3 = GetTickCount();
				}
				else if (IsKeyPressed(VK_NUMPAD4) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneLeft) && Settings::controllerinput) {
					Settings::rightPressed = true;
					Settings::keyPressPreviousTick3 = GetTickCount();
				}
				else if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept) && Settings::controllerinput) {
					Settings::selectPressed = true;
					Settings::keyPressPreviousTick = GetTickCount();
				}
			}
		}
	}
  }
	Settings::optionCount = 0;
}
#pragma warning(default : 4018)
void UI::MenuLevelHandler::MoveMenu(SubMenus menu)
{
	Settings::menusArray[Settings::menuLevel] = Settings::currentMenu;
	Settings::optionsArray[Settings::menuLevel] = Settings::currentOption;
	Settings::menuLevel++;
	Settings::currentMenu = menu;
	Settings::currentOption = 1;
}

void UI::MenuLevelHandler::BackMenu()
{
	if (Settings::menuLevel > 1) {
		Settings::menuLevel--;
		Settings::currentMenu = Settings::menusArray[Settings::menuLevel];
		Settings::currentOption = Settings::optionsArray[Settings::menuLevel];
	}
}

void g_IncreaseAlpha() {
	g_GlobalAlpha += 5;
}

void g_DecreaseAlpha() {
	g_GlobalAlpha -= 5;
}

int g_OpenMenu_tick = GetTickCount();
void UI::MonitorMenu() {
	if (GetTickCount() - g_OpenMenu_tick > UI::Settings::keyPressDelay) {
		if (IsKeyPressed(VK_MULTIPLY)) {
			g_OpenMenu = !g_OpenMenu;
			g_OpenMenu_tick = GetTickCount();
		}
	}

	if (g_OpenMenu)
	{
		if (g_GlobalAlpha < 255)
			CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(g_IncreaseAlpha), nullptr, 0, nullptr);
		UI::Settings::titleText = { 255, 255, 255, g_GlobalAlpha, 1 };
		UI::Settings::titleRect = { 35, 35, 35, g_GlobalAlpha };
		UI::Settings::optionText = { 255, 255, 255, g_GlobalAlpha, 0 };
		UI::Settings::breakText = { 255, 255, 255, g_GlobalAlpha, 0 };
		UI::Settings::optionRect = { 35, 35, 35, g_GlobalAlpha };
		UI::Settings::scroller = { 25, 25, 25, g_GlobalAlpha };
		UI::Settings::arrow2 = { 255, 255, 255, g_GlobalAlpha, 3 };
		UI::Settings::arrow = { 0, 0, 0, g_GlobalAlpha };
		UI::Settings::caixasetinhascroll = { 0, 0, 0, g_GlobalAlpha };
		//Float
		UI::HIDE_HELP_TEXT_THIS_FRAME();
		CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_NEXT_CAMERA, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_CHARACTER_WHEEL, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_LIGHT, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_HEAVY, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MULTIPLAYER_INFO, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_ALTERNATE, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_CIN_CAM, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MAP_POI, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_RADIO_WHEEL, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_HEADLIGHT, true);
	}
	else {
		if (g_GlobalAlpha > 0)
			CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(g_DecreaseAlpha), nullptr, 0, nullptr);
		UI::Settings::titleText = { 255, 255, 255, g_GlobalAlpha, 1 };
		UI::Settings::titleRect = { 35, 35, 35, g_GlobalAlpha };
		UI::Settings::optionText = { 255, 255, 255, g_GlobalAlpha, 0 };
		UI::Settings::breakText = { 255, 255, 255, g_GlobalAlpha, 0 };
		UI::Settings::optionRect = { 35, 35, 35, g_GlobalAlpha };
		UI::Settings::scroller = { 25, 25, 25, g_GlobalAlpha };
		UI::Settings::arrow2 = { 255, 255, 255, g_GlobalAlpha, 3 };
		UI::Settings::arrow = { 0, 0, 0, g_GlobalAlpha };
		UI::Settings::caixasetinhascroll = { 0, 0, 0, g_GlobalAlpha };
	}
}

char * UI::Tools::StringToChar(std::string string)
{
	return _strdup(string.c_str());
}

void UI::Files::WriteStringToIni(std::string string, std::string file, std::string app, std::string key)
{
	WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), file.c_str());
}

std::string UI::Files::ReadStringFromIni(std::string file, std::string app, std::string key)
{
	char buf[100];
	GetPrivateProfileStringA(app.c_str(), key.c_str(), "NULL", buf, 100, file.c_str());
	return (std::string)buf;
}

void UI::Files::WriteIntToIni(int intValue, std::string file, std::string app, std::string key)
{
	WriteStringToIni(std::to_string(intValue), file, app, key);
}

int UI::Files::ReadIntFromIni(std::string file, std::string app, std::string key)
{
	return std::stoi(ReadStringFromIni(file, app, key));
}

void UI::Files::WriteFloatToIni(float floatValue, std::string file, std::string app, std::string key)
{
	WriteStringToIni((std::to_string(floatValue)), file, app, key);
}

float UI::Files::ReadFloatFromIni(std::string file, std::string app, std::string key)
{
	return std::stof(ReadStringFromIni(file, app, key));
}

void UI::Files::WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key)
{
	WriteStringToIni(b00l ? "true" : "false", file, app, key);
}

bool UI::Files::ReadBoolFromIni(std::string file, std::string app, std::string key)
{
	return ReadStringFromIni(file, app, key) == "true" ? true : false;
}

