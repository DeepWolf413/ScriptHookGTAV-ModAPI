#include "SpriteElement.h"

#include "../UI.h"
#include "../Streaming.h"
#include "natives.h"

ModAPI::GUIFramework::SpriteElement::SpriteElement(const std::string& category, const std::string& sprite,
                                                   const MMath::Vector2& position, const MMath::Vector2& size)
	: SpriteElement(category, sprite, position, size, TopLeft)
{
}

ModAPI::GUIFramework::SpriteElement::SpriteElement(const std::string& category, const std::string& sprite,
                                                   const MMath::Vector2& position, const MMath::Vector2& size,
                                                   const eGUIElementAnchor anchor)
	: GUIElement(position, size, anchor)
{
	SpriteElement::SetSprite(category, sprite);
	SpriteElement::CalculatePosition();
}

ModAPI::GUIFramework::SpriteElement::~SpriteElement()
{
	CleanUp();
}

void ModAPI::GUIFramework::SpriteElement::Draw()
{
	if (spriteCategory.empty() || spriteName.empty() || !Streaming::TryRequestTextureDict(spriteCategory))
	{
		return;
	}

	GRAPHICS::DRAW_SPRITE(spriteCategory.c_str(), spriteName.c_str(), calculatedPosition.X, calculatedPosition.Y,
	                      size.X, size.Y, 0.0f, color.R, color.G, color.B, color.A, 0, 0);
}

void ModAPI::GUIFramework::SpriteElement::SetSprite(const std::string& category, const std::string& sprite)
{
	CleanUp();

	spriteCategory = category;
	spriteName = sprite;
}

void ModAPI::GUIFramework::SpriteElement::CleanUp() const
{
	if (!spriteCategory.empty() && Streaming::HasTextureDictLoaded(spriteCategory))
	{
		Streaming::MarkTextureDictAsNoLongerNeeded(spriteCategory);
	}
}
