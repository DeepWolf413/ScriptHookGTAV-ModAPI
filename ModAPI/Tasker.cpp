#include "Tasker.h"

#include <shsdk/natives.h>

#include "Ped.h"
#include "Vehicle.h"
#include "math/Vector3.h"

ModAPI::Tasker::Tasker(const Ped& owner)
{
	this->owner = &owner;
}

void ModAPI::Tasker::EveryoneLeaveVehicle(const Vehicle& vehicle)
{ TASK::TASK_EVERYONE_LEAVE_VEHICLE(vehicle.GetHandle()); }

void ModAPI::Tasker::Arrest(const Ped& pedToArrest) const
{ TASK::TASK_ARREST_PED(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), pedToArrest.GetHandle()); }

void ModAPI::Tasker::Climb() const
{ TASK::TASK_CLIMB(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), FALSE); }

void ModAPI::Tasker::Cower(const int durationMs) const
{ TASK::TASK_COWER(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), durationMs); }

void ModAPI::Tasker::Cruise(const Vehicle& vehicle, const float speed) const
{ Cruise(vehicle, speed); }

void ModAPI::Tasker::Cruise(const Vehicle& vehicle, const float speed, const eDrivingStyle drivingStyle) const
{ TASK::TASK_VEHICLE_DRIVE_WANDER(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), vehicle.GetHandle(), speed, drivingStyle); }

void ModAPI::Tasker::DriveTo(const Vehicle& vehicle, const Vector3& position, const float stopRange, const float speed) const
{ DriveTo(vehicle, position, stopRange, speed, eDrivingStyle::DrivingStyleRushed); }

void ModAPI::Tasker::DriveTo(const Vehicle& vehicle, const Vector3& position, const float stopRange, const float speed, const eDrivingStyle drivingStyle) const
{ TASK::TASK_VEHICLE_DRIVE_TO_COORD(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), vehicle.GetHandle(), position.X, position.Y, position.Z, speed, 0, vehicle.GetModel(), drivingStyle, stopRange, -1.0f); }

void ModAPI::Tasker::EnterVehicle(const Vehicle& vehicle, const eVehicleSeat seat) const
{ EnterVehicle(vehicle, seat, 5000, 2.0f, 0); }

void ModAPI::Tasker::EnterVehicle(const Vehicle& vehicle, const eVehicleSeat seat, const int timeoutMs) const
{ EnterVehicle(vehicle, seat, timeoutMs, 2.0f, 0); }

void ModAPI::Tasker::EnterVehicle(const Vehicle& vehicle, const eVehicleSeat seat, const int timeoutMs, const float speed) const
{ EnterVehicle(vehicle, seat, timeoutMs, speed, 0); }

void ModAPI::Tasker::EnterVehicle(const Vehicle& vehicle, const eVehicleSeat seat, const int timeoutMs, const float speed, const int flag) const
{ TASK::TASK_ENTER_VEHICLE(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), vehicle.GetHandle(), timeoutMs, static_cast<int>(seat), speed, flag, 0); }

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
{ TASK::TASK_LEAVE_ANY_VEHICLE(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), 0, 0); }

void ModAPI::Tasker::ExitVehicle(const Vehicle& vehicle, const LeaveVehicleFlags flag) const
{ TASK::TASK_LEAVE_VEHICLE(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), vehicle.GetHandle(), static_cast<int>(flag)); }

void ModAPI::Tasker::DismountExit() const
{
	if(owner->IsOnVehicle())
	{ ExitVehicle(); }
}

void ModAPI::Tasker::FightAgainst(const Ped& target) const
{
	if(!owner->Exists() || !target.Exists() || target.GetHandle() == owner->GetHandle())
	{ return; }
	
	TASK::TASK_COMBAT_PED(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), target.GetHandle(), 0, 16);
}

void ModAPI::Tasker::FightAgainst(const Ped& target, const int durationMs) const
{
	if(!owner->Exists() || !target.Exists() || target.GetHandle() == owner->GetHandle())
	{ return; }
	
	TASK::TASK_COMBAT_PED(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), target.GetHandle(), durationMs, 0);
}

