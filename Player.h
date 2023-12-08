#pragma once
#include "Vec2.h"
#include "IGameObject.h"
#include "PlayState.h"
class Player : public IGameObject
{
public:
	PlayState* world;
	float speed;
	Player();
	virtual ~Player();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Shoot();
	void Hurt();

	bool hurt = false;
	bool triple = false;
protected:
private:
};