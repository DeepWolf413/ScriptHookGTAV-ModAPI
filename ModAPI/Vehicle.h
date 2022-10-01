#pragma once
#include <types.h>
#include <enums.h>

#include "Entity.h"

namespace ModAPI
{
	class Vehicle : public ModAPI::Entity {
	public:
		Vehicle(::Vehicle vehicleHandle);

		void EveryoneLeaveVehicle() const;
		[[nodiscard]] bool IsDriveable() const;
		[[nodiscard]] bool AreAnySeatsFree() const;
		[[nodiscard]] bool IsSeatFree(eVehicleSeat seat, bool isTaskRunning = true) const;
		[[nodiscard]] int GetSeatsCount() const;
		[[nodiscard]] int GetPassengersCount(bool includeDriver, bool includeDeadOccupants) const;
		[[nodiscard]] Entity GetPedInSeat(eVehicleSeat seat) const;
	};
}
