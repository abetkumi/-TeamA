#pragma once
#include "sound/SoundSource.h"

class Player;
class Arrow;
class Item;
class GameCamera;
class EnemyTarget;
class Enemy3 : public IGameObject
{
public:
	Enemy3();
	~Enemy3();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void AttackMove();
	void Rotation();
	void Attack();
	void HomingDec();
	void Calculation();
	void EnemyAttackBar();
	void ItemDrop();
	void PlayAnimation();
	bool Start();

	const bool Serch();
	const bool MoveSerch();
	const bool Distance();
	const bool PosDistance();
	const bool HomingSerch();

	void Collision();

	Vector3 m_position;
	Vector3 m_attackPos;
	Vector3 m_scale = Vector3::One;
	Vector3 m_moveSpeed;
	Vector3	m_forward = Vector3::AxisZ;
	Vector3 m_cNPos;
	Vector3 m_homingPos;
	Vector3 m_attackBar = { 1.0f,1.0f,1.0f };
	Vector2 m_spritePosition = Vector2::Zero;

	Quaternion m_rotation;
	SpriteRender m_spriteRender;
	ModelRender m_modelRender;

	//CharacterController m_charaCon;

	Player* player;
	Arrow* arrow;
	Item* item;
	GameCamera* gameCamera;
	CollisionObject* m_collisionObject;
	SoundSource* se;
	SoundSource* se2;

	enum EnEnemy3Clip
	{
		enEnemy3Clip_Idle,
		enEnemy3Clip_Down,
		enEnemy3Clip_Num,
	};
	AnimationClip m_animation3Clips[enEnemy3Clip_Num];

	float arrowtimer = 0.0f;
	float arrowtime = 3.0f;

	bool m_downFlag = false;
	int HP = 1;
	int initialAng = 0;			//Move�����p�x�ݒ�p
	int initialPos = 0;			//AttackMove�����ʒu�ݒ�p
	int moveStatus = 0;
	int m_enemy3Status = 0;
	int m_enemy3DownLag = 0;
	int m_itemGet = 0;
	

	//Move()��̂�
	float firstAng, Ang = 0.0f;
	int y = 0;
	float Xt = 0.3f;
	float m_Dir;

	bool homing = false;
};



