#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Arrow.h"
#include "Assist.h"
#include "GameCamera.h"

#include "collision/CollisionObject.h"

#include <time.h>

#define serch 2500.0f * 2500.0f
#define attackSerch 2000.0f * 2000.0f
#define playerSerch 3000.0f * 3000.0f
//#define attacktime 5.0f

namespace
{
	const Vector3 corre1 = { 0.0f,0.0f,0.0f };//à íuèCê≥ñ{ëÃìñÇΩÇËîªíË
	const Vector3 corre2 = { 0.0f,0.0f,10.0f };//à íuèCê≥íeä€î≠ê∂à íu
}

Enemy::Enemy()
{
	m_modelRender.Init("Assets/modelData/goblin.tkm");
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
}

Enemy::~Enemy()
{
	DeleteGO(m_collisionObject);
}

void Enemy::Update()
{
	Serch();
	AttackSerch();

	Rotation();
	Attack();
	Desision();

	Seek();
	Collision();
	
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
	
	m_collisionObject->SetPosition(m_position + corre1);
}

void Enemy::Attack()
{
	if (!AttackSerch())
		return;

	if (arrowtimer > 0)
	{
		arrowtimer -= g_gameTime->GetFrameDeltaTime();		
		return;
	}

		arrow = NewGO<Arrow>(0);
		arrow->m_position = (m_position + corre2);
		arrow->m_1stPosition = arrow->m_position;
		arrow->m_rotation = m_rotation;

		arrow->SetEnArrow(Arrow::enArrow_Enemy);

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

const bool Enemy::Desision()
{
	Vector3 diff = player->m_position - m_position;
	if (diff.LengthSq() <= playerSerch)
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

			if (HP <= 0) {
				DeleteGO(this);
			}
		}
	}
}

void Enemy::Seek()
{
	if (Desision() == true)
	{
		/*Vector3 pePos = m_position - player->m_position;
		double m_Dis = pePos.Length();
		assist->m_peTemporary = m_Dis;
		assist->m_peDisPos = pePos;*/
		
		Vector3 v = player->m_position + m_toCameraPos;
		v.Normalize();

		Vector3 ePos = m_position + m_toCameraPos;
		ePos.Normalize();

		m_Dec = v.Dot(ePos);
	}
}
