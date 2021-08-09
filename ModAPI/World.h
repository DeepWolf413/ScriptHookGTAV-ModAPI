#pragma once
#include "RaycastResult.h"
#include <shsdk/enums.h>

struct Vector3;

namespace ModAPI
{
	class World {
	public:
		static RaycastResult Raycast(Vector3 fromPos, Vector3 toPos, eTraceFlags flags);
	};
}
