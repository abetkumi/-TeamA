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
	const bool Traget();
	const bool Srech();
};

