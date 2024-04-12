#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy()
{
	m_modelRender.Init("Assets/modelData/enemy.tkm");
	player = FindGO<Player>("player");
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	Rotation();

	m_modelRender.Update();
}

void Enemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void Enemy::Rotation()
{
	Vector3 v = player -> m_position - m_position;
	v.Normalize();
	float distToPlayer = v.Length();
	if (distToPlayer < 30)
	{
		m_moveSpeed = v * 100.0f;
		//m_position += m_moveSpeed;
		m_modelRender.SetPosition(m_position);
	}

	m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	m_modelRender.SetRotation(m_rotation);
}
