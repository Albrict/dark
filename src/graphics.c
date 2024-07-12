#include <raylib.h>
#include "graphics.h"

static RenderTexture target_texture  = {0};
static Vector2       cursor_position = {0};

const RenderArea RENDER_AREA = { .width = 1280, .height = 720 };

bool InitGraphics(void)
{
    const char *title = "Dark";
    InitWindow(GetScreenWidth(), GetScreenHeight(), title); 
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    target_texture = LoadRenderTexture(RENDER_AREA.width, RENDER_AREA.height);
    SetTextureFilter(target_texture.texture, TEXTURE_FILTER_POINT);
    if (IsRenderTextureReady(target_texture) == true) {
        TraceLog(LOG_INFO, "Graphics module initialized successfully");
        TraceLog(LOG_INFO, "Render width: %d", RENDER_AREA.width);
        TraceLog(LOG_INFO, "Render height: %d", RENDER_AREA.height);
        return true;
    } else {
        TraceLog(LOG_ERROR, "Graphics module failed to initialize target texture");
        return false;
    }
    return IsRenderTextureReady(target_texture);
}

void CloseGraphics(void)
{
    UnloadRenderTexture(target_texture);
}
