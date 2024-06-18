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
	/*Quaternion rot;*/
	m_rotation.SetRotationDegY(180.0f);
	m_modelRender.SetRotation(m_rotation);

	m_modelRender.Update();
	//m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	player = FindGO<Player>("player");
	game = FindGO<Game>("game");
	
	m_shipPoint = player->m_point;

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
	ShipMove();
	m_modelRender.Update();
	
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();//����

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

	m_position.x = player->m_position.x;
	m_position.z = player->m_position.z;
	//船を上下に揺らす
	m_position.y -= 0.05f * m_shipswitch;
	m_shiptimer += g_gameTime->GetFrameDeltaTime() * m_shipswitch;
	if (m_shiptimer > 3.0f || m_shiptimer < 0.0f)
	{
		m_shipswitch *= -1.0f;
	}
	m_modelRender.SetPosition(m_position);
}

void Boat::Rotation()
{
	if (game->m_spriteStatus == 5 && player->m_moveSpeed.z != 0.0f)
	{
		auto moveDir = player->m_moveSpeed;
		moveDir.Normalize();
		m_direction = m_direction * 0.98f + moveDir * 0.02f;
		m_direction.Normalize();
		m_rotation.SetRotationYFromDirectionXZ(m_direction);
		m_modelRender.SetRotation(m_rotation);
	}
}

void Boat::ShipMove()
{

	if (player->m_point > m_shipPoint)
	{
		m_shipposition.x += 4.0f;
		m_shipPoint = player->m_point;
	}
}