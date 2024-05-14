#pragma once
#include "sound/SoundSource.h"

class Player;
class GameCamera;
class GameClear;
class GameOver;
class BackGround;
class Item;
class Status;
class Boat;
class Enemy;
class Enemy2;
class Enemy3;
class Ship_Gauge;
class Boss;
class Assist;
class Rock;

class Game : public IGameObject
{
public:
	bool Start();
	Game();
	~Game();
	void Update();
	void Render(RenderContext& rc);

	Player* player;
	GameCamera* gameCamera;
	GameOver* gameOver;
	GameClear* gameClear;
	BackGround* backGround;
	Item* item;
	Status* status;
	Boat* boat;
	Enemy* enemy;
	Enemy2* enemy2;
	Enemy3* enemy3;
	Boss* boss;
	Assist* assist;
	Rock* rock;

	Ship_Gauge* ship_Gauge;
	SpriteRender m_spriteRender;
	LevelRender m_levelRender;
	Vector3 position;
	std::vector<Vector3> path00_pointList;
	std::vector<Vector3> path01_pointList;
	std::vector<Vector3> path02_pointList;
	Vector3 m_pointPosition;
	Vector3 m_nextPosition;
	Vector3 m_pointPosition1;
	Vector3 m_nextPosition1;
	Vector3 m_pointPosition2;
	Vector3 m_nextPosition2;
};

