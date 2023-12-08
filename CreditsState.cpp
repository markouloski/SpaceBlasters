#include "CreditsState.h"
#include "raylib.h"
#include "Application.h"
#include "Assets.h"
#include "Config.h"
#include <vector>
#include <string>
CreditsState::CreditsState()
{

}
CreditsState::~CreditsState()
{

}

void CreditsState::Load()
{
	app->SetMusic(&Assets::musCredits);
	PlayMusicStream(Assets::musCredits);
}
void CreditsState::UnLoad()
{
	app->SetMusic(nullptr);
}
void CreditsState::Update(float deltaTime)
{
	if (IsKeyPressed(config.input.submitKey))
	{
		app->ChangeState(EGameState::MENU);
	}
}
void CreditsState::Draw()
{

	DrawTitleText();

	//Draw subtitle text
	DrawSubTitleText("Credits");

	std::vector<std::string> text = {
		"Jonny El Akar"
		"Developed at AIE"
		
		" 4/8/2022"
	};
	for (int i = 0; i < text.size(); i++)
	{
		auto ts = MeasureTextEx(Assets::fntOpenSansRegular, text[i].c_str(), 24, 0);
		DrawTextEx(
			Assets::fntOpenSansRegular,
			text[i].c_str(),
			{ GetScreenWidth() / 2.0f - ts.x / 2.0f, 200.0f + (i * 24) },
			24,
			0,
			WHITE
		);
	};

	DrawTexture(Assets::imgCredits, 0, 300, WHITE);

	DrawInfoPanel("Enter To Continue");
}
