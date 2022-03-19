#include "RectElement.h"

#include "shsdk/natives.h"

ModAPI::GUIFramework::RectElement::RectElement(const Vector2& position, const Vector2& size)
	: RectElement(position, size, TopLeft)
{
}

ModAPI::GUIFramework::RectElement::RectElement(const Vector2& position, const Vector2& size,
                                               const eGUIElementAnchor anchor)
	: GUIElement(position, size, anchor)
{
	RectElement::CalculatePosition();
}

void ModAPI::GUIFramework::RectElement::Draw()
{
	GRAPHICS::DRAW_RECT(calculatedPosition.X, calculatedPosition.Y, size.X, size.Y, color.R, color.G, color.B, color.A,
	                    true);
}
