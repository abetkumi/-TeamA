#pragma once

class Enemy;
class Player;
class GameCamera;
class Assist;
class Gravity;
class Arrow : public IGameObject
{
public:
	enum EnArrow {
		enArrow_None,
		enArrow_Player,
		enArrow_Enemy,
		enArrow_Goblin,
		enArrow_Skeleton,
		enArrow_Boss
	};

public:
	Arrow();
	~Arrow();
	bool Start();
	void Update();
	void Rotation();
	void Move();
	void Render(RenderContext& rc);
	void Inpacttime();
	void Inpacthit();
	void deletebullet();
	void Dec();

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
	float m_deleteTimer,m_xBulletTime = 0.0f;
	float m_peLen;
	float m_velocityLen;

	bool m_isDelete = false;
	const float deletetimer = 1.0f;
	int m_Damage;

	ModelRender m_modelRender;
	CollisionObject* m_collisionObject;

	Quaternion m_rotation;
	Vector3 m_position;
	Vector3 m_1stPosition;
	Vector3 m_ePos;
	Vector3 m_forward = Vector3::AxisZ;
	Vector3 m_velocity;
	Vector3 m_velocity2;
	Vector3	m_scale = Vector3::One;
	Vector3 m_CameraPos;

	Player* player;
	Enemy* enemy;
	GameCamera* gameCamera;
	Assist* assist;
	Gravity* gravity;

	EnArrow m_enArrow = enArrow_None;

	Vector3 test;
	float jo;
	SoundSource* ArrowSE;
};

