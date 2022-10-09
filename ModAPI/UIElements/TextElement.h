#pragma once

#include <enums.h>
#include <string>

#include "UIElement.h"

namespace ModAPI::UI
{
	class TextElement : public UIElement
	{
		struct DropShadow
		{
		public:
			DropShadow() = default;
			DropShadow(int distance, MMath::Color color);

			[[nodiscard]] int GetDistance() const;
			[[nodiscard]] const MMath::Color& GetColor() const;
			
		private:
			int distance {0};
			MMath::Color color {};
		};
		
	public:
		TextElement() = default;
		TextElement(const MMath::Vector2& position, const MMath::Vector2& size, const std::string& text, eFont font);
		TextElement(const MMath::Vector2& position, const MMath::Vector2& size, Enums::eUIAnchor anchor, const std::string& text, eFont font);
		
		void Display() override;
		void SetText(const std::string& newText);
		void SetFont(eFont newFont);
		void SetJustify(Enums::eUIAlignment horizontalAlignment);
		void SetWrap(float start, float end);
		void SetDropShadow(const DropShadow& newDropShadow);
		[[nodiscard]] float GetTextWidth() const;

		void CalculatePosition() override;

	protected:
		[[nodiscard]] MMath::Vector2 GetSize() const override;
		
		std::string text;
		eFont font;
		MMath::Vector2 wrap;
		DropShadow dropShadow;
		Enums::eUIAlignment horizontalAlignment {Enums::UIAlignment_AlignLeft};
	};
}
