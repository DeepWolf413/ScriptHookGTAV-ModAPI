#include "Screen.h"

#include <shsdk/natives.h>

void ModAPI::Screen::DrawSprite(const char* category, const char* sprite, const Vector2& position, const Vector2& scale, float rotation,
                        int r, int g, int b, int a)
{
	const float fX = position.x + scale.x / 2;
	const float fY = position.y + scale.y / 2;

	int ticks = 0;
	while (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(category))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(category, 0);
		WAIT(1);
		ticks++;

		if (ticks >= 5000)
		{
			break;
		}
	}

	GRAPHICS::DRAW_SPRITE(category, sprite, fX, fY, scale.x, scale.y, rotation, r, g, b, a, 1);
	GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(category);
}

void ModAPI::Screen::DisplayText(const char* text, const Vector2& position, int r, int g, int b, int a, bool centered, const Vector2& scale)
{
	DisplayText(text, position, r, g, b, a, eFont::FontPricedown, centered, scale);
}

void ModAPI::Screen::DisplayText(const char* text, const Vector2& position, int r, int g, int b, int a, eFont font, bool centered,
	const Vector2& scale)
{
	HUD::SET_TEXT_COLOUR(r, g, b, a);
	HUD::SET_TEXT_SCALE(scale.x, scale.y);
	HUD::SET_TEXT_FONT(font);
	HUD::SET_TEXT_CENTRE(centered);

	HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y, 0);
}

void ModAPI::Screen::DrawRect(const Vector2& position, const Vector2& size, int r, int g, int b, int a)
{
	const float fX = position.x + size.x / 2;
	const float fY = position.y + size.y / 2;
	GRAPHICS::DRAW_RECT(fX, fY, size.x, size.y, r, g, b, a, true);
}

void ModAPI::Screen::PrintSubtitle(const char* text)
{
    HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
    HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
    HUD::END_TEXT_COMMAND_PRINT(200, 1);
}

void ModAPI::Screen::ShowHelpTextThisFrame(const std::string& helpText)
{ ShowHelpTextThisFrame(helpText, true); }

void ModAPI::Screen::ShowHelpTextThisFrame(const std::string& helpText, const bool beep)
{
    HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
    HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(helpText.c_str());
    HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, beep, -1);
}