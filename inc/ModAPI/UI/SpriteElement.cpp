#include "SpriteElement.h"

#include "UI.h"
#include "../Streaming.h"
#include "natives.h"

namespace ModAPI::UI
{
	SpriteElement::SpriteElement(const std::string& category, const std::string& sprite,
	                                         const MMath::Vector2& position, const MMath::Vector2& size)
		: SpriteElement(category, sprite, position, size, Enums::UIAnchor_TopLeft)
	{
	}

	SpriteElement::SpriteElement(const std::string& category, const std::string& sprite,
	                                         const MMath::Vector2& position, const MMath::Vector2& size,
	                                         const Enums::eUIAnchor anchor)
		: UIElement(position, size, anchor)
	{
		SpriteElement::SetSprite(category, sprite);
		SpriteElement::CalculatePosition();
	}

	SpriteElement::~SpriteElement()
	{
		CleanUp();
	}

	void SpriteElement::Display()
	{
		if (spriteCategory.empty() || spriteName.empty() || !Streaming::TryRequestTextureDict(spriteCategory))
		{
			return;
		}

		GRAPHICS::DRAW_SPRITE(spriteCategory.c_str(), spriteName.c_str(), calculatedPosition.X, calculatedPosition.Y,
		                      size.X, size.Y, 0.0f, color.R, color.G, color.B, color.A, 0, 0);
	}

	void SpriteElement::SetSprite(const std::string& category, const std::string& sprite)
	{
		CleanUp();

		spriteCategory = category;
		spriteName = sprite;
	}

	void SpriteElement::CleanUp() const
	{
		if (!spriteCategory.empty() && Streaming::HasTextureDictLoaded(spriteCategory))
		{
			Streaming::MarkTextureDictAsNoLongerNeeded(spriteCategory);
		}
	}
}
