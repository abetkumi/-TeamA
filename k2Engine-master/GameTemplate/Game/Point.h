#pragma once

class Boat;

class Point:public IGameObject
{
public:
	Point();
	~Point();
	void Update();
	void Render(RenderContext& rc);

	Vector3 m_position;
	ModelRender m_modelRender;
	Boat* boat;

};

