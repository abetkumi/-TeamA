#include "stdafx.h"
#include "Rock.h"
#include "Player.h"
#include "Game.h"
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
	DeleteGO(r_collisionObject);
}

bool Rock::Start()
{
	r_modelRender.Init("Assets/modelData/rock1.tkm");
	r_modelRender.SetScale({ 0.1f,0.1f,0.1f });
	r_modelRender.SetPosition(r_position);
	r_modelRender.Update();

	Vector3 hoge = { 0.0f,0.0f,0.0f };

	r_collisionObject = NewGO<CollisionObject>(3);
	r_collisionObject->CreateMesh(hoge, r_rot, r_modelRender.GetModel(), r_modelRender.GetModel().GetWorldMatrix());
	r_collisionObject->SetName("r_rock");
	r_collisionObject->SetIsEnableAutoDelete(false);
	r_collisionObject->Update();
	//r_physicsStaticObject.CreateFromModel(r_modelRender.GetModel(), r_modelRender.GetModel().GetWorldMatrix());

	player = FindGO<Player>("player");
	game = FindGO<Game>("game");

	return true;
}

void Rock::Colision()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("r_rock");

	for (auto collision : collisions) {
		if (collision->IsHit(player->m_charaCon))
		{
			player->m_arrowState = 3;
			player->HP -= 5;
			player->m_position = game->m_pointPosition;
			r_rockFlag = true;
		}
	}
	if (r_rockFlag == true)
	{
		DeleteGO(r_collisionObject);
		r_rockFlag = false;
	}
}

void Rock::Update()
{
	Colision();
	r_modelRender.Update();
}

void Rock::Render(RenderContext& rc)
{
	r_modelRender.Draw(rc);
}