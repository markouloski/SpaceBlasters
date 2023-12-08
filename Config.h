#pragma once
#include "raylib.h"
#include <stdlib.h>
struct Config
{

	struct MinMax
	{
		float min = 0.0f;
		float max = 1.0f;

		float RandomRange()
		{
			float val = (float)rand() / RAND_MAX;
			float range = max - min;
			return val * range + min;
		}
	};
	struct Game
	{
		int windowWidth = 450;
		int windowHeight = 800;
		const char* windowTitle = "Space Blast";

		float bgMusicVolume = 0.1f;

		const char* highscorefile = "Highscore.txt";
	};
	Game game;

	struct Input
	{
		int upKey = KEY_UP;
		int downKey = KEY_DOWN;
		int leftKey = KEY_LEFT;
		int rightKey = KEY_RIGHT;
		int submitKey = KEY_ENTER;
		int shootKey = KEY_SPACE; 
	};
	Input input;

	struct Player
	{
		int max_lives = 3;
		int maxHealth = 100;
		float moveSpeed = 250;
		float bulletSpeed = 500;
	};

	Player player;

	struct Spawn
	{
		MinMax asteroidXVelocityRange = { -30, 30 };
		MinMax asteroidYVelocityRange = { -150, 150 };
		MinMax asteroidSizeRange = { 75, 150 };
		MinMax asteroidRotationSpeed = { -25, 500 };
		MinMax asteroidSpawnFrequency = { 1.0f, 2.0f };
		float asteroidSpawnTimeDecay = 0.9f;
		//Scared Enemy Spawns
		MinMax ScaredEnemyXVelocityRange = { -30, 30 };
		MinMax ScaredEnemyYVelocityRange = { 150, 150 };
		MinMax ScaredEnemySizeRange = { 100, 100 };
		MinMax ScaredEnemyRotationSpeed = { -100, 100 };
		MinMax ScaredEnemySpawnFrequency = { 1.0f, 4.0f };
		float ScaredEnemySpawnTimeDecay = 0.0;
		//Angry Enemy Spawns
		MinMax AngryEnemyXVelocityRange = { -30, 30 };
		MinMax AngryEnemyYVelocityRange = { 150, 150 };
		MinMax AngryEnemySizeRange = { 100, 100 };
		MinMax AngryEnemyRotationSpeed = { -100, 100 };
		MinMax AngryEnemySpawnFrequency = { 1.0f, 4.0f };
		float AngryEnemySpawnTimeDecay = 0.0;
		//Shooter enemy variables
		MinMax shooterEnemySpawnFrequency = { 1.0f, 4.0f };
		float shooterEnemySpawnDecay = 0.0f;
	};
	Spawn spawn;
	struct Enemy
	{
		float shooterEnemyYPos = 100;
		float shooterBulletSpeed = 500;
		float scaredEnemyRunSpeed = 300;
	};
	Enemy enemy;

	struct Ui
	{
		float infopanelHeight = 80;
		float maxoverlayTransparency = 0.3;
		float maxoverlmaxhealthbarTransparencyayTransparency = 0.5;
	};
	Ui ui;
	struct Damage
	{
		float playerAsteroidHit = 5.0f;
		float playerBulletHit = 10.0f;
		float playerScaredHit = 2.0f;
		float playerAngryHit = 900.0f;
		float playerShooterHit = 5.0f;
	};
	Damage damage;
	struct Score
	{
		float asteroid_hit = 10;
		float scaredEnemy_hit = 100;
		float shooterEnemy_hit = 300;
	};
	Score score;
	struct SharedData
	{
		int score = 0;
	};
	SharedData sharedGameData;
};
extern Config config;