#pragma once
#include "sound/SoundSource.h"

class Player;
class GameCamera;
class BackGround;
class Item;
class Status;
class Boat;
class GameOver;


class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Render(RenderContext& rc);

	Player* player;
	GameCamera* gameCamera;
	BackGround* backGround;
	Item* item;
	Status* status;
	Boat* boat;
	GameOver* gameOver;

	SpriteRender spriteRender;
	Vector3 position;

	int p_HP = 100;
};

