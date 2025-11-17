// widgets/animation.c
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zmk/display/status_screen.h>
#include <lvgl.h>

#include "animation.h"
#include "animation_assets.h"

static enum nice_view_theme current_theme = NICE_VIEW_THEME_CRYSTAL;
static bool nice_view_animation = true;

static lv_coord_t nice_view_theme_offset = 1;
static const int nice_view_animation_speed = 1400;

static void calc_offset_for_theme(enum nice_view_theme theme);

void nice_view_theme_init(void) {
    /* First draw will be triggered by display update */
    zmk_display_request_update();
}

bool nice_view_animation_is_enabled(void) {
    return nice_view_animation;
}

void nice_view_theme_set(enum nice_view_theme theme) {
    if (theme >= NICE_VIEW_THEME_COUNT) {
        theme = NICE_VIEW_THEME_CRYSTAL;
    }

    current_theme = theme;
    zmk_display_request_update();
}

enum nice_view_theme nice_view_theme_get(void) {
    return current_theme;
}

void nice_view_theme_next(void) {
    enum nice_view_theme theme = nice_view_theme_get();
    theme = (theme + 1) % NICE_VIEW_THEME_COUNT;
    nice_view_theme_set(theme);
}

void nice_view_animation_toggle(void) {
    nice_view_animation = !nice_view_animation;
    zmk_display_request_update();
}

void nice_view_animation_off(void) {
    if (nice_view_animation) {
        nice_view_animation = false;
        zmk_display_request_update();
    }
}

void nice_view_animation_on(void) {
    if (!nice_view_animation) {
        nice_view_animation = true;
        zmk_display_request_update();
    }
}

static void calc_offset_for_theme(enum nice_view_theme theme) {
    const lv_coord_t max_width = 120;
    const lv_img_dsc_t * const *frames = nice_view_anim_sets[theme];

    if (!frames || !frames[0]) {
        nice_view_theme_offset = 1;
        return;
    }

    lv_coord_t img_w = frames[0]->header.w;

    if (img_w >= max_width) {
        nice_view_theme_offset = 1;
    } else {
        nice_view_theme_offset = (max_width - img_w + 1) / 2;
    }
}

void draw_animation(lv_obj_t *canvas) {
    enum nice_view_theme theme = nice_view_theme_get();
    const lv_img_dsc_t * const *frames = nice_view_anim_sets[theme];
    const size_t frame_count = nice_view_anim_lengths[theme];

    if (!frames || !frame_count) {
        return; /* nothing to draw */
    }

    calc_offset_for_theme(theme);

    lv_obj_t *art;

    if (nice_view_animation) {
        art = lv_animimg_create(canvas);
        lv_obj_center(art);

        lv_animimg_set_src(art, (const void **)frames, frame_count);
        lv_animimg_set_duration(art, nice_view_animation_speed);
        lv_animimg_set_repeat_count(art, LV_ANIM_REPEAT_INFINITE);
        lv_animimg_start(art);
    } else {
        art = lv_img_create(canvas);
        uint32_t idx = k_uptime_get_32() % frame_count;
        lv_img_set_src(art, frames[idx]);
    }

    lv_obj_align(art, LV_ALIGN_TOP_LEFT, nice_view_theme_offset, 0);
}
