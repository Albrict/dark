#pragma once

typedef void(*scene_proccess)(void*);
typedef void(*scene_update)(void*);
typedef void(*scene_draw)(const void*);
typedef void(*scene_destroy)(void*);

typedef struct Scene {
    scene_proccess proccess_callback;
    scene_update   update_callback;
    scene_draw     draw_callback;
    scene_destroy  destroy_callback;
    void    *data;
} Scene;

static inline void ProccessScene(Scene *scene)
{
    if (scene->proccess_callback)
        scene->proccess_callback(scene->data);
}

static inline void UpdateScene(Scene *scene)
{
    if (scene->update_callback)
        scene->update_callback(scene->data);
}

static inline void DrawScene(Scene *scene)
{
    if (scene->draw_callback)
        scene->draw_callback(scene->data);
}

static inline void DestroyScene(Scene *scene)
{
    if (scene->destroy_callback)
        scene->destroy_callback(scene->data);
}
