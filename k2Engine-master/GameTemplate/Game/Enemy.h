#pragma once
class Player;
class Arrow;
class Assist;
class GameCamera;
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	void Update();
	void Render(RenderContext& rc);
	void Rotation();
	void Attack();
	void PlayAnimation();
	void Collision();
	void Seek();
	void EnemyAttackBar();

	bool Start();

	const bool Serch();
	const bool AttackSerch();
	const bool DeleteSerch();
	const bool Desision();
	const bool Dec();

	Vector3 m_position;
	Vector3 m_scale = Vector3::One;
	Vector3 m_moveSpeed;
	Vector3	m_forward = Vector3::AxisZ;
	Vector3 m_toCameraPos;
	Vector3 m_pePos;
	Vector3 m_attackBar = { 1.0f,1.0f,1.0f };
	Vector2 m_spritePosition = Vector2::Zero;
	//Vector3 m_cNPos = { 0.0f,0.0f,0.0f };

	float m_peDis;

	ModelRender m_modelRender;
	SpriteRender m_spriteRender;
	Quaternion m_rotation;

	enum EnEnemyClip
	{
		enEnemyClip_Idle,
		enEnemyClip_Attack,
		enEnemyClip_Down,
		enEnemyClip_Num,
	};
	AnimationClip m_animationClips[enEnemyClip_Num];

	int m_enemyState = 0;
	int m_enemyDownLag = 0;
	//CharacterController m_charaCon;

	Player* player;
	Arrow* arrow;
	Assist* assist;
	GameCamera* gameCamera;
	CollisionObject* m_collisionObject;

	float arrowtimer = 0.01f;
	float arrowtime = 3.0f;
	double m_Dec;
	int HP = 1;

	int i;
};