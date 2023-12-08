#pragma once

class Application;

enum EGameState
{
	NONE,
	MENU,
	PLAY,
	GAMEOVER,
	HIGHSCORE,
	CREDIT
};

class IGameState
{
public:
	Application* app = nullptr;
public:

	IGameState();
	virtual ~IGameState();

	virtual void Load();
	virtual void UnLoad();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void DrawTitleText();
	void DrawSubTitleText(const char* text);
	void DrawInfoPanel(const char* infoText);
protected:
private:
};