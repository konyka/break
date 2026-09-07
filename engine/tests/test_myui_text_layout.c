#include "test_framework.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myr/my_arabic_shape.h"
#include "myr/my_line_break.h"
#include "myr/generated/my_combining_marks_data.h"
#include "myr/my_line_break_data.h"
#include "myr/my_text_paragraph.h"
#include "myr/my_text_layout.h"
#include "myr/my_font_ft.h"
#include "myr/my_syntax.h"
#include "myc/my_str.h"

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
static char s_paragraph_last_features_storage[MY_FONT_SHAPE_MAX_FEATURE_BYTES +
                                              1u];
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
  if (params->features != NULL) {
    strncpy(s_paragraph_last_features_storage, params->features,
            sizeof(s_paragraph_last_features_storage) - 1u);
    s_paragraph_last_features_storage[
        sizeof(s_paragraph_last_features_storage) - 1u] = '\0';
    s_paragraph_last_features = s_paragraph_last_features_storage;
  } else {
    s_paragraph_last_features = NULL;
  }
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
    NULL, paragraph_test_shape, NULL, NULL, NULL, NULL};

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
              strcmp(params->features, "wide=1") == 0;
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

TEST(text_layout_shape_reuses_bounded_glyph_cache)
{
  paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0, 0, 0,
                                {0}, 0};
  my_font_shape_result_t first = {0};
  my_font_shape_result_t second = {0};
  my_text_layout_t* layout = my_text_layout_process(NULL, "ab");

  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(my_text_layout_shape_ex(layout, "ab", (my_font_t*)&font, 16,
                                    NULL, NULL, &first), MY_RET_OK);
  ASSERT_EQ(font.shape_calls, 1u);
  ASSERT_EQ(first.count, 2u);
  ASSERT_EQ(my_text_layout_shape_ex(layout, "ab", (my_font_t*)&font, 16,
                                    NULL, NULL, &second), MY_RET_OK);
  ASSERT_EQ(font.shape_calls, 1u);
  ASSERT_EQ(second.count, first.count);
  ASSERT_EQ(second.glyphs[0].glyph_id, first.glyphs[0].glyph_id);
  ASSERT_EQ(second.glyphs[1].glyph_id, first.glyphs[1].glyph_id);
  ASSERT_EQ(second.rtl, first.rtl);
  my_font_shape_destroy(&first);
  my_font_shape_destroy(&second);
  my_text_layout_destroy(layout);
}

TEST(text_layout_shape_cache_isolated_by_shaping_parameters)
{
  paragraph_test_font_t font = {{&s_layout_feature_shape_ex_vtable}, NULL, 0,
                                0, 0, {0}, 0};
  my_font_shape_params_t wide = {false, MY_FONT_SCRIPT_LATN, NULL, "wide=1"};
  my_font_shape_params_t narrow = {false, MY_FONT_SCRIPT_LATN, NULL,
                                   "wide=0"};
  my_font_shape_result_t result = {0};
  my_text_layout_t* layout = my_text_layout_process(NULL, "ab");

  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(my_text_layout_shape_ex(layout, "ab", (my_font_t*)&font, 16,
                                    &wide, NULL, &result), MY_RET_OK);
  ASSERT_EQ(font.shape_calls, 1u);
  my_font_shape_destroy(&result);
  ASSERT_EQ(my_text_layout_shape_ex(layout, "ab", (my_font_t*)&font, 16,
                                    &narrow, NULL, &result), MY_RET_OK);
  ASSERT_EQ(font.shape_calls, 2u);
  ASSERT_EQ(result.glyphs[0].advance_x_26_6, 64);
  my_font_shape_destroy(&result);
  ASSERT_EQ(my_text_layout_shape_ex(layout, "ab", (my_font_t*)&font, 16,
                                    &wide, NULL, &result), MY_RET_OK);
  ASSERT_EQ(font.shape_calls, 2u);
  ASSERT_EQ(result.glyphs[0].advance_x_26_6, 3 * 64);
  my_font_shape_destroy(&result);
  my_text_layout_destroy(layout);
}

TEST(text_layout_shape_cache_normalizes_language_tag_case)
{
  paragraph_test_font_t font = {{&s_layout_feature_shape_ex_vtable}, NULL, 0,
                                0, 0, {0}, 0};
  my_font_shape_params_t params = {false, MY_FONT_SCRIPT_LATN, "ZH-CN", NULL};
  my_font_shape_result_t result = {0};
  my_text_layout_t* layout = my_text_layout_process(NULL, "ab");

  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(my_text_layout_shape_ex(layout, "ab", (my_font_t*)&font, 16,
                                    &params, NULL, &result), MY_RET_OK);
  my_font_shape_destroy(&result);
  params.language = "zh-cn";
  ASSERT_EQ(my_text_layout_shape_ex(layout, "ab", (my_font_t*)&font, 16,
                                    &params, NULL, &result), MY_RET_OK);
  ASSERT_EQ(font.shape_calls, 1u);
  my_font_shape_destroy(&result);
  my_text_layout_destroy(layout);
}

TEST(text_layout_shape_cache_evicts_oldest_entry)
{
  paragraph_test_font_t font = {{&s_layout_feature_shape_ex_vtable}, NULL, 0,
                                0, 0, {0}, 0};
  const char* features[] = {"wide=0", "wide=1", "wide=2", "wide=3",
                            "wide=4"};
  my_font_shape_params_t params = {false, MY_FONT_SCRIPT_LATN, NULL, NULL};
  my_font_shape_result_t result = {0};
  my_text_layout_t* layout = my_text_layout_process(NULL, "ab");
  size_t i;

  ASSERT_NOT_NULL(layout);
  for (i = 0; i < 4u; i++) {
    params.features = features[i];
    ASSERT_EQ(my_text_layout_shape_ex(layout, "ab", (my_font_t*)&font, 16,
                                      &params, NULL, &result), MY_RET_OK);
    my_font_shape_destroy(&result);
  }
  params.features = features[0];
  ASSERT_EQ(my_text_layout_shape_ex(layout, "ab", (my_font_t*)&font, 16,
                                    &params, NULL, &result), MY_RET_OK);
  my_font_shape_destroy(&result);
  ASSERT_EQ(font.shape_calls, 4u);
  params.features = features[4];
  ASSERT_EQ(my_text_layout_shape_ex(layout, "ab", (my_font_t*)&font, 16,
                                    &params, NULL, &result), MY_RET_OK);
  my_font_shape_destroy(&result);
  ASSERT_EQ(font.shape_calls, 5u);
  params.features = features[1];
  ASSERT_EQ(my_text_layout_shape_ex(layout, "ab", (my_font_t*)&font, 16,
                                    &params, NULL, &result), MY_RET_OK);
  my_font_shape_destroy(&result);
  ASSERT_EQ(font.shape_calls, 6u);
  my_text_layout_destroy(layout);
}

TEST(text_layout_shape_cache_write_failure_keeps_result)
{
  text_shape_alloc_state_t state = {0};
  my_allocator_t allocator = {&state, text_shape_alloc, text_shape_calloc,
                              text_shape_realloc, text_shape_free};
  paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0, 0, 0,
                                {0}, 0};
  my_font_shape_result_t result = {0};
  my_text_layout_t* layout = my_text_layout_process(&allocator, "ab");

  ASSERT_NOT_NULL(layout);
  state.fail_at = state.calls + 1u;
  ASSERT_EQ(my_text_layout_shape_ex(layout, "ab", (my_font_t*)&font, 16,
                                    NULL, NULL, &result), MY_RET_OK);
  ASSERT_EQ(result.count, 2u);
  ASSERT_EQ(font.shape_calls, 1u);
  my_font_shape_destroy(&result);
  ASSERT_EQ(my_text_layout_shape_ex(layout, "ab", (my_font_t*)&font, 16,
                                    NULL, NULL, &result), MY_RET_OK);
  ASSERT_EQ(result.count, 2u);
  ASSERT_EQ(font.shape_calls, 2u);
  my_font_shape_destroy(&result);
  my_text_layout_destroy(layout);
  ASSERT_EQ(state.live, 0u);
}

TEST(text_layout_shape_cache_hit_only_allocates_output)
{
  text_shape_alloc_state_t state = {0};
  my_allocator_t allocator = {&state, text_shape_alloc, text_shape_calloc,
                              text_shape_realloc, text_shape_free};
  paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0, 0, 0,
                                {0}, 0};
  my_font_shape_result_t result = {0};
  my_text_layout_t* layout = my_text_layout_process(NULL, "ab");

  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(my_text_layout_shape_ex(layout, "ab", (my_font_t*)&font, 16,
                                    NULL, NULL, &result), MY_RET_OK);
  my_font_shape_destroy(&result);
  state.calls = 0u;
  state.fail_at = 2u;
  ASSERT_EQ(my_text_layout_shape_ex(layout, "ab", (my_font_t*)&font, 16,
                                    NULL, &allocator, &result), MY_RET_OK);
  ASSERT_EQ(state.calls, 1u);
  ASSERT_EQ(result.count, 2u);
  my_font_shape_destroy(&result);
  ASSERT_EQ(state.live, 0u);
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

TEST(text_layout_maps_additional_unicode_scripts)
{
  static const struct {
    const char* text;
    uint32_t script;
  } cases[] = {
      {"\xD4\xB1", MY_FONT_SCRIPT_ARMN},
      {"\xE1\x82\xA0", MY_FONT_SCRIPT_GEOR},
      {"\xE1\x88\x80", MY_FONT_SCRIPT_ETHI},
      {"\xE1\x80\x80", MY_FONT_SCRIPT_MYMR},
      {"\xE1\x9E\x80", MY_FONT_SCRIPT_KHMR},
      {"\xE0\xBA\x81", MY_FONT_SCRIPT_LAOO},
      {"\xE0\xAE\x85", MY_FONT_SCRIPT_TAML},
      {"\xE0\xB0\x80", MY_FONT_SCRIPT_TELU},
      {"\xE0\xB2\x80", MY_FONT_SCRIPT_KNDA},
      {"\xE0\xB4\x80", MY_FONT_SCRIPT_MLYM},
      {"\xE3\x81\x82", MY_FONT_SCRIPT_HIRA},
      {"\xE3\x82\xA2", MY_FONT_SCRIPT_KANA},
      {"\xEF\xBD\xB1", MY_FONT_SCRIPT_KANA},
  };
  size_t i;

  for (i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i) {
    paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0,
                                  0, 0, {0}, 0};
    my_font_shape_result_t result = {0};
    my_text_layout_t* layout = my_text_layout_process(NULL, cases[i].text);

    ASSERT_NOT_NULL(layout);
    ASSERT_EQ(my_text_layout_shape(layout, cases[i].text, (my_font_t*)&font,
                                   16, NULL, &result),
              MY_RET_OK);
    ASSERT_EQ(font.script_count, 1u);
    ASSERT_EQ(font.scripts[0], cases[i].script);
    my_font_shape_destroy(&result);
    my_text_layout_destroy(layout);
  }
}

TEST(text_layout_keeps_arabic_common_punctuation_with_neighbor_script)
{
  const char text[] = "a\xD8\x8C" "b";
  paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0, 0, 0,
                                {0}, 0};
  my_font_shape_result_t result = {0};
  my_text_layout_t* layout = my_text_layout_process(NULL, text);

  ASSERT_NOT_NULL(layout);
  ASSERT_FALSE(my_text_layout_may_need_bidi_n(text, sizeof(text) - 1));
  ASSERT_EQ(my_text_layout_shape(layout, text, (my_font_t*)&font, 16, NULL,
                                 &result),
            MY_RET_OK);
  ASSERT_EQ(font.script_count, 1u);
  ASSERT_EQ(font.scripts[0], MY_FONT_SCRIPT_LATN);
  ASSERT_EQ(result.count, 3u);
  my_font_shape_destroy(&result);
  my_text_layout_destroy(layout);
}

