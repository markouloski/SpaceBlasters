#pragma once
#include "Vec2.h"
#include "raylib.h"
enum class GameObjectTypes
{
	UNDEFINED,
	PLAYER,
	ASTEROID,
	BULLET,
	SCARED_ENEMY,
	ANGRY_ENEMY,
	SHOOTER_ENEMY
};

class IGameObject
{
public:
	GameObjectTypes type = GameObjectTypes::UNDEFINED;

	Vec2 pos; 
	Vec2 position;
	Vec2 size;
	Vec2 Velocity;
	Vec2 targetPos;
	Vec2 dir;
	float velocity;
	float rotation;
	float rotationSpeed;

	bool isAlive;

	IGameObject();
	virtual ~IGameObject();

	virtual void Update(float deltaTime);
	virtual void Draw();

	static bool isDead(IGameObject* obj);
	static bool Destroy(IGameObject* obj);
	static bool destroyifDead(IGameObject* obj);
private:
protected:

};