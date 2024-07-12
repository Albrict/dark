#pragma once
#include <stdbool.h>

typedef struct _RenderArea {
    const int width; 
    const int height;
} RenderArea;

extern const RenderArea RENDER_AREA;

bool InitGraphics(void);
void CloseGraphics(void);
