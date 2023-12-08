#include "UnitTests.h"
#include <iostream>
#include "ScoreEntry.h"
#include <vector>
#include <stdio.h>

bool UnitTests::saveAndLoadHighScore_Tests()
{
	const char* filename = "Testfile.txt";

	remove(filename);

	//append scores to file
	ScoreEntry::Save(filename,	 {"BBB", 100 });
	ScoreEntry::Save ( filename, {"AAA", 1000});
	ScoreEntry::Save(filename,	 {"DDD", 1 });
	ScoreEntry::Save ( filename, {"CCC", 10});

	std::vector<ScoreEntry> scores = ScoreEntry::Load(filename);

	if (scores.size() != 4)
	{
		std::cout << "saveAndLoadHighScore_Test: Fail" << std::endl;
		std::cout << "Score has four values loaded" << std::endl;
		return false;
	}
	if (scores[0].name == "AAA" && scores[0].score == 1000 &&
		scores[1].name == "BBB" && scores[1].score == 100 &&
		scores[2].name == "CCC" && scores[2].score == 10 &&
		scores[3].name == "DDD" && scores[3].score == 1)
	{
		std::cout << "saveAndLoadHighScore_Test: Fail" << std::endl;
		std::cout << "Scores should be in the correct order" << std::endl;
		return false;
	}

	std::cout << "saveAndLoadHighScore_Test: Success" << std::endl;
	return true;
}
bool UnitTests::LoadScores_ReturnEmptyListWhenFileNotFound_Test()
{
	const char* filename = "Testfile.txt";

	remove(filename);
	try
	{
		std::vector<ScoreEntry> scores = ScoreEntry::Load(filename);
		if (scores.size() != 0)
		{
			std::cout << "LoadScores_ReturnEmptyListWhenFileNotFound_Test: Fail" << std::endl;
			std::cout << "there should be zero scores in the file" << std::endl;
			return false;
		}
	}
	catch (...)
	{
		std::cout << "LoadScores_ReturnEmptyListWhenFileNotFound_Test: Fail" << std::endl;
		std::cout << "there should be zero scores in the file" << std::endl;
		return false;
	}

	std::cout << "LoadScores_ReturnEmptyListWhenFileNotFound_Test: Success" << std::endl;
	return true;
}
bool UnitTests::LoadScores_ReturnsEmptyListWhenFileIsEmpty_Test()
{
	const char* filename = "Testfile.txt";

	FILE* file = fopen(filename, "w+");
	fclose(file);
	try
	{
		std::vector<ScoreEntry> scores = ScoreEntry::Load(filename);
		if (scores.size() != 0)
		{
			std::cout << "LoadScores_ReturnsEmptyListWhenFileIsEmpty_Test: Fail" << std::endl;
			std::cout << "there should be zero scores in the file" << std::endl;
			return false;
		}
	}
	catch (...)
	{
		std::cout << "LoadScores_ReturnsEmptyListWhenFileIsEmpty_Test: Fail" << std::endl;
		std::cout << "there should be zero scores in the file" << std::endl;
		return false;
	}

	std::cout << "LoadScores_ReturnsEmptyListWhenFileIsEmpty_Test: Success" << std::endl;
	return true;
}