TEST(text_layout_maps_script_supplementary_blocks)
{
  static const struct {
    const char* text;
    uint32_t script;
  } cases[] = {
      {"\xE1\xBC\x80", MY_FONT_SCRIPT_GREK},
      {"\xEF\xAC\x93", MY_FONT_SCRIPT_ARMN},
      {"\xE1\xB2\x90", MY_FONT_SCRIPT_GEOR},
      {"\xE2\xB4\x80", MY_FONT_SCRIPT_GEOR},
      {"\xE2\xB6\x80", MY_FONT_SCRIPT_ETHI},
      {"\xEA\xA9\xA0", MY_FONT_SCRIPT_MYMR},
      {"\xE1\xA7\xA0", MY_FONT_SCRIPT_KHMR},
  };
  size_t i;

  for (i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i) {
    paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0,
                                  0, 0, {0}, 0};
    my_font_shape_result_t result = {0};
    my_text_layout_t* layout = my_text_layout_process(NULL, cases[i].text);

    ASSERT_NOT_NULL(layout);
    ASSERT_EQ(my_text_layout_shape(layout, cases[i].text, (my_font_t*)&font,
                                   16, NULL, &result),
              MY_RET_OK);
    ASSERT_EQ(font.script_count, 1u);
    ASSERT_EQ(font.scripts[0], cases[i].script);
    my_font_shape_destroy(&result);
    my_text_layout_destroy(layout);
  }
}

TEST(text_layout_uses_full_unicode_script_data_when_bidi_enabled)
{
  const char text[] = "\xE0\xAA\x95";
  paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0, 0, 0,
                                {0}, 0};
  my_font_shape_result_t result = {0};
  my_text_layout_t* layout = my_text_layout_process(NULL, text);
  const uint32_t expected_script =
#ifdef MYUI_BIDI
      MY_FONT_SCRIPT_TAG('G', 'u', 'j', 'r');
#else
      0u;
#endif

  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(my_text_layout_shape(layout, text, (my_font_t*)&font, 16, NULL,
                                 &result),
            MY_RET_OK);
  ASSERT_EQ(font.script_count, 1u);
  ASSERT_EQ(font.scripts[0], expected_script);
  my_font_shape_destroy(&result);
  my_text_layout_destroy(layout);
}

TEST(text_layout_keeps_katakana_prolonged_mark_in_one_run)
{
  const char text[] = "\xE3\x82\xA2\xEF\xBD\xB0\xE3\x82\xAB";
  paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0, 0, 0,
                                {0}, 0};
  my_font_shape_result_t result = {0};
  my_text_layout_t* layout = my_text_layout_process(NULL, text);

  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(my_text_layout_shape(layout, text, (my_font_t*)&font, 16, NULL,
                                 &result),
            MY_RET_OK);
  ASSERT_EQ(font.script_count, 1u);
  ASSERT_EQ(font.scripts[0], MY_FONT_SCRIPT_KANA);
  ASSERT_EQ(result.count, 3u);
  my_font_shape_destroy(&result);
  my_text_layout_destroy(layout);
}

TEST(text_layout_resolves_script_extensions_from_neighbors)
{
  const char text[] = "a\xE3\x83\xBB\xE7\x9F\xAD";
  paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0, 0, 0,
                                {0}, 0};
  my_font_shape_result_t result = {0};
  my_text_layout_t* layout = my_text_layout_process(NULL, text);

  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(my_text_layout_shape(layout, text, (my_font_t*)&font, 16, NULL,
                                 &result),
            MY_RET_OK);
  ASSERT_EQ(font.script_count, 2u);
  ASSERT_EQ(font.scripts[0], MY_FONT_SCRIPT_LATN);
  ASSERT_EQ(font.scripts[1], MY_FONT_SCRIPT_HANI);
  ASSERT_EQ(s_paragraph_segment_bytes[0], 1u);
  ASSERT_EQ(s_paragraph_segment_bytes[1], 6u);
  my_font_shape_destroy(&result);
  my_text_layout_destroy(layout);
}

TEST(text_layout_keeps_variation_selector_with_neighbor_script)
{
  const char text[] = "a\xEF\xB8\x8F" "b";
  const char supplementary_text[] = "a\xF3\xA0\x84\x80" "b";
  paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0, 0, 0,
                                {0}, 0};
  my_font_shape_result_t result = {0};
  my_text_layout_t* layout = my_text_layout_process(NULL, text);

  ASSERT_NOT_NULL(layout);
  ASSERT_FALSE(my_text_layout_may_need_bidi_n(text, sizeof(text) - 1));
  ASSERT_EQ(my_text_layout_shape(layout, text, (my_font_t*)&font, 16, NULL,
                                 &result),
            MY_RET_OK);
  ASSERT_EQ(font.script_count, 1u);
  ASSERT_EQ(font.scripts[0], MY_FONT_SCRIPT_LATN);
  ASSERT_EQ(result.count, 3u);
  my_font_shape_destroy(&result);
  my_text_layout_destroy(layout);

  font.script_count = 0;
  result = (my_font_shape_result_t){0};
  layout = my_text_layout_process(NULL, supplementary_text);
  ASSERT_NOT_NULL(layout);
  ASSERT_FALSE(my_text_layout_may_need_bidi_n(
      supplementary_text, sizeof(supplementary_text) - 1));
  ASSERT_EQ(my_text_layout_shape(layout, supplementary_text, (my_font_t*)&font,
                                 16, NULL, &result),
            MY_RET_OK);
  ASSERT_EQ(font.script_count, 1u);
  ASSERT_EQ(font.scripts[0], MY_FONT_SCRIPT_LATN);
  ASSERT_EQ(result.count, 3u);
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

TEST(paragraph_destroy_releases_owned_shaping_parameters_once)
{
  text_shape_alloc_state_t state = {0, 0, 0};
  my_allocator_t allocator = {&state, text_shape_alloc, text_shape_calloc,
                              text_shape_realloc, text_shape_free};
  const my_font_shape_params_t params = {false, MY_FONT_SCRIPT_LATN, "en",
                                         "liga=0"};
  my_text_paragraph_t* paragraph = my_text_paragraph_process_ex(
      &allocator, "ab", NULL, 16, 0, &params);

  ASSERT_NOT_NULL(paragraph);
  my_text_paragraph_destroy(paragraph);
  ASSERT_EQ(state.live, 0u);
}

TEST(paragraph_line_layout_lazily_caches_visual_mapping)
{
  my_font_t* font = my_font_bitmap_create(NULL);
  my_text_paragraph_t* paragraph;
  const my_text_layout_t* first;
  const my_text_layout_t* second;

  ASSERT_NOT_NULL(font);
  paragraph = my_text_paragraph_process(NULL, "(\xD7\x90\xD7\x91)", font,
                                         16, 0);
  ASSERT_NOT_NULL(paragraph);
  first = my_text_paragraph_line_layout(paragraph, 0u);
  ASSERT_NOT_NULL(first);
  second = my_text_paragraph_line_layout(paragraph, 0u);
  ASSERT_TRUE(first == second);
  ASSERT_EQ(first->logical_len, 4u);
  ASSERT_EQ(first->len, 4u);
#ifdef MYUI_BIDI
  ASSERT_EQ(first->visual_to_logical[0], 3u);
  ASSERT_EQ(first->visual_to_logical[3], 0u);
#else
  ASSERT_EQ(first->visual_to_logical[0], 0u);
  ASSERT_EQ(first->visual_to_logical[3], 3u);
#endif
  my_text_paragraph_destroy(paragraph);
  my_font_destroy(font);
}

TEST(paragraph_line_layout_cache_isolated_and_retriable_after_oom)
{
  text_shape_alloc_state_t state = {0};
  const my_allocator_t allocator = {&state, text_shape_alloc,
                                    text_shape_calloc, text_shape_realloc,
                                    text_shape_free};
  my_font_t* font = my_font_bitmap_create(NULL);
  my_text_paragraph_t* paragraph;
  const my_text_layout_t* first;
  const my_text_layout_t* second;

  ASSERT_NOT_NULL(font);
  paragraph = my_text_paragraph_process(&allocator, "ab\ncd", font, 16, 0);
  ASSERT_NOT_NULL(paragraph);
  state.fail_at = state.calls + 1u;
  ASSERT_TRUE(my_text_paragraph_line_layout(paragraph, 0u) == NULL);
  state.fail_at = 0u;
  first = my_text_paragraph_line_layout(paragraph, 0u);
  second = my_text_paragraph_line_layout(paragraph, 1u);
  ASSERT_NOT_NULL(first);
  ASSERT_NOT_NULL(second);
  ASSERT_TRUE(first != second);
  ASSERT_EQ(first->logical_len, 2u);
  ASSERT_EQ(second->logical_len, 2u);
  ASSERT_TRUE(my_text_paragraph_line_layout(paragraph, 0u) == first);
  ASSERT_TRUE(my_text_paragraph_line_layout(paragraph, 2u) == NULL);
  my_text_paragraph_destroy(paragraph);
  my_font_destroy(font);
  ASSERT_EQ(state.live, 0u);
}

TEST(paragraph_line_layout_rejects_corrupt_line_range)
{
  my_text_paragraph_t* paragraph =
      my_text_paragraph_process(NULL, "abc", NULL, 16, 0);

  ASSERT_NOT_NULL(paragraph);
  paragraph->lines[0].start_byte = SIZE_MAX;
  ASSERT_TRUE(my_text_paragraph_line_layout(paragraph, 0u) == NULL);
  my_text_paragraph_destroy(paragraph);
}

TEST(paragraph_line_layout_cache_is_bounded_and_lru)
{
  my_font_t* font = my_font_bitmap_create(NULL);
  my_text_paragraph_t* paragraph;
  const my_text_layout_t* first;
  const my_text_layout_t* replacement;
  bool found;
  size_t index;

  ASSERT_NOT_NULL(font);
  paragraph = my_text_paragraph_process(
      NULL, "a\nb\nc\nd\ne\nf\ng\nh", font, 16, 0);
  ASSERT_NOT_NULL(paragraph);
  first = my_text_paragraph_line_layout(paragraph, 0u);
  ASSERT_NOT_NULL(first);
  ASSERT_EQ(sizeof(paragraph->line_layout_cache) /
                sizeof(paragraph->line_layout_cache[0]),
            MY_TEXT_PARAGRAPH_LINE_LAYOUT_CACHE_CAPACITY);
  for (index = 1u; index < MY_TEXT_PARAGRAPH_LINE_LAYOUT_CACHE_CAPACITY + 1u;
       index++) {
    ASSERT_NOT_NULL(my_text_paragraph_line_layout(paragraph, index));
  }
  found = false;
  for (index = 0u; index < MY_TEXT_PARAGRAPH_LINE_LAYOUT_CACHE_CAPACITY;
       index++) {
    if (paragraph->line_layout_cache[index].layout != NULL &&
        paragraph->line_layout_cache[index].line_index == 0u) {
      found = true;
    }
  }
  ASSERT_FALSE(found);
  replacement = my_text_paragraph_line_layout(paragraph, 0u);
  ASSERT_NOT_NULL(replacement);
  found = false;
  for (index = 0u; index < MY_TEXT_PARAGRAPH_LINE_LAYOUT_CACHE_CAPACITY;
       index++) {
    if (paragraph->line_layout_cache[index].layout == replacement &&
        paragraph->line_layout_cache[index].line_index == 0u) {
      found = true;
    }
  }
  ASSERT_TRUE(found);
  my_text_paragraph_destroy(paragraph);
  my_font_destroy(font);
}

