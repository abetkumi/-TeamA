#pragma once
#include "sound/SoundSource.h" 

class Title;
class Game;

class GameClear : public IGameObject
{
public:
	GameClear();
	~GameClear();
	void Update();
	void Render(RenderContext& rc);

	Vector3 m_position;
	SpriteRender spriteRender;

	Game* game;
	Title* title;
	SoundSource* gameClearBGM;
};

