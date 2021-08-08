#include "RaycastResult.h"

#include <inc/natives.h>

RaycastResult::RaycastResult(int shapeTestHandle)
{ SHAPETEST::GET_SHAPE_TEST_RESULT(shapeTestHandle, &didHitSomething, &endCoords, &surfaceNormal, &hitEntity); }

BOOL RaycastResult::GetDidHitSomething() const
{ return didHitSomething; }

Vector3 RaycastResult::GetEndCoords() const
{ return endCoords; }

Vector3 RaycastResult::GetSurfaceNormal() const
{ return surfaceNormal; }

EntityHandle RaycastResult::GetHitEntity() const
{ return hitEntity; }
