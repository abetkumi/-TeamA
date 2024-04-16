#include "stdafx.h"
#include "Point.h"
#include "Boat.h"

Point::Point()
{
	m_modelRender.Init("Assets/modelData/Point.tkm");
	m_modelRender.SetPosition(m_position);
	boat = FindGO<Boat>("boat");
	m_modelRender.Update();
}

Point::~Point()
{

}

void Point::Update()
{
	Vector3 dif = m_position - boat->m_position;
	if (dif.Length() <= 100.0f)
	{
		DeleteGO(this);
	}
	m_modelRender.Update();
	m_modelRender.SetPosition(m_position);
}

void Point::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}