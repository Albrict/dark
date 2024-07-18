#pragma once
#include <stdbool.h>

typedef void(*message_callback)(void*, void*);

typedef enum MessageType {
    NONE,
    GAME
} MessageType;

typedef enum GameMessage {
    EXIT
} GameMessage;

bool InitMessageSystem(void);
void ProccessMessageSystem(void);
void CloseMessageSystem(void);

unsigned int Subscripe(const message_callback callback, const MessageType type,
                       void *data);
void Unsubscripe(const unsigned int id);
void SendMessage(const MessageType type, void *data);
