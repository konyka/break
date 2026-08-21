#ifdef ENGINE_PLATFORM_WAYLAND

#include <platform/platform.h>
#include <platform/input.h>
#include <platform/platform_text.h>
#include <core/log.h>
#include "gamepad_linux.h"

#include <wayland-client.h>
#include <wayland-cursor.h>
#include <wayland-egl.h>
#include <xkbcommon/xkbcommon.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h> /* R419: non-blocking socket check in platform_poll */
#include <sys/mman.h>
#include <linux/input-event-codes.h>

#include "xdg-shell-client-protocol.h"
#include "relative-pointer-unstable-v1-client-protocol.h"
#include "pointer-constraints-unstable-v1-client-protocol.h"
#include "text-input-unstable-v3-client-protocol.h"
#ifdef ENGINE_WAYLAND_CURSOR_SHAPE
#include "cursor-shape-v1-client-protocol.h"
#endif
#include "xdg-output-unstable-v1-client-protocol.h" /* R443 */
#ifdef ENGINE_WAYLAND_FRACTIONAL_SCALE
#include "fractional-scale-v1-client-protocol.h"
#include "viewporter-client-protocol.h"
#endif
#include "wayland_output.h"                         /* R443: pure output-list logic */

/* ---- Platform state ---- */

/* R443: per-output listener context — wl_output events for different outputs
 * may interleave on the wire, so handlers must not share a "current" slot. */
typedef struct {
    struct Platform *p;
    u32              global_name;
} WaylandOutputCtx;

typedef struct {
    struct wl_data_offer *offer;
    const char *mime_type;
} WaylandClipboardOffer;

typedef struct WaylandClipboardSource WaylandClipboardSource;
typedef struct WaylandClipboardWrite WaylandClipboardWrite;

struct WaylandClipboardSource {
    struct Platform *platform;
    struct wl_data_source *source;
    char *text;
    usize length;
    WaylandClipboardSource *next;
};

struct WaylandClipboardWrite {
    int fd;
    char *text;
    usize length;
    usize offset;
    WaylandClipboardWrite *next;
};

#define WAYLAND_CLIPBOARD_MAX_BYTES (16u * 1024u * 1024u)
#define WAYLAND_MIME_UTF8 "text/plain;charset=utf-8"
#define WAYLAND_MIME_TEXT "text/plain"

struct Platform {
    struct wl_display    *display;
    struct wl_registry   *registry;
    struct wl_compositor *compositor;
    struct wl_shm        *shm;
    struct wl_surface    *surface;
    struct wl_seat       *seat;
    u32                   seat_global_name;
    struct wl_keyboard   *keyboard;
    struct wl_pointer    *pointer;
    struct wl_data_device_manager *data_device_manager;
    struct wl_data_device *data_device;
    WaylandClipboardSource *clipboard_source;
    WaylandClipboardSource *clipboard_sources;
    WaylandClipboardOffer *clipboard_offer;
    WaylandClipboardOffer *drag_offer;
    char *clipboard_text;
    usize clipboard_length;
    char *clipboard_read_buffer;
    usize clipboard_read_length;
    usize clipboard_read_capacity;
    int clipboard_read_fd;
    WaylandClipboardWrite *clipboard_writes;
    bool clipboard_offer_read_complete;
    u32 keyboard_serial;
    bool clipboard_publish_pending;
#ifdef ENGINE_WAYLAND_CURSOR_SHAPE
    struct wp_cursor_shape_manager_v1 *cursor_shape_manager;
    struct wp_cursor_shape_device_v1  *cursor_shape_device;
#endif
    struct wl_cursor_theme *cursor_theme;
    struct wl_surface      *cursor_surface;
    struct xdg_wm_base   *xdg_wm_base;
    struct xdg_surface   *xdg_surface;
    struct xdg_toplevel  *toplevel;
#ifdef ENGINE_WAYLAND_FRACTIONAL_SCALE
    struct wp_fractional_scale_manager_v1 *fractional_scale_manager;
    struct wp_fractional_scale_v1         *fractional_scale;
    struct wp_viewporter                   *viewporter;
    struct wp_viewport                     *viewport;
    u32                                     preferred_scale_120;
#endif

    /* R443: multi-output enumeration — one slot per bound wl_output global
     * (was a single struct wl_output *, which leaked every binding past the
     * first and mixed all outputs' events into monitors[monitor_count]). */
    struct wl_output               *outputs[WAYLAND_OUTPUT_MAX];
    struct zxdg_output_manager_v1  *xdg_output_mgr;   /* optional */
    struct zxdg_output_v1          *xdg_outputs[WAYLAND_OUTPUT_MAX];
    WaylandOutputList               output_list;
    WaylandOptionalGlobals          optional_globals;
    WaylandOutputCtx               *output_ctx[WAYLAND_OUTPUT_MAX];
    u32                             surface_outputs[WAYLAND_OUTPUT_MAX];
    u32                             surface_output_count;

    /* Relative pointer + pointer constraints (unstable v1) */
    struct zwp_relative_pointer_manager_v1 *rel_pointer_mgr;
    struct zwp_pointer_constraints_v1      *pointer_constraints;
    struct zwp_relative_pointer_v1         *rel_pointer;
    struct zwp_locked_pointer_v1           *locked_pointer;

    struct zwp_text_input_manager_v3 *text_input_manager;
    struct zwp_text_input_v3         *text_input;
    PlatformTextQueue                  text_queue;
    char                              *pending_preedit;
    char                              *pending_commit;
    i32                                pending_cursor;
    i32                                pending_delete_before;
    i32                                pending_delete_after;
    bool                               pending_preedit_set;
    bool                               pending_commit_set;
    bool                               pending_delete_set;
    bool                               ime_enabled;
    bool                               text_input_focused;
    i32                                ime_spot_x;
    i32                                ime_spot_y;
    PlatformImeSurrounding             ime_surrounding;

    /* EGL / Vulkan window */
    struct wl_egl_window *egl_window;

    /* XKB keyboard state */
    struct xkb_context  *xkb_ctx;
    struct xkb_keymap   *xkb_keymap;
    struct xkb_state    *xkb_state;

    InputState input;
    u32 width, height;
    bool should_close;
    bool configured;
    bool is_fullscreen;
    i32 scale;
    i32 primary_scale;
    u32 content_scale_120;

    /* Mouse state */
    bool mouse_captured;
    bool mouse_visible;
    bool mouse_relative;
    f64 pointer_x, pointer_y;
    u32 pointer_enter_serial;   /* needed for wl_pointer_set_cursor */
    u32 pointer_button_serial;  /* required by xdg_toplevel_move */
    PlatformCursor cursor;

    /* DPI / Monitor — R443: per-output data lives in output_list (converted
     * to MonitorInfo on query); dpi/scale mirror the primary (slot 0) output. */
    f32 dpi;
};

/* Forward decls for relative-pointer wiring. */
static void wayland_apply_relative(Platform *p);
static void wayland_clear_relative(Platform *p);
static void wayland_update_cursor_visibility(Platform *p);
static void wayland_commit_text_input_state(Platform *p);
static void wayland_create_cursor_device(Platform *p);
static void wayland_create_data_device(Platform *p);
static void wayland_destroy_data_device(Platform *p);
static void wayland_create_text_input(Platform *p);
static void wayland_clear_text_input(Platform *p);
static void wayland_clipboard_publish(Platform *p);
static void wayland_update_surface_scale(Platform *p);
static void wayland_try_enable_fractional_scale(Platform *p);

static void wayland_clipboard_free_text(Platform *p) {
    free(p->clipboard_text);
    p->clipboard_text = NULL;
    p->clipboard_length = 0;
}

static void wayland_clipboard_destroy_sources(Platform *p) {
    while (p->clipboard_sources != NULL) {
        WaylandClipboardSource *source = p->clipboard_sources;
        p->clipboard_sources = source->next;
        if (source->source != NULL) wl_data_source_destroy(source->source);
        free(source->text);
        free(source);
    }
    p->clipboard_source = NULL;
}

static bool wayland_clipboard_set_cached(Platform *p, const char *text,
                                         usize length) {
    char *copy;
    if (length >= WAYLAND_CLIPBOARD_MAX_BYTES) return false;
    copy = malloc(length + 1);
    if (copy == NULL) return false;
    if (length > 0 && text != NULL) memcpy(copy, text, length);
    copy[length] = '\0';
    wayland_clipboard_free_text(p);
    p->clipboard_text = copy;
    p->clipboard_length = length;
    return true;
}

static char *wayland_clipboard_duplicate(const char *text) {
    usize length;
    char *copy;
    if (text == NULL) return NULL;
    length = strlen(text);
    copy = malloc(length + 1);
    if (copy != NULL) memcpy(copy, text, length + 1);
    return copy;
}

static void wayland_clipboard_offer_destroy(WaylandClipboardOffer **slot) {
    WaylandClipboardOffer *offer;
    if (slot == NULL || *slot == NULL) return;
    offer = *slot;
    if (offer->offer != NULL) wl_data_offer_destroy(offer->offer);
    free(offer);
    *slot = NULL;
}

static void wayland_clipboard_finish_read(Platform *p, bool success) {
    if (p->clipboard_read_fd >= 0) {
        close(p->clipboard_read_fd);
        p->clipboard_read_fd = -1;
    }
    if (success && p->clipboard_read_buffer != NULL) {
        p->clipboard_read_buffer[p->clipboard_read_length] = '\0';
        wayland_clipboard_free_text(p);
        p->clipboard_text = p->clipboard_read_buffer;
        p->clipboard_length = p->clipboard_read_length;
        p->clipboard_read_buffer = NULL;
        p->clipboard_offer_read_complete = true;
    }
    free(p->clipboard_read_buffer);
    p->clipboard_read_buffer = NULL;
    p->clipboard_read_length = 0;
    p->clipboard_read_capacity = 0;
}

static bool wayland_clipboard_grow_read_buffer(Platform *p) {
    usize next_capacity;
    char *next;
    if (p->clipboard_read_capacity > p->clipboard_read_length + 1)
        return true;
    if (p->clipboard_read_capacity >= WAYLAND_CLIPBOARD_MAX_BYTES + 1)
        return false;
    next_capacity = p->clipboard_read_capacity == 0 ? 4096
                                                      : p->clipboard_read_capacity * 2;
    if (next_capacity > WAYLAND_CLIPBOARD_MAX_BYTES + 1)
        next_capacity = WAYLAND_CLIPBOARD_MAX_BYTES + 1;
    next = realloc(p->clipboard_read_buffer, next_capacity);
    if (next == NULL) return false;
    p->clipboard_read_buffer = next;
    p->clipboard_read_capacity = next_capacity;
    return true;
}

static void wayland_clipboard_drain(Platform *p) {
    for (;;) {
        ssize_t count;
        if (p->clipboard_read_fd < 0) return;
        if (!wayland_clipboard_grow_read_buffer(p)) {
            wayland_clipboard_finish_read(p, false);
            return;
        }
        count = read(p->clipboard_read_fd,
                     p->clipboard_read_buffer + p->clipboard_read_length,
                     p->clipboard_read_capacity - p->clipboard_read_length - 1);
        if (count > 0) {
            p->clipboard_read_length += (usize)count;
            continue;
        }
        if (count == 0) {
            wayland_clipboard_finish_read(p, true);
            return;
        }
        if (errno == EINTR) continue;
        if (errno == EAGAIN || errno == EWOULDBLOCK) return;
        wayland_clipboard_finish_read(p, false);
        return;
    }
}

static void wayland_clipboard_drain_writes(Platform *p) {
    WaylandClipboardWrite **link = &p->clipboard_writes;
    while (*link != NULL) {
        WaylandClipboardWrite *write_state = *link;
        bool complete = false;
        while (write_state->offset < write_state->length) {
            ssize_t written = write(write_state->fd,
                                    write_state->text + write_state->offset,
                                    write_state->length - write_state->offset);
            if (written > 0) {
                write_state->offset += (usize)written;
            } else if (written < 0 && errno == EINTR) {
                continue;
            } else if (written < 0 &&
                       (errno == EAGAIN || errno == EWOULDBLOCK)) {
                break;
            } else {
                complete = true;
                break;
            }
        }
        if (write_state->offset == write_state->length) complete = true;
        if (!complete) {
            link = &write_state->next;
            continue;
        }
        close(write_state->fd);
        *link = write_state->next;
        free(write_state->text);
        free(write_state);
    }
}

