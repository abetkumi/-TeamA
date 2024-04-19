#include "stdafx.h"
#include "Boat.h"
#include "Game.h"


Boat::Boat()
{
	m_modelRender.Init("Assets/modelData/Boat.tkm");
	m_spriteRender.Init("Assets/sprite/ship.dds", 100.0f, 100.0f);

	m_shipposition.x = -850.0f;
	m_shipposition.y = 470.0f;
	m_spriteRender.SetPosition(m_shipposition);

	//m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	
}

Boat::~Boat()
{
	
}

void Boat::Update()
{
	Move();

	m_modelRender.Update();
	m_physicsStaticObject.Release();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();//”»’è

	m_spriteRender.SetPosition(m_shipposition);
	m_spriteRender.Update();
}

void Boat::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_modelRender.Draw(rc);
}

void Boat::Move()
{
	m_position.z -= 1.0f;

	m_modelRender.SetPosition(m_position);
	
	ShipMove();
	m_gauge.z = m_position.z;
}

void Boat::ShipMove()
{
	if (m_position.z < m_gauge.z)
	{
		m_shipposition.x += 0.05f;
	}
}
