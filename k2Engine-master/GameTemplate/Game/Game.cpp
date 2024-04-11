#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Item.h"
#include "Status.h"
#include "Boat.h"

Game::Game()
{
	player = NewGO<Player>(0, "player");
	gameCamera = NewGO<GameCamera>(0, "gamecamera");
	backGround = NewGO<BackGround>(0, "backGround");
	boat = NewGO<Boat>(0, "boat");

	status = FindGO<Status>("status");
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
	
}