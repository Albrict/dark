#include <flecs.h>
#include <raylib.h>
#include "world.h"

static ecs_world_t *world = nullptr;

bool InitWorld(void)
{
    ecs_log_set_level(0);
    world = ecs_init(); 
    if (world == NULL)
        return false;
    else
        return true;
}

ecs_world_t *GetWorld()
{
    return world;
}

void DestroyWorld(void)
{
    ecs_fini(world);
}

void ProgressWorld()
{
    ecs_progress(world, GetFrameTime()); 
}
