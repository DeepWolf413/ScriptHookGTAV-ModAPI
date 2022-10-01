#include <natives.h>

#include "Input.h"

namespace ModAPI
{
	bool Input::IsEnabled(const ePadType padType, const eControl control)
	{
		return PAD::IS_CONTROL_ENABLED(padType, control);
	}

	bool Input::IsPressed(const ePadType padType, const eControl control)
	{
		return PAD::IS_CONTROL_JUST_PRESSED(padType, control) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(padType, control);
	}

	bool Input::IsReleased(const ePadType padType, const eControl control)
	{
		return PAD::IS_CONTROL_JUST_RELEASED(padType, control) || PAD::IS_DISABLED_CONTROL_JUST_RELEASED(padType, control);
	}

	float Input::GetAxis(const ePadType padType, const eControl control)
	{
		return PAD::GET_CONTROL_NORMAL(padType, control);
	}

	float Input::GetAxisUnbound(const ePadType padType, const eControl control)
	{
		return PAD::GET_CONTROL_UNBOUND_NORMAL(padType, control);
	}

	void Input::Rumble(const ePadType padType, const float duration, const int frequency)
	{
		PAD::SET_CONTROL_SHAKE(padType, static_cast<int>(duration * 1000.0f), frequency);
	}

	void Input::StopRumble(const ePadType padType)
	{
		PAD::STOP_CONTROL_SHAKE(padType);
	}

	void Input::SetAction(const ePadType padType, const eControl control, const bool enable)
	{
		if(enable)
		{
			PAD::ENABLE_CONTROL_ACTION(padType, control, enable);
		}
		else
		{
			PAD::DISABLE_CONTROL_ACTION(padType, control, enable);
		}
	}

	void Input::SetAllActions(const ePadType padType, const bool enable)
	{
		if (enable)
		{
			PAD::ENABLE_ALL_CONTROL_ACTIONS(padType);
		}
		else
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(padType);
		}
	}

	void Input::SetExclusive(const ePadType padType, const bool enable)
	{
		PAD::SET_INPUT_EXCLUSIVE(padType, enable);
	}

	std::string Input::VkCodeToStr(UINT8 key)
	{
		return ""; // TODO: Implement
	}
}
