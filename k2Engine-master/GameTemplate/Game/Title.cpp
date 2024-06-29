#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Loading.h"
#include "sound/SoundSource.h"

Title::Title()
{
	m_spriteRender.Init("Assets/modelData/Title2.dds", 1920.0f, 1080.0f);
	m_spriteRender_m.Init("Assets/sprite/TitleMOZI.dds", 1920.0f, 1080.0f, m_alphaBlendMode);
	m_spriteRender_m.SetPosition({ 0.0f,-40.0f,0.0f });
	m_spriteRender_m.SetMulColor(Vector4(1.0f,1.0f,1.0f,m_shade));
	g_soundEngine->ResistWaveFileBank(0, "Assets/BGMÅESE/TitleBGM.wav");
	g_soundEngine->ResistWaveFileBank(11, "Assets/BGMÅESE/Select.wav");

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
	if (g_pad[0]->IsTrigger(enButtonA) && m_lagFlag == false)
	{
		m_timer *= 30.0f;
		m_lagFlag = true;
		titleSE = NewGO<SoundSource>(11);
		titleSE->Init(11);
		titleSE->Play(false);
	}
	if (m_lagFlag == true)
	{
		m_lag++;
		if (m_lag >= 80)
		{
			loading = NewGO<Loading>(0, "laoding");
			DeleteGO(this);
		}
	}
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
}
