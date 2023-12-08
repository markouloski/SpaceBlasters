#include "Bullet.h"
#include "Assets.h"
#include "raylib.h"
#include "IGameObject.h"
Bullet::Bullet()
{
	type = GameObjectTypes::BULLET;
	bulletType = BulletType::UNKNOWN;
	Velocity = { 0, -100 };
}
Bullet::~Bullet()
{

}
void Bullet::Update(float deltaTime)
{
	position += Velocity * deltaTime;

	Vec2 dir = Velocity.Normalise();
	rotation = atan2f(dir.x, -dir.y) * 180.0f / 3.14159f;

	if (position.y < -size.y || position.y > GetScreenHeight() + size.y)
	{
		isAlive = false;
	}
}
void Bullet::Draw()
{
	DrawTexturePro(
		bulletTexture,
		{ 0, 0, (float)bulletTexture.width, (float)bulletTexture.height },
		{ position.x, position.y, size.x, size.y },
		{ size.x / 2.0f, 0 },
		rotation,
		WHITE
	);
}