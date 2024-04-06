#pragma once
class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();
	void Update();
	void Render(RenderContext& rc);

	Vector3 m_position;
	SpriteRender spriteRender;
};

