#include <stddef.h>
#include <raylib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include "dynamic_array.h"

struct DynamicArray {
    unsigned char *data;
    unsigned int   size;
    unsigned int   size_in_bytes;
    unsigned int   object_size;
    unsigned int   current_element;
};

DynamicArray *CreateDynamicArray(const unsigned int object_size, const unsigned int size)
{
    DynamicArray *dynamic_array    = NULL;
    dynamic_array                  = MemAlloc(sizeof(DynamicArray));
    if (dynamic_array == NULL)
        return NULL;

    dynamic_array->size            = size;
    dynamic_array->object_size     = object_size;
    dynamic_array->size_in_bytes   = size * object_size;
    dynamic_array->current_element = 0;
    dynamic_array->data            = MemAlloc(sizeof(unsigned char) * size * object_size);
    return dynamic_array;
}

void DestroyDynamicArray(DynamicArray *dynamic_array)
{
    MemFree(dynamic_array->data); 
    dynamic_array = NULL;
}

void *GetDataFromDynamicArray(DynamicArray *dynamic_array, const unsigned int index)
{
    assert(index < dynamic_array->size && "GetDataFromDynamicArray: invalid index");
    assert(index <= dynamic_array->current_element);
    assert(index >= 0 && "GetDataFromDynamicArray: invalid index");
    
    return (dynamic_array->data + index * dynamic_array->object_size);
}

void PushDataToDynamicArray(DynamicArray *dynamic_array, void *data)
{
    const unsigned int object_size = dynamic_array->object_size;
    if (dynamic_array->current_element >= dynamic_array->size - 1) {
        dynamic_array->size          *= 2;
        dynamic_array->size_in_bytes  = dynamic_array->size * object_size;
        MemRealloc(dynamic_array->data, dynamic_array->size_in_bytes);     
    }
    memcpy(dynamic_array->data + dynamic_array->current_element * object_size, 
           data, object_size);
    ++dynamic_array->current_element;
}

void SetDataInDynamicArray(DynamicArray *dynamic_array, const unsigned int index, 
                           void *data)
{
    assert(index < dynamic_array->size && "GetDataFromDynamicArray: invalid index");
    assert(index > 0 && "GetDataFromDynamicArray: invalid index");
    
    const unsigned int object_size = dynamic_array->object_size;
    memcpy(dynamic_array->data + index * object_size, data, object_size);
}

bool IsDynamicArrayValid(const DynamicArray *dynamic_array)
{ return dynamic_array->data == NULL; }
