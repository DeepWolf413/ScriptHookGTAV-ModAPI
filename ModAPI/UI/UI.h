#pragma once
#include <enums.h>
#include <string>

#include "Enums.h"
#include "UI/TextElement.h"

namespace ModAPI
{
	namespace MMath
	{
		struct Color;
		struct Vector2;
	}
}

namespace ModAPI::UI
{
	void DisplayText(const std::string& text, const MMath::Vector2& position, const MMath::Color& color, Enums::eUIAlignment alignment, const MMath::Vector2& scale);
	void DisplayText(const std::string& text, const MMath::Vector2& position, const MMath::Color& color, eFont font, Enums::eUIAlignment alignment, const MMath::Vector2& scale);
	void DisplayText(const std::string& text, const MMath::Vector2& position, const MMath::Color& color, eFont font, Enums::eUIAlignment alignment, const MMath::Vector2& scale, const TextElement::DropShadow& dropShadow);
	void DrawRect(const MMath::Vector2& position, const MMath::Vector2& size, const MMath::Color& color);
	void DisplaySubtitle(const std::string& text);
	void DisplaySubtitle(const std::string& text, int durationMs);
	void DisplayHelpText(const std::string& helpText);
	void DisplayHelpText(const std::string& helpText, bool beep);
	int DisplayNotification(const std::string& text, bool blink = false);

	/**
	 * \brief Shows the busy spinner with the specified text for the specified duration.
	 * \param text The text to show next to the loading message.
	 * \param durationMs The duration for how long the loading message should be displayed.
	 */
	void DisplayBusySpinner(const std::string& text, int durationMs = 3000);
} // namespace