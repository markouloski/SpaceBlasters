#include "Application.h"
#include <iostream>
#include "raylib.h"
#include "MenuState.h"
#include "Config.h"
#include "Assets.h"
#include "PlayState.h"
#include "CreditsState.h"
#include "GameOverState.h"
#include "HighScoreState.h"
Application::Application()
{

}
Application::~Application()
{

}
void Application::Run()
{

    std::cout << config.game.windowWidth << std::endl;
    std::cout << config.game.windowHeight << std::endl;

    InitWindow(config.game.windowWidth, config.game.windowHeight, config.game.windowTitle);
    InitAudioDevice();
    SetTargetFPS(60);

    Assets::LoadAssets();

    SetMusic( &Assets::musMainMenu );
    PlayMusicStream(Assets::musMainMenu);
    ChangeState(EGameState::MENU);

    bool paused = false;

    float bgXoffset = 0.0f;
    float bgYoffset = 0.0f;
    while (!WindowShouldClose() && shouldExit == false)
    {
        if (IsKeyPressed(KEY_P))
            paused != paused;
        if (!paused)
        {
            ChangeToNextState();
            float deltaTime = GetFrameTime();


            //scrolling background texture
            bgYoffset -= 1.0f;
            UpdateMusic(deltaTime);
            currentGameState->Update(deltaTime);

            if (IsKeyPressed(KEY_ONE))      ChangeState(EGameState::MENU);
            if (IsKeyPressed(KEY_TWO))      ChangeState(EGameState::PLAY);
            if (IsKeyPressed(KEY_THREE))    ChangeState(EGameState::GAMEOVER);
            if (IsKeyPressed(KEY_FOUR))     ChangeState(EGameState::HIGHSCORE);
            if (IsKeyPressed(KEY_FIVE))     ChangeState(EGameState::CREDIT);

            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();
            ClearBackground(RAYWHITE);
            //draw background texture 
            DrawTexturePro(
                Assets::imgBackground,
                { bgXoffset,bgYoffset, (float)GetScreenWidth(), (float)GetScreenHeight() },
                { 0,0, (float)GetScreenWidth(), (float)GetScreenHeight() },
                { 0,0 },
                0.0f,
                WHITE
            );
            if (paused)
                DrawText("Paused", 10, 10, 24, RAYWHITE);

            currentGameState->Draw();
            EndDrawing();
        }
    }
    currentGameState->UnLoad();
    Assets::UnloadAssets();

    CloseAudioDevice();
    CloseWindow();

}

void Application::ChangeToNextState()
{
    if (nextState == EGameState::NONE)
    {
        return;
    }
    if (currentGameState != nullptr)
    {
        currentGameState->UnLoad();
        delete currentGameState;
    }
    switch (nextState)
    {
    case EGameState::PLAY:       currentGameState = new PlayState(); break;
    case EGameState::MENU:       currentGameState = new MenuState(); break;
    case EGameState::HIGHSCORE:  currentGameState = new HighScoreState(); break;
    case EGameState::GAMEOVER:   currentGameState = new GameOverState(); break;
    case EGameState::CREDIT:     currentGameState = new CreditsState(); break;
    }
    currentGameState->app = this;
    currentGameState->Load();


    nextState = EGameState::NONE;
}
void Application::ChangeState(EGameState newState)
{
    nextState = newState;
}
void Application::UpdateMusic(float deltaTime)
{
    if (currentMusic != currentMusic)
    {
        musicVolume -= deltaTime;
        if (musicVolume <= 0.0f)
        {

            if (currentMusic != nullptr)
            {
                StopMusicStream(*currentMusic);
            }

            currentMusic = nextMusic;

            if (currentMusic != nullptr)
            {
                PlayMusicStream(*currentMusic);
            }
        }
        else {
            musicVolume += deltaTime;
            if (musicVolume > 1.0f)
            {
                musicVolume = 1.0f;
            }
        }
    }
    if (currentMusic != nullptr)
    {
        SetMusicVolume(*currentMusic, musicVolume * config.game.bgMusicVolume);
        UpdateMusicStream(*currentMusic);
    }
}
void Application::SetMusic(Music* newMusic)
{
    currentMusic = newMusic;
}
void Application::Quit()
{
    shouldExit = true;
}