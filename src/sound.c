#include <raylib.h>
#include "sound.h"
#include "storage.h"

static Storage sound_storage = {0};
static bool InsertSound(const char *path, const char *name);

bool InitSound(void)
{
    InitAudioDevice();
    const unsigned int initial_size = 50;
    sound_storage = CreateStorage(sizeof(Sound), initial_size);

    if (InsertSound("assets/sound/ui/choose.wav", "Choose") == false)
            return false;
    if (InsertSound("assets/sound/ui/button_pressed.wav", "Pressed") == false)
            return false; 
    if (InsertSound("assets/sound/ui/button_pressed2.wav", "Pressed2") == false)
            return false;
    if (InsertSound("assets/sound/ui/button_pressed3.wav", "Pressed3") == false)
            return false;
    if (InsertSound("assets/sound/ui/ui_discard.wav", "Discard") == false)
            return false; 
    if (InsertSound("assets/sound/ui/ui_discard2.wav", "Discard2") == false)
            return false; 
    if (InsertSound("assets/sound/ui/ui_discard3.wav", "Discard3") == false)
            return false; 
    return true;
}

void CloseSound(void)
{
    for (unsigned int i = 0; i < sound_storage.current_object; ++i)
        UnloadSound(*(Sound*)GetDataFromStorageIndex(&sound_storage, i)); 
    CloseAudioDevice();
}

void PlayRandomPressedButtonSound(void)
{
    PlaySound(*(Sound*)GetDataFromStorageIndex(&sound_storage, (unsigned int)GetRandomValue(1, 3)));
}

void PlayInGameSound(const char *name)
{
    const DynamicString key = CreateString(name);
    PlaySound(*(Sound*)GetDataFromStorageKey(&sound_storage, &key));
}

static bool InsertSound(const char *path, const char *name)
{
    Sound sound = LoadSound(path);
    if (IsSoundReady(sound) == true) {
        const DynamicString key = CreateString(name);
        PushDataIntoStorage(&sound_storage, &sound, &key);
        return true;
    }
    return false;
}
