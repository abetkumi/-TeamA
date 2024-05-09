#pragma once

class Player;
class Enemy;
class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	void Decision();

	Player* m_player;
	Enemy* enemy;

	Vector3 m_toCameraPos;
	Vector3 m_toPosDir;

	double m_Dec;
};