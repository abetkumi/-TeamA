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
	const Vector3 scale = { 10.0f,10.0f,10.0f };
	const Vector3 scale2 = { 0.02f,0.02f,0.02f };
	const float g = 2000.0f;
}

Arrow::Arrow()
{

}

Arrow::~Arrow()
{
	DeleteGO(m_collisionObject);
}

bool Arrow::Start()
{
	gameCamera = FindGO<GameCamera>("gameCamera");
	//assist = FindGO<Assist>("assist");
	player = FindGO<Player>("player");

	m_collisionObject = NewGO<CollisionObject>(0);

	m_modelRender.SetPosition(m_1stPosition);
	m_modelRender.SetScale(scale);
	m_modelRender.SetRotation(m_rotation);

	m_velocity = Vector3::AxisZ;
	m_rotation.Apply(m_velocity);
	g_soundEngine->ResistWaveFileBank(12, "Assets/BGM_SE/player_shot.wav");


	if (m_enArrow == enArrow_Player)
	{
		m_collisionObject->SetName("p_arrow");
		arrowSE = NewGO<SoundSource>(12);
		arrowSE->Init(12);
		arrowSE->Play(false);
	}
	else if (m_enArrow == enArrow_Enemy)
	{
		m_collisionObject->SetName("e_arrow");
		arrowSE = NewGO<SoundSource>(12);
		arrowSE->Init(12);
		arrowSE->Play(false);
		m_Damage = 50;
	}
	else if (m_enArrow == enArrow_Goblin)
	{
		m_collisionObject->SetName("e_arrow");
		//m_velocity.y -= i;
		m_Damage = 5;
	}
	else if (m_enArrow == enArrow_Skeleton)
	{
		m_collisionObject->SetName("e_arrow");
		m_Damage = 8;
		pHoming = true;
	}
	/*else if (m_enArrow == enArrow_Boss)
	{
		m_collisionObject->SetName("e_arrow");
		m_Damage = 10;
	}*/


	m_position += m_velocity * 50.0f;
	m_velocity *= 3000.0f;
	m_rotation.SetRotationDegX(90.0f);

	/*Quaternion tmp;
	tmp.SetRotationDegX(90.0f);

	m_modelRender.SetRotation(tmp);*/
	m_modelRender.Update();

	switch (m_enArrow)
	{
	case Arrow::enArrow_Player:
	case Arrow::enArrow_Skeleton:
		m_modelRender.Init("Assets/modelData/Arrow.tkm");
		m_collisionObject->CreateBox(m_position, Quaternion::Identity, Vector3(10.0f, 10.0f, 10.0f));
		m_modelRender.SetScale(scale);
		break;

	case Arrow::enArrow_Goblin: {
		m_modelRender.Init("Assets/modelData/rock_4.tkm");
		//m_modelRender.Init("Assets/modelData/amo.tkm");
		m_modelRender.SetScale(scale);
		m_collisionObject->CreateBox(m_position, Quaternion::Identity, Vector3(10.0f, 10.0f, 10.0f));

		bullettime = 7.0f;

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

		m_modelRender.SetScale(scale2);

	}break;

	case Arrow::enArrow_Boss:
		//m_modelRnder.Init("Assts/modelData/");
		m_collisionObject->CreateBox(m_position, Quaternion::Identity, Vector3(10.0f, 10.0f, 10.0f));
		m_collisionObject->SetName("e_arrow");
		m_Damage = 10;
		break;

	case Arrow::enArrow_Enemy:
		m_modelRender.Init("Assets/modelData/Arrow.tkm");
		m_collisionObject->CreateBox(m_position, Quaternion::Identity, Vector3(10.0f, 10.0f, 10.0f));
		break;

	default:
		break;
	}
	
	m_collisionObject->SetIsEnableAutoDelete(false);

	return true;
}

void Arrow::Update()
{
	Move();
	Rotation();
	Inpacttime();
	Inpacthit();
	deletebullet();

	if (enemy->Dec() == true)
	{
		Dec();
	}

	m_modelRender.Update();
}

void Arrow::Rotation()
{
	float angle = atan2(-m_velocity.x, m_velocity.z);
	m_rotation.SetRotationY(-angle);
	//m_modelRender.SetRotation(m_rotation);
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
		for (int i = 0; i < enemys3.empty(); i++) {
			if (enemys3[i]->homing == true) {
				Vector3 diff = enemys3[i]->m_homingPos - m_position;
				diff.Normalize();

				m_position += diff * 1000.0f * g_gameTime->GetFrameDeltaTime();
			}
		}
	}
	
	if (pHoming == true) {
		Vector3 diff = player->m_position - m_position;
		diff.y += 80.0f;
		diff.Normalize();

		m_position += diff * 2000.0f * g_gameTime->GetFrameDeltaTime();
	}


	m_modelRender.SetPosition(m_position);
	m_collisionObject->SetPosition(m_position);
	bullettime -= g_gameTime->GetFrameDeltaTime();
}

void Arrow::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void Arrow::Inpacttime()
{
	if (bullettime > 0 && m_position.y > 0)
	{
		return;
	}
	//DeleteGO(m_collisionObject);
	DeleteGO(this);
}

void Arrow::Inpacthit()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("e_arrow");
	for (auto collision : collisions)
	{
		if (collision->IsHit(player->m_charaCon))
		{
			DeleteGO(m_collisionObject);
			DeleteGO(this);
		}
	}
}

void Arrow::deletebullet()
{
	if (m_isDelete) {
		m_deleteTimer -= g_gameTime->GetFrameDeltaTime();
		if (m_deleteTimer <= 0.0f) {
			//DeleteGO(m_collisionObject);
			DeleteGO(this);
		}
	}
}

void Arrow::Dec()
{


}