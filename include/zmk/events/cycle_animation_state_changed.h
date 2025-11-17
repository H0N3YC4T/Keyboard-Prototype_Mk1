#pragma once

#include <zephyr/kernel.h>
#include <zmk/event_manager.h>

#define NVC_TOG  0
#define NVC_OFF  1
#define NVC_ON   2
#define NVC_NEXT 3

/*
 * This is the payload your event carries.
 * It MUST match the struct used when raising the event.
 */
struct behavior_change_animation_data {
    int type;  /* 0=toggle, 1=next */
};

/*
 * Declare the event type for subscribers.
 * This gives you:
 *
 *   struct cycle_animation_state_changed *evt = cast_cycle_animation_state_changed(eh);
 *
 */
struct cycle_animation_state_changed {
    struct zmk_event_header header;
    struct behavior_change_animation_data data;
};

ZMK_EVENT_DECLARE(cycle_animation_state_changed);

/*
 * Helper to raise the event.
 */
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