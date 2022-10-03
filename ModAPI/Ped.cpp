#include "Ped.h"

#include <iostream>
#include <memory>
#include <string>

#include "Vehicle.h"
#include <natives.h>

#include "Time.h"
#include "Math/Vector3.h"

namespace ModAPI
{
	Ped::Ped() : ModAPI::Ped(NULL)
	{}

	Ped::Ped(const ::Ped pedHandle) : ModAPI::Entity(pedHandle), tasker(*this)
	{}

	std::string Ped::GetModelName() const
	{ return modelName; }

	bool Ped::IsInCombat() const
	{
		const auto targetPed = GetTarget();
		if(targetPed == nullptr)
		{ return false; }
	
		return PED::IS_PED_IN_COMBAT(handle, targetPed->GetHandle());
	}

	bool Ped::IsInMeleeCombat() const
	{ return PED::IS_PED_IN_MELEE_COMBAT(handle); }

	bool Ped::IsShooting() const
	{ return PED::IS_PED_SHOOTING(handle); }

	bool Ped::IsHuman() const
	{ return PED::IS_PED_HUMAN(handle); }

	bool Ped::IsAnimal() const
	{ return !PED::IS_PED_HUMAN(handle); }

	bool Ped::IsOnVehicle() const
	{ return PED::IS_PED_ON_VEHICLE(handle); }

	bool Ped::IsOnMount() const
	{ return PED::IS_PED_ON_MOUNT(handle); }

	bool Ped::IsOnFoot() const
	{ return PED::IS_PED_ON_FOOT(handle); }

	bool Ped::IsInAnyVehicle() const
	{ return PED::IS_PED_SITTING_IN_ANY_VEHICLE(handle); }

	bool Ped::IsInVehicle(const ::Vehicle vehicleHandle) const
	{ return PED::IS_PED_SITTING_IN_VEHICLE(handle, vehicleHandle); }

	bool Ped::IsUsingAnyScenario() const
	{ return PED::IS_PED_USING_ANY_SCENARIO(handle); }

	bool Ped::IsUsingScenario(const std::string& scenarioName) const
	{ return PED::IS_PED_USING_SCENARIO(handle, scenarioName.c_str()); }

	bool Ped::IsRagdoll() const
	{ return PED::IS_PED_RAGDOLL(handle); }

	std::unique_ptr<ModAPI::Vehicle> Ped::GetVehicle(const bool includeLastVehicle) const
	{ return std::make_unique<ModAPI::Vehicle>(PED::GET_VEHICLE_PED_IS_IN(handle, includeLastVehicle)); }

	std::unique_ptr<ModAPI::Entity> Ped::GetTarget() const
	{
		const ::Ped targetPedHandle = PED::GET_PED_TARGET_FROM_COMBAT_PED(handle, 0);
		if(targetPedHandle == NULL)
		{ return nullptr; }
	
		return std::make_unique<Entity>(targetPedHandle);
	}

	int Ped::GetTimeOfDeath() const
	{ return PED::GET_PED_TIME_OF_DEATH(handle); }

	float Ped::GetTimeSinceDeath() const
	{ return static_cast<float>(Time::GetGameTimeMs() - GetTimeOfDeath()) / 1000.0f; }

	std::unique_ptr<ModAPI::Entity> Ped::GetKiller() const
	{
		if(IsAlive())
		{ return nullptr; }

		auto killer = std::make_unique<ModAPI::Entity>(PED::GET_PED_SOURCE_OF_DEATH(handle));
		if(GetType() != Enums::eEntityType::Ped || !killer->Exists())
		{ return nullptr; }

		return std::move(killer);
	}

	void Ped::SetShootAccuracy(const int accuracy) const
	{ PED::SET_PED_ACCURACY(handle, accuracy); }

	void Ped::SetCombatAttribute(const Enums::eCombatAttribute attribute, const bool enabled) const
	{ PED::SET_PED_COMBAT_ATTRIBUTES(handle, static_cast<int>(attribute), enabled); }

	void Ped::SetConfigFlag(const Enums::ePedConfigFlag flagId, const bool enabled) const
	{ PED::SET_PED_CONFIG_FLAG(handle, flagId, enabled); }

	void Ped::SetBlockEvents(const bool blockEvents) const
	{ PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(handle, blockEvents); }

	void Ped::SetRelationshipGroup(const Hash groupHash) const
	{ PED::SET_PED_RELATIONSHIP_GROUP_HASH(handle, groupHash); }

	void Ped::SetDefaultRelationshipGroup(const Hash groupHash) const
	{ PED::SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(handle, groupHash); }

	eRelationship Ped::GetRelationship(const ModAPI::Ped& otherPed) const
	{ return static_cast<eRelationship>(PED::GET_RELATIONSHIP_BETWEEN_PEDS(handle, otherPed.GetHandle())); }

	Hash Ped::GetDefaultRelationshipGroup() const
	{ return PED::GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(handle); }

