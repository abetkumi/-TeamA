#pragma once

class Player;
class Enemy;
class Enemy2;
class Enemy3;

class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	void SpriteColor();
	void Render(RenderContext& rc);

	Player* m_player;
	Enemy* m_enemy;
	Enemy2* m_enemy2;
	Enemy3* m_enemy3;

	Vector3 m_toCameraPos;
	Vector3 m_toPosDir;
	Vector3 target;
	Vector3 pos;
	bool m_gameOverFlag = true;

	SpriteRender m_spriteRender;
};