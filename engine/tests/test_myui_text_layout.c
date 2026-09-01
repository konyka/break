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
  size_t shape_calls;
  size_t rtl_shape_calls;
  uint32_t scripts[8];
  size_t script_count;
} paragraph_test_font_t;

static my_ret_t layout_shape_font_shape(my_font_t* font, const char* text,
                                        int32_t size, bool rtl,
                                        const my_allocator_t* allocator,
                                        my_font_shape_result_t* result) {
  const char* p = text;
  size_t count = 0;
  size_t i;
  uint32_t cps[64];
  uint32_t clusters[64];
  (void)font;
  (void)rtl;
  if (text == NULL || size <= 0 || result == NULL) return MY_RET_INVALID_PARAMS;
  while (*p != '\0') {
    const char* next = p;
    if (count >= sizeof(cps) / sizeof(cps[0])) return MY_RET_FAIL;
    clusters[count] = (uint32_t)(p - text);
    cps[count] = my_utf8_next(&next);
    p = next;
    count++;
  }
  result->allocator = allocator;
  result->glyphs = (my_font_shape_glyph_t*)my_mem_calloc(
      allocator, count > 0 ? count : 1, sizeof(*result->glyphs));
  if (result->glyphs == NULL) return MY_RET_OOM;
  result->count = count;
  for (i = 0; i < count; i++) {
    size_t source = rtl ? count - i - 1u : i;
    result->glyphs[i].font = font;
    result->glyphs[i].glyph_id = cps[source];
    result->glyphs[i].cluster = clusters[source];
    result->glyphs[i].advance_x_26_6 = 64;
  }
  result->used_complex_shaping = true;
  return MY_RET_OK;
}

static const my_font_vtable_t s_layout_shape_font_vtable = {
    .shape = layout_shape_font_shape};

static my_ret_t layout_bad_cluster_shape(my_font_t* font, const char* text,
                                         int32_t size, bool rtl,
                                         const my_allocator_t* allocator,
                                         my_font_shape_result_t* result) {
  (void)rtl;
  if (text == NULL || size <= 0 || result == NULL) return MY_RET_INVALID_PARAMS;
  result->allocator = allocator;
  result->glyphs = (my_font_shape_glyph_t*)my_mem_calloc(
      allocator, 1, sizeof(*result->glyphs));
  if (result->glyphs == NULL) return MY_RET_OOM;
  result->count = 1;
  result->glyphs[0].font = font;
  result->glyphs[0].glyph_id = 1;
  result->glyphs[0].cluster = 1;
  result->glyphs[0].advance_x_26_6 = 64;
  return MY_RET_OK;
}

static const my_font_vtable_t s_layout_bad_cluster_vtable = {
    .shape = layout_bad_cluster_shape};

static my_font_t* layout_bad_cluster_test_font(void) {
  static my_font_t font = {&s_layout_bad_cluster_vtable};
  return &font;
}

