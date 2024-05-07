#pragma once

class Enemy;
class Player;
class Arrow : public IGameObject
{
public:
	enum EnArrow {
		enArrow_None,
		enArrow_Player,
		enArrow_Enemy
	};

public:
	Arrow() {};
	~Arrow() {};
	bool Start();
	void Update();
	void Rotation();
	void Move();
	void Render(RenderContext& rc);
	void Inpacttime();
	void Inpacthit();
	void deletebullet();


	void SetVelocity(const Vector3& velocity)
	{
		m_velocity = velocity;
	}
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	void Setrotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	void SetEnArrow(const EnArrow enArrow)
	{
		m_enArrow = enArrow;
	}


	float bullettime = 1.5f;
	float m_deleteTimer = 0.0f;
	bool m_isDelete = false;
	const float deletetimer = 1.0f;

	ModelRender m_modelRender;
	CollisionObject* m_collisionObject;

	Quaternion m_rotation;
	Vector3 m_position;
	Vector3 m_1stPosition;
	Vector3 m_forward = Vector3::AxisZ;
	Vector3 m_velocity;
	Vector3	m_scale = Vector3::One;

	Player* player;
	Enemy* enemy;

	EnArrow m_enArrow = enArrow_None;
};

