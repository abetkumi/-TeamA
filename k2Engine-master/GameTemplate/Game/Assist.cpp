#include "stdafx.h"
#include "Assist.h"
#include "Player.h"
#include "Enemy.h"
#include "GameCamera.h"

Assist::Assist()
{
	player = FindGO<Player>("player");
	enemy = FindGO<Enemy>("enemy");
	gameCamera = FindGO<GameCamera>("gameCamera");

}

Assist::~Assist()
{

}

void Assist::Update()
{
	if (enemy->Serch() == true)
	{
		Decision();
		Homing();
	}
}

void Assist::Homing()
{
	if (Decision() == true)
	{
		Vector3 Qua = enemy->m_position - player->m_position;
		Qua.Normalize();

		/*player->m_moveSpeed = Qua;*/
	}
}

const bool Assist::Decision()
{
	if (gameCamera->m_Dec >= 0.98)
	{
		return true;
	}
	else
		return false;
}


//bool GameCamera::Target()
//{
//	if (Serch() == true)
//		if (m_Dec >= 0.999)
//		{
//			return true;
//		}
//}
//
//const bool GameCamera::Serch()
//{
//	Vector3 diff = enemy->m_position - m_player->m_position;
//	if (diff.LengthSq() <= serch)
//	{
//		return true;
//	}
//}

//
//if (Target() == true)
//{
//	m_player->HP -= 100;
//}

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