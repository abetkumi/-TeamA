#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Arrow.h"
#include "Assist.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "GameCamera.h"

#include "collision/CollisionObject.h"

#include <time.h>
//4000,3000
#define serch 4000.0f * 4000.0f
#define attackSerch 3000.0f * 3000.0f
#define playerSerch 5000.0f * 5000.0f
#define deleteSerch 5000.0f * 5000.0f
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

	g_soundEngine->ResistWaveFileBank(1, "Assets/BGM・SE/hit.wav");
	g_soundEngine->ResistWaveFileBank(7, "Assets/BGM・SE/goblin_throw.wav");

	m_spriteRender.Init("Assets/sprite/HPWhite.dds", 200.0f, 200.0f);
	m_spriteRender.SetPivot({ 0.0f,0.5f });

	m_spriteRender.SetPosition(m_position);
	m_spriteRender.Update();

	player = FindGO<Player>("player");
	assist = FindGO<Assist>("assist");
	gameCamera = FindGO<GameCamera>("gameCamera");

	arrowtimer = arrowtime;

	m_modelRender.SetPosition(m_position);


	//m_charaCon.Init(20.0f, 100.0f, m_position);

	m_collisionObject = NewGO<CollisionObject>(0);

	m_collisionObject->CreateCapsule(m_position, Quaternion::Identity, 60.0f * m_scale.z,60.0f*m_scale.y);
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
	
	if (i == 1)
	{
		DeleteSerch();

		if (DeleteSerch() == true) {
			DeleteGO(this);
		}
	}

	m_modelRender.Update();
	//m_spriteRender.Update();
}

void Enemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	m_spriteRender.Draw(rc);
}

void Enemy::Rotation()
{
	Vector3 diff = player->m_position - m_position;

	if (!Serch()) {
		m_enemyState = 0;
		arrowtimer = arrowtime;
	}

	if (Serch() == true)
	{
		m_moveSpeed = diff * 100.0f;
		i = 1;
	}

	

	m_modelRender.SetPosition(m_position);
	m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	m_modelRender.SetRotation(m_rotation);
	
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
	i = 1;
	m_enemyState = 1;
	if (m_attackBar.x <= 0)
	{
		m_attackBar.x = 1.6f;

		SoundSource* se = NewGO<SoundSource>(7);
		se->Init(7);
		se->Play(false);

		arrow = NewGO<Arrow>(0);

		arrow->m_position = (m_position + corre2);
		arrow->m_1stPosition = arrow->m_position;
		arrow->m_rotation = m_rotation;

		diff.y = 0.0f;
		arrow->m_velocity = diff;
		arrow->m_velocity.y = 0.0f;
		arrow->m_velocity.Normalize();
		arrow->m_velocity *= sqrt(2) / 2;
		arrow->m_velocity.y = sqrt(2) / 2;

		arrow->m_peLen = diff.Length();

		arrow->SetEnArrow(Arrow::enArrow_Goblin);

		arrowtimer = arrowtime;

	}
}

const bool Enemy::Serch()
{
	Vector3 diff = player->m_position - m_position;
	if (diff.LengthSq() <= serch)
	{
		return true;
	}
	return false;
}

const bool Enemy::AttackSerch()
{
	Vector3 diff = player->m_position - m_position;
	if (diff.LengthSq() <= attackSerch)
	{
		return true;
	}
	return false;
}

const bool Enemy::DeleteSerch()
{
	Vector3 diff = player->m_position - m_position;
	if (diff.LengthSq() > deleteSerch)
	{
		return true;
	}
	return false;
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
	return false;
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
		EnemyAttackBar();
		m_modelRender.PlayAnimation(enEnemyClip_Attack);
		break;
	case 2:
		m_modelRender.PlayAnimation(enEnemyClip_Down);
		m_enemyDownLag++;
		if (m_enemyDownLag >= 20)
		{
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(1);
			se->Play(false);

			DeleteGO(this);
		}
		break;
	}
}

void Enemy::EnemyAttackBar()
{
	Vector3 V0, V1;
	float V2;

	V0 = g_camera3D->GetForward();
	V1 = m_position - g_camera3D->GetPosition();
	V1.Normalize();

	V2 = V0.x * V1.x + V0.y * V1.y + V0.z * V1.z ;

	if (V2 >= 0)
	{


		Vector3 position = m_position;

		position.y += 200.0f;

		if (m_attackBar.x >= 0.4f)
		{
			m_spriteRender.SetMulColor({ 0.0f,1.0f,0.0f,1.0f });
			m_attackBar.x -= 0.009f;
		}
		else if (m_attackBar.x < 0.4f && m_attackBar.x > 0.0f)
		{
			m_spriteRender.SetMulColor({ 1.0f,0.0f,0.0f,1.0f });
			m_attackBar.x -= 0.009f;
		}
		else if (m_attackBar.x <= 0)
		{
			m_attackBar.x = 1.36f;
		}

		g_camera3D->CalcScreenPositionFromWorldPosition(m_spritePosition, position);
		m_spriteRender.SetPosition(Vector3(m_spritePosition.x, m_spritePosition.y, 0.0f));
		m_spriteRender.SetScale(m_attackBar);
		m_spriteRender.Update();
	}
}