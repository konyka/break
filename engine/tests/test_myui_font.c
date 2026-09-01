#include "test_framework.h"

#include <stdio.h>
#include <stdlib.h>

#include "myr/my_font.h"
#include "myr/my_font_ft.h"

#ifdef MYUI_FONT_FREETYPE
typedef struct {
  const char *path;
  int face_index;
} CjkFontCandidate;

static const CjkFontCandidate *find_cjk_font(void) {
  static const CjkFontCandidate candidates[] = {
#if defined(_WIN32)
      {"C:/Windows/Fonts/msyh.ttc", 0},
#elif defined(__APPLE__)
      {"/System/Library/Fonts/PingFang.ttc", 0},
#else
      {"/usr/share/fonts/google-noto-sans-cjk-vf-fonts/NotoSansCJK-VF.ttc", 2},
      {"/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc", 2},
#endif
      {NULL, 0},
  };
  size_t i;

  for (i = 0; candidates[i].path != NULL; i++) {
    FILE *file = fopen(candidates[i].path, "rb");
    if (file != NULL) {
      fclose(file);
      return &candidates[i];
    }
  }
  return NULL;
}
#endif

typedef struct shape_allocator_state_t {
  size_t calls;
  size_t fail_at;
  size_t live;
} shape_allocator_state_t;

static bool shape_allocator_should_fail(shape_allocator_state_t* state) {
  state->calls++;
  return state->fail_at != 0 && state->calls == state->fail_at;
}

static void* shape_alloc(void* context, size_t size) {
  shape_allocator_state_t* state = (shape_allocator_state_t*)context;
  void* memory;
  if (shape_allocator_should_fail(state)) return NULL;
  memory = malloc(size);
  if (memory != NULL) state->live++;
  return memory;
}

static void* shape_calloc(void* context, size_t count, size_t size) {
  shape_allocator_state_t* state = (shape_allocator_state_t*)context;
  void* memory;
  if (shape_allocator_should_fail(state)) return NULL;
  memory = calloc(count, size);
  if (memory != NULL) state->live++;
  return memory;
}

static void* shape_realloc(void* context, void* old_memory, size_t size) {
  shape_allocator_state_t* state = (shape_allocator_state_t*)context;
  void* memory;
  if (shape_allocator_should_fail(state)) return NULL;
  memory = realloc(old_memory, size);
  if (memory != NULL && old_memory == NULL) state->live++;
  return memory;
}

static void shape_free(void* context, void* memory) {
  shape_allocator_state_t* state = (shape_allocator_state_t*)context;
  if (memory != NULL) {
    free(memory);
    state->live--;
  }
}

static my_ret_t shape_alloc_then_fail(my_font_t* font, const char* text,
                                      int32_t size, bool rtl,
                                      const my_allocator_t* allocator,
                                      my_font_shape_result_t* result) {
  (void)font;
  (void)text;
  (void)size;
  (void)rtl;
  result->allocator = allocator;
  result->glyphs = (my_font_shape_glyph_t*)my_mem_alloc(
      allocator, sizeof(*result->glyphs));
  if (result->glyphs == NULL) return MY_RET_OOM;
  result->allocator = NULL;
  result->count = 1;
  return MY_RET_FAIL;
}

static const my_font_vtable_t s_shape_failure_vtable = {
    .shape = shape_alloc_then_fail};

#ifdef MYUI_FONT_FREETYPE
static bool glyph_has_coverage(const my_glyph_t *glyph) {
  size_t i;
  size_t count;

  if (glyph->bitmap == NULL || glyph->w <= 0 || glyph->h <= 0) {
    return false;
  }
  count = (size_t)glyph->w * (size_t)glyph->h;
  for (i = 0; i < count; i++) {
    if (glyph->bitmap[i] != 0) {
      return true;
    }
  }
  return false;
}
#endif

TEST(utf8_decodes_chinese_codepoints)
{
  const char *text = "\xE7\x9F\xAD\xE7\xBA\xBF\xE4\xBE\xA0";

  ASSERT_EQ(my_utf8_next(&text), 0x77EDu);
  ASSERT_EQ(my_utf8_next(&text), 0x7EBFu);
  ASSERT_EQ(my_utf8_next(&text), 0x4FA0u);
  ASSERT_EQ(*text, '\0');
}

TEST(font_shape_cleans_partial_provider_results)
{
  shape_allocator_state_t state = {0};
  const my_allocator_t allocator = {&state, shape_alloc, shape_calloc,
                                    shape_realloc, shape_free};
  my_font_t font = {&s_shape_failure_vtable};
  my_font_shape_result_t result = {0};

  ASSERT_EQ(my_font_shape(&font, "a", 12, false, &allocator, &result),
            MY_RET_FAIL);
  ASSERT_EQ(result.count, 0u);
  ASSERT_TRUE(result.glyphs == NULL);
  ASSERT_EQ(state.live, 0u);
}

