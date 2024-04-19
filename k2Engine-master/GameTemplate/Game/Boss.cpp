#include "stdafx.h"
#include "Boss.h"
#include "Player.h"

Boss::Boss()
{
	m_modelRender.Init("Assets/modelData/boss/BOSS_fake.tkm");
	player = FindGO<Player>("player");
}

Boss::~Boss()
{

}

void Boss::Update()
{
	Rotation();

	m_modelRender.Update();
}

void Boss::Rotation()
{
	Vector3 v = player->m_position - m_position;
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

void Boss::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}