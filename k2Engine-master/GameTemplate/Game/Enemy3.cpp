#include "stdafx.h"
#include "Enemy3.h"
#include "Player.h"
#include "Arrow.h"

#include "collision/CollisionObject.h"

#include <time.h>
#include <math.h>

#define serch 1300.0f * 1300.0f
#define moveSerch 5000.0f * 5000.0f

#define distance 100.0f * 100.0f
//#define attacktime 5.0f

namespace
{
	const Vector3 corre1 = { 0.0f,0.0f,0.0f };//à íuèCê≥ñ{ëÃìñÇΩÇËîªíË
	//const Vector3 corre2 = { 0.0f,80.0f,10.0f };//à íuèCê≥íeä€î≠ê∂à íu
}

Enemy3::Enemy3()
{
	
}

Enemy3::~Enemy3()
{
	DeleteGO(m_collisionObject);
}

bool Enemy3::Start()
{
	m_modelRender.Init("Assets/modelData/bat.tkm");


	player = FindGO<Player>("player");
	arrowtimer = arrowtime;


	m_collisionObject = NewGO<CollisionObject>(0);

	m_collisionObject->CreateSphere(m_position, Quaternion::Identity, 60.0f * m_scale.z);
	m_collisionObject->SetName("bat_enemy_col");
	
	m_modelRender.SetPosition(m_position);
	m_collisionObject->SetPosition(m_position + corre1);

	m_collisionObject->SetIsEnableAutoDelete(false);


	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

	return true;
}

void Enemy3::Update()
{
	Serch();
	MoveSerch();
	Collision();
	Rotation();
	Attack();

	switch (a)
	{
	case 0:
		if(Serch() == true)
		a = 1;
		break;
	case 1:
		Calculation();
		break;
	case 2:
		Move();
		break;
	default:
		break;
	}
	
	m_modelRender.Update();
}

void Enemy3::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void Enemy3::Move()
{
	if (MoveSerch() == true) {
		y = rand() % 100000;

		if (y == 1)
		{
			Xt *= -1.0f;
		}

		m_position = { 
			player->m_position.x + cos(x1) * 1190.0f,
			m_position.y,
			player->m_position.z + sin(x1) * 1190.0f
		};
		x1 += Xt * g_gameTime->GetFrameDeltaTime();

		//m_position += player->m_moveSpeed * 3.0f * g_gameTime->GetFrameDeltaTime();
	}
	
	if (arrowtimer > 0.0f) {
		m_modelRender.SetPosition(m_position);
		m_collisionObject->SetPosition(m_position);
	}
	else {
		
	}
	
}

void Enemy3::AttackMove()
{
	Distance();

	
	Vector3 moveSpeed;
	Vector3 diff1 = player->m_position - m_attackPos;
	Vector3 diff2 = m_position - m_attackPos;
	
	diff1.Normalize();
	diff2.Normalize();

	if (AM == 0) {
		moveSpeed = diff1 * 2000.0f;

		m_attackPos += moveSpeed * g_gameTime->GetFrameDeltaTime();

		if (Distance() == true) {
			AM = 1;
		}
	}
	else {
		moveSpeed = diff2 * 2000.0f;

		m_attackPos += moveSpeed * g_gameTime->GetFrameDeltaTime();

		if (PosDistance() == true) {
			AM = 0;
			arrowtimer = arrowtime;
			b = 0;
		}
	}

	m_modelRender.SetPosition(m_attackPos);
	m_collisionObject->SetPosition(m_attackPos);
}

void Enemy3::Rotation()
{
	Vector3 diff = player->m_position - m_position;
	if (Serch() == true)
	{
		m_moveSpeed = diff * 100.0f;
	}

	//m_modelRender.SetPosition(m_position);
	m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	m_modelRender.SetRotation(m_rotation);

	m_cNPos = m_position - player->m_position;
	m_cNPos.Normalize();
	m_rotation.AddRotationX(m_cNPos.y);

	
}

void Enemy3::Attack()
{
	

	if (Serch() == false)
		return;

	if (arrowtimer > 0.0f)
	{
		arrowtimer -= g_gameTime->GetFrameDeltaTime();
		return;
	}

	else
	if (b == 0) {
		m_attackPos = m_position;
		b = 1;
	}

	AttackMove();
	
	//arrowtimer = arrowtime;
}

void Enemy3::Calculation()
{
	Vector3 diff = player->m_position - m_position;

	diff.y = 0;
	diff.Normalize();


	x1 = diff.z / diff.x;
	x1 = atan(x1);
	x1 += 3.1f;
	

	a = 2;
}

const bool Enemy3::Serch()
{
	Vector3 diff = player->m_position - m_position;
	if (diff.LengthSq() <= serch)
	{
		return true;
	}
	//arrowtimer = arrowtime;
}

const bool Enemy3::MoveSerch()
{
	Vector3 diff = player->m_position - m_position;
	if (diff.LengthSq() <= moveSerch)
	{
		return true;
	}
}

const bool Enemy3::Distance()
{
	Vector3 diff = player->m_position - m_attackPos;
	if (diff.LengthSq() <= distance)
	{
		return true;
	}
}

const bool Enemy3::PosDistance()
{
	Vector3 diff = m_position - m_attackPos;
	if (diff.LengthSq() <= distance / 25.0f)
	{
		return true;
	}
}

void Enemy3::Collision()
{
	
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("p_arrow");

	for (auto collision : collisions) {
		if (collision->IsHit(m_collisionObject))
		{
			HP -= player->ATK;

			if (HP <= 0) {
				DeleteGO(this);
			}
		}
	}
}

