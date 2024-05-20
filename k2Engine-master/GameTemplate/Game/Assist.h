#pragma once

class Player;
class Enemy;
class GameCamera;
class Assist : public IGameObject
{
public:
	Assist();
	~Assist();
	void Update();
	void Homing();
	void Distance();
	const bool Decision();

	Player* player;
	Enemy* enemy;
	GameCamera* gameCamera;

	Vector3 m_ePos;
	Vector3 m_peDisPos;
	
	double m_peDistane;		//”»’è
	double m_peTemporary;	//ˆêŽž“I
};


