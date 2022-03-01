#pragma once
#include <string>
#include <vector>


#include <shsdk/types.h>
#include "enums/eVehicleFlags.h"
#include "shsdk/enums.h"

struct Vector3;
enum eVehicleSeat : int;

namespace ModAPI
{
	class Vehicle;
	class Entity;
	class Ped;

	class Tasker {
	public:
		Tasker(const Ped& owner);

		void EveryoneLeaveVehicle(const Vehicle& vehicle);
		void AchieveHeading(float heading);
		void AchieveHeading(float heading, int timeoutMs);
		void AimAt(const Entity& target, int durationMs);
		void AimAt(const Vector3& aimPosition, int durationMs);
		void Arrest(const Ped& pedToArrest) const;
		void Climb() const;
		void Cower(int durationMs) const;
		void Cruise(const Vehicle& vehicle, float speed) const;
		void Cruise(const Vehicle& vehicle, float speed, eDrivingStyle drivingStyle) const;
		void DriveTo(const Vehicle& vehicle, const Vector3& position, float stopRange, float speed) const;
		void DriveTo(const Vehicle& vehicle, const Vector3& position, float stopRange, float speed, eDrivingStyle drivingStyle) const;
		void EnterVehicle(const Vehicle& vehicle, eVehicleSeat seat) const;
		void EnterVehicle(const Vehicle& vehicle, eVehicleSeat seat, int timeoutMs) const;
		void EnterVehicle(const Vehicle& vehicle, eVehicleSeat seat, int timeoutMs, float speed) const;
		void EnterVehicle(const Vehicle& vehicle, eVehicleSeat seat, int timeoutMs, float speed, int flag) const;
		void EnterClosestVehicle(std::vector<EntityHandle>& entitiesToIgnore) const;
		void ExitVehicle() const;
		void ExitVehicle(const Vehicle& vehicle, LeaveVehicleFlags flag = LeaveVehicleFlags::None) const;
		void DismountExit() const;
		void FightAgainst(const Ped& target) const;
		void FightAgainst(const Ped& target, int durationMs) const;
		void FightAgainstHatedTargets(float radius) const;
		void FightAgainstHatedTargets(float radius, int durationMs) const;
		void UseNearestScenario(bool warp = false, float distance = 10.0f, int durationMs = 0) const;
		void StopScenario() const;
		void FleeFrom(const Ped& pedToFleeFrom);
		void FleeFrom(const Ped& pedToFleeFrom, int durationMs);
		void FleeFrom(const Vector3& position);
		void FleeFrom(const Vector3& position, int durationMs);
		void FollowPointRoute(Vector3 points[]);

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
		void GoTo(const Vector3& position) const;

		/**
		 * \brief Tasks the ped to go to the specified position.
		 * \param position The position to go to.
		 * \param ignorePaths Whether or not the ped should go straight to the position without pathfinding.
		 */
		void GoTo(const Vector3& position, bool ignorePaths) const;

		/**
		 * \brief Tasks the ped to go to the specified position.
		 * \param position The position to go to.
		 * \param ignorePaths Whether or not the ped should go straight to the position without pathfinding.
		 * \param timeoutMs The timeout in milliseconds. Can be set to -1 if the timeout should be ignored.
		 */
		void GoTo(const Vector3& position, bool ignorePaths, int timeoutMs) const;
		void FollowToOffsetFromEntity(const Entity& target, const Vector3& offset, int timeoutMs, float stoppingRange);
		void FollowToOffsetFromEntity(const Entity& target, const Vector3& offset, int timeoutMs, float stoppingRange, bool persistFollowing);
		void GuardCurrentPosition() const;
		void HandsUp(int durationMs);
		void Jump();
		void LeaveVehicle(LeaveVehicleFlags leaveFlag) const;
		void LeaveVehicle(const Vehicle& vehicle, LeaveVehicleFlags leaveFlag) const;
		void LookAt(const Entity& target);
		void LookAt(const Entity& target, int durationMs);
		void LookAt(const Vector3& position);
		void LookAt(const Vector3& position, int durationMs);
		void OpenSequenceTask();
		void PerformSequence();
		void ClearTasks(bool immediately = false) const;
		void PlayAnimation(const std::string& animDict, const std::string& animName);
		void PlayAnimation(const std::string& animDict, const std::string& animName, float speed, int durationMs, float playbackRate);
		//void PlayAnimation(std::string animDict, std::string animName, float blendInSpeed, int durationMs, eAnimationFlags flags); // TODO: Implement when eAnimationFlags is implemented
		//void PlayAnimation(std::string animDict, std::string animName, float blendInSpeed, float blendOutSpeed, int durationMs, eAnimationFlags flags, float playbackRate, float timeoutMs = 1000.0f);
		void ClearAnimation(const std::string& animDict, const std::string& animName, float blendOutSpeed = -8.0f);
		void ReactToEvent();
		void ReloadWeapon();

	
	private:
		[[nodiscard]] bool IsSequenceTaskOpen() const;
		
		const Ped* owner;
		TaskSequence currentSequenceTask {-1};
	};
}
