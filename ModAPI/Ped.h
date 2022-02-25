#pragma once
#include <memory>
#include <xstring>
#include <shsdk/enums.h>

#include "Entity.h"

namespace ModAPI
{
	class Vehicle;
	class Tasker;
	class Team;

	// A convenience class for the ::ped type.
	class Ped : public Entity
	{
	public:
		Ped(PedHandle pedToRepresent);
		virtual ~Ped() = default;

		static std::unique_ptr<Ped> SpawnPed(const std::string& modelName, const Vector3& spawnPosition, float heading,
		                                     int outfitNumber = 0);
		static std::unique_ptr<Ped> SpawnPed(ePedType pedType, const std::string& modelName, const Vector3& spawnPosition,
		                                     float heading, int outfitNumber = 0);

		std::string GetModelName() const;
		std::unique_ptr<Ped> GetTarget() const;
		//std::unique_ptr<Ped> GetTarget() const;
		
		// Returns the time of death in milliseconds.
		int GetTimeOfDeath() const;

		float GetTimeSinceDeath() const;
		PedHandle GetKiller() const;
		bool IsInCombat() const;
		bool IsInMeleeCombat() const;
		bool IsShooting() const;
		bool IsHuman() const;
		bool IsOnVehicle() const;
		bool IsOnMount() const;
		bool IsOnFoot() const;
		bool IsInAnyVehicle() const;
		bool IsInVehicle(VehicleHandle vehicleHandle) const;
		bool IsUsingAnyScenario() const;
		bool IsUsingScenario(const std::string& scenarioName) const;
		void SetShootAccuracy(int accuracy) const;
		void SetCombatAttribute(eCombatAttribute attribute, bool enabled) const;
		void SetConfigFlag(int flagId, bool enabled) const;
		void SetBlockEvents(bool blockEvents) const;
		void SetRelationshipGroup(Hash groupHash) const;
		void ClearTasksImmediately() const;
		void EquipBestWeapon() const;
		void EquipWeapon(Hash weaponHash) const;
		void GiveWeapon(Hash weaponHash, int ammoCount, bool forceInHand, bool forceInHolster) const;
		bool HasWeapon(Hash weaponHash) const;
		void RemoveAllWeapons() const;
		Tasker* GetTasker() const;

	protected:
		std::unique_ptr<Tasker> tasker;
		std::string modelName;
	};
}
