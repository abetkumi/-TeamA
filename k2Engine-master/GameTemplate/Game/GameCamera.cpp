#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Enemy3.h"

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
	m_enemy = FindGO<Enemy>("enemy");
	m_enemy2 = FindGO<Enemy2>("enemy2");
	m_enemy3 = FindGO<Enemy3>("enemy3");
	m_toCameraPos.Set(0.0f, -20.0f, -250.0f);
	m_player = FindGO<Player>("player");

	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(81000.0f);

	m_spriteRender.Init("Assets/sprite/syoujun.dds", 350.0f, 250.0f);
	m_spriteRender.SetMulColor({ 1.0f,0.0f,0.0f,1.0f });
	m_spriteRender.SetPosition(corre3);
	m_spriteRender.Update();

	return true;
}

void GameCamera::Update()
{
	//未完成
	//SpriteColor();

	target = m_player->m_position;
	target.y += 200.0f;


	
	if (m_player->m_arrowState == 4 || m_player->m_arrowState == 6)
	{
		Vector3 toCameraPosOld = m_toCameraPos;

		float x = g_pad[0]->GetRStickXF();
		float y = g_pad[0]->GetRStickYF();

		Quaternion qRot;
		qRot.SetRotationDeg(Vector3::AxisY, 0.0f * x);//���x
		qRot.Apply(m_toCameraPos);

		Vector3 axisX;
		axisX.Cross(Vector3::AxisY, m_toCameraPos);
		axisX.Normalize();
		qRot.SetRotationDeg(axisX, 0.0f * y);
		qRot.Apply(m_toCameraPos);

		Vector3 toPosDir = m_toCameraPos;
		toPosDir.Normalize();
		if (m_player->m_arrowState == 6)
		{
			target = pos + m_toCameraPos;
			pos = target - m_toCameraPos;
	
		}
		else if (m_player->m_arrowState == 4)
		{
			if (m_gameOverFlag == true)
			{
				target.y = target.y + 900.0f;
				target.z = target.z + 100.0f;
				pos.y = pos.y - 300.0f;
				m_gameOverFlag = false;
			}
		}
		g_camera3D->SetTarget(pos);
		g_camera3D->SetPosition(target);
	}
	else
	{
		Vector3 toCameraPosOld = m_toCameraPos;

		float x = g_pad[0]->GetRStickXF();
		float y = g_pad[0]->GetRStickYF();

		Quaternion qRot;
		qRot.SetRotationDeg(Vector3::AxisY, 1.2f * x);//���x
		qRot.Apply(m_toCameraPos);

		Vector3 axisX;
		axisX.Cross(Vector3::AxisY, m_toCameraPos);
		axisX.Normalize();
		qRot.SetRotationDeg(axisX, -1.2f * y);
		qRot.Apply(m_toCameraPos);

		Vector3 toPosDir = m_toCameraPos;
		toPosDir.Normalize();
		if (toPosDir.y < -0.5f) {
			m_toCameraPos = toCameraPosOld;
		}
		else if (toPosDir.y > 0.5f) {
			m_toCameraPos = toCameraPosOld;
		}
		pos = target + m_toCameraPos;
		target = target - m_toCameraPos;
		g_camera3D->SetTarget(pos);
		g_camera3D->SetPosition(target);
	}
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

//void GameCamera::SpriteColor()
//{
//	Vector3 diff1, diff2, diff3;
//	diff1 = m_enemy->m_position - pos;
//	diff2 = m_enemy2->m_position - pos;
//	diff3 = m_enemy3->m_position - pos;
//	if (diff1.Length() <= 5000)
//	{
//		diff1.Normalize();
//		Vector3 m_cameraFor;
//		m_cameraFor = g_camera3D->GetForward();
//		float v1 = diff1.x * m_cameraFor.x + diff1.y * m_cameraFor.y + diff1.z * m_cameraFor.z;
//	
//		if (v1 >= 0.99f)
//		{
//			m_spriteRender.SetMulColor({ 0.0f, 1.0f, 0.0f, 1.0f });
//		}
//		else
//		{
//			m_spriteRender.SetMulColor({ 1.0f,0.0f,0.0f,1.0f });
//		}
//	}
//	else if (diff2.Length() <= 5000)
//	{
//		diff2.Normalize();
//		Vector3 m_cameraFor;
//		m_cameraFor = g_camera3D->GetForward();
//		float v2 = diff2.x * m_cameraFor.x + diff2.y * m_cameraFor.y + diff2.z * m_cameraFor.z;
//		if (v2 >= 0.99f)
//		{
//			m_spriteRender.SetMulColor({ 0.0f, 1.0f, 0.0f, 1.0f });
//		}
//		else
//		{
//			m_spriteRender.SetMulColor({ 1.0f,0.0f,0.0f,1.0f });
//		}
//	}
//	else if (diff3.Length() <= 5000)
//	{
//		Vector3 m_cameraFor;
//		m_cameraFor = g_camera3D->GetForward();
//		diff3.Normalize();
//		float v3 = diff3.x * m_cameraFor.x + diff3.y * m_cameraFor.y + diff3.z * m_cameraFor.z;
//		if (v3 >= 0.99)
//		{
//			m_spriteRender.SetMulColor({ 0.0f, 1.0f, 0.0f, 1.0f });
//		}
//		else
//		{
//			m_spriteRender.SetMulColor({ 1.0f,0.0f,0.0f,1.0f });
//		}
//	}
//	else
//	{
//		m_spriteRender.SetMulColor({ 1.0f,0.0f,0.0f,1.0f });
//	}
//	m_spriteRender.Update();
//}

void GameCamera::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}