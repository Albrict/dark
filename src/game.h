#pragma once
#include <stdbool.h>

typedef enum GameEvent {
    GAME_EXIT,
} GameEvent;

bool StartGame(void);
void RunGame(void);
void CloseGame(void);

void NotifyGame(const GameEvent event);
