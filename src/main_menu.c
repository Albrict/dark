#include <raylib.h>
#include <stdlib.h>
#include "main_menu.h"
#include "game.h"
#include "graphics.h"
#include "text_button.h"
#include "widget.h"

typedef enum MainMenuWidgets {
    PLAY,
    LOAD,
    SETTINGS,
    QUIT,
    ALL_WIDGETS
} MainMenuWidgets;

typedef struct SceneData {
    Rectangle       menu_rect;
    Widget          widgets[4];
    MainMenuWidgets current_choosen_widget;
} SceneData;

static const Color UIRed = { 145, 75, 62, 255 };

static void ProccessMainMenu(void *data);
static void UpdateMainMenu(void *data);
static void DrawMainMenu(const void *data);
static void DestroyMainMenu(void *data);
static void QuitButtonCallback(void *data);

Scene CreateMainMenu(void)
{
    const float     width     = 250.f; 
    const float     height    = 270.f;
    const Rectangle menu_rect = {
        .x      = RENDER_AREA.width / 2.f - width / 2.f,
        .y      = height,
        .width  = width,
        .height = height
    };
    const float   initial_x            = menu_rect.x + menu_rect.width / 2.f - GetTextButtonWidth() / 2.f;
    const Vector2 play_button_position = {
        .x = initial_x,
        .y = menu_rect.y + 50.f
    };
    
    const Vector2 load_button_position = {
        .x = initial_x,
        .y = play_button_position.y + 50.f
    };
    
    const Vector2 settings_button_position = {
        .x = initial_x,
        .y = load_button_position.y + 50.f
    };

    const Vector2 quit_button_position = {
        .x = initial_x,
        .y = settings_button_position.y + 50.f
    };

    SceneData *data              = malloc(sizeof(SceneData));
    data->menu_rect              = menu_rect;
    data->widgets[PLAY]          = CreateTextButtonVec("Play", &play_button_position);
    data->widgets[LOAD]          = CreateTextButtonVec("Load", &load_button_position);
    data->widgets[SETTINGS]      = CreateTextButtonVec("Settings", &settings_button_position);
    data->widgets[QUIT]          = CreateTextButtonVec("Quit", &quit_button_position);
    data->current_choosen_widget = PLAY;

    SetWidgetCallback(&data->widgets[QUIT], QuitButtonCallback, NULL);
    return (Scene) {
        .proccess_callback = ProccessMainMenu,
        .update_callback   = UpdateMainMenu,
        .draw_callback     = DrawMainMenu,
        .destroy_callback  = DestroyMainMenu,
        .data              = data
    };
}

static void ProccessMainMenu(void *data)
{
    SceneData *scene_data = (SceneData*)(data); 
    if (IsKeyPressed(KEY_S) == true || IsKeyPressed(KEY_DOWN) == true) {
        TextButtonUnsetFocus(&scene_data->widgets[scene_data->current_choosen_widget]);
        if (scene_data->current_choosen_widget < ALL_WIDGETS - 1)
            ++scene_data->current_choosen_widget;
    }
    if (IsKeyPressed(KEY_W) == true || IsKeyPressed(KEY_UP) == true) {
        TextButtonUnsetFocus(&scene_data->widgets[scene_data->current_choosen_widget]);
        if (scene_data->current_choosen_widget > 0)
            --scene_data->current_choosen_widget;
    }
    if (IsTextButtonFocused(&scene_data->widgets[scene_data->current_choosen_widget]) == false)
        TextButtonSetFocus(&scene_data->widgets[scene_data->current_choosen_widget]);

    for (size_t i = 0; i < ALL_WIDGETS; ++i) {
        ProccessWidget(&scene_data->widgets[i]);
    }
}

static void UpdateMainMenu(void *data)
{
    SceneData *scene_data = (SceneData*)(data); 
    for (size_t i = 0; i < ALL_WIDGETS; ++i) {
        UpdateWidget(&scene_data->widgets[i]);
    }
}

static void DrawMainMenu(const void *data)
{
    const SceneData *scene_data = (const SceneData*)(data); 
    const Rectangle  rect       = scene_data->menu_rect;
    for (size_t i = 0; i < ALL_WIDGETS; ++i) {
        DrawWidget(&scene_data->widgets[i]);
    }
}

static void DestroyMainMenu(void *data)
{
    SceneData *scene_data = (SceneData*)(data);
    for (size_t i = 0; i < ALL_WIDGETS; ++i) {
        DestroyWidget(&scene_data->widgets[i]);
    }
    free(scene_data);
}

static void QuitButtonCallback(void *data)
{
    NotifyGame(GAME_EXIT);
}