TEST(cjk_ttc_face_rasterizes_chinese_glyphs)
{
#ifdef MYUI_FONT_FREETYPE
  const CjkFontCandidate *candidate = find_cjk_font();
  const uint32_t codepoints[] = {0x77EDu, 0x7EBFu, 0x4FA0u};
  my_font_t *font;
  size_t i;

  if (candidate == NULL) {
    printf("  SKIP: no system CJK font\n");
    return;
  }
  {
    const my_font_source_t source = {candidate->path, candidate->face_index};
    font = my_font_create_chain_ex(NULL, &source, 1, 32);
  }
  ASSERT_NOT_NULL(font);
  for (i = 0; i < sizeof(codepoints) / sizeof(codepoints[0]); i++) {
    my_glyph_t glyph;
    ASSERT_TRUE(my_font_has_glyph(font, codepoints[i]));
    ASSERT_EQ(my_font_get_glyph(font, codepoints[i], 18, &glyph), MY_RET_OK);
    ASSERT_TRUE(glyph.advance > 0);
    ASSERT_TRUE(glyph_has_coverage(&glyph));
  }
  my_font_destroy(font);
#else
  printf("  SKIP: MYUI_FONT_FREETYPE is unavailable\n");
#endif
}

TEST(optional_opentype_shaping_has_explicit_fallback)
{
  my_font_shape_result_t result;
  my_font_t *font;
  const char *path = "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  memset(&result, 0, sizeof(result));
  if (file == NULL) {
    printf("  SKIP: no shaping test font\n");
    return;
  }
  fclose(file);
#ifdef MYUI_FONT_FREETYPE
  font = my_font_ft_create(NULL, path, 0, 32);
#else
  font = my_font_bitmap_create(NULL);
#endif
  ASSERT_NOT_NULL(font);
#ifdef MYUI_FONT_HARFBUZZ
  ASSERT_EQ(my_font_shape(font, "office", 24, false, NULL, &result),
            MY_RET_OK);
  ASSERT_EQ(result.count, 5u);
  ASSERT_TRUE(result.used_complex_shaping);
  ASSERT_EQ(result.glyphs[0].cluster, 0u);
  ASSERT_EQ(result.glyphs[1].cluster, 1u);
  ASSERT_EQ(result.glyphs[2].cluster, 2u);
  ASSERT_EQ(result.glyphs[3].cluster, 4u);
  ASSERT_EQ(result.glyphs[4].cluster, 5u);
  ASSERT_TRUE(result.glyphs[2].advance_x_26_6 > 0);
  my_font_shape_destroy(&result);
#else
  ASSERT_EQ(my_font_shape(font, "office", 24, false, NULL, &result),
            MY_RET_NOT_SUPPORTED);
#endif
  my_font_destroy(font);
}

