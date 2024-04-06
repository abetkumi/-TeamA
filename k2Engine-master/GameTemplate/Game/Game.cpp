#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Item.h"

Game::Game()
{
	player = NewGO<Player>(0, "player");
	gameCamera = NewGO<GameCamera>(0, "gamecamera");

	if (item->Count >= 10) {
		item = NewGO<Item>(0, "item");
	}
}

Game::~Game()
{
	DeleteGO(player);
	DeleteGO(gameCamera);

}

void Game::Update()
{

}