TEST(paragraph_line_mapping_uses_global_logical_boundaries)
{
  my_font_t* font = my_font_bitmap_create(NULL);
  my_text_paragraph_t* paragraph;
  const my_text_paragraph_line_t* line;
  const my_text_layout_t* layout;
  size_t visual;

  ASSERT_NOT_NULL(font);
  paragraph = my_text_paragraph_process(NULL, "ab\n(\xD7\x90\xD7\x91)", font,
                                         16, 0);
  ASSERT_NOT_NULL(paragraph);
  line = my_text_paragraph_line_at(paragraph, 1u);
  layout = my_text_paragraph_line_layout(paragraph, 1u);
  ASSERT_NOT_NULL(line);
  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(line->start_cp, 2u);
  ASSERT_EQ(line->cp_count, layout->logical_len);
  for (visual = 0u; visual <= layout->len; visual++) {
    size_t global = my_text_paragraph_line_logical_at_visual(
        paragraph, 1u, visual);
    ASSERT_TRUE(global >= line->start_cp);
    ASSERT_TRUE(global <= line->start_cp + line->cp_count);
    ASSERT_EQ(global - line->start_cp,
              my_text_layout_logical_at_visual(layout, visual));
  }
  ASSERT_EQ(my_text_paragraph_line_visual_of_logical(
                paragraph, 1u, line->start_cp),
            my_text_layout_visual_of_logical(layout, 0u));
  ASSERT_EQ(my_text_paragraph_line_visual_of_logical(
                paragraph, 1u, line->start_cp + line->cp_count),
            my_text_layout_visual_of_logical(layout, layout->logical_len));
  my_text_paragraph_destroy(paragraph);
  my_font_destroy(font);
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

TEST(text_layout_bidi_prescan_does_not_read_past_slice)
{
  const unsigned char truncated[] = {0xD7u};
  const unsigned char complete[] = {0xD7u, 0x90u};

  ASSERT_FALSE(my_text_layout_may_need_bidi_n((const char*)truncated, 1u));
  ASSERT_TRUE(my_text_layout_may_need_bidi_n((const char*)complete, 2u));
}

TEST(text_layout_process_n_uses_exact_utf8_slice)
{
  const char text[] = "ab\xD7\x90" "cd";
  my_text_layout_t* layout;

  layout = my_text_layout_process_n(NULL, text + 2u, 2u);
  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(layout->logical_len, 1u);
  ASSERT_EQ(layout->visual_cps[0], 0x05D0u);
  my_text_layout_destroy(layout);
  layout = my_text_layout_process_n(NULL, text + 1u, 2u);
  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(layout->logical_len, 2u);
  ASSERT_EQ(layout->visual_cps[1], 0xFFFDu);
  my_text_layout_destroy(layout);
}

TEST(string_utf8_length_validates_scalar_sequences)
{
  const char valid_two[] = "\xC2\xA2";
  const char valid_three[] = "\xE2\x82\xAC";
  const char valid_four[] = "\xF0\x9F\x98\x80";
  const char overlong[] = "\xC0\x80";
  const char surrogate[] = "\xED\xA0\x80";
  const char truncated[] = "\xE2\x82";

  ASSERT_EQ(my_str_utf8_char_len(valid_two), 2u);
  ASSERT_EQ(my_str_utf8_char_len(valid_three), 3u);
  ASSERT_EQ(my_str_utf8_char_len(valid_four), 4u);
  ASSERT_EQ(my_str_utf8_char_len(overlong), 1u);
  ASSERT_EQ(my_str_utf8_char_len(surrogate), 1u);
  ASSERT_EQ(my_str_utf8_char_len(truncated), 1u);
  ASSERT_EQ(my_str_utf8_strlen(overlong), 2u);
  ASSERT_EQ(my_str_utf8_strlen(truncated), 2u);
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
  my_font_shape_params_t wide = {false, MY_FONT_SCRIPT_LATN, NULL, "wide=1"};
  my_font_shape_params_t wide_alias = {false, MY_FONT_SCRIPT_LATN, NULL,
                                       "+wide"};
  my_text_layout_t* layout = my_text_layout_process(NULL, "ab");

  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(my_text_layout_visual_boundary_x_ex(
                layout, (my_font_t*)&font, 16, 2, &narrow),
            2);
  ASSERT_EQ(my_text_layout_visual_boundary_x_ex(
                layout, (my_font_t*)&font, 16, 2, &wide),
            6);
  ASSERT_EQ(my_text_layout_visual_boundary_x_ex(
                layout, (my_font_t*)&font, 16, 2, &wide_alias),
            6);
  ASSERT_EQ(my_text_layout_visual_boundary_x_ex(
                layout, (my_font_t*)&font, 16, 2, &narrow),
            2);
  ASSERT_EQ(font.shape_calls, 2u);
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

TEST(line_break_combining_data_uses_pinned_unicode_version)
{
  ASSERT_EQ(strcmp(MY_COMBINING_MARKS_UCD_VERSION, "17.0.0"), 0);
  ASSERT_EQ(strcmp(MY_LINE_BREAK_UCD_VERSION, "17.0.0"), 0);
  ASSERT_FALSE(my_line_break_allowed(0x4E00u, 0x1AB0u));
}

TEST(line_break_uses_unicode17_new_letter_classes)
{
  ASSERT_EQ(my_line_break_class(0x11F04u), MY_LB_AK);
  ASSERT_EQ(my_line_break_class(0x11F05u), MY_LB_AK);
  ASSERT_TRUE(my_line_break_allowed(0x11F04u, 0x11F05u));
  ASSERT_EQ(my_line_break_class(0x11F43u), MY_LB_BA);
}

TEST(line_break_preserves_unicode_cm_class)
{
  my_line_break_state_t state;

  ASSERT_EQ(my_line_break_class(0x0000u), MY_LB_CM);
  ASSERT_FALSE(my_line_break_allowed(0x1B05u, 0x0000u));
  ASSERT_FALSE(my_line_break_allowed(0x0000u, 0x1B05u));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x000Bu));
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x0308u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x2757u));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '"'));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x2757u));
}

TEST(line_break_preserves_unicode_gl_class)
{
  ASSERT_EQ(my_line_break_class(0x16FE4u), MY_LB_GL);
  ASSERT_FALSE(my_line_break_allowed(0x1B05u, 0x16FE4u));
  ASSERT_FALSE(my_line_break_allowed(0x16FE4u, 0x1B05u));
  ASSERT_TRUE(my_line_break_allowed(0x05BEu, 0x16FE4u));
  ASSERT_TRUE(my_line_break_allowed(0x00ADu, 0x16FE4u));
  ASSERT_TRUE(my_line_break_allowed(0x002Du, 0x16FE4u));
  ASSERT_FALSE(my_line_break_allowed(0x3000u, 0x002Du));
  ASSERT_TRUE(my_line_break_allowed(0x3000u, '('));
  ASSERT_TRUE(my_line_break_allowed(0x232Au, '('));
  ASSERT_TRUE(my_line_break_allowed(')', '('));
}

TEST(line_break_preserves_ambiguous_east_asian_class)
{
  ASSERT_EQ(my_line_break_class(0x2757u), MY_LB_AI);
  ASSERT_FALSE(my_line_break_allowed(0x05BEu, 0x0023u));
  ASSERT_FALSE(my_line_break_allowed(0x05BEu, 0x05D0u));
  ASSERT_TRUE(my_line_break_allowed(0x05BEu, 0x11003u));
  ASSERT_TRUE(my_line_break_allowed(0x05BEu, 0x1B05u));
  ASSERT_TRUE(my_line_break_allowed(0x05BEu, 0x1B50u));
  ASSERT_TRUE(my_line_break_allowed(0x05BEu, 0xAC00u));
  ASSERT_TRUE(my_line_break_allowed(0x05BEu, 0x231Au));
  ASSERT_TRUE(my_line_break_allowed(0x05BEu, 0x2329u));
  ASSERT_TRUE(my_line_break_allowed(0x05BEu, '('));
  ASSERT_TRUE(my_line_break_allowed(0x05BEu, 0x1F1E6u));
  ASSERT_FALSE(my_line_break_allowed('-', 0x2757u));
  ASSERT_FALSE(my_line_break_allowed('-', 0x2630u));
  ASSERT_FALSE(my_line_break_allowed('-', 0x25CCu));
  ASSERT_FALSE(my_line_break_allowed('-', '#'));
  ASSERT_TRUE(my_line_break_allowed('-', 0xAC00u));
  ASSERT_TRUE(my_line_break_allowed('-', 0x2329u));
  ASSERT_TRUE(my_line_break_allowed('-', 0x1F1E6u));
  ASSERT_FALSE(my_line_break_allowed('-', '-'));
  ASSERT_TRUE(my_line_break_allowed('-', 0x2329u));
  ASSERT_TRUE(my_line_break_allowed('-', '('));
  ASSERT_TRUE(my_line_break_allowed(0x231Au, '('));
  ASSERT_TRUE(my_line_break_allowed('g', 0xFF08u));
  ASSERT_FALSE(my_line_break_allowed(0xFE19u, '-'));
  ASSERT_TRUE(my_line_break_allowed(0xFE19u, '('));
  ASSERT_TRUE(my_line_break_allowed(',', '('));
  ASSERT_TRUE(my_line_break_allowed(',', '%'));
  ASSERT_TRUE(my_line_break_allowed(',', 0x1F1E6u));
  ASSERT_TRUE(my_line_break_allowed(0x3005u, '('));
  ASSERT_TRUE(my_line_break_allowed(0x3005u, '%'));
  ASSERT_TRUE(my_line_break_allowed(0xFE6Au, 0x2329u));
  ASSERT_TRUE(my_line_break_allowed(0xFE6Au, '('));
  ASSERT_FALSE(my_line_break_allowed(0xFE6Au, '0'));
  ASSERT_FALSE(my_line_break_allowed(0xFE6Au, 0x1F8FFu));
  ASSERT_TRUE(my_line_break_allowed(0x20A9u, '('));
  ASSERT_FALSE(my_line_break_allowed(0x00ABu, 0x1F1E6u));
  ASSERT_FALSE(my_line_break_allowed(0x00BBu, 0x1F1E6u));
  ASSERT_FALSE(my_line_break_allowed(0x05BEu, 0x2757u));
  ASSERT_FALSE(my_line_break_allowed(0x05BEu, 0x2630u));
  ASSERT_FALSE(my_line_break_allowed(0x05BEu, 0x25CCu));
}

static size_t line_break_dictionary_calls;

