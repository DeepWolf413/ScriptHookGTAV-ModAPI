#include "Vehicle.h"


#include <shsdk/natives.h>

ModAPI::Vehicle::Vehicle(const VehicleHandle handle) : Entity(handle)
{}

bool ModAPI::Vehicle::IsSeatFree(const eVehicleSeat seat) const
{ return VEHICLE::IS_VEHICLE_SEAT_FREE(handle, seat, false); }