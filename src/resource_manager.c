#include <raylib.h>
#include <raylib-aseprite.h>
#include <stdbool.h>
#include <stddef.h>
#include "dynamic_array.h"
#include "dynamic_string.h"
#include "storage.h"
#include "resource_manager.h"

#define DEFAULT_STORAGE_SIZE 256
#define MUSIC_STORAGE_SIZE 24
#define FONT_STORAGE_SIZE 24

typedef struct AsepriteStorage {
    DynamicArray aseprites;
    DynamicArray names;
    unsigned int current_aseprite;  
} AsepriteStorage;

typedef struct AsepriteTagStorage {
    DynamicArray aseprite_tags;
    DynamicArray names;
    unsigned int current_aseprite_tag;
} AsepriteTagStorage;

typedef struct MusicStorage {
    DynamicArray musics;
    DynamicArray names;
    unsigned int current_music;
} MusicStorage;

typedef struct FontStorage {
    DynamicArray fonts;
    DynamicArray names;
    unsigned int current_font;
} FontStorage;

static bool InitStorages(void);
static bool InitAsepriteStorage(void);
static bool InitAsepriteTagStorage(void);
static bool InitMusicStorage(void);
static bool InitFontStorage(void);

static void DestroyStorages(void);
static void DestroyAsepriteStorage(void);
static void DestroyAsepriteTagStorage(void);
static void DestroyMusicStorage(void);
static void DestroyFontStorage(void);

static bool InsertAseprite(const char *path, const char *name);
static bool InsertAsepriteTag(const Aseprite *aseprite, const int id);
static bool InsertMusic(const char *path, const char *name);
static bool InsertFont(const char *path, const char *name);

//static Font                Becker               = {0};
static AsepriteStorage    aseprite_storage     = {0};
static AsepriteTagStorage aseprite_tag_storage = {0};
static MusicStorage       music_storage        = {0};
static FontStorage        font_storage         = {0};

bool LoadResources(void)
{
    InitStorages();
    if (InsertFont("assets/fonts/Becker.ttf", "Becker") == false)
        return false;
    return true;
}

void UnloadResources(void)
{
    DestroyStorages();
}

Font GetFont(const char *name)
{
    for (unsigned int i = 0; i < font_storage.current_font; ++i) {
        DynamicString *string = GetDataFromDynamicArray(&font_storage.names, i); 
        if (TextIsEqual(name, GetContents(string)) == true)
            return *(Font*)GetDataFromDynamicArray(&font_storage.fonts, i);
    }
    return (Font){0};
}

static bool InitStorages(void)
{
    InitAsepriteStorage();
    InitAsepriteTagStorage();
    InitMusicStorage();
    InitFontStorage();
    return true;
}

static bool InitAsepriteStorage(void)
{
    aseprite_storage.current_aseprite = 0;
    aseprite_storage.aseprites        = CreateDynamicArray(sizeof(Aseprite), 50);
    aseprite_storage.names            = CreateDynamicArray(sizeof(DynamicString), 50);
    return true;
}

static bool InitAsepriteTagStorage(void)
{
    aseprite_tag_storage.current_aseprite_tag = 0;
    aseprite_tag_storage.aseprite_tags        = CreateDynamicArray(sizeof(AsepriteTag), 50);
    aseprite_tag_storage.names                = CreateDynamicArray(sizeof(DynamicString), 50);
    return true;
}

static bool InitMusicStorage(void)
{
    music_storage.current_music = 0;
    music_storage.musics        = CreateDynamicArray(sizeof(Music), 50);
    music_storage.names         = CreateDynamicArray(sizeof(DynamicString), 50);
    return true;  
}

static bool InitFontStorage(void)
{
    font_storage.current_font = 0;
    font_storage.fonts        = CreateDynamicArray(sizeof(Font), 50);
    font_storage.names        = CreateDynamicArray(sizeof(DynamicString), 50);
    return true;
}

static void DestroyStorages(void)
{
    DestroyAsepriteStorage();
    DestroyAsepriteTagStorage();
    DestroyMusicStorage();
    DestroyFontStorage();
}

