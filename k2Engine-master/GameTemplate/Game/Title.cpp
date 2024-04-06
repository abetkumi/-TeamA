#include "stdafx.h"
#include "Title.h"

Title::Title()
{

}

Title::~Title()
{

}

void Title::Update()
{
	spriteRender.Update();
}

void Title::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}
