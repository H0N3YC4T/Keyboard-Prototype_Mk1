// widgets/animation.c

#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <lvgl.h>

#include "animation.h"
#include "animation_assets.h"


static enum nice_view_theme current_theme = NICE_VIEW_THEME_CRYSTAL;
_Bool nice_view_animation = true;
unsigned char nice_view_theme_offset = 1;
const int nice_view_animation_speed = 1400;

void nice_view_theme_init(void) {
    nice_view_theme_set(nice_view_theme_get());
    draw_animation(current_theme);
}

void nice_view_theme_set(enum nice_view_theme theme) {
    if (theme >= NICE_VIEW_THEME_COUNT) {
        theme = NICE_VIEW_THEME_CRYSTAL;
    }
    current_theme = theme;
}


void nice_view_theme_next(void) {
    current_theme += 1;
    nice_view_theme_set(nice_view_theme_get());
    draw_animation(current_theme);
}


enum nice_view_theme nice_view_theme_get(void) {
    calc_offset_for_theme(current_theme);
    return current_theme;
}


void nice_view_animation_toggle(void) {
    if (nice_view_animation) ? nice_view_animation = false : nice_view_animation = true;
    nice_view_theme_set(nice_view_theme_get());
    draw_animation(current_theme);
}


void nice_view_animation_off(void) {
    if (nice_view_animation) {
        nice_view_animation = false;
        nice_view_theme_set(nice_view_theme_get());
        draw_animation(current_theme);
    }
}

void nice_view_animation_on(void) {
    if (!nice_view_animation) {
        nice_view_animation = true;
        nice_view_theme_set(nice_view_theme_get());
        draw_animation(current_theme);
    }
}

void calc_offset_for_theme(enum nice_view_theme theme) {
    const unsigned char max_width = 120;
    const lv_img_dsc_t * const *frames = nice_view_anim_sets[theme];
    int img_w = frames[0]->header.w;

    if (img_w >= max_width) {
        nice_view_theme_offset = 1;
    } else {
        nice_view_theme_offset = ((max_width - img_w + 1) / 2);
    }
}


void draw_animation(enum nice_view_theme theme) {
    const lv_img_dsc_t * const *frames = nice_view_anim_sets[theme];
    const size_t frame_count = nice_view_anim_lengths[theme];

    if (!frames || !frame_count) {
        return; // nothing to draw 
    }

    if (nice_view_animation) {
        lv_obj_t *art = lv_animimg_create(canvas);
        lv_obj_center(art);

        lv_animimg_set_src(art, (const void **)frames, frame_count);
        lv_animimg_set_duration(art, nice_view_animation_speed);
        lv_animimg_set_repeat_count(art, LV_ANIM_REPEAT_INFINITE);
        lv_animimg_start(art);

    } else {
        lv_obj_t *art = lv_img_create(canvas);
        uint32_t idx = k_uptime_get_32() % frame_count;
        lv_img_set_src(art, frames[idx]);
    }

    lv_obj_align(art, LV_ALIGN_TOP_LEFT, nice_view_theme_offset, 0);
}
