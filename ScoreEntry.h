#pragma once
#include <string>
#include <vector>

struct ScoreEntry
{
	std::string name;

	int score;

	static void Save(const char* filename, ScoreEntry entry);
	static std::vector<ScoreEntry> Load(const char* filename);

};