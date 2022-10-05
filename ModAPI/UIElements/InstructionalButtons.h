#pragma once
#include <enums.h>
#include <string>
#include <vector>

#include "Scaleform.h"

namespace ModAPI::GUIFramework
{
	struct InstructionalButton
	{
		int button;
		std::string text;
		bool isKey;

		[[nodiscard]] std::string GetKeyInstructionalButton() const;
	};
	
	class InstructionalButtons
	{
	public:
		InstructionalButtons();
		~InstructionalButtons();

		void Draw();
		void AddControl(eControl control, const std::string& text);
		void RemoveControl(eControl control);
		void ClearAllControls();
		
	private:
		std::vector<InstructionalButton> buttons;
		Scaleform scaleform;
	};
}
