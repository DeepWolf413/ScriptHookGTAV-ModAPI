#pragma once
#include <enums.h>
#include <string>
#include <vector>
#include <types.h>

#include "Entity.h"
#include "Enums.h"
#include "Vehicle.h"

namespace ModAPI
{
	class Ped;
	
	namespace MMath
	{
		struct Vector3;
	}

	class Tasker {
	public:
		Tasker(Ped& owner);
		
		void AchieveHeading(float heading, int timeoutMs = -1) const;
		void AimAt(const Entity& target, int durationMs = -1) const;
		void AimAt(const MMath::Vector3& aimPosition, int durationMs = -1) const;
		void Arrest(const Ped& pedToArrest) const;
		void Climb() const;
		void Cower(int durationMs) const;
		void Cruise(const Entity& vehicle, float speed) const;
		void Cruise(const Entity& vehicle, float speed, eDrivingStyle drivingStyle) const;
		void DriveTo(const Entity& vehicle, const MMath::Vector3& position, float stopRange, float speed) const;
		void DriveTo(const Entity& vehicle, const MMath::Vector3& position, float stopRange, float speed, eDrivingStyle drivingStyle) const;
		void EnterVehicle(const Entity& vehicle, eVehicleSeat seat) const;
		void EnterVehicle(const Entity& vehicle, eVehicleSeat seat, int timeoutMs) const;
		void EnterVehicle(const Entity& vehicle, eVehicleSeat seat, int timeoutMs, float speed) const;
		void EnterVehicle(const Entity& vehicle, eVehicleSeat seat, int timeoutMs, float speed, int flag) const;
		void EnterClosestVehicle(std::vector<::Entity>& entitiesToIgnore) const;
		void ExitVehicle() const;
		void ExitVehicle(const Vehicle& vehicle, Enums::eLeaveVehicleFlag flag = Enums::eLeaveVehicleFlag::None) const;
		void DismountExit() const;
		void FightAgainst(const Ped& target) const;
		void FightAgainst(const Ped& target, int durationMs) const;
		void FightAgainstHatedTargets(float radius) const;
		void FightAgainstHatedTargets(float radius, int durationMs) const;
		void UseNearestScenario(bool warp = false, float distance = 10.0f, int durationMs = 0) const;
		void StopScenario() const;
		void FleeFrom(const Ped& pedToFleeFrom, int durationMs = -1) const;
		void FleeFrom(const Ped& pedToFleeFrom, float distance = 50) const;
		void FleeFrom(const MMath::Vector3& position, int durationMs = -1) const;
		void FleeFrom(const MMath::Vector3& position, float distance = 50) const;
		void FollowPointRoute(const std::vector<MMath::Vector3>& points, float speed = 2.0f) const;

		/**
		 * \brief Tasks the ped to go to the specified target entity.
		 * \param target The entity to go to.
		 */
		void GoTo(const Entity& target) const;

		/**
		 * \brief Tasks the ped to go to the specified target entity.
		 * \param target The entity to go to.
		 * \param stopDistance How far away from the entity should the ped be before it stops.
		 */
		void GoTo(const Entity& target, float stopDistance) const;
		
		/**
		 * \brief Tasks the ped to go to the specified target entity.
		 * \param target The entity to go to.
		 * \param stopDistance How far away from the entity should the ped be before it stops.
		 * \param timeoutMs The timeout in milliseconds. Can be set to -1 if the timeout should be ignored.
		 */
		void GoTo(const Entity& target, float stopDistance, int timeoutMs) const;

		/**
		 * \brief Tasks the ped to go to the specified position.
		 * \param position The position to go to.
		 */
		void GoTo(const MMath::Vector3& position) const;

		/**
		 * \brief Tasks the ped to go to the specified position.
		 * \param position The position to go to.
		 * \param ignorePaths Whether or not the ped should go straight to the position without pathfinding.
		 */
		void GoTo(const MMath::Vector3& position, bool ignorePaths) const;

		/**
		 * \brief Tasks the ped to go to the specified position.
		 * \param position The position to go to.
		 * \param ignorePaths Whether or not the ped should go straight to the position without pathfinding.
		 * \param timeoutMs The timeout in milliseconds. Can be set to -1 if the timeout should be ignored.
		 */
		void GoTo(const MMath::Vector3& position, bool ignorePaths, int timeoutMs) const;
		void FollowToOffsetFromEntity(const Entity& target, const MMath::Vector3& offset, float moveSpeed, int timeoutMs = -1, float stoppingRange = 3.0f, bool persistFollowing = false) const;
		void GuardCurrentPosition() const;
		void HandsUp(int durationMs) const;
		void HandsUp(int durationMs, const Ped& facingTarget) const;
		void Jump(bool superJump = false) const;
		void LeaveVehicle(Enums::eLeaveVehicleFlag leaveFlag) const;
		void LeaveVehicle(const Vehicle& vehicle, Enums::eLeaveVehicleFlag leaveFlag) const;
		void LookAt(const Entity& target, int durationMs = -1) const;
		void LookAt(const MMath::Vector3& position, int durationMs = -1) const;
		void OpenSequenceTask();
		void PerformSequence();
		void ClearTasks(bool immediately = false) const;
		void PlayAnimation(const std::string& animDict, const std::string& animName, float speed, int durationMs, Enums::eAnimationFlag flags, float playbackRate, BOOL lockX = 0, BOOL lockY = 0, BOOL lockZ = 0) const;
		void StopAnimation(const std::string& animDict, const std::string& animName, float blendOutSpeed = -8.0f) const;
		void ShockingEventReact(int eventHandle) const;
		void ReloadWeapon() const;

	
	private:
		[[nodiscard]] bool IsSequenceTaskOpen() const;
		
		Ped* const owner;
		TaskSequence currentSequenceTask {-1};
	};
}
