#include "stdafx.h"
#include "Enemy2.h"
#include "Player.h"
#include "Arrow.h"
#include "Assist.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "GameCamera.h"
#include "collision/CollisionObject.h"

#include <time.h>

#define serch 4000.0f * 4000.0f
#define attackSerch 3000.0f * 3000.0f
#define playerSerch 5000.0f * 5000.0f
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
	m_animation2Clips[enEnemy2Clip_Idle].Load("Assets/animData/goblinArcher_idle.tka");
	m_animation2Clips[enEnemy2Clip_Idle].SetLoopFlag(true);
	m_animation2Clips[enEnemy2Clip_Pull].Load("Assets/animData/goblinArcher_aimhold.tka");
	m_animation2Clips[enEnemy2Clip_Pull].SetLoopFlag(false);
	m_animation2Clips[enEnemy2Clip_Attack].Load("Assets/animData/goblinArcher_attack.tka");
	m_animation2Clips[enEnemy2Clip_Attack].SetLoopFlag(false);
	m_animation2Clips[enEnemy2Clip_Down].Load("Assets/animData/goblinArcher_death.tka");
	m_animation2Clips[enEnemy2Clip_Down].SetLoopFlag(false);

	m_modelRender.Init("Assets/modelData/goblin_Archer3.tkm"
		, m_animation2Clips, enEnemy2Clip_Num);

	//m_modelRender.Init("Assets/modelData/goblin_Archer3.tkm");

	g_soundEngine->ResistWaveFileBank(1, "Assets/BGMÅESE/hit.wav");

	player = FindGO<Player>("player");
	//assist = FindGO<Assist>("assist");

	arrowtimer = arrowtime;

	m_scale = { 1.5f, 1.5f, 1.5f };
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_spriteRender.Init("Assets/sprite/HPWhite.dds", 200.0f, 200.0f);
	m_spriteRender.SetPivot({ 0.0f,0.5f });

	m_spriteRender.SetPosition(m_position);
	m_spriteRender.Update();

	//m_charaCon.Init(20.0f, 100.0f, m_position);

	m_collisionObject = NewGO<CollisionObject>(1);

	m_collisionObject->CreateCapsule(m_position, Quaternion::Identity, 60.0f * m_scale.z, 60.0f * m_scale.y);
	m_collisionObject->SetName("enemy_col");
	m_collisionObject->SetPosition(m_position + corre1);

	m_collisionObject->SetIsEnableAutoDelete(false);

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);


	//m_modelRender.Update();
	return true;
}

void Enemy2::Update()
{
	Serch();
	AttackSerch();

	Rotation();
	Attack();
	Desision();

	Seek();
	Collision();
	PlayAnimation();

	m_modelRender.Update();
}

void Enemy2::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	m_spriteRender.Draw(rc);
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

	if (m_attackBar.x <= 0)
	{
		m_enemy2State = 2;
		arrow = NewGO<Arrow>(0, "arrow");

		arrow->m_position = (m_position + corre2);
		arrow->m_1stPosition = arrow->m_position;
		arrow->m_rotation = m_rotation;

		arrow->SetEnArrow(Arrow::enArrow_Enemy);

		arrowtimer = arrowtime;
	}
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
			m_enemy2State = 3;
		}
	}
}

void Enemy2::Seek()
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

const bool Enemy2::Desision()
{
	Vector3 diff = player->m_position - m_position;
	if (diff.LengthSq() <= playerSerch)
	{
		return true;
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
		EnemyAttackBar();
		m_modelRender.PlayAnimation(enEnemy2Clip_Pull);
		break;
	case 2:
		m_modelRender.PlayAnimation(enEnemy2Clip_Attack);
		break;
	case 3:
		m_modelRender.PlayAnimation(enEnemy2Clip_Down);
		m_enemy2DownLag++;
		if (m_enemy2DownLag >= 20)
		{
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(1);
			se->Play(false);

			DeleteGO(this);
		}
		break;
	}
}


void Enemy2::EnemyAttackBar()
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
		m_attackBar.x = 1.0f;
	}

	g_camera3D->CalcScreenPositionFromWorldPosition(m_spritePosition, position);
	m_spriteRender.SetPosition(Vector3(m_spritePosition.x, m_spritePosition.y, 0.0f));
	m_spriteRender.SetScale(m_attackBar);
	m_spriteRender.Update();
}