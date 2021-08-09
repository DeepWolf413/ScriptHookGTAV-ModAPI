#include "Entity.h"

#include <memory>
#include <valarray>
#include <shsdk/natives.h>

#include "Model.h"
#include "Ped.h"
#include "StdUtils.h"
#include "Vehicle.h"

ModAPI::Entity::Entity(const EntityHandle handle)
{ this->handle = handle; }

std::unique_ptr<ModAPI::Entity> ModAPI::Entity::FromHandle(EntityHandle handle)
{ return std::make_unique<Entity>(handle); }

bool ModAPI::Entity::Exists(Entity* entity)
{ return entity != nullptr && entity->Exists(); }

bool ModAPI::Entity::Exists(const EntityHandle entity)
{ return ENTITY::DOES_ENTITY_EXIST(entity); }

Hash ModAPI::Entity::GetModel() const
{ return ENTITY::GET_ENTITY_MODEL(handle); }

EntityHandle ModAPI::Entity::GetHandle() const
{ return handle; }

void ModAPI::Entity::MarkAsNoLongerNeeded()
{
	SetPersistent(false);
	ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&handle);
}

void ModAPI::Entity::Delete()
{
	if(!Exists())
	{
		// TODO: Log error "Failed to delete entity. Entity handle doesn't exist.".
		return;
	}

	SetPersistent(false);
	PED::DELETE_PED(&handle);
}

bool ModAPI::Entity::Exists() const
{ return ENTITY::DOES_ENTITY_EXIST(handle); }

bool ModAPI::Entity::IsModel(const Hash modelHash) const
{ return GetModel() == modelHash; }

eEntityType ModAPI::Entity::GetType() const
{ return static_cast<eEntityType>(ENTITY::GET_ENTITY_TYPE(handle)); }

bool ModAPI::Entity::IsPersistent() const
{ return ENTITY::IS_ENTITY_A_MISSION_ENTITY(handle); }

void ModAPI::Entity::SetPersistent(const bool persist) const
{ ENTITY::SET_ENTITY_AS_MISSION_ENTITY(handle, persist, !persist); }

void ModAPI::Entity::FreezePosition(const bool freeze) const
{ ENTITY::FREEZE_ENTITY_POSITION(handle, freeze); }

int ModAPI::Entity::GetBoneIndex(const std::string boneName) const
{ return ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(handle, boneName.c_str()); }

bool ModAPI::Entity::HasBone(const std::string boneName) const
{ return GetBoneIndex(boneName) != -1; }

int ModAPI::Entity::GetHealth() const
{ return ENTITY::GET_ENTITY_HEALTH(handle); }

void ModAPI::Entity::SetHealth(const int newHealth) const
{ ENTITY::SET_ENTITY_HEALTH(handle, newHealth, 0); }

int ModAPI::Entity::GetMaxHealth() const
{ return ENTITY::GET_ENTITY_MAX_HEALTH(handle); }

void ModAPI::Entity::SetMaxHealth(const int newMaxHealth) const
{ return ENTITY::SET_ENTITY_MAX_HEALTH(handle, newMaxHealth); }

bool ModAPI::Entity::HasBeenDamagedBy(Entity* entity) const
{ return ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(handle, entity->GetHandle(), 1); }

void ModAPI::Entity::SetInvincibility(const bool enable) const
{ ENTITY::SET_ENTITY_INVINCIBLE(handle, enable); }

void ModAPI::Entity::SetOnlyDamageableByPlayer(const bool enable) const
{ return ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(handle, enable); }

bool ModAPI::Entity::IsDead() const
{ return ENTITY::IS_ENTITY_DEAD(handle, 0); }

bool ModAPI::Entity::IsAlive() const
{ return !IsDead(); }

float ModAPI::Entity::GetDistanceTo(const Entity* otherEntity, const bool useZ) const
{
	if(otherEntity == nullptr || !otherEntity->Exists())
	{
		// TODO: Log error "Failed to GetDistanceTo(). The supplied otherEntity is null, or does not exist.".
		return 0.0f;
	}
	
	const auto entityPos = GetPosition();
	const auto otherEntityPos = otherEntity->GetPosition();
	return MISC::GET_DISTANCE_BETWEEN_COORDS(entityPos.x, entityPos.y, entityPos.z, otherEntityPos.x, otherEntityPos.y, otherEntityPos.z, useZ);
}

