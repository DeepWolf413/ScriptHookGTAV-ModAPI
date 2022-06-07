#pragma once
#include <vector>

#include "../math/Vector3.h"

namespace ModAPI::GUIFramework
{
	class GUIElement;

	class GUIContainer
	{
	public:
		GUIContainer(const Vector3& position);

		void AddElement(GUIElement* elementToAdd);
		void RemoveElement(GUIElement* elementToRemove);
		void SetOpacity(float opacity);
		
	private:
		std::vector<GUIElement*> elements;
		Vector3 position;
	};
}