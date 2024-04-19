#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"

GameOver::GameOver()
{
	spriteRender.Init("Assets/modelData/GameOver.dds", 1920.0f, 1080.0f);
}

GameOver::~GameOver()
{

}

void GameOver::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Title>(0);
		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}
