#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <lvgl.h>

#include <prototype_mk1/animation.h>
#include "animation_assets.h"


static enum nice_view_theme current_theme = NICE_VIEW_THEME_CRYSTAL;

void nice_view_theme_set(enum nice_view_theme theme) {
    if (theme >= NICE_VIEW_THEME_COUNT) {
        theme = NICE_VIEW_THEME_CRYSTAL;
    }

    current_theme = theme;
    zmk_display_request_update();
}

void nice_view_theme_next(void) {
    current_theme = (current_theme + 1) % NICE_VIEW_THEME_COUNT;
    zmk_display_request_update();
}

enum nice_view_theme nice_view_theme_get(void) {
    return current_theme;
}

static lv_coord_t calc_x_offset_for_theme(enum nice_view_theme theme) {
    const int max_width = 120;

    const lv_img_dsc_t * const *frames = nice_view_anim_sets[theme];
    const size_t frame_count = nice_view_anim_lengths[theme];

    if (!frames || !frame_count || !frames[0]) {
        return 1; // sane fallback
    }

    int img_w = frames[0]->header.w;
    if (img_w >= max_width) {
        return 1;
    }

    return (lv_coord_t)((max_width - img_w + 1) / 2);
}

void draw_animation(lv_obj_t *canvas) {
    enum nice_view_theme theme = nice_view_theme_get();
    const lv_img_dsc_t * const *frames = nice_view_anim_sets[theme];
    const size_t frame_count = nice_view_anim_lengths[theme];

    if (!frames || !frame_count) {
        return; // nothing to draw
    }

#if IS_ENABLED(CONFIG_NICE_VIEW_GEM_ANIMATION)
    lv_obj_t *art = lv_animimg_create(canvas);
    lv_obj_center(art);

    lv_animimg_set_src(art, (const void **)frames, frame_count);
    lv_animimg_set_duration(art, CONFIG_NICE_VIEW_GEM_ANIMATION_MS);
    lv_animimg_set_repeat_count(art, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(art);

#else
    lv_obj_t *art = lv_img_create(canvas);
    uint32_t idx = k_uptime_get_32() % frame_count;
    lv_img_set_src(art, frames[idx]);
#endif
    lv_obj_align(art, LV_ALIGN_TOP_LEFT, animation_offset, 0);
}
