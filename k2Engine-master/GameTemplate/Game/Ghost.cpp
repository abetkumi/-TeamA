#include "stdafx.h"
#include "Ghost.h"
#include "Game.h"

#include "collision/CollisionObject.h"

Ghost::Ghost()
{

}

Ghost::~Ghost()
{

}


bool Ghost::Start()
{
	m_charaCon.Init(10.0f, 10.0f, m_position);


	game = FindGO<Game>("game");

	return true;

}

void Ghost::Update()
{
	Move();
	Rotation();


}

void Ghost::Move()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//‚±‚±‚©‚ç3ƒ‰ƒCƒ“‚ÌˆÚ“®Ž®
	game->m_pointPositionG = game->path00_pointList[m_point];
	game->m_nextPositionG = game->path00_pointList[m_point + 1];
	game->m_pointPosition1G = game->path01_pointList[m_point];
	game->m_nextPosition1G = game->path01_pointList[m_point + 1];
	game->m_pointPosition2G = game->path02_pointList[m_point];
	game->m_nextPosition2G = game->path02_pointList[m_point + 1];

	//ì‚Ì3ƒ‰ƒCƒ“ŠÔ‚ðˆÚ“®‚·‚é‚½‚ß‚ÌŒvŽZ
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();

	switch (m_moveState) {
	case MoveState_Normal:

		if (stickL.x <= -0.8f && m_lag == 0)
		{
			m_moveState = MoveState_Left;
		}
		else if (stickL.x >= 0.8f && m_lag == 0)
		{
			m_moveState = MoveState_Right;
		}

		break;
	case MoveState_Left:

		m_moveFlag--;
		m_lag++;
		m_moveState = MoveState_Normal;
		break;
	case MoveState_Right:

		m_moveFlag++;
		m_lag++;
		m_moveState = MoveState_Normal;
		break;
	}

	if (m_lag >= 1)
	{
		m_lag++;
		if (m_lag == 10)
		{

			m_lag = 0;
		}
	}



	if (m_moveFlag < 0)
	{
		m_moveFlag = 0;
	}
	if (m_moveFlag > 2)
	{
		m_moveFlag = 2;
	}

	if (m_moveFlag == 0)
	{
		Vector3 m_moveLineV0 = m_position - game->m_pointPositionG;
		Vector3 m_moveLineV1 = game->m_nextPositionG - game->m_pointPositionG;
		m_moveLineV1.Normalize();
		float V2 = m_moveLineV0.x * m_moveLineV1.x +
			m_moveLineV0.y * m_moveLineV1.y +
			m_moveLineV0.z * m_moveLineV1.z;
		Vector3 m_moveLineV3 = m_moveLineV1 * V2;

		Vector3 m_moveLine = m_moveLineV0 - m_moveLineV3;

		m_moveSpeed.x += m_moveLine.x * 10.0f;
		diff = game->m_pointPositionG - m_position;

	}

	if (m_moveFlag == 1)
	{
		Vector3 m_moveLineV0 = m_position - game->m_pointPosition1G;
		Vector3 m_moveLineV1 = game->m_nextPosition1G - game->m_pointPosition1G;
		m_moveLineV1.Normalize();
		float V2 = m_moveLineV0.x * m_moveLineV1.x +
			m_moveLineV0.y * m_moveLineV1.y +
			m_moveLineV0.z * m_moveLineV1.z;
		Vector3 m_moveLineV3 = m_moveLineV1 * V2;

		Vector3 m_moveLine = m_moveLineV0 - m_moveLineV3;

		m_moveSpeed.x += m_moveLine.x * 10.0f;

		diff = game->m_pointPosition1G - m_position;
	}

	if (m_moveFlag == 2)
	{
		Vector3 m_moveLineV0 = m_position - game->m_pointPosition2G;
		Vector3 m_moveLineV1 = game->m_nextPosition2G - game->m_pointPosition2G;
		m_moveLineV1.Normalize();
		float V2 = m_moveLineV0.x * m_moveLineV1.x +
			m_moveLineV0.y * m_moveLineV1.y +
			m_moveLineV0.z * m_moveLineV1.z;
		Vector3 m_moveLineV3 = m_moveLineV1 * V2;

		Vector3 m_moveLine = m_moveLineV0 - m_moveLineV3;

		m_moveSpeed.x += m_moveLine.x * 10.0f;

		diff = game->m_pointPosition2G - m_position;

	}

	float disToPlayer = diff.Length();
	if (disToPlayer <= 200.0f)
	{
		m_point++;
	}


	diff.Normalize();

	static bool hoge = false;

	if (hoge) {
		m_moveSpeed = diff * 0.0f;
	}
	else {
		m_moveSpeed = diff * 300.0f;
	}

	m_position = m_charaCon.Execute(m_moveSpeed, 1.0f / 20.0f);

}

void Ghost::Rotation()
{
	//m_rotation.SetRotationYFromDirectionXZ(gameCamera->m_toCameraPos);

}

void Ghost::Render(RenderContext& rc)
{

}