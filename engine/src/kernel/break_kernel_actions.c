#include <kernel/break_kernel_internal.h>
#include <math.h>

static bool binding_ok(const BreakKernelBinding *b) {
    if (!b || !isfinite(b->scale)) {
        return false;
    }
    switch (b->source) {
    case BREAK_KERNEL_BIND_KEY:
    case BREAK_KERNEL_BIND_MOUSE_BUTTON:
        return b->pad == 0 && b->code >= 0 && b->code < INPUT_MAX_KEYS;
    case BREAK_KERNEL_BIND_MOUSE_AXIS:
        return b->pad == 0 && b->code >= 0 && b->code <= 2;
    case BREAK_KERNEL_BIND_PAD_BUTTON:
        return b->pad >= 0 && b->pad < INPUT_MAX_GAMEPADS &&
               b->code >= 0 && b->code < INPUT_MAX_PAD_BUTTONS;
    case BREAK_KERNEL_BIND_PAD_AXIS:
        return b->pad >= 0 && b->pad < INPUT_MAX_GAMEPADS &&
               b->code >= 0 && b->code < INPUT_MAX_AXES;
    default:
        return false;
    }
}

static bool digital_down(const InputState *input, const BreakKernelBinding *b) {
    switch (b->source) {
    case BREAK_KERNEL_BIND_KEY:
    case BREAK_KERNEL_BIND_MOUSE_BUTTON:
        return input_key_down(input, b->code);
    case BREAK_KERNEL_BIND_PAD_BUTTON:
        return input->gamepads[b->pad].connected && input_pad_button_down(input, b->pad, b->code);
    default:
        return false;
    }
}

static f32 binding_axis(const InputState *input, const BreakKernelBinding *b) {
    if (b->source == BREAK_KERNEL_BIND_KEY || b->source == BREAK_KERNEL_BIND_MOUSE_BUTTON ||
        b->source == BREAK_KERNEL_BIND_PAD_BUTTON) {
        return digital_down(input, b) ? b->scale : 0.0f;
    }
    if (b->source == BREAK_KERNEL_BIND_MOUSE_AXIS) {
        f32 raw = 0.0f;
        if (b->code == 0) {
            raw = input->mouse_dx;
        } else if (b->code == 1) {
            raw = input->mouse_dy;
        } else {
            raw = input->scroll_dy;
        }
        return raw * b->scale;
    }
    if (!input->gamepads[b->pad].connected) {
        return 0.0f;
    }
    return input->gamepads[b->pad].axes[b->code] * b->scale;
}

BreakKernelError break_kernel_bind_actions(BreakKernel *kernel, const BreakKernelActionDesc *actions, u32 count) {
    if (!kernel || (count > 0 && !actions)) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    if (count > BREAK_KERNEL_HARD_MAX_ACTIONS) {
        return BREAK_KERNEL_OVERLOAD;
    }
    BreakKernelAction staged[BREAK_KERNEL_HARD_MAX_ACTIONS];
    memset(staged, 0, sizeof(staged));
    for (u32 i = 0; i < count; i++) {
        if (!break_kernel_copy_name(actions[i].name, staged[i].name, false)) {
            return BREAK_KERNEL_INVALID;
        }
        if (actions[i].binding_count > BREAK_KERNEL_HARD_MAX_BINDINGS) {
            return BREAK_KERNEL_INVALID;
        }
        if (actions[i].binding_count > 0 && !actions[i].bindings) {
            return BREAK_KERNEL_INVALID;
        }
        for (u32 j = 0; j < i; j++) {
            if (strcmp(staged[j].name, staged[i].name) == 0) {
                return BREAK_KERNEL_REJECTED;
            }
        }
        for (u32 b = 0; b < actions[i].binding_count; b++) {
            if (!binding_ok(&actions[i].bindings[b])) {
                return BREAK_KERNEL_INVALID;
            }
            staged[i].bindings[b] = actions[i].bindings[b];
        }
        staged[i].binding_count = actions[i].binding_count;
    }
    memcpy(kernel->actions, staged, sizeof(staged));
    kernel->action_count = count;
    return BREAK_KERNEL_OK;
}

BreakKernelError break_kernel_eval_actions(BreakKernel *kernel, const InputState *input,
                                      BreakKernelActionValue *out, u32 cap) {
    if (!kernel || !input || (cap > 0 && !out)) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    if (cap < kernel->action_count) {
        return BREAK_KERNEL_OVERLOAD;
    }
    for (u32 i = 0; i < kernel->action_count; i++) {
        const BreakKernelAction *action = &kernel->actions[i];
        f32 axis = 0.0f;
        bool down = false;
        for (u32 b = 0; b < action->binding_count; b++) {
            const BreakKernelBinding *binding = &action->bindings[b];
            if (digital_down(input, binding)) {
                down = true;
            }
            axis += binding_axis(input, binding);
        }
        if (axis > 1.0f) {
            axis = 1.0f;
        } else if (axis < -1.0f) {
            axis = -1.0f;
        }
        out[i].down = down;
        out[i].axis = axis;
    }
    return BREAK_KERNEL_OK;
}
