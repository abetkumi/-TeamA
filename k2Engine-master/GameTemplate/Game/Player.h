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
	void HPGauge();
	void Collision();
	void ArrowAnimation();

	Vector3 m_position;
	Vector3 m_scale = Vector3::One;
	Vector3 m_moveSpeed;

	Vector3 m_cNPos;

	ModelRender m_modelRender;
	SpriteRender m_spriteRender;
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

	enum ArrowState
	{
		ArrowState_Idle,
		ArrowState_Draw,
		ArrowState_Aim,
		ArrowState_Num,
	};
	int m_arrowState = 0;
	enum EnArrowClip
	{
		enArrowClip_Idle,
		enArrowClip_Draw,
		enArrowClip_Aim,
		enArrowClip_Num,
	};
	AnimationClip m_animationClips[enArrowClip_Num];

	float HP,ST,ATK = 1;
	Vector3 diff;
	Vector3 m_HPBarposition;
	int m_point = 0;
	int m_moveFlag = 1;
	int m_lag = 0;
	Vector3 m_HPGauge;
};