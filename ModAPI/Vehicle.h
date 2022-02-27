#pragma once
#include "Entity.h"
#include "shsdk/enums.h"

namespace ModAPI
{
	class Vehicle : public Entity{
	public:
		Vehicle(VehicleHandle handle);

		[[nodiscard]] bool IsSeatFree(eVehicleSeat seat) const;
	};
}
