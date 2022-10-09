#pragma once

namespace ModAPI::MMath::Random
{
    /**
     * \brief Generates a random integer within the specified range.
     * \param minInclusive The minimum value that can be generated (Inclusive)
     * \param maxExclusive The maximum value that can be generated (Exclusive)
     * \return A randomly generated integer within the specified range.
     */
    int IntInRange(int minInclusive, int maxExclusive);

    /**
     * \brief Generates a random float within the specified range.
     * \param minInclusive The minimum value that can be generated (Inclusive)
     * \param maxInclusive The maximum value that can be generated (Inclusive)
     * \return A randomly generated float within the specified range.
     */
    float FloatInRange(float minInclusive, float maxInclusive);

    /**
     * \brief Generates a random number between 0 - 100, and returns false if that number is above the specified chance.
     * \param chance The chance to return true (the value should be between 0 - 100).
     * \return True if the generated random number is below or equal the specified chance, otherwise false.
     */
    bool Chance(int chance);
}
