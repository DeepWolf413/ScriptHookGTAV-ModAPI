#include "Vehicle.h"

#include <natives.h>

namespace ModAPI
{
    Vehicle::Vehicle(const ::Vehicle vehicleHandle) : ModAPI::Entity(vehicleHandle)
    {}

    void Vehicle::EveryoneLeaveVehicle() const
    { TASK::TASK_EVERYONE_LEAVE_VEHICLE(handle); }

    bool Vehicle::IsDriveable() const
    {
        return VEHICLE::IS_VEHICLE_DRIVEABLE(handle, true);
    }

    bool Vehicle::AreAnySeatsFree() const
    {
        return VEHICLE::ARE_ANY_VEHICLE_SEATS_FREE(handle);
    }

    bool Vehicle::IsSeatFree(const eVehicleSeat seat, bool isTaskRunning) const
    { return VEHICLE::IS_VEHICLE_SEAT_FREE(handle, seat, isTaskRunning); }

    int Vehicle::GetSeatsCount() const
    {
        return VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(GetModel().GetHash());
    }

    int Vehicle::GetPassengersCount(const bool includeDriver, const bool includeDeadOccupants) const
    {
        return VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(handle, includeDriver, includeDeadOccupants);
    }

    Entity Vehicle::GetPedInSeat(const eVehicleSeat seat) const
    {
        return {VEHICLE::GET_PED_IN_VEHICLE_SEAT(handle, seat, FALSE)};
    }
}
