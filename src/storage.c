#include <raylib.h>
#include "storage.h"


void *GetDataFromStorageKey(const Storage *storage, const DynamicString *string)
{
    for (unsigned int i = 0; i < storage->current_object; ++i) {
        DynamicString *key = GetDataFromDynamicArray(&storage->keys, i);
        if (TextIsEqual(GetContents(key), GetContents(string)))
            return GetDataFromDynamicArray(&storage->array, i);
    }
    return NULL;
}

void PushDataIntoStorage(Storage *storage, void *data, const DynamicString *string)
{
    PushDataToDynamicArray(&storage->keys, string); 
    PushDataToDynamicArray(&storage->array, data);
    ++storage->current_object;
}
