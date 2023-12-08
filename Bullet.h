#pragma once
#include "IGameObject.h"
#include "raylib.h"

enum class BulletType
{
	UNKNOWN,
	PLAYER,
	ENEMY
};
class Bullet : public IGameObject
{
public:
	BulletType bulletType;
	Texture2D bulletTexture;

	Bullet();
	virtual ~Bullet();

	virtual void Update(float deltaTime);
	virtual void Draw();


private:

protected:

};