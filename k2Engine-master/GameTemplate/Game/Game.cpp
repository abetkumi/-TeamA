#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "GameOver.h"
#include "GameClear.h"
#include "BackGround.h"
#include "Sky.h"
#include "Item.h"
#include "Status.h"
#include "Boat.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Boss.h"
#include "Assist.h"
#include "Arrow.h"
#include "Rock.h"
#include "Wood.h"


Game::Game()
{

}

Game::~Game()
{
	/*DeleteGO(assist);*/
	DeleteGO(player);
	DeleteGO(gameCamera);
	DeleteGO(backGround);
	DeleteGO(boat);
	
	QueryGOs<Enemy>("enemy", [&](Enemy* enemy)
		{
			DeleteGO(enemy);
			return true;
		});
	QueryGOs<Enemy2>("enemy2", [&](Enemy2* enemy2)
		{
			DeleteGO(enemy2);
			return true;
		});
	QueryGOs<Enemy3>("enemy3", [&](Enemy3* enemy3)
		{
			DeleteGO(enemy3);
			return true;
		});
	DeleteGO(status);
	DeleteGO(boss);
	QueryGOs<Rock>("rock", [&](Rock* rock)
		{
			DeleteGO(rock);
			return true;
		});
}

bool Game::Start()
{

	m_levelRender.Init("Assets/Level/stage_trueA.tkl", [&](LevelObjectData& objData)
	{
		if (objData.EqualObjectName(L"a_player") == true)
		{
			player = NewGO<Player>(0, "player");

			player->m_position = objData.position;

			player->m_rotation = objData.rotation;

			return true;
		}
		else if (objData.EqualObjectName(L"level_true") == true)
		{
			backGround = NewGO<BackGround>(0, "backGround");

			backGround->m_position = objData.position;

			return true;
		}
		else if (objData.EqualObjectName(L"sky") == true)
		{
			sky = NewGO<Sky>(0, "sky");

			sky->s_position = objData.position;

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
		else if (objData.ForwardMatchName(L"goblin") == true)
		{
			enemy = NewGO<Enemy>(0, "enemy");

			enemy->m_position = objData.position;

			return true;
		}
		else if (objData.ForwardMatchName(L"skelton") == true)
		{
			enemy2 = NewGO<Enemy2>(0, "enemy2");

			enemy2->m_position = objData.position;

			return true;
		}
		else if (objData.ForwardMatchName(L"bat") == true)
		{
			enemy3 = NewGO<Enemy3>(0, "enemy3");

			enemy3->m_position = objData.position;

			return true;
		}
		else if (objData.EqualObjectName(L"BOSS_fake") == true)
		{
			boss = NewGO<Boss>(0, "Boss_fake");
			boss->m_position = objData.position;
			boss->m_scale = objData.scale;
			return true;
		}
		else if (objData.ForwardMatchName(L"00_Path_Point_") == true) {
			// 1 line
			path00_pointList.push_back(objData.position);
			return true;
		}
		else if (objData.ForwardMatchName(L"01_Path_Point_") == true) {
			// 2 line
			path01_pointList.push_back(objData.position);
			return true;
		}
		else if (objData.ForwardMatchName(L"02_Path_Point_") == true) {
			// 3 line
			path02_pointList.push_back(objData.position);
			return true;
		}
		else if(objData.ForwardMatchName(L"rock") == true) {
			//岩
			rock = NewGO<Rock>(0, "rock");
			rock->r_position = objData.position;
			rock->r_rotation = objData.rotation;
			return true;
		}
		else if (objData.ForwardMatchName(L"wood") == true)
		{
			wood = NewGO<Wood>(0, "wood");
			wood->w_position = objData.position;
			wood->w_scale = objData.scale;
			return true;
		}
		return true;
	});

	gameCamera = NewGO<GameCamera>(0, "gameCamera");
	status = FindGO<Status>("status");
	//assist = NewGO<Assist>(0,"assist");

	m_spriteRender.Init("Assets/sprite/stage_gauge.dds", 512.0f, 512.0f);

	return true;
}
void Game::Update()
{
	position.x = -650.0f;
	position.y = 500.0f;
	m_spriteRender.SetPosition(position);
	m_spriteRender.Update();

	//ゲームオーバー判定
	if (player->HP <= 0 || boat->HP <= 0)
	{
		player->m_arrowState = 4;
		if (player->m_arrowLag == 100)
		{
			gameOver = NewGO<GameOver>(0, "gameOver");
			QueryGOs<Enemy>("enemy", [&](Enemy* enemy)
				{
					DeleteGO(enemy);
					return true;
				});
			QueryGOs<Enemy2>("enemy2", [&](Enemy2* enemy2)
				{
					DeleteGO(enemy2);
					return true;
				});
			QueryGOs<Enemy3>("enemy3", [&](Enemy3* enemy3)
				{
					DeleteGO(enemy3);
					return true;
				});
			//DeleteGO(this);
		}
	}
	//クリアのポイント判定
	if (player->m_point == 100)
	{
		gameClear = NewGO<GameClear>(0, "gameClear");
		QueryGOs<Enemy>("enemy", [&](Enemy* enemy)
			{
				DeleteGO(enemy);
				return true;
			});
		QueryGOs<Enemy2>("enemy2", [&](Enemy2* enemy2)
			{
				DeleteGO(enemy2);
				return true;
			});
		QueryGOs<Enemy3>("enemy3", [&](Enemy3* enemy3)
			{
				DeleteGO(enemy3);
				return true;
			});
		player->m_arrowState=6;
		//DeleteGO(this);
	}
}

void Game::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}