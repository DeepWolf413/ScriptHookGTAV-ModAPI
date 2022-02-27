#pragma once
#include <shsdk/nativeCaller.h>
#include <shsdk/types.h>
#include "math/Vector3.h"

struct RaycastResult
{
public:
	RaycastResult(int shapeTestHandle);

	[[nodiscard]] BOOL GetDidHitSomething() const;
	[[nodiscard]] Vector3 GetEndCoords() const;
	[[nodiscard]] Vector3 GetSurfaceNormal() const;
	[[nodiscard]] EntityHandle GetHitEntity() const;

private:
	BOOL didHitSomething;
	Vector3 endCoords;
	Vector3 surfaceNormal;
	EntityHandle hitEntity;
};
