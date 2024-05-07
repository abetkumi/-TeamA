#pragma once

class  Player;
class Game;

class Boat : public IGameObject
{
public:
	Boat();
	~Boat();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();
	void ShipMove();

	ModelRender m_modelRender;
	Quaternion m_rotation;
	SpriteRender m_spriteRender;
	PhysicsStaticObject m_physicsStaticObject;

	Vector3 m_position;
	Vector3 m_scale;
	Vector3 m_shipGauge;
	Vector3 m_shipposition;
	Player* player;
	Game* game;

	int HP = 1;
};

