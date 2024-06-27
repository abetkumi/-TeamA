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
#include "Ghost.h"
#include "sound/SoundSource.h" 

Game::Game()
{

}

Game::~Game()
{
	/*DeleteGO(assist);*/
	QueryGOs<Item>("item", [&](Item* item)
		{
			DeleteGO(item);
			return true;
		});
	DeleteGO(player);
	DeleteGO(ghost);
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
	//DeleteGO(boss);
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
		//else if (objData.EqualObjectName(L"sky") == true)
		//{
		//	sky = NewGO<Sky>(0, "sky");

		//	sky->s_position = objData.position;

		//	return true;
		//}
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
		//else if (objData.EqualObjectName(L"BOSS_fake") == true)
		//{
		//	boss = NewGO<Boss>(0, "Boss_fake");
		//	boss->m_position = objData.position;
		//	boss->m_scale = objData.scale;
		//	return true;
		//}
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
	//ghost = NewGO<Ghost>(0, "ghost");
	//assist = NewGO<Assist>(0,"assist");

	m_spriteRender.Init("Assets/sprite/stage_gauge.dds", 512.0f, 512.0f);
	m_spriteRender_L.Init("Assets/sprite/Game_Move.dds", 1920.0f, 1080.0f);
	m_spriteRender_R.Init("Assets/sprite/Game_Lock.dds", 1920.0f, 1080.0f);
	m_spriteRender_LB.Init("Assets/sprite/Game_Arrow.dds", 1920.0f, 1080.0f);
	m_spriteRender_UI.Init("Assets/sprite/UI_name.dds", 1920.0f, 1080.0f);
	m_spriteRender_B.Init("Assets/sprite/Game_BSkip.dds", 1920.0f, 1080.0f);
	m_spriteRender_L.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_shade));
	m_spriteRender_R.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_shade));
	m_spriteRender_LB.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_shade));
	m_spriteRender_UI.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_shade));
	g_soundEngine->ResistWaveFileBank(3, "Assets/BGM・SE/GameBGM.wav");
	m_gameBGM = NewGO<SoundSource>(3);
	m_gameBGM->Init(3);
	m_gameBGM->Play(true);

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
			DeleteGO(m_gameBGM);
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
	if (player->m_point == 200)
	{
		DeleteGO(m_gameBGM);
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
		player->m_point = 11;
		//DeleteGO(this);
	}
	SpriteFlag();
}

void Game::SpriteFlag()
{
	m_shade += g_gameTime->GetFrameDeltaTime() * spritetimer;
	if (m_shade >= 0.7f)
	{
		if (m_shade >= 1.0f)
		{
			m_shade = 1.0f;
		}
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			spritetimer *= -1.0f;
		}
	}
	if (m_shade <= 0.2f)
	{
		spritetimer *= -1.0f;
		m_spriteStatus++;
	}
	if (m_spriteStatus >= 5||g_pad[0]->IsTrigger(enButtonB))
	{
		m_spriteStatus = 5;
	}
	m_spriteRender_L.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_shade));
	m_spriteRender_L.Update();
	m_spriteRender_R.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_shade));
	m_spriteRender_R.Update();
	m_spriteRender_LB.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_shade));
	m_spriteRender_LB.Update();
	m_spriteRender_UI.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_shade));
	m_spriteRender_UI.Update();
}

void Game::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	if (m_spriteStatus == 1)
	{
		m_spriteRender_L.Draw(rc);
		m_spriteRender_B.Draw(rc);
	}
	if (m_spriteStatus == 2)
	{
		m_spriteRender_R.Draw(rc);
		m_spriteRender_B.Draw(rc);
	}
	if (m_spriteStatus == 3)
	{
		m_spriteRender_LB.Draw(rc);
		m_spriteRender_B.Draw(rc);
	}
	if (m_spriteStatus == 4)
	{
		m_spriteRender_UI.Draw(rc);
		m_spriteRender_B.Draw(rc);
	}
}