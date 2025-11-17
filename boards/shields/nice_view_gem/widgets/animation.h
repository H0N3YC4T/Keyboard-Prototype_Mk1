// widgets/animation.h
#pragma once

#include <lvgl.h>
// #include "util.h"
// #include "screen_peripheral.h"

// Theme selection
enum nice_view_theme {
    NICE_VIEW_THEME_CRYSTAL = 0,
    NICE_VIEW_THEME_OMNISSIAH,
    NICE_VIEW_THEME_ULTRAMAR,
    NICE_VIEW_THEME_TRANSMUTATION,
    NICE_VIEW_THEME_COUNT,
};

bool nice_view_animation_is_enabled(void);

// Init (optional hook if you need it)
void nice_view_theme_init(void);

// Draw the current theme onto the given canvas
void draw_animation(lv_obj_t *canvas);

// Theme control API
void nice_view_theme_set(enum nice_view_theme theme);
enum nice_view_theme nice_view_theme_get(void);
void nice_view_theme_next(void);

void nice_view_animation_toggle(void);
void nice_view_animation_off(void);
void nice_view_animation_on(void);