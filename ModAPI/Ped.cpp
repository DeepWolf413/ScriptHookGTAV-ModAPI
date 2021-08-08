#include "Ped.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Model.h"
#include "Tasker.h"
#include "Vehicle.h"
#include <inc/natives.h>

#include "Screen.h"
#include "stdUtils.h"

ModAPI::Ped::Ped(const PedHandle pedToRepresent) : Entity(pedToRepresent)
{ this->tasker = std::make_unique<Tasker>(this); }

std::string ModAPI::Ped::GetModelName() const
{ return modelName; }

bool ModAPI::Ped::IsInCombat() const
{
	const auto targetPed = GetTarget();
	if(targetPed == nullptr)
	{ return false; }
	
	return PED::IS_PED_IN_COMBAT(handle, targetPed->GetHandle());
}

bool ModAPI::Ped::IsInMeleeCombat() const
{ return PED::IS_PED_IN_MELEE_COMBAT(handle); }

bool ModAPI::Ped::IsShooting() const
{ return PED::IS_PED_SHOOTING(handle); }

bool ModAPI::Ped::IsHorse() const
{ return PED::_IS_THIS_MODEL_A_HORSE(GetModel()); }

bool ModAPI::Ped::IsHuman() const
{ return PED::IS_PED_HUMAN(handle); }

bool ModAPI::Ped::IsOnVehicle() const
{ return PED::IS_PED_ON_VEHICLE(handle, false); }

bool ModAPI::Ped::IsOnMount() const
{ return PED::IS_PED_ON_MOUNT(handle); }

bool ModAPI::Ped::IsOnFoot() const
{ return PED::IS_PED_ON_FOOT(handle); }

bool ModAPI::Ped::IsUsingAnyScenario() const
{ return PED::IS_PED_USING_ANY_SCENARIO(handle); }

bool ModAPI::Ped::IsUsingScenario(const Hash scenarioHash) const
{ return PED::IS_PED_USING_SCENARIO_HASH(handle, scenarioHash); }

std::unique_ptr<ModAPI::Ped> ModAPI::Ped::GetTarget() const
{
	const PedHandle target = PED::GET_CURRENT_TARGET_FOR_PED(handle);
	if(target == NULL)
	{ return nullptr; }
	
	return std::make_unique<Ped>(target);
}

int ModAPI::Ped::GetTimeOfDeath() const
{ return PED::GET_PED_TIME_OF_DEATH(handle); }

float ModAPI::Ped::GetTimeSinceDeath() const
{ return (MISC::GET_GAME_TIMER() - GetTimeOfDeath()) / 1000.0f; }

::PedHandle ModAPI::Ped::GetKiller() const
{
	if(IsAlive())
	{ return NULL; }

	const auto killer = PED::GET_PED_SOURCE_OF_DEATH(handle);
	if(!ENTITY::IS_ENTITY_A_PED(handle) || !ENTITY::DOES_ENTITY_EXIST(killer))
	{ return NULL; }

	return killer;
}

void ModAPI::Ped::SetShootAccuracy(const int accuracy) const
{ PED::SET_PED_ACCURACY(handle, accuracy); }

void ModAPI::Ped::SetOutfit(const int newOutfit)
{
	PED::_SET_PED_OUTFIT_PRESET(handle, newOutfit, true);
		
	if (GetModel() == 0xB69710) // Player_Three (John)
	{ PED::_APPLY_SHOP_ITEM_TO_PED(handle, static_cast<Hash>(0x87BB07E7), true, false, true); }

	PED::_UPDATE_PED_VARIATION(handle, false, true, true, true, false);
	currentOutfit = newOutfit;
}

void ModAPI::Ped::SetToNextOutfit()
{
	int nextOutfit = GetCurrentOutfit() + 1;
	if(nextOutfit > GetMaxOutfit())
	{ nextOutfit = 0; }

	SetOutfit(nextOutfit);
	
	const std::string subtitleText = "Outfit " + std::to_string(currentOutfit) + " / " + std::to_string(GetMaxOutfit());
	Screen::PrintSubtitle(subtitleText.c_str());
}

void ModAPI::Ped::SetToPreviousOutfit()
{
	int previousOutfit = GetCurrentOutfit() - 1;
	if(previousOutfit < 0)
	{ previousOutfit = GetMaxOutfit(); }

	SetOutfit(previousOutfit);

	const std::string subtitleText = "Outfit " + std::to_string(currentOutfit) + " / " + std::to_string(GetMaxOutfit());
	Screen::PrintSubtitle(subtitleText.c_str());
}

void ModAPI::Ped::ResetOutfit()
{
	SetOutfit(0);
	
	const std::string subtitleText = "Outfit " + std::to_string(currentOutfit) + " / " + std::to_string(GetMaxOutfit());
	Screen::PrintSubtitle(subtitleText.c_str());
}

void ModAPI::Ped::SetRndOutfit()
{
	const int rndNumber = MISC::GET_RANDOM_INT_IN_RANGE(0, GetMaxOutfit());
	SetOutfit(rndNumber);
}

