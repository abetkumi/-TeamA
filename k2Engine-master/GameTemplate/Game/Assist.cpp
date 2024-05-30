#include "stdafx.h"
#include "Assist.h"
#include "Player.h"
#include "Enemy.h"
#include "GameCamera.h"

Assist::Assist()
{
	player = FindGO<Player>("player");
	//enemy = FindGO<Enemy>("enemy");
	gameCamera = FindGO<GameCamera>("gameCamera");

}

Assist::~Assist()
{

}

void Assist::Update()
{
	const std::vector<Enemy*>& enemys = FindGOs<Enemy>("enemy");

	for (int i = 0; i < enemys.max_size(); i++)
	{
		Distance();
		Homing();
	}
}
const bool Assist::Homing()
{
	if (enemy->Dec() == true)
	{
		return true;
	}
	/*return true;*/
}

void Assist::Distance()
{
	//m_peDisPos = enemy->m_pePos;
	m_peTemporary = enemy->m_peDis;

	if (m_peDistane > m_peTemporary)
	{
		m_ePos = enemy->m_position;
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