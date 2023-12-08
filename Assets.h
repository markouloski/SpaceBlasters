#pragma once
#include "raylib.h"

namespace Assets
{
	void LoadAssets();
	void UnloadAssets();


	// TODO: Define Textures
	// -------------------------------
	extern Texture2D imgNull;
	extern Texture2D imgBackground;
	extern Texture2D imgPlayer;
	extern Texture2D imgPlayerLaser;
	extern Texture2D imgEnemyLaser;
	extern Texture2D imgAsteroidBrownBig1;
	extern Texture2D imgPlayerLifeIcon;
	extern Texture2D imgScaredUFO;
	extern Texture2D imgAgroUFO;
	extern Texture2D imgShooterEnemy;
	extern Texture2D imgCredits;

	// TODO: Define Fonts
	// -------------------------------
	extern Font fntKenVector;
	extern Font fntKenVectorThin;
	extern Font fntOpenSansRegular;

	// TODO: Define Sound Effects
	// -------------------------------
	extern Sound sndShoot;
	extern Sound sndExplode1;
	extern Sound sndExplosion2;

	// TODO: Define Music
	// -------------------------------
	extern Music musMainMenu;
	extern Music musEndGame;
	extern Music musMidGame;
	extern Music musBeginGame;
	extern Music musGameOver;
	extern Music musHighscores;
	extern Music musCredits;

}