static my_ret_t layout_ligature_shape(my_font_t* font, const char* text,
                                      int32_t size, bool rtl,
                                      const my_allocator_t* allocator,
                                      my_font_shape_result_t* result) {
  (void)rtl;
  if (font == NULL || text == NULL || size <= 0 || result == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (strcmp(text, "fi") != 0) return MY_RET_FAIL;
  result->allocator = allocator;
  result->glyphs = (my_font_shape_glyph_t*)my_mem_calloc(
      allocator, 1, sizeof(*result->glyphs));
  if (result->glyphs == NULL) return MY_RET_OOM;
  result->count = 1;
  result->glyphs[0].font = font;
  result->glyphs[0].glyph_id = 1;
  result->glyphs[0].cluster = 0;
  result->glyphs[0].advance_x_26_6 = 10 * 64;
  return MY_RET_OK;
}

static const my_font_vtable_t s_layout_ligature_vtable = {
    .shape = layout_ligature_shape};

static my_font_t* layout_ligature_test_font(void) {
  static my_font_t font = {&s_layout_ligature_vtable};
  return &font;
}

static my_font_t* layout_shape_test_font(void) {
  static my_font_t font = {&s_layout_shape_font_vtable};
  return &font;
}

typedef struct text_budget_alloc_state_t {
  size_t calls;
} text_budget_alloc_state_t;

static void* text_budget_alloc(void* context, size_t size) {
  text_budget_alloc_state_t* state = (text_budget_alloc_state_t*)context;
  (void)size;
  state->calls++;
  return NULL;
}

static void* text_budget_calloc(void* context, size_t count, size_t size) {
  text_budget_alloc_state_t* state = (text_budget_alloc_state_t*)context;
  (void)count;
  (void)size;
  state->calls++;
  return NULL;
}

static void* text_budget_realloc(void* context, void* memory, size_t size) {
  text_budget_alloc_state_t* state = (text_budget_alloc_state_t*)context;
  (void)memory;
  (void)size;
  state->calls++;
  return NULL;
}

static void text_budget_free(void* context, void* memory) {
  (void)context;
  (void)memory;
}

typedef struct text_shape_alloc_state_t {
  size_t calls;
  size_t fail_at;
  size_t live;
} text_shape_alloc_state_t;

static bool text_shape_should_fail(text_shape_alloc_state_t* state) {
  state->calls++;
  return state->fail_at != 0 && state->calls == state->fail_at;
}

static void* text_shape_alloc(void* context, size_t size) {
  text_shape_alloc_state_t* state = (text_shape_alloc_state_t*)context;
  void* memory;
  if (text_shape_should_fail(state)) return NULL;
  memory = malloc(size);
  if (memory != NULL) state->live++;
  return memory;
}

static void* text_shape_calloc(void* context, size_t count, size_t size) {
  text_shape_alloc_state_t* state = (text_shape_alloc_state_t*)context;
  void* memory;
  if (text_shape_should_fail(state)) return NULL;
  memory = calloc(count, size);
  if (memory != NULL) state->live++;
  return memory;
}

static void* text_shape_realloc(void* context, void* old_memory,
                                size_t size) {
  text_shape_alloc_state_t* state = (text_shape_alloc_state_t*)context;
  void* memory;
  if (text_shape_should_fail(state)) return NULL;
  memory = realloc(old_memory, size);
  if (memory != NULL && old_memory == NULL) state->live++;
  return memory;
}

static void text_shape_free(void* context, void* memory) {
  text_shape_alloc_state_t* state = (text_shape_alloc_state_t*)context;
  if (memory != NULL) {
    free(memory);
    state->live--;
  }
}

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

static const char* s_paragraph_last_language;
static const char* s_paragraph_last_features;
static size_t s_paragraph_shape_ex_calls;
static size_t s_paragraph_shape_ex_fail_after;
static size_t s_paragraph_segment_bytes[8];

static my_ret_t paragraph_test_shape(my_font_t* font, const char* text,
                                     int32_t size, bool rtl,
                                     const my_allocator_t* allocator,
                                     my_font_shape_result_t* result) {
  paragraph_test_font_t* test_font = (paragraph_test_font_t*)font;
  test_font->shape_calls++;
  if (rtl) test_font->rtl_shape_calls++;
  if (text == NULL || size <= 0 || result == NULL) return MY_RET_INVALID_PARAMS;
  result->allocator = allocator;
  if (strcmp(text, "office") != 0) {
    const char* p = text;
    uint32_t cps[64];
    uint32_t clusters[64];
    size_t count = 0;
    size_t i;
    while (*p != '\0') {
      const char* next = p;
      if (count >= 64u) return MY_RET_FAIL;
      clusters[count] = (uint32_t)(p - text);
      cps[count] = my_utf8_next(&next);
      p = next;
      count++;
    }
    result->glyphs = (my_font_shape_glyph_t*)my_mem_calloc(
        allocator, count > 0 ? count : 1, sizeof(*result->glyphs));
    if (result->glyphs == NULL) return MY_RET_OOM;
    result->count = count;
    for (i = 0; i < count; i++) {
      size_t source = rtl ? count - i - 1u : i;
      result->glyphs[i].font = font;
      result->glyphs[i].glyph_id = cps[source];
      result->glyphs[i].cluster = clusters[source];
      result->glyphs[i].advance_x_26_6 = 64;
    }
    return MY_RET_OK;
  }
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

static my_ret_t paragraph_test_shape_ex(
    my_font_t* font, const char* text, int32_t size,
    const my_font_shape_params_t* params, const my_allocator_t* allocator,
    my_font_shape_result_t* result) {
  paragraph_test_font_t* test_font = (paragraph_test_font_t*)font;
  if (params == NULL || test_font->script_count >= 8u) return MY_RET_FAIL;
  s_paragraph_last_language = params->language;
  s_paragraph_last_features = params->features;
  s_paragraph_shape_ex_calls++;
  s_paragraph_segment_bytes[test_font->script_count] = strlen(text);
  test_font->scripts[test_font->script_count++] = params->script;
  if (s_paragraph_shape_ex_fail_after != 0u &&
      s_paragraph_shape_ex_calls > s_paragraph_shape_ex_fail_after) {
    return MY_RET_FAIL;
  }
  return paragraph_test_shape(font, text, size, params->rtl, allocator, result);
}

static const my_font_vtable_t s_paragraph_test_vtable = {
    paragraph_test_measure, paragraph_test_glyph, paragraph_test_ascent,
    paragraph_test_descent, paragraph_test_line_height, paragraph_test_destroy,
    NULL, paragraph_test_shape, NULL, NULL};

static const my_font_vtable_t s_paragraph_shape_ex_vtable = {
    .shape = paragraph_test_shape,
    .shape_ex = paragraph_test_shape_ex};

static my_ret_t layout_feature_shape_ex(
    my_font_t* font, const char* text, int32_t size,
    const my_font_shape_params_t* params, const my_allocator_t* allocator,
    my_font_shape_result_t* result) {
  paragraph_test_font_t* test_font = (paragraph_test_font_t*)font;
  const char* p = text;
  size_t count = 0;
  size_t i;
  bool wide = params != NULL && params->features != NULL &&
              strcmp(params->features, "wide") == 0;
  uint32_t cps[64];
  uint32_t clusters[64];

  if (font == NULL || text == NULL || size <= 0 || params == NULL ||
      result == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  while (*p != '\0') {
    const char* next = p;
    if (count >= sizeof(cps) / sizeof(cps[0])) return MY_RET_FAIL;
    clusters[count] = (uint32_t)(p - text);
    cps[count] = my_utf8_next(&next);
    p = next;
    count++;
  }
  test_font->shape_calls++;
  result->allocator = allocator;
  result->glyphs = (my_font_shape_glyph_t*)my_mem_calloc(
      allocator, count > 0 ? count : 1, sizeof(*result->glyphs));
  if (result->glyphs == NULL) return MY_RET_OOM;
  result->count = count;
  for (i = 0; i < count; i++) {
    result->glyphs[i].font = font;
    result->glyphs[i].glyph_id = cps[i];
    result->glyphs[i].cluster = clusters[i];
    result->glyphs[i].advance_x_26_6 = wide ? 3 * 64 : 64;
  }
  return MY_RET_OK;
}

static const my_font_vtable_t s_layout_feature_shape_ex_vtable = {
    .shape_ex = layout_feature_shape_ex};

TEST(text_layout_splits_mixed_scripts_for_shape_provider)
{
  paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0, 0, 0,
                                {0}, 0};
  my_text_layout_t* layout;
  my_font_shape_result_t result = {0};

  layout = my_text_layout_process(NULL, "a" "\xE7\x9F\xAD" "b");
  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(my_text_layout_shape(layout, "a" "\xE7\x9F\xAD" "b", (my_font_t*)&font,
                                 16, NULL, &result), MY_RET_OK);
  ASSERT_EQ(font.script_count, 3u);
  ASSERT_EQ(font.scripts[0], MY_FONT_SCRIPT_LATN);
  ASSERT_EQ(font.scripts[1], MY_FONT_SCRIPT_HANI);
  ASSERT_EQ(font.scripts[2], MY_FONT_SCRIPT_LATN);
  ASSERT_EQ(result.count, 3u);
  my_font_shape_destroy(&result);
  my_text_layout_destroy(layout);
}

TEST(text_layout_shape_ex_forwards_language_and_features)
{
  paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0, 0, 0,
                                {0}, 0};
  my_font_shape_params_t params = {false, MY_FONT_SCRIPT_LATN, "en",
                                   "kern=0,liga=1"};
  my_font_shape_result_t result = {0};
  my_text_layout_t* layout = my_text_layout_process(NULL, "ab");

  ASSERT_NOT_NULL(layout);
  s_paragraph_last_language = NULL;
  s_paragraph_last_features = NULL;
  s_paragraph_shape_ex_calls = 0;
  ASSERT_EQ(my_text_layout_shape_ex(layout, "ab", (my_font_t*)&font, 16,
                                    &params, NULL, &result), MY_RET_OK);
  ASSERT_EQ(s_paragraph_shape_ex_calls, 1u);
  ASSERT_TRUE(s_paragraph_last_language != NULL);
  ASSERT_EQ(strcmp(s_paragraph_last_language, "en"), 0);
  ASSERT_TRUE(s_paragraph_last_features != NULL);
  ASSERT_EQ(strcmp(s_paragraph_last_features, "kern=0,liga=1"), 0);
  ASSERT_EQ(result.count, 2u);
  my_font_shape_destroy(&result);
  my_text_layout_destroy(layout);
}

TEST(text_layout_shape_ex_failure_rolls_back_segment_results)
{
  text_shape_alloc_state_t state = {0};
  my_allocator_t allocator = {&state, text_shape_alloc, text_shape_calloc,
                              text_shape_realloc, text_shape_free};
  paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0, 0, 0,
                                {0}, 0};
  my_font_shape_result_t result = {0};
  my_ret_t ret;
  my_text_layout_t* layout =
      my_text_layout_process(NULL, "a" "\xE7\x9F\xAD" "b");

  ASSERT_NOT_NULL(layout);
  s_paragraph_shape_ex_calls = 0;
  s_paragraph_shape_ex_fail_after = 1;
  ret = my_text_layout_shape(layout, "a" "\xE7\x9F\xAD" "b",
                             (my_font_t*)&font, 16, &allocator, &result);
  s_paragraph_shape_ex_fail_after = 0;
  ASSERT_EQ(ret, MY_RET_FAIL);
  ASSERT_TRUE(result.glyphs == NULL);
  ASSERT_EQ(result.count, 0u);
  ASSERT_EQ(state.live, 0u);
  my_text_layout_destroy(layout);
}

