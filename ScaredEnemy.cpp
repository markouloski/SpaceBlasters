#include "ScaredEnemy.h"
#include "raylib.h"
#include "Assets.h"
#include "Config.h"
#include "IGameObject.h"
#include "Asteroid.h"

ScaredEnemy::ScaredEnemy() : IGameObject()
{
	type = GameObjectTypes::SCARED_ENEMY;
	rotationSpeed = 0;
	rotation = 0;
}
ScaredEnemy::~ScaredEnemy()
{

}

void ScaredEnemy::Update(float deltaTime)
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
void ScaredEnemy::Draw()
{
	DrawTexturePro(
		Assets::imgScaredUFO,
		{ 0, 0, (float)Assets::imgScaredUFO.width, (float)Assets::imgScaredUFO.height },
		{ position.x, position.y, size.x, size.y },
		{ size.x / 2.0f, size.y / 2.0f },
		rotation,
		WHITE
	);
}
void ScaredEnemy::RunAway()
{
	float XDir = 1.0f;
	if (position.x < GetScreenWidth() / 2.0f)
		XDir = -1.0f;

	Velocity.x += config.enemy.scaredEnemyRunSpeed * XDir;


}