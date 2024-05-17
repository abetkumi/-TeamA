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
	if (enemy->Desision() == true)
	{
		Decision();
		Homing();
	}
}

void Assist::Homing()
{
	if (Decision() == true)
	{
		/*player->HP -= 100;*/
	}
}

void Assist::Distance()
{
	if (m_peDistane >= m_peTemporary)
	{
		m_ePos = m_peDisPos;
	}
}

const bool Assist::Decision()
{
	if (enemy->m_Dec >= 0.98)
	{
		return true;
	}
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