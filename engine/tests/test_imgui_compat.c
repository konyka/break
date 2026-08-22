#include "test_framework.h"

#include "ui/imgui.h"
#include "myr/my_vgcanvas_break_rhi.h"
#include "myr/my_vgcanvas_break_rhi_internal.h"

TEST(imgui_button_clicks_on_release)
{
  ImUI ui = {0};
  ui.mouse_x = 20.0f;
  ui.mouse_y = 20.0f;
  ui.mouse_down = true;
  imui_init(&ui, NULL);
  imui_begin(&ui, 320.0f, 240.0f, 320.0f, 240.0f, 20.0f, 20.0f, true);
  imui_panel(&ui, 10.0f, 10.0f, 120.0f, 80.0f);
  ASSERT_TRUE(!imui_button(&ui, 1, "OK"));
  imui_end(&ui, NULL);

  imui_begin(&ui, 320.0f, 240.0f, 320.0f, 240.0f, 20.0f, 20.0f, false);
  imui_panel(&ui, 10.0f, 10.0f, 120.0f, 80.0f);
  ASSERT_TRUE(imui_button(&ui, 1, "OK"));
  imui_end(&ui, NULL);
}

TEST(imgui_controls_update_values)
{
  ImUI ui = {0};
  bool checked = false;
  bool open = false;
  i32 selected = 0;
  i32 level = 0;

  imui_init(&ui, NULL);
  imui_begin(&ui, 320.0f, 240.0f, 320.0f, 240.0f, 20.0f, 20.0f, true);
  imui_panel(&ui, 10.0f, 10.0f, 120.0f, 200.0f);
  ASSERT_TRUE(!imui_checkbox(&ui, 1, "check", &checked));
  imui_end(&ui, NULL);

  imui_begin(&ui, 320.0f, 240.0f, 320.0f, 240.0f, 20.0f, 20.0f, false);
  imui_panel(&ui, 10.0f, 10.0f, 120.0f, 200.0f);
  ASSERT_TRUE(imui_checkbox(&ui, 1, "check", &checked));
  ASSERT_TRUE(checked);
  imui_end(&ui, NULL);

  imui_begin(&ui, 320.0f, 240.0f, 320.0f, 240.0f, 20.0f, 20.0f, true);
  imui_panel(&ui, 10.0f, 10.0f, 120.0f, 200.0f);
  (void)imui_collapsing_header(&ui, 2, "group", &open);
  imui_end(&ui, NULL);
  imui_begin(&ui, 320.0f, 240.0f, 320.0f, 240.0f, 20.0f, 20.0f, false);
  imui_panel(&ui, 10.0f, 10.0f, 120.0f, 200.0f);
  ASSERT_TRUE(imui_collapsing_header(&ui, 2, "group", &open));
  ASSERT_TRUE(open);
  imui_end(&ui, NULL);

  imui_begin(&ui, 320.0f, 240.0f, 320.0f, 240.0f, 20.0f, 20.0f, true);
  imui_panel(&ui, 10.0f, 10.0f, 120.0f, 200.0f);
  (void)imui_radio(&ui, 3, "option", &selected, 7);
  imui_end(&ui, NULL);
  imui_begin(&ui, 320.0f, 240.0f, 320.0f, 240.0f, 20.0f, 20.0f, false);
  imui_panel(&ui, 10.0f, 10.0f, 120.0f, 200.0f);
  ASSERT_TRUE(imui_radio(&ui, 3, "option", &selected, 7));
  ASSERT_EQ(selected, 7);
  imui_end(&ui, NULL);

  imui_begin(&ui, 320.0f, 240.0f, 320.0f, 240.0f, 120.0f, 20.0f, true);
  imui_panel(&ui, 10.0f, 10.0f, 120.0f, 200.0f);
  ASSERT_TRUE(imui_slider_int(&ui, 4, "level", &level, 0, 3));
  ASSERT_EQ(level, 3);
  imui_end(&ui, NULL);

  imui_reset_input(&ui, false);
  ASSERT_EQ(ui.active_id, 0u);
}

TEST(break_rhi_resize_preserves_or_clamps_device_clip)
{
  my_rect_t clip;

  /* A default full clip must grow with its physical drawable. */
  clip = my_vgcanvas_break_rhi_resize_clip(my_rect_init(0, 0, 160, 80),
                                           160u, 80u, 320u, 180u);
  ASSERT_EQ(clip.x, 0);
  ASSERT_EQ(clip.y, 0);
  ASSERT_EQ(clip.w, 320);
  ASSERT_EQ(clip.h, 180);

  /* A caller-provided clip remains bounded after a surface shrink. */
  clip = my_vgcanvas_break_rhi_resize_clip(my_rect_init(80, 20, 120, 70),
                                           320u, 180u, 160u, 80u);
  ASSERT_EQ(clip.x, 80);
  ASSERT_EQ(clip.y, 20);
  ASSERT_EQ(clip.w, 80);
  ASSERT_EQ(clip.h, 60);
}

TEST(break_rhi_aa_levels_map_to_transactional_targets)
{
  ASSERT_TRUE(my_vgcanvas_break_rhi_aa_level_is_supported(0));
  ASSERT_TRUE(my_vgcanvas_break_rhi_aa_level_is_supported(2));
  ASSERT_TRUE(!my_vgcanvas_break_rhi_aa_level_is_supported(1));
  ASSERT_TRUE(!my_vgcanvas_break_rhi_aa_level_is_supported(3));
  ASSERT_EQ(my_vgcanvas_break_rhi_sample_count_for_aa_level(0), 1u);
  ASSERT_EQ(my_vgcanvas_break_rhi_sample_count_for_aa_level(2), 2u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(imgui_button_clicks_on_release);
    RUN_TEST(imgui_controls_update_values);
    RUN_TEST(break_rhi_resize_preserves_or_clamps_device_clip);
    RUN_TEST(break_rhi_aa_levels_map_to_transactional_targets);
TEST_MAIN_END()
