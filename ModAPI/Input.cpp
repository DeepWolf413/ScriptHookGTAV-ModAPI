#include <shsdk/main.h>
#include <shsdk/natives.h>

#include "Input.h"

std::vector<std::unique_ptr<ModAPI::InputData>> ModAPI::Input::registeredInputs;

ModAPI::InputData::InputData(eControl control)
{
	this->control = control;
	this->holdStartTime = 0;
	this->holdEndTime = 0;
}

eControl ModAPI::InputData::GetControl() const
{ return control; }

bool ModAPI::InputData::IsPressed()
{
	bool isPressed = PAD::IS_CONTROL_JUST_PRESSED(0, control) || PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, control);
	if (isPressed)
	{
		// Deregister input immediately because it's just a press.
		Input::DeregisterInput(control);
	}

	return isPressed;
}

bool ModAPI::InputData::IsReleased()
{
	const bool isReleased = PAD::IS_CONTROL_JUST_RELEASED(0, control) || PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, control);
	if (isReleased)
	{
		holdEndTime = MISC::GET_GAME_TIMER();
		Input::DeregisterInput(this);
	}

	return isReleased;
}

bool ModAPI::InputData::IsHeld()
{
	const bool isHeld = PAD::IS_CONTROL_PRESSED(0, control) || PAD::IS_DISABLED_CONTROL_PRESSED(0, control);
	
	if (isHeld && !HasStartTimeBeenSet())
	{ holdStartTime = MISC::GET_GAME_TIMER(); }

	// Checking if the input is released to make sure it gets deregistered if that's the case. Note: The IsReleased function deregisters if the control is released.
	if (IsReleased())
	{ return false; }

	return isHeld;
}

float ModAPI::InputData::GetHeldTime() const
{ return (holdStartTime == 0 ? 0 : holdStartTime < holdEndTime ? holdEndTime - holdStartTime : MISC::GET_GAME_TIMER() - holdStartTime) / 1000.0f; }

bool ModAPI::InputData::HasStartTimeBeenSet() const
{ return holdStartTime > 0; }

ModAPI::InputData* ModAPI::Input::GetControl(eControl control)
{
	auto [foundRegisteredInput, inputData] = TryGetRegisteredInput(control);
	if (foundRegisteredInput)
	{ return inputData; }

	return RegisterInput(std::make_unique<ModAPI::InputData>(control));
}


ModAPI::InputData* ModAPI::Input::RegisterInput(std::unique_ptr<ModAPI::InputData> inputToRegister)
{
	registeredInputs.push_back(std::move(inputToRegister));
	return registeredInputs[registeredInputs.size() - 1].get();
}

void ModAPI::Input::DeregisterInput(ModAPI::InputData* inputToDeregister)
{
	for each (auto& registeredInput in registeredInputs)
	{
		if (registeredInput.get() == inputToDeregister)
		{
			registeredInputs.erase(std::remove(registeredInputs.begin(), registeredInputs.end(), registeredInput), registeredInputs.end());
			return;
		}
	}
}

void ModAPI::Input::DeregisterInput(eControl inputToDeregister)
{
	auto [foundRegisteredInput, inputData] = TryGetRegisteredInput(inputToDeregister);
	if (foundRegisteredInput)
	{ DeregisterInput(inputData); }
}

std::tuple<bool, ModAPI::InputData*> ModAPI::Input::TryGetRegisteredInput(eControl control)
{
	for each (auto& input in registeredInputs)
	{
		if (input->GetControl() == control)
		{ return std::make_tuple(true, input.get()); }
	}

	return std::make_tuple(false, nullptr);
}

bool ModAPI::Input::IsInputAlreadyRegistered(eControl control)
{
	for each (auto& input in registeredInputs)
	{
		if (input->GetControl() == control)
		{ return true; }
	}

	return false;
}
