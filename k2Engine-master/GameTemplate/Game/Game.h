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
	void Render(RenderContext& rc);

	Player* player;
	GameCamera* gameCamera;
	BackGround* backGround;
	Item* item;
	Status* status;
	Boat* boat;
	SpriteRender spriteRender;
	Vector3 position;
};

