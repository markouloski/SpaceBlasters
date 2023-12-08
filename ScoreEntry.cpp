#include "ScoreEntry.h"
#include <fstream>
#include <algorithm>

void ScoreEntry::Save(const char* filename, ScoreEntry entry)
{
	std::ofstream file;
	file.open(filename, std::ios::app);

	if (file.is_open() == false)
		return;

	file << entry.name << std::endl;
	file << entry.score << std::endl;

	file.close();
}
 std::vector<ScoreEntry> ScoreEntry::Load(const char* filename)
{
	 std::vector<ScoreEntry> scores;

	 std::ifstream file;
	 file.open(filename);

	 if (file.is_open() == false)
		 return scores;

	 while (file.eof() == false)
	 {
		 ScoreEntry entry;
		 file >> entry.name;
		 file >> entry.score;
		 
		 if (entry.name == "")
			 break;
		 scores.push_back(entry);
	 }

	 std::sort(scores.begin(), scores.end(), [](auto a, auto b) {
		 return a.score > b.score;
		 });

	 file.close();

	 return scores;
}