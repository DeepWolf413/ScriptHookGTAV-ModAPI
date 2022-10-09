#include "InstructionalButtons.h"

#include <natives.h>

#include "../InputAPI.h"
#include "../MathAPI.h"
#include "../UI.h"

namespace ModAPI::UI
{
	std::string InstructionalButton::GetKeyInstructionalButton() const
	{
		if (button == -3)
		{
			return "";
		}

		if (!isKey)
		{
			return PAD::GET_CONTROL_INSTRUCTIONAL_BUTTONS_STRING(Enums::eControlType::ControlType_Frontend, button, 1);
		}

		std::string buttonString = "t_" + Input::VkCodeToStr(button);
		return buttonString;
	}

	InstructionalButtons::InstructionalButtons()
	{
		scaleform = Scaleform();
	}

	InstructionalButtons::~InstructionalButtons()
	{
		ClearAllControls();
	}

	void InstructionalButtons::Draw()
	{
		if(buttons.empty() || MISC::UPDATE_ONSCREEN_KEYBOARD() == 0)
		{ return; }

		if (!scaleform.Load("instructional_buttons"))
		{ return; }

		scaleform.PushFunction("CLEAR_ALL");
		scaleform.PopFunction();
	
		scaleform.PushFunction("SET_MAX_WIDTH");
		scaleform.PushFloat(100.0f);
		scaleform.PopFunction();

		scaleform.PushFunction("TOGGLE_MOUSE_BUTTONS");
		scaleform.PushBoolean(true);
		scaleform.PopFunction();

		for (int i = 0; i < buttons.size(); ++i)
		{
			scaleform.PushFunction("SET_DATA_SLOT");
			scaleform.PushInteger(i);

			if (buttons[i].button >= 1000)
			{
				scaleform.PushInteger(buttons[i].button - 1000);
				scaleform.PushTextComponent(buttons[i].text);
			}
			else
			{
				scaleform.PushString2(buttons[i].GetKeyInstructionalButton());
				scaleform.PushTextComponent(buttons[i].text);
				scaleform.PushBoolean(true);
				scaleform.PushInteger(buttons[i].button);
			}
		
			scaleform.PopFunction();
		}

		scaleform.PushFunction("SET_BACKGROUND_COLOUR");
		scaleform.PushRGBA({0,0,0,80});
		scaleform.PopFunction();

		scaleform.PushFunction("DRAW_INSTRUCTIONAL_BUTTONS");
		scaleform.PushInteger(0);
		scaleform.PopFunction();

		GRAPHICS::SET_SCRIPT_GFX_ALIGN(76, 66);
		GRAPHICS::SET_SCRIPT_GFX_ALIGN_PARAMS(0.0f, 0.0f, 0.0f, 0.0f);
		GRAPHICS::RESET_SCRIPT_GFX_ALIGN();
	
		scaleform.Render2D();
	}

	void InstructionalButtons::AddControl(const eControl control, const std::string& text)
	{
		buttons.push_back({control, text, false});
	}

	void InstructionalButtons::RemoveControl(const eControl control)
	{
		// TODO: Implement InstructionalButtons::RemoveControl
		//std::erase(std::remove(buttons.begin(), buttons.end(), control), control);
	}

	void InstructionalButtons::ClearAllControls()
	{
		buttons.clear();
	}
}
