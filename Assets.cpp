
#include "Assets.h"

Texture2D Assets::imgNull;
Texture2D Assets::imgBackground;
Texture2D Assets::imgPlayer;
Texture2D Assets::imgPlayerLaser;
Texture2D Assets::imgEnemyLaser;
Texture2D Assets::imgPlayerLifeIcon;
Texture2D Assets::imgAsteroidBrownBig1;
Texture2D Assets::imgScaredUFO;
Texture2D Assets::imgAgroUFO;
Texture2D Assets::imgShooterEnemy;
Texture2D Assets::imgCredits;

Font Assets::fntKenVector;
Font Assets::fntKenVectorThin;
Font Assets::fntOpenSansRegular;

Sound Assets::sndShoot;
Sound Assets::sndExplode1;
Sound Assets::sndExplosion2;

Music Assets::musMainMenu;
Music Assets::musEndGame;
Music Assets::musMidGame;
Music Assets::musBeginGame;
Music Assets::musGameOver;
Music Assets::musHighscores;
Music Assets::musCredits;

void Assets::LoadAssets()
{
	imgNull = LoadTexture("");
	imgBackground = LoadTexture("./assets/spaceshooter/Backgrounds/blue.png");
	imgPlayer = LoadTexture("./assets/spaceshooter/PNG/playerShip1_blue.png");
	imgPlayerLaser = LoadTexture("./assets/spaceshooter/PNG/Lasers/laserBlue07.png");
	imgEnemyLaser = LoadTexture("./assets/spaceshooter/PNG/Lasers/laserRed07.png");
	imgAsteroidBrownBig1 = LoadTexture("./assets/spaceshooter/PNG/Meteors/meteorBrown_big1.png");
	imgPlayerLifeIcon = LoadTexture("./assets/spaceshooter/PNG/UI/playerLife1_blue.png");
	imgScaredUFO = LoadTexture("./assets/spaceshooter/PNG/ufoYellow.png");
	imgAgroUFO = LoadTexture("./assets/spaceshooter/PNG/ufoRed.png");
	imgShooterEnemy = LoadTexture("./assets/spaceshooter/PNG/Enemies/enemyBlack1.png");
	imgCredits = LoadTexture("./assets/credits.png");

	fntKenVector = LoadFontEx("./assets/spaceshooter/Bonus/kenvector_future.ttf", 32, 0, 255);
	fntKenVectorThin = LoadFontEx("./assets/spaceshooter/Bonus/kenvector_future_thin.ttf", 32, 0, 255);
	fntOpenSansRegular = LoadFontEx("./assets/fonts/Open_Sans/OpenSans-Regular.ttf", 24, 0, 255);

	sndShoot = LoadSound("./assets/sfx/Audio/laserSmall_001.ogg");
	sndExplode1 = LoadSound("./assets/sfx/Audio/explosionCrunch_000.ogg");
	sndExplosion2 = LoadSound("./assets/sfx/Audio/explosionCrunch_003.ogg");

	musMainMenu = LoadMusicStream("./assets/music/SkyFire (Title Screen).ogg");
	musBeginGame = LoadMusicStream("./assets/music/Without Fear.ogg");
	musMidGame = LoadMusicStream("./assets/music/Rain of Lasers.ogg");
	musEndGame = LoadMusicStream("./assets/music/Epic End.ogg");
	musGameOver = LoadMusicStream("./assets/music/Victory Tune.ogg");
	musHighscores = LoadMusicStream("./assets/music/Space Heroes.ogg");
	musCredits = LoadMusicStream("./assets/music/Brave Pilots (Menu Screen).ogg");


	SetSoundVolume(sndShoot, 0.1);
	SetSoundVolume(sndExplode1, 0.1);
	SetSoundVolume(sndExplosion2, 0.1);

}

void Assets::UnloadAssets()
{
	UnloadMusicStream(musCredits);
	UnloadMusicStream(musHighscores);
	UnloadMusicStream(musGameOver);
	UnloadMusicStream(musEndGame);
	UnloadMusicStream(musMidGame);
	UnloadMusicStream(musBeginGame);
	UnloadMusicStream(musMainMenu);

	UnloadSound(sndExplosion2);
	UnloadSound(sndExplode1);
	UnloadSound(sndShoot);

	UnloadFont(fntOpenSansRegular);
	UnloadFont(fntKenVectorThin);
	UnloadFont(fntKenVector);

	UnloadTexture(imgCredits);
	UnloadTexture(imgShooterEnemy);
	UnloadTexture(imgAgroUFO);
	UnloadTexture(imgScaredUFO);
	UnloadTexture(imgPlayerLifeIcon);
	UnloadTexture(imgAsteroidBrownBig1);
	UnloadTexture(imgEnemyLaser);
	UnloadTexture(imgPlayerLaser);
	UnloadTexture(imgPlayer);
	UnloadTexture(imgBackground);
}