void ModAPI::Ped::SetCombatAttribute(const eCombatAttribute attribute, const bool enabled) const
{ PED::SET_PED_COMBAT_ATTRIBUTES(handle, static_cast<int>(attribute), enabled); }

void ModAPI::Ped::SetConfigFlag(const int flagId, const bool enabled) const
{ PED::SET_PED_CONFIG_FLAG(handle, flagId, enabled); }

void ModAPI::Ped::SetBlockEvents(const bool blockEvents) const
{ PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(handle, blockEvents); }

void ModAPI::Ped::SetRelationshipGroup(const Hash groupHash) const
{ PED::SET_PED_RELATIONSHIP_GROUP_HASH(handle, groupHash); }

int ModAPI::Ped::GetCurrentOutfit() const
{ return currentOutfit; }

int ModAPI::Ped::GetMaxOutfit() const
{ return PED::GET_NUM_META_PED_OUTFITS(handle) - 1; }

void ModAPI::Ped::ClearTasksImmediately() const
{ TASK::CLEAR_PED_TASKS_IMMEDIATELY(handle, false, true); }

void ModAPI::Ped::EquipBestWeapon() const
{
	const auto pedBestWeapon = WEAPON::GET_BEST_PED_WEAPON(handle, false, false);
	WEAPON::SET_CURRENT_PED_WEAPON(handle, pedBestWeapon, true, WEAPON_ATTACH_POINT_HAND_PRIMARY, false, false);
}

void ModAPI::Ped::EquipWeapon(const Hash weaponHash) const
{ EquipWeapon(weaponHash, WEAPON_ATTACH_POINT_HAND_PRIMARY); }

void ModAPI::Ped::EquipWeapon(const Hash weaponHash, const eWeaponAttachPoint attachPoint) const
{
	if(!WEAPON::IS_WEAPON_VALID(weaponHash))
	{
		// TODO: Log error "Can't equip weapon because the weapon hash (" + std::to_string(weaponHash) + ") is invalid.".
		return;
	}

	if(!HasWeapon(weaponHash))
	{ return; }
	
	WEAPON::SET_CURRENT_PED_WEAPON(handle, weaponHash, true, attachPoint, false, false);
}

void ModAPI::Ped::GiveWeapon(const Hash weaponHash, const int ammoCount, const bool forceInHand, const bool forceInHolster, const bool allowMultipleCopies) const
{
	if(!allowMultipleCopies && HasWeapon(weaponHash))
	{ return; }
	
	auto attachPoint = WEAPON_ATTACH_POINT_HAND_PRIMARY;
	if(forceInHolster)
	{
		if(WEAPON::IS_WEAPON_BOW(weaponHash))
		{ attachPoint = WEAPON_ATTACH_POINT_BOW; }
		else if(WEAPON::_IS_WEAPON_TWO_HANDED(weaponHash))
		{ attachPoint = WEAPON_ATTACH_POINT_RIFLE; }
		else if(WEAPON::_IS_WEAPON_THROWABLE(weaponHash))
		{ attachPoint = WEAPON_ATTACH_POINT_THROWER; }
		else
		{ attachPoint = WEAPON_ATTACH_POINT_PISTOL_R; }
	}
	
	WEAPON::GIVE_WEAPON_TO_PED(handle, weaponHash, ammoCount, forceInHand, forceInHolster, attachPoint, allowMultipleCopies, 0.5f, 1.0f, ADD_REASON_DEFAULT, true, 0.0f, false);
}

bool ModAPI::Ped::HasWeapon(const Hash weaponHash) const
{ return WEAPON::HAS_PED_GOT_WEAPON(handle, weaponHash, 0, false); }

void ModAPI::Ped::RemoveAllWeapons() const
{ WEAPON::REMOVE_ALL_PED_WEAPONS(handle, true, true); }

ModAPI::Tasker* ModAPI::Ped::GetTasker() const
{ return tasker.get(); }

std::unique_ptr<ModAPI::Ped> ModAPI::Ped::SpawnPed(const std::string modelName, const Vector3 spawnPosition, const float heading, const int outfitNumber)
{
	if(PED::_GET_NUM_FREE_SLOTS_IN_PED_POOL() <= 0)
	{
		// TODO: Log error "Can't spawn ped due to no free slots in the game's ped pool.".
		return nullptr;
	}

	if(modelName.empty())
	{
		// TODO: Log error "Failed to SpawnPed(). The given model name is empty.".
		return nullptr;
	}
	
	const auto model = std::make_unique<Model>(modelName);
	if(!model->Request(2000))
	{ return nullptr; }

	const ::PedHandle spawnedPedHandle = PED::CREATE_PED(model->GetHash(), spawnPosition.x, spawnPosition.y, spawnPosition.z, heading, false, false, false, false);
	if(spawnedPedHandle == NULL)
	{
		// TODO: Log error "Failed to spawn ped.".
		return nullptr;
	}

	auto spawnedPed = std::make_unique<Ped>(spawnedPedHandle);
	spawnedPed->modelName = Utils::StdUtils::ToLower(modelName);

	if(outfitNumber < 0)
	{ spawnedPed->SetRndOutfit(); }
	else
	{ spawnedPed->SetOutfit(outfitNumber); }
	
	return std::move(spawnedPed);
}
