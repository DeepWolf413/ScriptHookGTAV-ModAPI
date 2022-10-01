#include "Entity.h"

#include <memory>
#include <valarray>
#include <natives.h>

#include "Model.h"
#include "Ped.h"
#include "StdUtils.h"
#include "Vehicle.h"
#include "Math/Vector3.h"

namespace ModAPI
{
	Entity::Entity() : ModAPI::Entity(NULL)
	{}

	Entity::Entity(const ::Entity entityHandle)
	{ this->handle = entityHandle; }

	Entity::operator int() const
	{ return GetHandle(); }

	bool Entity::Exists(const ModAPI::Entity* entity)
	{ return entity != nullptr && entity->Exists(); }

	bool Entity::Exists(const ::Entity entityHandle)
	{ return ENTITY::DOES_ENTITY_EXIST(entityHandle); }

	ModAPI::Model Entity::GetModel() const
	{ return {ENTITY::GET_ENTITY_MODEL(handle)}; }

	::Entity Entity::GetHandle() const
	{ return handle; }

	void Entity::MarkAsNoLongerNeeded()
	{
		SetPersistent(false);
		ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&handle);
	}

	void Entity::Delete()
	{
		if(!Exists())
		{
			// TODO: Log error "Failed to delete entity. Entity handle doesn't exist.".
			return;
		}

		SetPersistent(false);
		PED::DELETE_PED(&handle);
	}

	bool Entity::Exists() const
	{ return ENTITY::DOES_ENTITY_EXIST(handle); }

	bool Entity::IsModel(const Hash modelHash) const
	{ return GetModel().GetHash() == modelHash; }

	bool Entity::IsModel(const Model& model) const
	{ return GetModel().GetHash() == model.GetHash(); }

	Enums::eEntityType Entity::GetType() const
	{ return static_cast<Enums::eEntityType>(ENTITY::GET_ENTITY_TYPE(handle)); }

	bool Entity::IsPersistent() const
	{ return ENTITY::IS_ENTITY_A_MISSION_ENTITY(handle); }

	void Entity::SetPersistent(const bool persist) const
	{ ENTITY::SET_ENTITY_AS_MISSION_ENTITY(handle, persist, !persist); }

	void Entity::FreezePosition(const bool freeze) const
	{ ENTITY::FREEZE_ENTITY_POSITION(handle, freeze); }

	int Entity::GetBoneIndex(const std::string& boneName) const
	{ return ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(handle, boneName.c_str()); }

	bool Entity::HasBone(const std::string& boneName) const
	{ return GetBoneIndex(boneName) != -1; }

	int Entity::GetHealth() const
	{ return ENTITY::GET_ENTITY_HEALTH(handle); }

	void Entity::SetHealth(const int newHealth) const
	{ ENTITY::SET_ENTITY_HEALTH(handle, newHealth, 0); }

	int Entity::GetMaxHealth() const
	{ return ENTITY::GET_ENTITY_MAX_HEALTH(handle); }

	void Entity::SetMaxHealth(const int newMaxHealth) const
	{ return ENTITY::SET_ENTITY_MAX_HEALTH(handle, newMaxHealth); }

	bool Entity::HasBeenDamagedBy(const ModAPI::Entity& entity) const
	{ return ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(handle, entity.GetHandle(), 1); }

	void Entity::SetInvincibility(const bool enable) const
	{ ENTITY::SET_ENTITY_INVINCIBLE(handle, enable); }

	void Entity::SetOnlyDamageableByPlayer(const bool enable) const
	{ return ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(handle, enable); }

	void Entity::SetOnlyDamageableByRelationshipGroup(const bool enable, const Hash relationshipGroup) const
	{ ENTITY::SET_ENTITY_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP(handle, enable, relationshipGroup); }

	void Entity::SetCanBeDamagedByRelationshipGroup(const bool enable, const Hash relationshipGroup) const
	{ ENTITY::SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP(handle, enable, static_cast<int>(relationshipGroup)); }

	bool Entity::IsDead() const
	{ return ENTITY::IS_ENTITY_DEAD(handle, 0); }

	bool Entity::IsAlive() const
	{ return !IsDead(); }

	float Entity::GetDistanceTo(const ModAPI::Entity& otherEntity, const bool useZ) const
	{
		if(!otherEntity.Exists())
		{
			// TODO: Log error "Failed to GetDistanceTo(). The supplied otherEntity does not exist.".
			return 0.0f;
		}
	
		const auto entityPos = GetPosition();
		const auto otherEntityPos = otherEntity.GetPosition();
		return MISC::GET_DISTANCE_BETWEEN_COORDS(entityPos.X, entityPos.Y, entityPos.Z, otherEntityPos.X, otherEntityPos.Y, otherEntityPos.Z, useZ);
	}

	MMath::Vector3 Entity::GetPosition(const bool alive) const
	{ return MMath::Vector3::FromSHVector3(ENTITY::GET_ENTITY_COORDS(handle, alive)); }

	void Entity::SetPosition(const MMath::Vector3& newPosition) const
	{ ENTITY::SET_ENTITY_COORDS(handle, newPosition.X, newPosition.Y, newPosition.Z, true, true, true, false); }

	void Entity::SetPositionNoOffset(const MMath::Vector3& newPosition) const
	{ ENTITY::SET_ENTITY_COORDS_NO_OFFSET(handle, newPosition.X, newPosition.Y, newPosition.Z, true, true, true); }

	MMath::Vector3 Entity::GetRotation() const
	{ return MMath::Vector3::FromSHVector3(ENTITY::GET_ENTITY_ROTATION(handle, 2)); }

	void Entity::SetRotation(const MMath::Vector3& newRotation) const
	{ ENTITY::SET_ENTITY_ROTATION(handle, newRotation.X, newRotation.Y, newRotation.Z, 2, true); }

	float Entity::GetHeading() const
	{ return ENTITY::GET_ENTITY_HEADING(handle); }

	void Entity::SetHeading(const float newHeading) const
	{ return ENTITY::SET_ENTITY_HEADING(handle, newHeading); }

	float Entity::GetHeightAboveGround() const
	{ return ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(handle); }

	MMath::Vector3 Entity::GetUpVector() const
	{ return MMath::Vector3::Cross(GetRightVector(), GetForwardVector()); }

	MMath::Vector3 Entity::GetRightVector() const
	{
		constexpr double D2R = 0.01745329251994329576923690768489;

		const auto rotation = GetRotation();
		const double num1 = std::cos(rotation.Y * D2R);
		const double x = num1 * std::cos(-rotation.Z * D2R);
		const double y = num1 * std::sin(rotation.Z * D2R);
		const double z = std::sin(-rotation.Y * D2R);
		return {static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)};
	}

	MMath::Vector3 Entity::GetForwardVector() const
	{ return MMath::Vector3::FromSHVector3(ENTITY::GET_ENTITY_FORWARD_VECTOR(handle)); }

	MMath::Vector3 Entity::GetOffsetInWorldCoords(const MMath::Vector3& offset) const
	{ return MMath::Vector3::FromSHVector3(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(handle, offset.X, offset.Y, offset.Z)); }

	MMath::Vector3 Entity::GetOffsetFromWorldCoords(const MMath::Vector3& worldCoords) const
	{ return MMath::Vector3::FromSHVector3(ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(handle, worldCoords.X, worldCoords.Y, worldCoords.Z)); }

	MMath::Vector3 Entity::GetVelocity() const
	{ return MMath::Vector3::FromSHVector3(ENTITY::GET_ENTITY_VELOCITY(handle)); }

	void Entity::ApplyForce(const MMath::Vector3& velocity) const
	{ ApplyForce(velocity, MMath::Vector3(), 3); }

	void Entity::ApplyForce(const MMath::Vector3& velocity, const MMath::Vector3& rotation) const
	{ ApplyForce(velocity, rotation, 3); }

	void Entity::ApplyForce(const MMath::Vector3& velocity, const MMath::Vector3& rotation, const int forceType) const
	{ ENTITY::APPLY_FORCE_TO_ENTITY(handle, forceType, velocity.X, velocity.Y, velocity.Z, rotation.X, rotation.Y, rotation.Z, false, false, true, true, false, true); }

	void Entity::ApplyForceRelative(const MMath::Vector3& velocity) const
	{ ApplyForceRelative(velocity, MMath::Vector3(), 3); }

	void Entity::ApplyForceRelative(const MMath::Vector3& velocity, const MMath::Vector3& rotation) const
	{ ApplyForceRelative(velocity, rotation, 3); }

	void Entity::ApplyForceRelative(const MMath::Vector3& velocity, const MMath::Vector3& rotation, const int forceType) const
	{ ENTITY::APPLY_FORCE_TO_ENTITY(handle, forceType, velocity.X, velocity.Y, velocity.Z, rotation.X, rotation.Y, rotation.Z, false, true, true, true, false, true); }

	void Entity::ApplyForceTowardsEntity(const ModAPI::Entity& entityToPullTowards, const float force) const
	{
		MMath::Vector3 directionTowardsEntity = entityToPullTowards.GetPosition() - GetPosition();
		directionTowardsEntity.Normalize();
		ApplyForce(directionTowardsEntity * force);
	}

	void Entity::SetGravity(const bool enable) const
	{ PED::SET_PED_GRAVITY(handle, enable);}

	bool Entity::HasCollidedWithAnything() const
	{ return ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(handle); }

	void Entity::SetNoCollision(const ModAPI::Entity& otherEntity, const bool toggle) const
	{ ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(handle, otherEntity.GetHandle(), !toggle); }

	void Entity::SetAllCollision(const bool enable, const bool keepPhysics) const
	{ ENTITY::SET_ENTITY_COLLISION(handle, enable, keepPhysics); }

	bool Entity::IsInArea(const MMath::Vector3& minBounds, const MMath::Vector3& maxBounds) const
	{ return ENTITY::IS_ENTITY_IN_AREA(handle, minBounds.X, minBounds.Y, minBounds.Z, maxBounds.X, maxBounds.Y, maxBounds.Z, true, true, 0); }

	bool Entity::IsInArea(const MMath::Vector3& aPos, const MMath::Vector3& bPos, const float angle) const
	{ return IsInAngledArea(aPos, bPos, angle); }

	bool Entity::IsInAngledArea(const MMath::Vector3& origin, const MMath::Vector3& edge, const float angle) const
	{ return ENTITY::IS_ENTITY_IN_ANGLED_AREA(handle, origin.X, origin.Y, origin.Z, edge.X, edge.Y, edge.Z, angle, false, true, false); }

	bool Entity::IsInRangeOf(const MMath::Vector3& position, const float distance) const
	{ return (GetPosition() - position).Length() < distance; }

	bool Entity::IsNearEntity(const ModAPI::Entity& otherEntity, const MMath::Vector3& distance) const
	{ return ENTITY::IS_ENTITY_AT_ENTITY(handle, otherEntity.GetHandle(), distance.X, distance.Y, distance.Z, false, true, 0); }

	bool Entity::IsTouching(const Model& model) const
	{ return ENTITY::IS_ENTITY_TOUCHING_MODEL(handle, model.GetHash()); }

	bool Entity::IsTouching(const ModAPI::Entity& otherEntity) const
	{ return ENTITY::IS_ENTITY_TOUCHING_ENTITY(handle, otherEntity.GetHandle()); }

	void Entity::Detach() const
	{ ENTITY::DETACH_ENTITY(handle, true, true); }

	void Entity::AttachTo(const ModAPI::Entity& entity, const int boneIndex) const
	{ AttachTo(entity, boneIndex, MMath::Vector3(), MMath::Vector3()); }

	void Entity::AttachTo(const ModAPI::Entity& entity, const int boneIndex, const MMath::Vector3& position, const MMath::Vector3& rotation) const
	{ ENTITY::ATTACH_ENTITY_TO_ENTITY(handle, entity.GetHandle(), boneIndex, position.X, position.Y, position.Z, rotation.X, rotation.Y, rotation.Z, false, false, false, false, 2, true, 0); }

	bool Entity::IsAttached() const
	{ return ENTITY::IS_ENTITY_ATTACHED(handle); }

	bool Entity::IsAttachedTo(const ModAPI::Entity& entity) const
	{ return ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(handle, entity.GetHandle()); }

	ModAPI::Entity Entity::GetEntityAttachedTo() const
	{ return {ENTITY::GET_ENTITY_ATTACHED_TO(handle)}; }

	int Entity::GetAlpha() const
	{ return ENTITY::GET_ENTITY_ALPHA(handle); }

	void Entity::SetAlpha(const int newAlpha) const
	{ ENTITY::SET_ENTITY_ALPHA(handle, newAlpha, false); }

	void Entity::ResetAlpha() const
	{ ENTITY::RESET_ENTITY_ALPHA(handle); }

	bool Entity::IsVisible() const
	{ return ENTITY::IS_ENTITY_VISIBLE(handle); }

	void Entity::SetVisible(const bool enable) const
	{ ENTITY::SET_ENTITY_VISIBLE(handle, enable, false); }

	bool Entity::IsOccluded() const
	{ return ENTITY::IS_ENTITY_OCCLUDED(handle); }

	bool Entity::IsOnFire() const
	{ return FIRE::IS_ENTITY_ON_FIRE(handle); }

	bool Entity::IsOnScreen() const
	{ return ENTITY::IS_ENTITY_ON_SCREEN(handle); }

	bool Entity::IsUpright() const
	{ return ENTITY::IS_ENTITY_UPRIGHT(handle, 30.0f); }

	bool Entity::IsUpsideDown() const
	{ return ENTITY::IS_ENTITY_UPSIDEDOWN(handle); }

	bool Entity::IsInAir() const
	{ return ENTITY::IS_ENTITY_IN_AIR(handle); }

	bool Entity::IsInWater() const
	{ return ENTITY::IS_ENTITY_IN_WATER(handle); }

	std::vector<ModAPI::Entity> Entity::GetNearbyPeds(const int amount, const bool ignorePedsInVehicle,
	                                                                        const std::vector<ModAPI::Entity>& pedsToIgnore, const float maxDistance) const
	{
		::Ped pedHandles[256] = {};
		worldGetAllPeds(pedHandles, 256);
	
		auto nearbyPeds = std::vector<ModAPI::Entity>();
		auto closestDistances = std::vector<float>();

		for(const auto pedHandle : pedHandles)
		{
			const auto ped = ModAPI::Ped(pedHandle);
			if(!Exists(pedHandle) || pedHandle == GetHandle() || Utils::StdUtils::VectorContainsElement<ModAPI::Entity>(pedsToIgnore, pedHandle))
			{ continue; }

			if(ignorePedsInVehicle && ped.IsInAnyVehicle())
			{ continue; }

			const float distanceToPed = ped.GetDistanceTo(*this);
			if (distanceToPed > maxDistance)
			{ continue; }

			if(static_cast<int>(nearbyPeds.size()) < amount)
			{
				nearbyPeds.push_back(ped);
				closestDistances.push_back(distanceToPed);
				continue;
			}

			for(size_t i = 0; i < nearbyPeds.size(); ++i)
			{
				if(distanceToPed >= closestDistances[i])
				{ continue; }

				nearbyPeds[i] = ModAPI::Entity(pedHandle);
				closestDistances[i] = distanceToPed;
				break;
			}
		}

		return nearbyPeds;
	}

	void Entity::SetVelocity(const MMath::Vector3& newVelocity) const
	{ ENTITY::SET_ENTITY_VELOCITY(handle, newVelocity.X, newVelocity.Y, newVelocity.Z); }

	std::vector<ModAPI::Entity> Entity::GetNearbyHumans(const int amount, const bool ignorePedsInVehicle, const std::vector<ModAPI::Entity>& humansToIgnore, const float maxDistance) const
	{
		::Ped pedHandles[256] = {};
		worldGetAllPeds(pedHandles, 256);
	
		auto nearbyPeds = std::vector<ModAPI::Entity>();
		auto closestDistances = std::vector<float>();

		for(const auto pedHandle : pedHandles)
		{
			auto ped = ModAPI::Ped(pedHandle);
			if(!Exists(pedHandle) || pedHandle == GetHandle() || Utils::StdUtils::VectorContainsElement<ModAPI::Entity>(humansToIgnore, pedHandle))
			{ continue; }

			if(!ped.IsHuman() || ignorePedsInVehicle && ped.IsInAnyVehicle())
			{ continue; }

			const float distanceToPed = ped.GetDistanceTo(*this);
			if (distanceToPed > maxDistance)
			{ continue; }

			if(static_cast<int>(nearbyPeds.size()) < amount)
			{
				nearbyPeds.push_back(ped);
				closestDistances.push_back(distanceToPed);
				continue;
			}

			for(size_t i = 0; i < nearbyPeds.size(); ++i)
			{
				if(distanceToPed >= closestDistances[i])
				{ continue; }

				nearbyPeds[i] = ModAPI::Entity(ped.GetHandle());
				closestDistances[i] = distanceToPed;
				break;
			}
		}

		return nearbyPeds;
	}

	std::vector<ModAPI::Entity> Entity::GetNearbyAnimals(const int amount,
	                                                                           const std::vector<ModAPI::Entity>& animalsToIgnore, const float maxDistance) const
	{
		::Ped pedHandles[256] = {};
		worldGetAllPeds(pedHandles, 256);
	
		auto nearbyPeds = std::vector<ModAPI::Entity>();
		auto closestDistances = std::vector<float>();

		for(const auto pedHandle : pedHandles)
		{
			const auto ped = ModAPI::Ped(pedHandle);
			if(!Exists(pedHandle) || pedHandle == GetHandle() || Utils::StdUtils::VectorContainsElement<ModAPI::Entity>(animalsToIgnore, pedHandle))
			{ continue; }

			if(!ped.IsAnimal())
			{ continue; }

			const float distanceToPed = ped.GetDistanceTo(*this);
			if (distanceToPed > maxDistance)
			{ continue; }

			if(static_cast<int>(nearbyPeds.size()) < amount)
			{
				nearbyPeds.push_back(ped);
				closestDistances.push_back(distanceToPed);
				continue;
			}

			for(size_t i = 0; i < nearbyPeds.size(); ++i)
			{
				if(distanceToPed >= closestDistances[i])
				{ continue; }

				nearbyPeds[i] = ModAPI::Entity(pedHandle);
				closestDistances[i] = distanceToPed;
				break;
			}
		}

		return nearbyPeds;
	}

	std::vector<ModAPI::Entity> Entity::GetNearbyObjects(const int amount,
		const std::vector<ModAPI::Entity>& objectsToIgnore, const float maxDistance) const
	{
		::Entity objectHandles[256] = {};
		worldGetAllObjects(objectHandles, 256);
	
		auto nearbyObjects = std::vector<ModAPI::Entity>();
		auto closestDistances = std::vector<float>();

		for(const auto objectHandle : objectHandles)
		{
			const auto objectEntity = ModAPI::Entity(objectHandle);
			if(!Exists(objectHandle) || objectHandle == GetHandle() || Utils::StdUtils::VectorContainsElement<ModAPI::Entity>(objectsToIgnore, objectHandle))
			{ continue; }

			if(objectEntity.GetType() != Enums::eEntityType::Prop)
			{ continue; }

			const float distanceToObject = objectEntity.GetDistanceTo(*this);
			if (distanceToObject > maxDistance)
			{ continue; }

			if(static_cast<int>(nearbyObjects.size()) < amount)
			{
				nearbyObjects.push_back(objectEntity);
				closestDistances.push_back(distanceToObject);
				continue;
			}

			for(size_t i = 0; i < nearbyObjects.size(); ++i)
			{
				if(distanceToObject >= closestDistances[i])
				{ continue; }

				nearbyObjects[i] = ModAPI::Entity(objectHandle);
				closestDistances[i] = distanceToObject;
				break;
			}
		}

		return nearbyObjects;
	}

	std::vector<ModAPI::Entity> Entity::GetNearbyVehicles(const int amount, const std::vector<ModAPI::Entity>& vehiclesToIgnore, const float maxDistance) const
	{
		::Vehicle vehicleHandles[256] = {};
		worldGetAllVehicles(vehicleHandles, 256);
	
		auto nearbyVehicles = std::vector<ModAPI::Entity>();
		auto closestDistances = std::vector<float>();
	
		for(const auto vehicleHandle : vehicleHandles)
		{
			const auto vehicle = ModAPI::Vehicle(vehicleHandle);
			if(!Exists(vehicleHandle) || vehicleHandle == GetHandle() || Utils::StdUtils::VectorContainsElement<ModAPI::Entity>(vehiclesToIgnore, vehicleHandle))
			{ continue; }

			if(vehicle.GetType() != Enums::eEntityType::Vehicle)
			{ continue; }

			const float distanceToVehicle = vehicle.GetDistanceTo(*this);
			if (distanceToVehicle > maxDistance)
			{ continue; }
		
			if(static_cast<int>(nearbyVehicles.size()) < amount)
			{
				nearbyVehicles.push_back(vehicle);
				closestDistances.push_back(distanceToVehicle);
				continue;
			}

			for(size_t i = 0; i < nearbyVehicles.size(); ++i)
			{
				if(distanceToVehicle >= closestDistances[i])
				{ continue; }

				nearbyVehicles[i] = ModAPI::Entity(vehicleHandle);
				closestDistances[i] = distanceToVehicle;
				break;
			}
		}

		return nearbyVehicles;
	}
}
