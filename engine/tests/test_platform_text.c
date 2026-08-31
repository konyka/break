#include "test_framework.h"

#include "platform/platform_text.h"

#include <string.h>

TEST(queue_is_fifo_and_accepts_empty_preedit)
{
    PlatformTextQueue queue = {0};
    PlatformTextEvent events[3];

    ASSERT_TRUE(platform_text_queue_push(&queue, PLATFORM_TEXT_PREEDIT, "", 0));
    ASSERT_TRUE(platform_text_queue_push_delete(&queue, 3, 2));
    ASSERT_TRUE(platform_text_queue_push(&queue, PLATFORM_TEXT_COMMIT, "hello", 0));
    ASSERT_EQ(platform_text_queue_pop(&queue, events, 3), 3u);
    ASSERT_EQ(events[0].type, PLATFORM_TEXT_PREEDIT);
    ASSERT_EQ(strcmp(events[0].utf8, ""), 0);
    ASSERT_EQ(events[1].type, PLATFORM_TEXT_DELETE_SURROUNDING);
    ASSERT_EQ(events[1].before, 3);
    ASSERT_EQ(events[1].after, 2);
    ASSERT_EQ(events[2].type, PLATFORM_TEXT_COMMIT);
    ASSERT_EQ(strcmp(events[2].utf8, "hello"), 0);
    for (u32 i = 0; i < 3; i++) platform_text_event_destroy(&events[i]);
    platform_text_queue_destroy(&queue);
}

TEST(empty_queue_poll_is_safe)
{
    PlatformTextQueue queue = {0};
    PlatformTextEvent event;

    ASSERT_EQ(platform_text_queue_pop(&queue, &event, 1), 0u);
    platform_text_queue_destroy(&queue);
}

TEST(queue_preserves_long_utf8_text)
{
    PlatformTextQueue queue = {0};
    PlatformTextEvent event;
    char text[80];

    memset(text, 'a', 62);
    memcpy(text + 62, "\xE4\xB8\xAD", 3);
    text[65] = '\0';
    ASSERT_TRUE(platform_text_queue_push(&queue, PLATFORM_TEXT_COMMIT, text, 0));
    ASSERT_EQ(platform_text_queue_pop(&queue, &event, 1), 1u);
    ASSERT_EQ(strlen(platform_text_event_utf8(&event)), 65u);
    ASSERT_EQ(strcmp(platform_text_event_utf8(&event), text), 0);
    platform_text_event_destroy(&event);
    platform_text_queue_destroy(&queue);
}

TEST(utf8_copy_keeps_codepoint_boundaries)
{
    char output[5];

    ASSERT_EQ(platform_utf8_copy(output, sizeof(output),
                                  "a\xE4\xB8\xAD" "b"), 4u);
    ASSERT_EQ(strcmp(output, "a\xE4\xB8\xAD"), 0);
}

TEST(utf8_copy_handles_truncated_sequences)
{
    const char text[] = "\xE4";
    char output[4];

    ASSERT_EQ(platform_utf8_copy(output, sizeof(output), text), 1u);
    ASSERT_EQ((unsigned char)output[0], 0xE4u);
    ASSERT_EQ(output[1], '\0');
    ASSERT_EQ(platform_utf8_byte_to_codepoints(text, 1), 1);
}

TEST(queue_grows_without_dropping_events)
{
    PlatformTextQueue queue = {0};
    enum { event_count = 64 };
    PlatformTextEvent events[event_count];

    for (u32 i = 0; i < event_count; i++) {
        ASSERT_TRUE(platform_text_queue_push(&queue, PLATFORM_TEXT_COMMIT,
                                             "x", 0));
    }
    ASSERT_EQ(platform_text_queue_pop(&queue, events, event_count), event_count);
    for (u32 i = 0; i < event_count; i++) platform_text_event_destroy(&events[i]);
    platform_text_queue_destroy(&queue);
}

