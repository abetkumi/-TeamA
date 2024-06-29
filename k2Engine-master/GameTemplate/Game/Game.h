#pragma once
#include "sound/SoundSource.h"

class Player;
class GameCamera;
class GameClear;
class GameOver;
class BackGround;
class Sky;
class Item;
class Status;
class Boat;
class Enemy;
class Enemy2;
class Enemy3;
class Ship_Gauge;
class Boss;
class Assist;
class Arrow;
class Rock;
class Wood;
class Ghost;

class Game : public IGameObject
{
public:
	bool Start();
	Game();
	~Game();
	void Update();
	void Score();
	void Render(RenderContext& rc);
	void SpriteFlag();

	Player* player;
	GameCamera* gameCamera;
	GameOver* gameOver;
	GameClear* gameClear;
	BackGround* backGround;
	Sky* sky;
	Item* item;
	Status* status;
	Boat* boat;
	Enemy* enemy;
	Enemy2* enemy2;
	Enemy3* enemy3;
	Boss* boss;
	Assist* assist;
	Arrow* arrow;
	Rock* rock;
	Wood* wood;
	Ghost* ghost;
	Ship_Gauge* ship_Gauge;


	SpriteRender m_spriteRender;
	SpriteRender m_spriteRender_L;
	SpriteRender m_spriteRender_R;
	SpriteRender m_spriteRender_LB;
	SpriteRender m_spriteRender_UI;
	SpriteRender m_spriteRender_B;
	SpriteRender m_spriteRender_Re;
	SpriteRender m_spriteRender_Go;
	LevelRender m_levelRender;
	SoundSource* m_gameBGM;

	Vector3 position;
	float spritetimer = 0.5f;
	float spritetime = 0.0f;
	float m_shade = 1.0f;
	int m_spriteStatus = 1;

	std::vector<Vector3> path00_pointList;
	std::vector<Vector3> path01_pointList;
	std::vector<Vector3> path02_pointList;

	Vector3 m_pointPosition;
	Vector3 m_nextPosition;
	Vector3 m_pointPosition1;
	Vector3 m_nextPosition1;
	Vector3 m_pointPosition2;
	Vector3 m_nextPosition2;


	Vector3 m_pointPositionG;
	Vector3 m_nextPositionG;
	Vector3 m_pointPosition1G;
	Vector3 m_nextPosition1G;
	Vector3 m_pointPosition2G;
	Vector3 m_nextPosition2G;
};

