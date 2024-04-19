#include "stdafx.h"
#include "Boat.h"
#include "Game.h"
#include "Player.h"
#include <BackGround.h>

Boat::Boat()
{
	m_modelRender.Init("Assets/modelData/Boat.tkm");

	//m_modelRender.SetPosition(500.0f, -100.0f, 0.0f);
	//m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	player = FindGO<Player>("player");
	
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
	
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();//����
}

void Boat::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void Boat::Move()
{
	/*m_position.z -= 1.0f;*/

	m_position = player->m_position;
	m_position.y -= 70.0f;
	
	m_modelRender.SetPosition(m_position);

}