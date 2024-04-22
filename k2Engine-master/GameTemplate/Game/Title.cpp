#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundSource.h"

Title::Title()
{
	spriteRender.Init("Assets/modelData/Title.dds", 1920.0f, 1080.0f);
	g_soundEngine->ResistWaveFileBank(0, "Assets/BGMÅESE/TitleBGM.wav");

	bgm = NewGO<SoundSource>(0);
	bgm->Init(0);
	bgm->Play(true);
}

Title::~Title()
{
	
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0,"game");
		DeleteGO(this);
		DeleteGO(bgm);
	}

	/*spriteRender.Update();*/
}

void Title::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}
