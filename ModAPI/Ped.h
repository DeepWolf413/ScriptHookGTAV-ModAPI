#pragma once
#include <memory>
#include <xstring>
#include <enums.h>

#include "Entity.h"
#include "Tasker.h"

namespace ModAPI
{
	class Vehicle;

	// A convenience class for the PedHandle.
	class Ped : public ModAPI::Entity
	{
	public:
		Ped();
		Ped(::Ped pedHandle);

		static std::unique_ptr<ModAPI::Ped> SpawnPed(const std::string& modelName, const MMath::Vector3& spawnPosition, float heading,
		                                     int outfitNumber = 0);
		static std::unique_ptr<ModAPI::Ped> SpawnPed(Enums::ePedType pedType, const std::string& modelName, const MMath::Vector3& spawnPosition,
		                                     float heading, int outfitNumber = 0);

		[[nodiscard]] std::string GetModelName() const;
		[[nodiscard]] std::unique_ptr<ModAPI::Ped> GetTarget() const;

		/**
		 * \brief Gets time of death in game time milliseconds.
		 * \return the time of death in game time milliseconds.
		 */
		[[nodiscard]] int GetTimeOfDeath() const;

		/**
		 * \brief Gets the time in game time seconds that has passed since the death of the ped.
		 * \return the time in game time seconds that has passed since the death of the ped.
		 */
		[[nodiscard]] float GetTimeSinceDeath() const;
		[[nodiscard]] std::unique_ptr<ModAPI::Ped> GetKiller() const;
		[[nodiscard]] bool IsInCombat() const;
		[[nodiscard]] bool IsInMeleeCombat() const;
		[[nodiscard]] bool IsShooting() const;
		[[nodiscard]] bool IsHuman() const;
		[[nodiscard]] bool IsAnimal() const;
		[[nodiscard]] bool IsOnVehicle() const;
		[[nodiscard]] bool IsOnMount() const;
		[[nodiscard]] bool IsOnFoot() const;
		[[nodiscard]] bool IsInAnyVehicle() const;
		[[nodiscard]] bool IsInVehicle(::Vehicle vehicleHandle) const;
		[[nodiscard]] bool IsUsingAnyScenario() const;
		[[nodiscard]] bool IsUsingScenario(const std::string& scenarioName) const;
		[[nodiscard]] bool IsRagdoll() const;
		[[nodiscard]] std::unique_ptr<ModAPI::Vehicle> GetVehicle(bool includeLastVehicle = false) const;
		void SetShootAccuracy(int accuracy) const;
		void SetCombatAttribute(Enums::eCombatAttribute attribute, bool enabled) const;
		void SetConfigFlag(Enums::ePedConfigFlag flagId, bool enabled) const;
		void SetBlockEvents(bool blockEvents) const;
		void SetRelationshipGroup(Hash groupHash) const;
		void SetDefaultRelationshipGroup(Hash groupHash) const;
		[[nodiscard]] eRelationship GetRelationship(const ModAPI::Ped& otherPed) const;
		[[nodiscard]] Hash GetDefaultRelationshipGroup() const;
		[[nodiscard]] Hash GetRelationshipGroupHash() const;
		[[nodiscard]] int GetBoneIndex(eBone boneId) const;
		[[nodiscard]] MMath::Vector3 GetBonePosition(eBone boneId, const MMath::Vector3& offset) const;
		[[nodiscard]] bool TryGetLastDamageBone(eBone& boneId) const;
		void ClearLastDamageBone() const;
		void ClearTasksImmediately() const;
		void EquipBestWeapon() const;
		void EquipWeapon(Hash weaponHash) const;
		void GiveWeapon(Hash weaponHash, int ammoCount, bool forceInHand, bool forceInHolster) const;
		void EquipRandomProps() const;
		void EquipRandomComponentVariation() const;
		void ClearProps() const;
		void EquipDefaultComponentVariation() const;
		[[nodiscard]] bool HasWeapon(Hash weaponHash) const;
		void RemoveAllWeapons() const;
		[[nodiscard]] const Tasker& GetTasker() const;

	protected:
		Tasker tasker;
		std::string modelName;
	};
}
