#include "platform/platform_text.h"

#include <stdlib.h>
#include <string.h>

static usize utf8_sequence_length(const unsigned char *text) {
    if (text[0] == '\0') return 0;
    if (text[0] < 0x80u) return 1;
    if (text[1] != '\0' && text[0] >= 0xC2u && text[0] <= 0xDFu &&
        text[1] >= 0x80u &&
        text[1] <= 0xBFu) {
        return 2;
    }
    if (text[1] != '\0' && text[2] != '\0' && text[0] >= 0xE0u &&
        text[0] <= 0xEFu && text[1] >= 0x80u &&
        text[1] <= 0xBFu && text[2] >= 0x80u && text[2] <= 0xBFu &&
        !(text[0] == 0xE0u && text[1] < 0xA0u) &&
        !(text[0] == 0xEDu && text[1] >= 0xA0u)) {
        return 3;
    }
    if (text[1] != '\0' && text[2] != '\0' && text[3] != '\0' &&
        text[0] >= 0xF0u && text[0] <= 0xF4u && text[1] >= 0x80u &&
        text[1] <= 0xBFu && text[2] >= 0x80u && text[2] <= 0xBFu &&
        text[3] >= 0x80u && text[3] <= 0xBFu &&
        !(text[0] == 0xF0u && text[1] < 0x90u) &&
        !(text[0] == 0xF4u && text[1] >= 0x90u)) {
        return 4;
    }
    return 1;
}

static usize utf8_prefix_length(const char *text, usize capacity) {
    usize offset = 0;
    while (text[offset] != '\0') {
        usize length = utf8_sequence_length((const unsigned char *)text + offset);
        if (offset + length > capacity) break;
        offset += length;
    }
    return offset;
}

static usize text_length_limit(const char *text) {
    usize length = 0;
    while (length <= PLATFORM_TEXT_MAX_BYTES && text[length] != '\0') length++;
    return length;
}

static bool platform_text_event_init(PlatformTextEvent *event,
                                     PlatformTextType type, const char *utf8,
                                     usize length, i32 cursor) {
    if (event == NULL) return false;
    memset(event, 0, sizeof(*event));
    event->type = type;
    event->utf8_bytes = length;
    if (length < sizeof(event->utf8)) {
        memcpy(event->utf8, utf8, length + 1);
    } else {
        event->utf8_extra = malloc(length + 1);
        if (event->utf8_extra == NULL) return false;
        memcpy(event->utf8_extra, utf8, length + 1);
    }
    event->cursor = cursor;
    if (type == PLATFORM_TEXT_PREEDIT && cursor > 0) {
        i32 limit = platform_utf8_byte_to_codepoints(utf8, (i32)length);
        if (event->cursor > limit) event->cursor = limit;
    }
    return true;
}

static bool platform_text_queue_reserve(PlatformTextQueue *queue) {
    PlatformTextEvent *events;
    u32 capacity;
    u32 tail_count;
    if (queue == NULL || queue->count >= PLATFORM_TEXT_QUEUE_MAX_EVENTS)
        return false;
    if (queue->count < queue->capacity) return true;
    if (queue->capacity >= PLATFORM_TEXT_QUEUE_MAX_EVENTS) return false;
    if (queue->capacity == 0) {
        capacity = PLATFORM_TEXT_QUEUE_INITIAL_CAPACITY;
    } else if (queue->capacity > PLATFORM_TEXT_QUEUE_MAX_EVENTS / 2u) {
        capacity = PLATFORM_TEXT_QUEUE_MAX_EVENTS;
    } else {
        capacity = queue->capacity * 2u;
    }
    if (capacity > UINT32_MAX / (u32)sizeof(*events)) return false;
    events = realloc(queue->events, (usize)capacity * sizeof(*events));
    if (events == NULL) return false;
    if (queue->count > 0 && queue->head + queue->count > queue->capacity) {
        tail_count = queue->capacity - queue->head;
        memmove(events + queue->capacity, events,
                (usize)(queue->count - tail_count) * sizeof(*events));
    }
    queue->events = events;
    queue->capacity = capacity;
    return true;
}

