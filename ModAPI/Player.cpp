#include "Player.h"

#include <shsdk/natives.h>

#include "Ped.h"

int ModAPI::Player::GetId()
{ return PLAYER::GET_PLAYER_INDEX(); }

ModAPI::Ped ModAPI::Player::GetPed()
{ return {PLAYER::GET_PLAYER_PED(GetId())}; }

void ModAPI::Player::SetInvincible(const bool enable, const bool keepRagdollEnabled)
{
	if (keepRagdollEnabled)
	{
		PLAYER::SET_PLAYER_INVINCIBLE(GetId(), false);
		PLAYER::_SET_PLAYER_INVINCIBLE_KEEP_RAGDOLL_ENABLED(GetId(), enable);
		return;
	}

	PLAYER::_SET_PLAYER_INVINCIBLE_KEEP_RAGDOLL_ENABLED(GetId(), false);
	PLAYER::SET_PLAYER_INVINCIBLE(GetId(), enable);
}