static bool InsertAseprite(const char *path, const char *name)
{
    const Aseprite aseprite = LoadAseprite(path);
    if (IsAsepriteReady(aseprite) == true) {
        const DynamicString string = CreateString(name);
        const int tags             = GetAsepriteTagCount(aseprite);
        if (tags > 0) {
            for (int i = 0; i < tags; ++i)
                InsertAsepriteTag(&aseprite, i);
        }
        PushDataToDynamicArray(&aseprite_storage.aseprites, &aseprite);
        PushDataToDynamicArray(&aseprite_storage.names, &string);
        ++aseprite_storage.current_aseprite;
        return true;
    }
    return false;
}

static bool InsertAsepriteTag(const Aseprite *aseprite, const int id)
{
    const AsepriteTag aseprite_tag = LoadAsepriteTagFromIndex(*aseprite, id);
    if (IsAsepriteTagReady(aseprite_tag) == true) {
        DynamicString string = CreateString(aseprite_tag.name);
        PushDataToDynamicArray(&aseprite_tag_storage.aseprite_tags, &aseprite_tag);
        PushDataToDynamicArray(&aseprite_tag_storage.names, &string);
        ++aseprite_tag_storage.current_aseprite_tag;
        return true;
    } 
    return false;
}

static bool InsertMusic(const char *path, const char *name)
{
    const Music music = LoadMusicStream(path);
    if (IsMusicReady(music) == true) {
        DynamicString string = CreateString(name);
        PushDataToDynamicArray(&music_storage.musics, &music);
        PushDataToDynamicArray(&music_storage.names, &string);
        ++music_storage.current_music;
        return true;
    } 
    return false;
}

static bool InsertFont(const char *path, const char *name)
{
    const Font font = LoadFont(path);
    if (IsFontReady(font) == true) {
        DynamicString string = CreateString(name);
        PushDataToDynamicArray(&font_storage.fonts, &font);
        PushDataToDynamicArray(&font_storage.names, &string);
        ++font_storage.current_font;
        return true;
    }
    return false;
}

static void DestroyAsepriteStorage(void)
{
    for (unsigned int i = 0; i < aseprite_storage.current_aseprite; ++i) {
        Aseprite      *aseprite = GetDataFromDynamicArray(&aseprite_storage.aseprites, i);
        DynamicString *string   = GetDataFromDynamicArray(&aseprite_storage.names, i);
        UnloadAseprite(*aseprite);
        DestroyString(string);
    }
    DestroyDynamicArray(&aseprite_storage.aseprites);
    DestroyDynamicArray(&aseprite_storage.names);
}

static void DestroyMusicStorage(void)
{
    for (unsigned int i = 0; i < music_storage.current_music; ++i) {
        Music         *music  = GetDataFromDynamicArray(&music_storage.musics, i);
        DynamicString *string = GetDataFromDynamicArray(&music_storage.names, i);
        
        UnloadMusicStream(*music);
        DestroyString(string);
    }
    DestroyDynamicArray(&music_storage.musics);
    DestroyDynamicArray(&music_storage.names);
}

static void DestroyAsepriteTagStorage(void)
{
    for (unsigned int i = 0; i < aseprite_tag_storage.current_aseprite_tag; ++i) {
        DynamicString *string = GetDataFromDynamicArray(&aseprite_tag_storage.names, i);
        DestroyString(string);
    }
    DestroyDynamicArray(&aseprite_tag_storage.aseprite_tags);
    DestroyDynamicArray(&aseprite_tag_storage.names);
}

static void DestroyFontStorage(void)
{
    for (unsigned int i = 0; i < font_storage.current_font; ++i) {
        Font          *font   = GetDataFromDynamicArray(&font_storage.fonts, i);
        DynamicString *string = GetDataFromDynamicArray(&font_storage.names, i);
        
        UnloadFont(*font);
        DestroyString(string);
    }
    DestroyDynamicArray(&font_storage.fonts);
    DestroyDynamicArray(&font_storage.names);
}