static PlatformTextEvent *platform_text_queue_tail(PlatformTextQueue *queue) {
    u32 index;
    if (queue == NULL || queue->count == 0 || queue->capacity == 0) return NULL;
    index = (queue->head + queue->count - 1u) % queue->capacity;
    return &queue->events[index];
}

usize platform_utf8_copy(char *out, usize out_size, const char *text) {
    usize length;
    if (out == NULL || out_size == 0) return 0;
    if (text == NULL) {
        out[0] = '\0';
        return 0;
    }
    length = utf8_prefix_length(text, out_size - 1);
    memcpy(out, text, length);
    out[length] = '\0';
    return length;
}

static usize utf8_previous_boundary(const char *text, usize offset) {
    while (offset > 0 && (((unsigned char)text[offset] & 0xC0u) == 0x80u)) {
        offset--;
    }
    return offset;
}

void platform_ime_surrounding_set(PlatformImeSurrounding *surrounding,
                                  const char *text, usize cursor,
                                  usize anchor) {
    usize length;
    usize start = 0;
    usize end;
    if (surrounding == NULL) return;
    memset(surrounding, 0, sizeof(*surrounding));
    if (text == NULL) return;
    length = strlen(text);
    if (cursor > length) cursor = length;
    if (anchor > length) anchor = length;
    cursor = utf8_previous_boundary(text, cursor);
    anchor = utf8_previous_boundary(text, anchor);
    end = length;
    if (length > PLATFORM_IME_SURROUNDING_MAX) {
        usize focus = cursor > anchor ? cursor : anchor;
        start = focus > PLATFORM_IME_SURROUNDING_MAX / 2
                    ? focus - PLATFORM_IME_SURROUNDING_MAX / 2
                    : 0;
        start = utf8_previous_boundary(text, start);
        if (start + PLATFORM_IME_SURROUNDING_MAX < length) {
            end = start + PLATFORM_IME_SURROUNDING_MAX;
            while (end > start && (((unsigned char)text[end] & 0xC0u) == 0x80u)) {
                end--;
            }
        }
        if (cursor < start || anchor < start || cursor > end || anchor > end) {
            start = 0;
            end = utf8_prefix_length(text, PLATFORM_IME_SURROUNDING_MAX);
            /* R572: the fallback resets the window; cursor/anchor that were
             * outside the old window can still exceed the new end — clamp
             * them so the stored offsets stay within [0, end - start]. */
            if (cursor > end) cursor = end;
            if (anchor > end) anchor = end;
        }
    }
    memcpy(surrounding->utf8, text + start, end - start);
    surrounding->utf8[end - start] = '\0';
    surrounding->cursor = (i32)(cursor - start);
    surrounding->anchor = (i32)(anchor - start);
}

bool platform_text_queue_push(PlatformTextQueue *queue, PlatformTextType type,
                              const char *utf8, i32 cursor) {
    PlatformTextEvent event;
    PlatformTextEvent *tail;
    usize length;
    if (queue == NULL || utf8 == NULL) return false;
    length = text_length_limit(utf8);
    if (length > PLATFORM_TEXT_MAX_BYTES) return false;
    tail = type == PLATFORM_TEXT_PREEDIT ? platform_text_queue_tail(queue) : NULL;
    if (tail != NULL && tail->type == PLATFORM_TEXT_PREEDIT) {
        if (queue->bytes - tail->utf8_bytes >
            PLATFORM_TEXT_QUEUE_MAX_BYTES - length) {
            return false;
        }
        if (!platform_text_event_init(&event, type, utf8, length, cursor)) {
            return false;
        }
        queue->bytes -= tail->utf8_bytes;
        platform_text_event_destroy(tail);
        *tail = event;
        queue->bytes += length;
        return true;
    }
    if (queue->bytes > PLATFORM_TEXT_QUEUE_MAX_BYTES - length ||
        !platform_text_queue_reserve(queue) ||
        !platform_text_event_init(&event, type, utf8, length, cursor)) {
        return false;
    }
    queue->events[(queue->head + queue->count) % queue->capacity] = event;
    queue->count++;
    queue->bytes += length;
    return true;
}

