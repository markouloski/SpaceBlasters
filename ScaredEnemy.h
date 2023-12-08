#pragma once
#include "IGameObject.h"
class ScaredEnemy : public IGameObject
{
public:

	ScaredEnemy();
	virtual ~ScaredEnemy();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void RunAway();
protected:
private:
};