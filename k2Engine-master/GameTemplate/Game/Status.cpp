#include "stdafx.h"
#include "Status.h"
#include "Player.h"
#include "Boat.h"
#include "Enemy.h"

Status::Status()
{
	player = FindGO<Player>("player");

	player->HP = p_HP;
	player->ST = p_ST;
	player->ATK = p_ATK;

	boat->HP = i_HP;

	enemy->HP = g_HP;
}

Status::~Status()
{

}
