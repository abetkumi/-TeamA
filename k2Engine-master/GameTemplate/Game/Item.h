#pragma once

class Player;
class Item : public IGameObject
{
public:
	Item();
	~Item();
	void Update();
	void Render(RenderContext& renderContext);
	void Rotation();
	void Despawn();

	ModelRender m_modelRender;
	Vector3 m_position;
	Quaternion m_rotation;
	Player* player;

	int Count, r, i = 0;
};

