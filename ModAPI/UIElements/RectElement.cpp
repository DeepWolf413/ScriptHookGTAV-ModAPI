#include "RectElement.h"

#include "natives.h"

namespace ModAPI::GUIFramework
{
	RectElement::RectElement(const ModAPI::MMath::Vector2& position, const ModAPI::MMath::Vector2& size)
		: RectElement(position, size, Enums::UIAnchor_TopLeft)
	{
	}

	RectElement::RectElement(const ModAPI::MMath::Vector2& position, const ModAPI::MMath::Vector2& size,
	                                               const Enums::eUIAnchor anchor)
		: GUIElement(position, size, anchor)
	{
		RectElement::CalculatePosition();
	}

	void RectElement::Draw()
	{
		GRAPHICS::DRAW_RECT(calculatedPosition.X, calculatedPosition.Y, size.X, size.Y, color.R, color.G, color.B, color.A,
		                    true);
	}
}
