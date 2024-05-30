#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundSource.h"

Title::Title()
{
	m_spriteRender.Init("Assets/modelData/Title2.dds", 1920.0f, 1080.0f);
	m_spriteRender_m.Init("Assets/sprite/TitleMOZI.dds", 1920.0f, 1080.0f, m_alphaBlendMode);
	m_spriteRender_m.SetPosition({ 0.0f,-40.0f,0.0f });
	m_spriteRender_m.SetMulColor(Vector4(1.0f,1.0f,1.0f,m_shade));
	//m_fontRender.SetText(L"Press A Start");
	//m_fontRender.SetPosition({ -450.0f,-200.0f,0.0f });
	//m_fontRender.SetScale(3.0f);
	//m_fontRender.SetColor(g_vec4Black);
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
	//m_fontRender.SetShadowParam(true,m_shade,g_vec4Yellow);
	m_shade += g_gameTime->GetFrameDeltaTime()*m_timer;
	if (m_shade >= 1.0f)
	{
		m_timer *= -1.0f;
	}
	if (m_shade <= 0.2f)
	{
		m_timer *= -1.0f;
	}
	m_spriteRender_m.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_shade));
	m_spriteRender_m.Update();
}

void Title::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_spriteRender_m.Draw(rc);
	//m_fontRender.Draw(rc);
}
