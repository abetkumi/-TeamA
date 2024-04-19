#include "stdafx.h"
#include "Arrow.h"
#include "collision/CollisionObject.h"
#include "Enemy.h"
#include "Player.h"

namespace
{
	const Vector3 scale = { 1.0f,1.0f,1.0f };
}

bool Arrow::Start()
{
	m_modelRender.Init("Assets/modelData/amo.tkm");

	//enemy = FindGO<Enemy>("enemy");

	m_modelRender.SetPosition(m_1stPosition);
	m_modelRender.SetScale(scale);
	m_modelRender.SetRotation(m_rotation);

	m_velocity = Vector3::AxisZ;
	m_rotation.Apply(m_velocity);
	m_position += m_velocity * 50.0f;
	m_velocity *= 1200.0f;
	m_rotation.AddRotationDegY(360.0f);

	m_collisionObject = NewGO<CollisionObject>(0);
	m_collisionObject->CreateSphere(m_position, Quaternion::Identity, 20.0f * m_scale.z);
	m_collisionObject->SetName("player_atttack");
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

	m_modelRender.Update();
}

void Arrow::Rotation()
{
	float angle = atan2(-m_velocity.x, m_velocity.z);
	m_rotation.SetRotationY(-angle);
	m_modelRender.SetRotation(m_rotation);
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

void Arrow::Move()
{
	m_position += m_velocity * g_gameTime->GetFrameDeltaTime();
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
	if (bullettime > 0)
	{
		return;
	}
	DeleteGO(m_collisionObject);
	DeleteGO(this);
}

void Arrow::Inpacthit()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("enemy");
	for (auto collision : collisions)
	{
		if (collision->IsHit(m_collisionObject))
		{
			if (m_isDelete == false) {
				m_isDelete = true;
				m_deleteTimer = deletetimer;
			}
		}
	}
}

void Arrow::deletebullet()
{
	if (m_isDelete) {
		m_deleteTimer -= g_gameTime->GetFrameDeltaTime();
		if (m_deleteTimer <= 0.0f) {
			DeleteGO(m_collisionObject);
			DeleteGO(this);
		}
	}
}
