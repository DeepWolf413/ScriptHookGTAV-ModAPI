#include "Vehicle.h"


#include <inc/natives.h>

ModAPI::Vehicle::Vehicle(const VehicleHandle handle) : Entity(handle)
{}

bool ModAPI::Vehicle::IsSeatFree(const eVehicleSeat seat) const
{ return VEHICLE::IS_VEHICLE_SEAT_FREE(handle, static_cast<int>(seat)); }

bool ModAPI::Vehicle::IsCannon() const
{
	return IsModel(MISC::GET_HASH_KEY("BREACH_CANNON"))
                    || IsModel(MISC::GET_HASH_KEY("hotchkiss_cannon"))
                    || IsModel(MISC::GET_HASH_KEY("GATLING_GUN"))
                    || IsModel(MISC::GET_HASH_KEY("GATLINGMAXIM02"));
}
