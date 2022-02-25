#include <shsdk/natives.h>

#include "Input.h"

std::vector<std::unique_ptr<ModAPI::Input::InputData>> registeredInputs;

ModAPI::Input::InputData::InputData(const eControl control)
{
	this->control = control;
	this->holdStartTime = 0;
	this->holdEndTime = 0;
}

eControl ModAPI::Input::InputData::GetControl() const
{ return control; }

bool ModAPI::Input::InputData::IsPressed() const
{
	const bool isPressed = PAD::IS_CONTROL_JUST_PRESSED(0, control) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, control);
	if (isPressed)
	{
		// Deregister input immediately because it's just a press.
		DeregisterInput(control);
	}

	return isPressed;
}

bool ModAPI::Input::InputData::IsReleased()
{
	const bool isReleased = PAD::IS_CONTROL_JUST_RELEASED(0, control) || PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, control);
	if (isReleased)
	{
		holdEndTime = MISC::GET_GAME_TIMER();
		DeregisterInput(this);
	}

	return isReleased;
}

bool ModAPI::Input::InputData::IsHeld()
{
	const bool isHeld = PAD::IS_CONTROL_PRESSED(0, control) || PAD::IS_DISABLED_CONTROL_PRESSED(0, control);
	
	if (isHeld && !HasStartTimeBeenSet())
	{ holdStartTime = MISC::GET_GAME_TIMER(); }

	// Checking if the input is released to make sure it gets deregistered if that's the case. Note: The IsReleased function deregisters if the control is released.
	if (IsReleased())
	{ return false; }

	return isHeld;
}

float ModAPI::Input::InputData::GetHeldTime() const
{ return (holdStartTime == 0 ? 0 : holdStartTime < holdEndTime ? holdEndTime - holdStartTime : MISC::GET_GAME_TIMER() - holdStartTime) / 1000.0f; }

bool ModAPI::Input::InputData::HasStartTimeBeenSet() const
{ return holdStartTime > 0; }

ModAPI::Input::InputData* ModAPI::Input::GetControl(eControl control)
{
	if (auto [foundRegisteredInput, inputData] = TryGetRegisteredInput(control); foundRegisteredInput)
	{ return inputData; }

	return RegisterInput(std::make_unique<InputData>(control));
}


ModAPI::Input::InputData* ModAPI::Input::RegisterInput(std::unique_ptr<InputData> inputToRegister)
{
	registeredInputs.push_back(std::move(inputToRegister));
	return registeredInputs[registeredInputs.size() - 1].get();
}

void ModAPI::Input::DeregisterInput(InputData* inputToDeregister)
{
	for (auto& registeredInput : registeredInputs)
	{
		if (registeredInput.get() == inputToDeregister)
		{
			std::erase(registeredInputs, registeredInput);
			return;
		}
	}
}

void ModAPI::Input::DeregisterInput(const eControl inputToDeregister)
{
	if (auto [foundRegisteredInput, inputData] = TryGetRegisteredInput(inputToDeregister); foundRegisteredInput)
	{ DeregisterInput(inputData); }
}

std::tuple<bool, ModAPI::Input::InputData*> ModAPI::Input::TryGetRegisteredInput(const eControl control)
{
	for (const auto& input : registeredInputs)
	{
		if (input->GetControl() == control)
		{ return std::make_tuple(true, input.get()); }
	}

	return std::make_tuple(false, nullptr);
}

bool ModAPI::Input::IsInputAlreadyRegistered(const eControl control)
{
	for (const auto& input : registeredInputs)
	{
		if (input->GetControl() == control)
		{ return true; }
	}

	return false;
}
