#include <raylib.h>
#include "game.h"
#include "graphics.h"

bool StartGame(void)
{
    bool result = InitGraphics();    
    if (result == false)
        return false;
    return true;
}

void RunGame(void)
{
    while(!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(BLACK);
        }
        EndDrawing();
    }
}

void CloseGame(void)
{
    CloseGraphics();
    CloseWindow();
}
