#pragma once


#ifndef MATH_H
#define MATH_H

struct Vector3;

namespace MathUtils
{
	#define M_PI 3.14159265358979323846
	
	float ToRadian(const float deg);
	int GetRndIntInRange(int min, int max);
}

#endif