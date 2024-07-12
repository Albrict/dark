#pragma once

typedef struct ecs_world_t ecs_world_t;
[[nodiscard]] bool InitWorld();
void ProgressWorld();
void DestroyWorld();

[[nodiscard]] ecs_world_t *GetWorld();
