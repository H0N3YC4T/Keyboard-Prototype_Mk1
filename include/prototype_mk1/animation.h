#pragma once

#include <lvgl.h>
#include <prototype_mk1/util.h>
#include <prototype_mk1/screen_peripheral.h>

enum nice_view_theme {
    NICE_VIEW_THEME_CRYSTAL = 0,
    NICE_VIEW_THEME_OMNISSIAH,
    NICE_VIEW_THEME_ULTRAMAR,
    NICE_VIEW_THEME_TRANSMUTATION,
    NICE_VIEW_THEME_COUNT,
};

// Internal draw function
void draw_animation(lv_obj_t *canvas);

// Theme control API
void nice_view_theme_set(enum nice_view_theme theme);
void nice_view_theme_next(void);
enum nice_view_theme nice_view_theme_get(void);