static void wayland_clipboard_clear_writes(Platform *p) {
    while (p->clipboard_writes != NULL) {
        WaylandClipboardWrite *write_state = p->clipboard_writes;
        p->clipboard_writes = write_state->next;
        close(write_state->fd);
        free(write_state->text);
        free(write_state);
    }
}

static void wayland_destroy_data_device(Platform *p) {
    if (p == NULL) return;
    wayland_clipboard_finish_read(p, false);
    wayland_clipboard_clear_writes(p);
    wayland_clipboard_offer_destroy(&p->clipboard_offer);
    wayland_clipboard_offer_destroy(&p->drag_offer);
    wayland_clipboard_destroy_sources(p);
    if (p->data_device != NULL) {
        wl_data_device_release(p->data_device);
        p->data_device = NULL;
    }
    p->clipboard_publish_pending = false;
}

static void clipboard_offer_offer(void *data, struct wl_data_offer *offer,
                                  const char *mime_type) {
    WaylandClipboardOffer *state = data;
    (void)offer;
    if (state == NULL || mime_type == NULL) return;
    if (strcmp(mime_type, WAYLAND_MIME_UTF8) == 0) {
        state->mime_type = WAYLAND_MIME_UTF8;
    } else if (strcmp(mime_type, WAYLAND_MIME_TEXT) == 0 &&
               state->mime_type == NULL) {
        state->mime_type = WAYLAND_MIME_TEXT;
    }
}

static void clipboard_offer_source_actions(void *data,
                                           struct wl_data_offer *offer,
                                           u32 actions) {
    (void)data;
    (void)offer;
    (void)actions;
}

static void clipboard_offer_action(void *data, struct wl_data_offer *offer,
                                   u32 action) {
    (void)data;
    (void)offer;
    (void)action;
}

static const struct wl_data_offer_listener clipboard_offer_listener = {
    .offer = clipboard_offer_offer,
    .source_actions = clipboard_offer_source_actions,
    .action = clipboard_offer_action,
};

static void clipboard_source_target(void *data, struct wl_data_source *source,
                                    const char *mime_type) {
    (void)data;
    (void)source;
    (void)mime_type;
}

static void clipboard_source_send(void *data, struct wl_data_source *source,
                                  const char *mime_type, i32 fd) {
    WaylandClipboardSource *clipboard_source = data;
    Platform *p = clipboard_source != NULL ? clipboard_source->platform : NULL;
    WaylandClipboardWrite *write_state;
    (void)source;
    if (p == NULL || mime_type == NULL || clipboard_source->text == NULL) {
        close(fd);
        return;
    }
    write_state = calloc(1, sizeof(*write_state));
    if (write_state == NULL) {
        close(fd);
        return;
    }
    write_state->text = malloc(clipboard_source->length + 1);
    if (write_state->text == NULL ||
        fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK) < 0) {
        free(write_state->text);
        free(write_state);
        close(fd);
        return;
    }
    memcpy(write_state->text, clipboard_source->text, clipboard_source->length);
    write_state->fd = fd;
    write_state->length = clipboard_source->length;
    write_state->next = p->clipboard_writes;
    p->clipboard_writes = write_state;
    wayland_clipboard_drain_writes(p);
}

static void clipboard_source_cancelled(void *data, struct wl_data_source *source) {
    WaylandClipboardSource *clipboard_source = data;
    Platform *p = clipboard_source != NULL ? clipboard_source->platform : NULL;
    if (p != NULL) {
        WaylandClipboardSource **link = &p->clipboard_sources;
        while (*link != NULL && *link != clipboard_source) link = &(*link)->next;
        if (*link == clipboard_source) *link = clipboard_source->next;
        if (p->clipboard_source == clipboard_source) p->clipboard_source = NULL;
    }
    wl_data_source_destroy(source);
    free(clipboard_source->text);
    free(clipboard_source);
}

static void clipboard_source_dnd_drop_performed(void *data,
                                                struct wl_data_source *source) {
    (void)data;
    (void)source;
}

static void clipboard_source_dnd_finished(void *data,
                                          struct wl_data_source *source) {
    (void)data;
    (void)source;
}

static void clipboard_source_action(void *data, struct wl_data_source *source,
                                    u32 action) {
    (void)data;
    (void)source;
    (void)action;
}

static const struct wl_data_source_listener clipboard_source_listener = {
    .target = clipboard_source_target,
    .send = clipboard_source_send,
    .cancelled = clipboard_source_cancelled,
    .dnd_drop_performed = clipboard_source_dnd_drop_performed,
    .dnd_finished = clipboard_source_dnd_finished,
    .action = clipboard_source_action,
};

static void clipboard_device_data_offer(void *data,
                                        struct wl_data_device *device,
                                        struct wl_data_offer *offer) {
    WaylandClipboardOffer *state;
    (void)data;
    (void)device;
    state = calloc(1, sizeof(*state));
    if (state == NULL) return;
    state->offer = offer;
    wl_data_offer_add_listener(offer, &clipboard_offer_listener, state);
    wl_data_offer_set_user_data(offer, state);
}

static void clipboard_device_enter(void *data, struct wl_data_device *device,
                                   u32 serial, struct wl_surface *surface,
                                   wl_fixed_t x, wl_fixed_t y,
                                   struct wl_data_offer *offer) {
    Platform *p = data;
    WaylandClipboardOffer *state = wl_data_offer_get_user_data(offer);
    (void)device;
    (void)serial;
    (void)surface;
    (void)x;
    (void)y;
    wayland_clipboard_offer_destroy(&p->drag_offer);
    p->drag_offer = state;
}

static void clipboard_device_leave(void *data, struct wl_data_device *device) {
    Platform *p = data;
    (void)device;
    wayland_clipboard_offer_destroy(&p->drag_offer);
}

static void clipboard_device_motion(void *data, struct wl_data_device *device,
                                    u32 time, wl_fixed_t x, wl_fixed_t y) {
    (void)data;
    (void)device;
    (void)time;
    (void)x;
    (void)y;
}

static void clipboard_device_drop(void *data, struct wl_data_device *device) {
    (void)data;
    (void)device;
}

static void clipboard_device_selection(void *data,
                                       struct wl_data_device *device,
                                       struct wl_data_offer *offer) {
    Platform *p = data;
    WaylandClipboardOffer *state = offer != NULL ? wl_data_offer_get_user_data(offer)
                                                  : NULL;
    (void)device;
    if (p->clipboard_offer != state)
        wayland_clipboard_offer_destroy(&p->clipboard_offer);
    p->clipboard_offer = state;
    wayland_clipboard_finish_read(p, false);
    p->clipboard_offer_read_complete = false;
    if (state == NULL && p->clipboard_source == NULL)
        wayland_clipboard_free_text(p);
}

static const struct wl_data_device_listener clipboard_device_listener = {
    .data_offer = clipboard_device_data_offer,
    .enter = clipboard_device_enter,
    .leave = clipboard_device_leave,
    .motion = clipboard_device_motion,
    .drop = clipboard_device_drop,
    .selection = clipboard_device_selection,
};

static void wayland_create_data_device(Platform *p) {
    if (p->data_device_manager == NULL || p->seat == NULL ||
        p->data_device != NULL) return;
    p->data_device = wl_data_device_manager_get_data_device(p->data_device_manager,
                                                              p->seat);
    if (p->data_device != NULL)
        wl_data_device_add_listener(p->data_device, &clipboard_device_listener, p);
}

static void wayland_clipboard_publish(Platform *p) {
    if (p->data_device == NULL || p->clipboard_source == NULL ||
        p->keyboard_serial == 0) {
        p->clipboard_publish_pending = true;
        return;
    }
    wl_data_device_set_selection(p->data_device, p->clipboard_source->source,
                                 p->keyboard_serial);
    wl_display_flush(p->display);
    p->clipboard_publish_pending = false;
}

static bool wayland_text_replace(char **out, const char *text) {
    char *copy;
    usize length;
    if (out == NULL) return false;
    if (text == NULL) text = "";
    length = strlen(text);
    if (length > PLATFORM_TEXT_MAX_BYTES) return false;
    copy = malloc(length + 1);
    if (copy == NULL) return false;
    memcpy(copy, text, length + 1);
    free(*out);
    *out = copy;
    return true;
}

/* ---- text-input-unstable-v3 listener ---- */

static void text_input_enter(void *data, struct zwp_text_input_v3 *text_input,
                             struct wl_surface *surface) {
    Platform *p = data;
    (void)text_input;
    p->text_input_focused = surface == p->surface;
    wayland_commit_text_input_state(p);
}

static void text_input_leave(void *data, struct zwp_text_input_v3 *text_input,
                             struct wl_surface *surface) {
    Platform *p = data;
    (void)text_input;
    (void)surface;
    p->text_input_focused = false;
    free(p->pending_preedit);
    p->pending_preedit = NULL;
    free(p->pending_commit);
    p->pending_commit = NULL;
    p->pending_preedit_set = false;
    p->pending_commit_set = false;
    p->pending_delete_set = false;
    (void)platform_text_queue_push(&p->text_queue, PLATFORM_TEXT_PREEDIT,
                                   "", 0);
}

static void text_input_preedit_string(void *data,
                                      struct zwp_text_input_v3 *text_input,
                                      const char *text, i32 cursor_begin,
                                      i32 cursor_end) {
    Platform *p = data;
    (void)text_input;
    (void)cursor_end;
    if (!wayland_text_replace(&p->pending_preedit, text)) return;
    p->pending_cursor = platform_utf8_byte_to_codepoints(text, cursor_begin);
    p->pending_preedit_set = true;
}

static void text_input_commit_string(void *data,
                                     struct zwp_text_input_v3 *text_input,
                                     const char *text) {
    Platform *p = data;
    (void)text_input;
    if (!wayland_text_replace(&p->pending_commit, text)) return;
    p->pending_commit_set = true;
}

static void text_input_delete_surrounding(void *data,
                                          struct zwp_text_input_v3 *text_input,
                                          u32 before_length, u32 after_length) {
    Platform *p = data;
    (void)text_input;
    p->pending_delete_before = before_length > INT32_MAX ? INT32_MAX
                                                           : (i32)before_length;
    p->pending_delete_after = after_length > INT32_MAX ? INT32_MAX
                                                         : (i32)after_length;
    p->pending_delete_set = true;
}

static void text_input_done(void *data, struct zwp_text_input_v3 *text_input,
                            u32 serial) {
    Platform *p = data;
    (void)text_input;
    (void)serial;
    if (p->ime_enabled && p->text_input_focused) {
        if (p->pending_delete_set) {
            (void)platform_text_queue_push_delete(
                &p->text_queue, p->pending_delete_before, p->pending_delete_after);
        }
        if (p->pending_commit_set && p->pending_commit != NULL &&
            p->pending_commit[0] != '\0') {
            (void)platform_text_queue_push(&p->text_queue, PLATFORM_TEXT_COMMIT,
                                           p->pending_commit, 0);
        }
        if (p->pending_preedit_set && p->pending_preedit != NULL) {
            (void)platform_text_queue_push(&p->text_queue, PLATFORM_TEXT_PREEDIT,
                                           p->pending_preedit, p->pending_cursor);
        }
    }
    free(p->pending_preedit);
    p->pending_preedit = NULL;
    free(p->pending_commit);
    p->pending_commit = NULL;
    p->pending_preedit_set = false;
    p->pending_commit_set = false;
    p->pending_delete_set = false;
}

static void text_input_action(void *data, struct zwp_text_input_v3 *text_input,
                              u32 action, u32 serial) {
    (void)data;
    (void)text_input;
    (void)action;
    (void)serial;
}

static void text_input_language(void *data, struct zwp_text_input_v3 *text_input,
                                const char *language) {
    (void)data;
    (void)text_input;
    (void)language;
}

