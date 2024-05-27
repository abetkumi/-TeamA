#pragma once
class Rock : public IGameObject
{
	public:
		bool Start();
		Rock();
		~Rock();
		void Colision();
		void Update();
		void Render(RenderContext& rc);

		Vector3 r_position;
		Quaternion r_rotation;
		Vector3 r_scale = Vector3::One;
		ModelRender r_modelRender;
		PhysicsStaticObject r_physicsStaticObject;
		CollisionObject* r_collisionObject;
};

