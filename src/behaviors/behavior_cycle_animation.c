/* behavior_cycle_animation.c
 *
 * Nice!View theme + animation control behavior
 */

/* Convert "zmk,behavior-cycle-animation" → zmk_behavior_cycle_animation */
#define DT_DRV_COMPAT zmk_behavior_cycle_animation

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>
#include <zmk/keymap.h>
#include "boards/shields/nice_view_gem/widgets/animation.h"

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)
static const struct behavior_parameter_value_metadata no_arg_values[] = {
    { .display_name = "Toggle Animation", .type = BEHAVIOR_PARAMETER_VALUE_TYPE_VALUE, .value = NVC_TOG },
    { .display_name = "Turn Animation Off", .type = BEHAVIOR_PARAMETER_VALUE_TYPE_VALUE, .value = NVC_OFF },
    { .display_name = "Turn Animation On",  .type = BEHAVIOR_PARAMETER_VALUE_TYPE_VALUE, .value = NVC_ON  },
    { .display_name = "Cycle Theme",       .type = BEHAVIOR_PARAMETER_VALUE_TYPE_VALUE, .value = NVC_NEXT },
};

static const struct behavior_parameter_metadata metadata = {
    .sets = no_arg_values,
    .sets_len = ARRAY_SIZE(no_arg_values),
};
#endif


static int on_keymap_binding_convert_central_state_dependent_params(
    struct zmk_behavior_binding *binding,
    struct zmk_behavior_binding_event event
) {
    if (binding->param1 == NVC_TOG) {
        binding->param1 = nice_view_animation_is_enabled() ? NVC_OFF : NVC_ON;
    }
    return 0;
}


static int on_keymap_binding_pressed(
    struct zmk_behavior_binding *binding,
    struct zmk_behavior_binding_event event
) {
    switch (binding->param1) {
    case NVC_TOG:
        nice_view_animation_toggle();
        return ZMK_BEHAVIOR_OPAQUE;

    case NVC_OFF:
        nice_view_animation_off();
        return ZMK_BEHAVIOR_OPAQUE;

    case NVC_ON:
        nice_view_animation_on();
        return ZMK_BEHAVIOR_OPAQUE;

    case NVC_NEXT:
        nice_view_theme_next();
        return ZMK_BEHAVIOR_OPAQUE;

    default:
        LOG_ERR("Unknown animation command param1=%d", binding->param1);
        return -ENOTSUP;
    }
}


static int on_keymap_binding_released(
    struct zmk_behavior_binding *binding,
    struct zmk_behavior_binding_event event
) {
    return ZMK_BEHAVIOR_OPAQUE;
}


static const struct behavior_driver_api behavior_cycle_animation_driver_api = {
    .binding_convert_central_state_dependent_params =
        on_keymap_binding_convert_central_state_dependent_params,
    .binding_pressed =
        on_keymap_binding_pressed,
    .binding_released =
        on_keymap_binding_released,
    .locality = BEHAVIOR_LOCALITY_GLOBAL,
#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)
    .parameter_metadata = &metadata,
#endif
};

BEHAVIOR_DT_INST_DEFINE(
    0, NULL, NULL, NULL, NULL,
    APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
    &behavior_cycle_animation_driver_api
);

#endif
