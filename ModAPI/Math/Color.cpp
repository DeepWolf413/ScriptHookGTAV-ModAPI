#include "Color.h"

namespace ModAPI::MMath
{
    Color::Color() : Color(0, 0, 0, 255)
    {}

    Color::Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
        : R(r), G(g), B(b), A(a)
    {}
}
