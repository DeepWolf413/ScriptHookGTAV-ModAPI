#include "Vehicle.h"

#include <natives.h>

#include "Math/Vector3.h"

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

    std::vector<eVehicleSeat> Vehicle::GetSeats(const bool hasToBeFreeSeats) const
    {
        const auto vehicleModel = GetModel();
        const bool isVehicleWithSideSeats = !vehicleModel.IsBicycle() && !vehicleModel.IsBike() && !vehicleModel.IsJetski() && !vehicleModel.IsQuadBike();

        std::vector<eVehicleSeat> seats {};

        const bool hasTwoColumnSeats = vehicleModel.IsCar() || vehicleModel.IsBoat() || vehicleModel.IsHelicopter() || vehicleModel.IsPlane();
        if (hasToBeFreeSeats && IsSeatFree(eVehicleSeat::VehicleSeatDriver) || !hasToBeFreeSeats)
        {
            seats.push_back(eVehicleSeat::VehicleSeatDriver);
        }
        else if (hasToBeFreeSeats && IsSeatFree(eVehicleSeat::VehicleSeatPassenger) || !hasToBeFreeSeats)
        {
            seats.push_back(eVehicleSeat::VehicleSeatPassenger);
        }

        if (isVehicleWithSideSeats)
        {
            if (hasToBeFreeSeats && IsSeatFree(eVehicleSeat::VehicleSeatLeftRear) || !hasToBeFreeSeats && hasTwoColumnSeats)
            {
                seats.push_back(eVehicleSeat::VehicleSeatLeftRear);
            }
            else if (hasToBeFreeSeats && IsSeatFree(eVehicleSeat::VehicleSeatRightRear) || !hasToBeFreeSeats && hasTwoColumnSeats)
            {
                seats.push_back(eVehicleSeat::VehicleSeatRightRear);
            }
        }

        return seats;
    }

    eVehicleSeat Vehicle::GetClosestSeat(const MMath::Vector3& position, const bool hasToBeFreeSeat)
    {
        const auto seats = GetSeats(hasToBeFreeSeat);
        if (seats.empty())
        { return eVehicleSeat::VehicleSeatNone; }

        eVehicleSeat closestSeat = eVehicleSeat::VehicleSeatNone;
        float closestDistanceToSeat = 0.0f;
        for (const auto seat : seats)
        {
            const auto seatBone = GetSeatBone(seat);
            const auto seatDistance = seatBone.GetPosition().DistanceTo(position);
            if (seatDistance < closestDistanceToSeat || closestSeat == eVehicleSeat::VehicleSeatNone)
            {
                closestSeat = seat;
                closestDistanceToSeat = seatDistance;
            }
        }
        
        return closestSeat;
    }

    Bone Vehicle::GetSeatBone(const eVehicleSeat seat)
    {
        switch (seat)
        {
        case VehicleSeatDriver:
            return {*this, "seat_dside_f"};
        case VehicleSeatPassenger:
            return {*this, "seat_pside_f"};
        case VehicleSeatLeftRear:
            return {*this, "seat_dside_r"};
        case VehicleSeatRightRear:
            return {*this, "seat_pside_r"};
        }

        return {*this, ""};
    }
}
