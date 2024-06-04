#pragma once
#include "sound/SoundSource.h" 

class Title;
class Game;
class GameCamera;

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
	GameCamera* gameCamera;
	Title* title;
	SoundSource* gameClearBGM;
};

