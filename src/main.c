#include <raylib.h>
#include <stdlib.h>
#include "game.h"

int main(int argc, const char **argv)
{
    const bool result = StartGame();
    if (result == false) {
        TraceLog(LOG_FATAL, "Can't start a game!");
        return EXIT_FAILURE;
    }
    RunGame();
    CloseGame();
    return EXIT_SUCCESS;
}
