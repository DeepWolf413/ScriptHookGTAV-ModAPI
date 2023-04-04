#include "RaycastResult.h"

#include <natives.h>

namespace ModAPI
{
    RaycastResult::RaycastResult(const MMath::Vector3& fromPos, const MMath::Vector3& toPos, const eIntersectFlags flags) : RaycastResult(fromPos, toPos, flags, NULL)
    {}

    RaycastResult::RaycastResult(const MMath::Vector3& fromPos, const MMath::Vector3& toPos, const eIntersectFlags flags, const ModAPI::Entity& entityToIgnore)
    {
        const int raycastHandle = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(fromPos.X, fromPos.Y, fromPos.Z, toPos.X, toPos.Y, toPos.Z, static_cast<int>(flags), entityToIgnore.GetHandle(), 7);

        Vector3 endCoords, surfaceNormal;
        BOOL hit;
        ::Entity hitEntityHandle;
        SHAPETEST::GET_SHAPE_TEST_RESULT(raycastHandle, &hit, &endCoords, &surfaceNormal, &hitEntityHandle);

        this->hasHitAnything = hit;
        this->hitPosition = MMath::Vector3::FromSHVector3(endCoords);
        this->hitSurfaceNormal = MMath::Vector3::FromSHVector3(surfaceNormal);
        this->hitEntity = Entity(hitEntityHandle);
    }

    bool RaycastResult::HasHitAnything() const
    { return hasHitAnything; }

    MMath::Vector3 RaycastResult::GetHitPosition() const
    { return hitPosition; }

    MMath::Vector3 RaycastResult::GetHitSurfaceNormal() const
    { return hitSurfaceNormal; }

    Entity* RaycastResult::GetHitEntity()
    { return &hitEntity; }
} // namespace