#pragma once
#include <cstdint>

namespace ModAPI
{
	namespace Time
	{
		int GetGameTimeMs();
		uint64_t GetSystemTimeMs();
		void SetTimeScale(float newTimeScale);
		float GetDeltaTime();

		/**
		 * \brief Checks the specified time if it is past the game time.
		 * \param timeToCheck The time in milliseconds to check
		 * \return Returns true if the specified time is past the game time, or false if behind.
		 */
		bool IsPastGameTime(int timeToCheck);

		/**
		 * \brief Checks the specified time if it is past the system time.
		 * \param timeToCheck The time in milliseconds to check
		 * \return Returns true if the specified time is past the system time, or false if behind.
		 */
		bool IsPastSystemTime(uint64_t timeToCheck);
	}
}
