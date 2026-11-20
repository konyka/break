#ifndef MY_PAL_SCREEN_CURSOR_H
#define MY_PAL_SCREEN_CURSOR_H

#include "mypal/my_pal.h"

#define MY_SCREEN_CURSOR_WIDTH 16u
#define MY_SCREEN_CURSOR_HEIGHT 16u
#define MY_SCREEN_CURSOR_MAX_PIXELS \
  (MY_SCREEN_CURSOR_WIDTH * MY_SCREEN_CURSOR_HEIGHT)

typedef struct my_screen_cursor_t {
  my_cursor_t shape;
  int32_t x;
  int32_t y;
  bool enabled;
  bool has_position;
} my_screen_cursor_t;

void my_screen_cursor_init(my_screen_cursor_t* cursor);
void my_screen_cursor_set_enabled(my_screen_cursor_t* cursor, bool enabled);
my_ret_t my_screen_cursor_set_shape(my_screen_cursor_t* cursor,
                                    my_cursor_t shape);
void my_screen_cursor_set_position(my_screen_cursor_t* cursor, int32_t x,
                                   int32_t y);
my_ret_t my_screen_cursor_bounds(const my_screen_cursor_t* cursor,
                                 int32_t width, int32_t height,
                                 my_rect_t* out);
my_ret_t my_screen_cursor_composite(const my_screen_cursor_t* cursor,
                                    uint8_t* pixels, uint32_t stride,
                                    int32_t width, int32_t height,
                                    my_rect_t* out);

#endif
