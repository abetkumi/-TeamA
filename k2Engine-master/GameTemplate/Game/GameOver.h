#pragma once
#include "sound/SoundSource.h" 

class Title;
class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();
	void Update();
	void Render(RenderContext& rc);

	Vector3 m_position;
	SpriteRender spriteRender;

	Title* title;
	SoundSource* gameOverBGM;
};