TEST(queue_wraps_without_reordering_events)
{
    PlatformTextQueue queue = {0};
    PlatformTextEvent events[PLATFORM_TEXT_QUEUE_INITIAL_CAPACITY];

    for (u32 i = 0; i < PLATFORM_TEXT_QUEUE_INITIAL_CAPACITY; i++) {
        ASSERT_TRUE(platform_text_queue_push_delete(&queue, (i32)i, 0));
    }
    ASSERT_EQ(platform_text_queue_pop(&queue, events, 8), 8u);
    for (u32 i = 0; i < 8; i++) platform_text_event_destroy(&events[i]);
    for (u32 i = 0; i < 8; i++) {
        ASSERT_TRUE(platform_text_queue_push_delete(&queue, (i32)(16 + i), 0));
    }
    ASSERT_EQ(platform_text_queue_pop(&queue, events,
                                      PLATFORM_TEXT_QUEUE_INITIAL_CAPACITY),
              PLATFORM_TEXT_QUEUE_INITIAL_CAPACITY);
    for (u32 i = 0; i < PLATFORM_TEXT_QUEUE_INITIAL_CAPACITY; i++) {
        ASSERT_EQ(events[i].before, (i32)(8 + i));
        platform_text_event_destroy(&events[i]);
    }
    platform_text_queue_destroy(&queue);
}

TEST(queue_coalesces_adjacent_preedit_events)
{
    PlatformTextQueue queue = {0};
    PlatformTextEvent event;

    ASSERT_TRUE(platform_text_queue_push(&queue, PLATFORM_TEXT_PREEDIT, "a", 1));
    ASSERT_TRUE(platform_text_queue_push(&queue, PLATFORM_TEXT_PREEDIT,
                                         "a\xE4\xB8\xAD", 2));
    ASSERT_EQ(queue.count, 1u);
    ASSERT_EQ(platform_text_queue_pop(&queue, &event, 1), 1u);
    ASSERT_EQ(strcmp(platform_text_event_utf8(&event), "a\xE4\xB8\xAD"), 0);
    ASSERT_EQ(event.cursor, 2);
    platform_text_event_destroy(&event);
    platform_text_queue_destroy(&queue);
}

TEST(queue_rejects_events_when_payload_budget_is_exhausted)
{
    PlatformTextQueue queue = {0};
    char *text = malloc(PLATFORM_TEXT_MAX_BYTES + 1u);

    ASSERT_NOT_NULL(text);
    memset(text, 'x', PLATFORM_TEXT_MAX_BYTES);
    text[PLATFORM_TEXT_MAX_BYTES] = '\0';
    ASSERT_TRUE(platform_text_queue_push(&queue, PLATFORM_TEXT_COMMIT, text, 0));
    ASSERT_TRUE(platform_text_queue_push(&queue, PLATFORM_TEXT_COMMIT, text, 0));
    ASSERT_FALSE(platform_text_queue_push(&queue, PLATFORM_TEXT_COMMIT, text, 0));
    free(text);
    platform_text_queue_destroy(&queue);
}

TEST(queue_rejects_events_when_slot_budget_is_exhausted)
{
    PlatformTextQueue queue = {0};

    for (u32 i = 0; i < PLATFORM_TEXT_QUEUE_MAX_EVENTS; i++) {
        ASSERT_TRUE(platform_text_queue_push_delete(&queue, 0, 0));
    }
    ASSERT_FALSE(platform_text_queue_push_delete(&queue, 0, 0));
    platform_text_queue_destroy(&queue);
}

TEST(utf16_converts_surrogates_and_replacements)
{
    const uint16_t text[] = {'A', 0x4E2D, 0xD83D, 0xDE42, 0xD800, 'B'};
    char utf8[32];

    ASSERT_EQ(platform_utf16_to_utf8(text, 6, utf8, sizeof(utf8)), 12u);
    ASSERT_EQ(strcmp(utf8, "A\xE4\xB8\xAD\xF0\x9F\x99\x82"
                           "\xEF\xBF\xBD"
                           "B"), 0);
    ASSERT_EQ(platform_utf16_units_to_codepoints(text, 4), 3);
    ASSERT_EQ(platform_utf16_units_to_codepoints(text, 6), 5);
}

TEST(utf16_alloc_preserves_long_text)
{
    enum { units = 512 };
    uint16_t text[units];
    char *utf8;

    for (u32 i = 0; i < units; i++) text[i] = 'x';
    utf8 = platform_utf16_to_utf8_alloc(text, units);
    ASSERT_NOT_NULL(utf8);
    ASSERT_EQ(strlen(utf8), (usize)units);
    ASSERT_EQ(utf8[units - 1], 'x');
    free(utf8);
}

