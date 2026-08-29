#include "test_framework.h"

#include <stdlib.h>
#include <string.h>

#include "myr/my_arabic_shape.h"
#include "myr/my_line_break.h"
#include "myr/my_text_paragraph.h"
#include "myr/my_text_layout.h"
#include "myr/my_syntax.h"

typedef struct paragraph_test_font_t {
  my_font_t base;
  const uint8_t* bitmap;
  size_t glyph_calls;
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
  test_font->glyph_calls++;
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

TEST(text_layout_reuses_font_boundary_prefix_cache)
{
  static const uint8_t bitmap[] = {255};
  paragraph_test_font_t font = {{&s_paragraph_test_vtable}, bitmap, 0};
  my_text_layout_t* layout =
      my_text_layout_process(NULL, "\xD7\x90\xD7\x91\xD7\x92");
  my_rectf_t rects[2];
  size_t before;

  ASSERT_NOT_NULL(layout);
  before = font.glyph_calls;
  (void)my_text_layout_visual_x(layout, (my_font_t*)&font, 16, 2);
  (void)my_text_layout_logical_at_x(layout, (my_font_t*)&font, 16, 2);
  ASSERT_EQ(my_text_layout_visual_rects(layout, (my_font_t*)&font, 16, 0, 2,
                                        rects, 2), 1u);
  ASSERT_TRUE(font.glyph_calls > before);
  before = font.glyph_calls;
  (void)my_text_layout_visual_x(layout, (my_font_t*)&font, 16, 1);
  (void)my_text_layout_logical_at_x(layout, (my_font_t*)&font, 16, 3);
  (void)my_text_layout_visual_rects(layout, (my_font_t*)&font, 16, 1, 3,
                                    rects, 2);
  ASSERT_EQ(font.glyph_calls, before);
  (void)my_text_layout_visual_x(layout, (my_font_t*)&font, 18, 1);
  ASSERT_TRUE(font.glyph_calls > before);
  my_text_layout_destroy(layout);
}

TEST(text_layout_visual_rects_honors_output_capacity)
{
  uint32_t visual_cps[] = {'a', 'b', 'c', 'd'};
  uint32_t visual_to_logical[] = {0, 2, 1, 3};
  uint32_t visual_span[] = {1, 1, 1, 1};
  uint32_t logical_to_visual[] = {0, 2, 1, 3};
  uint8_t visual_rtl[] = {0, 0, 0, 0};
  my_rectf_t rect;
  my_text_layout_t layout = {
      .visual_cps = visual_cps,
      .visual_to_logical = visual_to_logical,
      .visual_logical_span = visual_span,
      .logical_to_visual = logical_to_visual,
      .visual_rtl = visual_rtl,
      .len = 4,
      .logical_len = 4};

  ASSERT_EQ(my_text_layout_visual_rects(&layout, NULL, 16, 0, 2, &rect, 1),
            1u);
  ASSERT_EQ(rect.x, 0.0f);
  ASSERT_EQ(rect.w, 8.0f);
}

TEST(line_break_applies_unicode_context_rules)
{
  ASSERT_FALSE(my_line_break_allowed('a', 0x0301u));
  ASSERT_FALSE(my_line_break_allowed('1', '.'));
  ASSERT_FALSE(my_line_break_allowed('.', '2'));
  ASSERT_FALSE(my_line_break_allowed(0x1F1E6u, 0x1F1E7u));
}

TEST(line_break_keeps_hebrew_quotes_and_unicode_numbers_together)
{
  ASSERT_FALSE(my_line_break_allowed(0x05D0u, '"'));
  ASSERT_FALSE(my_line_break_allowed('"', 0x05D0u));
  ASSERT_FALSE(my_line_break_allowed(0x0661u, 0x066Bu));
  ASSERT_FALSE(my_line_break_allowed(0x066Bu, 0x0662u));
  ASSERT_FALSE(my_line_break_allowed(0xFF11u, 0xFF0Eu));
  ASSERT_FALSE(my_line_break_allowed(0xFF0Eu, 0xFF12u));
}

TEST(line_break_keeps_unicode_glue_and_joiners_together)
{
  ASSERT_FALSE(my_line_break_allowed('a', 0x00A0u));
  ASSERT_FALSE(my_line_break_allowed(0x00A0u, 'b'));
  ASSERT_FALSE(my_line_break_allowed('a', 0x2060u));
  ASSERT_FALSE(my_line_break_allowed(0x2060u, 'b'));
  ASSERT_FALSE(my_line_break_allowed(0x4E00u, 0x00A0u));
  ASSERT_FALSE(my_line_break_allowed(0x202Fu, 0x4E00u));
  ASSERT_FALSE(my_line_break_allowed('a', 0x200Du));
  ASSERT_FALSE(my_line_break_allowed(0x200Du, 'b'));
}

TEST(line_break_keeps_emoji_extensions_with_base_text)
{
  ASSERT_FALSE(my_line_break_allowed(0x1F600u, 0xFE0Fu));
  ASSERT_FALSE(my_line_break_allowed(0xFE0Fu, 'a'));
  ASSERT_FALSE(my_line_break_allowed(0x1F600u, 0x1F3FBu));
  ASSERT_FALSE(my_line_break_allowed(0x1F3FBu, 'a'));
  ASSERT_FALSE(my_line_break_allowed(0x1F600u, 0xE0061u));
  ASSERT_FALSE(my_line_break_allowed(0xE0061u, 'a'));
}

TEST(syntax_cache_lexes_bounded_tokens_and_comments)
{
  my_syntax_cache_t* cache =
      my_syntax_cache_create(NULL, MY_SYNTAX_C_LIKE);
  const my_syntax_token_t* tokens;
  size_t count = 0;

  ASSERT_NOT_NULL(cache);
  ASSERT_EQ(my_syntax_cache_set_text(cache,
                                     "int value = 42; // note\n"),
            MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_ensure(cache, 1), MY_RET_OK);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 0));
  tokens = my_syntax_cache_line_tokens(cache, 0, &count);
  ASSERT_NOT_NULL(tokens);
  ASSERT_TRUE(count >= 7u);
  ASSERT_EQ(tokens[0].kind, MY_SYNTAX_TOKEN_KEYWORD);
  ASSERT_EQ(tokens[1].kind, MY_SYNTAX_TOKEN_TEXT);
  ASSERT_EQ(tokens[2].kind, MY_SYNTAX_TOKEN_IDENTIFIER);
  ASSERT_EQ(tokens[count - 1].kind, MY_SYNTAX_TOKEN_COMMENT);
  my_syntax_cache_destroy(cache);
}

