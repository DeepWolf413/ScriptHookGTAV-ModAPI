#pragma once

#include <enums.h>

#include "Entity.h"
#include "MathAPI.h"

namespace ModAPI
{
	struct Raycast
	{
		Raycast(const MMath::Vector3& fromPos, const MMath::Vector3& toPos, eIntersectFlags flags);
		Raycast(const MMath::Vector3& fromPos, const MMath::Vector3& toPos, eIntersectFlags flags, const ModAPI::Entity& entityToIgnore);

		[[nodiscard]] bool HasHitAnything() const;
		[[nodiscard]] MMath::Vector3 GetHitPosition() const;
		[[nodiscard]] MMath::Vector3 GetHitSurfaceNormal() const;
		[[nodiscard]] ModAPI::Entity* GetHitEntity();

	private:
		bool hasHitAnything;
		MMath::Vector3 hitPosition;
		MMath::Vector3 hitSurfaceNormal;
		ModAPI::Entity hitEntity;
	};
} // namespace
