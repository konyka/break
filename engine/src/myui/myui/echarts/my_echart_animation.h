#ifndef MY_ECHART_ANIMATION_H
#define MY_ECHART_ANIMATION_H

#include "myc/my_error.h"
#include "myc/my_mem.h"

typedef struct my_echart_animation_t my_echart_animation_t;

my_echart_animation_t* my_echart_animation_create(const my_allocator_t* allocator,
                                                  uint64_t duration_ms);
void my_echart_animation_destroy(my_echart_animation_t* animation);
my_ret_t my_echart_animation_start(my_echart_animation_t* animation,
                                   uint64_t now_ms);
my_ret_t my_echart_animation_tick(my_echart_animation_t* animation,
                                  uint64_t now_ms, float* progress);
my_ret_t my_echart_animation_reset(my_echart_animation_t* animation);
bool my_echart_animation_active(const my_echart_animation_t* animation);

#endif
