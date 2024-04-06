#pragma once

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();

	void Render(RenderContext& rc);

	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
	Vector3 m_position;
};