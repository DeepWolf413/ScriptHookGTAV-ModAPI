#pragma once
#include <inc/nativeCaller.h>
#include <inc/types.h>
#include "math/Vector3.h"

struct RaycastResult {
public:
	RaycastResult(int shapeTestHandle);

	BOOL    GetDidHitSomething() const;
	Vector3 GetEndCoords() const;
	Vector3 GetSurfaceNormal() const;
	EntityHandle  GetHitEntity() const;

private:
	BOOL didHitSomething;
	Vector3 endCoords;
	Vector3 surfaceNormal;
	EntityHandle hitEntity;
};
