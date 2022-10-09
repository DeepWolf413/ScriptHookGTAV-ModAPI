#include "Vector4.h"

namespace ModAPI::MMath
{
	Vector4::Vector4()
	{
		X = 0;
		Y = 0;
		Z = 0;
		W = 0;
	}

	Vector4::Vector4(const float x, const float y, const float z, const float w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}

	Vector4 Vector4::ThisVector() const
	{
		return {this->X, this->Y, this->Z, this->W};
	}
}
