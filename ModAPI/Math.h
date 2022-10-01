#pragma once
namespace ModAPI::MathHelpers
{
	#define M_PI 3.14159265358979323846
	
	float ToRadian(const float deg);
	int GetRndIntInRange(int min, int max);
	float GetRndFloatInRange(float min, float max);
}