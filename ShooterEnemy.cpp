#include "ShooterEnemy.h"
#include "IGameObject.h"
#include "Assets.h"
#include "Config.h"
#include "PlayState.h"
ShooterEnemy::ShooterEnemy()
{
	type = GameObjectTypes::SHOOTER_ENEMY;

	world = nullptr;

	size.x = Assets::imgShooterEnemy.width;
	size.y = Assets::imgShooterEnemy.height;

	moveSpeed = 100;
	aliveTime = 0.0f;
	xOffset = 0.0f;
	osilateSpeed = 1.0f;

	shootSpawnTime = 0;
	shootSpawnTimeReset = 3.0f;
}
ShooterEnemy::~ShooterEnemy()
{

}

void ShooterEnemy::Update(float deltaTime)
{
	if (position.y < config.enemy.shooterEnemyYPos)
	{
		position.y += moveSpeed * deltaTime;
		xOffset = position.x;
	}

	if (position.y >= config.enemy.shooterEnemyYPos)
	{
		aliveTime += deltaTime;
		position.x = xOffset + sin(aliveTime * osilateSpeed) * (GetScreenWidth() / 2.0f);
	}
	shootSpawnTime -= deltaTime;
	if (shootSpawnTime < 0)
	{
		Shoot();
		shootSpawnTime = shootSpawnTimeReset;
	}


}
void ShooterEnemy::Draw()
{
	DrawTexturePro(
		Assets::imgShooterEnemy,
		{ 0, 0, (float)Assets::imgShooterEnemy.width, (float)Assets::imgShooterEnemy.height },
		{ position.x, position.y, size.x, size.y },
		{ size.x / 2.0f, size.y / 2.0f },
		rotation,
		WHITE
	);
}

void ShooterEnemy::Shoot()
{
	if (world != nullptr)
	{
		world->CreateBullet(
			BulletType::ENEMY,
			position + Vec2(0, size.y / 2),
			{ 0,config.enemy.shooterBulletSpeed }
		);
	}
}