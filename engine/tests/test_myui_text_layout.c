#include "test_framework.h"

#include <string.h>

#include "myr/my_arabic_shape.h"
#include "myr/my_line_break.h"
#include "myr/my_text_paragraph.h"
#include "myr/my_text_layout.h"

typedef struct paragraph_test_font_t {
  my_font_t base;
  const uint8_t* bitmap;
} paragraph_test_font_t;

static my_ret_t paragraph_test_measure(my_font_t* font, const char* text,
                                       int32_t size, int32_t* w, int32_t* h) {
  (void)font;
  (void)text;
  if (size <= 0) return MY_RET_INVALID_PARAMS;
  if (w != NULL) *w = size;
  if (h != NULL) *h = size;
  return MY_RET_OK;
}

static my_ret_t paragraph_test_glyph(my_font_t* font, uint32_t cp,
                                     int32_t size, my_glyph_t* glyph) {
  paragraph_test_font_t* test_font = (paragraph_test_font_t*)font;
  (void)cp;
  if (glyph == NULL || size <= 0) return MY_RET_INVALID_PARAMS;
  glyph->bitmap = test_font->bitmap;
  glyph->w = 1;
  glyph->h = 1;
  glyph->bearing_x = 0;
  glyph->bearing_y = 1;
  glyph->advance = 1;
  return MY_RET_OK;
}

static int32_t paragraph_test_ascent(my_font_t* font, int32_t size) {
  (void)font;
  return size;
}

static int32_t paragraph_test_descent(my_font_t* font, int32_t size) {
  (void)font;
  (void)size;
  return 0;
}

static int32_t paragraph_test_line_height(my_font_t* font, int32_t size) {
  (void)font;
  return size;
}

static void paragraph_test_destroy(my_font_t* font) { (void)font; }

static my_ret_t paragraph_test_shape(my_font_t* font, const char* text,
                                     int32_t size, bool rtl,
                                     const my_allocator_t* allocator,
                                     my_font_shape_result_t* result) {
  (void)font;
  (void)rtl;
  if (text == NULL || size <= 0 || result == NULL) return MY_RET_INVALID_PARAMS;
  result->allocator = allocator;
  result->glyphs = (my_font_shape_glyph_t*)my_mem_calloc(
      allocator, 4, sizeof(my_font_shape_glyph_t));
  if (result->glyphs == NULL) return MY_RET_OOM;
  result->count = 4;
  result->glyphs[0].glyph_id = 1;
  result->glyphs[0].cluster = 0;
  result->glyphs[0].advance_x_26_6 = 64;
  result->glyphs[1].glyph_id = 1;
  result->glyphs[1].cluster = 1;
  result->glyphs[1].advance_x_26_6 = 64;
  result->glyphs[2].glyph_id = 1;
  result->glyphs[2].cluster = 2;
  result->glyphs[2].advance_x_26_6 = 3 * 64;
  result->glyphs[3].glyph_id = 1;
  result->glyphs[3].cluster = 5;
  result->glyphs[3].advance_x_26_6 = 2 * 64;
  return MY_RET_OK;
}

static const my_font_vtable_t s_paragraph_test_vtable = {
    paragraph_test_measure, paragraph_test_glyph, paragraph_test_ascent,
    paragraph_test_descent, paragraph_test_line_height, paragraph_test_destroy,
    NULL, paragraph_test_shape, NULL};

TEST(arabic_shape_forms_lam_alef)
{
  uint32_t cps[] = {0x0644u, 0x0627u};

  ASSERT_EQ(my_arabic_shape(cps, 2), 1u);
  ASSERT_EQ(cps[0], 0xFEFBu);
}

TEST(text_layout_maps_rtl_visual_order)
{
  const char* text = "(\xD7\x90)";
  my_text_layout_t* layout = my_text_layout_process(NULL, text);

  ASSERT_NOT_NULL(layout);
#ifdef MYUI_BIDI
  ASSERT_TRUE(layout->has_rtl);
  ASSERT_EQ(layout->len, 3u);
  ASSERT_EQ(layout->visual_cps[0], 0x0028u);
  ASSERT_EQ(layout->visual_cps[2], 0x0029u);
  ASSERT_EQ(layout->visual_to_logical[0], 2u);
#else
  ASSERT_EQ(layout->len, 3u);
  ASSERT_EQ(layout->visual_to_logical[0], 0u);
#endif
  my_text_layout_destroy(layout);
}