TEST(text_layout_keeps_inherited_marks_with_previous_script)
{
  paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0, 0, 0,
                                {0}, 0};
  my_font_shape_result_t result = {0};
  my_text_layout_t* layout =
      my_text_layout_process(NULL, "a" "\xCC\x81" "\xE7\x9F\xAD");

  ASSERT_NOT_NULL(layout);
  memset(s_paragraph_segment_bytes, 0, sizeof(s_paragraph_segment_bytes));
  ASSERT_EQ(my_text_layout_shape(layout, "a" "\xCC\x81" "\xE7\x9F\xAD",
                                 (my_font_t*)&font, 16, NULL, &result),
            MY_RET_OK);
  ASSERT_EQ(font.script_count, 2u);
  ASSERT_EQ(font.scripts[0], MY_FONT_SCRIPT_LATN);
  ASSERT_EQ(font.scripts[1], MY_FONT_SCRIPT_HANI);
  ASSERT_EQ(s_paragraph_segment_bytes[0], 3u);
  ASSERT_EQ(s_paragraph_segment_bytes[1], 3u);
  my_font_shape_destroy(&result);
  my_text_layout_destroy(layout);
}

TEST(text_layout_maps_thai_to_thai_script)
{
  paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0, 0, 0,
                                {0}, 0};
  my_font_shape_result_t result = {0};
  my_text_layout_t* layout = my_text_layout_process(NULL, "\xE0\xB8\x81");

  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(my_text_layout_shape(layout, "\xE0\xB8\x81", (my_font_t*)&font,
                                 16, NULL, &result),
            MY_RET_OK);
  ASSERT_EQ(font.script_count, 1u);
  ASSERT_EQ(font.scripts[0], MY_FONT_SCRIPT_THAI);
  my_font_shape_destroy(&result);
  my_text_layout_destroy(layout);
}

