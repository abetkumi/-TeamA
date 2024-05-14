#include "stdafx.h"
#include "Rock.h"

Rock::Rock()
{

}

Rock::~Rock()
{

}

bool Rock::Start()
{
	r_modelRender.Init("Assets/modelData/rock1.tkm");
	r_modelRender.SetScale({ 0.1f,0.1f,0.1f });

	r_modelRender.SetPosition(r_position);

	return true;
}

void Rock::Update()
{
	r_modelRender.Update();
}

void Rock::Render(RenderContext& rc)
{
	r_modelRender.Draw(rc);
}