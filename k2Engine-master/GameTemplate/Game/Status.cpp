#include "stdafx.h"
#include "Status.h"

Status::Status()
{
	//�v���C���[
	p_HP = 100;
	p_ST = 100;
	p_ATK = 10;

	//�C�J�_
	i_HP = 100;

	//�S�u����
	g_HP = 10;
	g_ATK = 5;
	g_AS = 6.0;
	g_IT = 2;

	//�X�P���g��
	s_HP = 15;
	s_ATK = 8;
	s_AS = 4.5;
	s_IT = 5;

	//BOSS
	boss_HP = 200;
	boss_ATK = 10;
	boss_AS = 8.0;
}

Status::~Status()
{

}
