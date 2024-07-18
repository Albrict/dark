#include <raylib.h>
#include <stddef.h>
#include <assert.h>
#include "message_system.h"

#define MAX_HANDLERS 100
#define MAX_MESSAGES 20

typedef struct MessageHandler {
    message_callback callback;
    void            *data;
    void            *messages[MAX_MESSAGES];
    MessageType      type;
    unsigned int     current_message;
} MessageHandler;

typedef struct MessageStorage {
    MessageHandler   handlers[MAX_HANDLERS];
    unsigned int     current_handler;
} MessageStorage;

static MessageStorage *message_storage = NULL;

bool InitMessageSystem(void)
{
    message_storage                  = MemAlloc(sizeof(MessageStorage));
    message_storage->current_handler = 0;
    if (message_storage == NULL)
        return false;
    else
        return true;
}

void ProccessMessageSystem(void)
{
    for (unsigned int i = 0; i < message_storage->current_handler; ++i) {
        if (message_storage->handlers[i].callback != NULL) {
            const MessageHandler *message_handler = &message_storage->handlers[i];
            //
        }
    }
}

void CloseMessageSystem(void)
{
    MemFree(message_storage);
}

unsigned int Subscripe(const message_callback callback, const MessageType type,
                       void *data) 
{
    const unsigned int current_handler = message_storage->current_handler;
    MessageHandler handler = {
        .callback = callback,
        .data     = data,
        .type     = type
    };
    while (message_storage->handlers[message_storage->current_handler].callback != NULL)
        ++message_storage->current_handler;
    message_storage->handlers[message_storage->current_handler] = handler;
    return current_handler;
}


void Unsubscripe(const unsigned int id)
{
    assert(id <= MAX_HANDLERS);
    assert(id >= 0);
    
    MessageHandler *handler = &message_storage->handlers[id];
    handler->type           = NONE;
    handler->data           = NULL;
    handler->callback       = NULL;
}

void SendMessage(const MessageType type, void *data)
{
    for (unsigned int i = 0; i < message_storage->current_handler; ++i) {
        if (message_storage->handlers[i].type == type) {
            MessageHandler *handler = &message_storage->handlers[i];
            handler->messages[handler->current_message] = data;
            ++handler->current_message;
        }
    }
}
