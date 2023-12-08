#pragma once
#include "raylib.h"
#include "IGameState.h"
class Application
{
public:

	Application();
	~Application();

	void Run();

	void ChangeState(EGameState newState);
	void ChangeToNextState();

	void UpdateMusic(float deltaTime);
	void SetMusic(Music* newMusic);

	void Quit();

protected:
private:

	IGameState* currentGameState = nullptr;
	EGameState nextState = EGameState::NONE;


	Music* currentMusic = nullptr;
	Music* nextMusic = nullptr;
	float musicVolume = 1.0f;

	bool shouldExit = false;

};