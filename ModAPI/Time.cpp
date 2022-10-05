#include "Time.h"

#include <chrono>
#include <natives.h>

using namespace std::chrono;

namespace ModAPI::Time
{
    int GetGameTimeMs()
    { return MISC::GET_GAME_TIMER(); }

    uint64_t GetSystemTimeMs()
    { return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count(); }

    void SetTimeScale(const float newTimeScale)
    { MISC::SET_TIME_SCALE(newTimeScale); }

    float GetDeltaTime()
    { return 30.0f / (1.0f / SYSTEM::TIMESTEP()); }

    bool IsPastGameTime(const int timeToCheck)
    { return timeToCheck >= GetGameTimeMs(); }

    bool IsPastSystemTime(const uint64_t timeToCheck)
    { return timeToCheck >= GetSystemTimeMs(); }
}
