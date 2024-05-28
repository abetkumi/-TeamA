#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"
#include "sound/SoundSource.h" 
#include "Game.h"

GameOver::GameOver()
{
	spriteRender.Init("Assets/modelData/GameOver.dds", 1920.0f, 1080.0f);
	g_soundEngine->ResistWaveFileBank(1, "Assets/BGMÅESE/GameOver.wav");

	gameOverBGM = NewGO<SoundSource>(1);
	gameOverBGM->Init(1);
	gameOverBGM->Play(true);
	game = FindGO<Game>("game");
}

GameOver::~GameOver()
{
	DeleteGO(gameOverBGM);
}

void GameOver::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Title>(0,"title");
		DeleteGO(this);
		DeleteGO(game);
	}
}

void GameOver::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}
