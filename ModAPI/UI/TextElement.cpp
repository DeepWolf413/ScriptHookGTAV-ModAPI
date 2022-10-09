#include "TextElement.h"

#include "natives.h"

namespace ModAPI::UI
{
	TextElement::DropShadow::DropShadow(const int distance, const MMath::Color color)
	{
		this->distance = distance;
		this->color = color;
	}

	int TextElement::DropShadow::GetDistance() const
	{
		return distance;
	}

	const MMath::Color& TextElement::DropShadow::GetColor() const
	{
		return color;
	}

	TextElement::TextElement(const MMath::Vector2& position, const MMath::Vector2& size, const std::string& text,
	                         const eFont font)
		: TextElement(position, size, Enums::UIAnchor_TopLeft, text, font)
	{
	}

	TextElement::TextElement(const MMath::Vector2& position, const MMath::Vector2& size,
	                                     const Enums::eUIAnchor anchor,
	                                     const std::string& text, const eFont font)
		: UIElement(position, size, anchor)
	{
		this->text = text;
		this->font = font;
		TextElement::CalculatePosition();
	}

	void TextElement::Display()
	{
		HUD::SET_TEXT_FONT(font);
		HUD::SET_TEXT_SCALE(0.0f, size.Y);
		HUD::SET_TEXT_COLOUR(color.R, color.G, color.B, color.A);

		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(calculatedPosition.X, calculatedPosition.Y, 0);
	}

	void TextElement::SetText(const std::string& newText)
	{
		text = newText;
		CalculatePosition();
	}

	void TextElement::SetFont(const eFont newFont)
	{
		font = newFont;
		CalculatePosition();
	}

	void TextElement::SetJustify(const Enums::eUIAlignment horizontalAlignment)
	{
		this->horizontalAlignment = horizontalAlignment;
	}

	void TextElement::SetWrap(float start, float end)
	{
		wrap = {start, end};
	}

	void TextElement::SetDropShadow(const DropShadow& newDropShadow)
	{
		dropShadow = newDropShadow;
	}

	float TextElement::GetTextWidth() const
	{
		HUD::BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		HUD::SET_TEXT_FONT(font);
		HUD::SET_TEXT_SCALE(size.Y, size.Y);
		return HUD::END_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(true);
	}

	void TextElement::CalculatePosition()
	{
		const float textWidth = GetTextWidth();
		const float textHeight = HUD::GET_RENDERED_CHARACTER_HEIGHT(size.Y, font);

		switch (anchor)
		{
		case Enums::UIAnchor_TopLeft:
			calculatedPosition = position;
			break;
		case Enums::UIAnchor_Top:
			calculatedPosition = position - MMath::Vector2(textWidth * 0.5f, 0.0f);
			break;
		case Enums::UIAnchor_TopRight:
			calculatedPosition = position - MMath::Vector2(textWidth, 0.0f);
			break;
		case Enums::UIAnchor_MiddleLeft:
			calculatedPosition = position - MMath::Vector2(0.0f, textHeight * 0.5f);
			break;
		case Enums::UIAnchor_Middle:
			calculatedPosition = position - MMath::Vector2(textWidth * 0.5f, textHeight * 0.5f);
			break;
		case Enums::UIAnchor_MiddleRight:
			calculatedPosition = position - MMath::Vector2(textWidth, textHeight * 0.5f);
			break;
		case Enums::UIAnchor_BottomLeft:
			calculatedPosition = position - MMath::Vector2(0.0f, textHeight);
			break;
		case Enums::UIAnchor_Bottom:
			calculatedPosition = position - MMath::Vector2(textWidth * 0.5f, textHeight);
			break;
		case Enums::UIAnchor_BottomRight:
			calculatedPosition = position - MMath::Vector2(textWidth, textHeight);
			break;
		}
	}

	MMath::Vector2 TextElement::GetSize() const
	{
		const float textWidth = GetTextWidth();
		const float textHeight = HUD::GET_RENDERED_CHARACTER_HEIGHT(size.Y, font);
		return {textWidth, textHeight};
	}
}
