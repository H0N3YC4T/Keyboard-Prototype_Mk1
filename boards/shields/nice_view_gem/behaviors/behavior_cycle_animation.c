#define DT_DRV_COMPAT zmk_behavior_cycle_animation

#include <zephyr/device.h>
#include <zmk/behavior.h>
#include <zephyr/logging/log.h>
#include <zmk/keymap.h>
#include "nice_view_cycle.h"
#include "../widgets/animation.h"

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

static int on_keymap_binding_pressed(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event)
{
    uint32_t cmd = binding->param1;

    if (cmd == NVC_TOG) {
        cmd = nice_view_animation_is_enabled() ? NVC_OFF : NVC_ON;
    }

    switch (cmd) {
    case NVC_OFF:
        nice_view_animation_off();
        break;

    case NVC_ON:
        nice_view_animation_on();
        break;

    case NVC_NEXT:
        nice_view_theme_next();
        break;

    default:
        LOG_ERR("Unknown animation command param1=%d", cmd);
        return -ENOTSUP;
    }

    return ZMK_BEHAVIOR_OPAQUE;
}

static int on_keymap_binding_released(struct zmk_behavior_binding *binding,
                                      struct zmk_behavior_binding_event event)
{
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_cycle_animation_driver_api = {
    .binding_pressed = on_keymap_binding_pressed,
    .binding_released = on_keymap_binding_released,
};

BEHAVIOR_DT_INST_DEFINE(0,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        APPLICATION,
                        CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
                        &behavior_cycle_animation_driver_api);

#endif
