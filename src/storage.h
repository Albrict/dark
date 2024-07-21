#pragma once
#include <assert.h>
#include "dynamic_array.h"
#include "dynamic_string.h"

typedef struct Storage {
    DynamicArray array;
    DynamicArray keys;
    unsigned int current_object;
} Storage;

static inline Storage CreateStorage(const unsigned int object_size, 
                                    const unsigned int initial_size)
{
    return (Storage) {
        .array          = CreateDynamicArray(object_size, initial_size),
        .keys           = CreateDynamicArray(sizeof(DynamicString), initial_size),
        .current_object = 0
    };
}

static inline void DestroyStorage(Storage *storage)
{
    for (unsigned int i = 0 ; i < storage->current_object; ++i)
        DestroyString(GetDataFromDynamicArray(&storage->keys, i));
    DestroyDynamicArray(&storage->keys);
    DestroyDynamicArray(&storage->array);
}

static inline void *GetDataFromStorageIndex(Storage *storage,   
                                            const unsigned int index)
{ 
    assert(index >= 0);
    assert(index <= storage->current_object);
    return GetDataFromDynamicArray(&storage->array, index); 
}

void *GetDataFromStorageKey(const Storage *storage, const DynamicString *string);
void PushDataIntoStorage(Storage *storage, void *data, const DynamicString *string);
