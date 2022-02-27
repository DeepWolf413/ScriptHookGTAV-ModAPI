#include "World.h"

#include <shsdk/natives.h>

RaycastResult ModAPI::World::Raycast(const Vector3& fromPos, const Vector3& toPos, const eTraceFlags flags)
{
	const int shapeTestHandle = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(fromPos.X, fromPos.Y, fromPos.Z, toPos.X, toPos.Y, toPos.Z, static_cast<int>(flags), 0, 7);
	return {shapeTestHandle};
}
