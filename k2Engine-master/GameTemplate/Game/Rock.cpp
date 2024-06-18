#include "stdafx.h"
#include "Rock.h"
#include "Player.h"
#include "Game.h"
#include "collision/CollisionObject.h"

#define kyori 500.0f * 500.0f

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
	r_modelRender.Update();

	Vector3 hoge = { 0.0f,0.0f,0.0f };

	r_physicsStaticObject.CreateFromModel(r_modelRender.GetModel(), r_modelRender.GetModel().GetWorldMatrix());

	player = FindGO<Player>("player");
	game = FindGO<Game>("game");

	return true;
}

void Rock::RockDamage()
{
	if (r_rockFlag == true)
	{
		r_damageLag += g_gameTime->GetFrameDeltaTime();
		if (r_damageLag > 2.0f)
		{
			r_rockFlag = false;
		}
		return;
	}
	else
	{
		r_rockFlag = false;
	}

	Vector3 diff = r_position - player->m_position;
	float distToPlayer = diff.Length();
	if (distToPlayer < 400)
	{
		r_rockFlag = true;
		player->HP -= 5;
		player->m_arrowState = 3;
		player->m_position = game->path01_pointList[player->m_point - 2];
		player->m_moveFlag = 1;
		player->m_modelRender.SetPosition(player->m_position);
		player->m_charaCon.SetPosition(player->m_position);
		player->m_modelRender.Update();
	}
}

void Rock::Update()
{
	RockDamage();
	r_modelRender.Update();
}

void Rock::Render(RenderContext& rc)
{
	r_modelRender.Draw(rc);
}

//const bool Rock::rRock()
//{
//Vector3 diff = player->m_position - r_position;
//	if (diff.LengthSq() >= kyori)
//	{
//		return true;
//	}
//	return false;
//}
