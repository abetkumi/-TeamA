#pragma once

class  Player;
class Boat : public IGameObject
{
public:
	Boat();
	~Boat();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void ShipMove();

	ModelRender m_modelRender;
	SpriteRender m_spriteRender;
	PhysicsStaticObject m_physicsStaticObject;

	Vector3 m_position;
	Vector3 m_scale;
	Vector3 m_shipGauge;
	Vector3 m_shipposition;
	Player* player;

	int HP = 1;
};

