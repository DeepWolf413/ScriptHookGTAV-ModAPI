#pragma once
#include <enums.h>
#include <string>

#include "Constants.h"

namespace ModAPI
{
	namespace MMath
	{
		struct Color;
		struct Vector2;
	}
}

namespace ModAPI::Screen
{
	void DisplayText(const std::string& text, const MMath::Vector2& position, const MMath::Color& color, bool centered, const MMath::Vector2& scale);
	void DisplayText(const std::string& text, const MMath::Vector2& position, const MMath::Color& color, eFont font, bool centered, const MMath::Vector2& scale);
	void DrawRect(const MMath::Vector2& position, const MMath::Vector2& size, const MMath::Color& color);
	void PrintSubtitle(const std::string& text);
	void PrintSubtitle(const std::string& text, int durationMs);
	void ShowHelpTextThisFrame(const std::string& helpText);
	void ShowHelpTextThisFrame(const std::string& helpText, bool beep);
	int ShowNotification(const std::string& text, bool blink = false);
	std::string GetUserInput(const char* title = Constants::WindowTitle::FMMC_KEY_TIP8, const std::string& defaultText = "", int maxLength = 255);
	
	/**
	 * \brief Shows the busy spinner for 3 seconds with the specified text, and then disappears.
	 * \param text The text to show next to the loading message.
	 */
	void ShowLoadingMessage(const std::string& text);
}
