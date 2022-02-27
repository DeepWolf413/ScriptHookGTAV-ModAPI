#pragma once
#include <memory>
#include <string>
#include <vector>
#include <shsdk/types.h>


#include "enums/eEntityType.h"
#include "math/Vector3.h"

namespace ModAPI
{
	class Vehicle;
	class Ped;
	class Model;

	class Entity
	{
	public:
		Entity(EntityHandle handle);
		virtual ~Entity() = default;

		static std::unique_ptr<Entity> FromHandle(EntityHandle handle);
		static bool Exists(const Entity* entity);
		static bool Exists(EntityHandle entity);

		[[nodiscard]] Hash GetModel() const;
		[[nodiscard]] EntityHandle GetHandle() const;
		void MarkAsNoLongerNeeded();
		virtual void Delete();
		[[nodiscard]] bool Exists() const;
		[[nodiscard]] bool IsModel(Hash modelHash) const;

		[[nodiscard]] eEntityType GetType() const;
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
		[[nodiscard]] bool IsDead() const;
		[[nodiscard]] bool IsAlive() const;

		[[nodiscard]] float GetDistanceTo(const Entity& otherEntity, bool useZ = true) const;
		[[nodiscard]] Vector3 GetPosition(bool alive = true) const;
		void SetPosition(const Vector3& newPosition) const;
		void SetPositionNoOffset(const Vector3& newPosition) const;
		[[nodiscard]] Vector3 GetRotation() const;
		void SetRotation(const Vector3& newRotation) const;
		[[nodiscard]] float GetHeading() const;
		void SetHeading(float newHeading) const;
		[[nodiscard]] float GetHeightAboveGround() const;
		[[nodiscard]] Vector3 GetUpVector() const;
		[[nodiscard]] Vector3 GetRightVector() const;
		[[nodiscard]] Vector3 GetForwardVector() const;
		[[nodiscard]] Vector3 GetOffsetInWorldCoords(const Vector3& offset) const;
		[[nodiscard]] Vector3 GetOffsetFromWorldCoords(const Vector3& worldCoords) const;
		void SetVelocity(const Vector3& newVelocity) const;
		[[nodiscard]] Vector3 GetVelocity() const;
		void ApplyForce(const Vector3& direction) const;
		void ApplyForce(const Vector3& direction, const Vector3& rotation) const;
		void ApplyForce(const Vector3& direction, const Vector3& rotation, int forceType) const;
		void ApplyForceRelative(const Vector3& direction) const;
		void ApplyForceRelative(const Vector3& direction, const Vector3& rotation) const;
		void ApplyForceRelative(const Vector3& direction, const Vector3& rotation, int forceType) const;
		void SetGravity(bool enable) const;
		[[nodiscard]] bool HasCollidedWithAnything() const;

		// Makes this entity, and the otherEntity not able to collide with eachother.
		void SetNoCollision(const Entity& otherEntity, bool toggle) const;
		void SetAllCollision(bool enable, bool keepPhysics) const;
		[[nodiscard]] bool IsInArea(const Vector3& minBounds, const Vector3& maxBounds) const;
		[[nodiscard]] bool IsInArea(const Vector3& aPos, const Vector3& bPos, float angle) const;
		[[nodiscard]] bool IsInAngledArea(const Vector3& origin, const Vector3& edge, float angle) const;
		[[nodiscard]] bool IsInRangeOf(const Vector3& position, float distance) const;
		[[nodiscard]] bool IsNearEntity(const Entity& otherEntity, const Vector3& distance) const;
		[[nodiscard]] bool IsTouching(const Model& model) const;
		[[nodiscard]] bool IsTouching(const Entity& otherEntity) const;

		void Detach() const;
		void AttachTo(const Entity& entity, int boneIndex) const;
		void AttachTo(const Entity& entity, int boneIndex, const Vector3& position, const Vector3& rotation) const;
		[[nodiscard]] bool IsAttached() const;
		[[nodiscard]] bool IsAttachedTo(const Entity& entity) const;
		[[nodiscard]] std::unique_ptr<Entity> GetEntityAttachedTo() const;

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

		[[nodiscard]] std::vector<std::unique_ptr<Ped>> GetNearbyHumans(
			int amount, const std::vector<EntityHandle>& entitiesToIgnore = std::vector<EntityHandle>(),
			float maxDistance = 15) const;
		[[nodiscard]] std::vector<std::unique_ptr<Vehicle>> GetNearbyVehicles(
			int amount, const std::vector<EntityHandle>& entitiesToIgnore = std::vector<EntityHandle>(),
			float maxDistance = 15) const;

	protected:
		EntityHandle handle;
	};
}
