#pragma once
#include "Entity.h"
#include "shsdk/enums.h"

namespace ModAPI
{
	class Vehicle : public Entity{
	public:
		Vehicle(VehicleHandle vehicleHandle);

		void EveryoneLeaveVehicle() const;
		[[nodiscard]] bool IsSeatFree(eVehicleSeat seat) const;
	};
}
