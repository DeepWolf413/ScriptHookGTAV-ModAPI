#include "Tasker.h"

#include <inc/natives.h>

#include "Ped.h"
#include "Vehicle.h"
#include "enums/eVehicleSeat.h"
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

void ModAPI::Tasker::MountEnterClosest(std::vector<EntityHandle>& entitiesToIgnore) const
{
	if(!Entity::Exists(ped))
	{
		// TODO: Log error "Failed to task ped to mount/enter closest horse/vehicle".
		return;
	}
	
	const auto nearbyEntity = ped->GetClosestHorseVehicle(entitiesToIgnore);
	if(nearbyEntity == nullptr)
	{ return; }
	
	entitiesToIgnore.push_back(nearbyEntity->GetHandle());
	if(nearbyEntity->GetType() == eEntityType::Vehicle)
	{
		const auto vehicle = std::make_unique<Vehicle>(nearbyEntity->GetHandle());
		EnterVehicle(vehicle.get(), eVehicleSeat::VS_DRIVER);
	}
	else
	{
		const auto horse = std::make_unique<Ped>(nearbyEntity->GetHandle());
		MountAnimal(horse.get(), eMountSeat::Rider);
	}
}

void ModAPI::Tasker::MountClosestAnimal() const
{
	const auto nearbyHorses = ped->GetNearbyHorses(1);

	if(!nearbyHorses.empty())
	{ MountAnimal(nearbyHorses[0].get(), eMountSeat::Rider); }
}

void ModAPI::Tasker::EnterClosestVehicle() const
{
	const auto nearbyVehicles = ped->GetNearbyVehicles(1);

	if(!nearbyVehicles.empty())
	{ EnterVehicle(nearbyVehicles[0].get(), eVehicleSeat::VS_DRIVER); }
}

void ModAPI::Tasker::ExitVehicle() const
{ TASK::TASK_LEAVE_ANY_VEHICLE(ped->GetHandle(), 0, 0); }

void ModAPI::Tasker::ExitVehicle(Vehicle* vehicle, const LeaveVehicleFlags flag) const
{ TASK::TASK_LEAVE_VEHICLE(ped->GetHandle(), vehicle->GetHandle(), static_cast<int>(flag), 0); }

void ModAPI::Tasker::MountAnimal(Ped* animal, eMountSeat seat) const
{ MountAnimal(animal, seat, 5000, 2.0f, eMountStyle::Normal); }

void ModAPI::Tasker::MountAnimal(Ped* animal, eMountSeat seat, int timerMs) const
{ MountAnimal(animal, seat, timerMs, 2.0f, eMountStyle::Normal); }

void ModAPI::Tasker::MountAnimal(Ped* animal, eMountSeat seat, int timerMs, float speed) const
{ MountAnimal(animal, seat, timerMs, speed, eMountStyle::Normal); }

void ModAPI::Tasker::MountAnimal(Ped* animal, eMountSeat seat, int timerMs, float speed, eMountStyle mountStyle) const
{ TASK::TASK_MOUNT_ANIMAL(ped->GetHandle(), animal->GetHandle(), timerMs, static_cast<int>(seat), speed, static_cast<int>(mountStyle), 0, 0); }

void ModAPI::Tasker::DismountAnimal(const int exitFlag) const
{ TASK::TASK_DISMOUNT_ANIMAL(ped->GetHandle(), exitFlag, 0, 0, 0, 0); }

void ModAPI::Tasker::DismountExit() const
{
	if(ped->IsOnMount())
	{ DismountAnimal(); }
	else if(ped->IsOnVehicle())
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

	TASK::TASK_COMBAT_HATED_TARGETS_AROUND_PED(ped->GetHandle(), radius, 0, 0);
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
	TASK::_TASK_USE_NEAREST_SCENARIO_TO_COORD(ped->GetHandle(), position.x, position.y, position.z, 10.0f, 0.0f, false, false, false, false);
}

void ModAPI::Tasker::StopScenario() const
{
	
}
