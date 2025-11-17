// widgets/animation_assets.h
#pragma once

#include <lvgl.h>
#include <stddef.h>
#include <animation.h>

// One pointer-array per theme, to be indexed with nice_view_gem_theme.
extern const lv_img_dsc_t * const anim_sets[NICE_VIEW_GEM_THEME_COUNT];
extern const size_t anim_set_lengths[NICE_VIEW_GEM_THEME_COUNT];