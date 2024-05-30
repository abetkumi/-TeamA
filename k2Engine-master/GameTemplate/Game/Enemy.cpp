#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Arrow.h"
#include "Assist.h"
#include "GameCamera.h"

#include "collision/CollisionObject.h"

#include <time.h>
//4000,3000
#define serch 5000.0f * 5000.0f
#define attackSerch 4400.0f * 4400.0f
#define playerSerch 5000.0f * 5000.0f
//#define attacktime 5.0f

namespace
{
	const Vector3 corre1 = { 0.0f,0.0f,0.0f };//�ʒu�C���{�̓����蔻��
	const Vector3 corre2 = { 0.0f,0.0f,10.0f };//�ʒu�C���e�۔����ʒu
}

Enemy::Enemy()
{
	
}

Enemy::~Enemy()
{
	DeleteGO(arrow);
	DeleteGO(m_collisionObject);

	//assist->
	DeleteGO(assist);
}
bool Enemy::Start()
{

	m_animationClips[enEnemyClip_Idle].Load("Assets/animData/goblin_idle.tka");
	m_animationClips[enEnemyClip_Idle].SetLoopFlag(true);
	m_animationClips[enEnemyClip_Attack].Load("Assets/animData/goblin_attack.tka");
	m_animationClips[enEnemyClip_Attack].SetLoopFlag(true);
	m_animationClips[enEnemyClip_Down].Load("Assets/animData/goblin_death.tka");
	m_animationClips[enEnemyClip_Down].SetLoopFlag(false);

	m_modelRender.Init("Assets/modelData/goblin.tkm"
	,m_animationClips,enEnemyClip_Num);
	player = FindGO<Player>("player");
	assist = FindGO<Assist>("assist");
	gameCamera = FindGO<GameCamera>("gameCamera");

	arrowtimer = arrowtime;

	m_modelRender.SetPosition(m_position);


	//m_charaCon.Init(20.0f, 100.0f, m_position);

	m_collisionObject = NewGO<CollisionObject>(0);

	m_collisionObject->CreateSphere(m_position, Quaternion::Identity, 60.0f * m_scale.z);
	m_collisionObject->SetName("enemy");
	m_collisionObject->SetPosition(m_position + corre1);

	m_collisionObject->SetIsEnableAutoDelete(false);

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

	return true;
}

void Enemy::Update()
{
	Serch();
	AttackSerch();

	Rotation();
	Attack();
	Desision();

	Seek();
	Dec();
	Collision();
	PlayAnimation();

	m_modelRender.Update();
}

void Enemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void Enemy::Rotation()
{
	Vector3 diff = player->m_position - m_position;
	if (Serch() == true)
	{
		m_moveSpeed = diff * 100.0f;
	}

	

	m_modelRender.SetPosition(m_position);
	m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	m_modelRender.SetRotation(m_rotation);

	m_rotation.AddRotationX(-45.0);
	
	m_collisionObject->SetPosition(m_position + corre1);
}

void Enemy::Attack()
{
	Vector3 diff = player->m_position - m_position;
	if (!AttackSerch())
		return;

	if (arrowtimer > 0)
	{
		arrowtimer -= g_gameTime->GetFrameDeltaTime();		
		return;
	}
	m_enemyState = 1;
	arrow = NewGO<Arrow>(0);

	arrow->m_position = (m_position + corre2);
	arrow->m_1stPosition = arrow->m_position;
	arrow->m_rotation = m_rotation;

	diff.y = 0.0f;
	arrow->m_peLen = diff.Length();

	arrow->SetEnArrow(Arrow::enArrow_Goblin);

	arrowtimer = arrowtime;
}

const bool Enemy::Serch()
{
	Vector3 diff = player->m_position - m_position;
	if (diff.LengthSq() <= serch)
	{
		return true;
	}
	arrowtimer = arrowtime;
}

const bool Enemy::AttackSerch()
{
	Vector3 diff = player->m_position - m_position;
	if (diff.LengthSq() <= attackSerch)
	{
		return true;
	}
}



void Enemy::Collision()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("p_arrow");

	for (auto collision : collisions) {
		if (collision->IsHit(m_collisionObject))
		{
			HP -= 100;
		}
		if (HP <= 0) {
			m_enemyState = 2;
			m_enemyDownLag++;
			if (m_enemyDownLag >= 20)
			{
				DeleteGO(this);
			}
		}
	}
}

void Enemy::Seek()
{
	if (Desision() == true)
	{
		m_pePos = m_position - player->m_position;
		m_peDis = m_pePos.Length();

		
		Vector3 v = player->m_position + m_toCameraPos;
		v.Normalize();

		Vector3 ePos = m_position + m_toCameraPos;
		ePos.Normalize();

		m_Dec = v.Dot(ePos);
	}
}

const bool Enemy::Desision()
{
	Vector3 diff = player->m_position - m_position;
	if (diff.LengthSq() <= playerSerch)
	{
		return true;
	}
}

const bool Enemy::Dec()
{
	/*if (m_Dec >= 0.98)
	{
		return true;
	}*/
	return true;
}

void Enemy::PlayAnimation()
{
	switch (m_enemyState)
	{
	case 0:
		m_modelRender.PlayAnimation(enEnemyClip_Idle);
		break;
	case 1:
		m_modelRender.PlayAnimation(enEnemyClip_Attack);
		break;
	case 2:
		m_modelRender.PlayAnimation(enEnemyClip_Down);
		break;
	}
}