bool platform_text_queue_push_delete(PlatformTextQueue *queue, i32 before,
                                     i32 after) {
    PlatformTextEvent *event;
    if (queue == NULL || before < 0 || after < 0) return false;
    if (!platform_text_queue_reserve(queue)) return false;
    event = &queue->events[(queue->head + queue->count) % queue->capacity];
    memset(event, 0, sizeof(*event));
    event->type = PLATFORM_TEXT_DELETE_SURROUNDING;
    event->before = before;
    event->after = after;
    queue->count++;
    return true;
}

u32 platform_text_queue_pop(PlatformTextQueue *queue, PlatformTextEvent *out,
                            u32 max_events) {
    u32 count;
    if (queue == NULL || out == NULL || max_events == 0) return 0;
    if (queue->count == 0 || queue->capacity == 0) return 0;
    count = queue->count < max_events ? queue->count : max_events;
    for (u32 i = 0; i < count; i++) {
        u32 index = (queue->head + i) % queue->capacity;
        out[i] = queue->events[index];
        queue->bytes -= out[i].utf8_bytes;
        memset(&queue->events[index], 0, sizeof(queue->events[index]));
    }
    queue->head = (queue->head + count) % queue->capacity;
    queue->count -= count;
    if (queue->count == 0) queue->head = 0;
    return count;
}

const char *platform_text_event_utf8(const PlatformTextEvent *event) {
    if (event == NULL) return "";
    return event->utf8_extra != NULL ? event->utf8_extra : event->utf8;
}

void platform_text_event_destroy(PlatformTextEvent *event) {
    if (event == NULL) return;
    free(event->utf8_extra);
    memset(event, 0, sizeof(*event));
}

void platform_text_queue_destroy(PlatformTextQueue *queue) {
    if (queue == NULL) return;
    for (u32 i = 0; i < queue->count; i++) {
        u32 index = (queue->head + i) % queue->capacity;
        platform_text_event_destroy(&queue->events[index]);
    }
    free(queue->events);
    queue->events = NULL;
    queue->count = 0;
    queue->capacity = 0;
    queue->head = 0;
    queue->bytes = 0;
}

static usize utf8_encode(uint32_t codepoint, char *out, usize out_size) {
    if (codepoint <= 0x7Fu) {
        if (out_size < 1) return 0;
        out[0] = (char)codepoint;
        return 1;
    }
    if (codepoint <= 0x7FFu) {
        if (out_size < 2) return 0;
        out[0] = (char)(0xC0u | (codepoint >> 6));
        out[1] = (char)(0x80u | (codepoint & 0x3Fu));
        return 2;
    }
    if (codepoint <= 0xFFFFu) {
        if (out_size < 3) return 0;
        out[0] = (char)(0xE0u | (codepoint >> 12));
        out[1] = (char)(0x80u | ((codepoint >> 6) & 0x3Fu));
        out[2] = (char)(0x80u | (codepoint & 0x3Fu));
        return 3;
    }
    if (out_size < 4) return 0;
    out[0] = (char)(0xF0u | (codepoint >> 18));
    out[1] = (char)(0x80u | ((codepoint >> 12) & 0x3Fu));
    out[2] = (char)(0x80u | ((codepoint >> 6) & 0x3Fu));
    out[3] = (char)(0x80u | (codepoint & 0x3Fu));
    return 4;
}