static void text_input_preedit_hint(void *data,
                                    struct zwp_text_input_v3 *text_input,
                                    u32 start, u32 end, u32 hint) {
    (void)data;
    (void)text_input;
    (void)start;
    (void)end;
    (void)hint;
}

static const struct zwp_text_input_v3_listener text_input_listener = {
    .enter = text_input_enter,
    .leave = text_input_leave,
    .preedit_string = text_input_preedit_string,
    .commit_string = text_input_commit_string,
    .delete_surrounding_text = text_input_delete_surrounding,
    .done = text_input_done,
    .action = text_input_action,
    .language = text_input_language,
    .preedit_hint = text_input_preedit_hint,
};

static void wayland_clear_text_input(Platform *p) {
    if (p == NULL) return;
    if (p->text_input != NULL) {
        zwp_text_input_v3_destroy(p->text_input);
        p->text_input = NULL;
    }
    p->text_input_focused = false;
    free(p->pending_preedit);
    p->pending_preedit = NULL;
    free(p->pending_commit);
    p->pending_commit = NULL;
    p->pending_preedit_set = false;
    p->pending_commit_set = false;
    p->pending_delete_set = false;
}

static void wayland_create_text_input(Platform *p) {
    if (p == NULL || p->text_input_manager == NULL || p->seat == NULL ||
        p->text_input != NULL) return;
    p->text_input = zwp_text_input_manager_v3_get_text_input(
        p->text_input_manager, p->seat);
    if (p->text_input != NULL)
        zwp_text_input_v3_add_listener(p->text_input, &text_input_listener, p);
}

static void wayland_commit_text_input_state(Platform *p) {
    if (p->text_input == NULL || !p->text_input_focused) return;
    if (p->ime_enabled) {
        zwp_text_input_v3_enable(p->text_input);
        zwp_text_input_v3_set_content_type(
            p->text_input, ZWP_TEXT_INPUT_V3_CONTENT_HINT_NONE,
            ZWP_TEXT_INPUT_V3_CONTENT_PURPOSE_NORMAL);
        zwp_text_input_v3_set_surrounding_text(
            p->text_input, p->ime_surrounding.utf8, p->ime_surrounding.cursor,
            p->ime_surrounding.anchor);
        zwp_text_input_v3_set_cursor_rectangle(p->text_input, p->ime_spot_x,
                                                p->ime_spot_y, 1, 1);
    } else {
        zwp_text_input_v3_disable(p->text_input);
    }
    zwp_text_input_v3_commit(p->text_input);
    if (p->surface != NULL) wl_surface_commit(p->surface);
}

/* ---- Key mapping (XKB keysyms are identical to X11 KeySyms) ---- */

static i32 wayland_keysym_to_engine(xkb_keysym_t ks) {
    if (ks >= XKB_KEY_a && ks <= XKB_KEY_z) return (i32)ks;
    if (ks >= XKB_KEY_A && ks <= XKB_KEY_Z) return (i32)(ks - XKB_KEY_A + 'a');
    if (ks >= XKB_KEY_0 && ks <= XKB_KEY_9) return (i32)ks;
    if (ks == XKB_KEY_Escape)    return 256;
    if (ks == XKB_KEY_space)     return 32;
    if (ks == XKB_KEY_Return || ks == XKB_KEY_KP_Enter) return 257; /* R371: keypad Enter = Select */
    if (ks == XKB_KEY_Tab)       return 259;
    if (ks == XKB_KEY_BackSpace) return 260;
    if (ks == XKB_KEY_Left)      return 261;
    if (ks == XKB_KEY_Right)     return 262;
    if (ks == XKB_KEY_Up)        return 263;
    if (ks == XKB_KEY_Down)      return 264;
    if (ks >= XKB_KEY_F1 && ks <= XKB_KEY_F12) return (i32)(ks - XKB_KEY_F1 + 271);
    if (ks == XKB_KEY_Page_Up)   return 283;
    if (ks == XKB_KEY_Page_Down) return 284;
    if (ks == XKB_KEY_Home)      return 285;
    if (ks == XKB_KEY_End)       return 286;
    if (ks == XKB_KEY_Insert)    return 287;
    if (ks == XKB_KEY_Delete)    return 288;
    /* R360: disambiguate End/Insert dual-binds in main (reset/DOF). */
    if (ks == XKB_KEY_Pause)       return 291;
    if (ks == XKB_KEY_Scroll_Lock) return 292;
    if (ks == XKB_KEY_Num_Lock)    return 293;
    if (ks == XKB_KEY_Caps_Lock)   return 294;
    if (ks == XKB_KEY_Menu)        return 295; /* R361: SSGI (was '[') */
    if (ks == XKB_KEY_KP_Multiply) return 296; /* R361: SSS */
    if (ks == XKB_KEY_KP_Divide)   return 297; /* R361: lens flare */
    if (ks == XKB_KEY_KP_Subtract) return 298; /* R361: sharpen */
    if (ks == XKB_KEY_KP_Add)      return 299; /* R361: contact shadow */
    /* R363: boom was 300 (=INPUT_MOUSE_LEFT); KP_* live at 305+ */
    if (ks == XKB_KEY_KP_0 || ks == XKB_KEY_KP_Insert) return 305; /* particle boom */
    if (ks == XKB_KEY_KP_1 || ks == XKB_KEY_KP_End)    return 306; /* tornado */
    if (ks == XKB_KEY_KP_2 || ks == XKB_KEY_KP_Down)   return 307; /* particle trail */
    if (ks == XKB_KEY_KP_3 || ks == XKB_KEY_KP_Next)   return 308; /* layout */
    if (ks == XKB_KEY_KP_4 || ks == XKB_KEY_KP_Left)   return 309; /* AA cycle */
    /* R364: CG/lens off digit row (FPS is Shift+`) */
    if (ks == XKB_KEY_KP_5 || ks == XKB_KEY_KP_Begin)  return 310; /* temp- */
    if (ks == XKB_KEY_KP_6 || ks == XKB_KEY_KP_Right)  return 311; /* temp+ */
    if (ks == XKB_KEY_KP_7 || ks == XKB_KEY_KP_Home)   return 312; /* tint- */
    if (ks == XKB_KEY_KP_8 || ks == XKB_KEY_KP_Up)     return 313; /* tint+ */
    if (ks == XKB_KEY_KP_9 || ks == XKB_KEY_KP_Prior)  return 314; /* color grade */
    if (ks == XKB_KEY_KP_Decimal || ks == XKB_KEY_KP_Delete) return 315; /* lensfx / CA / vig cycle */
    if (ks == XKB_KEY_Shift_L || ks == XKB_KEY_Shift_R) return 289;
    if (ks == XKB_KEY_Control_L || ks == XKB_KEY_Control_R) return 290; /* R366: anim crossfade */
    if (ks == XKB_KEY_minus || ks == XKB_KEY_underscore)      return (i32)'-';
    if (ks == XKB_KEY_plus || ks == XKB_KEY_equal)            return (i32)'=';
    if (ks == XKB_KEY_parenleft || ks == XKB_KEY_braceleft)   return (i32)'(';
    if (ks == XKB_KEY_parenright || ks == XKB_KEY_braceright) return (i32)')';
    if (ks == XKB_KEY_bracketleft)  return (i32)'[';
    if (ks == XKB_KEY_bracketright) return (i32)']';
    if (ks == XKB_KEY_slash || ks == XKB_KEY_question)    return (i32)'/';
    if (ks == XKB_KEY_backslash || ks == XKB_KEY_bar)     return (i32)'\\';
    if (ks == XKB_KEY_grave || ks == XKB_KEY_asciitilde)  return (i32)'`';
    if (ks == XKB_KEY_semicolon || ks == XKB_KEY_colon)   return (i32)';';
    if (ks == XKB_KEY_apostrophe || ks == XKB_KEY_quotedbl) return (i32)'\'';
    if (ks == XKB_KEY_comma)  return (i32)',';
    if (ks == XKB_KEY_period) return (i32)'.';
    return -1;
}

/* ---- XDG WM Base (ping/pong) ---- */

static void xdg_wm_base_ping(void *data, struct xdg_wm_base *base, u32 serial) {
    (void)data;
    xdg_wm_base_pong(base, serial);
}

static const struct xdg_wm_base_listener xdg_wm_base_listener = {
    .ping = xdg_wm_base_ping,
};

/* ---- XDG Surface ---- */

static void xdg_surface_handle_configure(void *data, struct xdg_surface *surface, u32 serial) {
    Platform *p = data;
    xdg_surface_ack_configure(surface, serial);
    p->configured = true;
}

static const struct xdg_surface_listener xdg_surface_listener = {
    .configure = xdg_surface_handle_configure,
};

/* ---- XDG Toplevel ---- */

static void xdg_toplevel_handle_configure(void *data, struct xdg_toplevel *tl,
                                          i32 w, i32 h, struct wl_array *states) {
    (void)tl;
    (void)states;
    Platform *p = data;
    if (w > 0 && h > 0) {
        p->width = (u32)w;
        p->height = (u32)h;
        wayland_update_surface_scale(p);
    }
}

static void xdg_toplevel_handle_close(void *data, struct xdg_toplevel *tl) {
    (void)tl;
    Platform *p = data;
    p->should_close = true;
}

static const struct xdg_toplevel_listener xdg_toplevel_listener = {
    .configure = xdg_toplevel_handle_configure,
    .close = xdg_toplevel_handle_close,
};

/* ---- Keyboard listener ---- */

static void keyboard_keymap(void *data, struct wl_keyboard *kb, u32 format,
                            i32 fd, u32 size) {
    (void)kb;
    Platform *p = data;
    if (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        return;
    }
    char *map_str = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map_str == MAP_FAILED) {
        close(fd);
        return;
    }

    if (p->xkb_keymap) xkb_keymap_unref(p->xkb_keymap);
    if (p->xkb_state)  xkb_state_unref(p->xkb_state);

    p->xkb_keymap = xkb_keymap_new_from_string(p->xkb_ctx, map_str,
        XKB_KEYMAP_FORMAT_TEXT_V1, XKB_KEYMAP_COMPILE_NO_FLAGS);
    if (p->xkb_keymap)
        p->xkb_state = xkb_state_new(p->xkb_keymap);

    munmap(map_str, size);
    close(fd);
}

static void keyboard_enter(void *data, struct wl_keyboard *kb, u32 serial,
                           struct wl_surface *surface, struct wl_array *keys) {
    Platform *p = data;
    (void)kb;
    (void)surface;
    (void)keys;
    p->keyboard_serial = serial;
    if (p->clipboard_publish_pending) wayland_clipboard_publish(p);
}

static void keyboard_leave(void *data, struct wl_keyboard *kb, u32 serial,
                           struct wl_surface *surface) {
    (void)kb; (void)serial; (void)surface;
    /* R263: keyboard focus lost — release all keys so a key released while
     * unfocused (Wayland delivers no key event to an unfocused surface) can't
     * stay stuck down and keep driving movement after refocus. */
    Platform *p = data;
    if (p) {
        p->keyboard_serial = 0;
        input_release_all(&p->input);
    }
}

static void keyboard_key(void *data, struct wl_keyboard *kb, u32 serial,
                         u32 time, u32 key, u32 state) {
    (void)kb;
    (void)time;
    Platform *p = data;
    if (state == WL_KEYBOARD_KEY_STATE_PRESSED) {
        p->keyboard_serial = serial;
        if (p->clipboard_publish_pending) wayland_clipboard_publish(p);
    }
    if (!p->xkb_state) return;

    /* Wayland key codes are evdev codes; XKB expects evdev + 8 */
    u32 keycode = key + 8;
    xkb_keysym_t sym = xkb_state_key_get_one_sym(p->xkb_state, keycode);
    i32 engine_key = wayland_keysym_to_engine(sym);
    if (engine_key >= 0) {
        input_set_key(&p->input, engine_key, state == WL_KEYBOARD_KEY_STATE_PRESSED);
    }
}

