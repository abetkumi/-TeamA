#include "stdafx.h"
#include "Player.h"
#include "Arrow.h"
#include "Game.h"

Player::Player()
{
	m_modelRender.Init("Assets/modelData/unityChan.tkm");
	m_charaCon.Init(25.0f, 75.0f, m_position);

	HP = 100;
	game = FindGO<Game>("game");

}

Player::~Player()
{

}

void Player::Update()
{
	Move();
	Rotation();

	m_modelRender.Update();

	if (g_pad[0]->IsTrigger(enButtonB))
	{
		arrow = NewGO<Arrow>(0, "arrow");
		arrow->m_position = (m_position);
		arrow->m_1stPosition = arrow->m_position;
		arrow->m_rotation = m_rotation;

	}
}

void Player::Move()
{
	//m_moveSpeed.x = 0.0f;
	//m_moveSpeed.z = 0.0f;

	////通常の移動モーション
	//Vector3 stickL;
	//stickL.x = g_pad[0]->GetLStickXF();
	//stickL.y = g_pad[0]->GetLStickYF();

	//Vector3 forward = g_camera3D->GetForward();
	//Vector3 right = g_camera3D->GetRight();

	//forward.y = 0.0f;
	//right.y = 0.0f;

	//right *= stickL.x * 120.0f;
	//forward *= stickL.y * 120.0f;

	//m_moveSpeed += right + forward;

	game->m_pointPosition = game->path00_pointList[point];
	Vector3 diff = game->m_pointPosition - m_position;
	
	float disToPlayer = diff.Length();
	if (disToPlayer <= 10.0f)
	{
		point++;
	}
	diff.Normalize();
	

	m_moveSpeed = diff * 10.0f;
	//if (m_charaCon.IsOnGround())
	//{
	//	m_moveSpeed.y = 0.0f;
	//}
	//else
	//{
	//	m_moveSpeed.y -= 10.0f;
	//}
	
	
	//ダッシュとジャンプ
//if (g_pad[0]->IsPress(enButtonA))
//	{
//		m_moveSpeed.y = 300.0f;
//	}
//	if (g_pad[0]->IsPress(enButtonX))
//	{
//		m_moveSpeed = (right + forward) * 7.5;
//	}
	//強制ゲームオーバーコマンド
	if (g_pad[0]->IsPress(enButtonY))
	{
		HP -= 100;
	}

	m_position = m_charaCon.Execute(m_moveSpeed, 1.0f / 20.0f);//大まかな移動速度
	//m_position = m_moveSpeed;
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		m_modelRender.SetRotation(m_rotation);
	}
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}