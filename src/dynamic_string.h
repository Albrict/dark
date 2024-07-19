#pragma once
#define SMALL_STRING_BUFFER_SIZE 40

typedef struct DynamicString {
    char        *string;
    char         small_string[SMALL_STRING_BUFFER_SIZE];
    unsigned int size;
} DynamicString;

DynamicString CreateString(const char *string);
void DestroyString(DynamicString *string);
const char *GetContents(DynamicString *string);
void SetContents(DynamicString *string, const char *contents);
