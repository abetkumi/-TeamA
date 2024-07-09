#include "stdafx.h"
#include "Arrow.h"
#include "collision/CollisionObject.h"
#include "sound/SoundEngine.h"
#include "Enemy.h"
#include "Enemy3.h"
#include "Player.h"
#include "GameCamera.h"
#include "Assist.h"
#include "Gravity.h"

#define attackSerch 1000.0f * 1000.0f

namespace
{
	const Vector3 scale = { 1.0f,1.0f,1.0f };
	const Vector3 scale2 = { 0.2f,0.2f,0.2f };
	const float g = 2000.0f;
}

Arrow::Arrow()
{

}

Arrow::~Arrow()
{
	
}

bool Arrow::Start()
{
	gameCamera = FindGO<GameCamera>("gameCamera");
	player = FindGO<Player>("player");


	m_modelRender[0].Init("Assets/modelData/Arrow.tkm");
	m_modelRender[0].SetScale(scale);

	m_modelRender[1].Init("Assets/modelData/test.tkm");
	m_modelRender[1].SetScale(scale2);
	

	g_soundEngine->ResistWaveFileBank(12, "Assets/BGM�ESE/player_shot.wav");
	g_soundEngine->ResistWaveFileBank(12, "Assets/BGM_SE/player_shot.wav");

	return true;
}

void Arrow::Update()
{
	if (m_Activate == true) {
		switch (m_Status)
		{
		case 0:
			Standby();
			break;

		case 1:
			Firstly();
			break;

		case 2:
			if (eHoming == true)
			{
				//Dec();
			}

			Move();
			Rotation();
			Inpacttime();
			Inpacthit();
			deletebullet();

			m_modelRender[m_model].Update();
			break;

		case 3:
			Release();
			break;

		default:
			break;
		}
	}
	

	
}

void Arrow::Standby()
{
	m_collisionObject = NewGO<CollisionObject>(0);

	switch (m_enArrow)
	{
		//�A���[
	case Arrow::enArrow_Player:
	case Arrow::enArrow_Skeleton:
		m_collisionObject->CreateBox(m_position, Quaternion::Identity, Vector3(10.0f, 10.0f, 10.0f));
		
		break;

		//��
	case Arrow::enArrow_Goblin:
		m_model++;
		m_collisionObject->CreateBox(m_position, Quaternion::Identity, Vector3(10.0f, 10.0f, 10.0f));
		break;

	default:
		break;
	}


	//�_���[�W,���O,SE�ȂǕ���
	switch (m_enArrow)
	{
	case Arrow::enArrow_Player:
		m_collisionObject->SetName("p_arrow");
		arrowSE = NewGO<SoundSource>(12);

		break;

	case Arrow::enArrow_Goblin:
		bullettime = 7.0f;
		m_collisionObject->SetName("e_arrow");
		m_Damage = 5;
		pHoming = true;
		break;

	case Arrow::enArrow_Skeleton:
		m_collisionObject->SetName("e_arrow");
		m_Damage = 8;
		pHoming = true;
		break;

	default:
		break;
	}

	m_collisionObject->SetIsEnableAutoDelete(false);

	m_Status++;
}

void Arrow::Firstly()
{
	m_velocity = Vector3::AxisZ;
	m_rotation.Apply(m_velocity);

	m_position += m_velocity * 50.0f;
	m_velocity *= 3000.0f;
	//m_rotation.SetRotationDegX(90.0f);


	if (m_enArrow == enArrow_Player) {
		arrowSE->Init(12);
		arrowSE->Play(false);
	}

	if (m_enArrow == enArrow_Goblin) {
		

		// �����x����߂�
		float initVel = sqrt((m_peLen * g * 1.0f) / 2.0f);
		// XZ���ʂł̑��x��v�Z����
		Vector3 velXZ = m_velocity;
		velXZ.y = 0.0f;
		velXZ.Normalize();
		velXZ *= initVel;
		m_velocity = velXZ;

		// Y�����̑��x����߂�
		m_velocity.y = initVel;
	}

	m_modelRender[m_model].SetPosition(m_1stPosition);
	m_modelRender[m_model].SetScale(scale);
	m_modelRender[m_model].SetRotation(m_rotation);
	m_collisionObject->SetPosition(m_position);

	m_modelRender[m_model].Update();

	m_Status++;
}