TEST(paragraph_process_ex_forwards_shaping_parameters)
{
  paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0, 0, 0,
                                {0}, 0};
  const my_font_shape_params_t params = {
      false, MY_FONT_SCRIPT_LATN, "en-US", "kern=0,liga=1"};
  my_text_paragraph_t* paragraph;

  s_paragraph_last_language = NULL;
  s_paragraph_last_features = NULL;
  s_paragraph_shape_ex_calls = 0;
  paragraph = my_text_paragraph_process_ex(NULL, "office", (my_font_t*)&font,
                                           16, 0, &params);
  ASSERT_NOT_NULL(paragraph);
  ASSERT_EQ(s_paragraph_shape_ex_calls, 1u);
  ASSERT_STR_EQ(s_paragraph_last_language, "en-US");
  ASSERT_STR_EQ(s_paragraph_last_features, "kern=0,liga=1");
  my_text_paragraph_destroy(paragraph);
}

TEST(paragraph_process_ex_owns_shaping_parameter_strings)
{
  paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0, 0, 0,
                                {0}, 0};
  char language[] = "ar";
  char features[] = "liga=0";
  my_font_shape_params_t params = {true, MY_FONT_SCRIPT_ARAB, language,
                                   features};
  const my_font_shape_params_t* stored;
  my_text_paragraph_t* paragraph = my_text_paragraph_process_ex(
      NULL, "ab", (my_font_t*)&font, 16, 0, &params);

  ASSERT_NOT_NULL(paragraph);
  language[0] = 'x';
  features[0] = 'x';
  stored = my_text_paragraph_shape_params(paragraph);
  ASSERT_NOT_NULL(stored);
  ASSERT_TRUE(stored->language != language);
  ASSERT_TRUE(stored->features != features);
  ASSERT_TRUE(stored->rtl);
  ASSERT_EQ(stored->script, MY_FONT_SCRIPT_ARAB);
  ASSERT_STR_EQ(stored->language, "ar");
  ASSERT_STR_EQ(stored->features, "liga=0");
  ASSERT_TRUE(my_text_paragraph_shape_params(NULL) == NULL);
  my_text_paragraph_destroy(paragraph);
}

