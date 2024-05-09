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
	const bool Decision();

	Player* player;
	Enemy* enemy;
	GameCamera* gameCamera;
};