static my_ret_t line_break_test_dictionary(void* context,
                                           const uint32_t* codepoints,
                                           size_t count, bool* allow_before)
{
  size_t i;
  (void)context;
  line_break_dictionary_calls++;
  if (count < 2u || codepoints == NULL || allow_before == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  for (i = 1u; i < count; i++) {
    allow_before[i] = (i == 1u);
  }
  return MY_RET_OK;
}

static my_ret_t line_break_failing_dictionary(void* context,
                                              const uint32_t* codepoints,
                                              size_t count,
                                              bool* allow_before)
{
  (void)context;
  (void)codepoints;
  (void)count;
  if (allow_before != NULL && count > 1u) allow_before[1] = true;
  return MY_RET_FAIL;
}

static my_ret_t line_break_dictionary_mutates_run_start(
    void* context, const uint32_t* codepoints, size_t count,
    bool* allow_before)
{
  size_t i;
  (void)context;
  (void)codepoints;
  if (count == 0u || allow_before == NULL) return MY_RET_INVALID_PARAMS;
  allow_before[0] = !allow_before[0];
  for (i = 1u; i < count; i++) allow_before[i] = true;
  return MY_RET_OK;
}

static size_t line_break_profile_dictionary_calls;
static const char* line_break_profile_dictionary_locale;

static my_ret_t line_break_profile_dictionary(
    void* context, const my_line_break_dictionary_profile_t* profile,
    const uint32_t* codepoints, size_t count, bool* allow_before) {
  size_t i;
  (void)context;
  if (profile == NULL || profile->locale == NULL || codepoints == NULL ||
      allow_before == NULL || count < 2u) {
    return MY_RET_INVALID_PARAMS;
  }
  line_break_profile_dictionary_calls++;
  line_break_profile_dictionary_locale = profile->locale;
  for (i = 1u; i < count; ++i) {
    allow_before[i] = codepoints[i] == 0x0E02u;
  }
  return MY_RET_OK;
}

static my_ret_t line_break_profile_failing_dictionary(
    void* context, const my_line_break_dictionary_profile_t* profile,
    const uint32_t* codepoints, size_t count, bool* allow_before) {
  (void)context;
  (void)profile;
  (void)codepoints;
  if (allow_before != NULL && count > 1u) allow_before[1] = true;
  return MY_RET_FAIL;
}

TEST(line_break_sa_requires_explicit_dictionary_tailoring)
{
  uint32_t thai[] = {0x0E01u, 0x0E02u, 0x0E03u};
  bool allow_before[] = {true, false, false};
  my_line_break_options_t options = {line_break_test_dictionary, NULL, 8u};

  ASSERT_EQ(my_line_break_class(thai[0]), MY_LB_SA);
  ASSERT_EQ(my_line_break_class(thai[1]), MY_LB_SA);
  ASSERT_EQ(my_line_break_class(thai[2]), MY_LB_SA);
  ASSERT_EQ(my_line_break_apply_dictionary(thai, 3u, allow_before, NULL),
            MY_RET_OK);
  ASSERT_FALSE(allow_before[1]);
  line_break_dictionary_calls = 0u;
  ASSERT_EQ(my_line_break_apply_dictionary(thai, 3u, allow_before, &options),
            MY_RET_OK);
  ASSERT_EQ(line_break_dictionary_calls, 1u);
  ASSERT_TRUE(allow_before[1]);
  ASSERT_FALSE(allow_before[2]);
}

TEST(line_break_dictionary_budget_and_failure_does_not_commit)
{
  uint32_t thai[] = {0x0E01u, 0x0E02u};
  bool allow_before[] = {true, false};
  my_line_break_options_t too_small = {line_break_test_dictionary, NULL, 1u};
  my_line_break_options_t failing = {line_break_failing_dictionary, NULL, 8u};

  ASSERT_EQ(my_line_break_apply_dictionary(thai, 2u, allow_before, &too_small),
            MY_RET_INVALID_PARAMS);
  ASSERT_FALSE(allow_before[1]);
  ASSERT_EQ(my_line_break_apply_dictionary(thai, 2u, allow_before, &failing),
            MY_RET_FAIL);
  ASSERT_FALSE(allow_before[1]);
}

TEST(line_break_dictionary_cannot_change_run_start_boundary)
{
  uint32_t thai[] = {0x0E01u, 0x0E02u};
  bool allow_before[] = {false, false};
  my_line_break_options_t options = {
      line_break_dictionary_mutates_run_start, NULL, 8u};

  ASSERT_EQ(my_line_break_apply_dictionary(thai, 2u, allow_before, &options),
            MY_RET_OK);
  ASSERT_FALSE(allow_before[0]);
  ASSERT_TRUE(allow_before[1]);
}

TEST(line_break_dictionary_profile_requires_versioned_locale_contract)
{
  uint32_t thai[] = {0x0E01u, 0x0E02u};
  bool allow_before[] = {false, false};
  my_line_break_dictionary_profile_t profile = {1u, "th-Thai"};
  my_line_break_options_t options = {line_break_test_dictionary, NULL, 8u};

  line_break_dictionary_calls = 0u;
  ASSERT_EQ(my_line_break_apply_dictionary_ex(thai, 2u, allow_before,
                                              &options, &profile),
            MY_RET_OK);
  ASSERT_EQ(line_break_dictionary_calls, 1u);
  ASSERT_TRUE(my_line_break_dictionary_profile_valid(&profile));

  profile.version = 2u;
  ASSERT_FALSE(my_line_break_dictionary_profile_valid(&profile));
  ASSERT_EQ(my_line_break_apply_dictionary_ex(thai, 2u, allow_before,
                                              &options, &profile),
            MY_RET_INVALID_PARAMS);

  profile.version = 1u;
  profile.locale = "th--Thai";
  ASSERT_FALSE(my_line_break_dictionary_profile_valid(&profile));
  ASSERT_EQ(my_line_break_apply_dictionary_ex(thai, 2u, allow_before,
                                              &options, &profile),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_line_break_apply_dictionary_ex(thai, 2u, allow_before, NULL,
                                              &profile),
            MY_RET_INVALID_PARAMS);
  profile.locale = "12";
  ASSERT_FALSE(my_line_break_dictionary_profile_valid(&profile));
  ASSERT_EQ(my_line_break_apply_dictionary_ex(thai, 2u, allow_before, &options,
                                              &profile),
            MY_RET_INVALID_PARAMS);

  profile.locale = "th-Thai";
  ASSERT_EQ(my_line_break_apply_dictionary_ex(thai, 2u, allow_before, NULL,
                                              &profile),
            MY_RET_INVALID_PARAMS);
}

TEST(line_break_dictionary_rejects_invalid_unicode_scalars)
{
  uint32_t invalid_scalars[][2] = {{0xD800u, 0x0E01u},
                                   {0x0E01u, 0x110000u}};
  bool allow_before[] = {false, false};
  my_line_break_options_t options = {line_break_test_dictionary, NULL, 8u};
  size_t i;

  for (i = 0u; i < sizeof(invalid_scalars) / sizeof(invalid_scalars[0]);
       ++i) {
    line_break_dictionary_calls = 0u;
    allow_before[0] = false;
    allow_before[1] = false;
    ASSERT_EQ(my_line_break_apply_dictionary_ex(
                  invalid_scalars[i], 2u, allow_before, &options, NULL),
              MY_RET_INVALID_PARAMS);
    ASSERT_EQ(line_break_dictionary_calls, 0u);
    ASSERT_FALSE(allow_before[0]);
    ASSERT_FALSE(allow_before[1]);
  }
}

TEST(line_break_builtin_dictionary_is_bounded_and_conservative)
{
  uint32_t thai_words[] = {
      0x0E20u, 0x0E32u, 0x0E29u, 0x0E32u,
      0x0E44u, 0x0E17u, 0x0E22u
  };
  uint32_t unknown[] = {0x0E01u, 0x0E02u, 0x0E03u};
  bool allow_before[] = {false, false, false, false, false, false, false};
  bool unknown_boundaries[] = {false, false, false};
  my_line_break_dictionary_profile_t profile = {1u, "th-Thai"};
  my_line_break_dictionary_profile_t unsupported = {1u, "en"};

  ASSERT_TRUE(my_line_break_builtin_dictionary_supports(&profile));
  ASSERT_FALSE(my_line_break_builtin_dictionary_supports(&unsupported));
  ASSERT_EQ(my_line_break_apply_builtin_dictionary(
                thai_words, 7u, allow_before, &profile), MY_RET_OK);
  ASSERT_FALSE(allow_before[1]);
  ASSERT_FALSE(allow_before[2]);
  ASSERT_FALSE(allow_before[3]);
  ASSERT_TRUE(allow_before[4]);
  ASSERT_FALSE(allow_before[5]);
  ASSERT_FALSE(allow_before[6]);
  ASSERT_EQ(my_line_break_apply_builtin_dictionary(
                unknown, 3u, unknown_boundaries, &profile), MY_RET_OK);
  ASSERT_FALSE(unknown_boundaries[1]);
  ASSERT_FALSE(unknown_boundaries[2]);
  ASSERT_EQ(my_line_break_apply_builtin_dictionary(
                thai_words, 7u, allow_before, &unsupported),
            MY_RET_NOT_SUPPORTED);
}

TEST(line_break_builtin_dictionary_rejects_invalid_input_transactionally)
{
  uint32_t invalid[] = {0x0E20u, 0xD800u};
  uint32_t too_many[MY_LINE_BREAK_MAX_DICTIONARY_CODEPOINTS + 1u];
  bool allow_before[] = {false, true};
  bool too_many_boundaries[MY_LINE_BREAK_MAX_DICTIONARY_CODEPOINTS + 1u];
  my_line_break_dictionary_profile_t profile = {1u, "th-Thai"};
  size_t i;

  ASSERT_EQ(my_line_break_apply_builtin_dictionary(
                invalid, 2u, allow_before, &profile),
            MY_RET_INVALID_PARAMS);
  ASSERT_FALSE(allow_before[0]);
  ASSERT_TRUE(allow_before[1]);
  for (i = 0u; i < sizeof(too_many) / sizeof(too_many[0]); ++i) {
    too_many[i] = 0x0E01u;
    too_many_boundaries[i] = true;
  }
  ASSERT_EQ(my_line_break_apply_builtin_dictionary(
                too_many, sizeof(too_many) / sizeof(too_many[0]),
                too_many_boundaries, &profile),
            MY_RET_INVALID_PARAMS);
  ASSERT_TRUE(too_many_boundaries[0]);
  ASSERT_TRUE(too_many_boundaries[MY_LINE_BREAK_MAX_DICTIONARY_CODEPOINTS]);
}

TEST(line_break_profile_callback_receives_locale_without_legacy_abi_change)
{
  uint32_t thai[] = {0x0E01u, 0x0E02u, 0x0E03u};
  bool allow_before[] = {false, false, false};
  my_line_break_profile_options_t options = {
      line_break_profile_dictionary, NULL, 8u};
  my_line_break_dictionary_profile_t profile = {1u, "th-Thai"};

  line_break_profile_dictionary_calls = 0u;
  line_break_profile_dictionary_locale = NULL;
  ASSERT_EQ(my_line_break_apply_dictionary_profile(
                thai, 3u, allow_before, &options, &profile),
            MY_RET_OK);
  ASSERT_EQ(line_break_profile_dictionary_calls, 1u);
  ASSERT_STR_EQ(line_break_profile_dictionary_locale, "th-Thai");
  ASSERT_FALSE(allow_before[0]);
  ASSERT_TRUE(allow_before[1]);
  ASSERT_FALSE(allow_before[2]);

  profile.version = 2u;
  ASSERT_EQ(my_line_break_apply_dictionary_profile(
                thai, 3u, allow_before, &options, &profile),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(line_break_profile_dictionary_calls, 1u);
}

TEST(line_break_profile_callback_budget_and_failure_are_transactional)
{
  uint32_t thai[] = {0x0E01u, 0x0E02u};
  bool allow_before[] = {false, false};
  my_line_break_dictionary_profile_t profile = {1u, "th-Thai"};
  my_line_break_profile_options_t too_small = {
      line_break_profile_dictionary, NULL, 1u};
  my_line_break_profile_options_t failing = {
      line_break_profile_failing_dictionary, NULL, 8u};

  ASSERT_EQ(my_line_break_apply_dictionary_profile(
                thai, 2u, allow_before, &too_small, &profile),
            MY_RET_INVALID_PARAMS);
  ASSERT_FALSE(allow_before[1]);
  ASSERT_EQ(my_line_break_apply_dictionary_profile(
                thai, 2u, allow_before, &failing, &profile),
            MY_RET_FAIL);
  ASSERT_FALSE(allow_before[1]);
}

TEST(paragraph_consumes_profile_aware_dictionary_callback)
{
  my_line_break_dictionary_profile_t profile = {1u, "th-Thai"};
  my_line_break_profile_options_t options = {
      line_break_profile_dictionary, NULL, 8u};
  my_text_paragraph_t* paragraph =
      my_text_paragraph_process_n_break_profile_callback_ex(
          NULL, "\xE0\xB8\x81\xE0\xB8\x82\xE0\xB8\x83", 9u, NULL, 16,
          16, NULL, &options, &profile);

  ASSERT_NOT_NULL(paragraph);
  ASSERT_EQ(paragraph->line_count, 2u);
  ASSERT_EQ(paragraph->lines[0].cp_count, 1u);
  ASSERT_EQ(paragraph->lines[1].start_cp, 1u);
  my_text_paragraph_destroy(paragraph);
}

TEST(line_break_state_pairs_regional_indicators)
{
  my_line_break_state_t state;
  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x1F1E6u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x1F1E7u));
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x1F1E8u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x1F1E9u));
}

TEST(line_break_hard_breaks_split_all_unicode_separators)
{
  my_text_paragraph_t* paragraph;
  const my_text_paragraph_line_t* first;
  const my_text_paragraph_line_t* second;

  paragraph = my_text_paragraph_process_n(NULL, "a\r\nb", 4u, NULL, 16, 0);
  ASSERT_NOT_NULL(paragraph);
  ASSERT_EQ(paragraph->line_count, 2u);
  first = my_text_paragraph_line_at(paragraph, 0u);
  second = my_text_paragraph_line_at(paragraph, 1u);
  ASSERT_EQ(first->start_byte, 0u);
  ASSERT_EQ(first->end_byte, 1u);
  ASSERT_EQ(second->start_byte, 3u);
  ASSERT_EQ(second->end_byte, 4u);
  my_text_paragraph_destroy(paragraph);

  paragraph = my_text_paragraph_process(NULL, "a\xC2\x85" "b", NULL, 16, 0);
  ASSERT_NOT_NULL(paragraph);
  ASSERT_EQ(paragraph->line_count, 2u);
  my_text_paragraph_destroy(paragraph);

  paragraph = my_text_paragraph_process(NULL, "a\vb", NULL, 16, 0);
  ASSERT_NOT_NULL(paragraph);
  ASSERT_EQ(paragraph->line_count, 2u);
  my_text_paragraph_destroy(paragraph);

  paragraph = my_text_paragraph_process(NULL, "a\fb", NULL, 16, 0);
  ASSERT_NOT_NULL(paragraph);
  ASSERT_EQ(paragraph->line_count, 2u);
  my_text_paragraph_destroy(paragraph);
}

TEST(line_break_hard_break_length_is_bounded_and_crlf_is_atomic)
{
  ASSERT_EQ(my_line_break_hard_break_len(NULL, 0u), 0u);
  ASSERT_EQ(my_line_break_hard_break_len("\n", 1u), 1u);
  ASSERT_EQ(my_line_break_hard_break_len("\v", 1u), 1u);
  ASSERT_EQ(my_line_break_hard_break_len("\f", 1u), 1u);
  ASSERT_EQ(my_line_break_hard_break_len("\r\n", 2u), 2u);
  ASSERT_EQ(my_line_break_hard_break_len("\r\n", 1u), 1u);
  ASSERT_EQ(my_line_break_hard_break_len("\xC2\x85" "x", 2u), 2u);
  ASSERT_EQ(my_line_break_hard_break_len("\xE2\x80\xA8" "x", 3u), 3u);
  ASSERT_EQ(my_line_break_hard_break_len("\xE2\x80\xA9" "x", 3u), 3u);
  ASSERT_EQ(my_line_break_hard_break_len("\xE2\x80", 2u), 0u);
}

