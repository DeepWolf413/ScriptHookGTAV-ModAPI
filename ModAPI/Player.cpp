#include "Player.h"

#include <memory>
#include <shsdk/natives.h>

#include "Ped.h"

int ModAPI::Player::GetId()
{ return PLAYER::GET_PLAYER_INDEX(); }

std::unique_ptr<ModAPI::Ped> ModAPI::Player::GetPed()
{ return std::make_unique<ModAPI::Ped>(PLAYER::GET_PLAYER_PED(GetId())); }
