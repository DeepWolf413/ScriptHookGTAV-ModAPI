#pragma once
#include "Entity.h"
#include "enums/eVehicleSeat.h"

namespace ModAPI
{
	class Vehicle : public Entity{
	public:
		Vehicle(VehicleHandle handle);

		bool IsSeatFree(eVehicleSeat seat) const;
		bool IsCannon() const;
	};
}
