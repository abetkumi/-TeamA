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
	
	Vector3 m_position;
	Vector3 m_scale;
	Vector3 m_shipposition;
	Vector3 m_direction;	 // ‘DŽñ‚ÌŒü‚«
	Player* player;
	Game* game;

	int HP = 1;
	int m_shipPoint = 0;
	float m_shiptimer = 0.5f;
	float m_shipswitch = 1.0f;
};

