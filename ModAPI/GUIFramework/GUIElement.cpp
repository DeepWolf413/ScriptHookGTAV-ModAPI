#include "GUIElement.h"

#include <cmath>

#include "../Screen.h"


ModAPI::GUIFramework::GUIElement::GUIElement(const Vector2& position, const Vector2& size)
: GUIElement(position, size, eGUIElementAnchor::TopLeft)
{ }

ModAPI::GUIFramework::GUIElement::GUIElement(const Vector2& position, const Vector2& size, const eGUIElementAnchor anchor)
{
	this->position = position;
	this->size = size;
	this->anchor = anchor;
	this->color = Color(255, 255, 255, 255);
}

void ModAPI::GUIFramework::GUIElement::SetPosition(const Vector2& newPosition)
{
	position = newPosition;
	CalculatePosition();
}

void ModAPI::GUIFramework::GUIElement::SetSize(const Vector2& newSize)
{
	size = newSize;
	CalculatePosition();
}

void ModAPI::GUIFramework::GUIElement::SetAnchor(const eGUIElementAnchor newAnchor)
{
	anchor = newAnchor;
	CalculatePosition();
}

void ModAPI::GUIFramework::GUIElement::SetColor(const Color& newColor)
{ color = newColor; }

const Vector2& ModAPI::GUIFramework::GUIElement::GetCalculatedPosition() const
{ return calculatedPosition; }

const Color& ModAPI::GUIFramework::GUIElement::GetColor() const
{ return color; }

Vector2 ModAPI::GUIFramework::GUIElement::GetRelativePos(const Vector2& relativeOffset) const
{
	const Vector2 cachedSize = GetSize();
	const float calculatedXOffset = std::lerp(0.0f, cachedSize.X, abs(relativeOffset.X));
	const float calculatedYOffset = std::lerp(0.0f, cachedSize.Y, abs(relativeOffset.Y));
	const auto calculatedOffset = Vector2(calculatedXOffset, calculatedYOffset);

	if (relativeOffset.X < 0)
	{ return position - calculatedOffset; }

	return position + calculatedOffset;
}

void ModAPI::GUIFramework::GUIElement::CalculatePosition()
{
	const Vector2 halfSize = GetSize() * 0.5f;
	
	switch (anchor)
	{
		case TopLeft:
			calculatedPosition = position + halfSize;
			break;
		case Top:
			calculatedPosition = position + Vector2(0.0f, halfSize.Y);
			break;
		case TopRight:
			calculatedPosition = position + Vector2(-halfSize.X, halfSize.Y);
			break;
		case MiddleLeft:
			calculatedPosition = position + Vector2(halfSize.X, 0.0f);
			break;
		case Middle:
			calculatedPosition = position;
			break;
		case MiddleRight:
			calculatedPosition = position + Vector2(-halfSize.X, 0.0f);
			break;
		case BottomLeft:
			calculatedPosition = position + Vector2(halfSize.X, -halfSize.Y);
			break;
		case Bottom:
			calculatedPosition = position + Vector2(0.0f, -halfSize.Y);
			break;
		case BottomRight:
			calculatedPosition = position + Vector2(-halfSize.X, -halfSize.Y);
			break;
	}
}

Vector2 ModAPI::GUIFramework::GUIElement::GetSize() const
{ return size; }
