#include "Asteroid.h"
#include "raylib.h"
#include "Assets.h"
#include "IGameObject.h"
Asteroid::Asteroid() : IGameObject()
{
	type = GameObjectTypes::ASTEROID;
	rotation = 0.0f;
	rotationSpeed = 0.0f;
}
Asteroid::~Asteroid()
{

}

void Asteroid::Update(float deltaTime)
{
	rotation += rotationSpeed * deltaTime;
	position += Velocity * deltaTime;

	if (position.y > GetScreenHeight() + size.y)
	{
		isAlive = false;
	}
}
void Asteroid::Draw()
{
	DrawTexturePro(
		Assets::imgAsteroidBrownBig1,
		{ 0, 0, (float)Assets::imgAsteroidBrownBig1.width, (float)Assets::imgAsteroidBrownBig1.height },
		{ position.x, position.y, size.x, size.y },
		{ size.x / 2.0f, size.y / 2.0f },
		rotation,
		WHITE
	);
}
