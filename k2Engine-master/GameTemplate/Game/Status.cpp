#include "stdafx.h"
#include "Status.h"
#include "Player.h"

Status::Status()
{
	player = FindGO<Player>("player");

	player->HP = p_HP;
}

Status::~Status()
{

}
