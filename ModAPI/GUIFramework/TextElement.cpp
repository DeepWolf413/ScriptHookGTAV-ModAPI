﻿#include "TextElement.h"

#include "shsdk/natives.h"

ModAPI::GUIFramework::TextElement::TextElement(const Vector2& position, const Vector2& size, const std::string& text,
                                               const eFont font)
	: TextElement(position, size, TopLeft, text, font)
{
}

ModAPI::GUIFramework::TextElement::TextElement(const Vector2& position, const Vector2& size,
                                               const eGUIElementAnchor anchor,
                                               const std::string& text, const eFont font)
	: GUIElement(position, size, anchor)
{
	this->text = text;
	this->font = font;
	TextElement::CalculatePosition();
}

void ModAPI::GUIFramework::TextElement::Draw()
{
	HUD::SET_TEXT_FONT(font);
	HUD::SET_TEXT_SCALE(0.0f, size.Y);
	HUD::SET_TEXT_COLOUR(color.R, color.G, color.B, color.A);

	HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
	HUD::END_TEXT_COMMAND_DISPLAY_TEXT(calculatedPosition.X, calculatedPosition.Y, 0);
}

void ModAPI::GUIFramework::TextElement::SetText(const std::string& newText)
{
	text = newText;
	CalculatePosition();
}

void ModAPI::GUIFramework::TextElement::SetFont(const eFont newFont)
{
	font = newFont;
	CalculatePosition();
}

float ModAPI::GUIFramework::TextElement::GetTextWidth() const
{
	HUD::_BEGIN_TEXT_COMMAND_GET_WIDTH("STRING");
	HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
	HUD::SET_TEXT_FONT(font);
	HUD::SET_TEXT_SCALE(size.Y, size.Y);
	return HUD::_END_TEXT_COMMAND_GET_WIDTH(true);
}

void ModAPI::GUIFramework::TextElement::CalculatePosition()
{
	const float textWidth = GetTextWidth();
	const float textHeight = HUD::GET_RENDERED_CHARACTER_HEIGHT(size.Y, font);

	switch (anchor)
	{
	case TopLeft:
		calculatedPosition = position;
		break;
	case Top:
		calculatedPosition = position - Vector2(textWidth * 0.5f, 0.0f);
		break;
	case TopRight:
		calculatedPosition = position - Vector2(textWidth, 0.0f);
		break;
	case MiddleLeft:
		calculatedPosition = position - Vector2(0.0f, textHeight * 0.5f);
		break;
	case Middle:
		calculatedPosition = position - Vector2(textWidth * 0.5f, textHeight * 0.5f);
		break;
	case MiddleRight:
		calculatedPosition = position - Vector2(textWidth, textHeight * 0.5f);
		break;
	case BottomLeft:
		calculatedPosition = position - Vector2(0.0f, textHeight);
		break;
	case Bottom:
		calculatedPosition = position - Vector2(textWidth * 0.5f, textHeight);
		break;
	case BottomRight:
		calculatedPosition = position - Vector2(textWidth, textHeight);
		break;
	}
}

Vector2 ModAPI::GUIFramework::TextElement::GetSize() const
{
	const float textWidth = GetTextWidth();
	const float textHeight = HUD::GET_RENDERED_CHARACTER_HEIGHT(size.Y, font);
	return {textWidth, textHeight};
}
