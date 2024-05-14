#pragma once

class Player;
class Arrow;
class Enemy2 : public IGameObject
{
public:
	Enemy2();
	~Enemy2();
	void Update();
	void Render(RenderContext& rc);
	void Rotation();
	void Attack();
	bool Start();

	const bool Serch();
	const bool AttackSerch();

	void Collision();

	Vector3 m_position;
	Vector3 m_scale = Vector3::One;
	Vector3 m_moveSpeed;
	Vector3	m_forward = Vector3::AxisZ;

	Quaternion m_rotation;

	ModelRender m_modelRender;

	//CharacterController m_charaCon;

	Player* player;
	Arrow* arrow;
	CollisionObject* m_collisionObject;

	float arrowtimer = 0.0f;
	float arrowtime = 3.0f;

	int HP = 1;
};



