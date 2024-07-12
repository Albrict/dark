#include <raylib.h>
#include <flecs.h>

#include "game.h"
#include "graphics.h"
#include "world.h"

static void move(ecs_iter_t *it)
{
    Rectangle *rect = ecs_field(it, Rectangle, 1);
    for (int i = 0; i < it->count; ++i)
        rect[i].x += 10.f * GetFrameTime();
}

bool StartGame(void)
{
    bool result = InitGraphics();    
    if (result == false)
        return false;

    result = InitWorld();
    if (result == false)
        return false;
    
    return true;
}

void RunGame(void)
{
    auto world = GetWorld();
    ECS_COMPONENT(world, Rectangle);
    ECS_SYSTEM(world, move, EcsOnUpdate, Rectangle);
    auto base = ecs_new(world, Rectangle);
    ecs_set(world, base, Rectangle, {500.f, 500.f, 200.f, 200.f});
    while(!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(BLACK);
            ProgressWorld(); 
            const Rectangle *rect = ecs_get(world, base, Rectangle);
            DrawRectangleRec(*rect, RED);
        }
        EndDrawing();
    }
}

void CloseGame(void)
{
    DestroyWorld();
    CloseGraphics();
    CloseWindow();
}
