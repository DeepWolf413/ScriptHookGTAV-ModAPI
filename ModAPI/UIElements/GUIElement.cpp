#include "GUIElement.h"

#include <cmath>

#include "../UI.h"

namespace ModAPI
{
	GUIFramework::GUIElement::GUIElement(const MMath::Vector2& position, const MMath::Vector2& size)
		: GUIElement(position, size, Enums::eUIAnchor::UIAnchor_TopLeft)
	{ }

	GUIFramework::GUIElement::GUIElement(const MMath::Vector2& position, const MMath::Vector2& size, const Enums::eUIAnchor anchor)
	{
		this->position = position;
		this->size = size;
		this->anchor = anchor;
		this->color = MMath::Color(255, 255, 255, 255);
	}

	void GUIFramework::GUIElement::SetPosition(const MMath::Vector2& newPosition)
	{
		position = newPosition;
		CalculatePosition();
	}

	void GUIFramework::GUIElement::SetSize(const MMath::Vector2& newSize)
	{
		size = newSize;
		CalculatePosition();
	}

	void GUIFramework::GUIElement::SetAnchor(const Enums::eUIAnchor newAnchor)
	{
		anchor = newAnchor;
		CalculatePosition();
	}

	void GUIFramework::GUIElement::SetColor(const MMath::Color& newColor)
	{ color = newColor; }

	const MMath::Vector2& GUIFramework::GUIElement::GetCalculatedPosition() const
	{ return calculatedPosition; }

	const MMath::Color& GUIFramework::GUIElement::GetColor() const
	{ return color; }

	MMath::Vector2 GUIFramework::GUIElement::GetRelativePos(const MMath::Vector2& relativeOffset) const
	{
		const MMath::Vector2 cachedSize = GetSize();
		const float calculatedXOffset = std::lerp(0.0f, cachedSize.X, abs(relativeOffset.X));
		const float calculatedYOffset = std::lerp(0.0f, cachedSize.Y, abs(relativeOffset.Y));
		const auto calculatedOffset = MMath::Vector2(relativeOffset.X < 0 ? -calculatedXOffset : calculatedXOffset, relativeOffset.Y < 0 ? -calculatedYOffset : calculatedYOffset);
	
		return position + calculatedOffset;
	}

	void GUIFramework::GUIElement::CalculatePosition()
	{
		const MMath::Vector2 halfSize = GetSize() * 0.5f;
	
		switch (anchor)
		{
		case Enums::UIAnchor_TopLeft:
			calculatedPosition = position + halfSize;
			break;
		case Enums::UIAnchor_Top:
			calculatedPosition = position + MMath::Vector2(0.0f, halfSize.Y);
			break;
		case Enums::UIAnchor_TopRight:
			calculatedPosition = position + MMath::Vector2(-halfSize.X, halfSize.Y);
			break;
		case Enums::UIAnchor_MiddleLeft:
			calculatedPosition = position + MMath::Vector2(halfSize.X, 0.0f);
			break;
		case Enums::UIAnchor_Middle:
			calculatedPosition = position;
			break;
		case Enums::UIAnchor_MiddleRight:
			calculatedPosition = position + MMath::Vector2(-halfSize.X, 0.0f);
			break;
		case Enums::UIAnchor_BottomLeft:
			calculatedPosition = position + MMath::Vector2(halfSize.X, -halfSize.Y);
			break;
		case Enums::UIAnchor_Bottom:
			calculatedPosition = position + MMath::Vector2(0.0f, -halfSize.Y);
			break;
		case Enums::UIAnchor_BottomRight:
			calculatedPosition = position + MMath::Vector2(-halfSize.X, -halfSize.Y);
			break;
		}
	}

	MMath::Vector2 ModAPI::GUIFramework::GUIElement::GetSize() const
	{ return size; }
}
