#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Arrow.h"

Enemy::Enemy()
{
	m_modelRender.Init("Assets/modelData/goblin.tkm");
	player = FindGO<Player>("player");

	//キャラクターコントローラーの初期化処理しないとエラー吐かれるので注意
	m_charaCon.Init(0.0f, 0.0f, Vector3::Zero);
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	Rotation();

	/*if (g_pad[0]->IsTrigger(enButtonB))
	{
		arrow = NewGO<Arrow>(0, "arrow");
		arrow->m_position = (m_position);
		arrow->m_1stPosition = arrow->m_position;
		arrow->m_rotation = m_rotation;

	}*/

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