void Arrow::Release()
{
	Reset();
}

void Arrow::Rotation()
{
	float angle = atan2(-m_velocity.x, m_velocity.z);
	m_rotation.SetRotationY(-angle);
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

void Arrow::Move()
{
	if (m_enArrow == enArrow_Player) {
		m_position += m_velocity * g_gameTime->GetFrameDeltaTime();
		m_position.y += 80.0f * g_gameTime->GetFrameDeltaTime();
	}
	
	

	
	/*if (eHoming == true) {
		Vector3 diff = player->m_position - m_targetPos;
		diff.Normalize();

		m_position += diff * 2000.0f * g_gameTime->GetFrameDeltaTime();
	}*/
	
	if (pHoming == true) {
		Vector3 diff = player->m_position - m_position;
		Vector3 moveSpeed;
		float addSpeed = g * g_gameTime->GetFrameDeltaTime();

		switch (m_enArrow)
		{
		case Arrow::enArrow_Goblin:			
			//diff += m_velocity;
			diff.y = 0.0f;
			diff.Normalize();

			// ���x�ɑ΂��ďd�͉����x�������
		// ���̃t���[���ŉ������鑬�x����
			
			m_velocity.y -= addSpeed;

			moveSpeed = m_velocity;
			moveSpeed.y = 0;

			m_position.y += m_velocity.y * g_gameTime->GetFrameDeltaTime();
			m_position.x += diff.x * moveSpeed.Length() * 1.3f * g_gameTime->GetFrameDeltaTime();
			m_position.z += diff.z * moveSpeed.Length() * 1.3f * g_gameTime->GetFrameDeltaTime();
			break;

		case Arrow::enArrow_Skeleton:
			diff.y += 80.0f;
			diff.Normalize();

			m_position += diff * 2000.0f * g_gameTime->GetFrameDeltaTime();
			break;

		default:
			break;
		}
		
		//m_moveLock = 1;
		
	}


	m_modelRender[m_model].SetPosition(m_position);
	m_collisionObject->SetPosition(m_position);
	bullettime -= g_gameTime->GetFrameDeltaTime();
}

void Arrow::Render(RenderContext& rc)
{
	if (m_Status == 1 || m_Status == 2) {
		m_modelRender[m_model].Draw(rc);
	}
	
}

void Arrow::Inpacttime()
{
	if (bullettime > 0 && m_position.y > 0)
	{
		return;
	}
	m_Status++;
	//DeleteGO(m_collisionObject);
}

void Arrow::Inpacthit()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("e_arrow");
	for (auto collision : collisions)
	{
		if (collision->IsHit(player->m_charaCon))
		{
			DeleteGO(m_collisionObject);
			player->HP -= m_Damage;
			m_Status++;
		}
	}
}

void Arrow::deletebullet()
{
	/*if (m_isDelete) {
		m_deleteTimer -= g_gameTime->GetFrameDeltaTime();
		if (m_deleteTimer <= 0.0f) {
			//DeleteGO(m_collisionObject);
			DeleteGO(this);
		}
	}*/
}

void Arrow::Dec()
{
	//QueryGOs<Enemy>("Enemy", [&](Enemy* a) {
	//	if (a->homing == false)
	//	{
	//		enemy = a;
	//		return false;
	//	}
	//	return true;
	//	});

	//QueryGOs<Enemy2>("Enemy2", [&](Enemy2* a) {
	//	if (a->homing == false)
	//	{
	//		enemy2 = a;
	//		return false;
	//	}
	//	return true;
	//	});

	QueryGOs<Enemy3>("Enemy3", [&](Enemy3* a) {
		if (a->homing == false)
		{
			enemy3 = a;
			return false;
		}
		return true;
	});
	if (enemy != nullptr) {
			m_targetPos = enemy3->m_homingPos;
	}
	else {
		
	}
	
}

void Arrow::Collision()
{
	/*const auto& collisions = g_collisionObjectManager->FindCollisionObjects("e_arrow");

	for (auto collision : collisions) {
		if (collision->IsHit(player->m_charaCon))
		{
			player->HP -= m_Damage;
			DeleteGO(m_collisionObject);
			m_Status++;
		}
	}*/
}
