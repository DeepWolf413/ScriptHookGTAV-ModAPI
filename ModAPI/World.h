#pragma once
#include "RaycastResult.h"
#include <shsdk/enums.h>

struct Vector3;

namespace ModAPI
{
	namespace World
	{
		RaycastResult Raycast(const Vector3& fromPos, const Vector3& toPos, eTraceFlags flags);
	}
}
