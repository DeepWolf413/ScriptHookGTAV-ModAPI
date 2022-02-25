#pragma once

#ifndef PLAYER_H
#define PLAYER_H
#include <memory>

namespace ModAPI {
	class Ped;
}

namespace ModAPI::Player
{
	int GetId();
	std::unique_ptr<ModAPI::Ped> GetPed();
}

#endif