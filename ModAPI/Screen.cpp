#include "Screen.h"

#include <shsdk/natives.h>

#include "math/Color.h"
#include "math/Vector2.h"

void ModAPI::Screen::DisplayText(const std::string& text, const Vector2& position, const Color& color, const bool centered, const Vector2& scale)
{
	DisplayText(text, position, color, eFont::FontPricedown, centered, scale);
}

void ModAPI::Screen::DisplayText(const std::string& text, const Vector2& position, const Color& color, const eFont font, const bool centered,
	const Vector2& scale)
{
	HUD::SET_TEXT_COLOUR(color.R, color.G, color.B, color.A);
	HUD::SET_TEXT_SCALE(scale.X, scale.Y);
	HUD::SET_TEXT_FONT(font);
	HUD::SET_TEXT_CENTRE(centered);

	HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
	HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.X, position.Y, 0);
}

void ModAPI::Screen::PrintSubtitle(const std::string& text)
{
	HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
	HUD::END_TEXT_COMMAND_PRINT(2000, 1);
}

void ModAPI::Screen::PrintSubtitle(const std::string& text, const int durationMs)
{
    HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
    HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
    HUD::END_TEXT_COMMAND_PRINT(durationMs, 1);
}

void ModAPI::Screen::ShowHelpTextThisFrame(const std::string& helpText)
{ ShowHelpTextThisFrame(helpText, true); }

void ModAPI::Screen::ShowHelpTextThisFrame(const std::string& helpText, const bool beep)
{
    HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
    HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(helpText.c_str());
    HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, beep, -1);
}

int ModAPI::Screen::ShowNotification(const std::string& text, const bool blink)
{
	HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
	return HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(blink, TRUE);
}

std::string ModAPI::Screen::GetUserInput(const char* title, const std::string& defaultText, const int maxLength)
{
	MISC::DISPLAY_ONSCREEN_KEYBOARD(true, title, "", defaultText.c_str(), "", "", "", maxLength);
	while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0)
	{
		WAIT(0);
	}

	return MISC::GET_ONSCREEN_KEYBOARD_RESULT();
}

void ModAPI::Screen::ShowLoadingMessage(const std::string& text)
{
	HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
	HUD::END_TEXT_COMMAND_BUSYSPINNER_ON(5);
	WAIT(3000);
	HUD::BUSYSPINNER_OFF();
}
