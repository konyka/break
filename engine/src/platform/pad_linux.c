#ifdef ENGINE_PLATFORM_LINUX

/* Linux evdev pad backend.
 *
 * Discovers /dev/input/event* devices, filters those that look like
 * pads (EV_ABS axes + EV_KEY pad buttons), polls them non-blocking
 * each frame, and watches /dev/input via inotify for hot-plug events.
 */

#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/inotify.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <platform/input.h>
#include <core/types.h>
#include <core/log.h>

#include "pad_linux.h"

/* Bit-test helper used with EVIOCGBIT result arrays. */
#define BITS_PER_LONG (sizeof(unsigned long) * 8)
#define NLONGS(x)     (((x) + BITS_PER_LONG - 1) / BITS_PER_LONG)
#define TEST_BIT(arr, bit) \
    (((arr)[(bit) / BITS_PER_LONG] >> ((bit) % BITS_PER_LONG)) & 1UL)

#define DEV_INPUT_DIR "/dev/input"

typedef struct {
    int  fd;
    bool connected;
    bool feedback_available;
    int  effect_id;
    u32  connection_serial;
    char name[128];
    char path[288];
    /* Per-axis calibration. We only really need the codes used by pads,
     * but keeping the full ABS_MAX range keeps the indexing straightforward. */
    struct {
        i32  min;
        i32  max;
        bool present;
    } abs_info[ABS_CNT];
} PadDevice;

typedef struct {
    PadDevice devices[INPUT_MAX_PADS];
    int           inotify_fd;
    int           inotify_wd;
    u32           next_serial;
    bool          initialized;
} PadSystem;

static PadSystem g_pad_sys;

/* ---------------------------------------------------------------- */
/*  Helpers                                                         */
/* ---------------------------------------------------------------- */

static f32 normalize_axis(i32 value, i32 min, i32 max) {
    f32 range = (f32)(max - min);
    if (range == 0.0f) return 0.0f;
    return ((f32)(value - min) / range) * 2.0f - 1.0f;
}

/* Triggers report 0..max on most pads — emit 0..1 instead of -1..1. */
static f32 normalize_trigger(i32 value, i32 min, i32 max) {
    f32 range = (f32)(max - min);
    if (range == 0.0f) return 0.0f;
    f32 v = (f32)(value - min) / range;
    if (v < 0.0f) v = 0.0f;
    if (v > 1.0f) v = 1.0f;
    return v;
}

static i32 evdev_btn_to_pad(u16 code) {
    switch (code) {
        case BTN_SOUTH:  return PAD_BTN_SOUTH;
        case BTN_EAST:   return PAD_BTN_EAST;
        case BTN_NORTH:  return PAD_BTN_NORTH;
        case BTN_WEST:   return PAD_BTN_WEST;
        case BTN_TL:     return PAD_BTN_LB;
        case BTN_TR:     return PAD_BTN_RB;
        case BTN_SELECT: return PAD_BTN_BACK;
        case BTN_START:  return PAD_BTN_START;
        case BTN_MODE:   return PAD_BTN_GUIDE;
        case BTN_THUMBL: return PAD_BTN_LSTICK;
        case BTN_THUMBR: return PAD_BTN_RSTICK;
        case BTN_DPAD_UP:    return PAD_BTN_DPAD_UP;
        case BTN_DPAD_DOWN:  return PAD_BTN_DPAD_DOWN;
        case BTN_DPAD_LEFT:  return PAD_BTN_DPAD_LEFT;
        case BTN_DPAD_RIGHT: return PAD_BTN_DPAD_RIGHT;
        default: return -1;
    }
}

static void apply_button_state(u8 *slot, bool pressed) {
    if (pressed) {
        if (*slot != 2) *slot = 3;
    } else {
        if (*slot == 3 || *slot == 2) *slot = 1;
    }
}

/* ---------------------------------------------------------------- */
/*  Device probing                                                  */
/* ---------------------------------------------------------------- */

