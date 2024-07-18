#pragma once
#include <raylib.h>

typedef struct RenderArea {
    const float width; 
    const float height;
} RenderArea;

extern const RenderArea RENDER_AREA;

bool InitGraphics(void);
void CloseGraphics(void);

void BeginRender(void);
void EndRender(void);

Vector2 GetCursorPosition(void);
