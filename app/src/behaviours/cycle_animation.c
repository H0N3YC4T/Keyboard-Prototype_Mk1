#include <zephyr/device.h>
#include <zmk/behavior.h>
#include <zmk/event_manager.h>

#include "animation.h"

static int nice_view_theme_pressed(struct zmk_behavior_binding *binding,
                                   struct zmk_behavior_binding_event *event) {
    ARG_UNUSED(binding);
    ARG_UNUSED(event);

    nice_view_theme_next();
    return ZMK_BEHAVIOR_OPAQUE;
}

static int nice_view_theme_released(struct zmk_behavior_binding *binding,
                                    struct zmk_behavior_binding_event *event) {
    ARG_UNUSED(binding);
    ARG_UNUSED(event);
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api nice_view_theme_api = {
    .binding_pressed = nice_view_theme_pressed,
    .binding_released = nice_view_theme_released,
};

DEVICE_DT_INST_DEFINE(0, NULL, NULL, NULL, NULL, APPLICATION,
                      CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
                      &nice_view_theme_api);
