#pragma once
#include <enums.h>

#include "RaycastResult.h"

namespace ModAPI::World
{
	RaycastResult Raycast(const MMath::Vector3& fromPos, const MMath::Vector3& toPos, eIntersectFlags flags);
} // namespace
