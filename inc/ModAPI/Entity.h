#pragma once
#include <string>
#include <vector>
#include <types.h>

#include "Enums.h"
#include "Model.h"

namespace ModAPI
{
	class Entity
	{
	public:
		Entity();
		Entity(::Entity entityHandle);
		virtual ~Entity() = default;

		bool operator==(int otherHandle) const;
		bool operator==(const Entity& otherEntity) const;

		static bool Exists(const ModAPI::Entity* entity);
		static bool Exists(::Entity entityHandle);

		[[nodiscard]] Model GetModel() const;
		[[nodiscard]] ::Entity GetHandle() const;
		void MarkAsNoLongerNeeded();
		void Delete();
		[[nodiscard]] bool Exists() const;
		[[nodiscard]] bool IsModel(Hash modelHash) const;
		[[nodiscard]] bool IsModel(const Model& model) const;

		[[nodiscard]] Enums::eEntityType GetType() const;
		[[nodiscard]] bool IsPersistent() const;
		void SetPersistent(bool persist) const;
		void FreezePosition(bool freeze) const;

		[[nodiscard]] int GetBoneIndex(const std::string& boneName) const;
		[[nodiscard]] bool HasBone(const std::string& boneName) const;

		[[nodiscard]] int GetHealth() const;
		void SetHealth(int newHealth) const;
		[[nodiscard]] int GetMaxHealth() const;
		void SetMaxHealth(int newMaxHealth) const;
		[[nodiscard]] bool HasBeenDamagedBy(const Entity& entity) const;
		void SetInvincibility(bool enable) const;
		void SetOnlyDamageableByPlayer(bool enable) const;
		void SetOnlyDamageableByRelationshipGroup(bool enable, Hash relationshipGroup) const;
		void SetCanBeDamagedByRelationshipGroup(bool enable, Hash relationshipGroup) const;
		[[nodiscard]] bool IsDead() const;
		[[nodiscard]] bool IsAlive() const;

		[[nodiscard]] float GetDistanceTo(const ModAPI::Entity& otherEntity, bool useZ = true) const;
		[[nodiscard]] MMath::Vector3 GetPosition(bool alive = true) const;
		void SetPosition(const MMath::Vector3& newPosition) const;
		void SetPositionNoOffset(const MMath::Vector3& newPosition) const;
		[[nodiscard]] MMath::Vector3 GetRotation() const;
		void SetRotation(const MMath::Vector3& newRotation) const;
		[[nodiscard]] float GetHeading() const;
		void SetHeading(float newHeading) const;
		[[nodiscard]] float GetHeightAboveGround() const;
		[[nodiscard]] MMath::Vector3 GetUpVector() const;
		[[nodiscard]] MMath::Vector3 GetRightVector() const;
		[[nodiscard]] MMath::Vector3 GetForwardVector() const;
		[[nodiscard]] MMath::Vector3 GetOffsetInWorldCoords(const MMath::Vector3& offset) const;
		[[nodiscard]] MMath::Vector3 GetOffsetFromWorldCoords(const MMath::Vector3& worldCoords) const;
		void SetVelocity(const MMath::Vector3& newVelocity) const;
		[[nodiscard]] MMath::Vector3 GetVelocity() const;
		void ApplyForce(const MMath::Vector3& velocity) const;
		void ApplyForce(const MMath::Vector3& velocity, const MMath::Vector3& rotation) const;
		void ApplyForce(const MMath::Vector3& velocity, const MMath::Vector3& rotation, int forceType) const;
		void ApplyForceRelative(const MMath::Vector3& velocity) const;
		void ApplyForceRelative(const MMath::Vector3& velocity, const MMath::Vector3& rotation) const;
		void ApplyForceRelative(const MMath::Vector3& velocity, const MMath::Vector3& rotation, int forceType) const;
		void ApplyForceTowardsEntity(const ModAPI::Entity& entityToPullTowards, float force) const;
		void SetGravity(bool enable) const;
		[[nodiscard]] bool HasCollidedWithAnything() const;

		// Makes this entity, and the otherEntity not able to collide with eachother.
		void SetNoCollision(const ModAPI::Entity& otherEntity, bool toggle) const;
		void SetAllCollision(bool enable, bool keepPhysics) const;
		[[nodiscard]] bool IsInArea(const MMath::Vector3& minBounds, const MMath::Vector3& maxBounds) const;
		[[nodiscard]] bool IsInArea(const MMath::Vector3& aPos, const MMath::Vector3& bPos, float angle) const;
		[[nodiscard]] bool IsInAngledArea(const MMath::Vector3& origin, const MMath::Vector3& edge, float angle) const;
		[[nodiscard]] bool IsInRangeOf(const MMath::Vector3& position, float distance) const;
		[[nodiscard]] bool IsNearEntity(const ModAPI::Entity& otherEntity, const MMath::Vector3& distance) const;
		[[nodiscard]] bool IsTouching(const ModAPI::Model& model) const;
		[[nodiscard]] bool IsTouching(const ModAPI::Entity& otherEntity) const;

		void Detach() const;
		void AttachTo(const ModAPI::Entity& entity, int boneIndex) const;
		void AttachTo(const ModAPI::Entity& entity, int boneIndex, const MMath::Vector3& position, const MMath::Vector3& rotation) const;
		[[nodiscard]] bool IsAttached() const;
		[[nodiscard]] bool IsAttachedTo(const ModAPI::Entity& entity) const;
		[[nodiscard]] ModAPI::Entity GetEntityAttachedTo() const;

		[[nodiscard]] int GetAlpha() const;
		void SetAlpha(int newAlpha) const;
		void ResetAlpha() const;
		[[nodiscard]] bool IsVisible() const;
		void SetVisible(bool enable) const;
		[[nodiscard]] bool IsOccluded() const;
		[[nodiscard]] bool IsOnFire() const;
		[[nodiscard]] bool IsOnScreen() const;

		[[nodiscard]] bool IsUpright() const;
		[[nodiscard]] bool IsUpsideDown() const;
		[[nodiscard]] bool IsInAir() const;
		[[nodiscard]] bool IsInWater() const;

		[[nodiscard]] std::vector<ModAPI::Entity> GetNearbyPeds(
					int amount, bool ignorePedsInVehicle, const std::vector<ModAPI::Entity>& pedsToIgnore = std::vector<ModAPI::Entity>(),
					float maxDistance = 15) const;
		[[nodiscard]] std::vector<ModAPI::Entity> GetNearbyHumans(
			int amount, bool ignorePedsInVehicle, const std::vector<ModAPI::Entity>& humansToIgnore = std::vector<ModAPI::Entity>(),
			float maxDistance = 15) const;
		[[nodiscard]] std::vector<ModAPI::Entity> GetNearbyAnimals(
			int amount, const std::vector<ModAPI::Entity>& animalsToIgnore = std::vector<ModAPI::Entity>(),
			float maxDistance = 15) const;
		[[nodiscard]] std::vector<Entity> GetNearbyObjects(
			int amount, const std::vector<ModAPI::Entity>& objectsToIgnore = std::vector<ModAPI::Entity>(),
			float maxDistance = 15) const;
		[[nodiscard]] std::vector<ModAPI::Entity> GetNearbyVehicles(
			int amount, const std::vector<ModAPI::Entity>& vehiclesToIgnore = std::vector<ModAPI::Entity>(),
			float maxDistance = 15) const;

	protected:
		::Entity handle;
	};
}
