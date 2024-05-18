#pragma once

class Player;
class Arrow;
class Item;
class Game;

class Enemy2 : public IGameObject
{
public:
	Enemy2();
	~Enemy2();
	void Update();
	void Render(RenderContext& rc);
	void Rotation();
	void Attack();
	void PlayAnimation();
	bool Start();

	const bool Serch();
	const bool AttackSerch();

	void Collision();

	Vector3 m_position;
	Vector3 m_scale = Vector3::One;
	Vector3 m_moveSpeed;
	Vector3	m_forward = Vector3::AxisZ;

	Quaternion m_rotation;

	ModelRender m_modelRender;

	//アニメーション
	enum EnEnemy2Clip
	{
		enEnemy2Clip_Idle,
		enEnemy2Clip_Attack,
		enEnemy2Clip_Down,
		enEnemy2Clip_Num,
	};
	AnimationClip m_animationClips[enEnemy2Clip_Num];
	int m_enemy2State = 0;
	int m_enemy2DownLag = 0;

	//CharacterController m_charaCon;

	Player* player;
	Arrow* arrow;

	CollisionObject* m_collisionObject;

	float arrowtimer = 0.0f;
	float arrowtime = 3.0f;

	int HP = 1;
};



