#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct DynamicArray DynamicArray;

DynamicArray *CreateDynamicArray(const unsigned int object_size, const unsigned int size);
void DestroyDynamicArray(DynamicArray *dynamic_array);
void *GetDataFromDynamicArray(DynamicArray *dynamic_array, const unsigned int index); 
void PushDataToDynamicArray(DynamicArray *dynamic_array, void *data);
void SetDataInDynamicArray(DynamicArray *dynamic_array, const unsigned int index, 
                           void *data);
bool IsDynamicArrayValid(const DynamicArray *dynamic_array);
