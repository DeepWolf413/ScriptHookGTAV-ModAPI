#pragma once
#include <string>
#include <vector>

#include "Scaleform.h"
#include "shsdk/enums.h"

namespace ModAPI
{
	struct InstructionalButton
	{
		int button;
		std::string text;
		bool isKey;

		std::string GetKeyInstructionalButton();
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
