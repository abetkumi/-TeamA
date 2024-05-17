#pragma once
class Rock : public IGameObject
{
	public:
		bool Start();
		Rock();
		~Rock();
		void Update();
		void Render(RenderContext& rc);

		Vector3 r_position;
		Quaternion r_rotation;
		ModelRender r_modelRender;
		CollisionObject* r_collisionObject;
};

