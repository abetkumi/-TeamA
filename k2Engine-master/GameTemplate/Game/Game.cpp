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
	player = NewGO<Player>(0, "player");
	gameCamera = NewGO<GameCamera>(0, "gamecamera");
	backGround = NewGO<BackGround>(0, "backGround");
	boat = NewGO<Boat>(0, "boat");

	Enemy* enemy = NewGO<Enemy>(0, "enemy");
	enemy->m_position = { 100.0f,0.0f,-200.0f };

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