TEST(line_break_state_keeps_crlf_as_one_hard_break)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 'a'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '\r'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '\n'));
  ASSERT_TRUE(my_line_break_state_feed(&state, 'b'));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '\v'));
  ASSERT_TRUE(my_line_break_state_feed(&state, '\v'));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '\r'));
  ASSERT_TRUE(my_line_break_state_feed(&state, '\v'));
}

TEST(line_break_state_keeps_exponent_sign_with_digits)
{
  my_line_break_state_t state;
  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '1'));
  ASSERT_FALSE(my_line_break_state_feed(&state, 'e'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '-'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '1'));
}

TEST(line_break_state_keeps_all_unicode_numeric_classes)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x0966u));
  ASSERT_EQ(state.numeric_context, 1u);
  ASSERT_FALSE(my_line_break_state_feed(&state, 'e'));
  ASSERT_EQ(state.numeric_context, 2u);
  ASSERT_FALSE(my_line_break_state_feed(&state, '+'));
  ASSERT_EQ(state.numeric_context, 3u);
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x0967u));
  ASSERT_EQ(state.numeric_context, 1u);

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x1D7D8u));
  ASSERT_EQ(state.numeric_context, 1u);
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x066Bu));
  ASSERT_EQ(state.numeric_context, 1u);
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x1D7D9u));
  ASSERT_EQ(state.numeric_context, 1u);
}

TEST(line_break_state_keeps_numeric_operator_sequence_together)
{
  my_line_break_state_t state;
  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '1'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '/'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '2'));
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x4E00u));
}

TEST(line_break_state_uses_numeric_separator_lookahead)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed_with_lookahead(&state, 'a', ' ', true));
  ASSERT_FALSE(my_line_break_state_feed_with_lookahead(&state, ' ', '.', true));
  ASSERT_FALSE(my_line_break_state_feed_with_lookahead(&state, '.', 'c', true));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed_with_lookahead(&state, 'a', ' ', true));
  ASSERT_FALSE(my_line_break_state_feed_with_lookahead(&state, ' ', '.', true));
  ASSERT_TRUE(my_line_break_state_feed_with_lookahead(&state, '.', '3', true));
}

TEST(line_break_state_keeps_numeric_separator_closing_affixes_together)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '1'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '/'));
  ASSERT_FALSE(my_line_break_state_feed(&state, ')'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '%'));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '1'));
  ASSERT_FALSE(my_line_break_state_feed(&state, ','));
  ASSERT_FALSE(my_line_break_state_feed(&state, ']'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '$'));
}

TEST(line_break_state_keeps_numeric_affix_operator_sequences_together)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '%'));
  ASSERT_TRUE(my_line_break_state_feed(&state, '('));
  ASSERT_FALSE(my_line_break_state_feed(&state, ','));
  ASSERT_FALSE(my_line_break_state_feed(&state, '1'));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '$'));
  ASSERT_TRUE(my_line_break_state_feed(&state, '('));
  ASSERT_FALSE(my_line_break_state_feed(&state, ','));
  ASSERT_FALSE(my_line_break_state_feed(&state, '1'));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed_with_lookahead(&state, '$', '(', true));
  ASSERT_FALSE(my_line_break_state_feed_with_lookahead(&state, '(', '1', true));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '1'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '.'));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x20ACu));
}

TEST(line_break_state_keeps_numeric_closing_group_with_prefix)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '0'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '}'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '+'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '{'));
}

TEST(line_break_state_keeps_currency_and_percent_numbers_together)
{
  my_line_break_state_t state;
  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '$'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '1'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '0'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '%'));
  ASSERT_TRUE(my_line_break_state_feed(&state, 'x'));
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
  ASSERT_FALSE(my_line_break_allowed(0xFEFFu, 0x1F1E6u));
  ASSERT_FALSE(my_line_break_allowed(0x4E00u, 0x00A0u));
  ASSERT_FALSE(my_line_break_allowed(0x202Fu, 0x4E00u));
  ASSERT_FALSE(my_line_break_allowed('a', 0x200Du));
  ASSERT_FALSE(my_line_break_allowed(0x200Du, 'b'));
}

TEST(line_break_keeps_zero_width_non_joiner_with_adjacent_text)
{
  ASSERT_FALSE(my_line_break_allowed(0x4E00u, 0x200Cu));
  ASSERT_FALSE(my_line_break_allowed(0x200Cu, 0x4E00u));
}

TEST(line_break_state_preserves_starter_after_combining_marks)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x4E00u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x0301u));
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x4E01u));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 'a'));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x0301u));
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x4E00u));
}

TEST(line_break_state_ignores_combining_marks_for_sequence_context)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '1'));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x0301u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 'e'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '-'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '1'));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x1F1E6u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x0301u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x1F1E7u));
}

TEST(line_break_keeps_zero_width_space_break_direction)
{
  ASSERT_EQ(my_line_break_class(0x200Bu), MY_LB_ZW);
  ASSERT_FALSE(my_line_break_allowed('a', 0x200Bu));
  ASSERT_TRUE(my_line_break_allowed(0x200Bu, 'b'));
  ASSERT_FALSE(my_line_break_allowed(0x200Bu, ' '));
  ASSERT_FALSE(my_line_break_allowed(0x200Bu, 0x200Bu));
  {
    my_line_break_state_t state;
    my_line_break_state_init(&state);
    ASSERT_TRUE(my_line_break_state_feed(&state, 0x200Bu));
    ASSERT_TRUE(my_line_break_state_feed(&state, 0x0308u));
    ASSERT_FALSE(my_line_break_state_feed(&state, 0x2757u));
  }
  {
    my_line_break_state_t state;
    my_line_break_state_init(&state);
    ASSERT_TRUE(my_line_break_state_feed(&state, 0x200Du));
    ASSERT_FALSE(my_line_break_state_feed(&state, 0x0308u));
    ASSERT_TRUE(my_line_break_state_feed(&state, 0x1B05u));
  }
  {
    my_line_break_state_t state;
    my_line_break_state_init(&state);
    ASSERT_TRUE(my_line_break_state_feed(&state, 0x200Bu));
    ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
    ASSERT_TRUE(my_line_break_state_feed(&state, 0x232Au));
  }
}

TEST(line_break_state_keeps_opening_punctuation_with_following_spaces)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '('));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_FALSE(my_line_break_state_feed(&state, 'a'));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '('));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_FALSE(my_line_break_state_feed(&state, '-'));
  ASSERT_FALSE(my_line_break_state_feed(&state, 'a'));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 'a'));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_TRUE(my_line_break_state_feed(&state, '-'));
  ASSERT_FALSE(my_line_break_state_feed(&state, 't'));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '['));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x0308u));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x4E00u));
}

TEST(line_break_state_keeps_opening_punctuation_with_unicode_spaces)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '('));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x2003u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 'a'));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '['));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x3000u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x4E00u));
}

TEST(line_break_breaking_space_helper_has_bounded_set)
{
  ASSERT_TRUE(my_line_break_is_breaking_space(0x0020u));
  ASSERT_TRUE(my_line_break_is_breaking_space(0x2000u));
  ASSERT_TRUE(my_line_break_is_breaking_space(0x2006u));
  ASSERT_FALSE(my_line_break_is_breaking_space(0x2007u));
  ASSERT_TRUE(my_line_break_is_breaking_space(0x2008u));
  ASSERT_TRUE(my_line_break_is_breaking_space(0x200Au));
  ASSERT_FALSE(my_line_break_is_breaking_space(0x200Bu));
  ASSERT_FALSE(my_line_break_is_breaking_space(0x202Fu));
  ASSERT_TRUE(my_line_break_is_breaking_space(0x205Fu));
  ASSERT_TRUE(my_line_break_is_breaking_space(0x3000u));
  ASSERT_FALSE(my_line_break_is_breaking_space(0x00A0u));
}

TEST(paragraph_consumes_unicode_breaking_spaces_when_wrapping)
{
  my_text_paragraph_t* paragraph;
  const my_text_paragraph_line_t* first;
  const my_text_paragraph_line_t* second;

  paragraph = my_text_paragraph_process(NULL,
                                        "a\xE2\x80\x83" "\xE2\x80\x83" "b",
                                        NULL, 16, 8);
  ASSERT_NOT_NULL(paragraph);
  ASSERT_EQ(paragraph->line_count, 2u);
  first = my_text_paragraph_line_at(paragraph, 0u);
  second = my_text_paragraph_line_at(paragraph, 1u);
  ASSERT_EQ(first->start_byte, 0u);
  ASSERT_EQ(first->end_byte, 1u);
  ASSERT_EQ(second->start_byte, 7u);
  ASSERT_EQ(second->end_byte, 8u);
  my_text_paragraph_destroy(paragraph);
}

TEST(line_break_preserves_uax14_space_numeric_and_hebrew_context)
{
  ASSERT_FALSE(my_line_break_allowed('a', ' '));
  ASSERT_TRUE(my_line_break_allowed(' ', 'b'));
  ASSERT_TRUE(my_line_break_allowed(' ', '$'));

  ASSERT_FALSE(my_line_break_allowed('a', '1'));
  ASSERT_FALSE(my_line_break_allowed('1', 'a'));
  ASSERT_FALSE(my_line_break_allowed('$', '1'));
  ASSERT_TRUE(my_line_break_allowed('$', '('));
  ASSERT_TRUE(my_line_break_allowed(0xFE6Au, '('));
  ASSERT_FALSE(my_line_break_allowed('1', '%'));
  ASSERT_FALSE(my_line_break_allowed(',', '1'));
  ASSERT_FALSE(my_line_break_allowed('1', ','));
  ASSERT_TRUE(my_line_break_allowed('/', '0'));
  ASSERT_TRUE(my_line_break_allowed('/', '('));
  ASSERT_TRUE(my_line_break_allowed('/', '%'));
  ASSERT_FALSE(my_line_break_allowed('a', ','));
  ASSERT_FALSE(my_line_break_allowed(' ', ','));
  ASSERT_FALSE(my_line_break_allowed('.', 'A'));

  ASSERT_FALSE(my_line_break_allowed(0x05D0u, 0x05BEu));
  ASSERT_FALSE(my_line_break_allowed(0x05BEu, 0x05D0u));
  ASSERT_FALSE(my_line_break_allowed('/', 0xFB1Du));

  my_line_break_state_t bidi_hyphen_state;
  my_line_break_state_init(&bidi_hyphen_state);
  ASSERT_TRUE(my_line_break_state_feed(&bidi_hyphen_state, 0x200Fu));
  ASSERT_FALSE(my_line_break_state_feed(&bidi_hyphen_state, '-'));
  ASSERT_TRUE(my_line_break_state_feed(&bidi_hyphen_state, 0x05D9u));

}

