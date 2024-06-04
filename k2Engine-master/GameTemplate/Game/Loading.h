#pragma once
class Game;
class Loading : public IGameObject
{
public:
	Loading();
	~Loading();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Game* game;
	SpriteRender m_spriteRender;
	SpriteRender m_spriteRender2;
	int m_lag = 0;
	float m_shade = 0.5f;
	float m_timer = 0.8f;
};

