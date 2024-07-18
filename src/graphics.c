#include "graphics.h"

static RenderTexture target_texture  = {0};
static Vector2       cursor_position = {0};

const RenderArea RENDER_AREA = { .width = 1280, .height = 720 };

bool InitGraphics(void)
{
    const char *title = "Dark";
    InitWindow(GetScreenWidth(), GetScreenHeight(), title); 
    SetTargetFPS(120);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    target_texture = LoadRenderTexture((int)RENDER_AREA.width, (int)RENDER_AREA.height);
    SetTextureFilter(target_texture.texture, TEXTURE_FILTER_TRILINEAR);
    if (IsRenderTextureReady(target_texture) == true) {
        TraceLog(LOG_INFO, "Graphics module initialized successfully");
        TraceLog(LOG_INFO, "Render width: %d", RENDER_AREA.width);
        TraceLog(LOG_INFO, "Render height: %d", RENDER_AREA.height);
        return true;
    } else {
        TraceLog(LOG_ERROR, "Graphics module failed to initialize target texture");
        return false;
    }
}

void CloseGraphics(void)
{
    UnloadRenderTexture(target_texture);
}

void BeginRender(void)
{
    cursor_position.x = (float)GetMouseX() * RENDER_AREA.width / (float)GetScreenWidth();
    cursor_position.y = (float)GetMouseY() * RENDER_AREA.height / (float)GetScreenHeight();
    BeginTextureMode(target_texture);
}

void EndRender(void)
{
    EndTextureMode();
    BeginDrawing();
        ClearBackground(BLACK);
        const Rectangle source_rect = { 
            0.f, 0.f, 
            RENDER_AREA.width,
            -RENDER_AREA.height
        };
        const Rectangle dest_rect = {
            0.f, 0.f,
            (float)GetScreenWidth(),
            (float)GetScreenHeight()
        };
        DrawTexturePro(target_texture.texture, source_rect, dest_rect, (Vector2){0}, 0.f, 
                       WHITE);
    EndDrawing();
}

Vector2 GetCursorPosition(void)
{
    return cursor_position;
}
