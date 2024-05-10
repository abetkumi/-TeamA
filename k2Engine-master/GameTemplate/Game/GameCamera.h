#pragma once

class Player;
class Enemy;
class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Decision();

	Player* m_player;
	Enemy* enemy;
	Vector3 m_toCameraPos;
	Vector3 m_toPosDir;
	Vector3 target;
	Vector3 pos;
	SpriteRender m_spriteRender;

	double m_Dec;
};