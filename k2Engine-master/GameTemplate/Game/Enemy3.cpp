#include "stdafx.h"
#include "Enemy3.h"
#include "Player.h"
#include "Arrow.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Item.h"

#include "collision/CollisionObject.h"

#include <time.h>
#include <math.h>

#define serch 1300.0f * 1300.0f
#define moveSerch 5000.0f * 5000.0f

#define distance 100.0f * 100.0f
//#define attacktime 5.0f

namespace
{
	const Vector3 corre1 = { 0.0f,0.0f,0.0f };//�ʒu�C���{�̓����蔻��
	//const Vector3 corre2 = { 0.0f,80.0f,10.0f };//�ʒu�C���e�۔����ʒu
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

	g_soundEngine->ResistWaveFileBank(1, "Assets/BGM・SE/hit.wav");
	g_soundEngine->ResistWaveFileBank(20, "Assets/BGM・SE/bat_voice.wav");

	player = FindGO<Player>("player");
	arrowtimer = arrowtime;


	m_collisionObject = NewGO<CollisionObject>(0);

	m_collisionObject->CreateSphere(m_position, Quaternion::Identity, 60.0f * m_scale.z);
	m_collisionObject->SetName("bat_enemy_col");
	
	m_modelRender.SetPosition(m_position);
	m_collisionObject->SetPosition(m_position + corre1);

	m_collisionObject->SetIsEnableAutoDelete(false);



	m_spriteRender.Init("Assets/sprite/HPWhite.dds", 200.0f, 200.0f);
	m_spriteRender.SetPivot({ 0.0f,0.5f });

	m_spriteRender.SetPosition(m_position);
	m_spriteRender.Update();


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
	ItemDrop();

	switch (initialAng)
	{
	case 0:
		if(Serch() == true)
		Calculation();
		break;
	case 1:
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
	m_spriteRender.Draw(rc);
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
	PosDistance();

	
	Vector3 moveSpeed;
	Vector3 diff1 = player->m_position - m_attackPos;
	Vector3 diff2 = m_position - m_attackPos;
	
	diff1.Normalize();
	diff2.Normalize();

	if (moveStatus == 0) {
		moveSpeed = diff1 * 2000.0f;

		m_attackPos += moveSpeed * g_gameTime->GetFrameDeltaTime();

		if (Distance() == true) {
			moveStatus = 1;
		}
	}
	else {
		moveSpeed = diff2 * 2000.0f;

		m_attackPos += moveSpeed * g_gameTime->GetFrameDeltaTime();

		if (PosDistance() == true) {
			moveStatus = 0;
			arrowtimer = arrowtime;
			initialPos = 0;
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
	
	if (!Serch())
		return;

	if (arrowtimer > 0.0f)
	{
		arrowtimer -= g_gameTime->GetFrameDeltaTime();
		EnemyAttackBar();
		return;
	}

	else {
		if (initialPos == 0) {
			m_attackPos = m_position;
			initialPos = 1;
		}
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
	

	initialAng = 1;
}

void Enemy3::EnemyAttackBar()
 {
	float Decrease = (1.0f / arrowtime) * g_gameTime->GetFrameDeltaTime();

	Vector3 V0, V1;
	float V2;

	V0 = g_camera3D->GetForward();
	V1 = m_position - g_camera3D->GetPosition();
	V1.Normalize();

	V2 = V0.x * V1.x + V0.y * V1.y + V0.z * V1.z;

	if (V2 >= 0)
	{

		Vector3 position = m_position;

		position.y += 200.0f;

		if (m_attackBar.x >= 0.4f)
		{
			m_spriteRender.SetMulColor({ 0.0f,1.0f,0.0f,1.0f });
			m_attackBar.x -= Decrease;
		}
		else if (m_attackBar.x < 0.4f && m_attackBar.x > 0.0f)
		{
			m_spriteRender.SetMulColor({ 1.0f,0.0f,0.0f,1.0f });
			m_attackBar.x -= Decrease;
		}
		else if (m_attackBar.x <= 0)
		{
			//m_enemy2State = 2;
			m_attackBar.x = 1.0f;
		}

		g_camera3D->CalcScreenPositionFromWorldPosition(m_spritePosition, position);
		m_spriteRender.SetPosition(Vector3(m_spritePosition.x, m_spritePosition.y, 0.0f));
		m_spriteRender.SetScale(m_attackBar);
		m_spriteRender.Update();
	}
}



const bool Enemy3::Serch()
{
	Vector3 diff = player->m_position - m_position;
	if (diff.LengthSq() <= serch)
	{
		return true;
	}
	//arrowtimer = arrowtime;
	return false;
}

const bool Enemy3::MoveSerch()
{
	Vector3 diff = player->m_position - m_position;
	if (diff.LengthSq() <= moveSerch)
	{
		return true;
	}
	return false;
}

const bool Enemy3::Distance()
{
	Vector3 diff = player->m_position - m_attackPos;
	if (diff.LengthSq() <= distance)
	{
		return true;
	}
	return false;
}

const bool Enemy3::PosDistance()
{
	Vector3 diff = m_position - m_attackPos;
	if (diff.LengthSq() <= distance / 25.0f)
	{
		return true;
	}
	return false;
}

void Enemy3::Collision()
{
	
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("p_arrow");

	for (auto collision : collisions) {
		if (collision->IsHit(m_collisionObject))
		{
			HP -= (int)player->ATK;

			if (HP <= 0) {
				m_downFlag = true;

				se = NewGO<SoundSource>(1);
				se->Init(1);
				se->Play(false);

				se = NewGO<SoundSource>(20);
				se->Init(20);
				se->Play(false);

			}
		}
	}
	if (m_downFlag == true)
	{
		m_enemy3DownLag++;
		if (m_enemy3DownLag >= 20)
		{
			m_itemGet = rand() % 4;
			player->m_score += 300;
			DeleteGO(this);
		}
	}
}

void Enemy3::ItemDrop()
{
	switch (m_itemGet)
	{
	case 0:
		break;
	case 1:
		item = NewGO<Item>(0, "item");
		m_itemGet = 0;
		break;
	default:
		break;
	}
}