#pragma once
class Game;

class MoveRock : public IGameObject
{
	MoveRock();
	~MoveRock();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();

	Vector3 m_position;
	Quaternion m_rotation;
	ModelRender m_modelRender;

	Game* game;
};

