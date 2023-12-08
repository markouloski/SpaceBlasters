#pragma once

namespace UnitTests
{
	bool saveAndLoadHighScore_Tests();


	bool LoadScores_ReturnEmptyListWhenFileNotFound_Test();

	bool LoadScores_ReturnsEmptyListWhenFileIsEmpty_Test();
}