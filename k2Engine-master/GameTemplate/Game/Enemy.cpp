#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy()
{
	m_modelRender.Init("Assets/modelData/unityChan.tkm");
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
	m_modelRender.SetPosition(m_position);
}
