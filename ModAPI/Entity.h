#pragma once
#include <memory>
#include <string>
#include <vector>
#include <inc/types.h>


#include "enums/EEntityType.h"
#include "math/Vector3.h"

namespace ModAPI
{
	class Vehicle;
	class Ped;
	class Model;

	class Entity {
	public:
		Entity(EntityHandle handle);

		static std::unique_ptr<Entity> FromHandle(EntityHandle handle);
		static bool Exists(Entity* entity);
		static bool Exists(EntityHandle entity);
		
		Hash         GetModel() const;
		EntityHandle GetHandle() const;
		void         MarkAsNoLongerNeeded();
		virtual void Delete();
		bool         Exists() const;
		bool		 IsModel(Hash modelHash) const;
		
		eEntityType GetType() const;
		bool IsPersistent() const;
		void SetPersistent(bool persist) const;
		void FreezePosition(bool freeze) const;
		
		int GetBoneIndex(std::string boneName) const;
		bool HasBone(std::string boneName) const;

		int  GetHealth() const;
		void SetHealth(int newHealth) const;
		int  GetMaxHealth() const;
		void SetMaxHealth(int newMaxHealth) const;
		bool HasBeenDamagedBy(Entity* entity) const;
		void SetInvincibility(bool enable) const;
		void SetOnlyDamageableByPlayer(bool enable) const;
		bool IsDead() const;
		bool IsAlive() const;

		float   GetDistanceTo(const Entity* otherEntity, bool useZ = true) const;
		Vector3 GetPosition(bool alive = true) const;
		void    SetPosition(Vector3 newPosition) const;
		void    SetPositionNoOffset(Vector3 newPosition) const;
		Vector3 GetRotation() const;
		void    SetRotation(Vector3 newRotation) const;
		float   GetHeading() const;
		void    SetHeading(float newHeading) const;
		float   GetHeightAboveGround() const;
		Vector3 GetUpVector() const;
		Vector3 GetRightVector() const;
		Vector3 GetForwardVector() const;
		Vector3 GetOffsetInWorldCoords(Vector3 offset) const;
		Vector3 GetOffsetFromWorldCoords(Vector3 worldCoords) const;
		void    SetVelocity(Vector3 newVelocity) const;
		Vector3 GetVelocity() const;
		void    ApplyForce(Vector3 direction) const;
		void    ApplyForce(Vector3 direction, Vector3 rotation) const;
		void    ApplyForce(Vector3 direction, Vector3 rotation, int forceType) const;
		void    ApplyForceRelative(Vector3 direction) const;
		void    ApplyForceRelative(Vector3 direction, Vector3 rotation) const;
		void    ApplyForceRelative(Vector3 direction, Vector3 rotation, int forceType) const;
		void    SetGravity(bool enable) const;
		bool    HasCollidedWithAnything() const;

		// Makes this entity, and the otherEntity not able to collide with eachother.
		void SetNoCollision(Entity* otherEntity, bool toggle) const;
		void SetAllCollision(bool enable, bool keepPhysics) const;
		bool IsInArea(Vector3 minBounds, Vector3 maxBounds) const;
		bool IsInArea(Vector3 aPos, Vector3 bPos, float angle) const;
		bool IsInAngledArea(Vector3 origin, Vector3 edge, float angle) const;
		bool IsInRangeOf(Vector3 position, float distance) const;
		bool IsNearEntity(Entity* otherEntity, Vector3 distance) const;
		bool IsTouching(Model* model) const;
		bool IsTouching(Entity* otherEntity) const;

		void                    Detach() const;
		void                    AttachTo(Entity* entity, int boneIndex) const;
		void                    AttachTo(Entity* entity, int boneIndex, Vector3 position, Vector3 rotation) const;
		bool                    IsAttached() const;
		bool                    IsAttachedTo(Entity* entity) const;
		std::unique_ptr<Entity> GetEntityAttachedTo() const;

		int GetAlpha() const;
		void SetAlpha(int newAlpha) const;
		void ResetAlpha() const;
		bool IsVisible() const;
		void SetVisible(bool enable) const;
		bool IsOccluded() const;
		bool IsOnFire() const;
		bool IsOnScreen() const;
		
		bool IsUpright() const;
		bool IsUpsideDown() const;
		bool IsInAir() const;
		bool IsInWater() const;

		std::vector<std::unique_ptr<ModAPI::Ped>>     GetNearbyHumans(int amount, std::vector<EntityHandle> entitiesToIgnore = std::vector<EntityHandle>(), float maxDistance = 15) const;
		std::vector<std::unique_ptr<ModAPI::Vehicle>> GetNearbyVehicles(int amount, std::vector<EntityHandle> entitiesToIgnore = std::vector<EntityHandle>(), float maxDistance = 15) const;

	protected:
		EntityHandle handle;
	};
}
