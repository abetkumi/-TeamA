#include "stdafx.h"
#include "Gravity.h"
#include "Arrow.h"

#include <cmath>

using namespace std;

namespace
{
	float const g = 9.8f;
	float const ang = 45.0f;
}

void  Gravity::Move(Vector3 v, const float Len)
{
	arrow = FindGO<Arrow>("arrow");

	x = g * 80 * Len * 2;
	m_sNew = sqrt(x) / 2;
}
