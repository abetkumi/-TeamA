#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Item.h"
#include "Status.h"
#include "Boat.h"
#include "Enemy.h"

Game::Game()
{



	m_levelRender.Init("Assets/Level/stage1.tkl", [&](LevelObjectData& objData)
		{
			if (objData.EqualObjectName(L"unityChan") == true)
			{
				player = NewGO<Player>(0, "player");

				player->m_position=objData.position;
				
				player->m_rotation=objData.rotation;

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
				Enemy* enemy = NewGO<Enemy>(0, "enemy");

				enemy->m_position = objData.position;

				return true;

			}
			return true;
		});

	gameCamera = NewGO<GameCamera>(0, "gamecamera");
	status = FindGO<Status>("status");

	spriteRender.Init("Assets/sprite/ステージのゲージ.dds", 512.0f, 512.0f);
}

Game::~Game()
{
	DeleteGO(player);
	DeleteGO(gameCamera);
	DeleteGO(backGround);
	DeleteGO(boat);

	DeleteGO(status);
}

void Game::Update()
{
	spriteRender.SetPosition(position);
	spriteRender.Update();
}

void Game::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}