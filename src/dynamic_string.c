#include "dynamic_string.h"
#include <stdlib.h>
#include <string.h>

DynamicString CreateString(const char *string)
{
    const unsigned long string_size    = strlen(string);  
    DynamicString       dynamic_string = {0};
    dynamic_string.size                = (unsigned int)string_size;

    if (string_size < SMALL_STRING_BUFFER_SIZE)
        strcpy(dynamic_string.small_string, string);
    else
        dynamic_string.string = strdup(string);
    return dynamic_string;
}

void DestroyString(DynamicString *string)
{
    if (string->string != NULL) {
        free(string->string);
        string->string = NULL;
    }
    string->size = 0;
}

const char *GetContents(const DynamicString *string)
{
    if (string->size < SMALL_STRING_BUFFER_SIZE)
        return string->small_string;
    else
        return string->string;
}

void SetContents(DynamicString *string, const char *contents)
{
    if (string->string != NULL)
        free(string->string);
    *string = CreateString(contents);
}
