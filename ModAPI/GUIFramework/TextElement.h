#pragma once

#include <enums.h>
#include <string>

#include "GUIElement.h"
#include "Enums.h"

namespace ModAPI::GUIFramework
{
	class TextElement : public GUIElement
	{
	public:
		TextElement() = default;
		TextElement(const MMath::Vector2& position, const MMath::Vector2& size, const std::string& text, eFont font);
		TextElement(const MMath::Vector2& position, const MMath::Vector2& size, eGUIElementAnchor anchor, const std::string& text, eFont font);
		
		void Draw() override;
		void SetText(const std::string& newText);
		void SetFont(eFont newFont);
		[[nodiscard]] float GetTextWidth() const;

		void CalculatePosition() override;

	protected:
		[[nodiscard]] MMath::Vector2 GetSize() const override;
		
		std::string text;
		eFont font;
	};
}
