#pragma once

#ifndef PLAYER_H
#define PLAYER_H
#include <memory>

namespace ModAPI {
	class Ped;
}

namespace ModAPI
{
	namespace PlayerUtils
	{
		int GetPlayerId();
		std::unique_ptr<ModAPI::Ped> GetPlayerPed();
	}
}

#endif