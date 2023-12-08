#include "Player.h"
#include "raylib.h"
#include "Assets.h"
#include "Config.h"
#include "PlayState.h"
#include "Bullet.h"
Player::Player() : IGameObject()
{
	type = GameObjectTypes::PLAYER;

	world = nullptr;

	position.x = GetScreenWidth() / 2.0f;
	position.y = GetScreenHeight() - 150.0f;

	size.x = Assets::imgPlayer.width * 0.5f;
	size.y = Assets::imgPlayer.height * 0.5f;

	speed = config.player.moveSpeed;
};
Player::~Player()
{

};
void Player::Update(float deltaTime)
{

	if (IsKeyDown(config.input.leftKey))
	{
		position.x -= speed * deltaTime;
	}
	if (IsKeyDown(config.input.rightKey))
	{
		position.x += speed * deltaTime;
	}
	if (IsKeyDown(config.input.upKey))
	{
		position.y -= speed * deltaTime;
	}
	if (IsKeyDown(config.input.downKey))
	{
		position.y += speed * deltaTime;
	}

	if (IsKeyPressed(config.input.shootKey))
	{
		Shoot();
	};
	if (IsKeyPressed(KEY_E))
	{
		triple = !triple; 
	};
}

void Player::Draw()
{
	if (hurt == false)
	{
		DrawTexturePro(
			Assets::imgPlayer,
			{ 0, 0, (float)Assets::imgPlayer.width, (float)Assets::imgPlayer.height },
			{ position.x, position.y, size.x, size.y },
			{ size.x / 2.0f, size.y / 2.0f },
			0.0f,
			{ 255,255,255,255 }
		); 
	}
	else
	{
		DrawTexturePro(
			Assets::imgPlayer,
			{ 0, 0, (float)Assets::imgPlayer.width, (float)Assets::imgPlayer.height },
			{ position.x, position.y, size.x, size.y },
			{ size.x / 2.0f, size.y / 2.0f },
			0.0f,
			{ 255,0,0,255 }
		);
		hurt = false;
	}
}
void Player::Shoot()
{
	if (world != nullptr && triple == false)
	{
		world->CreateBullet(
			BulletType::PLAYER,
			position - Vec2{ 0, size.y / 2.0f },
			{ 0, -config.player.bulletSpeed }
		);
	}
	if (world != nullptr && triple == true)
	{
		world->CreateBullet(
			BulletType::PLAYER,
			position - Vec2{ 2, size.y / 2.0f },
			{ 30, -config.player.bulletSpeed*0.5f }
		);
		world->CreateBullet(
			BulletType::PLAYER,
			position - Vec2{ 0, size.y / 2.0f },
			{ 0, -config.player.bulletSpeed*0.5f }
		);
		world->CreateBullet(
			BulletType::PLAYER,
			position - Vec2{ -2, size.y / 2.0f },
			{ -30, -config.player.bulletSpeed*0.5f }
		);
	}
}
void Player::Hurt()
{
 hurt = true;
}