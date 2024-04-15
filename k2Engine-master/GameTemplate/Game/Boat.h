#pragma once
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
	CollisionObject collisonObject;
	Vector3 m_position;
	Quaternion m_rotation;
	Vector3 size;
};

