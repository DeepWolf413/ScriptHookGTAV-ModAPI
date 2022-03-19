#pragma once
#include <cstdint>

struct Color
{
public:
	Color();
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	uint8_t R {0};
	uint8_t G {0};
	uint8_t B {0};
	uint8_t A {0};
};

static_assert(sizeof(Color) == 4);