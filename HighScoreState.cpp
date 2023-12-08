#include "HighScoreState.h"
#include "raylib.h"
#include "Application.h"
#include "Assets.h"
#include "ScoreEntry.h"
#include "Config.h"
HighScoreState::HighScoreState()
{

}
HighScoreState::~HighScoreState()
{

}

void HighScoreState::Load()
{
	app->SetMusic(&Assets::musHighscores);
	scores = ScoreEntry::Load(config.game.highscorefile);
}
void HighScoreState::UnLoad()
{
	app->SetMusic(nullptr);
}
void HighScoreState::Update(float deltaTime)
{
	if (IsKeyPressed(config.input.submitKey))
	{
		app->ChangeState(EGameState::MENU);
	}
}
void HighScoreState::Draw()
{
	DrawTitleText();
	DrawSubTitleText("HighScores");

	for (int i = 0; i < scores.size(); i++)
	{
		float itemHeight = 28;
		int seperation = 2;
		float yPos = 200 + i* (itemHeight + seperation);

		DrawRectangle(0, yPos, GetScreenWidth(), itemHeight, {255,255,255,25});

		DrawTextEx(Assets::fntKenVector, scores[i].name.c_str(), { 100.0f, yPos }, itemHeight, 0, WHITE);

		std::string scoreText = std::to_string(scores[i].score);
		auto ts = MeasureTextEx(Assets::fntKenVector, scoreText.c_str(), itemHeight, 0);
		DrawTextEx(Assets::fntKenVector, scoreText.c_str(), { GetScreenWidth() - 100.0f - ts.x, yPos }, itemHeight, 0, WHITE);
	}

	DrawInfoPanel("Enter to continue");
}