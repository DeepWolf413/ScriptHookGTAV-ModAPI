#include "Screen.h"

#include <shsdk/natives.h>

#include "math/Color.h"

void ModAPI::Screen::DrawSprite(const char* category, const char* sprite, const Vector2& position, const Vector2& scale, const float rotation,
                                const Color& color)
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

	GRAPHICS::DRAW_SPRITE(category, sprite, fX, fY, scale.x, scale.y, rotation, color.R, color.G, color.B, color.A, 1);
	GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(category);
}

void ModAPI::Screen::DisplayText(const char* text, const Vector2& position, const Color& color, const bool centered, const Vector2& scale)
{
	DisplayText(text, position, color, eFont::FontPricedown, centered, scale);
}

void ModAPI::Screen::DisplayText(const char* text, const Vector2& position, const Color& color, const eFont font, const bool centered,
	const Vector2& scale)
{
	HUD::SET_TEXT_COLOUR(color.R, color.G, color.B, color.A);
	HUD::SET_TEXT_SCALE(scale.x, scale.y);
	HUD::SET_TEXT_FONT(font);
	HUD::SET_TEXT_CENTRE(centered);

	HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y, 0);
}

void ModAPI::Screen::DrawRect(const Vector2& position, const Vector2& size, const Color& color)
{
	const float fX = position.x + size.x / 2;
	const float fY = position.y + size.y / 2;
	GRAPHICS::DRAW_RECT(fX, fY, size.x, size.y, color.R, color.G, color.B, color.A, true);
}

void ModAPI::Screen::PrintSubtitle(const char* text)
{
	HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	HUD::END_TEXT_COMMAND_PRINT(2000, 1);
}

void ModAPI::Screen::PrintSubtitle(const char* text, const float duration)
{
    HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
    HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
    HUD::END_TEXT_COMMAND_PRINT(duration * 1000, 1);
}

void ModAPI::Screen::ShowHelpTextThisFrame(const std::string& helpText)
{ ShowHelpTextThisFrame(helpText, true); }

void ModAPI::Screen::ShowHelpTextThisFrame(const std::string& helpText, const bool beep)
{
    HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
    HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(helpText.c_str());
    HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, beep, -1);
}