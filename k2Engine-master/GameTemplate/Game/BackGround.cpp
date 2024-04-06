#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{

	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

BackGround::~BackGround()
{

}

void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}