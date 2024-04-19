#pragma once

class Enemy;
class Player;
class Amo : public IGameObject
{
public:
	Amo(){};
	~Amo(){};
	bool Start();
	void Update();
	void Rotation();
	void Movebullet();
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


	float bullettime = 1.5f;
	float m_deleteTimer = 0.0f;
	bool m_isDelete = false;
	const float deletetimer = 1.0f;

	ModelRender m_modelRender;
	CollisionObject* m_collisionObject;
	Player* player;
	Enemy* enemy;

	Quaternion m_rotation;
	Vector3 m_position;
	Vector3 m_forward = Vector3::AxisZ;
	Vector3 m_velocity;
	Vector3	m_scale = Vector3::One;
};

