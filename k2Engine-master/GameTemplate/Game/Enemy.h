#pragma once

class Player;
class Arrow;
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	void Update();
	void Render(RenderContext& rc);
	void Rotation();
	void Arrow1();
	
	Vector3 m_position;
	Vector3 m_scale = Vector3::One;
	Vector3 m_moveSpeed;

	ModelRender m_modelRender;

	CharacterController m_charaCon;

	Quaternion m_rotation;

	Player* player;
	Arrow* arrow;
	
	float arrowtimer = 0.0f;
	float arrowtime = 3.0f;
};

