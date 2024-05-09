#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	enemy = FindGO<Enemy>("enemy");
	m_toCameraPos.Set(0.0f, 125.0f, -250.0f);
	m_player = FindGO<Player>("player");

	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(10000.0f);

	return true;
}

void GameCamera::Update()
{
	Vector3 target = m_player->m_position;
	target.y += 80.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 3.3f * x);//���x
	qRot.Apply(m_toCameraPos);

	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 3.3f * y);
	qRot.Apply(m_toCameraPos);

	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();

	if (toPosDir.y < -0.2f) {
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.9f) {
		m_toCameraPos = toCameraPosOld;
	}

	Vector3 pos = target + m_toCameraPos;

	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);
																																																																																																																																																																																																																																								
	Decision();

	g_camera3D->Update();
}

void GameCamera::Decision()
{
		Vector3 v = m_player->m_position - m_toCameraPos;
		v.Normalize();

		Vector3 ePos = enemy->m_position - m_toCameraPos;
		ePos.Normalize();

		m_Dec = v.Dot(ePos);
}