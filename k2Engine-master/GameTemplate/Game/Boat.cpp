#include "stdafx.h"
#include "Boat.h"
#include "Game.h"

Boat::Boat()
{
	m_modelRender.Init("Assets/modelData/Boat.tkm");

	FindGO<Game>("game");
	m_modelRender.SetScale(m_scale);
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
}

void Boat::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void Boat::Move()
{
	m_position.z -= 1.0f;

	m_modelRender.SetPosition(m_position);
	
}
