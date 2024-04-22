#include "stdafx.h"
#include "Status.h"
#include "Player.h"
#include "Boat.h"

Status::Status()
{
	player = FindGO<Player>("player");

	player->HP = p_HP;
	player->ST = p_ST;

	boat->HP = i_HP;
}

Status::~Status()
{

}
