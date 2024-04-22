#pragma once

class Player;

class Boss:public IGameObject
{
public:
	Boss();
	~Boss();

	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();


	ModelRender m_modelRender;
	Vector3 m_position;
	Vector3 m_scale;
	Vector3 m_moveSpeed;
	Quaternion m_rotation;
	Player* player;

	
};

