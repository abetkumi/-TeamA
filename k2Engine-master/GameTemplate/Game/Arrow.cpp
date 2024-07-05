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

	m_collisionObject = NewGO<CollisionObject>(0);
	m_collisionObject->SetName("arrow");


	m_modelRender[0].Init("Assets/modelData/Arrow.tkm");
	m_modelRender[0].SetScale(scale);

	m_modelRender[1].Init("Assets/modelData/test.tkm");
	m_modelRender[1].SetScale(scale2);
	

	g_soundEngine->ResistWaveFileBank(12, "Assets/BGM・SE/player_shot.wav");
	
	m_collisionObject->SetIsEnableAutoDelete(false);

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
			Move();
			Rotation();
			Inpacttime();
			Inpacthit();
			deletebullet();

			if (enemy->Dec() == true)
			{
				Dec();
			}

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
	switch (m_enArrow)
	{
		//アロー
	case Arrow::enArrow_Player:
	case Arrow::enArrow_Skeleton:
		m_collisionObject->CreateBox(m_position, Quaternion::Identity, Vector3(10.0f, 10.0f, 10.0f));
		
		break;

		//岩
	case Arrow::enArrow_Goblin:
		m_model++;
		m_collisionObject->CreateBox(m_position, Quaternion::Identity, Vector3(10.0f, 10.0f, 10.0f));
		
		break;

	default:
		break;
	}


	//ダメージ,名前,SEなど分岐
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
		break;

	case Arrow::enArrow_Skeleton:
		m_collisionObject->SetName("e_arrow");
		m_Damage = 8;
		pHoming = true;
		break;

	default:
		break;
	}

	m_Status++;
}

void Arrow::Firstly()
{
	m_velocity = Vector3::AxisZ;
	m_rotation.Apply(m_velocity);

	m_position += m_velocity * 50.0f;
	m_velocity *= 3000.0f;
	m_rotation.SetRotationDegX(90.0f);


	if (m_enArrow == enArrow_Player) {
		arrowSE->Init(12);
		arrowSE->Play(false);
	}

	if (m_enArrow == enArrow_Goblin) {
		

		// 初速度を求める
		float initVel = sqrt((m_peLen * g * 1.0f) / 2.0f);
		// XZ平面での速度を計算する
		Vector3 velXZ = m_velocity;
		velXZ.y = 0.0f;
		velXZ.Normalize();
		velXZ *= initVel;
		m_velocity = velXZ;

		// Y方向の速度を求める
		m_velocity.y = initVel;
	}

	m_modelRender[m_model].SetPosition(m_1stPosition);
	m_modelRender[m_model].SetScale(scale);
	m_modelRender[m_model].SetRotation(m_rotation);

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
	const std::vector<Enemy3*>& enemys3 = FindGOs<Enemy3>("enemy3");
	
	m_position += m_velocity * g_gameTime->GetFrameDeltaTime();


	if (m_enArrow == enArrow_Goblin){
		// 速度に対して重力加速度を加える
		// このフレームで加速する速度する
		float addSpeed = g * g_gameTime->GetFrameDeltaTime();
		m_velocity.y -= addSpeed;
	}

	if (eHoming == true) {
		/*for (int i = 0; i < enemys3.empty(); i++) {
			if (enemys3[i]->homing == true) {
				Vector3 diff = enemys3[i]->m_homingPos - m_position;
				diff.Normalize();

				m_position += diff * 1000.0f * g_gameTime->GetFrameDeltaTime();
			}
		}*/
	}
	
	if (pHoming == true) {
		Vector3 diff = player->m_position - m_position;
		diff.y += 80.0f;
		diff.Normalize();

		m_position += diff * 2000.0f * g_gameTime->GetFrameDeltaTime();
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
}

void Arrow::Inpacthit()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("e_arrow");
	for (auto collision : collisions)
	{
		if (collision->IsHit(player->m_charaCon))
		{
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
			DeleteGO(m_collisionObject);
			DeleteGO(this);
		}
	}*/
}

void Arrow::Dec()
{


}