#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Arrow.h"

#include <time.h>

#define enemyserch 700.0f*700.0f

Enemy::Enemy()
{
	m_modelRender.Init("Assets/modelData/enemy.tkm");
	player = FindGO<Player>("player");

	arrowtimer = arrowtime;

	////�L�����N�^�[�R���g���[���[�̏������������Ȃ��ƃG���[�f�����̂Œ���
	//m_charaCon.Init(0.0f, 0.0f, Vector3::Zero);
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	Rotation();

	Arrow1();
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
	Vector3 diff = player->m_position - m_position;
	
if (diff.LengthSq() <= enemyserch)
	{
		m_moveSpeed = diff * 100.0f;
	}
	m_modelRender.SetPosition(m_position);
	m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	m_modelRender.SetRotation(m_rotation);
}

void Enemy::Arrow1()
{
	if (arrowtimer > 0)
	{
		arrowtimer -= g_gameTime->GetFrameDeltaTime();
		return;
	}

	arrow = NewGO<Arrow>(0, "arrow");
	arrow->m_position = (m_position);
	arrow->m_1stPosition = arrow->m_position;
	arrow->m_rotation = m_rotation;


	arrowtimer = arrowtime;
}