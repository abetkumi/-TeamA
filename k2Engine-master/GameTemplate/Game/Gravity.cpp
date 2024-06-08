#include "stdafx.h"
#include "Gravity.h"
#include "Arrow.h"

#include <cmath>

using namespace std;

namespace
{
	float const g = 2000.0f;
}

void  Gravity::Move(Vector3 v, const float Len)
{
	arrow = FindGO<Arrow>("arrow");

	float vy = sqrt((Len * g) / 2.0f);
	
	m_sNew = vy;
}

//01_Path_Point_003