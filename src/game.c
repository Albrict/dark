#include <raylib.h>
#include <string.h>
#include "game.h"
#include "graphics.h"
#include "main_menu.h"
#include "resource_manager.h"

#define MAX_EVENTS 100

typedef struct Events {
    GameEvent    events[MAX_EVENTS];
    unsigned int current_event;
} Events;

static Events *events  = NULL;
static bool    running = false;

static void ProccessMessages(void);

bool StartGame(void)
{
    events = MemAlloc(sizeof(Events));
    if (events == NULL)
        return false;
    events->current_event = 0;

    bool result = InitGraphics();    
    if (result == false)
        return false;

    InitAudioDevice();
    result = LoadResources();
    if (result == false)
        return false;
    
    running = true;
    return true;
}

void RunGame(void)
{
    Scene main_menu = CreateMainMenu();
    while(running && !WindowShouldClose()) {
        ProccessMessages();
        ProccessScene(&main_menu);
        UpdateScene(&main_menu);
        BeginRender();
            ClearBackground(BLACK);
            DrawScene(&main_menu);
        EndRender();
    }
    DestroyScene(&main_menu);
}

void CloseGame(void)
{
    CloseAudioDevice();
    UnloadResources();
    CloseGraphics();
    CloseWindow();
}

void NotifyGame(const GameEvent event)
{
    events->events[events->current_event] = event;
    ++events->current_event;
}

static void ProccessMessages(void)
{
    for (unsigned int i = events->current_event; i > 0; --i) {
        GameEvent event = events->events[i];
        switch(event) {
        case GAME_EXIT:
            running = false;    
            break;
        default:
            break;
        }
    } 
}

