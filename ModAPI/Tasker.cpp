#include "Tasker.h"

#include <natives.h>

#include "Ped.h"
#include "MathAPI.h"

namespace ModAPI
{
	Tasker::Tasker(Ped& owner) : owner(&owner)
	{}

	void Tasker::AchieveHeading(const float heading, const int timeoutMs) const
	{ TASK::TASK_ACHIEVE_HEADING(owner->GetHandle(), heading, timeoutMs); }

	void Tasker::AimAt(const ModAPI::Entity& target, const int durationMs) const
	{ TASK::TASK_AIM_GUN_AT_ENTITY(owner->GetHandle(), target.GetHandle(), durationMs, false); }

	void Tasker::AimAt(const MMath::Vector3& aimPosition, const int durationMs) const
	{ TASK::TASK_AIM_GUN_AT_COORD(owner->GetHandle(), aimPosition.X, aimPosition.Y, aimPosition.Z, durationMs, true, false); }

	void Tasker::Arrest(const Ped& pedToArrest) const
	{ TASK::TASK_ARREST_PED(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), pedToArrest.GetHandle()); }

	void Tasker::Climb() const
	{ TASK::TASK_CLIMB(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), FALSE); }

	void Tasker::Cower(const int durationMs) const
	{ TASK::TASK_COWER(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), durationMs); }

	void Tasker::Cruise(const ModAPI::Entity& vehicle, const float speed) const
	{ Cruise(vehicle, speed); }

	void Tasker::Cruise(const ModAPI::Entity& vehicle, const float speed, const eDrivingStyle drivingStyle) const
	{ TASK::TASK_VEHICLE_DRIVE_WANDER(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), vehicle.GetHandle(), speed, drivingStyle); }

	void Tasker::DriveTo(const ModAPI::Entity& vehicle, const MMath::Vector3& position, const float stopRange, const float speed) const
	{ DriveTo(vehicle, position, stopRange, speed, eDrivingStyle::DrivingStyleRushed); }

	void Tasker::DriveTo(const ModAPI::Entity& vehicle, const MMath::Vector3& position, const float stopRange, const float speed, const eDrivingStyle drivingStyle) const
	{ TASK::TASK_VEHICLE_DRIVE_TO_COORD(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), vehicle.GetHandle(), position.X, position.Y, position.Z, speed, 0, vehicle.GetModel().GetHash(), drivingStyle, stopRange, -1.0f); }

	void Tasker::EnterVehicle(const ModAPI::Entity& vehicle, const eVehicleSeat seat) const
	{ EnterVehicle(vehicle, seat, 5000, 2.0f, 0); }

	void Tasker::EnterVehicle(const ModAPI::Entity& vehicle, const eVehicleSeat seat, const int timeoutMs) const
	{ EnterVehicle(vehicle, seat, timeoutMs, 2.0f, 0); }

	void Tasker::EnterVehicle(const ModAPI::Entity& vehicle, const eVehicleSeat seat, const int timeoutMs, const float speed) const
	{ EnterVehicle(vehicle, seat, timeoutMs, speed, 0); }

	void Tasker::EnterVehicle(const ModAPI::Entity& vehicle, const eVehicleSeat seat, const int timeoutMs, const float speed, const int flag) const
	{ TASK::TASK_ENTER_VEHICLE(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), vehicle.GetHandle(), timeoutMs, static_cast<int>(seat), speed, flag, 0); }

	void Tasker::EnterClosestVehicle(std::vector<::Entity>& entitiesToIgnore) const
	{
		const auto nearbyVehicles = owner->GetNearbyVehicles(1);

		if(!nearbyVehicles.empty())
		{
			entitiesToIgnore.push_back(nearbyVehicles[0].GetHandle());
			EnterVehicle(nearbyVehicles[0], eVehicleSeat::VehicleSeatDriver);
		}
	}

	void Tasker::ExitVehicle() const
	{ TASK::TASK_LEAVE_ANY_VEHICLE(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), 0, 0); }

	void Tasker::ExitVehicle(const ModAPI::Vehicle& vehicle, const Enums::eLeaveVehicleFlag flag) const
	{ TASK::TASK_LEAVE_VEHICLE(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), vehicle.GetHandle(), static_cast<int>(flag)); }

	void Tasker::DismountExit() const
	{
		if(owner->IsOnVehicle())
		{ ExitVehicle(); }
	}

	void Tasker::FightAgainst(const ModAPI::Ped& target) const
	{
		if(!owner->Exists() || !target.Exists() || target.GetHandle() == owner->GetHandle())
		{ return; }
	
		TASK::TASK_COMBAT_PED(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), target.GetHandle(), 0, 16);
	}

	void Tasker::FightAgainst(const ModAPI::Ped& target, const int durationMs) const
	{
		if(!owner->Exists() || !target.Exists() || target.GetHandle() == owner->GetHandle())
		{ return; }
	
		TASK::TASK_COMBAT_PED(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), target.GetHandle(), durationMs, 0);
	}

	void Tasker::FightAgainstHatedTargets(const float radius) const
	{
		if(!owner->Exists())
		{ return; }

		TASK::TASK_COMBAT_HATED_TARGETS_AROUND_PED(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), radius, 0);
	}

	void Tasker::FightAgainstHatedTargets(const float radius, const int durationMs) const
	{
		if(!owner->Exists())
		{ return; }

		TASK::TASK_COMBAT_HATED_TARGETS_AROUND_PED_TIMED(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), radius, durationMs, 0);
	}

	void Tasker::UseNearestScenario(const bool warp, const float distance, const int durationMs) const
	{
		const MMath::Vector3 position = owner->GetPosition();

		if (warp)
		{
			TASK::TASK_USE_NEAREST_SCENARIO_TO_COORD_WARP(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), position.X, position.Y, position.Z, distance, durationMs);
			return;
		}
	
		TASK::TASK_USE_NEAREST_SCENARIO_TO_COORD(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), position.X, position.Y, position.Z, distance, durationMs);
	}

	void Tasker::StopScenario() const
	{
		if (!owner->IsUsingAnyScenario())
		{ return; }
	
		PED::SET_PED_SHOULD_PLAY_NORMAL_SCENARIO_EXIT(owner->GetHandle());
		ClearTasks();
	}

	void Tasker::FleeFrom(const ModAPI::Ped& pedToFleeFrom, const int durationMs) const
	{ TASK::TASK_SMART_FLEE_PED(owner->GetHandle(), pedToFleeFrom.GetHandle(), -1, durationMs, true, false); }

	void Tasker::FleeFrom(const ModAPI::Ped& pedToFleeFrom, const float distance) const
	{ TASK::TASK_SMART_FLEE_PED(owner->GetHandle(), pedToFleeFrom.GetHandle(), distance, -1, true, false); }

	void Tasker::FleeFrom(const MMath::Vector3& position, const int durationMs) const
	{ TASK::TASK_SMART_FLEE_COORD(owner->GetHandle(), position.X, position.Y, position.Z, -1, durationMs, true, false); }

	void Tasker::FleeFrom(const MMath::Vector3& position, const float distance) const
	{ TASK::TASK_SMART_FLEE_COORD(owner->GetHandle(), position.X, position.Y, position.Z, distance, -1, true, false); }

	void Tasker::FollowPointRoute(const std::vector<MMath::Vector3>& points, const float speed) const
	{
		if (points.empty())
		{ return; }
	
		TASK::TASK_FLUSH_ROUTE();
		for (const auto routePoint : points)
		{ TASK::TASK_EXTEND_ROUTE(routePoint.X, routePoint.Y, routePoint.Z); }
	
		TASK::TASK_FOLLOW_POINT_ROUTE(owner->GetHandle(), speed, 0);
	}

	void Tasker::GoTo(const ModAPI::Entity& target) const
	{ GoTo(target, 2.0f, -1); }

	void Tasker::GoTo(const ModAPI::Entity& target, const float stopDistance) const
	{ GoTo(target, stopDistance, -1); }

	void Tasker::GoTo(const ModAPI::Entity& target, const float stopDistance, const int timeoutMs) const
	{ TASK::TASK_GO_TO_ENTITY(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), target.GetHandle(), timeoutMs, stopDistance, 2.0f, 2.0f, 0); }

	void Tasker::GoTo(const MMath::Vector3& position) const
	{ GoTo(position, false, -1); }

	void Tasker::GoTo(const MMath::Vector3& position, const bool ignorePaths) const
	{ GoTo(position, ignorePaths, -1); }

	void Tasker::GoTo(const MMath::Vector3& position, bool ignorePaths, int timeoutMs) const
	{
		// TODO: Implement
	}

	void Tasker::FollowToOffsetFromEntity(const ModAPI::Entity& target, const MMath::Vector3& offset, const float moveSpeed, const int timeoutMs,
	                                              const float stoppingRange, const bool persistFollowing) const
	{ TASK::TASK_FOLLOW_TO_OFFSET_OF_ENTITY(owner->GetHandle(), target.GetHandle(), offset.X, offset.Y, offset.Z, moveSpeed, timeoutMs, stoppingRange, persistFollowing); }

	void Tasker::GuardCurrentPosition() const
	{ TASK::TASK_GUARD_CURRENT_POSITION(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), 35.0f, 35.0f, TRUE); }

	void Tasker::HandsUp(const int durationMs) const
	{ TASK::TASK_HANDS_UP(owner->GetHandle(), durationMs, NULL, -1, false); }

	void Tasker::HandsUp(const int durationMs, const Ped& facingTarget) const
	{ TASK::TASK_HANDS_UP(owner->GetHandle(), durationMs, facingTarget.GetHandle(), -1, false);  }

	void Tasker::Jump(const bool superJump) const
	{ TASK::TASK_JUMP(owner->GetHandle(), true, superJump, superJump); }

	void Tasker::LeaveVehicle(const Enums::eLeaveVehicleFlag leaveFlag) const
	{ TASK::TASK_LEAVE_ANY_VEHICLE(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), 0, leaveFlag); }

	void Tasker::LeaveVehicle(const ModAPI::Vehicle& vehicle, const Enums::eLeaveVehicleFlag leaveFlag) const
	{ TASK::TASK_LEAVE_VEHICLE(IsSequenceTaskOpen() ? 0 : owner->GetHandle(), vehicle.GetHandle(), leaveFlag); }

	void Tasker::LookAt(const ModAPI::Entity& target, const int durationMs) const
	{ TASK::TASK_LOOK_AT_ENTITY(owner->GetHandle(), target.GetHandle(), durationMs, 2048, 3); }

	void ModAPI::Tasker::LookAt(const MMath::Vector3& position, const int durationMs) const
	{ TASK::TASK_LOOK_AT_COORD(owner->GetHandle(), position.X, position.Y, position.Z, durationMs, 0, 2); }

	void Tasker::OpenSequenceTask()
	{ TASK::OPEN_SEQUENCE_TASK(&currentSequenceTask); }

	void Tasker::PerformSequence()
	{
		TASK::CLOSE_SEQUENCE_TASK(currentSequenceTask);
		TASK::TASK_PERFORM_SEQUENCE(owner->GetHandle(), currentSequenceTask);
		TASK::CLEAR_SEQUENCE_TASK(&currentSequenceTask);
		currentSequenceTask = -1;
	}

	void Tasker::ClearTasks(const bool immediately) const
	{
		if (immediately)
		{ TASK::CLEAR_PED_TASKS_IMMEDIATELY(owner->GetHandle()); }
		else
		{ TASK::CLEAR_PED_TASKS(owner->GetHandle()); }
	}

	void Tasker::PlayAnimation(const std::string& animDict, const std::string& animName, const float speed, const int durationMs, const Enums::eAnimationFlag flags, const float playbackRate, const BOOL lockX, const BOOL lockY, const BOOL lockZ) const
	{ TASK::TASK_PLAY_ANIM(owner->GetHandle(), animDict.c_str(), animName.c_str(), speed, speed, durationMs, flags, playbackRate, lockX, lockY, lockZ); }

	void Tasker::StopAnimation(const std::string& animDict, const std::string& animName, const float blendOutSpeed) const
	{ TASK::STOP_ANIM_TASK(owner->GetHandle(), animDict.c_str(), animName.c_str(), blendOutSpeed); }

	void Tasker::ShockingEventReact(const int eventHandle) const
	{ TASK::TASK_SHOCKING_EVENT_REACT(owner->GetHandle(), eventHandle); }

	void Tasker::ReloadWeapon() const
	{ TASK::TASK_RELOAD_WEAPON(owner->GetHandle(), 1); }

	bool Tasker::IsSequenceTaskOpen() const
	{ return currentSequenceTask != -1; }
}
