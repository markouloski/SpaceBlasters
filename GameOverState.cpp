#include "GameOverState.h"
#include "raylib.h"
#include "Application.h"
#include "Assets.h"
#include "Config.h"
#include "ScoreEntry.h"
#include <string>
GameOverState::GameOverState()
{

}
GameOverState::~GameOverState()
{

}

void GameOverState::Load()
{
	app->SetMusic(&Assets::musGameOver);
	PlayMusicStream(Assets::musGameOver);
}
void GameOverState::UnLoad()
{
	app->SetMusic(nullptr);
}
void GameOverState::Update(float deltaTime)
{
	for (char c = 'A'; c <= 'Z'; c++)
	{
		if (IsKeyPressed(c))
		{
			name += c;
		}
	}
	if (IsKeyPressed(KEY_BACKSPACE) && name.empty() == false)
	{
		name.pop_back();
	}
	if (IsKeyPressed(KEY_ENTER) && name.empty() == false)
	{
		ScoreEntry::Save(config.game.highscorefile, {name.c_str(), config.sharedGameData.score});
		app->ChangeState(EGameState::HIGHSCORE);
	}
}
void GameOverState::Draw()
{
	Color redOverlayColor = { 255, 0, 0, (int)(config.ui.maxoverlayTransparency * 255) };
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() - config.ui.infopanelHeight, redOverlayColor);

	DrawTitleText();
	DrawSubTitleText("GameOver");
	
	std::string scoreText = std::to_string(config.sharedGameData.score);
	auto ts = MeasureTextEx(Assets::fntKenVectorThin, scoreText.c_str(), 24, 0);
	DrawTextEx(Assets::fntKenVectorThin, scoreText.c_str(), { (float)GetScreenWidth() / 2.0f - ts.x /2.0f,  200.0f }, 24, 0, WHITE);

	
	std::string enterYourNameText = "Enter Your Name";
    ts = MeasureTextEx(Assets::fntKenVector, enterYourNameText.c_str(), 32, 0);
	DrawTextEx(Assets::fntKenVector, enterYourNameText.c_str(), { (float)GetScreenWidth() / 2.0f - ts.x / 2.0f,  300.0f }, 32, 0, WHITE);

	ts = MeasureTextEx(Assets::fntKenVectorThin, name.c_str(), 32, 0);
	DrawTextEx(Assets::fntKenVectorThin, name.c_str(), { (float)GetScreenWidth() / 2.0f - ts.x / 2.0f,  340.0f }, 32, 0, WHITE);

	std::string EnterToContinue = "";
	if (name.empty() == false)
		EnterToContinue = "Enter to continue";

	DrawInfoPanel(EnterToContinue.c_str());
}