static bool fd_is_pad(int fd) {
    unsigned long evbits[NLONGS(EV_CNT)]   = {0};
    unsigned long keybits[NLONGS(KEY_CNT)] = {0};

    if (ioctl(fd, EVIOCGBIT(0, sizeof(evbits)), evbits) < 0) return false;
    if (!TEST_BIT(evbits, EV_KEY)) return false;
    if (!TEST_BIT(evbits, EV_ABS)) return false;

    if (ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(keybits)), keybits) < 0) return false;

    /* Accept anything that exposes at least one canonical pad button. */
    if (TEST_BIT(keybits, BTN_GAMEPAD)) return true;  /* alias of BTN_SOUTH */
    if (TEST_BIT(keybits, BTN_SOUTH))   return true;
    if (TEST_BIT(keybits, BTN_A))       return true;
    return false;
}

static void device_query_axes(PadDevice *d) {
    for (int axis = 0; axis < ABS_CNT; axis++) {
        struct input_absinfo ai;
        if (ioctl(d->fd, EVIOCGABS(axis), &ai) == 0) {
            d->abs_info[axis].min     = ai.minimum;
            d->abs_info[axis].max     = ai.maximum;
            d->abs_info[axis].present = (ai.minimum != 0 || ai.maximum != 0);
        } else {
            d->abs_info[axis].min     = 0;
            d->abs_info[axis].max     = 0;
            d->abs_info[axis].present = false;
        }
    }
}

static void device_query_haptic(PadDevice *d, bool writable) {
    unsigned long evbits[NLONGS(EV_CNT)] = {0};
    unsigned long ffbits[NLONGS(FF_CNT)] = {0};
    d->feedback_available = false;
    if (!writable) return;
    if (ioctl(d->fd, EVIOCGBIT(0, sizeof(evbits)), evbits) < 0 ||
        !TEST_BIT(evbits, EV_FF)) return;
    if (ioctl(d->fd, EVIOCGBIT(EV_FF, sizeof(ffbits)), ffbits) < 0) return;
    d->feedback_available = TEST_BIT(ffbits, FF_RUMBLE) != 0;
}

static i32 find_free_slot(void) {
    for (i32 i = 0; i < INPUT_MAX_PADS; i++) {
        if (!g_pad_sys.devices[i].connected) return i;
    }
    return -1;
}

static i32 find_slot_by_path(const char *path) {
    for (i32 i = 0; i < INPUT_MAX_PADS; i++) {
        if (g_pad_sys.devices[i].connected &&
            strcmp(g_pad_sys.devices[i].path, path) == 0) {
            return i;
        }
    }
    return -1;
}

static bool try_open_device(const char *path) {
    bool writable = false;
    if (find_slot_by_path(path) >= 0) return false;

    int fd = open(path, O_RDWR | O_NONBLOCK);
    if (fd >= 0) {
        writable = true;
    } else {
        fd = open(path, O_RDONLY | O_NONBLOCK);
    }
    if (fd < 0) {
        /* Permission denied is the common case for non-input-group users. */
        if (errno != EACCES && errno != ENOENT) {
            LOG_DEBUG("pad: open(%s) failed: %s", path, strerror(errno));
        }
        return false;
    }

    if (!fd_is_pad(fd)) {
        close(fd);
        return false;
    }

    i32 slot = find_free_slot();
    if (slot < 0) {
        close(fd);
        LOG_WARN("pad: no free slot for %s (max %d)", path, INPUT_MAX_PADS);
        return false;
    }

    PadDevice *d = &g_pad_sys.devices[slot];
    memset(d, 0, sizeof(*d));
    d->fd        = fd;
    d->connected = true;
    d->effect_id = -1;
    g_pad_sys.next_serial++;
    if (g_pad_sys.next_serial == 0u) g_pad_sys.next_serial++;
    d->connection_serial = g_pad_sys.next_serial;
    snprintf(d->path, sizeof(d->path), "%s", path);

    char name[128] = {0};
    if (ioctl(fd, EVIOCGNAME(sizeof(name) - 1), name) < 0) {
        snprintf(d->name, sizeof(d->name), "Unknown Pad");
    } else {
        snprintf(d->name, sizeof(d->name), "%s", name);
    }

    device_query_axes(d);
    device_query_haptic(d, writable);

    LOG_INFO("pad: connected slot=%d path=%s name=\"%s\" feedback=%d",
             slot, d->path, d->name, d->feedback_available ? 1 : 0);
    return true;
}

