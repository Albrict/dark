#pragma once
#include <raylib.h>

bool LoadResources(void);
void UnloadResources(void);

Font GetFont(const char *name);
Sound GetSound(const char *name);
