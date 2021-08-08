#pragma once
#include <string>
#include <vector>


#include <inc/types.h>
#include "enums/eMountSeat.h"
#include "enums/eMountStyle.h"
#include "enums/eVehicleFlags.h"

struct Vector3;
enum eVehicleSeat : int;

namespace ModAPI
{
	class Vehicle;
	class Entity;
	class Ped;

	class Tasker {
	public:
		Tasker(Ped* ped);

		static void EveryoneLeaveVehicle(VehicleHandle vehicle);
		
		void AchieveHeading(float heading);
		void AchieveHeading(float heading, int timeoutMs);
		void AimAt(Entity* target, int durationMs);
		void AimAt(Vector3 aimPosition, int durationMs);
		void Arrest(Ped* pedToArrest);
		void Climb();
		void Cower(int durationMs);
		void CruiseWithVehicle(Vehicle* vehicle, float speed);
		void CruiseWithVehicle(Vehicle* vehicle, float speed, int drivingStyle);
		void DriveTo(Vehicle* vehicle, Vector3 position, float radius, float speed);
		void DriveTo(Vehicle* vehicle, Vector3 position, float radius, float speed, int drivingStyle);
		void EnterVehicle(Vehicle* vehicle, eVehicleSeat seat) const;
		void EnterVehicle(Vehicle* vehicle, eVehicleSeat seat, int timeoutMs) const;
		void EnterVehicle(Vehicle* vehicle, eVehicleSeat seat, int timeoutMs, float speed) const;
		void EnterVehicle(Vehicle* vehicle, eVehicleSeat seat, int timeoutMs, float speed, int flag) const;
		void MountEnterClosest(std::vector<EntityHandle>& entitiesToIgnore) const;
		void MountClosestAnimal() const;
		void EnterClosestVehicle() const;
		void ExitVehicle() const;
		void ExitVehicle(Vehicle* vehicle, LeaveVehicleFlags flag = LeaveVehicleFlags::None) const;
		void MountAnimal(Ped* animal, eMountSeat mountSeat) const;
		void MountAnimal(Ped* animal, eMountSeat mountSeat, int timerMs) const;
		void MountAnimal(Ped* animal, eMountSeat mountSeat, int timerMs, float speed) const;
		void MountAnimal(Ped* animal, eMountSeat mountSeat, int timerMs, float speed, eMountStyle mountStyle) const;
		void DismountAnimal(int exitFlag = 1 << 18) const;
		void DismountExit() const;
		void FightAgainst(Ped* target) const;
		void FightAgainst(Ped* target, int durationMs) const;
		void FightAgainstHatedTargets(float radius) const;
		void FightAgainstHatedTargets(float radius, int durationMs) const;
		void UseNearestScenario() const;
		void StopScenario() const;
		void FleeFrom(Ped* pedToFleeFrom);
		void FleeFrom(Ped* pedToFleeFrom, int durationMs);
		void FleeFrom(Vector3 position);
		void FleeFrom(Vector3 position, int durationMs);
		void FollowPointRoute(Vector3 points[]);
		void GoTo(Entity* target);
		void GoTo(Entity* target, Vector3 offset);
		void GoTo(Entity* target, Vector3 offset, int timeoutMs);
		void GoTo(Vector3 position);
		void GoTo(Vector3 position, bool ignorePaths);
		void GoTo(Vector3 position, bool ignorePaths, int timeoutMs);
		void FollowToOffsetFromEntity(Entity* target, Vector3 offset, int timeoutMs, float stoppingRange);
		void FollowToOffsetFromEntity(Entity* target, Vector3 offset, int timeoutMs, float stoppingRange, bool persistFollowing);
		void GuardCurrentPosition();
		void HandsUp(int durationMs);
		void Jump();
		void LeaveVehicle();
		void LeaveVehicle(VehicleHandle vehicle, bool closeDoor);
		void LookAt(Entity* target);
		void LookAt(Entity* target, int durationMs);
		void LookAt(Vector3 position);
		void LookAt(Vector3 position, int durationMs);
		//void PerformSequence(TaskSequence sequence); // TODO: Implement when TaskSequence class has been made
		void PlayAnimation(std::string animDict, std::string animName);
		void PlayAnimation(std::string animDict, std::string animName, float speed, int durationMs, float playbackRate);
		//void PlayAnimation(std::string animDict, std::string animName, float blendInSpeed, int durationMs, eAnimationFlags flags); // TODO: Implement when eAnimationFlags is implemented
		//void PlayAnimation(std::string animDict, std::string animName, float blendInSpeed, float blendOutSpeed, int durationMs, eAnimationFlags flags, float playbackRate, float timeoutMs = 1000.0f);
		void ClearAnimation(std::string animDict, std::string animName, float blendOutSpeed = -8.0f);
		void ReactToEvent();
		void ReloadWeapon();

	
	private:
		Ped* ped;
	};
}