static void close_device(i32 slot) {
    PadDevice *d = &g_pad_sys.devices[slot];
    if (!d->connected) return;

    LOG_INFO("pad: disconnected slot=%d path=%s name=\"%s\"",
             slot, d->path, d->name);

    if (d->fd >= 0 && d->effect_id >= 0)
        (void)ioctl(d->fd, EVIOCRMFF, d->effect_id);
    if (d->fd >= 0) close(d->fd);
    memset(d, 0, sizeof(*d));
    d->fd = -1;
    d->effect_id = -1;
}

/* ---------------------------------------------------------------- */
/*  Public API                                                      */
/* ---------------------------------------------------------------- */

/* Full scan of /dev/input for pad event devices. Used at init and to
 * recover from an inotify queue overflow (events may have been lost). */
static void scan_input_dir(void) {
    DIR *dir = opendir(DEV_INPUT_DIR);
    if (!dir) {
        LOG_WARN("pad: opendir(%s) failed: %s — no pads available",
                 DEV_INPUT_DIR, strerror(errno));
        return;
    }

    struct dirent *e;
    while ((e = readdir(dir))) {
        if (strncmp(e->d_name, "event", 5) != 0) continue;
        char path[288];
        snprintf(path, sizeof(path), "%s/%s", DEV_INPUT_DIR, e->d_name);
        try_open_device(path);
    }
    closedir(dir);
}

void pad_init(void) {
    memset(&g_pad_sys, 0, sizeof(g_pad_sys));
    for (i32 i = 0; i < INPUT_MAX_PADS; i++) {
        g_pad_sys.devices[i].fd = -1;
    }

    /* inotify watcher for hot-plug. Not fatal if unavailable. */
    g_pad_sys.inotify_fd = inotify_init1(IN_NONBLOCK | IN_CLOEXEC);
    if (g_pad_sys.inotify_fd < 0) {
        LOG_WARN("pad: inotify_init1 failed (%s) — hot-plug disabled",
                 strerror(errno));
        g_pad_sys.inotify_wd = -1;
    } else {
        g_pad_sys.inotify_wd = inotify_add_watch(
            g_pad_sys.inotify_fd, DEV_INPUT_DIR,
            IN_CREATE | IN_DELETE | IN_ATTRIB);
        if (g_pad_sys.inotify_wd < 0) {
            LOG_WARN("pad: inotify_add_watch(%s) failed: %s — hot-plug disabled",
                     DEV_INPUT_DIR, strerror(errno));
            close(g_pad_sys.inotify_fd);
            g_pad_sys.inotify_fd = -1;
        }
    }

    /* Initial scan. */
    scan_input_dir();

    g_pad_sys.initialized = true;
}

static void process_inotify_events(void) {
    if (g_pad_sys.inotify_fd < 0) return;

    /* Buffer must be large enough for at least one event. */
    char buf[4096] ENGINE_ALIGN(__alignof__(struct inotify_event));
    for (;;) {
        ssize_t len = read(g_pad_sys.inotify_fd, buf, sizeof(buf));
        if (len <= 0) {
            if (len < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
                LOG_WARN("pad: inotify read failed: %s", strerror(errno));
            }
            return;
        }
        for (char *p = buf; p < buf + len; ) {
            struct inotify_event *ev = (struct inotify_event *)p;
            /* R423: IN_Q_OVERFLOW means the kernel dropped events — a pad
             * plugged during the burst would never be opened. Re-scan the
             * whole directory to recover (try_open_device dedups by path). */
            if (ev->mask & IN_Q_OVERFLOW) {
                LOG_WARN("pad: inotify queue overflow — re-scanning %s",
                         DEV_INPUT_DIR);
                scan_input_dir();
                p += sizeof(struct inotify_event) + ev->len;
                continue;
            }
            if (ev->len > 0 && strncmp(ev->name, "event", 5) == 0) {
                char path[288];
                snprintf(path, sizeof(path), "%s/%s", DEV_INPUT_DIR, ev->name);
                if (ev->mask & (IN_CREATE | IN_ATTRIB)) {
                    try_open_device(path);
                } else if (ev->mask & IN_DELETE) {
                    i32 slot = find_slot_by_path(path);
                    if (slot >= 0) close_device(slot);
                }
            }
            p += sizeof(struct inotify_event) + ev->len;
        }
    }
}

