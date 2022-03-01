#include "Screen.h"

#include <shsdk/natives.h>

#include "math/Color.h"

void ModAPI::Screen::DrawSprite(const std::string& category, const std::string& sprite, const Vector2& position, const Vector2& scale, const float rotation,
                                const Color& color)
{
	const float fX = position.x + scale.x / 2;
	const float fY = position.y + scale.y / 2;

	int ticks = 0;
	while (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(category.c_str()))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(category.c_str(), 0);
		WAIT(1);
		ticks++;

		if (ticks >= 5000)
		{
			break;
		}
	}

	GRAPHICS::DRAW_SPRITE(category.c_str(), sprite.c_str(), fX, fY, scale.x, scale.y, rotation, color.R, color.G, color.B, color.A, 1);
	GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(category.c_str());
}

void ModAPI::Screen::DisplayText(const std::string& text, const Vector2& position, const Color& color, const bool centered, const Vector2& scale)
{
	DisplayText(text, position, color, eFont::FontPricedown, centered, scale);
}

void ModAPI::Screen::DisplayText(const std::string& text, const Vector2& position, const Color& color, const eFont font, const bool centered,
	const Vector2& scale)
{
	HUD::SET_TEXT_COLOUR(color.R, color.G, color.B, color.A);
	HUD::SET_TEXT_SCALE(scale.x, scale.y);
	HUD::SET_TEXT_FONT(font);
	HUD::SET_TEXT_CENTRE(centered);

	HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
	HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y, 0);
}

void ModAPI::Screen::DrawRect(const Vector2& position, const Vector2& size, const Color& color)
{
	const float fX = position.x + size.x / 2;
	const float fY = position.y + size.y / 2;
	GRAPHICS::DRAW_RECT(fX, fY, size.x, size.y, color.R, color.G, color.B, color.A, true);
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

void ModAPI::Screen::ShowLoadingMessage(const std::string& text)
{
	HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
	HUD::END_TEXT_COMMAND_BUSYSPINNER_ON(5);
	WAIT(3000);
	HUD::BUSYSPINNER_OFF();
}
