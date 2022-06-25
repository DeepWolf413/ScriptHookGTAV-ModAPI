#include "Ped.h"

#include <iostream>
#include <memory>
#include <string>

#include "Vehicle.h"
#include <shsdk/natives.h>

#include "StdUtils.h"
#include "Time.h"

ModAPI::Ped::Ped() : Ped(NULL)
{}

ModAPI::Ped::Ped(const PedHandle pedToRepresent) : Entity(pedToRepresent), tasker(*this)
{}

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

bool ModAPI::Ped::IsHuman() const
{ return PED::IS_PED_HUMAN(handle); }

bool ModAPI::Ped::IsAnimal() const
{ return !PED::IS_PED_HUMAN(handle); }

bool ModAPI::Ped::IsOnVehicle() const
{ return PED::IS_PED_ON_VEHICLE(handle); }

bool ModAPI::Ped::IsOnMount() const
{ return PED::IS_PED_ON_MOUNT(handle); }

bool ModAPI::Ped::IsOnFoot() const
{ return PED::IS_PED_ON_FOOT(handle); }

bool ModAPI::Ped::IsInAnyVehicle() const
{ return PED::IS_PED_SITTING_IN_ANY_VEHICLE(handle); }

bool ModAPI::Ped::IsInVehicle(VehicleHandle vehicleHandle) const
{ return PED::IS_PED_SITTING_IN_VEHICLE(handle, vehicleHandle); }

bool ModAPI::Ped::IsUsingAnyScenario() const
{ return PED::IS_PED_USING_ANY_SCENARIO(handle); }

bool ModAPI::Ped::IsUsingScenario(const std::string& scenarioName) const
{ return PED::IS_PED_USING_SCENARIO(handle, scenarioName.c_str()); }

bool ModAPI::Ped::IsRagdoll() const
{ return PED::IS_PED_RAGDOLL(handle); }

ModAPI::Vehicle ModAPI::Ped::GetVehicle(const bool includeLastVehicle) const
{ return {PED::GET_VEHICLE_PED_IS_IN(handle, includeLastVehicle)}; }

std::unique_ptr<ModAPI::Ped> ModAPI::Ped::GetTarget() const
{
	const PedHandle target = PED::_GET_PED_TASK_COMBAT_TARGET(handle, 0);
	if(target == NULL)
	{ return nullptr; }
	
	return std::make_unique<Ped>(target);
}

int ModAPI::Ped::GetTimeOfDeath() const
{ return PED::GET_PED_TIME_OF_DEATH(handle); }

float ModAPI::Ped::GetTimeSinceDeath() const
{ return static_cast<float>(Time::GetGameTimeMs() - GetTimeOfDeath()) / 1000.0f; }

ModAPI::Ped ModAPI::Ped::GetKiller() const
{
	if(IsAlive())
	{ return NULL; }

	const auto killer = Ped(PED::GET_PED_SOURCE_OF_DEATH(handle));
	if(GetType() != eEntityType::Ped || !killer.Exists())
	{ return NULL; }

	return killer;
}

void ModAPI::Ped::SetShootAccuracy(const int accuracy) const
{ PED::SET_PED_ACCURACY(handle, accuracy); }

void ModAPI::Ped::SetCombatAttribute(const eCombatAttribute attribute, const bool enabled) const
{ PED::SET_PED_COMBAT_ATTRIBUTES(handle, static_cast<int>(attribute), enabled); }

void ModAPI::Ped::SetConfigFlag(const ePedConfigFlags flagId, const bool enabled) const
{ PED::SET_PED_CONFIG_FLAG(handle, flagId, enabled); }

void ModAPI::Ped::SetBlockEvents(const bool blockEvents) const
{ PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(handle, blockEvents); }

void ModAPI::Ped::SetRelationshipGroup(const Hash groupHash) const
{ PED::SET_PED_RELATIONSHIP_GROUP_HASH(handle, groupHash); }

void ModAPI::Ped::SetDefaultRelationshipGroup(const Hash groupHash) const
{ PED::SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(handle, groupHash); }

eRelationship ModAPI::Ped::GetRelationship(const Ped& otherPed) const
{ return static_cast<eRelationship>(PED::GET_RELATIONSHIP_BETWEEN_PEDS(handle, otherPed.GetHandle())); }

Hash ModAPI::Ped::GetDefaultRelationshipGroup() const
{ return PED::GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(handle); }

Hash ModAPI::Ped::GetRelationshipGroupHash() const
{ return PED::GET_PED_RELATIONSHIP_GROUP_HASH(handle); }

