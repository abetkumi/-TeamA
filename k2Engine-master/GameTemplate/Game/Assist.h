#pragma once

class Player;
class Enemy;
class GameCamera;
class Assist : public IGameObject
{
public:
	enum State {
		enAssist_None,
		enAssist_ON,
		enAssist_OFF
	};

	Assist();
	~Assist();
	void Update();
	void Distance();

	const bool Homing();

	Player* player;
	Enemy* enemy;
	GameCamera* gameCamera;

	Vector3 m_ePos;
	Vector3 m_peDisPos;
	
	float m_peDistane = 10000.0f;		//”»’è
	float m_peTemporary;	//ˆêŽž“I

	State state = enAssist_None;
};


