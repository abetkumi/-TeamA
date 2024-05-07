#pragma once

class Arrow;
class Game;
class GameCamera;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();

	void Collision();

	Vector3 m_position;
	Vector3 m_scale = Vector3::One;
	Vector3 m_moveSpeed;

	ModelRender m_modelRender;

	CharacterController m_charaCon;

	Quaternion m_rotation;

	Arrow* arrow;
	Game* game;
	GameCamera* gameCamera;
	enum MoveState {
		MoveState_Normal,
		MoveState_Left,	// ç∂Ç…à⁄ìÆíÜ
		MoveState_Right, // âEÇ…à⁄ìÆíÜ
	};
	
	MoveState m_moveState = MoveState_Normal;
	int HP,ST,ATK = 1;
	Vector3 diff;
	int m_point = 0;
	int m_moveFlag = 1;
	int m_lag = 0;
};