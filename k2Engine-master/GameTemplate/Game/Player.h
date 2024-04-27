#pragma once

class Arrow;
class Game;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();

	Vector3 m_position;
	Vector3 m_scale = Vector3::One;
	Vector3 m_moveSpeed;

	ModelRender m_modelRender;

	CharacterController m_charaCon;

	Quaternion m_rotation;

	Arrow* arrow;
	Game* game;

	int HP,ST = 1;
	int point = 0;
};