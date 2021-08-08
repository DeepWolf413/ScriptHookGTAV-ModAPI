#pragma once
#include <memory>
#include <vector>
#include <xstring>
#include <inc/enums.h>

#include "Entity.h"

namespace ModAPI
{
	class Vehicle;
	class Tasker;
	class Team;

	// A convenience class for the ::ped type.
	class Ped : public Entity {
	public:
		Ped(PedHandle pedToRepresent);
		virtual ~Ped() = default;

		static std::unique_ptr<Ped> SpawnPed(std::string modelName, Vector3 spawnPosition, float heading, int outfitNumber = 0);

		std::string GetModelName() const;
		std::unique_ptr<ModAPI::Ped> GetTarget() const;
		//std::unique_ptr<Ped> GetTarget() const;
		

		// Returns the time of death in milliseconds.
		int GetTimeOfDeath() const;

		float                                          GetTimeSinceDeath() const;
		PedHandle                                      GetKiller() const;
		bool                                           IsInCombat() const;
		bool                                           IsInMeleeCombat() const;
		bool                                           IsShooting() const;
		bool                                           IsHorse() const;
		bool                                           IsHuman() const;
		bool                                           IsOnVehicle() const;
		bool                                           IsOnMount() const;
		bool                                           IsOnFoot() const;
		bool                                           IsUsingAnyScenario() const;
		bool                                           IsUsingScenario(Hash scenarioHash) const;
		void                                           SetShootAccuracy(int accuracy) const;
		void                                           SetOutfit(int newOutfit);
		void                                           SetToNextOutfit();
		void                                           SetToPreviousOutfit();
		void                                           ResetOutfit();
		void                                           SetRndOutfit();
		void                                           SetCombatAttribute(eCombatAttribute attribute, bool enabled) const;
		void                                           SetConfigFlag(int flagId, bool enabled) const;
		void                                           SetBlockEvents(bool blockEvents) const;
		void                                           SetRelationshipGroup(Hash groupHash) const;
		int                                            GetCurrentOutfit() const;
		int                                            GetMaxOutfit() const;
		void                                           ClearTasksImmediately() const;
		void                                           EquipBestWeapon() const;
		void                                           EquipWeapon(Hash weaponHash) const;
		void                                           EquipWeapon(Hash weaponHash, eWeaponAttachPoint attachPoint) const;
		void                                           GiveWeapon(Hash weaponHash, int ammoCount, bool forceInHand, bool forceInHolster, bool allowMultipleCopies = false) const;
		bool                                           HasWeapon(Hash weaponHash) const;
		void                                           RemoveAllWeapons() const;
		Tasker*                                        GetTasker() const;

	protected:
		std::unique_ptr<Tasker> tasker;
		std::string             modelName;
		int                     currentOutfit{0};
	};
}
