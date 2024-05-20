#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundSource.h"

Title::Title()
{
	m_spriteRender.Init("Assets/modelData/Title2.dds", 1920.0f, 1080.0f);
	m_fontRender.SetText(L"Pless A Start");
	m_fontRender.SetPosition({ -450.0f,-200.0f,0.0f });
	m_fontRender.SetScale(3.0f);
	m_fontRender.SetColor(g_vec4Yellow);
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
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}
