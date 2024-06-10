#include "stdafx.h"
#include "Loading.h"
#include "Game.h"
Loading::Loading()
{

}

Loading::~Loading()
{

}

bool Loading::Start()
{
	m_spriteRender.Init("Assets/sprite/Black.dds",1920.0f,1080.0f);
	m_spriteRender2.Init("Assets/sprite/Now Loading.dds",1920.0f,1080.0f);
	m_spriteRender2.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_shade));

	return true;
}

void Loading::Update()
{
	m_shade += g_gameTime->GetFrameDeltaTime() * m_timer;
	if (m_shade >= 1.0f)
	{
		m_timer *= -1.0f;
	}
	if (m_shade <= 0.2f)
	{
		m_timer *= -1.0f;
	}
	m_spriteRender2.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_shade));
	m_spriteRender2.Update();

	m_lag++;
	if (m_lag >= 200)
	{
		game = NewGO<Game>(0, "game");
		DeleteGO(this);
	}
}

void Loading::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_spriteRender2.Draw(rc);
}