static void keyboard_modifiers(void *data, struct wl_keyboard *kb, u32 serial,
                               u32 mods_depressed, u32 mods_latched,
                               u32 mods_locked, u32 group) {
    (void)kb; (void)serial;
    Platform *p = data;
    if (p->xkb_state)
        xkb_state_update_mask(p->xkb_state, mods_depressed, mods_latched,
                              mods_locked, 0, 0, group);
}

static void keyboard_repeat_info(void *data, struct wl_keyboard *kb,
                                 i32 rate, i32 delay) {
    (void)data; (void)kb; (void)rate; (void)delay;
}

static const struct wl_keyboard_listener keyboard_listener = {
    .keymap      = keyboard_keymap,
    .enter       = keyboard_enter,
    .leave       = keyboard_leave,
    .key         = keyboard_key,
    .modifiers   = keyboard_modifiers,
    .repeat_info = keyboard_repeat_info,
};

/* ---- Pointer listener ---- */

static void pointer_enter(void *data, struct wl_pointer *ptr, u32 serial,
                          struct wl_surface *surface, wl_fixed_t sx, wl_fixed_t sy) {
    (void)surface;
    Platform *p = data;
    p->pointer_x = wl_fixed_to_double(sx);
    p->pointer_y = wl_fixed_to_double(sy);
    p->pointer_enter_serial = serial;
    (void)ptr;
    /* Re-apply hidden cursor each time the pointer re-enters the surface. */
    wayland_update_cursor_visibility(p);
}

static void pointer_leave(void *data, struct wl_pointer *ptr, u32 serial,
                          struct wl_surface *surface) {
    (void)ptr; (void)serial; (void)surface;
    /* R354: compositor may omit ButtonRelease when the pointer leaves the
     * surface; release mouse keys so drag/click cannot stick (keyboard_leave
     * already calls input_release_all for focus loss). */
    Platform *p = data;
    if (!p) return;
    input_set_key(&p->input, INPUT_MOUSE_LEFT, false);
    input_set_key(&p->input, INPUT_MOUSE_MIDDLE, false);
    input_set_key(&p->input, INPUT_MOUSE_RIGHT, false);
    input_set_key(&p->input, INPUT_MOUSE_4, false);
    input_set_key(&p->input, INPUT_MOUSE_5, false);
}

static void pointer_motion(void *data, struct wl_pointer *ptr, u32 time,
                           wl_fixed_t sx, wl_fixed_t sy) {
    (void)ptr; (void)time;
    Platform *p = data;
    f64 nx = wl_fixed_to_double(sx);
    f64 ny = wl_fixed_to_double(sy);

    /* R346: when zwp_relative_pointer is active (relative/capture), deltas
     * come from relative_pointer_motion. Also accumulating surface Δ here
     * double-counts — especially if pointer-constraints lock is missing and
     * the cursor still moves on the surface. */
    if (!p->rel_pointer) {
        /* R432: seed on the first sample — pointer_x/pointer_y start zeroed,
         * so the first motion event otherwise emitted a delta spike up to the
         * window size (same fix as input_set_mouse's has_mouse_pos). */
        if (p->input.has_mouse_pos) {
            p->input.mouse_dx += (f32)(nx - p->pointer_x);
            p->input.mouse_dy += (f32)(ny - p->pointer_y);
        } else {
            p->input.has_mouse_pos = true;
        }
    }
    p->pointer_x = nx;
    p->pointer_y = ny;
    p->input.mouse_x = (f32)nx;
    p->input.mouse_y = (f32)ny;
}

static void pointer_button(void *data, struct wl_pointer *ptr, u32 serial,
                           u32 time, u32 button, u32 state) {
    (void)ptr; (void)time;
    Platform *p = data;
    i32 key = -1;
    if (button == BTN_LEFT)        key = INPUT_MOUSE_LEFT;
    else if (button == BTN_RIGHT)  key = INPUT_MOUSE_RIGHT;
    else if (button == BTN_MIDDLE) key = INPUT_MOUSE_MIDDLE;
    else if (button == BTN_SIDE)   key = INPUT_MOUSE_4;
    else if (button == BTN_EXTRA)  key = INPUT_MOUSE_5;
    if (key >= 0) {
        input_set_key(&p->input, key, state == WL_POINTER_BUTTON_STATE_PRESSED);
        if (state == WL_POINTER_BUTTON_STATE_PRESSED)
            p->pointer_button_serial = serial;
        else if (key == INPUT_MOUSE_LEFT)
            p->pointer_button_serial = 0;
    }
}

static void pointer_axis(void *data, struct wl_pointer *ptr, u32 time,
                         u32 axis, wl_fixed_t value) {
    (void)ptr; (void)time;
    Platform *p = data;
    f32 v = (f32)wl_fixed_to_double(value);
    if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL)
        input_set_scroll(&p->input, 0.0f, -v / 10.0f);
    else if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL)
        input_set_scroll(&p->input, v / 10.0f, 0.0f);
}

static void pointer_frame(void *data, struct wl_pointer *ptr) {
    (void)data; (void)ptr;
}

static void pointer_axis_source(void *data, struct wl_pointer *ptr, u32 source) {
    (void)data; (void)ptr; (void)source;
}

static void pointer_axis_stop(void *data, struct wl_pointer *ptr, u32 time, u32 axis) {
    (void)data; (void)ptr; (void)time; (void)axis;
}

static void pointer_axis_discrete(void *data, struct wl_pointer *ptr, u32 axis, i32 discrete) {
    (void)data; (void)ptr; (void)axis; (void)discrete;
}

static const struct wl_pointer_listener pointer_listener = {
    .enter         = pointer_enter,
    .leave         = pointer_leave,
    .motion        = pointer_motion,
    .button        = pointer_button,
    .axis          = pointer_axis,
    .frame         = pointer_frame,
    .axis_source   = pointer_axis_source,
    .axis_stop     = pointer_axis_stop,
    .axis_discrete = pointer_axis_discrete,
};

/* ---- Relative pointer listener (zwp_relative_pointer_v1) ---- */

static void relative_pointer_motion(void *data, struct zwp_relative_pointer_v1 *rp,
                                    u32 utime_hi, u32 utime_lo,
                                    wl_fixed_t dx, wl_fixed_t dy,
                                    wl_fixed_t dx_unaccel, wl_fixed_t dy_unaccel) {
    (void)rp; (void)utime_hi; (void)utime_lo; (void)dx; (void)dy;
    Platform *p = data;
    /* Prefer unaccelerated deltas for camera-style relative input. */
    p->input.mouse_dx += (f32)wl_fixed_to_double(dx_unaccel);
    p->input.mouse_dy += (f32)wl_fixed_to_double(dy_unaccel);
}

static const struct zwp_relative_pointer_v1_listener relative_pointer_listener = {
    .relative_motion = relative_pointer_motion,
};

/* ---- Seat listener ---- */

static void seat_capabilities(void *data, struct wl_seat *seat, u32 caps) {
    Platform *p = data;

    if ((caps & WL_SEAT_CAPABILITY_KEYBOARD) && !p->keyboard) {
        p->keyboard = wl_seat_get_keyboard(seat);
        wl_keyboard_add_listener(p->keyboard, &keyboard_listener, p);
    } else if (!(caps & WL_SEAT_CAPABILITY_KEYBOARD) && p->keyboard) {
        wl_keyboard_destroy(p->keyboard);
        p->keyboard = NULL;
    }
    wayland_create_data_device(p);

    if ((caps & WL_SEAT_CAPABILITY_POINTER) && !p->pointer) {
        p->pointer = wl_seat_get_pointer(seat);
        wl_pointer_add_listener(p->pointer, &pointer_listener, p);
        wayland_create_cursor_device(p);
        if (p->mouse_captured || p->mouse_relative) wayland_apply_relative(p);
    } else if (!(caps & WL_SEAT_CAPABILITY_POINTER) && p->pointer) {
        wayland_clear_relative(p);
#ifdef ENGINE_WAYLAND_CURSOR_SHAPE
        if (p->cursor_shape_device != NULL) {
            wp_cursor_shape_device_v1_destroy(p->cursor_shape_device);
            p->cursor_shape_device = NULL;
        }
#endif
        wl_pointer_destroy(p->pointer);
        p->pointer = NULL;
        p->pointer_enter_serial = 0;
    }
}

static void seat_name(void *data, struct wl_seat *seat, const char *name) {
    (void)data; (void)seat; (void)name;
}

static const struct wl_seat_listener seat_listener = {
    .capabilities = seat_capabilities,
    .name         = seat_name,
};

/* ---- wl_output listener (R443: per-output via WaylandOutputCtx) ---- */

static WaylandOutputInfo *wayland_output_from_ctx(WaylandOutputCtx *ctx,
                                                   u32 *slot_out) {
    i32 slot;
    if (ctx == NULL || ctx->p == NULL) return NULL;
    slot = wl_out_find(&ctx->p->output_list, ctx->global_name);
    if (slot < 0) return NULL;
    if (slot_out != NULL) *slot_out = (u32)slot;
    return &ctx->p->output_list.items[slot];
}

static bool wayland_surface_has_output(const Platform *p, u32 global_name) {
    for (u32 i = 0; i < p->surface_output_count; i++) {
        if (p->surface_outputs[i] == global_name) return true;
    }
    return false;
}

static void wayland_surface_add_output(Platform *p, u32 global_name) {
    if (global_name == 0 || wayland_surface_has_output(p, global_name)) return;
    if (p->surface_output_count < WAYLAND_OUTPUT_MAX)
        p->surface_outputs[p->surface_output_count++] = global_name;
}

static void wayland_surface_remove_output(Platform *p, u32 global_name) {
    for (u32 i = 0; i < p->surface_output_count; i++) {
        if (p->surface_outputs[i] == global_name) {
            p->surface_outputs[i] =
                p->surface_outputs[--p->surface_output_count];
            return;
        }
    }
}

static void wayland_update_surface_scale(Platform *p) {
    i32 integer_scale;
    WaylandSurfaceScale render_scale;
    bool scale_changed;
    if (p == NULL) return;
    integer_scale = p->surface_output_count > 0
                        ? wl_out_surface_scale(&p->output_list,
                                               p->surface_outputs,
                                               p->surface_output_count)
                        : p->primary_scale;
    if (integer_scale < 1) integer_scale = 1;
#ifdef ENGINE_WAYLAND_FRACTIONAL_SCALE
    render_scale = wl_out_surface_render_scale(
        integer_scale, p->preferred_scale_120,
        p->fractional_scale != NULL && p->viewport != NULL);
#else
    render_scale = wl_out_surface_render_scale(integer_scale, 0, false);
#endif
    scale_changed = integer_scale != p->scale ||
                    render_scale.content_scale_120 != p->content_scale_120;
    p->scale = integer_scale;
    p->content_scale_120 = render_scale.content_scale_120;
    p->dpi = 96.0f * (f32)p->content_scale_120 / 120.0f;
    if (p->surface != NULL)
        wl_surface_set_buffer_scale(p->surface, render_scale.buffer_scale);
#ifdef ENGINE_WAYLAND_FRACTIONAL_SCALE
    if (p->viewport != NULL && p->width > 0 && p->height > 0)
        wp_viewport_set_destination(p->viewport, (i32)p->width, (i32)p->height);
#endif
    if (p->egl_window != NULL)
        wl_egl_window_resize(p->egl_window,
                             (i32)wl_out_drawable_dimension(
                                 p->width, p->content_scale_120),
                             (i32)wl_out_drawable_dimension(
                                 p->height, p->content_scale_120),
                             0, 0);
    if (!scale_changed) return;
    if (p->cursor_theme != NULL) {
        wl_cursor_theme_destroy(p->cursor_theme);
        p->cursor_theme = NULL;
    }
    wayland_update_cursor_visibility(p);
}

#ifdef ENGINE_WAYLAND_FRACTIONAL_SCALE
static void wayland_disable_fractional_scale(Platform *p) {
    if (p == NULL) return;
    if (p->viewport != NULL) {
        wp_viewport_destroy(p->viewport);
        p->viewport = NULL;
    }
    if (p->fractional_scale != NULL) {
        wp_fractional_scale_v1_destroy(p->fractional_scale);
        p->fractional_scale = NULL;
    }
    p->preferred_scale_120 = 0;
}

