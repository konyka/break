#include "mypal/screen/my_pal_screen_cursor.h"

static const char s_arrow[MY_SCREEN_CURSOR_HEIGHT][MY_SCREEN_CURSOR_WIDTH + 1u] = {
    "#", "##", "#.#", "#..#", "#...#", "#....#", "#.....#", "#......#",
    "#.......#", "#........#", "#.....#####", "#..#..#", "#.#  #.#",
    "##    #.#", "#      ##", ""};

static const char s_text[MY_SCREEN_CURSOR_HEIGHT][MY_SCREEN_CURSOR_WIDTH + 1u] = {
    "   #########", "      ###", "       #", "       #", "       #",
    "       #", "       #", "       #", "       #", "       #",
    "       #", "       #", "       #", "      ###", "   #########", ""};

static const char s_hand[MY_SCREEN_CURSOR_HEIGHT][MY_SCREEN_CURSOR_WIDTH + 1u] = {
    "    ##", "   #..#", "   #..#", "   #..# ###", "   #..##..##",
    "   #..##..#.#", "   #..##..#.#", "   #........#", "   #........#",
    "    .......#", "    .......#", "     ......#", "     ......#",
    "      #####", "", ""};

void my_screen_cursor_init(my_screen_cursor_t* cursor) {
  if (cursor == NULL) return;
  cursor->shape = MY_CURSOR_ARROW;
  cursor->x = 0;
  cursor->y = 0;
  cursor->enabled = false;
  cursor->has_position = false;
}

void my_screen_cursor_set_enabled(my_screen_cursor_t* cursor, bool enabled) {
  if (cursor != NULL) cursor->enabled = enabled;
}

my_ret_t my_screen_cursor_set_shape(my_screen_cursor_t* cursor,
                                    my_cursor_t shape) {
  if (cursor == NULL) return MY_RET_INVALID_PARAMS;
  if (shape != MY_CURSOR_ARROW && shape != MY_CURSOR_TEXT &&
      shape != MY_CURSOR_HAND) {
    return MY_RET_INVALID_PARAMS;
  }
  cursor->shape = shape;
  return MY_RET_OK;
}

void my_screen_cursor_set_position(my_screen_cursor_t* cursor, int32_t x,
                                   int32_t y) {
  if (cursor == NULL) return;
  cursor->x = x;
  cursor->y = y;
  cursor->has_position = true;
}

static void screen_cursor_hotspot(my_cursor_t shape, int32_t* x, int32_t* y) {
  *x = shape == MY_CURSOR_TEXT ? 7 : shape == MY_CURSOR_HAND ? 4 : 0;
  *y = shape == MY_CURSOR_TEXT ? 7 : 0;
}

my_ret_t my_screen_cursor_bounds(const my_screen_cursor_t* cursor,
                                 int32_t width, int32_t height,
                                 my_rect_t* out) {
  int32_t hotspot_x;
  int32_t hotspot_y;
  int64_t left;
  int64_t top;
  int64_t right;
  int64_t bottom;
  int64_t clipped_right;
  int64_t clipped_bottom;
  if (out == NULL) return MY_RET_INVALID_PARAMS;
  *out = my_rect_init(0, 0, 0, 0);
  if (cursor == NULL || width < 0 || height < 0 ||
      (cursor->shape != MY_CURSOR_ARROW && cursor->shape != MY_CURSOR_TEXT &&
       cursor->shape != MY_CURSOR_HAND)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (!cursor->enabled || !cursor->has_position || width == 0 || height == 0) {
    return MY_RET_OK;
  }
  screen_cursor_hotspot(cursor->shape, &hotspot_x, &hotspot_y);
  left = (int64_t)cursor->x - hotspot_x;
  top = (int64_t)cursor->y - hotspot_y;
  right = left + MY_SCREEN_CURSOR_WIDTH;
  bottom = top + MY_SCREEN_CURSOR_HEIGHT;
  if (right <= 0 || bottom <= 0 || left >= width || top >= height) {
    return MY_RET_OK;
  }
  clipped_right = right < width ? right : width;
  clipped_bottom = bottom < height ? bottom : height;
  out->x = (int32_t)left;
  out->y = (int32_t)top;
  out->w = (int32_t)(clipped_right - (left < 0 ? 0 : left));
  out->h = (int32_t)(clipped_bottom - (top < 0 ? 0 : top));
  return MY_RET_OK;
}

my_ret_t my_screen_cursor_composite(const my_screen_cursor_t* cursor,
                                    uint8_t* pixels, uint32_t stride,
                                    int32_t width, int32_t height,
                                    my_rect_t* out) {
  const char(*glyph)[MY_SCREEN_CURSOR_WIDTH + 1u];
  my_ret_t result;
  int32_t source_x;
  int32_t source_y;
  int32_t destination_x;
  int32_t destination_y;
  int32_t row;
  if (out == NULL) return MY_RET_INVALID_PARAMS;
  *out = my_rect_init(0, 0, 0, 0);
  if (pixels == NULL || cursor == NULL || width < 0 || height < 0 ||
      (uint64_t)stride < (uint64_t)(uint32_t)width * 4u) {
    return MY_RET_INVALID_PARAMS;
  }
  result = my_screen_cursor_bounds(cursor, width, height, out);
  if (result != MY_RET_OK || my_rect_is_empty(out)) return result;
  glyph = cursor->shape == MY_CURSOR_TEXT
              ? s_text
              : cursor->shape == MY_CURSOR_HAND ? s_hand : s_arrow;
  source_x = out->x < 0 ? -out->x : 0;
  source_y = out->y < 0 ? -out->y : 0;
  destination_x = out->x < 0 ? 0 : out->x;
  destination_y = out->y < 0 ? 0 : out->y;
  for (row = 0; row < out->h; ++row) {
    int32_t column;
    for (column = 0; column < out->w; ++column) {
      char pixel = glyph[source_y + row][source_x + column];
      uint8_t* destination;
      if (pixel != '#' && pixel != '.') continue;
      destination = pixels + (size_t)(uint32_t)(destination_y + row) * stride +
                    (size_t)(uint32_t)(destination_x + column) * 4u;
      destination[0] = pixel == '#' ? 0u : 255u;
      destination[1] = pixel == '#' ? 0u : 255u;
      destination[2] = pixel == '#' ? 0u : 255u;
      destination[3] = 255u;
    }
  }
  return MY_RET_OK;
}
