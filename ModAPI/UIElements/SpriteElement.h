﻿#pragma once
#include <string>

#include "GUIElement.h"

namespace ModAPI::GUIFramework
{
	class SpriteElement : public GUIElement
	{
	public:
		SpriteElement() = default;
		SpriteElement(const std::string& category, const std::string& sprite, const MMath::Vector2& position, const MMath::Vector2& size);
		SpriteElement(const std::string& category, const std::string& sprite, const MMath::Vector2& position, const MMath::Vector2& size, Enums::eUIAnchor anchor);
		~SpriteElement() override;
		
		void Draw() override;
		virtual void SetSprite(const std::string& category, const std::string& sprite);
		
	protected:
		void CleanUp() const;
		
		std::string spriteCategory;
		std::string spriteName;
	};
}
