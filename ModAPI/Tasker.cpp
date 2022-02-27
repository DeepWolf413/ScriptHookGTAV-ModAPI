#include "Tasker.h"

#include <shsdk/natives.h>

#include "Ped.h"
#include "Vehicle.h"
#include "math/Vector3.h"

ModAPI::Tasker::Tasker(const Ped* owner)
{
	if(owner == nullptr)
	{
		// TODO: Log error "A null ped pointer was given to the Tasker constructor. Something ain't right".
	}
	
	this->owner = owner;
}

void ModAPI::Tasker::EnterVehicle(const Vehicle& vehicle, const eVehicleSeat seat) const
{ EnterVehicle(vehicle, seat, 5000, 2.0f, 0); }

void ModAPI::Tasker::EnterVehicle(const Vehicle& vehicle, const eVehicleSeat seat, const int timeoutMs) const
{ EnterVehicle(vehicle, seat, timeoutMs, 2.0f, 0); }

void ModAPI::Tasker::EnterVehicle(const Vehicle& vehicle, const eVehicleSeat seat, const int timeoutMs, const float speed) const
{ EnterVehicle(vehicle, seat, timeoutMs, speed, 0); }

void ModAPI::Tasker::EnterVehicle(const Vehicle& vehicle, const eVehicleSeat seat, const int timeoutMs, const float speed, const int flag) const
{
	TASK::TASK_ENTER_VEHICLE(owner->GetHandle(), vehicle.GetHandle(), timeoutMs, static_cast<int>(seat), speed, flag, 0);
}

void ModAPI::Tasker::EnterClosestVehicle(std::vector<EntityHandle>& entitiesToIgnore) const
{
	const auto nearbyVehicles = owner->GetNearbyVehicles(1);

	if(!nearbyVehicles.empty())
	{
		entitiesToIgnore.push_back(nearbyVehicles[0]->GetHandle());
		EnterVehicle(*nearbyVehicles[0], eVehicleSeat::VehicleSeatDriver);
	}
}

void ModAPI::Tasker::ExitVehicle() const
{ TASK::TASK_LEAVE_ANY_VEHICLE(owner->GetHandle(), 0, 0); }

void ModAPI::Tasker::ExitVehicle(const Vehicle& vehicle, const LeaveVehicleFlags flag) const
{ TASK::TASK_LEAVE_VEHICLE(owner->GetHandle(), vehicle.GetHandle(), static_cast<int>(flag)); }

void ModAPI::Tasker::DismountExit() const
{
	if(owner->IsOnVehicle())
	{ ExitVehicle(); }
}

void ModAPI::Tasker::FightAgainst(const Ped& target) const
{
	if(!owner->Exists() || !target.Exists() || target.GetHandle() == owner->GetHandle())
	{ return; }
	
	TASK::TASK_COMBAT_PED(owner->GetHandle(), target.GetHandle(), 0, 16);
}

void ModAPI::Tasker::FightAgainst(const Ped& target, const int durationMs) const
{
	if(!owner->Exists() || !target.Exists() || target.GetHandle() == owner->GetHandle())
	{ return; }
	
	TASK::TASK_COMBAT_PED(owner->GetHandle(), target.GetHandle(), durationMs, 0);
}

void ModAPI::Tasker::FightAgainstHatedTargets(const float radius) const
{
	if(!owner->Exists())
	{ return; }

	TASK::TASK_COMBAT_HATED_TARGETS_AROUND_PED(owner->GetHandle(), radius, 0);
}

void ModAPI::Tasker::FightAgainstHatedTargets(const float radius, const int durationMs) const
{
	if(!owner->Exists())
	{ return; }

	TASK::TASK_COMBAT_HATED_TARGETS_AROUND_PED_TIMED(owner->GetHandle(), radius, durationMs, 0);
}

void ModAPI::Tasker::UseNearestScenario() const
{
	const Vector3 position = owner->GetPosition();
	TASK::TASK_USE_NEAREST_SCENARIO_TO_COORD(owner->GetHandle(), position.X, position.Y, position.Z, 10.0f, 0.0f);
}

void ModAPI::Tasker::StopScenario() const
{ }
