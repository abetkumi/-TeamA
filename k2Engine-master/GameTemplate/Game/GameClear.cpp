#include "stdafx.h"
#include "GameClear.h"

GameClear::GameClear()
{

}

GameClear::~GameClear()
{

}

void GameClear::Update()
{
	spriteRender.Update();
}

void GameClear::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}
