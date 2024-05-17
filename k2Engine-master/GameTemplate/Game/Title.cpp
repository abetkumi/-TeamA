#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundSource.h"

Title::Title()
{
	spriteRender.Init("Assets/modelData/Title.dds", 1920.0f, 1080.0f);
	g_soundEngine->ResistWaveFileBank(0, "Assets/BGMÅESE/TitleBGM.wav");

	titleBGM = NewGO<SoundSource>(0);
	titleBGM->Init(0);
	titleBGM->Play(true);
}

Title::~Title()
{
	DeleteGO(titleBGM);
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		game = NewGO<Game>(0,"game");
		DeleteGO(this);
	}

	/*spriteRender.Update();*/
}

void Title::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}
