#include "test_framework.h"
#include "myui/echarts/my_echart_animation.h"

TEST(echart_animation_fake_clock_progress) {
  float progress = 0.0f;
  my_echart_animation_t* animation = my_echart_animation_create(NULL, 1000u);
  ASSERT_NOT_NULL(animation);
  ASSERT_EQ(my_echart_animation_start(animation, 100u), MY_RET_OK);
  ASSERT_TRUE(my_echart_animation_active(animation));
  ASSERT_EQ(my_echart_animation_tick(animation, 100u, &progress), MY_RET_OK);
  ASSERT_FLOAT_EQ(progress, 0.0f, 1e-6f);
  ASSERT_EQ(my_echart_animation_tick(animation, 600u, &progress), MY_RET_OK);
  ASSERT_FLOAT_EQ(progress, 0.5f, 1e-6f);
  ASSERT_EQ(my_echart_animation_tick(animation, 1100u, &progress), MY_RET_OK);
  ASSERT_FLOAT_EQ(progress, 1.0f, 1e-6f);
  ASSERT_FALSE(my_echart_animation_active(animation));
  my_echart_animation_destroy(animation);
}

TEST_MAIN_BEGIN()
  RUN_TEST(echart_animation_fake_clock_progress);
TEST_MAIN_END()
