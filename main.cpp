#include "Application.h"
#include "Vec2.h"
#include "UnitTests.h"
int main(int argc, char* argv[])
{
    UnitTests::saveAndLoadHighScore_Tests();
    UnitTests::LoadScores_ReturnEmptyListWhenFileNotFound_Test();
    UnitTests::LoadScores_ReturnsEmptyListWhenFileIsEmpty_Test();
    Application app;
    app.Run();

    return 0;
}