#pragma once

class Boat;
class Player;
class Status : public IGameObject
{
public:

	Status();
	~Status();
	//プレイヤー
	const int p_HP = 100;
	int p_ST = 100;
	int p_ATK = 10;

	//イカダ
	int i_HP = 100;

	//ゴブリン
	int g_HP = 10;
	int g_ATK = 5;
	double g_AS = 6.0;
	int g_IT = 2;

	//スケルトン
	int s_HP = 15;
	int s_ATK = 8;
	double s_AS = 4.5;
	int s_IT = 5;

	//BOSS
	int boss_HP = 200;
	double boss_ATK = 10;
	int boss_AS = 8.0;

	Player* player;
	Boat* boat;
};

