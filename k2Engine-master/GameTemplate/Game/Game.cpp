#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "GameOver.h"
#include "BackGround.h"
#include "Item.h"
#include "Status.h"
#include "Boat.h"
#include "Enemy.h"
#include "Boss.h"


Game::Game()
{

	m_levelRender.Init("Assets/Level/stage2_9.tkl", [&](LevelObjectData& objData)
		{
			/*if (objData.EqualObjectName(L"unityChan") == true)
			{
				player = NewGO<Player>(0, "player");

				player->m_position=objData.position;
				
				player->m_rotation=objData.rotation;

				return true;
			}*/

			if (objData.EqualObjectName(L"Archer") == true)
			{
				player = NewGO<Player>(0, "player");

				player->m_position = objData.position;

				player->m_rotation = objData.rotation;

				return true;
			}

			else if (objData.EqualObjectName(L"river") == true)
			{
				backGround = NewGO<BackGround>(0, "backGround");

				backGround->m_position = objData.position;

				return true;
			}
			else if (objData.EqualObjectName(L"boat") == true)
			{
				boat = NewGO<Boat>(0, "boat");

				boat->m_position = objData.position;

				//boat->m_rotation = objData.rotation;

				//boat->m_scale = objData.scale;

				return true;
			}

			else if (objData.EqualObjectName(L"enemy") == true)
			{
				enemy = NewGO<Enemy>(0, "enemy");

				enemy->m_position = objData.position;

				return true;

			}
			else if (objData.EqualObjectName(L"BOSS_fake") == true)
			{
				boss = NewGO<Boss>(0, "Boss_fake");
				boss->m_position = objData.position;
				boss->m_scale = objData.scale;
				return true;
			}
			return true;
		});

	gameCamera = NewGO<GameCamera>(0, "gameCamera");
	status = FindGO<Status>("status");
	
	m_spriteRender.Init("Assets/sprite/stage_gauge.dds", 512.0f, 512.0f);
}

Game::~Game()
{
	DeleteGO(player);
	DeleteGO(gameCamera);
	DeleteGO(backGround);
	DeleteGO(boat);
	QueryGOs<Enemy>("enemy", [&](Enemy* enemy)
		{
			DeleteGO(enemy);
			return true;
		});
	DeleteGO(status);
	DeleteGO(boss);
	//QueryGOs<Point>("point", [&](Point* point) 
	//	{
	//		DeleteGO(point);
	//		return true;
	//	});
}

void Game::Update()
{
	position.x = -650.0f;
	position.y = 500.0f;
	m_spriteRender.SetPosition(position);
	m_spriteRender.Update();

	if (player->HP <= 0 || boat->HP <= 0)
	{
		gameOver = NewGO<GameOver>(0, "gameOver");
		DeleteGO(this);
	}
}

void Game::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}