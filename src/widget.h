#pragma once
typedef void(*widget_callback)(void*);
typedef void(*widget_proccess)(void*, widget_callback, void*);
typedef void(*widget_update)(void*);
typedef void(*widget_draw)(const void*);
typedef void(*widget_destroy)(void*);

typedef struct Widget {
    widget_proccess proccess_callback;
    widget_update   update_callback;
    widget_draw     draw_callback;
    widget_destroy  destroy_callback;
    widget_callback user_callback;
    void            *data;
    void            *user_data;
} Widget;

static inline void ProccessWidget(Widget *widget)
{
    if (widget->proccess_callback)
        widget->proccess_callback(widget->data, widget->user_callback, widget->user_data);
}

static inline void UpdateWidget(Widget *widget)
{
    if (widget->update_callback)
        widget->update_callback(widget->data);
}

static inline void DrawWidget(const Widget *widget)
{
    if (widget->draw_callback)
        widget->draw_callback(widget->data);
}

static inline void DestroyWidget(Widget *widget)
{
    if (widget->destroy_callback)
        widget->destroy_callback(widget->data);
    *widget = (Widget){0};
}

static inline void SetWidgetCallback(Widget *widget, 
                                    const widget_callback callback, 
                                    void *user_data)
{
    widget->user_callback = callback;
    widget->user_data     = user_data;
}
