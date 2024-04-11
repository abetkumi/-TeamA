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
	CharacterController characterController;
	Vector3 m_position;
};

