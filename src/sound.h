#pragma once
#include "resource_manager.h"

static inline Sound GetRandomButtonPressSound(void)
{
    Sound sounds[3] = {
        GetSound("Pressed"),
        GetSound("Pressed2"),
        GetSound("Pressed3")
    };
    return sounds[GetRandomValue(0, 2)];
}
