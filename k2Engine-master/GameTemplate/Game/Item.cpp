#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "Game.h"
#include <random>
#include "sound/SoundSource.h" 

Item::Item()
{
	m_modelRender.Init("Assets/modelData/BlueBottle.tkm");
	g_soundEngine->ResistWaveFileBank(4, "Assets/BGMÅESE/TitleBGM.wav");

	player = FindGO<Player>("player");

	//r = rand() & 6;
	//Count -= 10;
	r = 4;
	//switch (r)
	//{
	//case 0:
	//	m_modelRender.Init();//DEF-50%
	//	break;
	//case 1:
	//	m_modelRender.Init();//ATK+5
	//	break;
	//case 2:
	//	m_modelRender.Init();//Stamina*2
	//	break;
	//case 3:
	//	m_modelRender.Init();//Arrow+2
	//	break;
	//case 4:
	//	m_modelRender.Init();//HP+30
	//	break;
	//case 5:
	//	m_modelRender.Init();//SPup
	//	break;
	//}
	game = FindGO<Game>("game");
	m_position = game->m_nextPosition1;
	m_position.y += 50.0f;
	m_modelRender.SetPosition(m_position);
}

Item::~Item()
{

	if (i == 0) {
		switch (r)
		{
		case 0:
			//DEF-50%
			break;
		case 1:
			//ATK+5
			break;
		case 2:
			//Stamina*2
			break;
		case 3:
			//Arrow+2
			break;
		case 4:
			//HP+30
			player->HP += 30;
			break;
		case 5:
			//SPup
			break;
		}
	}
	DeleteGO(ItemGetSE);
}

void Item::Update()
{
	Rotation();
	Despawn();

	m_modelRender.Update();

	Vector3 diff = player->m_position - m_position;
	if (diff.Length() <= 120.0f)
	{
		ItemGetSE = NewGO<SoundSource>(4);
		ItemGetSE->Init(4);
		ItemGetSE->Play(false);
		DeleteGO(this);
	}
}

void Item::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}

void Item::Rotation()
{
	m_rotation.AddRotationDegY(2.0f);
	m_modelRender.SetRotation(m_rotation);
}

void Item::Despawn()
{
	if (player->m_position.x/*âº*/ < m_position.z - 120.0f) {
		DeleteGO(this);
		i = 1;
	}
}
