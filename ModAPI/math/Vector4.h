#pragma once

#define ALIGN8 __declspec(align(8))

struct Vector4
{
public:
	Vector4();
	Vector4(float x, float y, float z, float w);

	ALIGN8 float X;
	ALIGN8 float Y;
	ALIGN8 float Z;
	ALIGN8 float W;
private:
	[[nodiscard]] Vector4 ThisVector() const;
};

static_assert(sizeof(Vector4) == 32);