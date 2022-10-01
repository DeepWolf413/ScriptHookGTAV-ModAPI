#include "Vehicle.h"

#include <natives.h>

namespace ModAPI
{
    Vehicle::Vehicle(const ::Vehicle vehicleHandle) : ModAPI::Entity(vehicleHandle)
    {}

    void Vehicle::EveryoneLeaveVehicle() const
    { TASK::TASK_EVERYONE_LEAVE_VEHICLE(handle); }

    bool Vehicle::IsSeatFree(const eVehicleSeat seat) const
    { return VEHICLE::IS_VEHICLE_SEAT_FREE(handle, seat, false); }

    int Vehicle::GetSeatsCount() const
    {
        return VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(GetModel().GetHash());
    }

    Entity Vehicle::GetPedInSeat(const eVehicleSeat seat) const
    {
        return Entity(VEHICLE::GET_PED_IN_VEHICLE_SEAT(GetHandle(), seat, FALSE));
    }
}
