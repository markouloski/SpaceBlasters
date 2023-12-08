#include "IGameObject.h"
#include "Vec2.h"
IGameObject::IGameObject()
{
	isAlive = true;
	rotation = 0.0f;
	rotationSpeed = 0.0f;
}
IGameObject::~IGameObject()
{

}

void IGameObject::Update(float deltaTime)
{

}

void IGameObject::Draw()
{

}

bool IGameObject::isDead(IGameObject* obj)
{
	return !obj->isAlive;
}

bool IGameObject::Destroy(IGameObject* obj)
{
	delete obj;
	return true;
}

bool IGameObject::destroyifDead(IGameObject* obj)
{
	if (!obj->isAlive)
	{
		delete obj;
		return true;
	}

	return false;
}