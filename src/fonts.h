#pragma once
#include "raylib.h"
#include "resource_manager.h"
#include "constants.h"

static inline Vector2 GetBeckerTextSizeEx(const char *text, const float font_size, const float spacing)
{
    return MeasureTextEx(GetFont("Becker"), text, font_size, spacing);
}

static inline Vector2 GetBeckerTextSize(const char *text)
{
    return MeasureTextEx(GetFont("Becker"), text, DEFAULT_FONT_SIZE, DEFAULT_SPACING_SIZE);
}
