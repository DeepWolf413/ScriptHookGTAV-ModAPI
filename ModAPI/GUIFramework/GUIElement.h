#pragma once
#include "eGUIElementAnchor.h"
#include "../math/Color.h"
#include "../math/Vector2.h"

namespace ModAPI::GUIFramework
{
	class GUIElement
	{
	public:
		GUIElement(const Vector2& position, const Vector2& size);
		GUIElement(const Vector2& position, const Vector2& size, eGUIElementAnchor anchor);
		GUIElement() = default;
		virtual ~GUIElement() = default;

		virtual void Draw() {}
		virtual void SetPosition(const Vector2& newPosition);
		virtual void SetSize(const Vector2& newSize);
		virtual void SetAnchor(eGUIElementAnchor newAnchor);
		virtual void SetColor(const Color& newColor);
		[[nodiscard]] virtual const Vector2& GetCalculatedPosition() const;
		[[nodiscard]] const Color& GetColor() const;
		
		/**
		 * \brief Returns the actual position of the specified relative offset.
		 * \param relativeOffset The relative offset from the anchor.
		 * \return The actual position of the relative offset.
		 */
		[[nodiscard]] virtual Vector2 GetRelativePos(const Vector2& relativeOffset) const;
		
	protected:
		virtual void CalculatePosition();
		
		Vector2 position;
		Vector2 size;
		eGUIElementAnchor anchor;
		Color color;
		
		/**
		 * \brief The final calculated position. This gets calculated based on the position, size, and anchor
		 */
		Vector2 calculatedPosition;
	};
}
