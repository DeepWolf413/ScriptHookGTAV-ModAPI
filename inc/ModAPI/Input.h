#pragma once

#include <enums.h>
#include <string>

#include "Enums.h"

namespace ModAPI::Input
{
    bool IsEnabled(Enums::eControlType controlType, eControl inputAction);
    bool IsPressed(Enums::eControlType controlType, eControl inputAction);
    bool IsReleased(Enums::eControlType controlType, eControl inputAction);
    float GetAxis(Enums::eControlType controlType, eControl inputAction);
    float GetAxisUnbound(Enums::eControlType controlType, eControl inputAction);
    void Rumble(Enums::eControlType controlType, float duration = 0.2f, int frequency = 100);
    void StopRumble(Enums::eControlType controlType);
    void SetAction(Enums::eControlType controlType, eControl inputAction, bool enable);
    void SetAllActions(Enums::eControlType controlType, bool enable);
    void SetExclusive(Enums::eControlType controlType, bool enable);
    [[nodiscard]] std::string VkCodeToStr(UINT8 key);
    [[nodiscard]] std::string GetUserString(const std::string& title, const std::string& defaultText = "", int maxLength = 255);
}
