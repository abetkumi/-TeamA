#include "stdafx.h"
#include "MoveRock.h"
#include "Game.h"

MoveRock::MoveRock()
{

}

MoveRock::~MoveRock()
{

}

bool MoveRock::Start()
{
	m_modelRender.Init("Assets/modelData/MoveRock.tkm");
	game = FindGO<Game>("game");

	return true;
}

void MoveRock::Update()
{

}

void MoveRock::Render(RenderContext& rc)
{

}

void MoveRock::Move()
{

}

void MoveRock::Rotation()
{

}