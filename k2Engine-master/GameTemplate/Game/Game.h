#pragma once
#include "sound/SoundSource.h"

class Player;
class GameCamera;
class BackGround;
class Item;
class Status;
class Boat;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();

	Player* player;
	GameCamera* gameCamera;
	BackGround* backGround;
	Item* item;
	Status* status;
	Boat* boat;
};

