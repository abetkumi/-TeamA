#pragma once

class Player;
class Arrow;
class Enemy3 : public IGameObject
{
public:
	Enemy3();
	~Enemy3();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();
	void Attack();
	void Calculation();
	
	bool Start();

	const bool Serch();
	const bool MoveSerch();

	void Collision();

	Vector3 m_position;
	Vector3 m_attackPos;
	Vector3 m_scale = Vector3::One;
	Vector3 m_moveSpeed;
	Vector3	m_forward = Vector3::AxisZ;
	Vector3 m_cNPos;

	Quaternion m_rotation;

	ModelRender m_modelRender;

	//CharacterController m_charaCon;

	Player* player;
	Arrow* arrow;
	CollisionObject* m_collisionObject;

	float arrowtimer = 0.0f;
	float arrowtime = 3.0f;

	int HP = 1;
	int a = 0;

	//Move()“à‚Ì‚Ý
	float x1,x2 = 0.0f;
	int y = 0;
	
	float Xt = 0.8f;
};



