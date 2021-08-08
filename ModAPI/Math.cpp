#include "Math.h"


#include <inc/natives.h>
#include <inc/types.h>

float MathUtils::ToRadian(const float deg)
{ return deg * M_PI / 180; }

int MathUtils::GetRndIntInRange(int min, int max)
{ return MISC::GET_RANDOM_INT_IN_RANGE(min, max); }
