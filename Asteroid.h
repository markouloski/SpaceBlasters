#pragma once
#include "Vec2.h"
#include "IGameObject.h"
class Asteroid : public IGameObject
{
public:
	Asteroid();
	virtual ~Asteroid();

	virtual void Update(float deltaTime);
	virtual void Draw();
private:
protected:
};