TEST(shaped_glyph_id_rasterization_is_separate_from_unicode)
{
#ifdef MYUI_FONT_FREETYPE
  const char *path = "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_glyph_t glyph;
  if (file == NULL) {
    printf("  SKIP: no shaping test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(NULL, path, 0, 32);
  ASSERT_NOT_NULL(font);
#ifdef MYUI_FONT_HARFBUZZ
  my_font_shape_result_t shaped = {0};
  ASSERT_EQ(my_font_shape(font, "office", 24, false, NULL, &shaped),
            MY_RET_OK);
  ASSERT_TRUE(shaped.count > 0);
  ASSERT_EQ(my_font_get_glyph_id(font, shaped.glyphs[0].glyph_id, 24, &glyph),
            MY_RET_OK);
  ASSERT_TRUE(glyph.advance > 0);
  ASSERT_TRUE(glyph_has_coverage(&glyph));
  ASSERT_EQ(my_font_get_glyph_id(font, 0u, 24, &glyph), MY_RET_NOT_FOUND);
  my_font_shape_destroy(&shaped);
#else
  ASSERT_EQ(my_font_get_glyph_id(font, 1u, 24, &glyph), MY_RET_OK);
  ASSERT_TRUE(glyph.advance > 0);
#endif
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType is unavailable\n");
#endif
}

TEST(font_chain_preserves_face_identity_in_shaped_runs)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const CjkFontCandidate *cjk = find_cjk_font();
  const char *latin_path =
      "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  const my_font_source_t sources[] = {{latin_path, 0},
                                      {cjk != NULL ? cjk->path : NULL,
                                       cjk != NULL ? cjk->face_index : 0}};
  my_font_shape_result_t result = {0};
  my_font_t *font;
  FILE *file = fopen(latin_path, "rb");
  size_t i;

  if (file == NULL || cjk == NULL) {
    if (file != NULL) fclose(file);
    printf("  SKIP: no Latin/CJK shaping font pair\n");
    return;
  }
  fclose(file);
  font = my_font_create_chain_ex(NULL, sources, 2, 32);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape(font, "office\xE7\x9F\xAD", 24, false, NULL,
                          &result),
            MY_RET_OK);
  ASSERT_TRUE(result.count > 0);
  ASSERT_TRUE(result.used_complex_shaping);
  for (i = 0; i < result.count; i++) {
    ASSERT_NOT_NULL(result.glyphs[i].font);
    if (result.glyphs[i].cluster < 6u) {
      ASSERT_TRUE(result.glyphs[i].font == result.glyphs[0].font);
    } else {
      ASSERT_TRUE(result.glyphs[i].font != result.glyphs[0].font);
    }
  }
  my_font_shape_destroy(&result);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(font_chain_shaping_rolls_back_allocator_failures)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const CjkFontCandidate *cjk = find_cjk_font();
  const char *latin_path =
      "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  const my_font_source_t sources[] = {{latin_path, 0},
                                      {cjk != NULL ? cjk->path : NULL,
                                       cjk != NULL ? cjk->face_index : 0}};
  shape_allocator_state_t state = {0};
  const my_allocator_t allocator = {&state, shape_alloc, shape_calloc,
                                    shape_realloc, shape_free};
  my_font_shape_result_t result = {0};
  my_font_t *font;
  FILE *file = fopen(latin_path, "rb");
  size_t successful_calls;
  size_t fail_at;

  if (file == NULL || cjk == NULL) {
    if (file != NULL) fclose(file);
    printf("  SKIP: no Latin/CJK shaping font pair\n");
    return;
  }
  fclose(file);
  font = my_font_create_chain_ex(NULL, sources, 2, 32);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape(font, "office\xE7\x9F\xAD", 24, false,
                          &allocator, &result), MY_RET_OK);
  successful_calls = state.calls;
  ASSERT_TRUE(successful_calls > 0);
  my_font_shape_destroy(&result);
  ASSERT_EQ(state.live, 0u);

  for (fail_at = 1; fail_at <= successful_calls; fail_at++) {
    state.calls = 0;
    state.fail_at = fail_at;
    ASSERT_EQ(my_font_shape(font, "office\xE7\x9F\xAD", 24, false,
                            &allocator, &result), MY_RET_OOM);
    ASSERT_EQ(result.count, 0u);
    ASSERT_TRUE(result.glyphs == NULL);
    ASSERT_EQ(state.live, 0u);
  }
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(font_chain_rtl_reverses_cross_face_runs)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const CjkFontCandidate *cjk = find_cjk_font();
  const char *latin_path =
      "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  const my_font_source_t sources[] = {{latin_path, 0},
                                      {cjk != NULL ? cjk->path : NULL,
                                       cjk != NULL ? cjk->face_index : 0}};
  my_font_shape_result_t result = {0};
  my_font_t *font;
  FILE *file = fopen(latin_path, "rb");
  size_t i;
  bool saw_latin = false;
  bool saw_cjk_after_latin = false;

  if (file == NULL || cjk == NULL) {
    if (file != NULL) fclose(file);
    printf("  SKIP: no Latin/CJK shaping font pair\n");
    return;
  }
  fclose(file);
  font = my_font_create_chain_ex(NULL, sources, 2, 32);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape(font, "\xE7\x9F\xADoffice", 24, true, NULL,
                          &result), MY_RET_OK);
  ASSERT_TRUE(result.count > 0);
  for (i = 0; i < result.count; i++) {
    if (result.glyphs[i].cluster >= 3u) saw_latin = true;
    if (saw_latin && result.glyphs[i].cluster < 3u) {
      saw_cjk_after_latin = true;
    }
  }
  ASSERT_TRUE(saw_latin);
  ASSERT_TRUE(saw_cjk_after_latin);
  my_font_shape_destroy(&result);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST_MAIN_BEGIN()
    RUN_TEST(utf8_decodes_chinese_codepoints);
    RUN_TEST(font_shape_cleans_partial_provider_results);
    RUN_TEST(cjk_ttc_face_rasterizes_chinese_glyphs);
    RUN_TEST(optional_opentype_shaping_has_explicit_fallback);
    RUN_TEST(shaped_glyph_id_rasterization_is_separate_from_unicode);
    RUN_TEST(font_chain_preserves_face_identity_in_shaped_runs);
    RUN_TEST(font_chain_shaping_rolls_back_allocator_failures);
    RUN_TEST(font_chain_rtl_reverses_cross_face_runs);
TEST_MAIN_END()
