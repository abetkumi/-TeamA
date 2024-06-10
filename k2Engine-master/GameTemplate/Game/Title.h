#pragma once
#include "sound/SoundSource.h" 

class Game;
class Loading;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render(RenderContext& rc);

	Vector3 m_position;
	SpriteRender m_spriteRender;
	SpriteRender m_spriteRender_m;
	Game* game;
	Loading* loading;
	SoundSource* titleBGM;
	SoundSource* titleSE;
	AlphaBlendMode m_alphaBlendMode = AlphaBlendMode_Trans;

	float m_shade = 0.5f;
	float m_timer = 0.5f;
	int m_lag = 0;
	bool m_lagFlag = false;
};