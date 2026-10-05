#include "myui/echarts/my_echart_animation.h"

#include <string.h>

struct my_echart_animation_t {
  const my_allocator_t* allocator;
  uint64_t duration_ms;
  uint64_t start_ms;
  bool active;
};

my_echart_animation_t* my_echart_animation_create(const my_allocator_t* allocator,
                                                  uint64_t duration_ms) {
  my_echart_animation_t* animation;
  if (duration_ms == 0u) return NULL;
  animation = (my_echart_animation_t*)my_mem_calloc(allocator, 1u,
                                                     sizeof(*animation));
  if (animation == NULL) return NULL;
  animation->allocator = allocator;
  animation->duration_ms = duration_ms;
  return animation;
}

void my_echart_animation_destroy(my_echart_animation_t* animation) {
  if (animation != NULL) my_mem_free(animation->allocator, animation);
}

my_ret_t my_echart_animation_start(my_echart_animation_t* animation,
                                   uint64_t now_ms) {
  if (animation == NULL) return MY_RET_INVALID_PARAMS;
  animation->start_ms = now_ms;
  animation->active = true;
  return MY_RET_OK;
}

my_ret_t my_echart_animation_tick(my_echart_animation_t* animation,
                                  uint64_t now_ms, float* progress) {
  uint64_t elapsed;
  if (animation == NULL || progress == NULL) return MY_RET_INVALID_PARAMS;
  if (!animation->active) { *progress = 1.0f; return MY_RET_OK; }
  elapsed = now_ms >= animation->start_ms ? now_ms - animation->start_ms : 0u;
  if (elapsed >= animation->duration_ms) {
    animation->active = false;
    *progress = 1.0f;
  } else {
    *progress = (float)elapsed / (float)animation->duration_ms;
  }
  return MY_RET_OK;
}

my_ret_t my_echart_animation_reset(my_echart_animation_t* animation) {
  if (animation == NULL) return MY_RET_INVALID_PARAMS;
  animation->active = false;
  animation->start_ms = 0u;
  return MY_RET_OK;
}

bool my_echart_animation_active(const my_echart_animation_t* animation) {
  return animation != NULL && animation->active;
}