	Hash Ped::GetRelationshipGroupHash() const
	{ return PED::GET_PED_RELATIONSHIP_GROUP_HASH(handle); }

	int Ped::GetBoneIndex(const eBone boneId) const
	{ return PED::GET_PED_BONE_INDEX(handle, boneId); }

	ModAPI::MMath::Vector3 Ped::GetBonePosition(const eBone boneId, const MMath::Vector3& offset) const
	{ return MMath::Vector3::FromSHVector3(PED::GET_PED_BONE_COORDS(handle, static_cast<int>(boneId), offset.X, offset.Y, offset.Z)); }

	bool Ped::TryGetLastDamageBone(eBone& boneId) const
	{
		int outBoneId = -1;
		const bool wasSomethingHit = PED::GET_PED_LAST_DAMAGE_BONE(handle, &outBoneId);
		boneId = static_cast<eBone>(outBoneId);
		return wasSomethingHit;
	}

	void Ped::ClearLastDamageBone() const
	{ PED::CLEAR_PED_LAST_DAMAGE_BONE(handle); }

	void Ped::ClearTasksImmediately() const
	{ TASK::CLEAR_PED_TASKS_IMMEDIATELY(handle); }

	void Ped::EquipBestWeapon() const
	{
		const auto pedBestWeapon = WEAPON::GET_BEST_PED_WEAPON(handle, false);
		EquipWeapon(pedBestWeapon);
	}

	void Ped::EquipWeapon(const Hash weaponHash) const
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

	void Ped::GiveWeapon(const Hash weaponHash, const int ammoCount, const bool forceInHand, const bool forceInHolster) const
	{
		if(HasWeapon(weaponHash))
		{ return; }
	
		WEAPON::GIVE_WEAPON_TO_PED(handle, weaponHash, ammoCount, forceInHolster, forceInHand);
	}

	void Ped::EquipRandomProps() const
	{ PED::SET_PED_RANDOM_PROPS(handle); }

	void Ped::EquipRandomComponentVariation() const
	{ PED::SET_PED_RANDOM_COMPONENT_VARIATION(handle, 0); }

	void Ped::ClearProps() const
	{ PED::CLEAR_ALL_PED_PROPS(handle); }

	void Ped::EquipDefaultComponentVariation() const
	{ PED::SET_PED_DEFAULT_COMPONENT_VARIATION(handle); }

	void Ped::RegisterTarget(const Entity& entityToRegisterAsTarget) const
	{
		PED::REGISTER_TARGET(handle, entityToRegisterAsTarget.GetHandle());
	}

	bool Ped::HasWeapon(const Hash weaponHash) const
	{ return WEAPON::HAS_PED_GOT_WEAPON(handle, weaponHash, false); }

	void Ped::RemoveAllWeapons() const
	{ WEAPON::REMOVE_ALL_PED_WEAPONS(handle, true); }

	void Ped::SetDrivingStyle(const Enums::eVehicleDrivingFlag drivingStyle) const
	{
		TASK::SET_DRIVE_TASK_DRIVING_STYLE(handle, drivingStyle);
	}

	void Ped::SetTargetLossResponse(const Enums::eTargetLossResponseType responseType) const
	{
		PED::SET_PED_TARGET_LOSS_RESPONSE(handle, responseType);
	}

	void Ped::SetCanAttackFriendly(const bool enable) const
	{
		PED::SET_CAN_ATTACK_FRIENDLY(handle, enable, false);
	}

	const Tasker& ModAPI::Ped::GetTasker() const
	{ return tasker; }

	std::unique_ptr<ModAPI::Ped> Ped::SpawnPed(const std::string& modelName, const MMath::Vector3& spawnPosition, const float heading, const int outfitNumber)
	{ return SpawnPed(Enums::ePedType::PED_TYPE_MISSION, modelName, spawnPosition, heading, outfitNumber); }


	std::unique_ptr<ModAPI::Ped> Ped::SpawnPed(const Enums::ePedType pedType, const std::string& modelName, const MMath::Vector3& spawnPosition, const float heading, const int outfitNumber)
	{
		if(modelName.empty())
		{
			// TODO: Log error "Failed to SpawnPed(). The given model name is empty.".
			return nullptr;
		}
	
		const auto model = std::make_unique<Model>(modelName);
		if(!model->Request(2000))
		{ return nullptr; }

		const ::Ped spawnedPedHandle = PED::CREATE_PED(static_cast<int>(pedType), model->GetHash(), spawnPosition.X, spawnPosition.Y, spawnPosition.Z, heading, false, false);
		if(spawnedPedHandle == NULL)
		{
			// TODO: Log error "Failed to spawn ped.".
			return nullptr;
		}

		auto spawnedPed = std::make_unique<Ped>(spawnedPedHandle);
		spawnedPed->modelName = modelName;

		return std::move(spawnedPed);
	}
}
