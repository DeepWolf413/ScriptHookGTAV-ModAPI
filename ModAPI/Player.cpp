#include "Player.h"

#include <natives.h>

#include "Ped.h"

namespace ModAPI
{
	int Player::GetId()
	{ return PLAYER::GET_PLAYER_INDEX(); }

	ModAPI::Ped Player::GetPed()
	{ return {PLAYER::GET_PLAYER_PED(GetId())}; }

	void Player::SetInvincible(const bool enable, const bool keepRagdollEnabled)
	{
		if (keepRagdollEnabled)
		{
			PLAYER::SET_PLAYER_INVINCIBLE(GetId(), false);
			PLAYER::SET_PLAYER_INVINCIBLE_BUT_HAS_REACTIONS(GetId(), enable);
			return;
		}

		PLAYER::SET_PLAYER_INVINCIBLE_BUT_HAS_REACTIONS(GetId(), false);
		PLAYER::SET_PLAYER_INVINCIBLE(GetId(), enable);
	}
}
