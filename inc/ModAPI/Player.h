#pragma once
namespace ModAPI {
	class Ped;
}

namespace ModAPI::Player
{
	[[nodiscard]] int GetId();
	[[nodiscard]] ModAPI::Ped GetPed();
	void SetInvincible(bool enable, bool keepRagdollEnabled = true);
}