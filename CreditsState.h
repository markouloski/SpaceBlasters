#pragma once
#include "IGameState.h"
class CreditsState : public IGameState
{
public:
	CreditsState();
	virtual ~CreditsState();

	virtual void Load();
	virtual void UnLoad();
	virtual void Update(float deltaTime);
	virtual void Draw();
private:
protected:
};