Vector3 ModAPI::Entity::GetPosition(const bool alive) const
{ return ENTITY::GET_ENTITY_COORDS(handle, alive); }

void ModAPI::Entity::SetPosition(const Vector3 newPosition) const
{ ENTITY::SET_ENTITY_COORDS(handle, newPosition.x, newPosition.y, newPosition.z, true, true, true, false); }

void ModAPI::Entity::SetPositionNoOffset(const Vector3 newPosition) const
{ ENTITY::SET_ENTITY_COORDS_NO_OFFSET(handle, newPosition.x, newPosition.y, newPosition.z, true, true, true); }

Vector3 ModAPI::Entity::GetRotation() const
{ return ENTITY::GET_ENTITY_ROTATION(handle, 2); }

void ModAPI::Entity::SetRotation(const Vector3 newRotation) const
{ ENTITY::SET_ENTITY_ROTATION(handle, newRotation.x, newRotation.y, newRotation.z, 2, true); }

float ModAPI::Entity::GetHeading() const
{ return ENTITY::GET_ENTITY_HEADING(handle); }

void ModAPI::Entity::SetHeading(const float newHeading) const
{ return ENTITY::SET_ENTITY_HEADING(handle, newHeading); }

float ModAPI::Entity::GetHeightAboveGround() const
{ return ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(handle); }

Vector3 ModAPI::Entity::GetUpVector() const
{ return Vector3::Cross(GetRightVector(), GetForwardVector()); }

Vector3 ModAPI::Entity::GetRightVector() const
{
	const double D2R = 0.01745329251994329576923690768489;

	const auto rotation = GetRotation();
	const double num1 = std::cos(rotation.y * D2R);
	const double x = num1 * std::cos(-rotation.z * D2R);
	const double y = num1 * std::sin(rotation.z * D2R);
	const double z = std::sin(-rotation.y * D2R);
	return Vector3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
}

Vector3 ModAPI::Entity::GetForwardVector() const
{ return ENTITY::GET_ENTITY_FORWARD_VECTOR(handle); }

Vector3 ModAPI::Entity::GetOffsetInWorldCoords(const Vector3 offset) const
{ return ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(handle, offset.x, offset.y, offset.z); }

Vector3 ModAPI::Entity::GetOffsetFromWorldCoords(const Vector3 worldCoords) const
{ return ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(handle, worldCoords.x, worldCoords.y, worldCoords.z); }

Vector3 ModAPI::Entity::GetVelocity() const
{ return ENTITY::GET_ENTITY_VELOCITY(handle); }

void ModAPI::Entity::ApplyForce(const Vector3 direction) const
{ ApplyForce(direction, Vector3(), 1); }

void ModAPI::Entity::ApplyForce(const Vector3 direction, const Vector3 rotation) const
{ ApplyForce(direction, rotation, 1); }

void ModAPI::Entity::ApplyForce(const Vector3 direction, const Vector3 rotation, const int forceType) const
{ ENTITY::APPLY_FORCE_TO_ENTITY(handle, forceType, direction.x, direction.y, direction.z, rotation.x, rotation.y, rotation.z, false, false, true, true, false, true); }

void ModAPI::Entity::ApplyForceRelative(const Vector3 direction) const
{ ApplyForceRelative(direction, Vector3(), 1); }

void ModAPI::Entity::ApplyForceRelative(const Vector3 direction, const Vector3 rotation) const
{ ApplyForceRelative(direction, rotation, 1); }

void ModAPI::Entity::ApplyForceRelative(const Vector3 direction, const Vector3 rotation, const int forceType) const
{ ENTITY::APPLY_FORCE_TO_ENTITY(handle, forceType, direction.x, direction.y, direction.z, rotation.x, rotation.y, rotation.z, false, true, true, true, false, true); }

void ModAPI::Entity::SetGravity(const bool enable) const
{ PED::SET_PED_GRAVITY(handle, enable);}