usize platform_utf16_to_utf8(const uint16_t *text, usize units, char *out,
                             usize out_size) {
    usize input_offset = 0;
    usize output_offset = 0;
    if (out == NULL || out_size == 0) return 0;
    if (text == NULL) {
        out[0] = '\0';
        return 0;
    }
    while (input_offset < units && text[input_offset] != 0) {
        uint32_t codepoint = text[input_offset++];
        usize written;
        if (codepoint >= 0xD800u && codepoint <= 0xDBFFu &&
            input_offset < units && text[input_offset] >= 0xDC00u &&
            text[input_offset] <= 0xDFFFu) {
            codepoint = 0x10000u + ((codepoint - 0xD800u) << 10) +
                        (text[input_offset++] - 0xDC00u);
        } else if (codepoint >= 0xD800u && codepoint <= 0xDFFFu) {
            codepoint = 0xFFFDu;
        }
        written = utf8_encode(codepoint, out + output_offset,
                              out_size - output_offset - 1);
        if (written == 0) break;
        output_offset += written;
    }
    out[output_offset] = '\0';
    return output_offset;
}

static bool utf16_utf8_length(const uint16_t *text, usize units, usize *out) {
    usize input_offset = 0;
    usize length = 0;
    if (text == NULL || out == NULL) return false;
    while (input_offset < units && text[input_offset] != 0) {
        uint32_t codepoint = text[input_offset++];
        usize encoded_length;
        if (codepoint >= 0xD800u && codepoint <= 0xDBFFu &&
            input_offset < units && text[input_offset] >= 0xDC00u &&
            text[input_offset] <= 0xDFFFu) {
            codepoint = 0x10000u + ((codepoint - 0xD800u) << 10) +
                        (text[input_offset++] - 0xDC00u);
        } else if (codepoint >= 0xD800u && codepoint <= 0xDFFFu) {
            codepoint = 0xFFFDu;
        }
        encoded_length = codepoint <= 0x7Fu ? 1u : codepoint <= 0x7FFu ? 2u
                              : codepoint <= 0xFFFFu ? 3u : 4u;
        if (length > PLATFORM_TEXT_MAX_BYTES - encoded_length) return false;
        length += encoded_length;
    }
    *out = length;
    return true;
}

char *platform_utf16_to_utf8_alloc(const uint16_t *text, usize units) {
    char *out;
    usize length;
    if (text == NULL && units != 0) return NULL;
    if (units == 0) {
        out = malloc(1);
        if (out != NULL) out[0] = '\0';
        return out;
    }
    if (!utf16_utf8_length(text, units, &length)) return NULL;
    out = malloc(length + 1);
    if (out == NULL) return NULL;
    (void)platform_utf16_to_utf8(text, units, out, length + 1);
    return out;
}

i32 platform_utf16_units_to_codepoints(const uint16_t *text, i32 units) {
    i32 offset = 0;
    i32 count = 0;
    if (text == NULL || units <= 0) return 0;
    while (offset < units && text[offset] != 0) {
        uint16_t first = text[offset++];
        if (first >= 0xD800u && first <= 0xDBFFu && offset < units &&
            text[offset] >= 0xDC00u && text[offset] <= 0xDFFFu) {
            offset++;
        }
        count++;
    }
    return count;
}

i32 platform_utf8_byte_to_codepoints(const char *text, i32 byte_offset) {
    i32 offset = 0;
    i32 count = 0;
    if (text == NULL || byte_offset <= 0) return 0;
    while (offset < byte_offset && text[offset] != '\0') {
        offset += (i32)utf8_sequence_length(
            (const unsigned char *)text + offset);
        count++;
    }
    return count;
}

i32 platform_utf8_byte_to_utf16_units(const char *text, i32 byte_offset) {
    i32 offset = 0;
    i32 units = 0;
    if (text == NULL || byte_offset <= 0) return 0;
    while (offset < byte_offset && text[offset] != '\0') {
        usize length = utf8_sequence_length((const unsigned char *)text + offset);
        units += length == 4 ? 2 : 1;
        offset += (i32)length;
    }
    return units;
}
