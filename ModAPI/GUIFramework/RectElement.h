#pragma once

#include "GUIElement.h"

namespace ModAPI::GUIFramework
{
	class RectElement : public GUIElement
	{
	public:
		RectElement() = default;
		RectElement(const Vector2& position, const Vector2& size);
		RectElement(const Vector2& position, const Vector2& size, eGUIElementAnchor anchor);
		
		void Draw() override;
	};
}
