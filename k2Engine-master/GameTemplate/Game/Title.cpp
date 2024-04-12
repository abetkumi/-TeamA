#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
	spriteRender.Init("Assets/modelData/Title.dds", 1920.0f, 1080.0f);
}

Title::~Title()
{
	
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0);
		DeleteGO(this);
	}

	/*spriteRender.Update();*/
}

void Title::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}
