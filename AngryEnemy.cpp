#include "AngryEnemy.h"
#include "raylib.h"
#include "Assets.h"
#include "Config.h"
#include "IGameObject.h"
#include "Asteroid.h"
#include "Vec2.h"

AngryEnemy::AngryEnemy() : IGameObject()
{
	type = GameObjectTypes::ANGRY_ENEMY;
	rotationSpeed = 0;
	rotation = 0;
}
AngryEnemy::~AngryEnemy()
{

}

void AngryEnemy::Update(float deltaTime)
{
	rotation += rotationSpeed * deltaTime;
	position += Velocity * deltaTime;


	if (position.y > GetScreenHeight() + size.y)
		isAlive = false;

	if (position.x < -size.x)
		isAlive = false;

	if (position.x > GetScreenWidth() + size.x)
		isAlive = false;
}
void AngryEnemy::Draw()
{
	DrawTexturePro(
		Assets::imgAgroUFO,
		{ 0, 0, (float)Assets::imgAgroUFO.width, (float)Assets::imgAgroUFO.height },
		{ position.x, position.y, size.x, size.y },
		{ size.x / 2.0f, size.y / 2.0f },
		rotation,
		WHITE
	);
}
void AngryEnemy::ChargeTowards()
{
	float YDir = 2.0f;

	Velocity.y += config.enemy.scaredEnemyRunSpeed * YDir;
}