void ModAPI::Tasker::FightAgainstHatedTargets(const float radius) const
{
	if(!owner->Exists())
	{ return; }

	TASK::TASK_COMBAT_HATED_TARGETS_AROUND_PED(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), radius, 0);
}

void ModAPI::Tasker::FightAgainstHatedTargets(const float radius, const int durationMs) const
{
	if(!owner->Exists())
	{ return; }

	TASK::TASK_COMBAT_HATED_TARGETS_AROUND_PED_TIMED(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), radius, durationMs, 0);
}

void ModAPI::Tasker::UseNearestScenario(const bool warp, const float distance, const int durationMs) const
{
	const Vector3 position = owner->GetPosition();

	if (warp)
	{
		TASK::TASK_USE_NEAREST_SCENARIO_TO_COORD_WARP(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), position.X, position.Y, position.Z, distance, durationMs);
		return;
	}
	
	TASK::TASK_USE_NEAREST_SCENARIO_TO_COORD(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), position.X, position.Y, position.Z, distance, durationMs);
}

void ModAPI::Tasker::StopScenario() const
{
	if (!owner->IsUsingAnyScenario())
	{ return; }
	
	PED::SET_PED_SHOULD_PLAY_NORMAL_SCENARIO_EXIT(owner->GetHandle());
	ClearTasks();
}

void ModAPI::Tasker::GoTo(const Entity& target) const
{ GoTo(target, 2.0f, -1); }

void ModAPI::Tasker::GoTo(const Entity& target, const float stopDistance) const
{ GoTo(target, stopDistance, -1); }

void ModAPI::Tasker::GoTo(const Entity& target, const float stopDistance, const int timeoutMs) const
{ TASK::TASK_GO_TO_ENTITY(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), target.GetHandle(), timeoutMs, stopDistance, 2.0f, 2.0f, 0); }

void ModAPI::Tasker::GoTo(const Vector3& position) const
{ GoTo(position, false, -1); }

void ModAPI::Tasker::GoTo(const Vector3& position, bool ignorePaths) const
{ GoTo(position, ignorePaths, -1); }

void ModAPI::Tasker::GoTo(const Vector3& position, bool ignorePaths, int timeoutMs) const
{
	// TODO: Implement
}

void ModAPI::Tasker::GuardCurrentPosition() const
{ TASK::TASK_GUARD_CURRENT_POSITION(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), 35.0f, 35.0f, TRUE); }

void ModAPI::Tasker::LeaveVehicle(const LeaveVehicleFlags leaveFlag) const
{ TASK::TASK_LEAVE_ANY_VEHICLE(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), 0, leaveFlag); }

void ModAPI::Tasker::LeaveVehicle(const Vehicle& vehicle, const LeaveVehicleFlags leaveFlag) const
{ TASK::TASK_LEAVE_VEHICLE(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), vehicle.GetHandle(), leaveFlag); }

void ModAPI::Tasker::OpenSequenceTask()
{ TASK::OPEN_SEQUENCE_TASK(&currentSequenceTask); }

void ModAPI::Tasker::PerformSequence()
{
	TASK::CLOSE_SEQUENCE_TASK(currentSequenceTask);
	TASK::TASK_PERFORM_SEQUENCE(owner->GetHandle(), currentSequenceTask);
	TASK::CLEAR_SEQUENCE_TASK(&currentSequenceTask);
	currentSequenceTask = -1;
}

void ModAPI::Tasker::ClearTasks(const bool immediately) const
{
	if (immediately)
	{ TASK::CLEAR_PED_TASKS_IMMEDIATELY(owner->GetHandle()); }
	else
	{ TASK::CLEAR_PED_TASKS(owner->GetHandle()); }
}

bool ModAPI::Tasker::IsSequenceTaskOpen() const
{ return currentSequenceTask != -1; }
