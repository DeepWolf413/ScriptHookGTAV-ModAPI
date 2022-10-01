#include "Math.h"


#include <natives.h>
#include <random>

namespace ModAPI
{
    float MathHelpers::ToRadian(const float deg)
    { return deg * M_PI / 180; }

    int MathHelpers::GetRndIntInRange(const int min, const int max)
    {
        std::random_device seed;
        std::mt19937 gen(seed());
        const std::uniform_int_distribution dist(min, max);
        return dist(gen);
    }

    float MathHelpers::GetRndFloatInRange(const float min, const float max)
    {
        std::random_device seed;
        std::mt19937 gen(seed());
        const std::uniform_real_distribution dist(min, max);
        return dist(gen);
    }
}