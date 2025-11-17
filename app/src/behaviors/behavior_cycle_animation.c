/* behavior_cycle_animation.c
 *
 * Nice!View theme + animation control behavior
 */

/* Convert "zmk,behavior-cycle-animation" → zmk_behavior_cycle_animation */
#define DT_DRV_COMPAT zmk_behavior_cycle_animation

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>

#include <zmk/behavior.h>
#include <zmk/keymap.h>
#include <zmk/keys.h>
#include <zmk/endpoints.h>
#include <zmk/event_manager.h>

#include <zmk/behaviors/cycle_animation.h>
#include <zmk/events/cycle_animation_state_changed.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)

static const struct behavior_parameter_value_metadata param_values[] = {
    {
        .display_name = "Toggle Animation Movement",
        .value = NVC_TOG,
        .type = BEHAVIOR_PARAMETER_VALUE_TYPE_VALUE,
    },
    {
        .display_name = "Turn Off Animation Movement",
        .value = NVC_OFF,
        .type = BEHAVIOR_PARAMETER_VALUE_TYPE_VALUE,
    },
    {
        .display_name = "Turn On Animation Movement",
        .value = NVC_ON,
        .type = BEHAVIOR_PARAMETER_VALUE_TYPE_VALUE,
    },
    {
        .display_name = "Go to next Theme",
        .value = NVC_NEXT,
        .type = BEHAVIOR_PARAMETER_VALUE_TYPE_VALUE,
    },
};

static const struct behavior_parameter_metadata_set param_metadata_set[] = {{
    .param1_values = param_values,
    .param1_values_len = ARRAY_SIZE(param_values),
}};

static const struct behavior_parameter_metadata metadata = {
    .sets_len = ARRAY_SIZE(param_metadata_set),
    .sets = param_metadata_set,
};

#endif /* CONFIG_ZMK_BEHAVIOR_METADATA */

/* Key pressed: raise custom animation-change event based on param1 */
static int on_keymap_binding_pressed(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event)
{
    struct behavior_change_animation_data data = {0};

    switch (binding->param1) {
    case NVC_TOG:
        data.type = 0;
        break;

    case NVC_NEXT:
        data.type = 1;
        break;

    default:
        LOG_ERR("Unknown animation command param1=%d", binding->param1);
        return -ENOTSUP;
    }

    /* This function is assumed to be declared in cycle_animation_state_changed.h */
    raise_zmk_change_animation_event(data);

    /* We "consume" the press; nothing else should interpret this key */
    return ZMK_BEHAVIOR_OPAQUE;
}

static int on_keymap_binding_released(struct zmk_behavior_binding *binding,
                                      struct zmk_behavior_binding_event event)
{
    /* Nothing to do on release; still consume the event */
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_cycle_animation_driver_api = {
    .binding_pressed =  on_keymap_binding_pressed,
    .binding_released = on_keymap_binding_released,
    .locality = BEHAVIOR_LOCALITY_GLOBAL,
#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)
    .parameter_metadata = &metadata,
#endif
};

/* One driver instance per devicetree node */
#define CYCLE_ANIMATION_INST(n)                                                \
    BEHAVIOR_DT_INST_DEFINE(n,                                                 \
                            NULL,                                              \
                            NULL,                                              \
                            NULL,                                              \
                            NULL,                                              \
                            APPLICATION,                                       \
                            CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,               \
                            &behavior_cycle_animation_driver_api);

DT_INST_FOREACH_STATUS_OKAY(CYCLE_ANIMATION_INST);

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
