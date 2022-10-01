#include "RaycastResult.h"

#include <natives.h>

namespace ModAPI
{
    RaycastResult::RaycastResult(const int shapeTestHandle)
    {
        Vector3 endCoords, surfaceNormal;
        ::Entity hitEntityHandle;
        SHAPETEST::GET_SHAPE_TEST_RESULT(shapeTestHandle, &didHitSomething, &endCoords, &surfaceNormal, &hitEntityHandle);
        this->endCoords = MMath::Vector3::FromSHVector3(endCoords);
        this->surfaceNormal = MMath::Vector3::FromSHVector3(surfaceNormal);
        this->hitEntity = Entity(hitEntityHandle);
    }

    BOOL RaycastResult::GetDidHitSomething() const
    { return didHitSomething; }

    MMath::Vector3 RaycastResult::GetEndCoords() const
    { return endCoords; }

    MMath::Vector3 RaycastResult::GetSurfaceNormal() const
    { return surfaceNormal; }

    ModAPI::Entity* RaycastResult::GetHitEntity()
    { return &hitEntity; }
}
