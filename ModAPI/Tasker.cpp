#include "Tasker.h"

#include <shsdk/natives.h>

#include "Ped.h"
#include "Vehicle.h"
#include "math/Vector3.h"

ModAPI::Tasker::Tasker(const Ped& owner)
{
	this->owner = &owner;
}

void ModAPI::Tasker::AchieveHeading(const float heading, const int timeoutMs) const
{ TASK::TASK_ACHIEVE_HEADING(owner->GetHandle(), heading, timeoutMs); }

void ModAPI::Tasker::AimAt(const Entity& target, const int durationMs) const
{ TASK::TASK_AIM_GUN_AT_ENTITY(owner->GetHandle(), target.GetHandle(), durationMs, false); }

void ModAPI::Tasker::AimAt(const Vector3& aimPosition, const int durationMs) const
{ TASK::TASK_AIM_GUN_AT_COORD(owner->GetHandle(), aimPosition, durationMs, true, false); }

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
{ TASK::TASK_VEHICLE_DRIVE_TO_COORD(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), vehicle.GetHandle(), position.X, position.Y, position.Z, speed, 0, vehicle.GetModel().GetHash(), drivingStyle, stopRange, -1.0f); }

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

void ModAPI::Tasker::FleeFrom(const Ped& pedToFleeFrom, const int durationMs) const
{ TASK::TASK_SMART_FLEE_PED(owner->GetHandle(), pedToFleeFrom.GetHandle(), -1, durationMs, true, false); }

void ModAPI::Tasker::FleeFrom(const Ped& pedToFleeFrom, const float distance) const
{ TASK::TASK_SMART_FLEE_PED(owner->GetHandle(), pedToFleeFrom.GetHandle(), distance, -1, true, false); }

void ModAPI::Tasker::FleeFrom(const Vector3& position, const int durationMs) const
{ TASK::TASK_SMART_FLEE_COORD(owner->GetHandle(), position, -1, durationMs, true, false); }

void ModAPI::Tasker::FleeFrom(const Vector3& position, const float distance) const
{ TASK::TASK_SMART_FLEE_COORD(owner->GetHandle(), position, distance, -1, true, false); }

void ModAPI::Tasker::FollowPointRoute(const std::vector<Vector3>& points, const float speed) const
{
	if (points.empty())
	{ return; }
	
	TASK::TASK_FLUSH_ROUTE();
	for (const auto routePoint : points)
	{ TASK::TASK_EXTEND_ROUTE(routePoint); }
	
	TASK::TASK_FOLLOW_POINT_ROUTE(owner->GetHandle(), speed, 0);
}

void ModAPI::Tasker::GoTo(const Entity& target) const
{ GoTo(target, 2.0f, -1); }

void ModAPI::Tasker::GoTo(const Entity& target, const float stopDistance) const
{ GoTo(target, stopDistance, -1); }

void ModAPI::Tasker::GoTo(const Entity& target, const float stopDistance, const int timeoutMs) const
{ TASK::TASK_GO_TO_ENTITY(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), target.GetHandle(), timeoutMs, stopDistance, 2.0f, 2.0f, 0); }

void ModAPI::Tasker::GoTo(const Vector3& position) const
{ GoTo(position, false, -1); }

void ModAPI::Tasker::GoTo(const Vector3& position, const bool ignorePaths) const
{ GoTo(position, ignorePaths, -1); }

void ModAPI::Tasker::GoTo(const Vector3& position, bool ignorePaths, int timeoutMs) const
{
	// TODO: Implement
}

void ModAPI::Tasker::FollowToOffsetFromEntity(const Entity& target, const Vector3& offset, const float moveSpeed, const int timeoutMs,
                                              const float stoppingRange, const bool persistFollowing) const
{ TASK::TASK_FOLLOW_TO_OFFSET_OF_ENTITY(owner->GetHandle(), target.GetHandle(), offset, moveSpeed, timeoutMs, stoppingRange, persistFollowing); }

void ModAPI::Tasker::GuardCurrentPosition() const
{ TASK::TASK_GUARD_CURRENT_POSITION(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), 35.0f, 35.0f, TRUE); }

void ModAPI::Tasker::HandsUp(const int durationMs) const
{ TASK::TASK_HANDS_UP(owner->GetHandle(), durationMs, NULL, -1, false); }

void ModAPI::Tasker::HandsUp(const int durationMs, const Ped& facingTarget) const
{ TASK::TASK_HANDS_UP(owner->GetHandle(), durationMs, facingTarget.GetHandle(), -1, false);  }

void ModAPI::Tasker::Jump(const bool superJump) const
{ TASK::TASK_JUMP(owner->GetHandle(), true, superJump, superJump); }

void ModAPI::Tasker::LeaveVehicle(const LeaveVehicleFlags leaveFlag) const
{ TASK::TASK_LEAVE_ANY_VEHICLE(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), 0, leaveFlag); }

void ModAPI::Tasker::LeaveVehicle(const Vehicle& vehicle, const LeaveVehicleFlags leaveFlag) const
{ TASK::TASK_LEAVE_VEHICLE(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), vehicle.GetHandle(), leaveFlag); }

void ModAPI::Tasker::LookAt(const Entity& target, const int durationMs) const
{ TASK::TASK_LOOK_AT_ENTITY(owner->GetHandle(), target.GetHandle(), durationMs, 2048, 3); }

void ModAPI::Tasker::LookAt(const Vector3& position, const int durationMs) const
{ TASK::TASK_LOOK_AT_COORD(owner->GetHandle(), position, durationMs, 0, 2); }

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

void ModAPI::Tasker::PlayAnimation(const std::string& animDict, const std::string& animName, const float speed, const int durationMs, const eAnimationFlags flags, const float playbackRate, const BOOL lockX, const BOOL lockY, const BOOL lockZ) const
{ TASK::TASK_PLAY_ANIM(owner->GetHandle(), animDict.c_str(), animName.c_str(), speed, speed, durationMs, flags, playbackRate, lockX, lockY, lockZ); }

void ModAPI::Tasker::StopAnimation(const std::string& animDict, const std::string& animName, const float blendOutSpeed) const
{ TASK::STOP_ANIM_TASK(owner->GetHandle(), animDict.c_str(), animName.c_str(), blendOutSpeed); }

void ModAPI::Tasker::ShockingEventReact(const int eventHandle) const
{ TASK::TASK_SHOCKING_EVENT_REACT(owner->GetHandle(), eventHandle); }

void ModAPI::Tasker::ReloadWeapon() const
{ TASK::TASK_RELOAD_WEAPON(owner->GetHandle(), 1); }

bool ModAPI::Tasker::IsSequenceTaskOpen() const
{ return currentSequenceTask != -1; }
