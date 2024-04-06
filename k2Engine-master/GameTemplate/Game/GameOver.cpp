#include "stdafx.h"
#include "GameOver.h"

GameOver::GameOver()
{

}

GameOver::~GameOver()
{

}

void GameOver::Update()
{
	spriteRender.Update();
}

void GameOver::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}
