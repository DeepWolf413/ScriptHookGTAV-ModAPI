#include "World.h"

#include <inc/natives.h>

RaycastResult ModAPI::World::Raycast(const Vector3 fromPos, const Vector3 toPos, const eTraceFlags flags)
{
	const int shapeTestHandle = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(fromPos.x, fromPos.y, fromPos.z, toPos.x, toPos.y, toPos.z, static_cast<int>(flags), 0, 7);
	return RaycastResult(shapeTestHandle);
}
