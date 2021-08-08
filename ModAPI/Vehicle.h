#pragma once
#include "Entity.h"
#include "inc/enums.h"

namespace ModAPI
{
	class Vehicle : public Entity{
	public:
		Vehicle(VehicleHandle handle);

		bool IsSeatFree(eVehicleSeat seat) const;
	};
}
