// SPDX-License-Identifier: MIT
#pragma once

#include <zephyr/kernel.h>
#include <zmk/event_manager.h>

/*
 * Animation control commands.
 * Only two remain:
 *  - NVC_TOGGLE = toggle animation movement
 *  - NVC_NEXT   = move to next theme
 */
#define NVC_TOGGLE  0
#define NVC_NEXT    1

struct behavior_change_animation_data {
    int type;  /* 0 = toggle, 1 = next */
};

struct cycle_animation_state_changed {
    struct behavior_change_animation_data data;
};

ZMK_EVENT_DECLARE(cycle_animation_state_changed);

static inline int raise_zmk_change_animation_event(struct behavior_change_animation_data d)
{
    struct cycle_animation_state_changed *evt =
        new_cycle_animation_state_changed();

    if (!evt) {
        return -ENOMEM;
    }

    evt->data = d;

    return ZMK_EVENT_RAISE(evt);
}
