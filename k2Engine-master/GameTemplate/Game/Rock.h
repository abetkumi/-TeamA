#pragma once
#include "sound/SoundSource.h"

class Player;
class Game;

class Rock : public IGameObject
{
public:
	bool Start();
	Rock();
	~Rock();
	void RockDamage();
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
	SoundSource* se;
	Vector3 r_position;
	Quaternion r_rotation = g_quatIdentity;// = g_identity;
	Quaternion r_rot;
	Vector3 r_scale = Vector3::One;
	ModelRender r_modelRender;
	PhysicsStaticObject r_physicsStaticObject;
	bool r_rockFlag = false;
	Vector3 r_damagePosition;
	float r_damageLag = 0.0f;
	
};

