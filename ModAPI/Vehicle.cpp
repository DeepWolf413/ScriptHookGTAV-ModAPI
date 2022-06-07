#include "Vehicle.h"


#include <shsdk/natives.h>

ModAPI::Vehicle::Vehicle(const VehicleHandle vehicleHandle) : Entity(vehicleHandle)
{}

void ModAPI::Vehicle::EveryoneLeaveVehicle() const
{ TASK::TASK_EVERYONE_LEAVE_VEHICLE(handle); }

bool ModAPI::Vehicle::IsSeatFree(const eVehicleSeat seat) const
{ return VEHICLE::IS_VEHICLE_SEAT_FREE(handle, seat, false); }