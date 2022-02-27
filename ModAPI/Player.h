#pragma once

#ifndef PLAYER_H
#define PLAYER_H
#include <memory>

namespace ModAPI {
	class Ped;
}

namespace ModAPI::Player
{
	[[nodiscard]]int GetId();
	[[nodiscard]] std::unique_ptr<ModAPI::Ped> GetPed();
}

#endif