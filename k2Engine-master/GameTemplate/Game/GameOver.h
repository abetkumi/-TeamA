#pragma once
#include "sound/SoundSource.h" 

class Title;
class Game;

class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();
	void Update();
	void Render(RenderContext& rc);

	Vector3 m_position;
	SpriteRender spriteRender;

	Game* game;
	Title* title;
	SoundSource* gameOverBGM;
};