int ModAPI::Ped::GetBoneIndex(const eBoneIds boneId) const
{ return PED::GET_PED_BONE_INDEX(handle, boneId); }

Vector3 ModAPI::Ped::GetBonePosition(const eBoneIds boneId, const Vector3& offset) const
{ return PED::GET_PED_BONE_COORDS(handle, static_cast<int>(boneId), offset); }

bool ModAPI::Ped::GetLastDamageBone(eBoneIds& boneId) const
{
	int outBoneId = -1;
	const bool wasSomethingHit = PED::GET_PED_LAST_DAMAGE_BONE(handle, &outBoneId);
	boneId = static_cast<eBoneIds>(outBoneId);
	return wasSomethingHit;
}

void ModAPI::Ped::ClearLastDamageBone() const
{ PED::CLEAR_PED_LAST_DAMAGE_BONE(handle); }

void ModAPI::Ped::ClearTasksImmediately() const
{ TASK::CLEAR_PED_TASKS_IMMEDIATELY(handle); }

void ModAPI::Ped::EquipBestWeapon() const
{
	const auto pedBestWeapon = WEAPON::GET_BEST_PED_WEAPON(handle, false);
	EquipWeapon(pedBestWeapon);
}

void ModAPI::Ped::EquipWeapon(const Hash weaponHash) const
{
	if (!WEAPON::IS_WEAPON_VALID(weaponHash))
	{
		// TODO: Log error "Can't equip weapon because the weapon hash (" + std::to_string(weaponHash) + ") is invalid.".
		return;
	}

	if (!HasWeapon(weaponHash))
	{ return; }

	WEAPON::SET_CURRENT_PED_WEAPON(handle, weaponHash, true);
}

void ModAPI::Ped::GiveWeapon(const Hash weaponHash, const int ammoCount, const bool forceInHand, const bool forceInHolster) const
{
	if(HasWeapon(weaponHash))
	{ return; }
	
	WEAPON::GIVE_WEAPON_TO_PED(handle, weaponHash, ammoCount, forceInHolster, forceInHand);
}

void ModAPI::Ped::EquipRandomProps() const
{ PED::SET_PED_RANDOM_PROPS(handle); }

void ModAPI::Ped::EquipRandomComponentVariation() const
{ PED::SET_PED_RANDOM_COMPONENT_VARIATION(handle, 0); }

void ModAPI::Ped::ClearProps() const
{ PED::CLEAR_ALL_PED_PROPS(handle); }

void ModAPI::Ped::EquipDefaultComponentVariation() const
{ PED::SET_PED_DEFAULT_COMPONENT_VARIATION(handle); }

bool ModAPI::Ped::HasWeapon(const Hash weaponHash) const
{ return WEAPON::HAS_PED_GOT_WEAPON(handle, weaponHash, false); }

void ModAPI::Ped::RemoveAllWeapons() const
{ WEAPON::REMOVE_ALL_PED_WEAPONS(handle, true); }

const ModAPI::Tasker& ModAPI::Ped::GetTasker() const
{ return tasker; }

std::unique_ptr<ModAPI::Ped> ModAPI::Ped::SpawnPed(const std::string& modelName, const Vector3& spawnPosition, const float heading, const int outfitNumber)
{ return SpawnPed(ePedType::PedTypeMission, modelName, spawnPosition, heading, outfitNumber); }


std::unique_ptr<ModAPI::Ped> ModAPI::Ped::SpawnPed(const ePedType pedType, const std::string& modelName, const Vector3& spawnPosition, const float heading, const int outfitNumber)
{
	if(modelName.empty())
	{
		// TODO: Log error "Failed to SpawnPed(). The given model name is empty.".
		return nullptr;
	}
	
	const auto model = std::make_unique<Model>(modelName);
	if(!model->Request(2000))
	{ return nullptr; }

	const PedHandle spawnedPedHandle = PED::CREATE_PED(static_cast<int>(pedType), model->GetHash(), spawnPosition.X, spawnPosition.Y, spawnPosition.Z, heading, false, false);
	if(spawnedPedHandle == NULL)
	{
		// TODO: Log error "Failed to spawn ped.".
		return nullptr;
	}

	auto spawnedPed = std::make_unique<Ped>(spawnedPedHandle);
	spawnedPed->modelName = modelName;

	// TODO: Implement when outfit system is done again.
	/*if(outfitNumber < 0)
	{ spawnedPed->SetRndOutfit(); }
	else
	{ spawnedPed->SetOutfit(outfitNumber); }*/
	
	return std::move(spawnedPed);
}
