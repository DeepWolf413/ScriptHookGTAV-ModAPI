#include "Random.h"

#include <random>

namespace ModAPI::MMath::Random
{
    int IntInRange(const int minInclusive, const int maxExclusive)
    {
        std::random_device seed;
        std::mt19937 gen(seed());
        std::uniform_int_distribution dist(minInclusive, maxExclusive - 1);
        return dist(gen);
    }

    float FloatInRange(const float minInclusive, const float maxInclusive)
    {
        std::random_device seed;
        std::mt19937 gen(seed());
        std::uniform_real_distribution dist(minInclusive, maxInclusive);
        return dist(gen);
    }

    bool Chance(const int chance)
    {
        return IntInRange(0, 101) <= chance;
    }
}
