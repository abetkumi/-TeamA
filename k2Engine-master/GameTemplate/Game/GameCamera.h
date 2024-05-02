#pragma once

class Player;
class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Player* m_player;
	Vector3 m_toCameraPos;
	Vector3 target;
	Vector3 pos;
	SpriteRender m_spriteRender;
};