static void process_device_events(i32 slot, PadState *out) {
    PadDevice *d = &g_pad_sys.devices[slot];
    if (!d->connected) return;

    struct input_event ev;
    for (;;) {
        ssize_t n = read(d->fd, &ev, sizeof(ev));
        if (n == (ssize_t)sizeof(ev)) {
            if (ev.type == EV_KEY) {
                i32 idx = evdev_btn_to_pad(ev.code);
                if (idx >= 0 && idx < INPUT_MAX_PAD_BUTTONS) {
                    apply_button_state(&out->buttons[idx], ev.value != 0);
                }
            } else if (ev.type == EV_ABS) {
                i32 ax = -1;
                bool is_trigger = false;
                switch (ev.code) {
                    case ABS_X:     ax = PAD_AXIS_LEFT_X;   break;
                    case ABS_Y:     ax = PAD_AXIS_LEFT_Y;   break;
                    case ABS_RX:    ax = PAD_AXIS_RIGHT_X;  break;
                    case ABS_RY:    ax = PAD_AXIS_RIGHT_Y;  break;
                    case ABS_Z:
                    case ABS_BRAKE:
                        ax = PAD_AXIS_LTRIGGER; is_trigger = true; break;
                    case ABS_RZ:
                    case ABS_GAS:
                        ax = PAD_AXIS_RTRIGGER; is_trigger = true; break;
                    case ABS_HAT0X: {
                        bool left  = ev.value < 0;
                        bool right = ev.value > 0;
                        apply_button_state(&out->buttons[PAD_BTN_DPAD_LEFT],  left);
                        apply_button_state(&out->buttons[PAD_BTN_DPAD_RIGHT], right);
                        break;
                    }
                    case ABS_HAT0Y: {
                        bool up   = ev.value < 0;
                        bool down = ev.value > 0;
                        apply_button_state(&out->buttons[PAD_BTN_DPAD_UP],   up);
                        apply_button_state(&out->buttons[PAD_BTN_DPAD_DOWN], down);
                        break;
                    }
                    default: break;
                }
                if (ax >= 0 && ax < INPUT_MAX_AXES &&
                    ev.code < ABS_CNT &&
                    d->abs_info[ev.code].present) {
                    if (is_trigger) {
                        out->axes[ax] = normalize_trigger(
                            ev.value,
                            d->abs_info[ev.code].min,
                            d->abs_info[ev.code].max);
                    } else {
                        out->axes[ax] = normalize_axis(
                            ev.value,
                            d->abs_info[ev.code].min,
                            d->abs_info[ev.code].max);
                    }
                }
            }
            continue;
        }
        if (n < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                return;
            }
            /* ENODEV is the typical "device gone" signal. */
            LOG_INFO("pad: read failed slot=%d (%s) — disconnecting",
                     slot, strerror(errno));
            close_device(slot);
            return;
        }
        /* Short read (n == 0 or partial): nothing to do this frame. */
        return;
    }
}