TEST(line_break_preserves_quotation_and_class_specific_context)
{
  ASSERT_EQ(my_line_break_class('"'), MY_LB_QU);
  ASSERT_FALSE(my_line_break_allowed('a', '"'));
  ASSERT_FALSE(my_line_break_allowed('"', 'a'));
  ASSERT_FALSE(my_line_break_allowed(0x201Cu, 0x4E00u));
  ASSERT_TRUE(my_line_break_allowed(0xFF1Au, 0x201Cu));
  ASSERT_TRUE(my_line_break_allowed(0xFF1Au, 0x2018u));
  ASSERT_TRUE(my_line_break_allowed(0x4E43u, 0x201Cu));
  ASSERT_FALSE(my_line_break_allowed(0x1FFFDu, 0x00ABu));
  my_line_break_state_t quote_state;
  my_line_break_state_init(&quote_state);
  ASSERT_TRUE(my_line_break_state_feed(&quote_state, '!'));
  ASSERT_FALSE(my_line_break_state_feed(&quote_state, 0x201Du));
  ASSERT_FALSE(my_line_break_state_feed(&quote_state, ' '));
  ASSERT_TRUE(my_line_break_state_feed(&quote_state, 0x4E00u));
  my_line_break_state_init(&quote_state);
  ASSERT_TRUE(my_line_break_state_feed(&quote_state, 0x3002u));
  ASSERT_FALSE(my_line_break_state_feed(&quote_state, 0x2019u));
  ASSERT_TRUE(my_line_break_state_feed(&quote_state, 0x5176u));
  my_line_break_state_init(&quote_state);
  ASSERT_TRUE(my_line_break_state_feed(&quote_state, 0x6C64u));
  ASSERT_FALSE(my_line_break_state_feed(&quote_state, 0x201Du));
  ASSERT_TRUE(my_line_break_state_feed(&quote_state, 0x800Cu));
  my_line_break_state_init(&quote_state);
  ASSERT_TRUE(my_line_break_state_feed(&quote_state, 0x300Bu));
  ASSERT_TRUE(my_line_break_state_feed(&quote_state, 0x7684u));
  ASSERT_FALSE(my_line_break_state_feed(&quote_state, 0x201Cu));
  ASSERT_FALSE(my_line_break_allowed(0x2757u, '('));
  ASSERT_TRUE(my_line_break_allowed(0x4E00u, '('));
  ASSERT_TRUE(my_line_break_allowed(0x1B05u, '('));
  ASSERT_TRUE(my_line_break_allowed(0x11003u, '('));
  ASSERT_TRUE(my_line_break_allowed(0x1B50u, '('));
  ASSERT_TRUE(my_line_break_allowed(0x2014u, '('));
  ASSERT_TRUE(my_line_break_allowed(0x2757u, 0x2329u));

  ASSERT_EQ(my_line_break_class(0x05BEu), MY_LB_HH);
  ASSERT_FALSE(my_line_break_allowed(0x05D0u, 0x05BEu));
  ASSERT_FALSE(my_line_break_allowed(0x05BEu, 0x05D0u));
  ASSERT_EQ(my_line_break_class('/'), MY_LB_SY);
  ASSERT_FALSE(my_line_break_allowed('/', 0x05D0u));

  /* UAX #14 LB20 keeps QU attached to an object character. */
  ASSERT_FALSE(my_line_break_allowed(0x00ABu, 0xFFFCu));
  ASSERT_FALSE(my_line_break_allowed(0x00BBu, 0xFFFCu));
  ASSERT_FALSE(my_line_break_allowed('"', 0xFFFCu));
  ASSERT_TRUE(my_line_break_allowed(0xFFFCu, 0xFE19u));

  ASSERT_EQ(my_line_break_class('1'), MY_LB_NU);
  ASSERT_EQ(my_line_break_class('$'), MY_LB_PR);
  ASSERT_EQ(my_line_break_class('%'), MY_LB_PO);
  ASSERT_EQ(my_line_break_class(','), MY_LB_IS);
}

TEST(line_break_preserves_break_after_and_numeric_affix_rules)
{
  ASSERT_FALSE(my_line_break_allowed('a', 0x05BEu));
  ASSERT_FALSE(my_line_break_allowed('a', '/'));

  ASSERT_FALSE(my_line_break_allowed('a', '$'));
  ASSERT_FALSE(my_line_break_allowed('$', 'a'));
  ASSERT_FALSE(my_line_break_allowed('a', '%'));
  ASSERT_FALSE(my_line_break_allowed('%', 'a'));
  ASSERT_FALSE(my_line_break_allowed(0x05D0u, '$'));
  ASSERT_FALSE(my_line_break_allowed('$', 0x05D0u));

  ASSERT_FALSE(my_line_break_allowed('$', 0x4E00u));
  ASSERT_FALSE(my_line_break_allowed(0x4E00u, '%'));
  ASSERT_FALSE(my_line_break_allowed('$', 0x1F466u));
  ASSERT_FALSE(my_line_break_allowed(0x1F466u, '%'));
  ASSERT_FALSE(my_line_break_allowed('-', '1'));

  ASSERT_FALSE(my_line_break_allowed(0x1100u, '%'));
  ASSERT_FALSE(my_line_break_allowed('$', 0x1100u));

  my_line_break_state_t state;
  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '1'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '%'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '2'));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '1'));
  ASSERT_FALSE(my_line_break_state_feed(&state, ')'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '$'));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x2014u));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x2E3Au));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x05D0u));
  ASSERT_FALSE(my_line_break_state_feed(&state, '-'));
  ASSERT_FALSE(my_line_break_state_feed(&state, 'a'));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x05D0u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x05BEu));
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x4E00u));

}

TEST(line_break_preserves_break_both_semantics)
{
  my_line_break_state_t state;

  ASSERT_EQ(my_line_break_class(0x2014u), MY_LB_B2);
  ASSERT_EQ(my_line_break_class(0x2015u), MY_LB_AI);
  ASSERT_TRUE(my_line_break_allowed('a', 0x2014u));
  ASSERT_TRUE(my_line_break_allowed(0x2014u, 'a'));
  ASSERT_TRUE(my_line_break_allowed(0x2014u, 0x2015u));
  ASSERT_FALSE(my_line_break_allowed(0x2014u, 0x2E3Au));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x2014u));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x2E3Au));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x2014u));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x00BBu));
}

TEST(line_break_preserves_break_before_semantics)
{
  ASSERT_EQ(my_line_break_class(0x00B4u), MY_LB_BB);
  ASSERT_TRUE(my_line_break_allowed('a', 0x00B4u));
  ASSERT_FALSE(my_line_break_allowed(0x00B4u, 'a'));
}

TEST(line_break_preserves_space_after_break_after_classes)
{
  ASSERT_TRUE(my_line_break_allowed(' ', 0x3000u));
  ASSERT_TRUE(my_line_break_allowed(' ', 0x2024u));
  ASSERT_TRUE(my_line_break_allowed(' ', 0x05BEu));
  ASSERT_TRUE(my_line_break_allowed(' ', 0x3041u));
  ASSERT_TRUE(my_line_break_allowed(' ', 0x3005u));
  ASSERT_TRUE(my_line_break_allowed(' ', 0x203Cu));
  ASSERT_TRUE(my_line_break_allowed(' ', 0x0308u));
  ASSERT_TRUE(my_line_break_allowed(' ', 0x00A0u));
  ASSERT_TRUE(my_line_break_allowed(' ', 0x1BF2u));
  ASSERT_FALSE(my_line_break_allowed(0xFFFCu, ' '));
  ASSERT_FALSE(my_line_break_allowed(0xFFFCu, 0x0308u));
  ASSERT_TRUE(my_line_break_allowed(0xFFFCu, 'a'));
  ASSERT_TRUE(my_line_break_allowed(0xFFFCu, 0x1BF2u));
  ASSERT_TRUE(my_line_break_allowed(0xFFFCu, 0x1B44u));
  ASSERT_FALSE(my_line_break_allowed(0xFFFCu, ')'));
  ASSERT_FALSE(my_line_break_allowed(0xFFFCu, ','));
  ASSERT_TRUE(my_line_break_allowed(0xFFFCu, 0x05BEu));
  ASSERT_TRUE(my_line_break_allowed(0xFFFCu, 0x3000u));
  ASSERT_TRUE(my_line_break_allowed(' ', 0xFFFCu));
  ASSERT_TRUE(my_line_break_allowed(' ', 0x00ABu));
  ASSERT_FALSE(my_line_break_allowed(' ', 0x00BBu));
  ASSERT_TRUE(my_line_break_allowed(' ', '"'));
  ASSERT_TRUE(my_line_break_allowed(' ', 0x200Du));
  ASSERT_TRUE(my_line_break_allowed(' ', 0x1F3FBu));
  ASSERT_FALSE(my_line_break_allowed(' ', '/'));
}

TEST(line_break_state_keeps_no_start_after_closing_space)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, ')'));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x3005u));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '/'));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x3005u));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, ')'));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_TRUE(my_line_break_state_feed(&state, 'a'));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '!'));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x3005u));
  ASSERT_TRUE(my_line_break_allowed('!', '('));
  ASSERT_TRUE(my_line_break_allowed(0xAC00u, '('));
}

TEST(line_break_state_allows_no_start_after_numeric_separator_space)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, ','));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x3005u));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x25CCu));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_FALSE(my_line_break_state_feed(&state, ','));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '#'));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_FALSE(my_line_break_state_feed(&state, ','));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0xFEFFu));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_FALSE(my_line_break_state_feed(&state, ','));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x200Du));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_FALSE(my_line_break_state_feed(&state, ','));
}

TEST(line_break_state_keeps_opening_space_before_ideographic_space)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '('));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x3000u));
}

TEST(line_break_state_keeps_opening_quote_space_before_ambiguous_text)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x00ABu));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x2757u));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x00ABu));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x2329u));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '('));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x0308u));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_FALSE(my_line_break_state_feed(&state, ')'));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x00BBu));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x00BBu));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x2014u));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x00BBu));
}

TEST(line_break_state_treats_combining_mark_after_space_as_alphabetic)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, ' '));
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x0308u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x2757u));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 'a'));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x00ABu));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_TRUE(my_line_break_state_feed(&state, 'P'));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, ':'));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x00ABu));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_FALSE(my_line_break_state_feed(&state, 'E'));
}

TEST(line_break_state_allows_alphabetic_space_before_closing_quote)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 'n'));
  ASSERT_FALSE(my_line_break_state_feed(&state, ' '));
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x00BBu));
}

TEST(line_break_preserves_additional_uax14_classes)
{
  ASSERT_EQ(my_line_break_class(0x3000u), MY_LB_BA);
  ASSERT_FALSE(my_line_break_allowed('a', 0x3000u));
  ASSERT_TRUE(my_line_break_allowed(0x3000u, 'a'));

  ASSERT_EQ(my_line_break_class(0x2024u), MY_LB_IN);
  ASSERT_FALSE(my_line_break_allowed('a', 0x2024u));
  ASSERT_TRUE(my_line_break_allowed(0x2024u, 'a'));

  ASSERT_EQ(my_line_break_class(0xFFFCu), MY_LB_CB);
  ASSERT_EQ(my_line_break_class(0x1F466u), MY_LB_EB);
  ASSERT_EQ(my_line_break_class(0x1F3FBu), MY_LB_EM);
  ASSERT_FALSE(my_line_break_allowed(0x1F466u, 0x1F3FBu));
  ASSERT_TRUE(my_line_break_allowed(0x1B05u, 0x1F3FBu));
  ASSERT_TRUE(my_line_break_allowed(0x2014u, 0x1BF2u));
  ASSERT_TRUE(my_line_break_allowed(0x2014u, 0x1B44u));
  ASSERT_TRUE(my_line_break_allowed(0x1BF2u, 'a'));
  ASSERT_TRUE(my_line_break_allowed(0x1BF2u, '('));
  ASSERT_TRUE(my_line_break_allowed(0x1B44u, 0x2757u));
  ASSERT_TRUE(my_line_break_allowed(0x1B44u, '('));
  {
    my_line_break_state_t state;
    my_line_break_state_init(&state);
    ASSERT_TRUE(my_line_break_state_feed(&state, 0x1BF2u));
    ASSERT_TRUE(my_line_break_state_feed(&state, 0x2757u));
  }
  {
    my_line_break_state_t state;
    my_line_break_state_init(&state);
    ASSERT_TRUE(my_line_break_state_feed(&state, 0x1B44u));
    ASSERT_FALSE(my_line_break_state_feed(&state, 0x0308u));
    ASSERT_TRUE(my_line_break_state_feed(&state, 0x2757u));
  }
  ASSERT_TRUE(my_line_break_allowed(0x1B44u, 'a'));

  ASSERT_EQ(my_line_break_class(0x3041u), MY_LB_CJ);
  ASSERT_FALSE(my_line_break_allowed('a', 0x3041u));
  ASSERT_TRUE(my_line_break_allowed(0x3041u, '('));
  ASSERT_TRUE(my_line_break_allowed(0x270Au, '('));
  ASSERT_TRUE(my_line_break_allowed(0x1F3FBu, '('));
}

