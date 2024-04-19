#pragma once
#include "sound/SoundSource.h"

class Player;
class GameCamera;
class BackGround;
class Item;
class Status;
class Boat;
class Enemy;
class Ship_Gauge;
class Boss;

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
	Enemy* enemy;
	Boss* boss;
	Ship_Gauge* ship_Gauge;
	SpriteRender m_spriteRender;
	LevelRender m_levelRender;
	Vector3 position;
};

