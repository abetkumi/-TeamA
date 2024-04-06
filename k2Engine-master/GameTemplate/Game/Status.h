#pragma once
class Status : public IGameObject
{
public:
	Status();
	~Status();

	int p_HP, i_HP, g_HP, s_HP, boss_HP;   //HP
	int p_ST;                              //スタミナ
	int p_ATK, g_ATK, s_ATK, boss_ATK;     //攻撃力
	int g_IT, s_IT;                        //アイテムポイント
	double g_AS, s_AS, boss_AS;            //攻撃速度
};

