#include "Screen.h"

#include <natives.h>

#include "Math/Color.h"
#include "Math/Vector2.h"

namespace ModAPI
{
	void Screen::DisplayText(const std::string& text, const MMath::Vector2& position, const MMath::Color& color, const bool centered, const MMath::Vector2& scale)
	{
		DisplayText(text, position, color, eFont::FontPricedown, centered, scale);
	}

	void Screen::DisplayText(const std::string& text, const MMath::Vector2& position, const MMath::Color& color, const eFont font, const bool centered,
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

	void Screen::PrintSubtitle(const std::string& text)
	{
		HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		HUD::END_TEXT_COMMAND_PRINT(2000, 1);
	}

	void Screen::PrintSubtitle(const std::string& text, const int durationMs)
	{
		HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		HUD::END_TEXT_COMMAND_PRINT(durationMs, 1);
	}

	void Screen::ShowHelpTextThisFrame(const std::string& helpText)
	{ ShowHelpTextThisFrame(helpText, true); }

	void Screen::ShowHelpTextThisFrame(const std::string& helpText, const bool beep)
	{
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(helpText.c_str());
		HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, beep, -1);
	}

	int Screen::ShowNotification(const std::string& text, const bool blink)
	{
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		return HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(blink, TRUE);
	}

	std::string Screen::GetUserInput(const std::string& title, const std::string& defaultText, const int maxLength)
	{
		MISC::DISPLAY_ONSCREEN_KEYBOARD(true, "", "", defaultText.c_str(), "", "", "", maxLength);
		while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0)
		{
			HUD::SET_TEXT_FONT(0);
			HUD::SET_TEXT_SCALE(0.34f, 0.34f);
			HUD::SET_TEXT_COLOUR(255, 255, 255, 255);
			HUD::SET_TEXT_WRAP(0.0f, 1.0f);
			HUD::SET_TEXT_RIGHT_JUSTIFY(FALSE);
			HUD::SET_TEXT_CENTRE(TRUE);
			HUD::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			HUD::SET_TEXT_EDGE(0, 0, 0, 0, 0);
			HUD::SET_TEXT_OUTLINE();

			if (HUD::DOES_TEXT_LABEL_EXIST(title.c_str()))
			{
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			}
			else if(title.length() < 100)
			{
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(title.c_str());
			}
			else
			{
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("jamyfafi");

				constexpr UINT8 maxStrComponentLength = 99;
				for (int i = 0; i < title.length(); i += maxStrComponentLength)
				{
					const std::string& strComp = title.substr(i, min(title.length() - i, maxStrComponentLength));
					HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(strComp.c_str());
				}
			}

			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(0.5f, 0.37f, 0);
			WAIT(0);
		}

		return MISC::GET_ONSCREEN_KEYBOARD_RESULT();
	}

	void Screen::ShowLoadingMessage(const std::string& text)
	{
		HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		HUD::END_TEXT_COMMAND_BUSYSPINNER_ON(5);
		WAIT(3000);
		HUD::BUSYSPINNER_OFF();
	}
}
