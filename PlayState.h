#pragma once
#include "IGameState.h"
#include <list>
#include "Asteroid.h"
#include "Bullet.h"

class Player;
class Bullet;
class ScaredEnemy;
class ShooterEnemy;
class Asteroid;
class AngryEnemy;
class PlayState : public IGameState
{
public:
	PlayState();
	virtual ~PlayState();
	
	Player* CreatePlayer();
	Asteroid* CreateAsteroid();
	Bullet* CreateBullet(BulletType bType, Vec2 pos, Vec2 vel);
	AngryEnemy* CreateAngryEnemy();
	ScaredEnemy* CreateScaredEnemy();
	ShooterEnemy* CreateShooterEnemy();

	void DestroyAsteroid(Asteroid* asteroid);
	void DestroyBullet(Bullet* bullets);
	void DestroyShooterEnemy(ShooterEnemy* enemy);

	virtual void Load();
	virtual void UnLoad();
	virtual void Update(float deltaTime);
	void UpdatePlayer(float deltaTime);
	void UpdateAsteroids(float deltaTime);
	void UpdateBullets(float deltaTime);
	void UpdateAngryEnemy(float deltaTime);
	void UpdateScaredEnemy(float deltaTime);
	void UpdateShooterEnemy(float deltaTime);

	void CheckCollisions();
	void OnCollision(IGameObject* objA, IGameObject* objB);


	void OnPlayerBulletCollision(Player* player, Bullet* bullets);
	void OnPlayerAsteroidCollision(Player* player, Asteroid* asteroid);
	void OnPlayerScaredEnemyCollision(Player* player, ScaredEnemy* enemy);
	void OnPlayerAngryEnemyCollision(Player* player, AngryEnemy* enemy);
	void OnPlayerShooterEnemyCollision(Player* player, ShooterEnemy* enemy);

	void OnBulletAsteroidCollision(Bullet* bullets, Asteroid* asteroid);
	void OnBulletScaredEnemyCollision(Bullet* bullets, ScaredEnemy* enemy);
	void OnBulletShooterEnemyCollision(Bullet* bullets, ShooterEnemy* enemy);
	void OnBulletAngryEnemyCollision(Bullet* bullets, AngryEnemy* enemy);


	virtual void Draw();

	void DrawPlayer();
	void DrawAsteroids();
	void DrawShooterEnemies();
	void DrawBullets();
	void DrawAngryEnemies();
	void DrawScaredEnemies();
	void DealDamage(int amount);
	void IncreaseScore(int amount);
	void DrawGameUi();
protected:
private:
	int lives;
	int health;
	int score;

	Player* player;

	std::list<IGameObject*> allGameObjects;
	std::list<Asteroid*> asteroids;
	std::list<Bullet*> bullets;
	std::list<AngryEnemy*> angryEnemies;
	std::list<ScaredEnemy*> scaredEnemies;
	std::list<ShooterEnemy*> shooterEnemies;

	float asteroidSpawnTime;
	float asteroidSpawnTimeReset;

	float scaredEnemySpawnTime;
	float scaredEnemySpawnReset;

	float AngryEnemySpawnTime;
	float AngryEnemySpawnReset;

	float shooterEnemySpawnTime;
	float shooterEnemyTimeReset;

};