TEST(paragraph_process_ex_parameter_copy_is_transactional)
{
  text_shape_alloc_state_t state = {0, 3, 0};
  my_allocator_t allocator = {&state, text_shape_alloc, text_shape_calloc,
                              text_shape_realloc, text_shape_free};
  const my_font_shape_params_t params = {false, MY_FONT_SCRIPT_LATN, "en",
                                         "liga=0"};

  ASSERT_TRUE(my_text_paragraph_process_ex(
                  &allocator, "ab", NULL, 16, 0, &params) == NULL);
  ASSERT_EQ(state.live, 0u);
}

static my_ret_t paragraph_bad_cluster_shape(my_font_t* font, const char* text,
                                            int32_t size, bool rtl,
                                            const my_allocator_t* allocator,
                                            my_font_shape_result_t* result) {
  (void)rtl;
  if (text == NULL || size <= 0 || result == NULL) return MY_RET_INVALID_PARAMS;
  result->allocator = allocator;
  result->glyphs = (my_font_shape_glyph_t*)my_mem_calloc(
      allocator, 1, sizeof(*result->glyphs));
  if (result->glyphs == NULL) return MY_RET_OOM;
  result->count = 1;
  result->glyphs[0].font = font;
  result->glyphs[0].cluster = 1;
  result->glyphs[0].advance_x_26_6 = 64;
  return MY_RET_OK;
}

static const my_font_vtable_t s_paragraph_bad_cluster_vtable = {
    .shape = paragraph_bad_cluster_shape};

TEST(arabic_shape_forms_lam_alef)
{
  uint32_t cps[] = {0x0644u, 0x0627u};

  ASSERT_EQ(my_arabic_shape(cps, 2), 1u);
  ASSERT_EQ(cps[0], 0xFEFBu);
}

