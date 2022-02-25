#pragma once
#include <memory>
#include <optional>
#include <vector>

#include "shsdk/enums.h"

namespace ModAPI::Input
{
    class InputData
    {
    public:
        InputData(eControl control);

        eControl GetControl() const;
        bool IsPressed() const;
        bool IsReleased();
        bool IsHeld();
        float GetHeldTime() const;

    private:
        bool HasStartTimeBeenSet() const;

        eControl control;
        int holdStartTime;
        int holdEndTime;
    };
    
    InputData* GetControl(eControl control);

    InputData* RegisterInput(std::unique_ptr<InputData> inputToRegister);
    void DeregisterInput(InputData* inputToDeregister);
    void DeregisterInput(eControl inputToDeregister);
    std::tuple<bool, InputData*> TryGetRegisteredInput(eControl control);
    bool IsInputAlreadyRegistered(eControl control);
}