TEST(text_layout_preserves_lam_alef_logical_boundaries)
{
  const char* text = "\xD9\x84\xD8\xA7";
  my_text_layout_t* layout = my_text_layout_process(NULL, text);

  ASSERT_NOT_NULL(layout);
#ifdef MYUI_BIDI
  my_rectf_t rects[2];
  ASSERT_EQ(layout->logical_len, 2u);
  ASSERT_EQ(layout->len, 1u);
  ASSERT_EQ(layout->visual_cps[0], 0xFEFBu);
  ASSERT_EQ(layout->visual_to_logical[0], 0u);
  ASSERT_EQ(layout->visual_logical_span[0], 2u);
  ASSERT_EQ(layout->logical_to_visual[0], 0u);
  ASSERT_EQ(layout->logical_to_visual[1], 0u);
  ASSERT_EQ(my_text_layout_visual_of_logical(layout, 0), 1u);
  ASSERT_EQ(my_text_layout_visual_of_logical(layout, 1), 0u);
  ASSERT_EQ(my_text_layout_visual_of_logical(layout, 2), 0u);
  ASSERT_EQ(my_text_layout_visual_rects(layout, NULL, 16, 0, 2, rects, 2),
            1u);
  ASSERT_EQ(my_text_layout_visual_rects(layout, NULL, 16, 1, 99, rects, 2),
            1u);
#else
  ASSERT_EQ(layout->logical_len, 2u);
  ASSERT_EQ(layout->len, 2u);
#endif
  my_text_layout_destroy(layout);
}

TEST(line_break_applies_unicode_context_rules)
{
  ASSERT_FALSE(my_line_break_allowed('a', 0x0301u));
  ASSERT_FALSE(my_line_break_allowed('1', '.'));
  ASSERT_FALSE(my_line_break_allowed('.', '2'));
  ASSERT_FALSE(my_line_break_allowed(0x1F1E6u, 0x1F1E7u));
}

TEST(paragraph_preserves_logical_ranges_and_hard_boundaries)
{
  my_text_paragraph_t* paragraph = my_text_paragraph_process(
      NULL, "abc\n\xD7\x90\xD7\x91", NULL, 16, 32);
  const my_text_paragraph_line_t* line;
  ASSERT_NOT_NULL(paragraph);
  ASSERT_EQ(paragraph->line_count, 2u);
  line = my_text_paragraph_line_at(paragraph, 0);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->start_cp, 0u);
  ASSERT_EQ(line->cp_count, 3u);
  line = my_text_paragraph_line_at(paragraph, 1);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->start_cp, 3u);
  ASSERT_EQ(line->cp_count, 2u);
  my_text_paragraph_destroy(paragraph);
}

TEST(paragraph_does_not_break_inside_shaping_cluster)
{
  static const uint8_t bitmap[] = {255};
  paragraph_test_font_t font = {{&s_paragraph_test_vtable}, bitmap};
  my_text_paragraph_t* paragraph = my_text_paragraph_process(
      NULL, "office", (my_font_t*)&font, 16, 4);
  const my_text_paragraph_line_t* line;
  ASSERT_NOT_NULL(paragraph);
  ASSERT_TRUE(paragraph->line_count >= 2u);
  line = my_text_paragraph_line_at(paragraph, 0);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->start_cp, 0u);
  ASSERT_EQ(line->cp_count, 2u);
  line = my_text_paragraph_line_at(paragraph, 1);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->start_cp, 2u);
  ASSERT_TRUE(line->cp_count >= 3u);
  my_text_paragraph_destroy(paragraph);
}

TEST_MAIN_BEGIN()
    RUN_TEST(arabic_shape_forms_lam_alef);
    RUN_TEST(text_layout_maps_rtl_visual_order);
    RUN_TEST(text_layout_preserves_lam_alef_logical_boundaries);
    RUN_TEST(line_break_applies_unicode_context_rules);
    RUN_TEST(paragraph_preserves_logical_ranges_and_hard_boundaries);
    RUN_TEST(paragraph_does_not_break_inside_shaping_cluster);
TEST_MAIN_END()
