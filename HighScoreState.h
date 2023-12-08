#pragma once
#include "IGameState.h"
#include <vector>
#include "ScoreEntry.h"
class HighScoreState : public IGameState
{
public:
	HighScoreState();
	virtual ~HighScoreState();

	virtual void Load();
	virtual void UnLoad();
	virtual void Update(float deltaTime);
	virtual void Draw();
private:
protected:

	std::vector<ScoreEntry> scores;
};
