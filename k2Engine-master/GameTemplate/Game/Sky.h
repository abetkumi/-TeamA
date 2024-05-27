#pragma once
class Sky : public IGameObject
{
public:
	Sky();
	~Sky();

	void Render(RenderContext& rc);

	ModelRender s_modelRender;
	PhysicsStaticObject s_physicsStaticObject;
	Vector3 s_position;
};

