#pragma once
#include "sound/SoundSource.h"

class Player;
class GameCamera;
class BackGround;
class Item;
class Status;
class Boat;
class Enemy;
class Point;

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
	Point* point;
	SpriteRender spriteRender;
	LevelRender m_levelRender;
	Vector3 position;
	SoundSource* bgm;
};