TEST(line_break_preserves_script_specific_uax14_classes)
{
  ASSERT_EQ(my_line_break_class(0x11003u), MY_LB_AP);
  ASSERT_EQ(my_line_break_class(0x11005u), MY_LB_AK);
  ASSERT_EQ(my_line_break_class(0x1B50u), MY_LB_AS);
  ASSERT_EQ(my_line_break_class(0x1BF2u), MY_LB_VF);
  ASSERT_EQ(my_line_break_class(0x1B44u), MY_LB_VI);
  ASSERT_FALSE(my_line_break_allowed(0x11003u, 0x11005u));
  ASSERT_FALSE(my_line_break_allowed(0x11005u, 0x1BF2u));
  ASSERT_FALSE(my_line_break_allowed(0x1B50u, 0x1B44u));
  ASSERT_FALSE(my_line_break_allowed(0x25CCu, 0x1B44u));
  ASSERT_TRUE(my_line_break_allowed(0x11F26u, 0x11F02u));
  ASSERT_TRUE(my_line_break_allowed(0x11F26u, 0x1B50u));
  ASSERT_TRUE(my_line_break_allowed(0x1B50u, 0x11F26u));
  ASSERT_TRUE(my_line_break_allowed(0x11F26u, 0x11F26u));
  ASSERT_TRUE(my_line_break_allowed(0x11F26u, 'a'));
  ASSERT_TRUE(my_line_break_allowed('a', 0x11F26u));
}

TEST(line_break_state_preserves_indic_context)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x1B50u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x1B44u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x25CCu));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x11F26u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x11F42u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x11F26u));
}

TEST(line_break_state_preserves_indic_virama_through_marks)
{
  my_line_break_state_t state;

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x1B50u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x1B44u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x0308u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x0301u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x25CCu));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x1BD2u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x1BEAu));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x1BC9u));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, 0x1BC2u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x1BE7u));
  ASSERT_FALSE(my_line_break_state_feed(&state, 0x1BC9u));
}

TEST(line_break_preserves_closing_punctuation_context)
{
  ASSERT_EQ(my_line_break_class(')'), MY_LB_CP);
  ASSERT_EQ(my_line_break_class(']'), MY_LB_CP);
  ASSERT_EQ(my_line_break_class('!'), MY_LB_EX);
  ASSERT_EQ(my_line_break_class('}'), MY_LB_CL);
  ASSERT_FALSE(my_line_break_allowed('a', ')'));
  ASSERT_FALSE(my_line_break_allowed(')', 'a'));
  ASSERT_TRUE(my_line_break_allowed(')', 0xAC00u));
  ASSERT_FALSE(my_line_break_allowed(')', 0x0E01u));
  ASSERT_FALSE(my_line_break_allowed(')', 0x1F8FFu));
  ASSERT_FALSE(my_line_break_allowed(')', 0xEFFFDu));
  ASSERT_TRUE(my_line_break_allowed(')', 0x1FFFDu));
  ASSERT_TRUE(my_line_break_allowed('!', 'a'));
}

TEST(line_break_keeps_unicode_spacing_marks_with_adjacent_text)
{
  ASSERT_FALSE(my_line_break_allowed(0x4E00u, 0x093Eu));
  ASSERT_FALSE(my_line_break_allowed(0x093Eu, 0x4E00u));
}

TEST(line_break_keeps_nonbreaking_hyphen_and_bom_glued)
{
  ASSERT_FALSE(my_line_break_allowed(0x4E00u, 0x2011u));
  ASSERT_FALSE(my_line_break_allowed(0x2011u, 0x4E00u));
  ASSERT_FALSE(my_line_break_allowed(0x4E00u, 0xFEFFu));
  ASSERT_FALSE(my_line_break_allowed(0xFEFFu, 0x4E00u));
}

TEST(line_break_keeps_emoji_extensions_with_base_text)
{
  ASSERT_FALSE(my_line_break_allowed(0x1F600u, 0xFE0Fu));
  ASSERT_FALSE(my_line_break_allowed(0xFE0Fu, 'a'));
  ASSERT_FALSE(my_line_break_allowed(0x1F466u, 0x1F3FBu));
  ASSERT_TRUE(my_line_break_allowed(0x1F3FBu, 'a'));
  ASSERT_FALSE(my_line_break_allowed(0x1F600u, 0xE0061u));
  ASSERT_FALSE(my_line_break_allowed(0xE0061u, 'a'));
}

TEST(line_break_keeps_hangul_syllable_sequences)
{
  /* UAX #14 LB26: Hangul Jamo and LV/LVT syllables stay in one cluster. */
  ASSERT_FALSE(my_line_break_allowed(0x1100u, 0x1161u));
  ASSERT_FALSE(my_line_break_allowed(0x1161u, 0x11A8u));
  ASSERT_FALSE(my_line_break_allowed(0x11A8u, 0x11A8u));
  ASSERT_FALSE(my_line_break_allowed(0xAC00u, 0x1161u));
  ASSERT_FALSE(my_line_break_allowed(0xAC00u, 0x11A8u));
  ASSERT_FALSE(my_line_break_allowed(0xAC01u, 0x11A8u));

  /* A trailing Jamo cannot be followed by a vowel without a break rule. */
  ASSERT_TRUE(my_line_break_allowed(0xAC01u, 0x1161u));
  ASSERT_TRUE(my_line_break_allowed(0x1100u, 0x11A8u));
}

TEST(line_break_separates_hangul_and_sa_contexts)
{
  /* SA is not part of a Hangul alphabetic run. */
  ASSERT_TRUE(my_line_break_allowed(0xAC00u, 0x0E01u));
  ASSERT_TRUE(my_line_break_allowed(0x1100u, 0x0E01u));
  ASSERT_TRUE(my_line_break_allowed(',', 0xAC00u));
  ASSERT_TRUE(my_line_break_allowed(',', 0x1100u));

  /* LB20 keeps HY/HH attached to a following SA character. */
  ASSERT_FALSE(my_line_break_allowed('-', 0x0E01u));
  ASSERT_FALSE(my_line_break_allowed(0x05BEu, 0x0E01u));
}

TEST(line_break_keeps_id_extended_pictographic_with_modifier)
{
  ASSERT_FALSE(my_line_break_allowed(0x1FFFDu, 0x1F3FBu));
  ASSERT_TRUE(my_line_break_allowed(0xEFFFDu, 0x1F3FBu));
  ASSERT_FALSE(my_line_break_allowed(0x2757u, 0x1F8FFu));
  ASSERT_FALSE(my_line_break_allowed(')', 0x2757u));
  ASSERT_TRUE(my_line_break_allowed(0x2757u, 0x1F1E6u));
  ASSERT_TRUE(my_line_break_allowed(0x1F1E6u, 0x2757u));
  ASSERT_TRUE(my_line_break_allowed(0x1F1E6u, '('));
  ASSERT_TRUE(my_line_break_allowed(0x1F1E6u, 0x1F8FFu));

  ASSERT_FALSE(my_line_break_allowed(0x1F02Cu, 0x1F3FBu));
  ASSERT_FALSE(my_line_break_allowed(0x1F8FFu, 0x1F3FBu));
  ASSERT_TRUE(my_line_break_allowed(0xAC00u, 0x1F8FFu));
  ASSERT_TRUE(my_line_break_allowed(0x1F8FFu, 0xAC00u));
  ASSERT_FALSE(my_line_break_allowed(0x1F8FFu, 0x2757u));
  ASSERT_FALSE(my_line_break_allowed(0x1F8FFu, '0'));
  ASSERT_FALSE(my_line_break_allowed(0x1F8FFu, '('));
  ASSERT_FALSE(my_line_break_allowed(0x1F8FFu, 0x20A9u));
  ASSERT_FALSE(my_line_break_allowed(0x1F8FFu, 0x0E01u));
  ASSERT_FALSE(my_line_break_allowed(0x1F8FFu, 0x1F8FFu));
  ASSERT_FALSE(my_line_break_allowed(0x05D0u, 0x1F8FFu));
  ASSERT_FALSE(my_line_break_allowed(0x1F8FFu, 0x05D0u));
  ASSERT_FALSE(my_line_break_allowed('-', 0x1F8FFu));
  ASSERT_FALSE(my_line_break_allowed('0', 0x1F8FFu));
  ASSERT_FALSE(my_line_break_allowed(',', 0x1F8FFu));
  ASSERT_FALSE(my_line_break_allowed(0x05BEu, 0x1F8FFu));
}

TEST(line_break_keeps_break_both_and_hebrew_solidus_sequences)
{
  ASSERT_FALSE(my_line_break_allowed(0x2014u, 0x2014u));
  ASSERT_FALSE(my_line_break_allowed(0x2014u, 0x2E3Au));
  ASSERT_FALSE(my_line_break_allowed(0x002Fu, 0x05D0u));
  ASSERT_FALSE(my_line_break_allowed(0x2044u, 0x05D0u));
}

