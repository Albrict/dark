#include <raylib.h>
#include <stdlib.h>
#include "text_button.h"
#include "sound.h"
#include "widget.h"

typedef struct TextButton {
    const char *text;   
    Font        font;
    Color       color;
    Rectangle   rect;
    Vector2     text_position;
    float       spacing;
    float       font_size;
    
    bool        is_focus_sound_played;
    bool        is_focused;
    bool        is_pressed;
} TextButton;

static const float TEXT_BUTTON_WIDTH = 150.f;

static void ProccessTextButton(void *text_button, widget_callback user_callback, 
                               void *user_data)
{
    TextButton *button = (TextButton*)(text_button);
    if (button->is_focused == true) {
        if (IsKeyPressed(KEY_ENTER) == true) {
            button->is_pressed = true;
            if (user_callback != NULL)
                user_callback(user_data);
        }
    }
}

static void UpdateTextButton(void *text_button)
{
    TextButton *button = (TextButton*)(text_button);
    if (button->is_focus_sound_played == false && button->is_focused) {
        PlaySound(GetSound("Choose"));
        button->is_focus_sound_played = true;
    }
    if (button->is_pressed == true) {
        PlaySound(GetRandomButtonPressSound());
        button->is_pressed = false;
    }
}

static void DrawTextButton(const void *text_button)
{
    const TextButton *button   = (const TextButton*)(text_button);
    if (button->is_focused == true)
        DrawRectangleLinesEx(button->rect, 2.f, GRAY);
    DrawTextEx(button->font, button->text, button->text_position, button->font_size, 
               button->spacing, button->color);
}

static void DestroyTextButton(void *text_button)
{
    free(text_button);
}

Widget CreateTextButtonEx(const char *text, const Font font, 
                          const Vector2 *position, const float font_size, 
                          const float spacing, const Color color)
{
    const Rectangle rect = {
        .x      = position->x,
        .y      = position->y,
        .width  = TEXT_BUTTON_WIDTH,
        .height = MeasureTextEx(font, text, font_size, spacing).y
    };
    const Vector2 text_position = { 
        .x = rect.x + rect.width / 2.f - (float)MeasureText(text, (int)font_size) / 2.f, 
        .y = rect.y
    };

    TextButton *text_button            = malloc(sizeof(TextButton));
    text_button->text                  = text;
    text_button->font                  = font;
    text_button->color                 = color;
    text_button->rect                  = rect;
    text_button->spacing               = spacing;
    text_button->font_size             = font_size;
    text_button->text_position         = text_position;
    text_button->is_focus_sound_played = false;
    text_button->is_focused            = false;
    text_button->is_pressed            = false;

    return (Widget) {
        .proccess_callback = ProccessTextButton,
        .update_callback   = UpdateTextButton,
        .draw_callback     = DrawTextButton,
        .destroy_callback  = DestroyTextButton, 
        .user_callback     = NULL,
        .data              = text_button
    };
}

float GetTextButtonWidth(void)
{
    return TEXT_BUTTON_WIDTH;
}

bool IsTextButtonFocused(const Widget *text_button)
{
    const TextButton *button = (const TextButton*)(text_button->data);
    return button->is_focused;
}

void TextButtonSetFocus(Widget *text_button)
{
    TextButton *button = (TextButton*)(text_button->data);
    button->is_focused = true;
}

void TextButtonUnsetFocus(Widget *text_button)
{
    TextButton *button            = (TextButton*)(text_button->data);
    button->is_focused            = false;
    button->is_focus_sound_played = false;
}

void TextButtonSetFont(Widget *text_button, const Font *font)
{
    TextButton *button = (TextButton*)(text_button->data);
    button->font       = *font;
}
