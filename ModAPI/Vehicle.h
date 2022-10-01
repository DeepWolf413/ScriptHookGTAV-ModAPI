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
		[[nodiscard]] bool IsSeatFree(eVehicleSeat seat) const;
	};
}
