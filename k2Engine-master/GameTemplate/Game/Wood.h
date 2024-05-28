#pragma once
class Wood : public IGameObject
{
public:
	Wood();
	~Wood();
	bool Start();

	void Render(RenderContext& rc);

	ModelRender w_modelRender;
	ModelRender w_scale;
	PhysicsStaticObject w_physicsStaticObject;
	Vector3 w_position;
};

