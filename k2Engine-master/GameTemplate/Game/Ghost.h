#pragma once

class Game;
class Ghost : public IGameObject
{
public:
	Ghost();
	~Ghost();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();

	Vector3 m_position;
	//Vector3 m_scale = Vector3::One;
	Vector3 m_moveSpeed;

	Vector3 m_cNPos;

	ModelRender m_modelRender;
	CharacterController m_charaCon;

	Quaternion m_rotation;

	Game* game;

	enum MoveState {
		MoveState_Normal,
		MoveState_Left,	// ¶‚ÉˆÚ“®’†
		MoveState_Right, // ‰E‚ÉˆÚ“®’†
	};
	MoveState m_moveState = MoveState_Normal;


	Vector3 diff;
	int m_point = 3;
	int m_moveFlag = 1;
	int m_lag = 0;

};

