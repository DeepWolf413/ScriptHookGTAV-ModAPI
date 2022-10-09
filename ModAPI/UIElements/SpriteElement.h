#pragma once
#include <string>

#include "UIElement.h"

namespace ModAPI::UI
{
	class SpriteElement : public UIElement
	{
	public:
		SpriteElement() = default;
		SpriteElement(const std::string& category, const std::string& sprite, const MMath::Vector2& position, const MMath::Vector2& size);
		SpriteElement(const std::string& category, const std::string& sprite, const MMath::Vector2& position, const MMath::Vector2& size, Enums::eUIAnchor anchor);
		~SpriteElement() override;
		
		void Display() override;
		virtual void SetSprite(const std::string& category, const std::string& sprite);
		
	protected:
		void CleanUp() const;
		
		std::string spriteCategory;
		std::string spriteName;
	};
}