void pad_poll(PadState *out_pads) {
    if (!g_pad_sys.initialized || !out_pads) return;

    process_inotify_events();

    for (i32 i = 0; i < INPUT_MAX_PADS; i++) {
        PadDevice *d = &g_pad_sys.devices[i];
        PadState  *s = &out_pads[i];

        if (!d->connected) {
            if (s->connected) {
                /* Clear state on the frame we observe disconnect. */
                memset(s->axes, 0, sizeof(s->axes));
                for (i32 b = 0; b < INPUT_MAX_PAD_BUTTONS; b++) {
                    apply_button_state(&s->buttons[b], false);
                }
                s->connected = false;
                s->name[0]   = 0;
            }
            continue;
        }

        if (!s->connected) {
            s->connected = true;
            snprintf(s->name, sizeof(s->name), "%s", d->name);
        }

        process_device_events(i, s);
    }
}

static InputExtResult linux_haptic_error(void) {
    return errno == ENODEV ? INPUT_EXT_DISCONNECTED : INPUT_EXT_FAILED;
}

static InputExtResult linux_device_haptic(PadDevice *d,
                                          const InputHapticCommand *command) {
    struct input_event event;
    ssize_t written;
    if (d == NULL || command == NULL) return INPUT_EXT_INVALID;
    if (!d->connected) return INPUT_EXT_DISCONNECTED;
    if (!d->feedback_available) return INPUT_EXT_UNSUPPORTED;
    if (command->duration_ms == 0u && d->effect_id < 0) return INPUT_EXT_OK;

    if (command->duration_ms != 0u) {
        struct ff_effect effect;
        memset(&effect, 0, sizeof(effect));
        effect.type = FF_RUMBLE;
        effect.id = d->effect_id;
        effect.replay.length = (u16)command->duration_ms;
        effect.u.rumble.strong_magnitude = (u16)(command->low * 65535.0f + 0.5f);
        effect.u.rumble.weak_magnitude = (u16)(command->high * 65535.0f + 0.5f);
        if (ioctl(d->fd, EVIOCSFF, &effect) < 0) return linux_haptic_error();
        d->effect_id = effect.id;
    }

    memset(&event, 0, sizeof(event));
    event.type = EV_FF;
    event.code = (u16)d->effect_id;
    event.value = command->duration_ms == 0u ? 0 : 1;
    written = write(d->fd, &event, sizeof(event));
    if (written == (ssize_t)sizeof(event)) return INPUT_EXT_OK;
    if (written < 0) return linux_haptic_error();
    return INPUT_EXT_FAILED;
}

static InputExtResult linux_execute_haptic(void *context,
                                           const InputHapticCommand *command) {
    InputExtResult result;
    (void)context;
    if (command->pad >= INPUT_MAX_PADS) return INPUT_EXT_INVALID;
    result = linux_device_haptic(&g_pad_sys.devices[command->pad], command);
    if (result == INPUT_EXT_DISCONNECTED) close_device((i32)command->pad);
    return result;
}

static void sync_haptic_pads(InputExtended *extended) {
    for (u32 i = 0; i < INPUT_MAX_PADS; i++) {
        const PadDevice *d = &g_pad_sys.devices[i];
        input_extended_backend_pad(extended, i, d->connected,
                                   d->feedback_available, d->connection_serial);
    }
}

void pad_feedback_poll(InputExtended *extended) {
    if (!g_pad_sys.initialized || extended == NULL) return;
    sync_haptic_pads(extended);
    (void)input_extended_haptic_pump(extended, linux_execute_haptic, NULL);
    sync_haptic_pads(extended);
}

void pad_shutdown(void) {
    if (!g_pad_sys.initialized) return;

    for (i32 i = 0; i < INPUT_MAX_PADS; i++) {
        if (g_pad_sys.devices[i].connected) {
            close_device(i);
        }
    }

    if (g_pad_sys.inotify_wd >= 0 && g_pad_sys.inotify_fd >= 0) {
        inotify_rm_watch(g_pad_sys.inotify_fd, g_pad_sys.inotify_wd);
    }
    if (g_pad_sys.inotify_fd >= 0) {
        close(g_pad_sys.inotify_fd);
    }
    memset(&g_pad_sys, 0, sizeof(g_pad_sys));
}

#endif /* ENGINE_PLATFORM_LINUX */
