#pragma once
//#include "sound/SoundSource.h"

class Player;
class Arrow;
class Assist;
class Item;
class Game;
class GameCamera;

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
	void Collision();
	void Seek();
	void EnemyAttackBar();
	void ItemDrop();
	bool Start();
	void CameraSyoujun();

	const bool Serch();
	const bool AttackSerch();
	const bool DeleteSerch();
	const bool Desision();

	Vector3 m_position;
	Vector3 m_scale = Vector3::One;
	Vector3 m_moveSpeed;
	Vector3	m_forward = Vector3::AxisZ;
	Vector3 m_toCameraPos;
	Vector3 m_pePos;
	Vector3 m_attackBar = { 1.0f,1.0f,1.0f };
	Vector2 m_spritePosition = Vector2::Zero;

	float m_peDis;

	ModelRender m_modelRender;
	SpriteRender m_spriteRender;
	Quaternion m_rotation;
	//CharacterController m_charaCon;

	enum EnEnemy2Clip
	{
		enEnemy2Clip_Idle,
		enEnemy2Clip_Pull,
		enEnemy2Clip_Attack,
		enEnemy2Clip_Down,
		enEnemy2Clip_Num,
	};
	AnimationClip m_animation2Clips[enEnemy2Clip_Num];

	int m_enemy2State = 0;
	int m_enemy2DownLag = 0;

	Player* player;
	Arrow* arrow;
	Assist* assist;
	Item* item;
	GameCamera* gameCamera;
	CollisionObject* m_collisionObject;

	float arrowtimer = 0.0f;
	float arrowtime = 3.0f;
	bool m_downFlag = false;
	double m_Dec;
	int HP = 1;
	int i = 0;
	int m_itemGet = 0;
};



