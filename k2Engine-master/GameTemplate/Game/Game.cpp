#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Item.h"
#include "Status.h"

Game::Game()
{
	player = NewGO<Player>(0, "player");
	gameCamera = NewGO<GameCamera>(0, "gamecamera");
	backGround = NewGO<BackGround>(0, "backGround");
	status = FindGO<Status>("status");


	
}

Game::~Game()
{
	DeleteGO(player);
	DeleteGO(gameCamera);

}

void Game::Update()
{
	
}