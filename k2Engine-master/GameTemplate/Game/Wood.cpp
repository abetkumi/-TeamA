#include "stdafx.h"
#include "Wood.h"

Wood::Wood()
{

}

Wood::~Wood()
{

}

bool Wood::Start()
{
	w_modelRender.Init("Assets/modelData/wood.tkm");
	w_modelRender.SetPosition(w_position);
	w_modelRender.SetScale(w_scale);
	w_modelRender.Update();

	return true;
}

void Wood::Render(RenderContext& rc)
{
	w_modelRender.Draw(rc);
}