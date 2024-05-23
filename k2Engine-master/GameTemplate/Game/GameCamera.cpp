#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Enemy.h"

namespace
{
	const Vector3 corre1 = { 0.0f,100.0f,0.0f };//??u?C???{?????????
	const Vector3 corre2 = { 0.0f,80.0f,10.0f };//??u?C???e???????u
	const Vector3 corre3 = { -10.0f,0.0f,0.0f };
}

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	enemy = FindGO<Enemy>("enemy");
	m_toCameraPos.Set(0.0f, -20.0f, -250.0f);
	m_player = FindGO<Player>("player");

	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(100000.0f);

	m_spriteRender.Init("Assets/sprite/syoujun.dds", 350.0f, 250.0f);
	m_spriteRender.SetPosition(corre3);
	m_spriteRender.Update();

	return true;
}

void GameCamera::Update()
{
	target = m_player->m_position;
	target.y += 200.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.3f * x);//���x
	qRot.Apply(m_toCameraPos);

	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, -1.3f * y);
	qRot.Apply(m_toCameraPos);

	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();

	if (toPosDir.y < -0.5f) {
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.3f) {
		m_toCameraPos = toCameraPosOld;
	}

	pos = target + m_toCameraPos;
	target = target - m_toCameraPos;
	g_camera3D->SetTarget(pos);
	g_camera3D->SetPosition(target);
}

//void GameCamera::Decision()
//{
//	Vector3 v = m_player->m_position - m_toCameraPos;
//	v.Normalize();
//
//	Vector3 ePos = enemy->m_position - m_toCameraPos;
//	ePos.Normalize();
//
//	m_Dec = v.Dot(ePos);
//}

void GameCamera::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}