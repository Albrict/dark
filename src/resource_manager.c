#include <raylib.h>
#include <raylib-aseprite.h>
#include <stdbool.h>
#include <stddef.h>
#include "resource_manager.h"

#define DEFAULT_STORAGE_SIZE 256
#define MUSIC_STORAGE_SIZE 24
#define FONT_STORAGE_SIZE 24

typedef struct SoundStorage {
    Sound        sounds[DEFAULT_STORAGE_SIZE];
    const char  *names[DEFAULT_STORAGE_SIZE];
    unsigned int current_sound;  
} SoundStorage;

typedef struct AsepriteStorage {
    Aseprite    aseprites[DEFAULT_STORAGE_SIZE];
    const char *names[DEFAULT_STORAGE_SIZE];
    unsigned int current_aseprite;  
} AsepriteStorage;

typedef struct AsepriteTagStorage {
    AsepriteTag aseprite_tags[DEFAULT_STORAGE_SIZE];
    const char *names[DEFAULT_STORAGE_SIZE];
    unsigned int current_aseprite_tag;
} AsepriteTagStorage;

typedef struct MusicStorage {
    Music music[MUSIC_STORAGE_SIZE];
    const char *names[MUSIC_STORAGE_SIZE];
    unsigned int current_music;
} MusicStorage;

typedef struct FontStorage {
    Font fonts[FONT_STORAGE_SIZE];
    const char *names[FONT_STORAGE_SIZE];
    unsigned int current_font;
} FontStorage;

static bool InitStorages(void);
static void DestroyStorages(void);

static bool InsertSound(const char *path, const char *name);
static bool InsertAseprite(const char *path, const char *name);
static bool InsertAsepriteTag(const Aseprite *aseprite, const int id);
static bool InsertMusic(const char *path, const char *name);
static bool InsertFont(const char *path, const char *name);

//static Font                Becker               = {0};
static SoundStorage       *sound_storage        = NULL;
static AsepriteStorage    *aseprite_storage     = NULL;
static AsepriteTagStorage *aseprite_tag_storage = NULL;
static MusicStorage       *music_storage        = NULL;
static FontStorage        *font_storage         = NULL;

bool LoadResources(void)
{
    InitStorages();
    if (InsertFont("assets/fonts/Becker.ttf", "Becker") == false)
        return false;
    
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

void UnloadResources(void)
{
    DestroyStorages();
}

Font GetFont(const char *name)
{
    for (unsigned int i = 0; i < font_storage->current_font; ++i)
        if (TextIsEqual(name, font_storage->names[i]) == true)
            return font_storage->fonts[i];
    return (Font){0};
}

Sound GetSound(const char *name)
{
    for (unsigned int i = 0; i < sound_storage->current_sound; ++i)
        if (TextIsEqual(name, sound_storage->names[i]) == true)
            return LoadSoundAlias(sound_storage->sounds[i]);
    return (Sound){0};
}

static bool InitStorages(void)
{
    sound_storage        = MemAlloc(sizeof(SoundStorage));
    if (sound_storage == NULL)
        return false;
    aseprite_storage     = MemAlloc(sizeof(AsepriteStorage));
    if (aseprite_storage == NULL)
        return false;
    aseprite_tag_storage = MemAlloc(sizeof(AsepriteTagStorage));
    if (aseprite_tag_storage == NULL)
        return false;
    music_storage        = MemAlloc(sizeof(MusicStorage));
    if (music_storage == NULL)
        return false;
    font_storage         = MemAlloc(sizeof(FontStorage));
    if (font_storage == NULL)
        return false;

    sound_storage->current_sound               = 0;
    aseprite_storage->current_aseprite         = 0;
    aseprite_tag_storage->current_aseprite_tag = 0; 
    music_storage->current_music               = 0;
    font_storage->current_font                 = 0;
    return true;
}

static void DestroyStorages(void)
{
    for (unsigned int i = 0; i < sound_storage->current_sound; ++i)
        UnloadSound(sound_storage->sounds[i]);
    for (unsigned int i = 0; i < aseprite_storage->current_aseprite; ++i)
        UnloadAseprite(aseprite_storage->aseprites[i]);
    for (unsigned int i = 0; i < music_storage->current_music; ++i)
        UnloadMusicStream(music_storage->music[i]);
    for (unsigned int i = 0; i < font_storage->current_font; ++i)
        UnloadFont(font_storage->fonts[i]);
}

static bool InsertSound(const char *path, const char *name)
{
    const Sound sound = LoadSound(path);
    if (IsSoundReady(sound) == true) {
        sound_storage->sounds[sound_storage->current_sound] = sound;        
        sound_storage->names[sound_storage->current_sound]  = name;
        ++sound_storage->current_sound;
        return true;
    }
    return false;
}

static bool InsertAseprite(const char *path, const char *name)
{
    const Aseprite aseprite = LoadAseprite(path);
    if (IsAsepriteReady(aseprite) == true) {
        const int tags = GetAsepriteTagCount(aseprite);
        if (tags > 0) {
            for (int i = 0; i < tags; ++i)
                InsertAsepriteTag(&aseprite, i);
        }
        aseprite_storage->aseprites[aseprite_storage->current_aseprite] = aseprite;        
        aseprite_storage->names[aseprite_storage->current_aseprite]     = name;
        ++aseprite_storage->current_aseprite;
        return true;
    }
    return false;
}

static bool InsertAsepriteTag(const Aseprite *aseprite, const int id)
{
    const AsepriteTag aseprite_tag = LoadAsepriteTagFromIndex(*aseprite, id);
    if (IsAsepriteTagReady(aseprite_tag) == true) {
        aseprite_tag_storage->aseprite_tags[aseprite_tag_storage->current_aseprite_tag] = aseprite_tag;
        aseprite_tag_storage->names[aseprite_tag_storage->current_aseprite_tag]         = aseprite_tag.name;
        ++aseprite_tag_storage->current_aseprite_tag;
        return true;
    } 
    return false;
}

static bool InsertMusic(const char *path, const char *name)
{
    const Music music = LoadMusicStream(path);
    if (IsMusicReady(music) == true) {
        music_storage->music[music_storage->current_music] = music;        
        music_storage->names[music_storage->current_music] = name;
        ++music_storage->current_music;
        return true;
    } 
    return false;
}

static bool InsertFont(const char *path, const char *name)
{
    const Font font = LoadFont(path);
    if (IsFontReady(font) == true) {
        font_storage->fonts[font_storage->current_font] = font;
        font_storage->names[font_storage->current_font] = name;
        ++font_storage->current_font;
        return true;
    }
    return false;
}

