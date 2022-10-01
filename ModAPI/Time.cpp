#include "Time.h"

#include <chrono>
#include <natives.h>

using namespace std::chrono;

namespace ModAPI
{
    int Time::GetGameTimeMs()
    { return MISC::GET_GAME_TIMER(); }

    uint64_t Time::GetSystemTimeMs()
    { return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count(); }

    void Time::SetTimeScale(const float newTimeScale)
    { MISC::SET_TIME_SCALE(newTimeScale); }

    float Time::GetDeltaTime()
    { return 30.0f / (1.0f / SYSTEM::TIMESTEP()); }

    bool Time::IsPastGameTime(const int timeToCheck)
    { return timeToCheck >= GetGameTimeMs(); }

    bool Time::IsPastSystemTime(const uint64_t timeToCheck)
    { return timeToCheck >= GetSystemTimeMs(); }
}
