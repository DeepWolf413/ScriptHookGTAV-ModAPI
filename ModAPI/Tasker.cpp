#include "Tasker.h"

#include <shsdk/natives.h>

#include "Ped.h"
#include "Vehicle.h"
#include "math/Vector3.h"

ModAPI::Tasker::Tasker(Ped* ped)
{
	if(ped == nullptr)
	{
		// TODO: Log error "A null ped pointer was given to the Tasker constructor. Something ain't right".
	}
	
	this->ped = ped;
}

void ModAPI::Tasker::EnterVehicle(Vehicle* vehicle, const eVehicleSeat seat) const
{ EnterVehicle(vehicle, seat, 5000, 2.0f, 0); }

void ModAPI::Tasker::EnterVehicle(Vehicle* vehicle, const eVehicleSeat seat, const int timeoutMs) const
{ EnterVehicle(vehicle, seat, timeoutMs, 2.0f, 0); }

void ModAPI::Tasker::EnterVehicle(Vehicle* vehicle, const eVehicleSeat seat, const int timeoutMs, const float speed) const
{ EnterVehicle(vehicle, seat, timeoutMs, speed, 0); }

void ModAPI::Tasker::EnterVehicle(Vehicle* vehicle, const eVehicleSeat seat, const int timeoutMs, const float speed, const int flag) const
{
	TASK::TASK_ENTER_VEHICLE(ped->GetHandle(), vehicle->GetHandle(), timeoutMs, static_cast<int>(seat), speed, flag, 0);
}

void ModAPI::Tasker::EnterClosestVehicle(std::vector<EntityHandle>& entitiesToIgnore) const
{
	const auto nearbyVehicles = ped->GetNearbyVehicles(1);

	if(!nearbyVehicles.empty())
	{
		entitiesToIgnore.push_back(nearbyVehicles[0]->GetHandle());
		EnterVehicle(nearbyVehicles[0].get(), eVehicleSeat::VehicleSeatDriver);
	}
}

void ModAPI::Tasker::ExitVehicle() const
{ TASK::TASK_LEAVE_ANY_VEHICLE(ped->GetHandle(), 0, 0); }

void ModAPI::Tasker::ExitVehicle(Vehicle* vehicle, const LeaveVehicleFlags flag) const
{ TASK::TASK_LEAVE_VEHICLE(ped->GetHandle(), vehicle->GetHandle(), static_cast<int>(flag)); }

void ModAPI::Tasker::DismountExit() const
{
	if(ped->IsOnVehicle())
	{ ExitVehicle(); }
}

void ModAPI::Tasker::FightAgainst(Ped* target) const
{
	if(!ped->Exists() || target == nullptr || !target->Exists() || target->GetHandle() == ped->GetHandle())
	{ return; }
	
	TASK::TASK_COMBAT_PED(ped->GetHandle(), target->GetHandle(), 0, 16);
}

void ModAPI::Tasker::FightAgainst(Ped* target, const int durationMs) const
{
	if(!ped->Exists() || target == nullptr || !target->Exists() || target->GetHandle() == ped->GetHandle())
	{ return; }
	
	TASK::TASK_COMBAT_PED(ped->GetHandle(), target->GetHandle(), durationMs, 0);
}

void ModAPI::Tasker::FightAgainstHatedTargets(const float radius) const
{
	if(!ped->Exists())
	{ return; }

	TASK::TASK_COMBAT_HATED_TARGETS_AROUND_PED(ped->GetHandle(), radius, 0);
}

void ModAPI::Tasker::FightAgainstHatedTargets(const float radius, const int durationMs) const
{
	if(!ped->Exists())
	{ return; }

	TASK::TASK_COMBAT_HATED_TARGETS_AROUND_PED_TIMED(ped->GetHandle(), radius, durationMs, 0);
}

void ModAPI::Tasker::UseNearestScenario() const
{
	const Vector3 position = ped->GetPosition();
	TASK::TASK_USE_NEAREST_SCENARIO_TO_COORD(ped->GetHandle(), position.x, position.y, position.z, 10.0f, 0.0f);
}

void ModAPI::Tasker::StopScenario() const
{ }
