#pragma once

class Arrow;
class Gravity : public IGameObject
{
public:
	void Move(Vector3 v,const float Len);
	
	Arrow* arrow;

	float m_sNew;
	float i, x;
};

