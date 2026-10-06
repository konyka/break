/* Widget key-event tests for my_edit / my_text_area (headless: the widget
 * vtable is driven directly, test_myui_chart precedent). */
#include "test_framework.h"

#include <string.h>

#include "mypal/my_event.h"
#include "myui/widgets/my_edit.h"
#include "myui/widgets/my_text_area.h"

static my_event_t key_event(uint32_t key) {
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
  event.u.key.key = key;
  return event;
}

TEST(edit_backspace_and_delete_are_grapheme_aware)
{
  /* R659: Backspace/Delete remove the whole grapheme cluster (bounded
   * UAX#29), never half of it. */
  my_widget_t* widget = my_edit_create(NULL);
  my_edit_t* edit = (my_edit_t*)widget;
  my_event_t event;

  ASSERT_NOT_NULL(widget);
  edit->focused = true;

  /* a + U+0301 + b (4 bytes) clusters as [á][b]: backspace between them
   * removes the whole á cluster. */
  ASSERT_EQ(my_edit_set_text(widget, "a" "\xCC\x81" "b"), MY_RET_OK);
  edit->cursor = 3u;
  edit->anchor = 3u;
  event = key_event(MY_KEY_BACKSPACE);
  ASSERT_EQ(widget->vtable->on_event(widget, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_edit_get_text(widget), "b");
  ASSERT_EQ(edit->cursor, 0u);

  /* at the very end: 'b' goes first, then the cluster. */
  ASSERT_EQ(my_edit_set_text(widget, "a" "\xCC\x81" "b"), MY_RET_OK);
  edit->cursor = 4u;
  edit->anchor = 4u;
  event = key_event(MY_KEY_BACKSPACE);
  ASSERT_EQ(widget->vtable->on_event(widget, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_edit_get_text(widget), "a" "\xCC\x81");
  ASSERT_EQ(edit->cursor, 3u);
  event = key_event(MY_KEY_BACKSPACE);
  ASSERT_EQ(widget->vtable->on_event(widget, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_edit_get_text(widget), "");

  /* Delete at 0 removes the whole cluster as well. */
  ASSERT_EQ(my_edit_set_text(widget, "a" "\xCC\x81" "b"), MY_RET_OK);
  edit->cursor = 0u;
  edit->anchor = 0u;
  event = key_event(MY_KEY_DELETE);
  ASSERT_EQ(widget->vtable->on_event(widget, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_edit_get_text(widget), "b");

  /* family emoji chain (18 bytes, 5 codepoints): one backspace. */
  ASSERT_EQ(my_edit_set_text(widget,
                             "\xF0\x9F\x91\xA8\xE2\x80\x8D\xF0\x9F\x91\xA9"
                             "\xE2\x80\x8D\xF0\x9F\x91\xA7"),
            MY_RET_OK);
  edit->cursor = 18u;
  edit->anchor = 18u;
  event = key_event(MY_KEY_BACKSPACE);
  ASSERT_EQ(widget->vtable->on_event(widget, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_edit_get_text(widget), "");

  /* arrows skip cluster interiors in byte space too. */
  ASSERT_EQ(my_edit_set_text(widget, "a" "\xCC\x81" "b"), MY_RET_OK);
  edit->cursor = 0u;
  edit->anchor = 0u;
  event = key_event(MY_KEY_RIGHT);
  ASSERT_EQ(widget->vtable->on_event(widget, &event), MY_RET_OK);
  ASSERT_EQ(edit->cursor, 3u);
  event = key_event(MY_KEY_LEFT);
  ASSERT_EQ(widget->vtable->on_event(widget, &event), MY_RET_OK);
  ASSERT_EQ(edit->cursor, 0u);

  /* regional indicators: backspace removes the trailing pair. */
  ASSERT_EQ(my_edit_set_text(widget,
                             "\xF0\x9F\x87\xAB\xF0\x9F\x87\xB7"
                             "\xF0\x9F\x87\xAF\xF0\x9F\x87\xB5"),
            MY_RET_OK);
  edit->cursor = 16u;
  edit->anchor = 16u;
  event = key_event(MY_KEY_BACKSPACE);
  ASSERT_EQ(widget->vtable->on_event(widget, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_edit_get_text(widget),
                "\xF0\x9F\x87\xAB\xF0\x9F\x87\xB7");

  my_widget_unref(widget);
}

TEST(text_area_backspace_and_delete_are_grapheme_aware)
{
  my_widget_t* widget = my_text_area_create(NULL);
  my_text_area_t* area = (my_text_area_t*)widget;
  my_event_t event;

  ASSERT_NOT_NULL(widget);
  area->focused = true;

  ASSERT_EQ(my_text_area_set_text(widget, "a" "\xCC\x81" "b"), MY_RET_OK);
  area->cursor_row = 0u;
  area->cursor_col = 2u;
  area->anchor_row = 0u;
  area->anchor_col = 2u;
  event = key_event(MY_KEY_BACKSPACE);
  ASSERT_EQ(widget->vtable->on_event(widget, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(widget), "b");
  ASSERT_EQ(area->cursor_col, 0u);

  ASSERT_EQ(my_text_area_set_text(widget, "a" "\xCC\x81" "b"), MY_RET_OK);
  area->cursor_row = 0u;
  area->cursor_col = 3u;
  area->anchor_row = 0u;
  area->anchor_col = 3u;
  event = key_event(MY_KEY_BACKSPACE);
  ASSERT_EQ(widget->vtable->on_event(widget, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(widget), "a" "\xCC\x81");
  ASSERT_EQ(area->cursor_col, 2u);
  event = key_event(MY_KEY_BACKSPACE);
  ASSERT_EQ(widget->vtable->on_event(widget, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(widget), "");

  ASSERT_EQ(my_text_area_set_text(widget, "a" "\xCC\x81" "b"), MY_RET_OK);
  area->cursor_row = 0u;
  area->cursor_col = 0u;
  area->anchor_row = 0u;
  area->anchor_col = 0u;
  event = key_event(MY_KEY_DELETE);
  ASSERT_EQ(widget->vtable->on_event(widget, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(widget), "b");

  /* family emoji chain: one backspace clears it. */
  ASSERT_EQ(my_text_area_set_text(widget,
                                  "\xF0\x9F\x91\xA8\xE2\x80\x8D\xF0\x9F\x91\xA9"
                                  "\xE2\x80\x8D\xF0\x9F\x91\xA7"),
            MY_RET_OK);
  area->cursor_row = 0u;
  area->cursor_col = 5u;
  area->anchor_row = 0u;
  area->anchor_col = 5u;
  event = key_event(MY_KEY_BACKSPACE);
  ASSERT_EQ(widget->vtable->on_event(widget, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(widget), "");

  my_widget_unref(widget);
}

TEST_MAIN_BEGIN()
RUN_TEST(edit_backspace_and_delete_are_grapheme_aware);
RUN_TEST(text_area_backspace_and_delete_are_grapheme_aware);
TEST_MAIN_END()