TEST(line_break_keeps_hyphen_before_hebrew_letter)
{
  my_line_break_state_t state;
  ASSERT_EQ(my_line_break_class('-'), MY_LB_HY);
  ASSERT_FALSE(my_line_break_allowed('-', 0x05D0u));
  ASSERT_FALSE(my_line_break_allowed(0x05D0u, '-'));
  ASSERT_TRUE(my_line_break_allowed('-', 'l'));

  my_line_break_state_init(&state);
  ASSERT_TRUE(my_line_break_state_feed(&state, '('));
  ASSERT_FALSE(my_line_break_state_feed(&state, 'c'));
  ASSERT_FALSE(my_line_break_state_feed(&state, 'o'));
  ASSERT_FALSE(my_line_break_state_feed(&state, 'n'));
  ASSERT_FALSE(my_line_break_state_feed(&state, ')'));
  ASSERT_FALSE(my_line_break_state_feed(&state, '-'));
  ASSERT_TRUE(my_line_break_state_feed(&state, 'l'));
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

TEST(paragraph_does_not_break_inside_cross_face_combining_cluster)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *primary_path =
      "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  const char *fallback_path =
      "/usr/share/fonts/google-noto-vf/NotoSans[wght].ttf";
  FILE *primary_file = fopen(primary_path, "rb");
  FILE *fallback_file = fopen(fallback_path, "rb");
  const my_font_source_t sources[] = {{primary_path, 0}, {fallback_path, 0}};
  my_font_t *font;
  my_text_paragraph_t *paragraph;
  const my_text_paragraph_line_t *first;
  const my_text_paragraph_line_t *second;

  if (primary_file == NULL || fallback_file == NULL) {
    if (primary_file != NULL) fclose(primary_file);
    if (fallback_file != NULL) fclose(fallback_file);
    printf("  SKIP: no paragraph cluster font pair\n");
    return;
  }
  fclose(primary_file);
  fclose(fallback_file);
  font = my_font_create_chain_ex(NULL, sources, 2u, 16u);
  ASSERT_NOT_NULL(font);
  paragraph = my_text_paragraph_process(NULL, "a\xCC\x85" "b", font, 24, 1);
  ASSERT_NOT_NULL(paragraph);
  ASSERT_EQ(paragraph->line_count, 2u);
  first = my_text_paragraph_line_at(paragraph, 0u);
  second = my_text_paragraph_line_at(paragraph, 1u);
  ASSERT_NOT_NULL(first);
  ASSERT_NOT_NULL(second);
  ASSERT_EQ(first->start_cp, 0u);
  ASSERT_EQ(first->cp_count, 2u);
  ASSERT_EQ(second->start_cp, 2u);
  ASSERT_EQ(second->cp_count, 1u);
  my_text_paragraph_destroy(paragraph);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
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

TEST(paragraph_process_n_uses_exact_utf8_slice)
{
  static const char source[] = {'a', 'b', '\n', 'c', 'd'};
  my_text_paragraph_t* paragraph = my_text_paragraph_process_n(
      NULL, source, 5u, NULL, 16, 0);
  const my_text_paragraph_line_t* first;
  const my_text_paragraph_line_t* second;

  ASSERT_NOT_NULL(paragraph);
  ASSERT_EQ(paragraph->logical_len, 4u);
  ASSERT_EQ(paragraph->line_count, 2u);
  first = my_text_paragraph_line_at(paragraph, 0u);
  second = my_text_paragraph_line_at(paragraph, 1u);
  ASSERT_NOT_NULL(first);
  ASSERT_NOT_NULL(second);
  ASSERT_EQ(first->start_byte, 0u);
  ASSERT_EQ(first->end_byte, 2u);
  ASSERT_EQ(second->start_byte, 3u);
  ASSERT_EQ(second->end_byte, 5u);
  my_text_paragraph_destroy(paragraph);
}

TEST(paragraph_process_n_rejects_embedded_nul)
{
  static const char source[] = {'a', '\0', 'b'};
  ASSERT_TRUE(my_text_paragraph_process_n(NULL, source, sizeof(source), NULL,
                                          16, 0) == NULL);
  {
    my_text_paragraph_t* paragraph =
        my_text_paragraph_process_n(NULL, source, 0u, NULL, 16, 0);
    ASSERT_NOT_NULL(paragraph);
    my_text_paragraph_destroy(paragraph);
  }
}

TEST(paragraph_shapes_only_current_physical_line)
{
  paragraph_test_font_t font = {{&s_paragraph_shape_ex_vtable}, NULL, 0, 0, 0,
                                {0}, 0};
  my_text_paragraph_t* paragraph;

  memset(s_paragraph_segment_bytes, 0, sizeof(s_paragraph_segment_bytes));
  s_paragraph_shape_ex_calls = 0;
  paragraph = my_text_paragraph_process(NULL, "a\nb", (my_font_t*)&font, 16,
                                        0);
  ASSERT_NOT_NULL(paragraph);
  ASSERT_EQ(s_paragraph_shape_ex_calls, 2u);
  ASSERT_EQ(s_paragraph_segment_bytes[0], 1u);
  ASSERT_EQ(s_paragraph_segment_bytes[1], 1u);
  my_text_paragraph_destroy(paragraph);
}

TEST(paragraph_consumes_bounded_sa_dictionary_options)
{
  my_line_break_options_t options = {line_break_test_dictionary, NULL, 8u};
  my_text_paragraph_t* paragraph = my_text_paragraph_process_n_break_ex(
      NULL, "\xE0\xB8\x81\xE0\xB8\x82\xE0\xB8\x83", 9u, NULL, 16, 16,
      NULL, &options);
  const my_text_paragraph_line_t* first;
  const my_text_paragraph_line_t* second;

  ASSERT_NOT_NULL(paragraph);
  ASSERT_EQ(paragraph->line_count, 2u);
  first = my_text_paragraph_line_at(paragraph, 0u);
  second = my_text_paragraph_line_at(paragraph, 1u);
  ASSERT_NOT_NULL(first);
  ASSERT_NOT_NULL(second);
  ASSERT_EQ(first->cp_count, 1u);
  ASSERT_EQ(second->start_cp, 1u);
  ASSERT_EQ(second->cp_count, 2u);
  my_text_paragraph_destroy(paragraph);
}

TEST(paragraph_consumes_versioned_sa_dictionary_profile)
{
  my_line_break_dictionary_profile_t profile = {1u, "th-Thai"};
  my_line_break_options_t options = {line_break_test_dictionary, NULL, 8u};
  my_text_paragraph_t* paragraph =
      my_text_paragraph_process_n_break_profile_ex(
          NULL, "\xE0\xB8\x81\xE0\xB8\x82\xE0\xB8\x83", 9u, NULL, 16, 16, NULL,
          &options, &profile);

  ASSERT_NOT_NULL(paragraph);
  ASSERT_EQ(paragraph->line_count, 2u);
  my_text_paragraph_destroy(paragraph);

  profile.version = 2u;
  ASSERT_TRUE(my_text_paragraph_process_n_break_profile_ex(
                  NULL, "\xE0\xB8\x81\xE0\xB8\x82\xE0\xB8\x83", 9u, NULL, 16, 16,
                  NULL, &options, &profile) == NULL);
}

TEST(paragraph_rejects_failed_sa_dictionary_transactionally)
{
  my_line_break_options_t options = {line_break_failing_dictionary, NULL, 8u};

  ASSERT_TRUE(my_text_paragraph_process_n_break_ex(
                  NULL, "\xE0\xB8\x81\xE0\xB8\x82", 6u, NULL, 16, 16,
                  NULL, &options) == NULL);
}

TEST_MAIN_BEGIN()
    RUN_TEST(arabic_shape_forms_lam_alef);
    RUN_TEST(text_layout_bidi_prescan_is_bounded);
    RUN_TEST(text_layout_bidi_prescan_does_not_read_past_slice);
    RUN_TEST(text_layout_process_n_uses_exact_utf8_slice);
    RUN_TEST(string_utf8_length_validates_scalar_sequences);
    RUN_TEST(text_layout_maps_rtl_visual_order);
    RUN_TEST(text_layout_shapes_bidi_runs_with_logical_clusters);
    RUN_TEST(text_layout_splits_mixed_scripts_for_shape_provider);
    RUN_TEST(text_layout_shape_ex_forwards_language_and_features);
    RUN_TEST(text_layout_shape_reuses_bounded_glyph_cache);
    RUN_TEST(text_layout_shape_cache_isolated_by_shaping_parameters);
    RUN_TEST(text_layout_shape_cache_normalizes_language_tag_case);
    RUN_TEST(text_layout_shape_cache_evicts_oldest_entry);
    RUN_TEST(text_layout_shape_cache_write_failure_keeps_result);
    RUN_TEST(text_layout_shape_cache_hit_only_allocates_output);
    RUN_TEST(text_layout_shape_ex_failure_rolls_back_segment_results);
    RUN_TEST(text_layout_keeps_inherited_marks_with_previous_script);
    RUN_TEST(text_layout_maps_thai_to_thai_script);
    RUN_TEST(text_layout_maps_additional_unicode_scripts);
    RUN_TEST(text_layout_keeps_arabic_common_punctuation_with_neighbor_script);
    RUN_TEST(text_layout_maps_script_supplementary_blocks);
    RUN_TEST(text_layout_uses_full_unicode_script_data_when_bidi_enabled);
    RUN_TEST(text_layout_keeps_katakana_prolonged_mark_in_one_run);
    RUN_TEST(text_layout_resolves_script_extensions_from_neighbors);
    RUN_TEST(text_layout_keeps_variation_selector_with_neighbor_script);
    RUN_TEST(paragraph_process_ex_forwards_shaping_parameters);
    RUN_TEST(paragraph_process_ex_owns_shaping_parameter_strings);
    RUN_TEST(paragraph_process_ex_parameter_copy_is_transactional);
    RUN_TEST(paragraph_destroy_releases_owned_shaping_parameters_once);
    RUN_TEST(paragraph_line_layout_lazily_caches_visual_mapping);
    RUN_TEST(paragraph_line_layout_cache_isolated_and_retriable_after_oom);
    RUN_TEST(paragraph_line_layout_rejects_corrupt_line_range);
    RUN_TEST(paragraph_line_layout_cache_is_bounded_and_lru);
    RUN_TEST(paragraph_line_mapping_uses_global_logical_boundaries);
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
    RUN_TEST(line_break_combining_data_uses_pinned_unicode_version);
    RUN_TEST(line_break_uses_unicode17_new_letter_classes);
    RUN_TEST(line_break_preserves_unicode_cm_class);
    RUN_TEST(line_break_preserves_unicode_gl_class);
    RUN_TEST(line_break_preserves_ambiguous_east_asian_class);
    RUN_TEST(line_break_sa_requires_explicit_dictionary_tailoring);
    RUN_TEST(line_break_dictionary_budget_and_failure_does_not_commit);
    RUN_TEST(line_break_dictionary_cannot_change_run_start_boundary);
    RUN_TEST(line_break_dictionary_profile_requires_versioned_locale_contract);
    RUN_TEST(line_break_dictionary_rejects_invalid_unicode_scalars);
    RUN_TEST(line_break_builtin_dictionary_is_bounded_and_conservative);
    RUN_TEST(line_break_builtin_dictionary_rejects_invalid_input_transactionally);
    RUN_TEST(line_break_profile_callback_receives_locale_without_legacy_abi_change);
    RUN_TEST(line_break_profile_callback_budget_and_failure_are_transactional);
    RUN_TEST(paragraph_consumes_profile_aware_dictionary_callback);
    RUN_TEST(line_break_state_pairs_regional_indicators);
    RUN_TEST(line_break_hard_breaks_split_all_unicode_separators);
    RUN_TEST(line_break_hard_break_length_is_bounded_and_crlf_is_atomic);
    RUN_TEST(line_break_state_keeps_crlf_as_one_hard_break);
    RUN_TEST(line_break_state_keeps_exponent_sign_with_digits);
    RUN_TEST(line_break_state_keeps_all_unicode_numeric_classes);
    RUN_TEST(line_break_state_keeps_numeric_operator_sequence_together);
    RUN_TEST(line_break_state_uses_numeric_separator_lookahead);
    RUN_TEST(line_break_state_keeps_numeric_separator_closing_affixes_together);
    RUN_TEST(line_break_state_keeps_numeric_affix_operator_sequences_together);
    RUN_TEST(line_break_state_keeps_numeric_closing_group_with_prefix);
    RUN_TEST(line_break_state_keeps_currency_and_percent_numbers_together);
    RUN_TEST(line_break_keeps_hebrew_quotes_and_unicode_numbers_together);
    RUN_TEST(line_break_preserves_break_both_semantics);
    RUN_TEST(line_break_preserves_break_before_semantics);
    RUN_TEST(line_break_preserves_space_after_break_after_classes);
    RUN_TEST(line_break_state_keeps_no_start_after_closing_space);
    RUN_TEST(line_break_state_allows_no_start_after_numeric_separator_space);
    RUN_TEST(line_break_state_keeps_opening_space_before_ideographic_space);
    RUN_TEST(line_break_state_keeps_opening_quote_space_before_ambiguous_text);
    RUN_TEST(line_break_state_treats_combining_mark_after_space_as_alphabetic);
    RUN_TEST(line_break_state_allows_alphabetic_space_before_closing_quote);
    RUN_TEST(line_break_keeps_unicode_glue_and_joiners_together);
    RUN_TEST(line_break_keeps_zero_width_non_joiner_with_adjacent_text);
    RUN_TEST(line_break_state_preserves_starter_after_combining_marks);
    RUN_TEST(line_break_state_ignores_combining_marks_for_sequence_context);
    RUN_TEST(line_break_keeps_zero_width_space_break_direction);
    RUN_TEST(line_break_state_keeps_opening_punctuation_with_following_spaces);
    RUN_TEST(line_break_state_keeps_opening_punctuation_with_unicode_spaces);
    RUN_TEST(line_break_breaking_space_helper_has_bounded_set);
    RUN_TEST(paragraph_consumes_unicode_breaking_spaces_when_wrapping);
    RUN_TEST(line_break_preserves_uax14_space_numeric_and_hebrew_context);
    RUN_TEST(line_break_preserves_quotation_and_class_specific_context);
    RUN_TEST(line_break_separates_hangul_and_sa_contexts);
    RUN_TEST(line_break_keeps_id_extended_pictographic_with_modifier);
    RUN_TEST(line_break_preserves_break_after_and_numeric_affix_rules);
    RUN_TEST(line_break_preserves_additional_uax14_classes);
    RUN_TEST(line_break_preserves_script_specific_uax14_classes);
    RUN_TEST(line_break_state_preserves_indic_context);
    RUN_TEST(line_break_state_preserves_indic_virama_through_marks);
    RUN_TEST(line_break_preserves_closing_punctuation_context);
    RUN_TEST(line_break_keeps_unicode_spacing_marks_with_adjacent_text);
    RUN_TEST(line_break_keeps_nonbreaking_hyphen_and_bom_glued);
    RUN_TEST(line_break_keeps_emoji_extensions_with_base_text);
    RUN_TEST(line_break_keeps_hangul_syllable_sequences);
    RUN_TEST(line_break_keeps_break_both_and_hebrew_solidus_sequences);
    RUN_TEST(line_break_keeps_hyphen_before_hebrew_letter);
    RUN_TEST(paragraph_preserves_logical_ranges_and_hard_boundaries);
    RUN_TEST(paragraph_does_not_break_inside_shaping_cluster);
    RUN_TEST(paragraph_does_not_break_inside_cross_face_combining_cluster);
    RUN_TEST(paragraph_shapes_bidi_runs_before_wrapping);
    RUN_TEST(paragraph_rejects_non_boundary_shape_cluster);
    RUN_TEST(text_layout_and_paragraph_reject_oversized_input_before_allocating);
    RUN_TEST(paragraph_process_n_uses_exact_utf8_slice);
    RUN_TEST(paragraph_process_n_rejects_embedded_nul);
    RUN_TEST(paragraph_shapes_only_current_physical_line);
    RUN_TEST(paragraph_consumes_bounded_sa_dictionary_options);
    RUN_TEST(paragraph_consumes_versioned_sa_dictionary_profile);
    RUN_TEST(paragraph_rejects_failed_sa_dictionary_transactionally);
    RUN_TEST(syntax_cache_lexes_bounded_tokens_and_comments);
    RUN_TEST(syntax_cache_records_utf8_token_byte_ranges);
    RUN_TEST(syntax_cache_propagates_state_only_from_dirty_suffix);
    RUN_TEST(syntax_cache_rejects_source_and_line_budget_overflow);
    RUN_TEST(syntax_cache_replacement_is_transactional);
TEST_MAIN_END()
