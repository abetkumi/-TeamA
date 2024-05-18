#include "stdafx.h"
#include "Enemy2.h"
#include "Player.h"
#include "Arrow.h"

#include "collision/CollisionObject.h"

#include <time.h>

#define serch 1300.0f * 1300.0f
#define attackSerch 700.0f * 700.0f
//#define attacktime 5.0f

namespace
{
	const Vector3 corre1 = { 0.0f,100.0f,0.0f };//à íuèCê≥ñ{ëÃìñÇΩÇËîªíË
	const Vector3 corre2 = { 0.0f,80.0f,10.0f };//à íuèCê≥íeä€î≠ê∂à íu
}

Enemy2::Enemy2()
{
	
}

Enemy2::~Enemy2()
{
	DeleteGO(m_collisionObject);
}

bool Enemy2::Start()
{
	m_animationClips[enEnemy2Clip_Idle].Load("Assets/animData/skelton_idle.tka");
	m_animationClips[enEnemy2Clip_Idle].SetLoopFlag(true);
	m_animationClips[enEnemy2Clip_Attack].Load("Assets/animData/skelton_shot.tka");
	m_animationClips[enEnemy2Clip_Attack].SetLoopFlag(true);
	m_animationClips[enEnemy2Clip_Down].Load("Assets/animData/skelton_death.tka");
	m_animationClips[enEnemy2Clip_Down].SetLoopFlag(false);

	m_modelRender.Init("Assets/modelData/skelton.tkm"
		, m_animationClips, enEnemy2Clip_Num);
	player = FindGO<Player>("player");

	arrowtimer = arrowtime;

	m_modelRender.SetPosition(m_position);


	//m_charaCon.Init(20.0f, 100.0f, m_position);

	m_collisionObject = NewGO<CollisionObject>(0);

	m_collisionObject->CreateSphere(m_position, Quaternion::Identity, 60.0f * m_scale.z);
	m_collisionObject->SetName("enemy_col");
	m_collisionObject->SetPosition(m_position + corre1);

	m_collisionObject->SetIsEnableAutoDelete(false);

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

	return true;
}

void Enemy2::Update()
{
	Serch();
	AttackSerch();

	Rotation();
	Attack();

	Collision();
	PlayAnimation();

	m_modelRender.Update();
}

void Enemy2::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void Enemy2::Rotation()
{
	Vector3 diff = player->m_position - m_position;
	if (Serch() == true)
	{
		m_moveSpeed = diff * 100.0f;
	}

	m_modelRender.SetPosition(m_position);
	m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	m_modelRender.SetRotation(m_rotation);

	m_collisionObject->SetPosition(m_position + corre1);
}

void Enemy2::Attack()
{
	if (!AttackSerch())
		return;
	
	if (arrowtimer > 0)
	{
		arrowtimer -= g_gameTime->GetFrameDeltaTime();
		return;
	}
	m_enemy2State = 1;
	arrow = NewGO<Arrow>(0, "arrow");
	arrow->m_position = (m_position + corre2);
	arrow->m_1stPosition = arrow->m_position;
	arrow->m_rotation = m_rotation;

	arrowtimer = arrowtime;
}

const bool Enemy2::Serch()
{
	Vector3 diff = player->m_position - m_position;
	if (diff.LengthSq() <= serch)
	{
		return true;
	}
	arrowtimer = arrowtime;
}

const bool Enemy2::AttackSerch()
{
	Vector3 diff = player->m_position - m_position;
	if (diff.LengthSq() <= attackSerch)
	{
		return true;
	}
}

void Enemy2::Collision()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("p_arrow");

	for (auto collision : collisions) {
		if (collision->IsHit(m_collisionObject))
		{
			HP -= player->ATK;
		}
		if (HP <= 0) {
			m_enemy2State = 2;
			m_enemy2DownLag++;
			if (m_enemy2DownLag >= 20)
			{
				DeleteGO(this);
			}
		}
	}
}

void Enemy2::PlayAnimation()
{
	switch (m_enemy2State)
	{
	case 0:
		m_modelRender.PlayAnimation(enEnemy2Clip_Idle);
		break;
	case 1:
		m_modelRender.PlayAnimation(enEnemy2Clip_Attack);
		break;
	case 2:
		m_modelRender.PlayAnimation(enEnemy2Clip_Down);
		break;
	}
}