bool ModAPI::Entity::HasCollidedWithAnything() const
{ return ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(handle); }

void ModAPI::Entity::SetNoCollision(Entity* otherEntity, const bool toggle) const
{ ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(handle, otherEntity->GetHandle(), !toggle); }

void ModAPI::Entity::SetAllCollision(const bool enable, const bool keepPhysics) const
{ ENTITY::SET_ENTITY_COLLISION(handle, enable, keepPhysics); }

bool ModAPI::Entity::IsInArea(const Vector3 minBounds, const Vector3 maxBounds) const
{ return ENTITY::IS_ENTITY_IN_AREA(handle, minBounds.x, minBounds.y, minBounds.z, maxBounds.x, maxBounds.y, maxBounds.z, true, true, 0); }

bool ModAPI::Entity::IsInArea(const Vector3 aPos, const Vector3 bPos, const float angle) const
{ return IsInAngledArea(aPos, bPos, angle); }

bool ModAPI::Entity::IsInAngledArea(const Vector3 origin, const Vector3 edge, const float angle) const
{ return ENTITY::IS_ENTITY_IN_ANGLED_AREA(handle, origin.x, origin.y, origin.z, edge.x, edge.y, edge.z, angle, false, true, false); }

bool ModAPI::Entity::IsInRangeOf(const Vector3 position, const float distance) const
{ return Vector3::Subtract(GetPosition(), position).Length() < distance; }

bool ModAPI::Entity::IsNearEntity(Entity* otherEntity, const Vector3 distance) const
{ return ENTITY::IS_ENTITY_AT_ENTITY(handle, otherEntity->GetHandle(), distance.x, distance.y, distance.z, false, true, 0); }

bool ModAPI::Entity::IsTouching(Model* model) const
{ return ENTITY::IS_ENTITY_TOUCHING_MODEL(handle, model->GetHash()); }

bool ModAPI::Entity::IsTouching(Entity* otherEntity) const
{ return ENTITY::IS_ENTITY_TOUCHING_ENTITY(handle, otherEntity->GetHandle()); }

void ModAPI::Entity::Detach() const
{ ENTITY::DETACH_ENTITY(handle, true, true); }

void ModAPI::Entity::AttachTo(Entity* entity, const int boneIndex) const
{ AttachTo(entity, boneIndex, Vector3(), Vector3()); }

void ModAPI::Entity::AttachTo(Entity* entity, const int boneIndex, const Vector3 position, const Vector3 rotation) const
{ ENTITY::ATTACH_ENTITY_TO_ENTITY(handle, entity->GetHandle(), boneIndex, position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, false, false, false, false, 2, true); }

bool ModAPI::Entity::IsAttached() const
{ return ENTITY::IS_ENTITY_ATTACHED(handle); }

bool ModAPI::Entity::IsAttachedTo(Entity* entity) const
{ return ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(handle, entity->GetHandle()); }

std::unique_ptr<ModAPI::Entity> ModAPI::Entity::GetEntityAttachedTo() const
{ return std::make_unique<Entity>(ENTITY::GET_ENTITY_ATTACHED_TO(handle)); }

int ModAPI::Entity::GetAlpha() const
{ return ENTITY::GET_ENTITY_ALPHA(handle); }

void ModAPI::Entity::SetAlpha(const int newAlpha) const
{ ENTITY::SET_ENTITY_ALPHA(handle, newAlpha, false); }

void ModAPI::Entity::ResetAlpha() const
{ ENTITY::RESET_ENTITY_ALPHA(handle); }

bool ModAPI::Entity::IsVisible() const
{ return ENTITY::IS_ENTITY_VISIBLE(handle); }

void ModAPI::Entity::SetVisible(const bool enable) const
{ ENTITY::SET_ENTITY_VISIBLE(handle, enable, false); }

bool ModAPI::Entity::IsOccluded() const
{ return ENTITY::IS_ENTITY_OCCLUDED(handle); }

bool ModAPI::Entity::IsOnFire() const
{ return FIRE::IS_ENTITY_ON_FIRE(handle); }

bool ModAPI::Entity::IsOnScreen() const
{ return ENTITY::IS_ENTITY_ON_SCREEN(handle); }

