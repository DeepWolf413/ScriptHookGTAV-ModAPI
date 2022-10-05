#pragma once

#include "GUIElement.h"

namespace ModAPI::GUIFramework
{
	class RectElement : public GUIElement
	{
	public:
		RectElement() = default;
		RectElement(const ModAPI::MMath::Vector2& position, const ModAPI::MMath::Vector2& size);
		RectElement(const ModAPI::MMath::Vector2& position, const ModAPI::MMath::Vector2& size, Enums::eUIAnchor anchor);
		
		void Draw() override;
	};
}
