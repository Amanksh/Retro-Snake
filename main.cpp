#include <iostream>
#include <raylib.h>
using namespace std;

int main()
{
    InitWindow(750, 750, "retro snake game");
    SetTargetFPS(60);
    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}