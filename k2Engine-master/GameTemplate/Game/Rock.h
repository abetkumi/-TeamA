#pragma once
class Player;
class Game;

class Rock : public IGameObject
{
public:
	bool Start();
	Rock();
	~Rock();
	void Colision();
	void Update();
	void Render(RenderContext& rc);

	void SetPosition(const Vector3& position)
	{
		r_position = position;
	}
	void Setrotation(const Quaternion& rotation)
	{
		r_rotation = rotation;
	}

	Game* game;
	Player* player;
	Vector3 r_position;
	Quaternion r_rotation = g_quatIdentity;// = g_identity;
	Quaternion r_rot;
	Vector3 r_scale = Vector3::One;
	ModelRender r_modelRender;
	PhysicsStaticObject r_physicsStaticObject;
	CollisionObject* r_collisionObject;
	bool r_rockFlag = false;
	float damageLag = 0.0f;
};

