#pragma once
#include <memory>
#include <optional>
#include <vector>

#include "shsdk/enums.h"

namespace ModAPI
{
    class InputData
    {
    public:
        InputData(eControl control);

        eControl GetControl() const;
        bool IsPressed();
        bool IsReleased();
        bool IsHeld();
        float GetHeldTime() const;

    private:
        bool HasStartTimeBeenSet() const;

        eControl control;
        int holdStartTime;
        int holdEndTime;
    };
    
    class Input
    {
    public:
        static ModAPI::InputData* GetControl(eControl control);

        static ModAPI::InputData* RegisterInput(std::unique_ptr<ModAPI::InputData> inputToRegister);
        static void DeregisterInput(ModAPI::InputData* inputToDeregister);
        static void DeregisterInput(eControl inputToDeregister);
        static std::tuple<bool, ModAPI::InputData*> TryGetRegisteredInput(eControl control);
        static bool IsInputAlreadyRegistered(eControl control);

        static std::vector<std::unique_ptr<ModAPI::InputData>> registeredInputs;
    };
}
