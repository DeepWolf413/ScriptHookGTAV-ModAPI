#pragma once
#include <memory>
#include <xstring>
#include <shsdk/enums.h>

#include "Entity.h"
#include "Tasker.h"

namespace ModAPI
{
	// A convenience class for the PedHandle.
	class Ped : public Entity
	{
	public:
		Ped();
		Ped(PedHandle pedToRepresent);
		~Ped() override = default;

		static std::unique_ptr<Ped> SpawnPed(const std::string& modelName, const Vector3& spawnPosition, float heading,
		                                     int outfitNumber = 0);
		static std::unique_ptr<Ped> SpawnPed(ePedType pedType, const std::string& modelName, const Vector3& spawnPosition,
		                                     float heading, int outfitNumber = 0);

		[[nodiscard]] std::string GetModelName() const;
		[[nodiscard]] std::unique_ptr<Ped> GetTarget() const;
		
		// Returns the time of death in milliseconds.
		[[nodiscard]] int GetTimeOfDeath() const;

		[[nodiscard]] float GetTimeSinceDeath() const;
		[[nodiscard]] Ped GetKiller() const;
		[[nodiscard]] bool IsInCombat() const;
		[[nodiscard]] bool IsInMeleeCombat() const;
		[[nodiscard]] bool IsShooting() const;
		[[nodiscard]] bool IsHuman() const;
		[[nodiscard]] bool IsOnVehicle() const;
		[[nodiscard]] bool IsOnMount() const;
		[[nodiscard]] bool IsOnFoot() const;
		[[nodiscard]] bool IsInAnyVehicle() const;
		[[nodiscard]] bool IsInVehicle(VehicleHandle vehicleHandle) const;
		[[nodiscard]] bool IsUsingAnyScenario() const;
		[[nodiscard]] bool IsUsingScenario(const std::string& scenarioName) const;
		[[nodiscard]] bool IsRagdoll() const;
		[[nodiscard]] Vehicle GetVehicle(bool includeLastVehicle = false) const;
		void SetShootAccuracy(int accuracy) const;
		void SetCombatAttribute(eCombatAttribute attribute, bool enabled) const;
		void SetConfigFlag(int flagId, bool enabled) const;
		void SetBlockEvents(bool blockEvents) const;
		void SetRelationshipGroup(Hash groupHash) const;
		void SetDefaultRelationshipGroup(Hash groupHash) const;
		[[nodiscard]] eRelationship GetRelationship(const Ped& otherPed) const;
		[[nodiscard]] Hash GetDefaultRelationshipGroup() const;
		[[nodiscard]] Hash GetRelationshipGroupHash() const;
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