bool ModAPI::Entity::IsUpright() const
{ return ENTITY::IS_ENTITY_UPRIGHT(handle, 30.0f); }

bool ModAPI::Entity::IsUpsideDown() const
{ return ENTITY::IS_ENTITY_UPSIDEDOWN(handle); }

bool ModAPI::Entity::IsInAir() const
{ return ENTITY::IS_ENTITY_IN_AIR(handle); }

bool ModAPI::Entity::IsInWater() const
{ return ENTITY::IS_ENTITY_IN_WATER(handle); }

void ModAPI::Entity::SetVelocity(const Vector3 newVelocity) const
{ ENTITY::SET_ENTITY_VELOCITY(handle, newVelocity.x, newVelocity.y, newVelocity.z); }

std::vector<std::unique_ptr<ModAPI::Ped>> ModAPI::Entity::GetNearbyHumans(const int amount, std::vector<EntityHandle> entitiesToIgnore, const float maxDistance) const
{
	::PedHandle peds[256] = {};
	worldGetAllPeds(peds, 256);
	
	auto nearbyPeds = std::vector<std::unique_ptr<Ped>>();
	auto closestDistances = std::vector<float>();

	for(auto pedHandle : peds)
	{
		if(!Exists(pedHandle) || pedHandle == GetHandle() || Utils::StdUtils::VectorContainsElement<EntityHandle>(entitiesToIgnore, pedHandle))
		{ continue; }

		auto ped = std::make_unique<Ped>(pedHandle);
		if(!ped->IsHuman())
		{ continue; }
		
		if(nearbyPeds.size() < amount)
		{
			const auto pedToCheck = nearbyPeds.size() > 0 ? nearbyPeds.back().get() : ped.get();
			const float distanceToPed = pedToCheck->GetDistanceTo(this);
			if(distanceToPed > maxDistance)
			{ continue; }
			
			nearbyPeds.push_back(std::move(ped));
			closestDistances.push_back(distanceToPed);
			continue;
		}

		for(size_t i = 0; i < nearbyPeds.size(); ++i)
		{
			const float distance = ped->GetDistanceTo(this);
			if(distance > maxDistance || distance >= closestDistances[i])
			{ continue; }

			nearbyPeds[i] = std::move(ped);
			closestDistances[i] = distance;
		}
	}

	return std::move(nearbyPeds);
}

std::vector<std::unique_ptr<ModAPI::Vehicle>> ModAPI::Entity::GetNearbyVehicles(const int amount, const std::vector<EntityHandle> entitiesToIgnore, const float maxDistance) const
{
	VehicleHandle vehicles[256] = {};
	worldGetAllVehicles(vehicles, 256);
	
	auto nearbyVehicles = std::vector<std::unique_ptr<Vehicle>>();
	auto closestDistances = std::vector<float>();

	for(auto vehicleHandle : vehicles)
	{
		if(!Exists(vehicleHandle) || Utils::StdUtils::VectorContainsElement(entitiesToIgnore, vehicleHandle))
		{ continue; }

		auto vehicle = std::make_unique<Vehicle>(vehicleHandle);
		if(vehicle->GetType() != eEntityType::Vehicle || !vehicle->IsSeatFree(eVehicleSeat::VehicleSeatDriver))
		{ continue; }

		if(nearbyVehicles.size() < amount)
		{
			const auto vehicleToCheck = !nearbyVehicles.empty() ? nearbyVehicles.back().get() : vehicle.get();
			const float distanceToVehicle = vehicleToCheck->GetDistanceTo(this);
			if(distanceToVehicle > maxDistance)
			{ continue; }
			
			nearbyVehicles.push_back(std::move(vehicle));
			closestDistances.push_back(distanceToVehicle);
			continue;
		}

		for(size_t i = 0; i < nearbyVehicles.size(); ++i)
		{
			const float distance = vehicle->GetDistanceTo(this);
			if(distance > maxDistance || distance >= closestDistances[i])
			{ continue; }

			nearbyVehicles[i] = std::move(vehicle);
			closestDistances[i] = distance;
		}
	}

	return std::move(nearbyVehicles);
}