#pragma once
#include <string>
#include <shsdk/types.h>
#include <shsdk/enums.h>

struct Color;

namespace ModAPI::Screen
{
	void DrawSprite(const std::string& category, const std::string& sprite, const Vector2& position, const Vector2& scale, float rotation, const Color& color);
	void DisplayText(const std::string& text, const Vector2& position, const Color& color, bool centered, const Vector2& scale);
	void DisplayText(const std::string& text, const Vector2& position, const Color& color, eFont font, bool centered, const Vector2& scale);
	void DrawRect(const Vector2& position, const Vector2& size, const Color& color);
	void PrintSubtitle(const std::string& text);
	void PrintSubtitle(const std::string& text, int durationMs);
	void ShowHelpTextThisFrame(const std::string& helpText);
	void ShowHelpTextThisFrame(const std::string& helpText, bool beep);
	
	/**
	 * \brief Shows the busy spinner for 3 seconds with the specified text, and then disappears.
	 * \param text The text to show next to the loading message.
	 */
	void ShowLoadingMessage(const std::string& text);
}
