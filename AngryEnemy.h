#pragma once
#include "IGameObject.h"
#include "Vec2.h"
class AngryEnemy : public IGameObject
{
public:
	AngryEnemy();
	virtual ~AngryEnemy();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void ChargeTowards();
protected:
private:
};