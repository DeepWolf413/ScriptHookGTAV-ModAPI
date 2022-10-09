#include "RectElement.h"

#include "natives.h"

namespace ModAPI::UI
{
	RectElement::RectElement(const MMath::Vector2& position, const MMath::Vector2& size)
		: RectElement(position, size, Enums::UIAnchor_TopLeft)
	{
	}

	RectElement::RectElement(const MMath::Vector2& position, const MMath::Vector2& size,
	                                               const Enums::eUIAnchor anchor)
		: UIElement(position, size, anchor)
	{
		RectElement::CalculatePosition();
	}

	void RectElement::Display()
	{
		GRAPHICS::DRAW_RECT(calculatedPosition.X, calculatedPosition.Y, size.X, size.Y, color.R, color.G, color.B, color.A,
		                    true);
	}
}
