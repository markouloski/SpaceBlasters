#pragma once
#include "IGameObject.h"

class PlayState;

class ShooterEnemy : public IGameObject
{
public:
	PlayState* world;

	float moveSpeed;
	float aliveTime;
	float xOffset;
	float osilateSpeed;

	float shootSpawnTime;
	float shootSpawnTimeReset;
public:

	ShooterEnemy();
	virtual ~ShooterEnemy();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Shoot();

private:

protected:

};

