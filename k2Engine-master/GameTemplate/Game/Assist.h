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
	const bool Decision() const;

	Player* player;
	Enemy* enemy;
	GameCamera* gameCamera;

	Vector3 m_ePos;
	Vector3 m_peDisPos;
	
	double m_peDistane;
	double m_peTemporary;

};

