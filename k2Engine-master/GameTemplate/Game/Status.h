#pragma once
class Status : public IGameObject
{
public:
	Status();
	~Status();

	int p_HP, i_HP, g_HP, s_HP, boss_HP;   //HP
	int p_ST;                              //�X�^�~�i
	int p_ATK, g_ATK, s_ATK, boss_ATK;     //�U����
	int g_IT, s_IT;                        //�A�C�e���|�C���g
	double g_AS, s_AS, boss_AS;            //�U�����x
};