TEST(utf16_alloc_accepts_maximum_ascii_text)
{
    uint16_t *text = malloc((PLATFORM_TEXT_MAX_BYTES + 1u) * sizeof(*text));
    char *utf8;

    ASSERT_NOT_NULL(text);
    for (usize i = 0; i < PLATFORM_TEXT_MAX_BYTES; i++) text[i] = 'x';
    text[PLATFORM_TEXT_MAX_BYTES] = 0;
    utf8 = platform_utf16_to_utf8_alloc(text, PLATFORM_TEXT_MAX_BYTES);
    ASSERT_NOT_NULL(utf8);
    ASSERT_EQ(strlen(utf8), (usize)PLATFORM_TEXT_MAX_BYTES);
    ASSERT_EQ(utf8[PLATFORM_TEXT_MAX_BYTES - 1u], 'x');
    free(utf8);
    free(text);
}

TEST(utf16_alloc_accepts_empty_text)
{
    char *utf8 = platform_utf16_to_utf8_alloc(NULL, 0);

    ASSERT_NOT_NULL(utf8);
    ASSERT_EQ(strcmp(utf8, ""), 0);
    free(utf8);
}

TEST(utf8_byte_offsets_convert_to_codepoints)
{
    const char *text = "A\xE4\xB8\xAD\xF0\x9F\x99\x82";

    ASSERT_EQ(platform_utf8_byte_to_codepoints(text, 1), 1);
    ASSERT_EQ(platform_utf8_byte_to_codepoints(text, 4), 2);
    ASSERT_EQ(platform_utf8_byte_to_codepoints(text, 8), 3);
}

TEST(surrounding_text_keeps_cursor_in_a_valid_window)
{
    PlatformImeSurrounding surrounding;
    char text[5001];

    memset(text, 'a', 5000);
    text[5000] = '\0';
    platform_ime_surrounding_set(&surrounding, text, 4500, 4499);
    ASSERT_TRUE(strlen(surrounding.utf8) <= PLATFORM_IME_SURROUNDING_MAX);
    ASSERT_TRUE(surrounding.cursor >= 0);
    ASSERT_TRUE((usize)surrounding.cursor <= strlen(surrounding.utf8));
    ASSERT_EQ(surrounding.anchor, surrounding.cursor - 1);
}

TEST(surrounding_text_preserves_utf8_offsets)
{
    PlatformImeSurrounding surrounding;
    const char *text = "a\xE4\xB8\xAD\xF0\x9F\x99\x82" "b";

    platform_ime_surrounding_set(&surrounding, text, 8, 1);
    ASSERT_EQ(strcmp(surrounding.utf8, text), 0);
    ASSERT_EQ(surrounding.cursor, 8);
    ASSERT_EQ(surrounding.anchor, 1);
    ASSERT_EQ(platform_utf8_byte_to_utf16_units(text, 8), 4);
}

TEST_MAIN_BEGIN()
    RUN_TEST(queue_is_fifo_and_accepts_empty_preedit);
    RUN_TEST(empty_queue_poll_is_safe);
    RUN_TEST(queue_preserves_long_utf8_text);
    RUN_TEST(utf8_copy_keeps_codepoint_boundaries);
    RUN_TEST(utf8_copy_handles_truncated_sequences);
    RUN_TEST(queue_grows_without_dropping_events);
    RUN_TEST(queue_wraps_without_reordering_events);
    RUN_TEST(queue_coalesces_adjacent_preedit_events);
    RUN_TEST(queue_rejects_events_when_payload_budget_is_exhausted);
    RUN_TEST(queue_rejects_events_when_slot_budget_is_exhausted);
    RUN_TEST(utf16_converts_surrogates_and_replacements);
    RUN_TEST(utf16_alloc_preserves_long_text);
    RUN_TEST(utf16_alloc_accepts_maximum_ascii_text);
    RUN_TEST(utf16_alloc_accepts_empty_text);
    RUN_TEST(utf8_byte_offsets_convert_to_codepoints);
    RUN_TEST(surrounding_text_keeps_cursor_in_a_valid_window);
    RUN_TEST(surrounding_text_preserves_utf8_offsets);
TEST_MAIN_END()
