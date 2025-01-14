#include "oneshot.h"

// update_oneshot manages oneshot logic
// if isLayerSwitch is true, 
void update_oneshot(
    oneshot_state *state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record,
    bool isLayerSwitch
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                if (isLayerSwitch) { // support for layer switch
                    layer_on(mod);
                } else {
                    register_code(mod);
                }
                *state = os_down_unused;
            }
            
            if (is_oneshot_cancel_key(keycode) && *state == os_up_queued) {
                // Cancel oneshot if keycode is used as cancel key (second tap will cancel)
                *state = os_up_unqueued;
                if (isLayerSwitch) {
                    layer_off(mod); 
                } else {
                    unregister_code(mod);
                }
            }
        } else {
            // Trigger keyup
            switch (*state) {
            case os_down_unused:
                // If we didn't use the mod while trigger was held, queue it.
                *state = os_up_queued;
                break;
            case os_down_used:
                // If we did use the mod while trigger was held, unregister it.
                *state = os_up_unqueued;
                if (isLayerSwitch) {
                    layer_off(mod);
                } else {
                    unregister_code(mod);
                }
                break;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (*state != os_up_unqueued) {
                if (is_oneshot_cancel_key(keycode) || *state == os_down_one_used) {
                    // Cancel oneshot on designated cancel keydown.
                    // Also cancel immediately before second keydown is registered,
                    // this prevents triggering mod (or layer) if more keys are down
                    // before first key is up.
                    *state = os_up_unqueued;
                    if (isLayerSwitch) {
                        layer_off(mod);
                    } else {
                        unregister_code(mod);
                    }
                } else {
                    if (*state == os_up_queued) {
                        *state = os_down_one_used;
                    }
                }
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_down_unused:
                    *state = os_down_used;
                    break;
		case os_down_one_used:
                case os_up_queued:
                    *state = os_up_unqueued;
                    if (isLayerSwitch) {
                        layer_off(mod);
                    } else {
                        unregister_code(mod);
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
}