static void fractional_scale_preferred(void *data,
                                       struct wp_fractional_scale_v1 *scale,
                                       u32 preferred_scale_120) {
    Platform *p = data;
    (void)scale;
    if (p == NULL || preferred_scale_120 == 0) return;
    p->preferred_scale_120 = preferred_scale_120;
    wayland_update_surface_scale(p);
}

static const struct wp_fractional_scale_v1_listener fractional_scale_listener = {
    .preferred_scale = fractional_scale_preferred,
};
#endif

static void wayland_try_enable_fractional_scale(Platform *p) {
#ifdef ENGINE_WAYLAND_FRACTIONAL_SCALE
    if (p == NULL || p->surface == NULL || p->fractional_scale != NULL ||
        p->fractional_scale_manager == NULL || p->viewporter == NULL) {
        return;
    }
    p->viewport = wp_viewporter_get_viewport(p->viewporter, p->surface);
    p->fractional_scale = wp_fractional_scale_manager_v1_get_fractional_scale(
        p->fractional_scale_manager, p->surface);
    if (p->viewport == NULL || p->fractional_scale == NULL) {
        wayland_disable_fractional_scale(p);
        LOG_WARN("Wayland: fractional-scale setup failed; using integer scale");
        return;
    }
    wp_fractional_scale_v1_add_listener(p->fractional_scale,
                                        &fractional_scale_listener, p);
    wayland_update_surface_scale(p);
#else
    (void)p;
#endif
}

static u32 wayland_output_global_name(const Platform *p,
                                      const struct wl_output *output) {
    for (u32 i = 0; i < p->output_list.count; i++) {
        if (p->outputs[i] == output) return p->output_list.items[i].global_name;
    }
    return 0;
}

static void surface_enter(void *data, struct wl_surface *surface,
                          struct wl_output *output) {
    Platform *p = data;
    (void)surface;
    wayland_surface_add_output(p, wayland_output_global_name(p, output));
    wayland_update_surface_scale(p);
}

static void surface_leave(void *data, struct wl_surface *surface,
                          struct wl_output *output) {
    Platform *p = data;
    (void)surface;
    wayland_surface_remove_output(p, wayland_output_global_name(p, output));
    wayland_update_surface_scale(p);
}

static const struct wl_surface_listener surface_listener = {
    .enter = surface_enter,
    .leave = surface_leave,
};

static void output_geometry(void *data, struct wl_output *output,
    i32 x, i32 y, i32 phys_w, i32 phys_h, i32 subpixel,
    const char *make, const char *model, i32 transform) {
    (void)output; (void)phys_w; (void)phys_h; (void)subpixel; (void)make; (void)transform;
    WaylandOutputCtx *ctx = data;
    WaylandOutputInfo *o = wayland_output_from_ctx(ctx, NULL);
    if (o == NULL) return;
    o->x = x;
    o->y = y;
    if (o->name[0] == '\0') {
        strncpy(o->name, model ? model : "unknown", 63);
        o->name[63] = '\0';
    }
}

static void output_mode(void *data, struct wl_output *output,
    u32 flags, i32 w, i32 h, i32 refresh) {
    (void)output;
    WaylandOutputCtx *ctx = data;
    WaylandOutputInfo *o = wayland_output_from_ctx(ctx, NULL);
    if (o != NULL)
        wl_out_accumulate_mode(o, (flags & WL_OUTPUT_MODE_CURRENT) != 0,
                               w, h, refresh);
}

static void output_scale(void *data, struct wl_output *output, i32 factor) {
    (void)output;
    WaylandOutputCtx *ctx = data;
    WaylandOutputInfo *o = wayland_output_from_ctx(ctx, NULL);
    if (o == NULL) return;
    o->scale = factor > 0 ? factor : 1;
    if (wayland_surface_has_output(ctx->p, ctx->global_name))
        wayland_update_surface_scale(ctx->p);
}

static void output_done(void *data, struct wl_output *output) {
    (void)output;
    WaylandOutputCtx *ctx = data;
    Platform *p = ctx->p;
    u32 slot = 0;
    WaylandOutputInfo *o = wayland_output_from_ctx(ctx, &slot);
    if (o == NULL) return;
    o->done = true;
    /* Slot 0 is the primary output; keep the global dpi/scale mirroring it
     * (single-output behavior unchanged from the pre-R443 implementation). */
    if (slot == 0) {
        p->primary_scale = o->scale;
    }
    wayland_update_surface_scale(p);
}

static const struct wl_output_listener output_listener = {
    .geometry = output_geometry,
    .mode     = output_mode,
    .done     = output_done,
    .scale    = output_scale,
};

/* ---- zxdg_output_v1 listener (R443: logical position + readable name) ---- */

static void xdg_output_logical_position(void *data, struct zxdg_output_v1 *xo,
                                        i32 x, i32 y) {
    (void)xo;
    WaylandOutputCtx *ctx = data;
    WaylandOutputInfo *o = wayland_output_from_ctx(ctx, NULL);
    if (o == NULL) return;
    /* More authoritative than wl_output.geometry (often 0,0 on wlroots). */
    o->x = x;
    o->y = y;
}

static void xdg_output_logical_size(void *data, struct zxdg_output_v1 *xo,
                                    i32 w, i32 h) {
    (void)data; (void)xo; (void)w; (void)h;
    /* MonitorInfo.width/height stay pixel-resolution (X11 parity); the
     * logical size is scale-derived and not part of the public shape. */
}

static void xdg_output_done(void *data, struct zxdg_output_v1 *xo) {
    (void)data; (void)xo;
}

static void xdg_output_name(void *data, struct zxdg_output_v1 *xo,
                            const char *name) {
    (void)xo;
    WaylandOutputCtx *ctx = data;
    WaylandOutputInfo *o = wayland_output_from_ctx(ctx, NULL);
    if (o == NULL) return;
    strncpy(o->name, name ? name : "unknown", 63);
    o->name[63] = '\0';
}

static void xdg_output_description(void *data, struct zxdg_output_v1 *xo,
                                   const char *description) {
    (void)data; (void)xo; (void)description;
}

static const struct zxdg_output_v1_listener xdg_output_listener = {
    .logical_position = xdg_output_logical_position,
    .logical_size     = xdg_output_logical_size,
    .done             = xdg_output_done,
    .name             = xdg_output_name,
    .description      = xdg_output_description,
};

/* R443: bind zxdg_output_v1 for a slot when the manager is available. Called
 * from both registry branches because global advertisement order between
 * wl_output and zxdg_output_manager_v1 is not guaranteed. */
static void wayland_bind_xdg_output(Platform *p, u32 slot) {
    if (!p->xdg_output_mgr || !p->outputs[slot] || p->xdg_outputs[slot]) return;
    p->xdg_outputs[slot] = zxdg_output_manager_v1_get_xdg_output(
        p->xdg_output_mgr, p->outputs[slot]);
    if (p->xdg_outputs[slot])
        zxdg_output_v1_add_listener(p->xdg_outputs[slot],
            &xdg_output_listener, p->output_ctx[slot]);
}

/* ---- Registry listener ---- */

static void registry_global(void *data, struct wl_registry *reg, u32 name,
                            const char *interface, u32 version) {
    (void)version;
    Platform *p = data;
    if (strcmp(interface, wl_compositor_interface.name) == 0)
        p->compositor = wl_registry_bind(reg, name, &wl_compositor_interface, 4);
    else if (strcmp(interface, wl_shm_interface.name) == 0)
        p->shm = wl_registry_bind(reg, name, &wl_shm_interface, 1);
    else if (strcmp(interface, xdg_wm_base_interface.name) == 0)
        p->xdg_wm_base = wl_registry_bind(reg, name, &xdg_wm_base_interface, 1);
    else if (strcmp(interface, wl_seat_interface.name) == 0) {
        if (p->seat == NULL) {
            p->seat = wl_registry_bind(reg, name, &wl_seat_interface, 5);
            p->seat_global_name = name;
            wl_seat_add_listener(p->seat, &seat_listener, p);
            wayland_create_data_device(p);
            wayland_create_text_input(p);
        }
    }
    else if (strcmp(interface, wl_data_device_manager_interface.name) == 0) {
        if (p->data_device_manager == NULL) {
            p->data_device_manager = wl_registry_bind(
                reg, name, &wl_data_device_manager_interface,
                version < 3 ? version : 3);
            wl_out_optional_global_set(&p->optional_globals,
                                       WAYLAND_OPTIONAL_DATA_DEVICE_MANAGER, name);
            wayland_create_data_device(p);
        }
    }
    else if (strcmp(interface, zwp_text_input_manager_v3_interface.name) == 0) {
        if (p->text_input_manager == NULL) {
            p->text_input_manager = wl_registry_bind(
                reg, name, &zwp_text_input_manager_v3_interface,
                version < 2 ? version : 2);
            wl_out_optional_global_set(&p->optional_globals,
                                       WAYLAND_OPTIONAL_TEXT_INPUT_MANAGER, name);
            wayland_create_text_input(p);
        }
    }
    else if (strcmp(interface, wl_output_interface.name) == 0) {
        /* R443: bind every advertised output (was: single p->output). */
        i32 slot = wl_out_add(&p->output_list, name);
        if (slot >= 0 && !p->outputs[slot]) {
            WaylandOutputCtx *ctx = calloc(1, sizeof(*ctx));
            if (ctx == NULL) {
                (void)wl_out_remove(&p->output_list, name);
                LOG_ERROR("Wayland: failed to allocate wl_output context");
                return;
            }
            ctx->p = p;
            ctx->global_name = name;
            p->output_ctx[slot] = ctx;
            /* v3: geometry/mode/done/scale (name/description need v4, which
             * xdg-output covers instead). */
            p->outputs[slot] = wl_registry_bind(reg, name, &wl_output_interface, 3);
            wl_output_add_listener(p->outputs[slot], &output_listener,
                ctx);
            wayland_bind_xdg_output(p, (u32)slot);
        }
    }
    else if (strcmp(interface, zxdg_output_manager_v1_interface.name) == 0) {
        /* R443: optional — logical position/names; degrade to wl_output-only
         * data when the compositor lacks it. */
        if (p->xdg_output_mgr == NULL) {
            p->xdg_output_mgr = wl_registry_bind(reg, name,
                &zxdg_output_manager_v1_interface, 3);
            wl_out_optional_global_set(&p->optional_globals,
                                       WAYLAND_OPTIONAL_XDG_OUTPUT_MANAGER, name);
            for (u32 i = 0; i < p->output_list.count; i++)
                wayland_bind_xdg_output(p, i);
        }
    }
#ifdef ENGINE_WAYLAND_FRACTIONAL_SCALE
    else if (strcmp(interface, wp_fractional_scale_manager_v1_interface.name) == 0) {
        if (p->fractional_scale_manager == NULL) {
            p->fractional_scale_manager = wl_registry_bind(
                reg, name, &wp_fractional_scale_manager_v1_interface, 1);
            wl_out_optional_global_set(&p->optional_globals,
                                       WAYLAND_OPTIONAL_FRACTIONAL_SCALE_MANAGER,
                                       name);
            wayland_try_enable_fractional_scale(p);
        }
    }
    else if (strcmp(interface, wp_viewporter_interface.name) == 0) {
        if (p->viewporter == NULL) {
            p->viewporter = wl_registry_bind(reg, name,
                                              &wp_viewporter_interface, 1);
            wl_out_optional_global_set(&p->optional_globals,
                                       WAYLAND_OPTIONAL_VIEWPORTER, name);
            wayland_try_enable_fractional_scale(p);
        }
    }
#endif
    else if (strcmp(interface, zwp_relative_pointer_manager_v1_interface.name) == 0) {
        if (p->rel_pointer_mgr == NULL) {
            p->rel_pointer_mgr = wl_registry_bind(reg, name,
                &zwp_relative_pointer_manager_v1_interface, 1);
            wl_out_optional_global_set(&p->optional_globals,
                                       WAYLAND_OPTIONAL_RELATIVE_POINTER_MANAGER,
                                       name);
            if (p->mouse_captured || p->mouse_relative) wayland_apply_relative(p);
        }
    }
    else if (strcmp(interface, zwp_pointer_constraints_v1_interface.name) == 0) {
        if (p->pointer_constraints == NULL) {
            p->pointer_constraints = wl_registry_bind(reg, name,
                &zwp_pointer_constraints_v1_interface, 1);
            wl_out_optional_global_set(&p->optional_globals,
                                       WAYLAND_OPTIONAL_POINTER_CONSTRAINTS, name);
            if (p->mouse_captured || p->mouse_relative) wayland_apply_relative(p);
        }
    }
#ifdef ENGINE_WAYLAND_CURSOR_SHAPE
    else if (strcmp(interface, wp_cursor_shape_manager_v1_interface.name) == 0) {
        if (p->cursor_shape_manager == NULL) {
            p->cursor_shape_manager = wl_registry_bind(
                reg, name, &wp_cursor_shape_manager_v1_interface,
                version < 2 ? version : 2);
            wl_out_optional_global_set(&p->optional_globals,
                                       WAYLAND_OPTIONAL_CURSOR_SHAPE_MANAGER,
                                       name);
            wayland_create_cursor_device(p);
            wayland_update_cursor_visibility(p);
        }
    }
#endif
}