TEST(syntax_cache_records_utf8_token_byte_ranges)
{
  my_syntax_cache_t* cache =
      my_syntax_cache_create(NULL, MY_SYNTAX_C_LIKE);
  const my_syntax_token_t* tokens;
  size_t count = 0;

  ASSERT_NOT_NULL(cache);
  ASSERT_EQ(my_syntax_cache_set_text(cache, "int \xE4\xB8\xAD\xE6\x96\x87 = 42;\n"),
            MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_ensure(cache, 1), MY_RET_OK);
  tokens = my_syntax_cache_line_tokens(cache, 0, &count);
  ASSERT_NOT_NULL(tokens);
  ASSERT_TRUE(count >= 7u);
  ASSERT_EQ(tokens[0].start_byte, 0u);
  ASSERT_EQ(tokens[0].len_bytes, 3u);
  ASSERT_EQ(tokens[2].start_cp, 4u);
  ASSERT_EQ(tokens[2].len_cp, 2u);
  ASSERT_EQ(tokens[2].start_byte, 4u);
  ASSERT_EQ(tokens[2].len_bytes, 6u);
  ASSERT_EQ(tokens[6].start_byte, 13u);
  ASSERT_EQ(tokens[6].len_bytes, 2u);
  my_syntax_cache_destroy(cache);
}

