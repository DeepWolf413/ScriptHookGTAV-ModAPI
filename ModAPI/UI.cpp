#include "UI.h"

#include <natives.h>

#include "MathAPI.h"

namespace ModAPI::UI
{
	void DisplayText(const std::string& text, const MMath::Vector2& position, const MMath::Color& color, const bool centered, const MMath::Vector2& scale)
	{
		DisplayText(text, position, color, eFont::FontPricedown, centered, scale);
	}

	void DisplayText(const std::string& text, const MMath::Vector2& position, const MMath::Color& color, const eFont font, const bool centered,
									 const MMath::Vector2& scale)
	{
		HUD::SET_TEXT_COLOUR(color.R, color.G, color.B, color.A);
		HUD::SET_TEXT_SCALE(scale.X, scale.Y);
		HUD::SET_TEXT_FONT(font);
		HUD::SET_TEXT_CENTRE(centered);

		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(position.X, position.Y, 0);
	}

	void DisplaySubtitle(const std::string& text)
	{
		HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		HUD::END_TEXT_COMMAND_PRINT(2000, 1);
	}

	void DisplaySubtitle(const std::string& text, const int durationMs)
	{
		HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		HUD::END_TEXT_COMMAND_PRINT(durationMs, 1);
	}

	void DisplayHelpText(const std::string& helpText)
	{ DisplayHelpText(helpText, true); }

	void DisplayHelpText(const std::string& helpText, const bool beep)
	{
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(helpText.c_str());
		HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, beep, -1);
	}

	int DisplayNotification(const std::string& text, const bool blink)
	{
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		return HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(blink, TRUE);
	}

	void DisplayBusySpinner(const std::string& text, const int durationMs)
	{
		HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		HUD::END_TEXT_COMMAND_BUSYSPINNER_ON(5);
		WAIT(durationMs);
		HUD::BUSYSPINNER_OFF();
	}
} // namespace