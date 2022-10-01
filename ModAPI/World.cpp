#include "World.h"

#include <natives.h>

namespace ModAPI
{
	RaycastResult World::Raycast(const MMath::Vector3& fromPos, const MMath::Vector3& toPos, const eIntersectFlags flags)
	{
		const int shapeTestHandle = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(fromPos.X, fromPos.Y, fromPos.Z, toPos.X, toPos.Y, toPos.Z, static_cast<int>(flags), 0, 7);
		return {shapeTestHandle};
	}
}
