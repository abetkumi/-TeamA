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
	SpriteRender m_spriteRender;
	//SpriteRender m_spriteRender_m;
	FontRender m_fontRender;
	Game* game;
	SoundSource* titleBGM;
	//AlphaBlendMode m_alphaBlendMode = AlphaBlendMode_Trans;

	float m_shade = 0.0f;
};