static void registry_global_remove(void *data, struct wl_registry *reg, u32 name) {
    (void)reg;
    Platform *p = data;
    if (p->seat_global_name == name) {
        wayland_clear_relative(p);
#ifdef ENGINE_WAYLAND_CURSOR_SHAPE
        if (p->cursor_shape_device != NULL) {
            wp_cursor_shape_device_v1_destroy(p->cursor_shape_device);
            p->cursor_shape_device = NULL;
        }
#endif
        wayland_clear_text_input(p);
        wayland_destroy_data_device(p);
        if (p->keyboard != NULL) {
            wl_keyboard_destroy(p->keyboard);
            p->keyboard = NULL;
        }
        if (p->pointer != NULL) {
            wl_pointer_destroy(p->pointer);
            p->pointer = NULL;
        }
        if (p->seat != NULL) wl_seat_destroy(p->seat);
        p->seat = NULL;
        p->seat_global_name = 0;
        p->keyboard_serial = 0;
        p->pointer_enter_serial = 0;
        p->pointer_button_serial = 0;
        input_release_all(&p->input);
        LOG_WARN("Wayland: seat removed; input, IME, and clipboard unavailable");
        return;
    }
    WaylandOptionalGlobal optional =
        wl_out_optional_global_take(&p->optional_globals, name);
    switch (optional) {
    case WAYLAND_OPTIONAL_DATA_DEVICE_MANAGER:
        wayland_destroy_data_device(p);
        if (p->data_device_manager != NULL)
            wl_data_device_manager_destroy(p->data_device_manager);
        p->data_device_manager = NULL;
        LOG_WARN("Wayland: data-device manager removed; clipboard unavailable");
        return;
    case WAYLAND_OPTIONAL_TEXT_INPUT_MANAGER:
        wayland_clear_text_input(p);
        if (p->text_input_manager != NULL)
            zwp_text_input_manager_v3_destroy(p->text_input_manager);
        p->text_input_manager = NULL;
        LOG_WARN("Wayland: text-input manager removed; IME unavailable");
        return;
    case WAYLAND_OPTIONAL_XDG_OUTPUT_MANAGER:
        for (u32 i = 0; i < p->output_list.count; i++) {
            if (p->xdg_outputs[i] != NULL) {
                zxdg_output_v1_destroy(p->xdg_outputs[i]);
                p->xdg_outputs[i] = NULL;
            }
        }
        if (p->xdg_output_mgr != NULL)
            zxdg_output_manager_v1_destroy(p->xdg_output_mgr);
        p->xdg_output_mgr = NULL;
        return;
    case WAYLAND_OPTIONAL_RELATIVE_POINTER_MANAGER:
        if (p->rel_pointer != NULL) {
            zwp_relative_pointer_v1_destroy(p->rel_pointer);
            p->rel_pointer = NULL;
        }
        if (p->rel_pointer_mgr != NULL)
            zwp_relative_pointer_manager_v1_destroy(p->rel_pointer_mgr);
        p->rel_pointer_mgr = NULL;
        LOG_WARN("Wayland: relative-pointer manager removed; relative mouse degraded");
        return;
    case WAYLAND_OPTIONAL_POINTER_CONSTRAINTS:
        if (p->locked_pointer != NULL) {
            zwp_locked_pointer_v1_destroy(p->locked_pointer);
            p->locked_pointer = NULL;
        }
        if (p->pointer_constraints != NULL)
            zwp_pointer_constraints_v1_destroy(p->pointer_constraints);
        p->pointer_constraints = NULL;
        LOG_WARN("Wayland: pointer-constraints removed; relative mouse degraded");
        return;
    case WAYLAND_OPTIONAL_CURSOR_SHAPE_MANAGER:
#ifdef ENGINE_WAYLAND_CURSOR_SHAPE
        if (p->cursor_shape_device != NULL) {
            wp_cursor_shape_device_v1_destroy(p->cursor_shape_device);
            p->cursor_shape_device = NULL;
        }
        if (p->cursor_shape_manager != NULL)
            wp_cursor_shape_manager_v1_destroy(p->cursor_shape_manager);
        p->cursor_shape_manager = NULL;
        wayland_update_cursor_visibility(p);
#endif
        return;
    case WAYLAND_OPTIONAL_FRACTIONAL_SCALE_MANAGER:
    case WAYLAND_OPTIONAL_VIEWPORTER:
#ifdef ENGINE_WAYLAND_FRACTIONAL_SCALE
        wayland_disable_fractional_scale(p);
        if (optional == WAYLAND_OPTIONAL_FRACTIONAL_SCALE_MANAGER) {
            if (p->fractional_scale_manager != NULL)
                wp_fractional_scale_manager_v1_destroy(p->fractional_scale_manager);
            p->fractional_scale_manager = NULL;
        } else {
            if (p->viewporter != NULL) wp_viewporter_destroy(p->viewporter);
            p->viewporter = NULL;
        }
        LOG_WARN("Wayland: fractional-scale global removed; using integer scale");
        wayland_update_surface_scale(p);
        return;
#else
        return;
#endif
    case WAYLAND_OPTIONAL_NONE:
    case WAYLAND_OPTIONAL_COUNT:
        break;
    }
    /* R444: output hot-unplug. Tombstones would exhaust the fixed 8-slot
     * budget under repeated plug/unplug and fight wl_out_add's append-dedup
     * semantics, so removal compacts all parallel arrays instead. */
    i32 slot = wl_out_find(&p->output_list, name);
    if (slot < 0) return; /* not an output we bound (seat, compositor...) */
    u32 i = (u32)slot;
    wayland_surface_remove_output(p, name);
    /* zxdg_output_v1 wraps the wl_output, so it must go first. */
    if (p->xdg_outputs[i]) zxdg_output_v1_destroy(p->xdg_outputs[i]);
    if (p->outputs[i])     wl_output_destroy(p->outputs[i]);
    free(p->output_ctx[i]);
    wl_out_remove(&p->output_list, name);
    u32 tail = p->output_list.count - i;
    if (tail > 0) {
        memmove(&p->outputs[i], &p->outputs[i + 1], tail * sizeof(p->outputs[0]));
        memmove(&p->xdg_outputs[i], &p->xdg_outputs[i + 1], tail * sizeof(p->xdg_outputs[0]));
        memmove(&p->output_ctx[i], &p->output_ctx[i + 1],
                tail * sizeof(p->output_ctx[0]));
    }
    p->outputs[p->output_list.count] = NULL;
    p->xdg_outputs[p->output_list.count] = NULL;
    p->output_ctx[p->output_list.count] = NULL;
    p->primary_scale = p->output_list.count > 0
                           ? p->output_list.items[0].scale
                           : 1;
    wayland_update_surface_scale(p);
}

static const struct wl_registry_listener registry_listener = {
    .global        = registry_global,
    .global_remove = registry_global_remove,
};

/* ---- Platform API ---- */

/* R427: bail-out cleanup for platform_create — destroys whatever was created
 * so far (every member NULL-checked), mirroring platform_destroy. The old
 * failure paths only disconnected the display, leaking the registry and the
 * xkb context (and any bound globals). */
static void wayland_create_fail(Platform *p) {
#ifdef ENGINE_WAYLAND_CURSOR_SHAPE
    if (p->cursor_shape_device) wp_cursor_shape_device_v1_destroy(p->cursor_shape_device);
#endif
    if (p->cursor_surface) wl_surface_destroy(p->cursor_surface);
    if (p->cursor_theme)   wl_cursor_theme_destroy(p->cursor_theme);
    wayland_clipboard_finish_read(p, false);
    wayland_clipboard_clear_writes(p);
    wayland_clipboard_offer_destroy(&p->clipboard_offer);
    wayland_clipboard_offer_destroy(&p->drag_offer);
    wayland_clipboard_destroy_sources(p);
    if (p->data_device) wl_data_device_release(p->data_device);
    if (p->data_device_manager) wl_data_device_manager_destroy(p->data_device_manager);
    wayland_clipboard_free_text(p);
#ifdef ENGINE_WAYLAND_FRACTIONAL_SCALE
    if (p->fractional_scale) wp_fractional_scale_v1_destroy(p->fractional_scale);
    if (p->viewport) wp_viewport_destroy(p->viewport);
#endif
    if (p->toplevel)     xdg_toplevel_destroy(p->toplevel);
    if (p->xdg_surface)  xdg_surface_destroy(p->xdg_surface);
    if (p->surface)      wl_surface_destroy(p->surface);
    if (p->keyboard)     wl_keyboard_destroy(p->keyboard);
    if (p->pointer)      wl_pointer_destroy(p->pointer);
    if (p->xdg_wm_base)  xdg_wm_base_destroy(p->xdg_wm_base);
    if (p->seat)         wl_seat_destroy(p->seat);
    /* R443: multi-output */
    for (u32 i = 0; i < WAYLAND_OUTPUT_MAX; i++) {
        if (p->xdg_outputs[i]) zxdg_output_v1_destroy(p->xdg_outputs[i]);
        if (p->outputs[i])     wl_output_destroy(p->outputs[i]);
        free(p->output_ctx[i]);
    }
    if (p->xdg_output_mgr) zxdg_output_manager_v1_destroy(p->xdg_output_mgr);
#ifdef ENGINE_WAYLAND_FRACTIONAL_SCALE
    if (p->fractional_scale_manager)
        wp_fractional_scale_manager_v1_destroy(p->fractional_scale_manager);
    if (p->viewporter) wp_viewporter_destroy(p->viewporter);
#endif
    if (p->compositor)   wl_compositor_destroy(p->compositor);
    if (p->shm)          wl_shm_destroy(p->shm);
#ifdef ENGINE_WAYLAND_CURSOR_SHAPE
    if (p->cursor_shape_manager) wp_cursor_shape_manager_v1_destroy(p->cursor_shape_manager);
#endif
    if (p->registry)     wl_registry_destroy(p->registry);
    if (p->xkb_ctx)      xkb_context_unref(p->xkb_ctx);
    if (p->display)      wl_display_disconnect(p->display);
    free(p);
}