TEST(syntax_cache_propagates_state_only_from_dirty_suffix)
{
  my_syntax_cache_t* cache =
      my_syntax_cache_create(NULL, MY_SYNTAX_C_LIKE);
  const my_syntax_token_t* tokens;
  size_t count = 0;

  ASSERT_NOT_NULL(cache);
  ASSERT_EQ(my_syntax_cache_set_text(cache, "/* open\ninside\n*/ int x;\n"),
            MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_ensure(cache, 3), MY_RET_OK);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 2));
  tokens = my_syntax_cache_line_tokens(cache, 1, &count);
  ASSERT_NOT_NULL(tokens);
  ASSERT_EQ(tokens[0].kind, MY_SYNTAX_TOKEN_COMMENT);
  ASSERT_EQ(my_syntax_cache_replace_line(cache, 0, "int open;"), MY_RET_OK);
  ASSERT_FALSE(my_syntax_cache_line_ready(cache, 0));
  ASSERT_FALSE(my_syntax_cache_line_ready(cache, 1));
  ASSERT_EQ(my_syntax_cache_ensure(cache, 1), MY_RET_OK);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 0));
  ASSERT_FALSE(my_syntax_cache_line_ready(cache, 1));
  ASSERT_EQ(my_syntax_cache_ensure(cache, 2), MY_RET_OK);
  tokens = my_syntax_cache_line_tokens(cache, 1, &count);
  ASSERT_NOT_NULL(tokens);
  ASSERT_EQ(tokens[0].kind, MY_SYNTAX_TOKEN_IDENTIFIER);
  my_syntax_cache_destroy(cache);
}

TEST(syntax_cache_rejects_source_and_line_budget_overflow)
{
  my_syntax_cache_t* cache =
      my_syntax_cache_create(NULL, MY_SYNTAX_YAML);
  char* line = (char*)malloc(MY_SYNTAX_MAX_LINE_BYTES + 2u);
  size_t i;

  ASSERT_NOT_NULL(cache);
  ASSERT_NOT_NULL(line);
  for (i = 0; i < MY_SYNTAX_MAX_LINE_BYTES + 1u; i++) line[i] = 'a';
  line[MY_SYNTAX_MAX_LINE_BYTES + 1u] = '\0';
  ASSERT_EQ(my_syntax_cache_set_text(cache, line), MY_RET_INVALID_PARAMS);
  free(line);
  my_syntax_cache_destroy(cache);
}

TEST(syntax_cache_replacement_is_transactional)
{
  my_syntax_cache_t* cache =
      my_syntax_cache_create(NULL, MY_SYNTAX_C_LIKE);
  char* line = (char*)malloc(MY_SYNTAX_MAX_LINE_BYTES + 2u);
  size_t i;

  ASSERT_NOT_NULL(cache);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(my_syntax_cache_set_text(cache, "int stable;\n"), MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_ensure(cache, 1), MY_RET_OK);
  for (i = 0; i < MY_SYNTAX_MAX_LINE_BYTES + 1u; i++) line[i] = 'x';
  line[MY_SYNTAX_MAX_LINE_BYTES + 1u] = '\0';
  ASSERT_EQ(my_syntax_cache_set_text(cache, line), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_syntax_cache_line_count(cache), 2u);
  ASSERT_TRUE(my_syntax_cache_line_ready(cache, 0));
  my_syntax_cache_destroy(cache);
  free(line);
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
  paragraph_test_font_t font = {{&s_paragraph_test_vtable}, bitmap, 0};
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
    RUN_TEST(text_layout_reuses_font_boundary_prefix_cache);
    RUN_TEST(text_layout_visual_rects_honors_output_capacity);
    RUN_TEST(line_break_applies_unicode_context_rules);
    RUN_TEST(line_break_keeps_hebrew_quotes_and_unicode_numbers_together);
    RUN_TEST(line_break_keeps_unicode_glue_and_joiners_together);
    RUN_TEST(line_break_keeps_emoji_extensions_with_base_text);
    RUN_TEST(paragraph_preserves_logical_ranges_and_hard_boundaries);
    RUN_TEST(paragraph_does_not_break_inside_shaping_cluster);
    RUN_TEST(syntax_cache_lexes_bounded_tokens_and_comments);
    RUN_TEST(syntax_cache_records_utf8_token_byte_ranges);
    RUN_TEST(syntax_cache_propagates_state_only_from_dirty_suffix);
    RUN_TEST(syntax_cache_rejects_source_and_line_budget_overflow);
    RUN_TEST(syntax_cache_replacement_is_transactional);
TEST_MAIN_END()
