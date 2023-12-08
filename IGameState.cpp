#include "IGameState.h"
#include "Assets.h"
#include "Config.h"
#include "raylib.h"
#include "MenuState.h"

IGameState::IGameState()
{

}
IGameState::~IGameState()
{

}
void IGameState::Load()
{

}
void IGameState::UnLoad()
{

}
void IGameState::Update(float deltaTime)
{

}
void IGameState::Draw()
{

}
void IGameState::DrawTitleText()
{
	auto ts = MeasureTextEx(Assets::fntKenVector, config.game.windowTitle, 42, 0);

	DrawTextEx(Assets::fntKenVector, config.game.windowTitle, { GetScreenWidth() / 2.0f - ts.x / 2.0f, 100 }, 42,0, WHITE);
}
void IGameState::DrawSubTitleText(const char* text)
{
	auto ts = MeasureTextEx(Assets::fntKenVector, text, 32, 0);
	DrawTextEx(Assets::fntKenVector, text, { GetScreenWidth() / 2.0f - ts.x / 2.0f, 142 }, 32, 0, WHITE);
}
void IGameState::DrawInfoPanel(const char* infoText)
{
	float infoHeight = config.ui.infopanelHeight;
	DrawRectangle(0, GetScreenHeight() - infoHeight, GetScreenWidth(), infoHeight, { 0, 0, 0, 128 });

	DrawLine(0, GetScreenHeight() - infoHeight, GetScreenWidth(), GetScreenHeight() - infoHeight, WHITE);

	auto ts = MeasureTextEx(Assets::fntKenVector, infoText, 32, 0);
	DrawTextEx(Assets::fntKenVector, infoText, { GetScreenWidth() / 2.0f - ts.x / 2.0f, GetScreenHeight() - infoHeight + 30 }, 32, 0, WHITE);
}