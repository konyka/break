#ifndef PLATFORM_TEXT_H
#define PLATFORM_TEXT_H

#include "platform/platform.h"

#define PLATFORM_TEXT_QUEUE_INITIAL_CAPACITY 16
#define PLATFORM_TEXT_MAX_BYTES (16u * 1024u * 1024u)
#define PLATFORM_TEXT_QUEUE_MAX_BYTES (32u * 1024u * 1024u)
#define PLATFORM_TEXT_QUEUE_MAX_EVENTS 4096u
#define PLATFORM_IME_SURROUNDING_MAX 4000

typedef struct PlatformTextQueue {
    PlatformTextEvent *events;
    u32 count;
    u32 capacity;
    u32 head;
    usize bytes;
} PlatformTextQueue;

typedef struct PlatformImeSurrounding {
    char utf8[PLATFORM_IME_SURROUNDING_MAX + 1];
    i32 cursor;
    i32 anchor;
} PlatformImeSurrounding;

bool platform_text_queue_push(PlatformTextQueue *queue, PlatformTextType type,
                              const char *utf8, i32 cursor);
bool platform_text_queue_push_delete(PlatformTextQueue *queue, i32 before,
                                     i32 after);
u32 platform_text_queue_pop(PlatformTextQueue *queue, PlatformTextEvent *out,
                            u32 max_events);
const char *platform_text_event_utf8(const PlatformTextEvent *event);
void platform_text_event_destroy(PlatformTextEvent *event);
void platform_text_queue_destroy(PlatformTextQueue *queue);
usize platform_utf8_copy(char *out, usize out_size, const char *text);
void platform_ime_surrounding_set(PlatformImeSurrounding *surrounding,
                                  const char *text, usize cursor,
                                  usize anchor);
usize platform_utf16_to_utf8(const uint16_t *text, usize units, char *out,
                             usize out_size);
char *platform_utf16_to_utf8_alloc(const uint16_t *text, usize units);
i32 platform_utf16_units_to_codepoints(const uint16_t *text, i32 units);
i32 platform_utf8_byte_to_codepoints(const char *text, i32 byte_offset);
i32 platform_utf8_byte_to_utf16_units(const char *text, i32 byte_offset);

#endif
