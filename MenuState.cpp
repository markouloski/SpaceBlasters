#include "MenuState.h"
#include "raylib.h"
#include "Application.h"
#include "Config.h"
#include "Assets.h"
MenuState::MenuState()
{

}
MenuState::~MenuState()
{

}
void MenuState::Load()
{
	app->SetMusic(&Assets::musMainMenu);

	menuItems.push_back("Play Game");
	menuItems.push_back("High Scores");
	menuItems.push_back("Credits");
	menuItems.push_back("Quit");
}
void MenuState::UnLoad()
{
	app->SetMusic(nullptr);
}
void MenuState::Update(float deltaTime)
{
	
	if (IsKeyPressed(config.input.downKey))
	{
		menuSelectedIndex += 1;
		if (menuSelectedIndex >= menuItems.size())
		{
			menuSelectedIndex = menuItems.size() - 1;
		}
	}
	if (IsKeyPressed(config.input.upKey))
	{
		menuSelectedIndex -= 1;
		if (menuSelectedIndex < 0)
		{
			menuSelectedIndex = 0;
		}

		if (IsKeyPressed(config.input.submitKey))
		{
			if (menuSelectedIndex == 0)
			{
				app->ChangeState(EGameState::PLAY);
			}
			else if (menuSelectedIndex == 1)
			{
				app->ChangeState(EGameState::HIGHSCORE);
			}
			else if (menuSelectedIndex == 2)
			{
				app->ChangeState(EGameState::CREDIT);
			}
			else if (menuSelectedIndex == 3)
			{
				app->Quit();
			}
		}
	}
}
void MenuState::Draw()
{
	
	DrawTitleText();
	for (int i = 0; i < menuItems.size(); i++)
	{
		if (menuSelectedIndex == i)
		{
			DrawRectangle(0, 370 + (i * 36.0f) - 3.0f, GetScreenWidth(), 36, { 255, 255, 255, 25 });
		}

		auto ts = MeasureTextEx(Assets::fntKenVectorThin, menuItems[i].c_str(), 32, 0);
		DrawTextEx(Assets::fntKenVectorThin, menuItems[i].c_str(), { GetScreenWidth() / 2.0f - ts.x / 2.0f, 370 + (i * 36.0f) }, 32, 0, WHITE);
	};
}