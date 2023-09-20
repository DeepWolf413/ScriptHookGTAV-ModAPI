#include "Vehicle.h"

#include <natives.h>

#include "Logger.h"
#include "Math/Vector3.h"

namespace ModAPI
{
	Vehicle::Vehicle(const ::Vehicle vehicleHandle) : ModAPI::Entity(vehicleHandle)
	{
	}

	void Vehicle::EveryoneLeaveVehicle() const
	{
		TASK::TASK_EVERYONE_LEAVE_VEHICLE(handle);
	}

	bool Vehicle::IsDriveable() const
	{
		return VEHICLE::IS_VEHICLE_DRIVEABLE(handle, true);
	}

	bool Vehicle::AreAnySeatsFree() const
	{
		return VEHICLE::ARE_ANY_VEHICLE_SEATS_FREE(handle);
	}

	bool Vehicle::IsSeatFree(const eVehicleSeat seat, bool isTaskRunning) const
	{
		return VEHICLE::IS_VEHICLE_SEAT_FREE(handle, seat, isTaskRunning);
	}

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
		return GetSeats(hasToBeFreeSeats, {});
	}

	std::vector<eVehicleSeat> Vehicle::GetSeats(const bool hasToBeFreeSeats,
	                                            const std::vector<eVehicleSeat>& seatsToIgnore) const
	{
		const auto vehicleModel = GetModel();
		const bool doesVehicleHaveTwoColumnSeats = !vehicleModel.IsBicycle() && !vehicleModel.IsBike() && !vehicleModel.
			IsJetski() && !vehicleModel.IsQuadBike();

		std::vector<eVehicleSeat> seats{};

		const bool isSeatsToIgnoreEmpty = seatsToIgnore.empty();
		const bool ignoreDriverSeat = std::ranges::find(seatsToIgnore, eVehicleSeat::VehicleSeatDriver) != seatsToIgnore.end();
		const bool ignorePassengerSeat = std::ranges::find(seatsToIgnore, eVehicleSeat::VehicleSeatPassenger) != seatsToIgnore.end();
		if ((hasToBeFreeSeats && IsSeatFree(eVehicleSeat::VehicleSeatDriver) || !hasToBeFreeSeats) && (!isSeatsToIgnoreEmpty && !ignoreDriverSeat || isSeatsToIgnoreEmpty))
		{
			seats.push_back(eVehicleSeat::VehicleSeatDriver);
		}

		if ((hasToBeFreeSeats && IsSeatFree(eVehicleSeat::VehicleSeatPassenger) || !hasToBeFreeSeats) && (!isSeatsToIgnoreEmpty && !ignorePassengerSeat || isSeatsToIgnoreEmpty))
		{
			seats.push_back(eVehicleSeat::VehicleSeatPassenger);
		}
		
		if (doesVehicleHaveTwoColumnSeats)
		{
			const bool ignoreLeftBackseat = std::ranges::find(seatsToIgnore, eVehicleSeat::VehicleSeatLeftRear) != seatsToIgnore.end();
			const bool ignoreRightBackseat = std::ranges::find(seatsToIgnore, eVehicleSeat::VehicleSeatRightRear) != seatsToIgnore.end();
			
			if ((hasToBeFreeSeats && IsSeatFree(eVehicleSeat::VehicleSeatLeftRear) || !hasToBeFreeSeats) && (!isSeatsToIgnoreEmpty && !ignoreLeftBackseat || isSeatsToIgnoreEmpty))
			{
				seats.push_back(eVehicleSeat::VehicleSeatLeftRear);
			}

			if ((hasToBeFreeSeats && IsSeatFree(eVehicleSeat::VehicleSeatRightRear) || !hasToBeFreeSeats) && (!isSeatsToIgnoreEmpty && !ignoreRightBackseat || isSeatsToIgnoreEmpty))
			{
				seats.push_back(eVehicleSeat::VehicleSeatRightRear);
			}
		}

		return seats;
	}

	eVehicleSeat Vehicle::GetClosestSeat(const MMath::Vector3& position, const bool hasToBeFreeSeat)
	{
		return GetClosestSeat(position, hasToBeFreeSeat, {});
	}

	eVehicleSeat Vehicle::GetClosestSeat(const MMath::Vector3& position, const bool hasToBeFreeSeat,
		const std::vector<eVehicleSeat>& seatsToIgnore)
	{
		const auto seats = GetSeats(hasToBeFreeSeat);
		if (seats.empty())
		{
			return eVehicleSeat::VehicleSeatNone;
		}

		eVehicleSeat closestSeat = eVehicleSeat::VehicleSeatNone;
		float closestDistanceToSeat = 0.0f;
		for (const auto seat : seats)
		{
			const auto seatBone = GetSeatBone(seat);
			if (!seatBone.IsValid())
			{
				continue;
			}

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
			{
				if (Bone::IsValid(*this, "seat_dside_f"))
				{
					return {*this, "seat_dside_f"};
				}

				return {*this, "seat_f"};
			}
		case VehicleSeatPassenger:
			if (Bone::IsValid(*this, "seat_pside_f"))
			{
				return {*this, "seat_pside_f"};
			}

			return {*this, "seat_r"};
		case VehicleSeatLeftRear:
			return {*this, "seat_dside_r"};
		case VehicleSeatRightRear:
			return {*this, "seat_pside_r"};
		}

		return {*this, ""};
	}
}
