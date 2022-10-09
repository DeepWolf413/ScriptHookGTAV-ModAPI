#pragma once

#include "UIElement.h"

namespace ModAPI::UI
{
	class RectElement : public UIElement
	{
	public:
		RectElement() = default;
		RectElement(const MMath::Vector2& position, const MMath::Vector2& size);
		RectElement(const MMath::Vector2& position, const MMath::Vector2& size, Enums::eUIAnchor anchor);
		
		void Display() override;
	};
}