Platform *platform_create(const PlatformConfig *cfg) {
    Platform *p = calloc(1, sizeof(Platform));
    if (!p) { LOG_FATAL("Failed to allocate Platform"); return NULL; }

    p->width  = cfg->width;
    p->height = cfg->height;
    p->mouse_visible = true;
    p->cursor = PLATFORM_CURSOR_ARROW;
    p->scale = 1;
    p->primary_scale = 1;
    p->content_scale_120 = 120;
    p->clipboard_read_fd = -1;
    wl_out_optional_globals_init(&p->optional_globals);

    /* Connect to Wayland display */
    p->display = wl_display_connect(NULL);
    if (!p->display) {
        LOG_FATAL("Failed to connect to Wayland display");
        free(p);
        return NULL;
    }

    /* Initialize XKB context */
    p->xkb_ctx = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
    if (!p->xkb_ctx) {
        LOG_ERROR("Failed to create XKB context");
    }

    /* Get registry and bind globals */
    p->registry = wl_display_get_registry(p->display);
    wl_registry_add_listener(p->registry, &registry_listener, p);
    wl_display_roundtrip(p->display);

    if (!p->compositor) {
        LOG_FATAL("Missing wl_compositor interface");
        wayland_create_fail(p);
        return NULL;
    }
    if (!p->xdg_wm_base) {
        LOG_FATAL("Missing xdg_wm_base interface");
        wayland_create_fail(p);
        return NULL;
    }

    xdg_wm_base_add_listener(p->xdg_wm_base, &xdg_wm_base_listener, p);

    /* Create surface. R443: the window is still created on whichever output
     * the compositor picks — per-output window placement is out of scope for
     * this round (enumeration/query only). */
    p->surface = wl_compositor_create_surface(p->compositor);
    if (!p->surface) {
        LOG_FATAL("Failed to create wl_surface");
        wayland_create_fail(p);
        return NULL;
    }
    wl_surface_add_listener(p->surface, &surface_listener, p);
    wl_surface_set_buffer_scale(p->surface, p->scale);
    wayland_try_enable_fractional_scale(p);

    wayland_create_text_input(p);

    /* Create xdg_surface + toplevel */
    p->xdg_surface = xdg_wm_base_get_xdg_surface(p->xdg_wm_base, p->surface);
    xdg_surface_add_listener(p->xdg_surface, &xdg_surface_listener, p);

    p->toplevel = xdg_surface_get_toplevel(p->xdg_surface);
    xdg_toplevel_add_listener(p->toplevel, &xdg_toplevel_listener, p);
    xdg_toplevel_set_title(p->toplevel, cfg->title);
    xdg_toplevel_set_app_id(p->toplevel, "break-engine");

    /* Create EGL window (used by RHI for EGL/Vulkan surface) */
    p->egl_window = wl_egl_window_create(
        p->surface,
        (i32)wl_out_drawable_dimension(cfg->width, p->content_scale_120),
        (i32)wl_out_drawable_dimension(cfg->height, p->content_scale_120));
    /* R427: NULL-check — a failed egl window would crash the RHI init later. */
    if (!p->egl_window) {
        LOG_FATAL("Failed to create wl_egl_window");
        wayland_create_fail(p);
        return NULL;
    }

    /* Commit surface and wait for initial configure */
    wl_surface_commit(p->surface);
    wl_display_roundtrip(p->display);

    /* The registry callback attaches the seat listener before the initial
     * roundtrip can deliver its capability event. */
    if (p->seat) {
        wayland_create_data_device(p);
        wayland_create_text_input(p);
        wl_display_roundtrip(p->display);
    }

    input_init(&p->input);
    gamepad_init();

    /* R443: extra roundtrip so wl_output/xdg-output initial events (bound
     * during the first roundtrip's dispatch) have arrived before queries. */
    wl_display_roundtrip(p->display);

    LOG_INFO("Platform initialized (Wayland): %ux%u \"%s\" (DPI=%.1f scale=%d monitors=%u)",
             cfg->width, cfg->height, cfg->title, p->dpi, p->scale,
             platform_get_monitor_count(p));
    return p;
}

void platform_destroy(Platform *p) {
    if (!p) return;

    gamepad_shutdown();

    wayland_clear_relative(p);
    wayland_clipboard_finish_read(p, false);
    wayland_clipboard_clear_writes(p);
    wayland_clipboard_offer_destroy(&p->clipboard_offer);
    wayland_clipboard_offer_destroy(&p->drag_offer);
    wayland_clipboard_destroy_sources(p);
    if (p->data_device) wl_data_device_release(p->data_device);
    if (p->data_device_manager) wl_data_device_manager_destroy(p->data_device_manager);
    wayland_clipboard_free_text(p);
    free(p->pending_preedit);
    free(p->pending_commit);
    platform_text_queue_destroy(&p->text_queue);
    if (p->rel_pointer_mgr)     zwp_relative_pointer_manager_v1_destroy(p->rel_pointer_mgr);
    if (p->pointer_constraints) zwp_pointer_constraints_v1_destroy(p->pointer_constraints);
    if (p->text_input)          zwp_text_input_v3_destroy(p->text_input);
    if (p->text_input_manager)  zwp_text_input_manager_v3_destroy(p->text_input_manager);
#ifdef ENGINE_WAYLAND_FRACTIONAL_SCALE
    if (p->fractional_scale) wp_fractional_scale_v1_destroy(p->fractional_scale);
    if (p->viewport) wp_viewport_destroy(p->viewport);
#endif
#ifdef ENGINE_WAYLAND_CURSOR_SHAPE
    if (p->cursor_shape_device)  wp_cursor_shape_device_v1_destroy(p->cursor_shape_device);
#endif
    if (p->cursor_surface) wl_surface_destroy(p->cursor_surface);
    if (p->cursor_theme)   wl_cursor_theme_destroy(p->cursor_theme);

    if (p->egl_window)   wl_egl_window_destroy(p->egl_window);
    if (p->keyboard)     wl_keyboard_destroy(p->keyboard);
    if (p->pointer)      wl_pointer_destroy(p->pointer);
    if (p->toplevel)     xdg_toplevel_destroy(p->toplevel);
    if (p->xdg_surface)  xdg_surface_destroy(p->xdg_surface);
    if (p->surface)      wl_surface_destroy(p->surface);
    if (p->xdg_wm_base)  xdg_wm_base_destroy(p->xdg_wm_base);
    if (p->seat)         wl_seat_destroy(p->seat);
    /* R443: multi-output */
    for (u32 i = 0; i < WAYLAND_OUTPUT_MAX; i++) {
        if (p->xdg_outputs[i]) zxdg_output_v1_destroy(p->xdg_outputs[i]);
        if (p->outputs[i])     wl_output_destroy(p->outputs[i]);
        free(p->output_ctx[i]);
    }
    if (p->xdg_output_mgr) zxdg_output_manager_v1_destroy(p->xdg_output_mgr);
#ifdef ENGINE_WAYLAND_FRACTIONAL_SCALE
    if (p->fractional_scale_manager)
        wp_fractional_scale_manager_v1_destroy(p->fractional_scale_manager);
    if (p->viewporter) wp_viewporter_destroy(p->viewporter);
#endif
    if (p->compositor)   wl_compositor_destroy(p->compositor);
    if (p->shm)          wl_shm_destroy(p->shm);
#ifdef ENGINE_WAYLAND_CURSOR_SHAPE
    if (p->cursor_shape_manager) wp_cursor_shape_manager_v1_destroy(p->cursor_shape_manager);
#endif
    if (p->registry)     wl_registry_destroy(p->registry);
    if (p->xkb_state)   xkb_state_unref(p->xkb_state);
    if (p->xkb_keymap)  xkb_keymap_unref(p->xkb_keymap);
    if (p->xkb_ctx)     xkb_context_unref(p->xkb_ctx);
    if (p->display)     wl_display_disconnect(p->display);

    free(p);
    LOG_INFO("Platform destroyed (Wayland)");
}

PlatformEventResult platform_poll(Platform *p) {
    input_new_frame(&p->input);

    if (wl_display_dispatch_pending(p->display) < 0) {
        LOG_ERROR("Wayland display error");
        p->should_close = true;
        return PLATFORM_EVENT_QUIT;
    }
    wayland_clipboard_drain(p);
    wayland_clipboard_drain_writes(p);

    /* R419 (PERF): wl_display_roundtrip() blocked on a full compositor
     * round-trip every frame. Use the prepare_read pattern with a zero-timeout
     * poll instead: flush outgoing requests, read whatever is already buffered
     * on the socket (non-blocking), then dispatch — all pending events are
     * still processed each call, but we never wait on the compositor. */
    while (wl_display_prepare_read(p->display) != 0) {
        if (wl_display_dispatch_pending(p->display) < 0) {
            LOG_ERROR("Wayland display error");
            p->should_close = true;
            return PLATFORM_EVENT_QUIT;
        }
    }
    wl_display_flush(p->display);
    struct pollfd pfd = { wl_display_get_fd(p->display), POLLIN, 0 };
    if (poll(&pfd, 1, 0) > 0 && (pfd.revents & POLLIN)) {
        if (wl_display_read_events(p->display) < 0) {
            LOG_ERROR("Wayland read failed");
            p->should_close = true;
            return PLATFORM_EVENT_QUIT;
        }
    } else {
        wl_display_cancel_read(p->display);
    }
    if (wl_display_dispatch_pending(p->display) < 0) {
        LOG_ERROR("Wayland dispatch failed");
        p->should_close = true;
        return PLATFORM_EVENT_QUIT;
    }
    wayland_clipboard_drain(p);
    wayland_clipboard_drain_writes(p);

    /* Pump gamepads (evdev) into the shared input state. */
    gamepad_poll(p->input.gamepads);

    if (p->should_close) return PLATFORM_EVENT_QUIT;
    return PLATFORM_EVENT_NONE;
}

u32 platform_poll_text(Platform *p, PlatformTextEvent *out, u32 max_events) {
    return p != NULL ? platform_text_queue_pop(&p->text_queue, out, max_events) : 0;
}

void platform_ime_set_enabled(Platform *p, bool enabled) {
    if (p == NULL || p->ime_enabled == enabled) return;
    p->ime_enabled = enabled;
    wayland_commit_text_input_state(p);
}

bool platform_ime_is_enabled(Platform *p) {
    return p != NULL && p->ime_enabled && p->text_input != NULL &&
           p->text_input_focused;
}

void platform_ime_set_surrounding(Platform *p, const char *utf8, i32 cursor,
                                  i32 anchor) {
    if (p == NULL) return;
    platform_ime_surrounding_set(&p->ime_surrounding, utf8,
                                 cursor > 0 ? (usize)cursor : 0,
                                 anchor > 0 ? (usize)anchor : 0);
    if (p->ime_enabled) wayland_commit_text_input_state(p);
}

void platform_ime_set_spot(Platform *p, i32 x, i32 y) {
    if (p == NULL) return;
    p->ime_spot_x = x;
    p->ime_spot_y = y;
    if (p->ime_enabled) wayland_commit_text_input_state(p);
}

InputState *platform_input(Platform *p) {
    return &p->input;
}

void *platform_window_native(Platform *p) {
    return (void *)p->egl_window;
}

void *platform_display_native(Platform *p) {
    return (void *)p->display;
}

void *platform_surface_native(Platform *p) {
    return (void *)p->surface;
}

void platform_get_size(Platform *p, u32 *w, u32 *h) {
    if (w) *w = p->width;
    if (h) *h = p->height;
}

void platform_get_logical_size(Platform *p, u32 *w, u32 *h) {
    if (w) *w = p != NULL ? p->width : 0;
    if (h) *h = p != NULL ? p->height : 0;
}

void platform_get_drawable_size(Platform *p, u32 *w, u32 *h) {
    u32 scale = p != NULL ? p->content_scale_120 : 120u;
    if (w) *w = p != NULL ? wl_out_drawable_dimension(p->width, scale) : 0;
    if (h) *h = p != NULL ? wl_out_drawable_dimension(p->height, scale) : 0;
}

f32 platform_get_dpi(Platform *p) {
    return p->dpi;
}

f32 platform_get_content_scale(Platform *p) {
    return p != NULL && p->content_scale_120 > 0
               ? (f32)p->content_scale_120 / 120.0f
               : 1.0f;
}

f32 platform_get_input_scale(Platform *p) {
    (void)p;
    return 1.0f;
}

i32 platform_get_scale_factor(Platform *p) {
    return p->scale;
}

u32 platform_get_monitor_count(Platform *p) {
    /* R443: count outputs whose initial event burst completed (done). */
    u32 n = 0;
    for (u32 i = 0; i < p->output_list.count; i++)
        if (p->output_list.items[i].done) n++;
    return n;
}

