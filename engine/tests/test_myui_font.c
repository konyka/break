#include "test_framework.h"

#include <stdio.h>

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

TEST_MAIN_BEGIN()
    RUN_TEST(utf8_decodes_chinese_codepoints);
    RUN_TEST(cjk_ttc_face_rasterizes_chinese_glyphs);
    RUN_TEST(optional_opentype_shaping_has_explicit_fallback);
TEST_MAIN_END()
