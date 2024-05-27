#include "stdafx.h"
#include "Sky.h"

Sky::Sky()
{
	s_modelRender.Init("Assets/modelData/sky.tkm");
	//m_modelRender.Init("Assets/modelData/level_3.tkm");

	s_modelRender.Update();
	s_physicsStaticObject.CreateFromModel(s_modelRender.GetModel(), s_modelRender.GetModel().GetWorldMatrix());
}

Sky::~Sky()
{

}

void Sky::Render(RenderContext& rc)
{
	s_modelRender.Draw(rc);
}