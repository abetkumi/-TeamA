#pragma once

class Point;

class Boat : public IGameObject
{
public:
	Boat();
	~Boat();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;

	Vector3 m_position;
	Vector3 m_scale;
	Vector3 m_moveSpeed;
	Point* point;

};