bool platform_get_monitor_info(Platform *p, u32 index, MonitorInfo *out) {
    if (!out) return false;
    /* R443: map the public packed index onto the nth completed output slot. */
    for (u32 i = 0; i < p->output_list.count; i++) {
        const WaylandOutputInfo *o = &p->output_list.items[i];
        if (!o->done) continue;
        if (index-- > 0) continue;
        memset(out, 0, sizeof(*out));
        memcpy(out->name, o->name, sizeof(out->name));
        out->x = o->x;
        out->y = o->y;
        out->width = o->width;
        out->height = o->height;
        out->refresh_rate = o->refresh_rate;
        out->scale = o->scale;
        out->dpi = 96.0f * (f32)o->scale;
        out->primary = (i == 0);
        return true;
    }
    return false;
}

void platform_toggle_fullscreen(Platform *p) {
    if (p->is_fullscreen) {
        xdg_toplevel_unset_fullscreen(p->toplevel);
    } else {
        xdg_toplevel_set_fullscreen(p->toplevel, NULL);
    }
    p->is_fullscreen = !p->is_fullscreen;
    wl_surface_commit(p->surface);
}

static const char *wayland_cursor_name(PlatformCursor cursor) {
    switch (cursor) {
    case PLATFORM_CURSOR_TEXT:
        return "text";
    case PLATFORM_CURSOR_HAND:
        return "pointer";
    case PLATFORM_CURSOR_ARROW:
    default:
        return "left_ptr";
    }
}

#ifdef ENGINE_WAYLAND_CURSOR_SHAPE
static u32 wayland_cursor_shape(PlatformCursor cursor) {
    switch (cursor) {
    case PLATFORM_CURSOR_TEXT:
        return WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_TEXT;
    case PLATFORM_CURSOR_HAND:
        return WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_POINTER;
    case PLATFORM_CURSOR_ARROW:
    default:
        return WP_CURSOR_SHAPE_DEVICE_V1_SHAPE_DEFAULT;
    }
}

static void wayland_create_cursor_device(Platform *p) {
    if (p->cursor_shape_manager != NULL && p->pointer != NULL &&
        p->cursor_shape_device == NULL) {
        p->cursor_shape_device = wp_cursor_shape_manager_v1_get_pointer(
            p->cursor_shape_manager, p->pointer);
    }
}
#else
static void wayland_create_cursor_device(Platform *p) {
    (void)p;
}
#endif

/* The optional cursor-shape protocol avoids client-side cursor buffers. When
 * unavailable, use the compositor's Xcursor theme without blocking the frame. */
static void wayland_update_cursor_visibility(Platform *p) {
    struct wl_cursor *cursor;
    struct wl_cursor_image *image;
    struct wl_buffer *buffer;
    if (!p->pointer || p->pointer_enter_serial == 0) return;
    if (!p->mouse_visible) {
        wl_pointer_set_cursor(p->pointer, p->pointer_enter_serial, NULL, 0, 0);
        return;
    }
#ifdef ENGINE_WAYLAND_CURSOR_SHAPE
    if (p->cursor_shape_device != NULL) {
        wp_cursor_shape_device_v1_set_shape(p->cursor_shape_device,
                                            p->pointer_enter_serial,
                                            wayland_cursor_shape(p->cursor));
        return;
    }
#endif
    if (p->cursor_theme == NULL && p->shm != NULL) {
        i32 cursor_scale = wl_out_cursor_buffer_scale(p->content_scale_120);
        p->cursor_theme = wl_cursor_theme_load(NULL, 24 * cursor_scale, p->shm);
        if (p->cursor_theme != NULL) {
            p->cursor_surface = wl_compositor_create_surface(p->compositor);
            if (p->cursor_surface != NULL)
                wl_surface_set_buffer_scale(p->cursor_surface, cursor_scale);
        }
    }
    if (p->cursor_theme == NULL || p->cursor_surface == NULL) return;
    cursor = wl_cursor_theme_get_cursor(p->cursor_theme,
                                        wayland_cursor_name(p->cursor));
    if (cursor == NULL || cursor->image_count == 0) return;
    image = cursor->images[0];
    buffer = wl_cursor_image_get_buffer(image);
    wl_pointer_set_cursor(p->pointer, p->pointer_enter_serial, p->cursor_surface,
                          image->hotspot_x, image->hotspot_y);
    wl_surface_attach(p->cursor_surface, buffer, 0, 0);
    wl_surface_damage(p->cursor_surface, 0, 0, image->width, image->height);
    wl_surface_commit(p->cursor_surface);
}

/* Lock + relative motion: confines the pointer in place and feeds unaccelerated
 * deltas via the relative-pointer protocol — the correct Wayland analog of an
 * X11 warp-based capture. */
static void wayland_apply_relative(Platform *p) {
    if (!p->pointer) return;

    if (p->rel_pointer_mgr && !p->rel_pointer) {
        p->rel_pointer = zwp_relative_pointer_manager_v1_get_relative_pointer(
            p->rel_pointer_mgr, p->pointer);
        if (p->rel_pointer)
            zwp_relative_pointer_v1_add_listener(p->rel_pointer,
                &relative_pointer_listener, p);
    }
    if (p->pointer_constraints && p->surface && !p->locked_pointer) {
        p->locked_pointer = zwp_pointer_constraints_v1_lock_pointer(
            p->pointer_constraints, p->surface, p->pointer, NULL,
            ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
    }
    if (!p->rel_pointer_mgr || !p->pointer_constraints) {
        LOG_WARN("Wayland: compositor lacks relative-pointer/pointer-constraints; "
                 "relative mouse degraded");
    }
}

static void wayland_clear_relative(Platform *p) {
    if (p->locked_pointer) {
        zwp_locked_pointer_v1_destroy(p->locked_pointer);
        p->locked_pointer = NULL;
    }
    if (p->rel_pointer) {
        zwp_relative_pointer_v1_destroy(p->rel_pointer);
        p->rel_pointer = NULL;
    }
}

void platform_mouse_capture(Platform *p, bool capture) {
    /* On Wayland "capture" maps to a persistent pointer lock. */
    p->mouse_captured = capture;
    if (capture) wayland_apply_relative(p);
    else if (!p->mouse_relative) wayland_clear_relative(p);
}

void platform_mouse_set_visible(Platform *p, bool visible) {
    p->mouse_visible = visible;
    wayland_update_cursor_visibility(p);
}

bool platform_cursor_set(Platform *p, PlatformCursor cursor) {
    if (p == NULL || cursor > PLATFORM_CURSOR_HAND) return false;
    p->cursor = cursor;
    wayland_update_cursor_visibility(p);
    return true;
}

bool platform_window_begin_move(Platform *p) {
    if (p == NULL || p->toplevel == NULL || p->seat == NULL ||
        p->pointer_button_serial == 0) {
        return false;
    }
    xdg_toplevel_move(p->toplevel, p->seat, p->pointer_button_serial);
    return true;
}

bool platform_needs_client_decoration(Platform *p) {
    (void)p;
    /* xdg-shell has no mandatory server-decoration protocol; use myui's CSD
     * so title bars and dragging behave consistently across compositors. */
    return true;
}

bool platform_clipboard_set_text(Platform *p, const char *utf8) {
    WaylandClipboardSource *source;
    usize length;
    if (p == NULL || utf8 == NULL || p->data_device_manager == NULL) return false;
    length = strlen(utf8);
    source = calloc(1, sizeof(*source));
    if (source == NULL) return false;
    source->text = malloc(length + 1);
    if (source->text == NULL) {
        free(source);
        return false;
    }
    memcpy(source->text, utf8, length + 1);
    source->source = wl_data_device_manager_create_data_source(p->data_device_manager);
    if (source->source == NULL || !wayland_clipboard_set_cached(p, utf8, length)) {
        if (source->source != NULL) wl_data_source_destroy(source->source);
        free(source->text);
        free(source);
        return false;
    }
    wayland_clipboard_offer_destroy(&p->clipboard_offer);
    p->clipboard_offer_read_complete = false;
    source->platform = p;
    source->length = length;
    source->next = p->clipboard_sources;
    p->clipboard_sources = source;
    wl_data_source_add_listener(source->source, &clipboard_source_listener, source);
    wl_data_source_offer(source->source, WAYLAND_MIME_UTF8);
    wl_data_source_offer(source->source, WAYLAND_MIME_TEXT);
    p->clipboard_source = source;
    wayland_clipboard_publish(p);
    return true;
}

bool platform_clipboard_get_text(Platform *p, char *out, usize out_size) {
    int fds[2];
    int flags;
    if (p == NULL || out == NULL || out_size == 0) return false;
    if (p->clipboard_offer != NULL && !p->clipboard_offer_read_complete) {
        /* A newly selected external owner supersedes our old local cache. */
    } else if (p->clipboard_text != NULL) {
        (void)platform_utf8_copy(out, out_size, p->clipboard_text);
        return true;
    }
    if (p->clipboard_offer == NULL || p->clipboard_offer->mime_type == NULL ||
        p->clipboard_read_fd >= 0) return false;
    if (pipe(fds) != 0) return false;
    flags = fcntl(fds[0], F_GETFL);
    if (flags < 0 || fcntl(fds[0], F_SETFL, flags | O_NONBLOCK) < 0) {
        close(fds[0]);
        close(fds[1]);
        return false;
    }
    wl_data_offer_receive(p->clipboard_offer->offer,
                          p->clipboard_offer->mime_type, fds[1]);
    close(fds[1]);
    p->clipboard_read_fd = fds[0];
    wl_display_flush(p->display);
    wayland_clipboard_drain(p);
    if (p->clipboard_offer_read_complete && p->clipboard_text != NULL) {
        (void)platform_utf8_copy(out, out_size, p->clipboard_text);
        return true;
    }
    return false;
}

PlatformClipboardResult platform_clipboard_get_text_alloc(Platform *p,
                                                           char **out) {
    int fds[2];
    int flags;
    if (p == NULL || out == NULL) return PLATFORM_CLIPBOARD_EMPTY;
    *out = NULL;
    if ((p->clipboard_offer == NULL || p->clipboard_offer_read_complete) &&
        p->clipboard_text != NULL) {
        *out = wayland_clipboard_duplicate(p->clipboard_text);
        return *out != NULL ? PLATFORM_CLIPBOARD_READY : PLATFORM_CLIPBOARD_EMPTY;
    }
    if (p->clipboard_offer == NULL || p->clipboard_offer->mime_type == NULL)
        return PLATFORM_CLIPBOARD_EMPTY;
    if (p->clipboard_read_fd >= 0) return PLATFORM_CLIPBOARD_PENDING;
    if (pipe(fds) != 0) return PLATFORM_CLIPBOARD_EMPTY;
    flags = fcntl(fds[0], F_GETFL);
    if (flags < 0 || fcntl(fds[0], F_SETFL, flags | O_NONBLOCK) < 0) {
        close(fds[0]);
        close(fds[1]);
        return PLATFORM_CLIPBOARD_EMPTY;
    }
    wl_data_offer_receive(p->clipboard_offer->offer,
                          p->clipboard_offer->mime_type, fds[1]);
    close(fds[1]);
    p->clipboard_read_fd = fds[0];
    wl_display_flush(p->display);
    wayland_clipboard_drain(p);
    if (p->clipboard_offer_read_complete && p->clipboard_text != NULL) {
        *out = wayland_clipboard_duplicate(p->clipboard_text);
        return *out != NULL ? PLATFORM_CLIPBOARD_READY : PLATFORM_CLIPBOARD_EMPTY;
    }
    return PLATFORM_CLIPBOARD_PENDING;
}

void platform_mouse_set_relative(Platform *p, bool relative) {
    p->mouse_relative = relative;
    if (relative) {
        wayland_apply_relative(p);
        p->mouse_visible = false;
        wayland_update_cursor_visibility(p);
    } else {
        if (!p->mouse_captured) wayland_clear_relative(p);
        p->mouse_visible = true;
        wayland_update_cursor_visibility(p);
    }
}

#endif /* ENGINE_PLATFORM_WAYLAND */
