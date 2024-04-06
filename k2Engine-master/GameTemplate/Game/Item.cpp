#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include <random>

Item::Item()
{
	player = FindGO<Player>("player");

	r = rand() & 6;
	Count -= 10;

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
}

Item::~Item()
{
	if (i = 0) {
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
			break;
		case 5:
			//SPup
			break;
		}
	}
}

void Item::Update()
{
	Rotation();
	Despawn();

	m_modelRender.Update();

	Vector3 diff = player->m_position - m_position;
	if (diff.Length() <= 120.0f)
	{
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
	if (player->m_position.x/*‰¼*/ < m_position.x - 120.0f) {
		DeleteGO(this);
		i = 1;
	}
}
