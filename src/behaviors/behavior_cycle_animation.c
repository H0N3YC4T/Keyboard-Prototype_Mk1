/* behavior_cycle_animation.c
 *
 * Nice!View theme cycle behavior
 */

/* DT compat must match the binding's "compatible" with commas -> underscores */
#define DT_DRV_COMPAT zmk_behavior_cycle_animation

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zmk/event_manager.h>

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <prototype_mk1/animation.h>

//#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

/* Press handler: cycle to next Nice!View theme */
static int on_cycle_animation_binding_pressed(struct zmk_behavior_binding *binding,
                                              struct zmk_behavior_binding_event event) {
    ARG_UNUSED(binding);
    ARG_UNUSED(event);

    nice_view_theme_next();
    return ZMK_BEHAVIOR_OPAQUE;
}

/* Release handler: nothing extra to do, but kept for completeness */
static int on_cycle_animation_binding_released(struct zmk_behavior_binding *binding,
                                               struct zmk_behavior_binding_event event) {
    ARG_UNUSED(binding);
    ARG_UNUSED(event);

    return ZMK_BEHAVIOR_OPAQUE;
}

/* No per-instance config; just satisfy the init hook. */
static int behavior_cycle_animation_init(const struct device *dev) {
    ARG_UNUSED(dev);
    return 0;
}

static const struct behavior_driver_api behavior_cycle_animation_driver_api = {
    .binding_pressed = on_cycle_animation_binding_pressed,
    .binding_released = on_cycle_animation_binding_released,

    /* Make it GLOBAL so halves + dongle all advance together on one key press. */
    .locality = BEHAVIOR_LOCALITY_GLOBAL,
};

BEHAVIOR_DT_INST_DEFINE(0,
                        behavior_cycle_animation_init,
                        NULL,
                        NULL,
                        NULL,
                        APPLICATION,
                        CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
                        &behavior_cycle_animation_driver_api);

//#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
