#include "Time.h"

#include <chrono>
#include <shsdk/natives.h>

int ModAPI::Time::GetGameTimeMs()
{ return MISC::GET_GAME_TIMER(); }

uint64_t ModAPI::Time::GetSystemTimeMs()
{ return duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); }
