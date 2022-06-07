#pragma once

#include <string>

#include "shsdk/enums.h"

namespace ModAPI::Input
{
    enum ePadType
    {
        Player = 0,
        Frontend = 2
    };

    bool IsEnabled(ePadType padType, eControl control);
    bool IsPressed(ePadType padType, eControl control);
    bool IsReleased(ePadType padType, eControl control);
    float GetAxis(ePadType padType, eControl control);
    float GetAxisUnbound(ePadType padType, eControl control);
    void Rumble(ePadType padType, float duration = 0.2f, int frequency = 100);
    void StopRumble(ePadType padType);
    void SetAction(ePadType padType, eControl control, bool enable);
    void SetAllActions(ePadType padType, bool enable);
    void SetExclusive(ePadType padType, bool enable);
    [[nodiscard]] std::string VkCodeToStr(UINT8 key);
}
