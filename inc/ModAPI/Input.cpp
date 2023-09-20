#include <natives.h>

#include "Input.h"

namespace ModAPI::Input
{
	bool IsEnabled(const Enums::eControlType controlType, const eControl inputAction)
	{
		return PAD::IS_CONTROL_ENABLED(controlType, inputAction);
	}

	bool IsPressed(const Enums::eControlType controlType, const eControl inputAction)
	{
		return PAD::IS_CONTROL_JUST_PRESSED(controlType, inputAction) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(controlType, inputAction);
	}

	bool IsReleased(const Enums::eControlType controlType, const eControl inputAction)
	{
		return PAD::IS_CONTROL_JUST_RELEASED(controlType, inputAction) || PAD::IS_DISABLED_CONTROL_JUST_RELEASED(controlType, inputAction);
	}

	float GetAxis(const Enums::eControlType controlType, const eControl inputAction)
	{
		return PAD::GET_CONTROL_NORMAL(controlType, inputAction);
	}

	float GetAxisUnbound(const Enums::eControlType controlType, const eControl inputAction)
	{
		return PAD::GET_CONTROL_UNBOUND_NORMAL(controlType, inputAction);
	}

	void Rumble(const Enums::eControlType controlType, const float duration, const int frequency)
	{
		PAD::SET_CONTROL_SHAKE(controlType, static_cast<int>(duration * 1000.0f), frequency);
	}

	void StopRumble(const Enums::eControlType controlType)
	{
		PAD::STOP_CONTROL_SHAKE(controlType);
	}

	void SetAction(const Enums::eControlType controlType, const eControl inputAction, const bool enable)
	{
		if(enable)
		{
			PAD::ENABLE_CONTROL_ACTION(controlType, inputAction, enable);
		}
		else
		{
			PAD::DISABLE_CONTROL_ACTION(controlType, inputAction, enable);
		}
	}

	void SetAllActions(const Enums::eControlType controlType, const bool enable)
	{
		if (enable)
		{
			PAD::ENABLE_ALL_CONTROL_ACTIONS(controlType);
		}
		else
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(controlType);
		}
	}

	void SetExclusive(const Enums::eControlType controlType, const bool enable)
	{
		PAD::SET_INPUT_EXCLUSIVE(controlType, enable);
	}

	std::string VkCodeToStr(UINT8 key)
	{
		return ""; // TODO: Implement
	}

	std::string GetUserString(const std::string& title, const std::string& defaultText, const int maxLength)
	{
		MISC::DISPLAY_ONSCREEN_KEYBOARD(true, "", "", defaultText.c_str(), "", "", "", maxLength);
		while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0)
		{
			HUD::SET_TEXT_FONT(0);
			HUD::SET_TEXT_SCALE(0.34f, 0.34f);
			HUD::SET_TEXT_COLOUR(255, 255, 255, 255);
			HUD::SET_TEXT_WRAP(0.0f, 1.0f);
			HUD::SET_TEXT_RIGHT_JUSTIFY(FALSE);
			HUD::SET_TEXT_CENTRE(TRUE);
			HUD::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			HUD::SET_TEXT_EDGE(0, 0, 0, 0, 0);
			HUD::SET_TEXT_OUTLINE();

			if (HUD::DOES_TEXT_LABEL_EXIST(title.c_str()))
			{
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			}
			else if(title.length() < 100)
			{
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(title.c_str());
			}
			else
			{
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("jamyfafi");

				constexpr UINT8 maxStrComponentLength = 99;
				for (int i = 0; i < title.length(); i += maxStrComponentLength)
				{
					const std::string& strComp = title.substr(i, min(title.length() - i, maxStrComponentLength));
					HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(strComp.c_str());
				}
			}

			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(0.5f, 0.37f, 0);
			WAIT(0);
		}

		return MISC::GET_ONSCREEN_KEYBOARD_RESULT();
	}
}
