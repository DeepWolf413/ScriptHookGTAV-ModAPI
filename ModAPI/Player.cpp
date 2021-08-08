#include "Player.h"

#include <memory>
#include <inc/natives.h>

#include "Ped.h"

int ModAPI::PlayerUtils::GetPlayerId()
{ return PLAYER::GET_PLAYER_INDEX(); }

std::unique_ptr<ModAPI::Ped> ModAPI::PlayerUtils::GetPlayerPed()
{ return std::make_unique<ModAPI::Ped>(PLAYER::GET_PLAYER_PED(GetPlayerId())); }
