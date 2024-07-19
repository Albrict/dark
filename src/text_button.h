#pragma once
#include <raylib.h>
#include "constants.h"
#include "resource_manager.h"
#include "widget.h"

Widget CreateTextButtonEx(const char *text, const Font font, 
                          const Vector2 *position, const float font_size, 
                          const float spacing, const Color color);

static inline Widget CreateTextButtonVec(const char *text, const Vector2 *position)
{
    return CreateTextButtonEx(text, GetFont("Becker"), position, DEFAULT_FONT_SIZE, 
                              DEFAULT_SPACING_SIZE, WHITE);
}

static inline Widget CreateTextButton(const char *text, const float x, const float y)
{ return CreateTextButtonVec(text, &(Vector2){x, y}); }

bool IsTextButtonFocused(const Widget *text_button);
void TextButtonSetFocus(Widget *text_button);
void TextButtonUnsetFocus(Widget *text_button);
void TextButtonPlayAnimation(Widget *text_button);
void TextButtonSetFont(Widget *text_button, const Font *font);

float GetTextButtonWidth(void);
