#pragma once

#include "../Enums.h"
#include "../MathAPI.h"

namespace ModAPI::UI
{
	class UIElement
	{
	public:
		UIElement(const MMath::Vector2& position, const MMath::Vector2& size);
		UIElement(const MMath::Vector2& position, const MMath::Vector2& size, Enums::eUIAnchor anchor);
		UIElement(const UIElement& elementToCopy) = default;
		UIElement() = default;
		virtual ~UIElement() = default;

		virtual void Display() {}
		virtual void SetPosition(const MMath::Vector2& newPosition);
		virtual void SetSize(const MMath::Vector2& newSize);
		virtual void SetAnchor(Enums::eUIAnchor newAnchor);
		virtual void SetColor(const MMath::Color& newColor);
		[[nodiscard]] virtual const MMath::Vector2& GetCalculatedPosition() const;
		[[nodiscard]] const MMath::Color& GetColor() const;
		
		/**
		 * \brief Returns the actual position of the specified relative offset.
		 * \param relativeOffset The relative offset from the anchor.
		 * \return The actual position of the relative offset.
		 */
		[[nodiscard]] virtual MMath::Vector2 GetRelativePos(const MMath::Vector2& relativeOffset) const;
		
	protected:
		virtual void CalculatePosition();
		[[nodiscard]] virtual MMath::Vector2 GetSize() const;
		
		MMath::Vector2 position;
		MMath::Vector2 size;
		Enums::eUIAnchor anchor;
		MMath::Color color;
		
		/**
		 * \brief The final calculated position. This gets calculated based on the position, size, and anchor
		 */
		MMath::Vector2 calculatedPosition;
	};
}
