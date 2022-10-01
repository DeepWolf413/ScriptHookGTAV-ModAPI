#pragma once
#include <types.h>

#include "Entity.h"
#include "Math/Vector3.h"

namespace ModAPI
{
	struct RaycastResult
	{
		RaycastResult(int shapeTestHandle);

		[[nodiscard]] BOOL GetDidHitSomething() const;
		[[nodiscard]] MMath::Vector3 GetEndCoords() const;
		[[nodiscard]] MMath::Vector3 GetSurfaceNormal() const;
		[[nodiscard]] ModAPI::Entity* GetHitEntity();

	private:
		BOOL didHitSomething{};
		MMath::Vector3 endCoords;
		MMath::Vector3 surfaceNormal;
		ModAPI::Entity hitEntity;
	};
}
