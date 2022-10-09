#include "UIElement.h"

#include <cmath>

#include "../UI.h"

namespace ModAPI::UI
{
	UIElement::UIElement(const MMath::Vector2& position, const MMath::Vector2& size)
		: UIElement(position, size, Enums::eUIAnchor::UIAnchor_TopLeft)
	{ }

	UIElement::UIElement(const MMath::Vector2& position, const MMath::Vector2& size, const Enums::eUIAnchor anchor)
	: position(position), size(size), anchor(anchor), color({255, 255, 255, 255})
	
	{}

	void UIElement::SetPosition(const MMath::Vector2& newPosition)
	{
		position = newPosition;
		CalculatePosition();
	}

	void UIElement::SetSize(const MMath::Vector2& newSize)
	{
		size = newSize;
		CalculatePosition();
	}

	void UIElement::SetAnchor(const Enums::eUIAnchor newAnchor)
	{
		anchor = newAnchor;
		CalculatePosition();
	}

	void UIElement::SetColor(const MMath::Color& newColor)
	{ color = newColor; }

	const MMath::Vector2& UIElement::GetCalculatedPosition() const
	{ return calculatedPosition; }

	const MMath::Color& UIElement::GetColor() const
	{ return color; }

	MMath::Vector2 UIElement::GetRelativePos(const MMath::Vector2& relativeOffset) const
	{
		const MMath::Vector2 cachedSize = GetSize();
		const float calculatedXOffset = std::lerp(0.0f, cachedSize.X, abs(relativeOffset.X));
		const float calculatedYOffset = std::lerp(0.0f, cachedSize.Y, abs(relativeOffset.Y));
		const auto calculatedOffset = MMath::Vector2(relativeOffset.X < 0 ? -calculatedXOffset : calculatedXOffset, relativeOffset.Y < 0 ? -calculatedYOffset : calculatedYOffset);
	
		return position + calculatedOffset;
	}

	void UIElement::CalculatePosition()
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

	MMath::Vector2 UIElement::GetSize() const
	{ return size; }
}
