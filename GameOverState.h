#pragma once
#include "IGameState.h"
#include <string>
class GameOverState : public IGameState
{
public:
	GameOverState();
	virtual ~GameOverState();

	virtual void Load();
	virtual void UnLoad();
	virtual void Update(float deltaTime);
	virtual void Draw();
private:

	std::string name = "";

protected:
};
