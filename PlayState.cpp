#include "PlayState.h"
#include "raylib.h"
#include "Application.h"
#include "Config.h"
#include <string>
#include "Assets.h"
#include "Player.h"
#include "ScaredEnemy.h"
#include "Bullet.h"
#include "ShooterEnemy.h"
#include "AngryEnemy.h"
#include <iostream>
PlayState::PlayState()
{

}
PlayState::~PlayState()
{

}

void PlayState::Load()
{
	app->SetMusic(&Assets::musBeginGame);
	//intitialise lives, health and score
	lives = config.player.max_lives;
	health = config.player.maxHealth;
	score = 0;

	player = CreatePlayer();
	CreateAsteroid();
	CreateAngryEnemy();
	CreateScaredEnemy();
	CreateShooterEnemy();

	scaredEnemySpawnTime = 0;
	scaredEnemySpawnReset = config.spawn.ScaredEnemySpawnFrequency.max;

	asteroidSpawnTime = 0;
	asteroidSpawnTimeReset = config.spawn.asteroidSpawnFrequency.max;

	AngryEnemySpawnTime = 0;
	AngryEnemySpawnTime = config.spawn.AngryEnemySpawnFrequency.max;

	shooterEnemySpawnTime = 0.0f;
	shooterEnemyTimeReset = config.spawn.shooterEnemySpawnFrequency.max;
}
Player* PlayState::CreatePlayer()
{
	auto p = new Player;
	p->world = this;
	allGameObjects.push_back(p);

	return p;
}
Asteroid* PlayState::CreateAsteroid()
{
	
	//Create Asteroid
	auto asteroid = new Asteroid();
	// set size
	float size = config.spawn.asteroidSizeRange.RandomRange();
	asteroid->size = { size, size };
	//set pos
	asteroid->position = {
		(float)(rand() % GetScreenHeight()),
		-size / 2.0f
	};
	asteroid->Velocity = {
		config.spawn.asteroidXVelocityRange.RandomRange(),
		config.spawn.asteroidYVelocityRange.RandomRange(),
	};
	asteroid->rotationSpeed = config.spawn.asteroidRotationSpeed.RandomRange();
	asteroids.push_back(asteroid);
	allGameObjects.push_back(asteroid);
	return asteroid;
}
ScaredEnemy* PlayState::CreateScaredEnemy()
{
	float size = config.spawn.ScaredEnemySizeRange.RandomRange();
	auto enemy = new ScaredEnemy();
	enemy->position = { (float)(rand() % GetScreenWidth()), -size / 2.0f };
	enemy->size = { size, size };
	enemy->Velocity = { 0, 100 };
	enemy->rotationSpeed = config.spawn.ScaredEnemyRotationSpeed.RandomRange();

	scaredEnemies.push_back(enemy);
	allGameObjects.push_back(enemy);

	return enemy;
}
ShooterEnemy* PlayState::CreateShooterEnemy()
{
	auto enemy = new ShooterEnemy();
	enemy->world = this;
	enemy->position = { GetScreenWidth() / 2.0f, -100 };

	shooterEnemies.push_back(enemy);
	allGameObjects.push_back(enemy);

	return enemy;
}
Bullet* PlayState::CreateBullet(BulletType bType, Vec2 pos, Vec2 vel)
{
	auto bullet = new Bullet();
	bullet->bulletType = bType;
	bullet->position = pos;
	bullet->Velocity = vel;

	if (bullet->bulletType == BulletType::PLAYER)
	{
		bullet->bulletTexture = Assets::imgPlayerLaser;
		bullet->size = { (float)Assets::imgPlayerLaser.width, (float)Assets::imgPlayerLaser .height};
	}
	else if
		(bullet->bulletType == BulletType::ENEMY)
	{
		bullet->bulletTexture = Assets::imgEnemyLaser;
		bullet->size = { (float)Assets::imgEnemyLaser.width, (float)Assets::imgEnemyLaser.height };
	}

	bullets.push_back(bullet);
	allGameObjects.push_back(bullet);

	PlaySound(Assets::sndShoot);
	return bullet;
}
AngryEnemy* PlayState::CreateAngryEnemy()
{
	float size = config.spawn.AngryEnemySizeRange.RandomRange();
	auto enemy = new AngryEnemy();
	enemy->position = { (float)(rand() % GetScreenWidth()), -size / 2.0f };
	enemy->size = { size, size };
	enemy->Velocity = { config.spawn.AngryEnemyXVelocityRange.RandomRange(),
						config.spawn.AngryEnemyYVelocityRange.RandomRange() };
	enemy->rotationSpeed = config.spawn.AngryEnemyRotationSpeed.RandomRange();

	angryEnemies.push_back(enemy);
	allGameObjects.push_back(enemy);

	return enemy;
}
void PlayState::UnLoad()
{
	app->SetMusic(nullptr);

	allGameObjects.remove_if(IGameObject::Destroy);
	bullets.clear();
	asteroids.clear();
	scaredEnemies.clear();
	angryEnemies.clear();
	shooterEnemies.clear();
}
void PlayState::Update(float deltaTime)
{
		UpdatePlayer(deltaTime);
		UpdateAsteroids(deltaTime);
		UpdateScaredEnemy(deltaTime);
		UpdateAngryEnemy(deltaTime);
		UpdateBullets(deltaTime);
		UpdateShooterEnemy(deltaTime);
		CheckCollisions();

		//Remove from objects from game when they are no longer active
		bullets.remove_if(IGameObject::isDead);
		asteroids.remove_if(IGameObject::isDead);
		scaredEnemies.remove_if(IGameObject::isDead);
		shooterEnemies.remove_if(IGameObject::isDead);
		angryEnemies.remove_if(IGameObject::isDead);

		allGameObjects.remove_if(IGameObject::destroyifDead);
}
void PlayState::UpdatePlayer(float deltaTime)
{
	player->Update(deltaTime);
}
void PlayState::UpdateAsteroids(float deltaTime)
{
	for (auto asteroid : asteroids)
	{
		asteroid->Update(deltaTime);
	}
	asteroidSpawnTime -= deltaTime;
	if (asteroidSpawnTime < 0)
	{
		CreateAsteroid();
		asteroidSpawnTime = asteroidSpawnTimeReset;
		asteroidSpawnTime -= config.spawn.asteroidSpawnTimeDecay;

		if (asteroidSpawnTimeReset < config.spawn.asteroidSpawnFrequency.min)
		{
			asteroidSpawnTimeReset = config.spawn.asteroidSpawnFrequency.min;
		}
	}
}
void PlayState::UpdateBullets(float deltaTime)
{
	for (auto bullet : bullets)
	{
		bullet->Update(deltaTime);
	}
}
void PlayState::CheckCollisions()
{
	for (auto iterA = allGameObjects.begin(); iterA != allGameObjects.end(); iterA++)
	{
		for (auto iterB = std::next(iterA); iterB != allGameObjects.end(); iterB++)
		{
			IGameObject* objA = *iterA;
			IGameObject* objB = *iterB;

			float distance = (objA->position - objB->position).Length();
			float aRadius = objA->size.x / 2.0f;
			float bRadius = objB->size.x / 2.0f;

			if (distance < aRadius + bRadius)
			{
				OnCollision(objA, objB);
			}
		}
	}
}
void PlayState::OnCollision(IGameObject* objA, IGameObject* objB)
{
	//Player vs Bullet
	if (objA->type == GameObjectTypes::PLAYER && objB->type == GameObjectTypes::BULLET) OnPlayerBulletCollision((Player*)objA, (Bullet*)objB);
	if (objB->type == GameObjectTypes::PLAYER && objA->type == GameObjectTypes::BULLET) OnPlayerBulletCollision((Player*)objB, (Bullet*)objA);
	//Player vs Asteroid
	if (objA->type == GameObjectTypes::PLAYER && objB->type == GameObjectTypes::ASTEROID) OnPlayerAsteroidCollision((Player*)objA, (Asteroid*)objB);
	if (objB->type == GameObjectTypes::PLAYER && objA->type == GameObjectTypes::ASTEROID) OnPlayerAsteroidCollision((Player*)objB, (Asteroid*)objA);
	//Player vs ScaredEnemy
	if (objA->type == GameObjectTypes::PLAYER && objB->type == GameObjectTypes::SCARED_ENEMY) OnPlayerScaredEnemyCollision((Player*)objA, (ScaredEnemy*)objB);
	if (objB->type == GameObjectTypes::PLAYER && objA->type == GameObjectTypes::SCARED_ENEMY) OnPlayerScaredEnemyCollision((Player*)objB, (ScaredEnemy*)objA);
	//Player vs AngryEnemy
	if (objA->type == GameObjectTypes::PLAYER && objB->type == GameObjectTypes::ANGRY_ENEMY) OnPlayerAngryEnemyCollision((Player*)objA, (AngryEnemy*)objB);
	if (objB->type == GameObjectTypes::PLAYER && objA->type == GameObjectTypes::ANGRY_ENEMY) OnPlayerAngryEnemyCollision((Player*)objB, (AngryEnemy*)objA);
	//Player vs ShooterEnemy
	if (objA->type == GameObjectTypes::PLAYER && objB->type == GameObjectTypes::SHOOTER_ENEMY) OnPlayerShooterEnemyCollision((Player*)objA, (ShooterEnemy*)objB);
	if (objB->type == GameObjectTypes::PLAYER && objA->type == GameObjectTypes::SHOOTER_ENEMY) OnPlayerShooterEnemyCollision((Player*)objB, (ShooterEnemy*)objA);
	//Bullet vs Asteroid
	if (objA->type == GameObjectTypes::BULLET && objB->type == GameObjectTypes::ASTEROID) OnBulletAsteroidCollision((Bullet*)objA, (Asteroid*)objB);
	if (objB->type == GameObjectTypes::BULLET && objA->type == GameObjectTypes::ASTEROID) OnBulletAsteroidCollision((Bullet*)objB, (Asteroid*)objA);
	//Bullet vs ScaredEnemy
	if (objA->type == GameObjectTypes::BULLET && objB->type == GameObjectTypes::SCARED_ENEMY) OnBulletScaredEnemyCollision((Bullet*)objA, (ScaredEnemy*)objB);
	if (objB->type == GameObjectTypes::BULLET && objA->type == GameObjectTypes::SCARED_ENEMY) OnBulletScaredEnemyCollision((Bullet*)objB, (ScaredEnemy*)objA);
	//Bullet vs ShooterEnemy
	if (objA->type == GameObjectTypes::BULLET && objB->type == GameObjectTypes::SHOOTER_ENEMY) OnBulletShooterEnemyCollision((Bullet*)objA, (ShooterEnemy*)objB);
	if (objB->type == GameObjectTypes::BULLET && objA->type == GameObjectTypes::SHOOTER_ENEMY) OnBulletShooterEnemyCollision((Bullet*)objB, (ShooterEnemy*)objA);
	//Bullet vs AngryEnemy
	if (objA->type == GameObjectTypes::BULLET && objB->type == GameObjectTypes::ANGRY_ENEMY) OnBulletAngryEnemyCollision((Bullet*)objA, (AngryEnemy*)objB);
	if (objB->type == GameObjectTypes::BULLET && objA->type == GameObjectTypes::ANGRY_ENEMY) OnBulletAngryEnemyCollision((Bullet*)objB, (AngryEnemy*)objA);
}
void PlayState::OnPlayerBulletCollision(Player* player, Bullet* bullets)
{
	if (bullets->bulletType == BulletType::PLAYER)
		return;
	PlaySound(Assets::sndExplosion2);
	player->Hurt();
	DealDamage(config.damage.playerBulletHit);
	DestroyBullet(bullets);
}
void PlayState::OnPlayerAsteroidCollision(Player* player, Asteroid* asteroid)
{
	PlaySound(Assets::sndExplosion2);
	player->Hurt();
	DealDamage(config.damage.playerAsteroidHit);
	DestroyAsteroid(asteroid);
}
void PlayState::OnPlayerScaredEnemyCollision(Player* player, ScaredEnemy* enemy)
{
	PlaySound(Assets::sndExplosion2);
	player->Hurt();
	DealDamage(config.damage.playerScaredHit);
	enemy->RunAway();
}
void PlayState::OnPlayerAngryEnemyCollision(Player* player, AngryEnemy* enemy)
{
	PlaySound(Assets::sndExplosion2);
	player->Hurt();
	DealDamage(config.damage.playerAngryHit);
	enemy->ChargeTowards();
}
void PlayState::OnPlayerShooterEnemyCollision(Player* player, ShooterEnemy* enemy)
{
	PlaySound(Assets::sndExplosion2);
	player->Hurt();
	DealDamage(config.damage.playerShooterHit);
}
void PlayState::OnBulletAsteroidCollision(Bullet* bullets, Asteroid* asteroid)
{
	PlaySound(Assets::sndExplode1);

	IncreaseScore(config.score.asteroid_hit);
	DestroyBullet(bullets);
	DestroyAsteroid(asteroid);
}
void PlayState::OnBulletScaredEnemyCollision(Bullet* bullets, ScaredEnemy* enemy)
{
	if (bullets->bulletType == BulletType::ENEMY)
		return;
	PlaySound(Assets::sndExplode1);
	IncreaseScore(config.score.scaredEnemy_hit);
	DestroyBullet(bullets);

	enemy->RunAway();

}
void PlayState::OnBulletShooterEnemyCollision(Bullet* bullets, ShooterEnemy* enemy)
{
	if (bullets->bulletType == BulletType::ENEMY)
		return;
	PlaySound(Assets::sndExplode1);
	IncreaseScore(config.score.shooterEnemy_hit);
	DestroyBullet(bullets);
	DestroyShooterEnemy(enemy);
}
void PlayState::OnBulletAngryEnemyCollision(Bullet* bullets, AngryEnemy* enemy)
{
	if (bullets->bulletType == BulletType::ENEMY)
		return;
	PlaySound(Assets::sndExplode1);
	IncreaseScore(config.score.scaredEnemy_hit);
	DestroyBullet(bullets);

	enemy->ChargeTowards();
}
void PlayState::DestroyAsteroid(Asteroid* asteroid)
{
	asteroid->rotationSpeed *= 2.0f;
	asteroid->size.x *= 0.75f;
	asteroid->size.y *= 0.75f;

	if (asteroid->size.x < 30)
		asteroid->isAlive = false;
}
void PlayState::DestroyBullet(Bullet* bullet)
{
	bullet->isAlive = false;
}
void PlayState::IncreaseScore(int amount)
{
	score += 10;
}
void PlayState::DestroyShooterEnemy(ShooterEnemy* enemy)
{
	enemy->isAlive = false;
}
void PlayState::UpdateScaredEnemy(float deltaTime)
{
	for (auto enemy : PlayState::scaredEnemies)
	{
		enemy->Update(deltaTime);
	}
	if (lives > 2)
		return;

	scaredEnemySpawnTime -= deltaTime;
	if (scaredEnemySpawnTime < 0.0f)
	{
		CreateScaredEnemy();
		scaredEnemySpawnTime = scaredEnemySpawnReset;
		scaredEnemySpawnReset -= config.spawn.ScaredEnemySpawnTimeDecay;

		if (scaredEnemySpawnReset < config.spawn.ScaredEnemySpawnFrequency.min)
		{
			scaredEnemySpawnReset = config.spawn.ScaredEnemySpawnFrequency.min;
		}
	}
}
void PlayState::UpdateShooterEnemy(float deltaTime)
{

	if (lives > 1)
		return;

		for (auto enemy : shooterEnemies)
		{
			enemy->Update(deltaTime);
		}
		shooterEnemySpawnTime -= deltaTime;
		if (shooterEnemySpawnTime < 0.0f)
		{
			CreateShooterEnemy();
			shooterEnemySpawnTime = shooterEnemyTimeReset;
			shooterEnemyTimeReset -= config.spawn.shooterEnemySpawnDecay;

			if (shooterEnemyTimeReset < config.spawn.shooterEnemySpawnFrequency.min)
			{
				shooterEnemyTimeReset = config.spawn.shooterEnemySpawnFrequency.max;
			}

		}
}
void PlayState::UpdateAngryEnemy(float deltaTime)
{
	for (auto enemy : PlayState::angryEnemies)
	{
		enemy->Update(deltaTime);
	}
	if (lives > 2)
		return;

	AngryEnemySpawnTime -= deltaTime;
	if (AngryEnemySpawnTime < 0.0f)
	{
		CreateAngryEnemy();
		AngryEnemySpawnTime = AngryEnemySpawnReset;
		AngryEnemySpawnReset -= config.spawn.AngryEnemySpawnTimeDecay;

		if (AngryEnemySpawnReset < config.spawn.AngryEnemySpawnFrequency.min)
		{
			AngryEnemySpawnReset = config.spawn.AngryEnemySpawnFrequency.min;
		}
	}
}
void PlayState::Draw()
{
	DrawBullets();
	DrawPlayer();
	DrawScaredEnemies();
	DrawAsteroids();
	DrawShooterEnemies();
	DrawAngryEnemies();
	DrawGameUi();
}
void PlayState::DrawPlayer()
{
	//Draw the player
	player->Draw();
}
void PlayState::DrawGameUi()
{
	float infoHeight = config.ui.infopanelHeight;
	float maxoverlayTransparency = config.ui.maxoverlayTransparency;
	float maxhealthbarTransparency = config.ui.maxoverlmaxhealthbarTransparencyayTransparency;

	float healthpercentage = health / (float)config.player.maxHealth;
	if (lives <= 0)
	{
		Color redOverlayColor = { 255, 0, 0, (int)(maxoverlayTransparency * 255 * (1.0f - healthpercentage)) };
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() - infoHeight, redOverlayColor);
	}
	std::string strScore = std::to_string(score);
	DrawInfoPanel(strScore.c_str());

	//Draw healthbar
	Color healthbarcolor = { 255, 0, 0, (int)(maxhealthbarTransparency * 255 )};
	DrawRectangle(0, GetScreenHeight() - infoHeight + 1 , GetScreenWidth() * healthpercentage, 20, healthbarcolor);

	//Draw lives
	for (int i = 0; i < lives; i++)
	{
		DrawTexture(Assets::imgPlayerLifeIcon,
			10 + (i * Assets::imgPlayerLifeIcon.width),
			GetScreenHeight() - infoHeight - (Assets::imgPlayerLifeIcon.height / 2.0f),
			WHITE);
	}
}
void PlayState::DrawBullets()
{
	for (auto bullet : bullets)
	{
		bullet->Draw();
	}
}
void PlayState::DrawScaredEnemies()
{
	for (auto enemy : scaredEnemies)
	{
		enemy->Draw();
	}
}
void PlayState::DrawAsteroids()
{
	for (auto asteroid : asteroids)
	{
		asteroid->Draw();
	}
}
void PlayState::DrawAngryEnemies()
{
	for (auto enemy : angryEnemies)
	{
		enemy->Draw();
	}
}
void PlayState::DrawShooterEnemies()
{
	for (auto enemy : shooterEnemies)
	{
		enemy->Draw();
	}
}
void PlayState::DealDamage(int amount)
{
	health -= amount;
	if (health < 0)
	{
		lives -= 1;
		health = config.player.maxHealth;

		if (lives < 0)
		{
			config.sharedGameData.score = score;
			app->ChangeState(EGameState::GAMEOVER);
		}
		else if (lives <= 0)
		{
			app->SetMusic(&Assets::musEndGame);
			PlayMusicStream(Assets::musEndGame);
		}
		else if (lives <= 1)
		{
			app->SetMusic(&Assets::musMidGame);
			PlayMusicStream(Assets::musMidGame);
		};
	};
};