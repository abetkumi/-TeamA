#pragma once

class Title;
class GameClear : public IGameObject
{
public:
	GameClear();
	~GameClear();
	void Update();
	void Render(RenderContext& rc);

	Vector3 m_position;
	SpriteRender spriteRender;

	Title* title;
};

