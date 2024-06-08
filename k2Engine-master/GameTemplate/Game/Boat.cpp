#include "stdafx.h"
#include "Boat.h"
#include "Game.h"
#include "Player.h"
#include <BackGround.h>

Boat::Boat()
{
	
}

Boat::~Boat()
{
	
}

bool Boat::Start()
{
	m_modelRender.Init("Assets/modelData/Boat.tkm");
	//m_modelRender.SetPosition(500.0f, -100.0f, 0.0f);
	//m_modelRender.SetScale(m_scale);

	m_spriteRender.Init("Assets/sprite/ship.dds", 100.0f, 100.0f);
	m_shipposition.x = -850.0f;
	m_shipposition.y = 470.0f;
	m_spriteRender.SetPosition(m_shipposition);

	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	player = FindGO<Player>("player");
	game = FindGO<Game>("game");
	
	return true;
}

void Boat::Update()
{
	if (m_direction.Length() < 0.1f) {
		m_direction = player->m_moveSpeed;
		m_direction.Normalize();
	}
	Move();
	Rotation();

	m_modelRender.Update();
	m_physicsStaticObject.Release();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();//����

	m_spriteRender.SetPosition(m_shipposition);
	m_spriteRender.Update();

}

void Boat::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	m_spriteRender.Draw(rc);
}

void Boat::Move()
{
	/*m_position.z -= 1.0f;*/

	m_position = player->m_position;
	m_position.y -= 70.0f;
	
	m_modelRender.SetPosition(m_position);

	ShipMove();
	m_shipGauge.z = m_position.z;

}

void Boat::Rotation()
{
	auto moveDir = player->m_moveSpeed;
	moveDir.Normalize();
	m_direction = m_direction * 0.98f + moveDir * 0.02f;
	m_direction.Normalize();
	m_rotation.SetRotationYFromDirectionXZ(m_direction);
	m_modelRender.SetRotation(m_rotation);
}

void Boat::ShipMove()
{
	if (m_position.z < m_shipGauge.z)
	{
		m_shipposition.x += 0.1f;
	}
}