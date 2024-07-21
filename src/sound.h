#pragma once
#include <stdbool.h>

bool InitSound(void);
void PlayInGameSound(const char *name);
void PlayRandomPressedButtonSound(void);
void CloseSound(void);
