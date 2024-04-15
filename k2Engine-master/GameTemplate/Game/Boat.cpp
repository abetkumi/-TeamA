#include "stdafx.h"
#include "Boat.h"

Boat::Boat()
{
	m_modelRender.Init("Assets/modelData/Boat.tkm");

	m_modelRender.SetScale(Vector3(3.0f, 1.0f, 3.0f));
	m_modelRender.Update();
	collisonObject.CreateBox(m_position, m_rotation,size );
}

Boat::~Boat()
{
	
}

void Boat::Update()
{
	Move();

	m_modelRender.Update();
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
