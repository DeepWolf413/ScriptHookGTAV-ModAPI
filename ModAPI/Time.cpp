#include "Time.h"

#include <chrono>
#include <shsdk/natives.h>

using namespace std::chrono;

int ModAPI::Time::GetGameTimeMs()
{ return MISC::GET_GAME_TIMER(); }

uint64_t ModAPI::Time::GetSystemTimeMs()
{ return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count(); }

void ModAPI::Time::SetTimeScale(const float newTimeScale)
{ MISC::SET_TIME_SCALE(newTimeScale); }

bool ModAPI::Time::IsPastGameTime(const int timeToCheck)
{ return timeToCheck >= GetGameTimeMs(); }

bool ModAPI::Time::IsPastSystemTime(const uint64_t timeToCheck)
{ return timeToCheck >= GetSystemTimeMs(); }