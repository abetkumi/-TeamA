#pragma once
#include "sound/SoundSource.h" 

class Game;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render(RenderContext& rc);

	Vector3 m_position;
	SpriteRender spriteRender;
	Game* game;
	SoundSource* titleBGM;
};