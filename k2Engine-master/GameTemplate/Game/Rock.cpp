#include "stdafx.h"
#include "Rock.h"

#include "collision/CollisionObject.h"

namespace
{
	const Vector3 rock1 = { 0.0f,0.0f,0.0f };
}

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
	r_modelRender.SetRotation(r_rotation);

	r_modelRender.Update();

	r_physicsStaticObject.CreateFromModel(r_modelRender.GetModel(), r_modelRender.GetModel().GetWorldMatrix());

	

	return true;
}

void Rock::Colision()
{

}

void Rock::Update()
{
	r_modelRender.Update();
}

void Rock::Render(RenderContext& rc)
{
	r_modelRender.Draw(rc);
}