TEST(text_layout_bidi_prescan_is_bounded)
{
  const char text[] = "abc\xD7\x90";

  ASSERT_FALSE(my_text_layout_may_need_bidi_n(text, 3));
  ASSERT_TRUE(my_text_layout_may_need_bidi_n(text, sizeof(text) - 1));
  ASSERT_FALSE(my_text_layout_may_need_bidi_n(NULL, 0));
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

TEST(text_layout_shapes_bidi_runs_with_logical_clusters)
{
  const char* text = "A\xD7\x90\xD7\x91" "B";
  my_text_layout_t* layout = my_text_layout_process(NULL, text);
  my_font_shape_result_t shaped = {0};

  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(my_text_layout_shape(layout, text, layout_shape_test_font(), 16,
                                 NULL, &shaped),
            MY_RET_OK);
  ASSERT_EQ(shaped.count, layout->logical_len);
  ASSERT_EQ(shaped.glyphs[0].cluster, 0u);
#ifdef MYUI_BIDI
  ASSERT_EQ(shaped.glyphs[1].cluster, 3u);
  ASSERT_EQ(shaped.glyphs[2].cluster, 1u);
#else
  ASSERT_EQ(shaped.glyphs[1].cluster, 1u);
  ASSERT_EQ(shaped.glyphs[2].cluster, 3u);
#endif
  ASSERT_EQ(shaped.glyphs[3].cluster, 5u);
  my_font_shape_destroy(&shaped);
  my_text_layout_destroy(layout);
}

TEST(text_layout_shape_oom_is_transactional)
{
  text_budget_alloc_state_t state = {0};
  const my_allocator_t allocator = {&state, text_budget_alloc,
                                    text_budget_calloc, text_budget_realloc,
                                    text_budget_free};
  my_text_layout_t* layout =
      my_text_layout_process(NULL, "A\xD7\x90\xD7\x91" "B");
  my_font_shape_result_t shaped = {0};

  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(my_text_layout_shape(layout,
                                 "A\xD7\x90\xD7\x91" "B",
                                 layout_shape_test_font(), 16, &allocator,
                                 &shaped),
            MY_RET_OOM);
  ASSERT_EQ(shaped.count, 0u);
  ASSERT_TRUE(shaped.glyphs == NULL);
  ASSERT_TRUE(state.calls > 0);
  my_text_layout_destroy(layout);
}

TEST(text_layout_shape_rejects_mismatched_source_text)
{
  my_text_layout_t* layout = my_text_layout_process(NULL, "A\xD7\x90");
  my_font_shape_result_t shaped = {0};

  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(my_text_layout_shape(layout, "B\xD7\x90",
                                 layout_shape_test_font(), 16, NULL, &shaped),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(shaped.count, 0u);
  ASSERT_TRUE(shaped.glyphs == NULL);
  my_text_layout_destroy(layout);
}

TEST(text_layout_shape_rejects_non_boundary_cluster)
{
  const char* text = "\xD7\x90";
  my_text_layout_t* layout = my_text_layout_process(NULL, text);
  my_font_shape_result_t shaped = {0};

  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(my_text_layout_shape(layout, text, layout_bad_cluster_test_font(),
                                 16, NULL, &shaped),
            MY_RET_FAIL);
  ASSERT_EQ(shaped.count, 0u);
  ASSERT_TRUE(shaped.glyphs == NULL);
  my_text_layout_destroy(layout);
}

TEST(text_layout_shape_allocation_failures_rollback)
{
  const char* text = "A\xD7\x90\xD7\x91" "B";
  my_text_layout_t* layout = my_text_layout_process(NULL, text);
  size_t fail_at;
  bool succeeded = false;

  ASSERT_NOT_NULL(layout);
  for (fail_at = 1; fail_at <= 32; fail_at++) {
    text_shape_alloc_state_t state = {0, fail_at, 0};
    const my_allocator_t allocator = {&state, text_shape_alloc,
                                      text_shape_calloc, text_shape_realloc,
                                      text_shape_free};
    my_font_shape_result_t shaped = {0};
    my_ret_t ret = my_text_layout_shape(layout, text,
                                        layout_shape_test_font(), 16,
                                        &allocator, &shaped);

    if (ret == MY_RET_OK) {
      succeeded = true;
      my_font_shape_destroy(&shaped);
      ASSERT_EQ(state.live, 0u);
      break;
    }
    ASSERT_EQ(ret, MY_RET_OOM);
    ASSERT_EQ(shaped.count, 0u);
    ASSERT_TRUE(shaped.glyphs == NULL);
    ASSERT_EQ(state.live, 0u);
  }
  ASSERT_TRUE(succeeded);
  my_text_layout_destroy(layout);
}

TEST(text_layout_shape_preserves_lam_alef_clusters)
{
  const char* text = "\xD9\x84\xD8\xA7";
  my_text_layout_t* layout = my_text_layout_process(NULL, text);
  my_font_shape_result_t shaped = {0};

  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(my_text_layout_shape(layout, text, layout_shape_test_font(), 16,
                                 NULL, &shaped),
            MY_RET_OK);
  ASSERT_EQ(shaped.count, 2u);
#ifdef MYUI_BIDI
  ASSERT_EQ(shaped.glyphs[0].cluster, 2u);
  ASSERT_EQ(shaped.glyphs[1].cluster, 0u);
#else
  ASSERT_EQ(shaped.glyphs[0].cluster, 0u);
  ASSERT_EQ(shaped.glyphs[1].cluster, 2u);
#endif
  my_font_shape_destroy(&shaped);
  my_text_layout_destroy(layout);
}

TEST(text_layout_boundaries_use_ligature_advance)
{
  my_text_layout_t* layout = my_text_layout_process(NULL, "fi");
  my_rectf_t rect;

  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(my_text_layout_visual_x(layout, layout_ligature_test_font(), 16, 1),
            10);
  ASSERT_EQ(my_text_layout_visual_x(layout, layout_ligature_test_font(), 16, 2),
            10);
  ASSERT_EQ(my_text_layout_visual_boundary_x(layout, layout_ligature_test_font(),
                                             16, 2),
            10);
  ASSERT_EQ(my_text_layout_logical_at_x(layout, layout_ligature_test_font(),
                                        16, 4),
            0u);
  ASSERT_EQ(my_text_layout_logical_at_x(layout, layout_ligature_test_font(),
                                        16, 6),
            2u);
  ASSERT_EQ(my_text_layout_visual_rects(layout, layout_ligature_test_font(), 16,
                                        1, 2, &rect, 1),
            1u);
  ASSERT_EQ(rect.w, 10.0f);
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
  paragraph_test_font_t font = {{&s_paragraph_test_vtable}, bitmap, 0, 0, 0,
                                {0}, 0};
  my_text_layout_t* layout =
      my_text_layout_process(NULL, "\xD7\x90\xD7\x91\xD7\x92");
  my_rectf_t rects[2];
  size_t before;

  ASSERT_NOT_NULL(layout);
  before = font.shape_calls;
  (void)my_text_layout_visual_x(layout, (my_font_t*)&font, 16, 2);
  (void)my_text_layout_logical_at_x(layout, (my_font_t*)&font, 16, 2);
  ASSERT_EQ(my_text_layout_visual_rects(layout, (my_font_t*)&font, 16, 0, 2,
                                        rects, 2), 1u);
  ASSERT_TRUE(font.shape_calls > before);
  before = font.shape_calls;
  (void)my_text_layout_visual_x(layout, (my_font_t*)&font, 16, 1);
  (void)my_text_layout_logical_at_x(layout, (my_font_t*)&font, 16, 3);
  (void)my_text_layout_visual_rects(layout, (my_font_t*)&font, 16, 1, 3,
                                    rects, 2);
  ASSERT_EQ(font.shape_calls, before);
  (void)my_text_layout_visual_x(layout, (my_font_t*)&font, 18, 1);
  ASSERT_TRUE(font.shape_calls > before);
  my_text_layout_destroy(layout);
}

TEST(text_layout_boundary_cache_keys_shaping_parameters)
{
  paragraph_test_font_t font = {{&s_layout_feature_shape_ex_vtable}, NULL, 0,
                                0, 0, {0}, 0};
  my_font_shape_params_t narrow = {false, MY_FONT_SCRIPT_LATN, NULL, NULL};
  my_font_shape_params_t wide = {false, MY_FONT_SCRIPT_LATN, NULL, "wide"};
  my_text_layout_t* layout = my_text_layout_process(NULL, "ab");

  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(my_text_layout_visual_boundary_x_ex(
                layout, (my_font_t*)&font, 16, 2, &narrow),
            2);
  ASSERT_EQ(my_text_layout_visual_boundary_x_ex(
                layout, (my_font_t*)&font, 16, 2, &wide),
            6);
  ASSERT_EQ(my_text_layout_visual_boundary_x_ex(
                layout, (my_font_t*)&font, 16, 2, &narrow),
            2);
  ASSERT_EQ(font.shape_calls, 3u);
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
  ASSERT_EQ(my_text_layout_visual_boundary_x(&layout, NULL, 16, 3), 24);
  my_mem_free(NULL, layout.visual_boundaries);
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
  paragraph_test_font_t font = {{&s_paragraph_test_vtable}, bitmap, 0, 0, 0,
                                {0}, 0};
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

TEST(paragraph_shapes_bidi_runs_before_wrapping)
{
  static const uint8_t bitmap[] = {255};
  paragraph_test_font_t font = {{&s_paragraph_test_vtable}, bitmap, 0, 0, 0,
                                {0}, 0};
  my_text_paragraph_t* paragraph = my_text_paragraph_process(
      NULL, "A\xD7\x90\xD7\x91" "B", (my_font_t*)&font, 16, 0);

  ASSERT_NOT_NULL(paragraph);
#ifdef MYUI_BIDI
  ASSERT_TRUE(font.shape_calls >= 3u);
  ASSERT_TRUE(font.rtl_shape_calls >= 1u);
#else
  ASSERT_EQ(font.shape_calls, 1u);
  ASSERT_EQ(font.rtl_shape_calls, 0u);
#endif
  my_text_paragraph_destroy(paragraph);
}

TEST(paragraph_rejects_non_boundary_shape_cluster)
{
  my_font_t font = {&s_paragraph_bad_cluster_vtable};

  ASSERT_TRUE(my_text_paragraph_process(NULL, "\xD7\x90", &font, 16, 0) ==
              NULL);
}

TEST(text_layout_and_paragraph_reject_oversized_input_before_allocating)
{
  text_budget_alloc_state_t state = {0};
  my_allocator_t allocator = {&state, text_budget_alloc, text_budget_calloc,
                              text_budget_realloc, text_budget_free};
  size_t layout_len = MY_TEXT_LAYOUT_MAX_BYTES + 1u;
  size_t paragraph_len = MY_TEXT_PARAGRAPH_MAX_BYTES + 1u;
  char* layout_text = (char*)malloc(layout_len + 1u);
  char* paragraph_text = (char*)malloc(paragraph_len + 1u);

  ASSERT_NOT_NULL(layout_text);
  ASSERT_NOT_NULL(paragraph_text);
  memset(layout_text, 'x', layout_len);
  memset(paragraph_text, 'y', paragraph_len);
  layout_text[layout_len] = '\0';
  paragraph_text[paragraph_len] = '\0';
  ASSERT_TRUE(my_text_layout_process(&allocator, layout_text) == NULL);
  ASSERT_EQ(state.calls, 0u);
  ASSERT_TRUE(my_text_paragraph_process(&allocator, paragraph_text, NULL, 16,
                                        0) == NULL);
  ASSERT_EQ(state.calls, 0u);
  free(layout_text);
  free(paragraph_text);
}

TEST_MAIN_BEGIN()
    RUN_TEST(arabic_shape_forms_lam_alef);
    RUN_TEST(text_layout_bidi_prescan_is_bounded);
    RUN_TEST(text_layout_maps_rtl_visual_order);
    RUN_TEST(text_layout_shapes_bidi_runs_with_logical_clusters);
    RUN_TEST(text_layout_splits_mixed_scripts_for_shape_provider);
    RUN_TEST(text_layout_shape_ex_forwards_language_and_features);
    RUN_TEST(text_layout_shape_ex_failure_rolls_back_segment_results);
    RUN_TEST(text_layout_keeps_inherited_marks_with_previous_script);
    RUN_TEST(text_layout_maps_thai_to_thai_script);
    RUN_TEST(paragraph_process_ex_forwards_shaping_parameters);
    RUN_TEST(paragraph_process_ex_owns_shaping_parameter_strings);
    RUN_TEST(paragraph_process_ex_parameter_copy_is_transactional);
    RUN_TEST(text_layout_shape_oom_is_transactional);
    RUN_TEST(text_layout_shape_rejects_mismatched_source_text);
    RUN_TEST(text_layout_shape_rejects_non_boundary_cluster);
    RUN_TEST(text_layout_shape_allocation_failures_rollback);
    RUN_TEST(text_layout_shape_preserves_lam_alef_clusters);
    RUN_TEST(text_layout_boundaries_use_ligature_advance);
    RUN_TEST(text_layout_preserves_lam_alef_logical_boundaries);
    RUN_TEST(text_layout_reuses_font_boundary_prefix_cache);
    RUN_TEST(text_layout_boundary_cache_keys_shaping_parameters);
    RUN_TEST(text_layout_visual_rects_honors_output_capacity);
    RUN_TEST(line_break_applies_unicode_context_rules);
    RUN_TEST(line_break_keeps_hebrew_quotes_and_unicode_numbers_together);
    RUN_TEST(line_break_keeps_unicode_glue_and_joiners_together);
    RUN_TEST(line_break_keeps_emoji_extensions_with_base_text);
    RUN_TEST(paragraph_preserves_logical_ranges_and_hard_boundaries);
    RUN_TEST(paragraph_does_not_break_inside_shaping_cluster);
    RUN_TEST(paragraph_shapes_bidi_runs_before_wrapping);
    RUN_TEST(paragraph_rejects_non_boundary_shape_cluster);
    RUN_TEST(text_layout_and_paragraph_reject_oversized_input_before_allocating);
    RUN_TEST(syntax_cache_lexes_bounded_tokens_and_comments);
    RUN_TEST(syntax_cache_records_utf8_token_byte_ranges);
    RUN_TEST(syntax_cache_propagates_state_only_from_dirty_suffix);
    RUN_TEST(syntax_cache_rejects_source_and_line_budget_overflow);
    RUN_TEST(syntax_cache_replacement_is_transactional);
TEST_MAIN_END()
