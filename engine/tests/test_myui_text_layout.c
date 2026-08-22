#include "test_framework.h"

#include <string.h>

#include "myr/my_arabic_shape.h"
#include "myr/my_line_break.h"
#include "myr/my_text_layout.h"

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

TEST_MAIN_BEGIN()
    RUN_TEST(arabic_shape_forms_lam_alef);
    RUN_TEST(text_layout_maps_rtl_visual_order);
    RUN_TEST(text_layout_preserves_lam_alef_logical_boundaries);
    RUN_TEST(line_break_applies_unicode_context_rules);
TEST_MAIN_END()
