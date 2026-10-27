#include "test_framework.h"
#include "mypal/screen/my_pal_screen.h"
#include <platform/time.h>
#include <screen/screen.h>

#define SCREEN_TEST_WIDTH 320
#define SCREEN_TEST_HEIGHT 180
#define SCREEN_BENCH_FRAMES 64u
#define SCREEN_BENCH_ROUNDS 5u

#define CHECK(x) do { \
  if (!(x)) { \
    printf("  FAIL: %s:%d: %s\n", __FILE__, __LINE__, #x); \
    g_test_fail++; \
  } \
} while (0)

typedef struct counting_allocator_t {
  my_allocator_t base;
  my_allocator_t* debug;
  size_t allocations;
  size_t frees;
} counting_allocator_t;

static uint32_t pointer_queries;
static uint32_t stride_queries;
static uint32_t post_calls;
static uint32_t rect_errors;
static uint32_t content_errors;
static int expected_rect_count;
static int expected_rect[4];

static void* counting_alloc(void* context, size_t size) {
  counting_allocator_t* state = (counting_allocator_t*)context;
  state->allocations++;
  return my_mem_alloc(state->debug, size);
}

static void* counting_calloc(void* context, size_t count, size_t size) {
  counting_allocator_t* state = (counting_allocator_t*)context;
  state->allocations++;
  return my_mem_calloc(state->debug, count, size);
}

static void* counting_realloc(void* context, void* pointer, size_t size) {
  counting_allocator_t* state = (counting_allocator_t*)context;
  state->allocations++;
  return my_mem_realloc(state->debug, pointer, size);
}

static void counting_free(void* context, void* pointer) {
  counting_allocator_t* state = (counting_allocator_t*)context;
  if (pointer != NULL) state->frees++;
  my_mem_free(state->debug, pointer);
}

static void counting_allocator_init(counting_allocator_t* state) {
  memset(state, 0, sizeof(*state));
  state->debug = my_allocator_debug_create(NULL);
  state->base.ctx = state;
  state->base.alloc = counting_alloc;
  state->base.calloc = counting_calloc;
  state->base.realloc = counting_realloc;
  state->base.free = counting_free;
}

static void reset_native_counters(void) {
  pointer_queries = 0u;
  stride_queries = 0u;
  post_calls = 0u;
}

int __real_screen_get_buffer_property_pv(screen_buffer_t buffer, int property,
                                         void** value);
int __real_screen_get_buffer_property_iv(screen_buffer_t buffer, int property,
                                         int* value);
int __real_screen_post_window(screen_window_t window, screen_buffer_t buffer,
                              int count, const int* rects, int flags);

int __wrap_screen_get_buffer_property_pv(screen_buffer_t buffer, int property,
                                         void** value) {
  if (property == SCREEN_PROPERTY_POINTER) pointer_queries++;
  return __real_screen_get_buffer_property_pv(buffer, property, value);
}

int __wrap_screen_get_buffer_property_iv(screen_buffer_t buffer, int property,
                                         int* value) {
  if (property == SCREEN_PROPERTY_STRIDE) stride_queries++;
  return __real_screen_get_buffer_property_iv(buffer, property, value);
}

int __wrap_screen_post_window(screen_window_t window, screen_buffer_t buffer,
                              int count, const int* rects, int flags) {
  post_calls++;
  if (count != expected_rect_count || flags != SCREEN_DONT_BLOCK) rect_errors++;
  if (count > 0) {
    if (rects == NULL || rects[0] != expected_rect[0] ||
        rects[1] != expected_rect[1] || rects[2] != expected_rect[2] ||
        rects[3] != expected_rect[3]) {
      rect_errors++;
    }
  } else if (rects != NULL) {
    rect_errors++;
  }
  return __real_screen_post_window(window, buffer, count, rects, flags);
}

typedef struct pixel_buffer_state_t {
  uint8_t* pixels;
} pixel_buffer_state_t;

static pixel_buffer_state_t pixel_buffers[2];
static uint32_t pixel_buffer_count;
static uint8_t latest_damage_shade;

static bool draw_frame(my_lcd_t* lcd, const my_rect_t* damage,
                       const my_rect_t* drawing, uint8_t shade,
                       bool verify, uint64_t* elapsed_us) {
  const my_rect_t small_damage = {7, 9, 16, 12};
  uint64_t started_us = time_microseconds();
  uint64_t deadline_us = started_us + 2000000u;
  my_ret_t result;
  uint8_t* pixels;
  uint32_t stride;
  uint32_t slot;
  bool valid;
  expected_rect_count = damage != NULL ? 1 : 0;
  expected_rect[0] = small_damage.x;
  expected_rect[1] = small_damage.y;
  expected_rect[2] = small_damage.w;
  expected_rect[3] = small_damage.h;
  do {
    result = my_lcd_begin_frame(lcd, damage);
    if (result == MY_RET_PENDING) {
      time_sleep_us(100u);
    }
  } while (result == MY_RET_PENDING && time_microseconds() < deadline_us);
  if (result != MY_RET_OK) {
    printf("  Screen begin failed: %d\n", result);
    return false;
  }
  pixels = my_lcd_get_buffer(lcd);
  stride = my_lcd_get_stride(lcd);
  valid = pixels != NULL && stride >= my_lcd_get_width(lcd) * 4u;
  for (slot = 0u; valid && slot < pixel_buffer_count; ++slot) {
    if (pixel_buffers[slot].pixels == pixels) break;
  }
  if (valid && verify) {
    valid = slot < pixel_buffer_count &&
            pixels[small_damage.y * stride + small_damage.x * 4u] ==
                latest_damage_shade;
  } else if (valid && slot == pixel_buffer_count) {
    if (pixel_buffer_count >= 2u) {
      valid = false;
    } else {
      pixel_buffers[pixel_buffer_count].pixels = pixels;
      pixel_buffer_count++;
    }
  }
  if (!valid) {
    printf("  Screen content mismatch: slot=%u buffers=%u pixels=%p "
           "background=%u dirty=%u expected=%u\n",
           slot, pixel_buffer_count, (void*)pixels,
           pixels != NULL ? pixels[0] : 0u,
           pixels != NULL && stride >= my_lcd_get_width(lcd) * 4u
               ? pixels[small_damage.y * stride + small_damage.x * 4u]
               : 0u,
           latest_damage_shade);
    content_errors++;
    (void)my_lcd_end_frame(lcd);
    return false;
  }
  result = my_lcd_fill_rect(lcd, drawing,
                            my_color_rgba(shade, shade, shade, 255u));
  if (result == MY_RET_OK) result = my_lcd_end_frame(lcd);
  if (elapsed_us != NULL) *elapsed_us = time_microseconds() - started_us;
  if (result != MY_RET_OK) {
    printf("  Screen draw/post failed: %d\n", result);
    return false;
  }
  latest_damage_shade = shade;
  return true;
}

static bool prime_buffers(my_pal_window_t* window) {
  const my_rect_t full = {0, 0, SCREEN_TEST_WIDTH, SCREEN_TEST_HEIGHT};
  my_lcd_t* lcd = my_pal_window_get_lcd(window);
  uint32_t i;
  if (lcd == NULL) return false;
  pixel_buffer_count = 0u;
  for (i = 0u; i < 2u; ++i) {
    if (!draw_frame(lcd, NULL, &full, 16u, false, NULL)) return false;
  }
  return pixel_buffer_count == 2u;
}

static int uint64_compare(const void* left, const void* right) {
  uint64_t a = *(const uint64_t*)left;
  uint64_t b = *(const uint64_t*)right;
  return a < b ? -1 : a > b ? 1 : 0;
}

TEST(screen_damage_and_buffer_reuse)
{
  const my_rect_t damage = {7, 9, 16, 12};
  counting_allocator_t allocator;
  my_pal_t* pal = NULL;
  my_pal_window_t* window = NULL;
  my_lcd_t* lcd;
  uint32_t i = 0u;
  counting_allocator_init(&allocator);
  CHECK(allocator.debug != NULL);
  if (allocator.debug == NULL) return;
  pal = my_pal_create(&allocator.base);
  CHECK(pal != NULL && my_pal_screen_native_context(pal) != NULL);
  if (pal != NULL) {
    window = my_pal_window_create(pal, SCREEN_TEST_WIDTH, SCREEN_TEST_HEIGHT,
                                 "myui Screen buffer reuse");
    CHECK(window != NULL);
  }
  if (window != NULL && my_pal_window_show(window) == MY_RET_OK &&
      prime_buffers(window)) {
    lcd = my_pal_window_get_lcd(window);
    allocator.allocations = 0u;
    allocator.frees = 0u;
    reset_native_counters();
    rect_errors = 0u;
    content_errors = 0u;
    for (i = 0u; i < 8u; ++i) {
      if (!draw_frame(lcd, &damage, &damage, (uint8_t)(32u + i), true,
                      NULL)) {
        break;
      }
    }
  }
  CHECK(i == 8u);
  CHECK(content_errors == 0u);
  CHECK(rect_errors == 0u);
  CHECK(my_pal_screen_test_post_count(window) == 10u);
  CHECK(allocator.allocations == 0u);
  CHECK(allocator.frees == 0u);
  CHECK(pointer_queries == 0u);
  CHECK(stride_queries == 0u);
  if (window != NULL) my_pal_window_destroy(window);
  if (pal != NULL) my_pal_destroy(pal);
  CHECK(my_allocator_debug_leak_count(allocator.debug) == 0);
  my_allocator_debug_destroy(allocator.debug);
}

TEST(screen_history_survives_alternating_damage)
{
  const my_rect_t regions[2] = {{3, 4, 5, 6}, {29, 24, 7, 8}};
  my_pal_t* pal = my_pal_create(NULL);
  my_pal_window_t* window = NULL;
  my_lcd_t* lcd = NULL;
  uint8_t colors[2][4] = {{16u, 16u, 16u, 255u}, {16u, 16u, 16u, 255u}};
  uint32_t completed = 0u;
  uint32_t i;
  int swap_interval = 0;
  bool ready;
  rect_errors = 0u;
  content_errors = 0u;
  CHECK(pal != NULL && my_pal_screen_native_context(pal) != NULL);
  if (pal != NULL) {
    window = my_pal_window_create(pal, 48, 40, "myui Screen frame history");
    CHECK(window != NULL);
  }
  ready = window != NULL &&
          screen_set_window_property_iv(
              (screen_window_t)my_pal_screen_native_window(window),
              SCREEN_PROPERTY_SWAP_INTERVAL, &swap_interval) == 0 &&
          screen_flush_context(
              (screen_context_t)my_pal_screen_native_context(pal), 0) == 0 &&
          my_pal_window_show(window) == MY_RET_OK && prime_buffers(window);
  CHECK(ready);
  if (ready) {
    lcd = my_pal_window_get_lcd(window);
    for (i = 0u; i < 8u; ++i) {
      const my_rect_t* damage = &regions[i % 2u];
      uint8_t color[4] = {(uint8_t)(32u + i), (uint8_t)(64u + i),
                          (uint8_t)(96u + i), 255u};
      uint64_t deadline_us = time_microseconds() + 2000000u;
      my_ret_t result;
      uint8_t* pixels;
      uint32_t stride;
      uint32_t region;
      uint32_t channel;
      bool valid;
      expected_rect_count = 1;
      expected_rect[0] = damage->x;
      expected_rect[1] = damage->y;
      expected_rect[2] = damage->w;
      expected_rect[3] = damage->h;
      do {
        result = my_lcd_begin_frame(lcd, damage);
        if (result == MY_RET_PENDING) time_sleep_us(100u);
      } while (result == MY_RET_PENDING && time_microseconds() < deadline_us);
      if (result != MY_RET_OK) break;
      pixels = my_lcd_get_buffer(lcd);
      stride = my_lcd_get_stride(lcd);
      valid = pixels != NULL && stride >= 48u * 4u && pixels[0] == 16u;
      for (region = 0u; valid && region < 2u; ++region) {
        size_t offset = (size_t)regions[region].y * stride +
                        (size_t)regions[region].x * 4u;
        for (channel = 0u; valid && channel < 4u; ++channel) {
          valid = pixels[offset + channel] == colors[region][channel];
        }
      }
      if (!valid) {
        printf("  Screen lost frame history at frame=%u region=%u\n", i,
               region < 2u ? region : 2u);
        content_errors++;
        (void)my_lcd_end_frame(lcd);
        break;
      }
      result = my_lcd_fill_rect(
          lcd, damage, my_color_rgba(color[0], color[1], color[2], color[3]));
      if (result == MY_RET_OK) result = my_lcd_end_frame(lcd);
      if (result != MY_RET_OK) break;
      memcpy(colors[i % 2u], color, sizeof(color));
      completed++;
    }
  }
  CHECK(completed == 8u);
  CHECK(content_errors == 0u);
  CHECK(rect_errors == 0u);
  CHECK(my_pal_screen_test_post_count(window) == 10u);
  if (window != NULL) my_pal_window_destroy(window);
  if (pal != NULL) my_pal_destroy(pal);
}

TEST(screen_present_throughput)
{
  const my_rect_t damage = {7, 9, 16, 12};
  my_pal_t* pal = my_pal_create(NULL);
  my_pal_window_t* window = NULL;
  my_lcd_t* lcd;
  uint32_t sequence = 0u;
  uint32_t mode;
  int swap_interval = 0;
  rect_errors = 0u;
  content_errors = 0u;
  CHECK(pal != NULL && my_pal_screen_native_context(pal) != NULL);
  if (pal != NULL) {
    window = my_pal_window_create(pal, SCREEN_TEST_WIDTH, SCREEN_TEST_HEIGHT,
                                 "myui Screen present benchmark");
    CHECK(window != NULL);
  }
  if (window == NULL ||
      screen_set_window_property_iv(
          (screen_window_t)my_pal_screen_native_window(window),
          SCREEN_PROPERTY_SWAP_INTERVAL, &swap_interval) != 0 ||
      screen_flush_context((screen_context_t)my_pal_screen_native_context(pal),
                           0) != 0 ||
      my_pal_window_show(window) != MY_RET_OK || !prime_buffers(window)) {
    CHECK(false);
    if (window != NULL) my_pal_window_destroy(window);
    if (pal != NULL) my_pal_destroy(pal);
    return;
  }
  printf("screen_present_config,swap_interval=0,frames_are_accepted_posts=1\n");
  lcd = my_pal_window_get_lcd(window);
  for (mode = 0u; mode < 2u; ++mode) {
    uint64_t rounds[SCREEN_BENCH_ROUNDS];
    uint64_t max_frame_us = 0u;
    uint32_t round;
    uint32_t completed = 0u;
    uint32_t accepted_before = my_pal_screen_test_post_count(window);
    bool valid = true;
    reset_native_counters();
    for (round = 0u; round < SCREEN_BENCH_ROUNDS; ++round) {
      uint64_t started_us = time_microseconds();
      uint32_t completed_frames;
      uint32_t frame;
      for (frame = 0u; frame < SCREEN_BENCH_FRAMES; ++frame) {
        uint8_t shade = (uint8_t)(32u + sequence % 64u);
        uint64_t frame_us = 0u;
        if (!draw_frame(lcd, mode == 0u ? &damage : NULL, &damage, shade,
                        true, &frame_us)) {
          valid = false;
          break;
        }
        if (frame_us > max_frame_us) max_frame_us = frame_us;
        sequence++;
      }
      completed_frames = valid ? SCREEN_BENCH_FRAMES : frame;
      rounds[round] = time_microseconds() - started_us;
      printf("screen_present_round,mode=%s,round=%u,frames=%u,elapsed_us=%llu,"
             "accepted_per_second=%llu\n",
             mode == 0u ? "small_damage" : "full_damage", round + 1u,
             completed_frames, (unsigned long long)rounds[round],
             (unsigned long long)(completed_frames * 1000000u /
                                  (rounds[round] != 0u ? rounds[round] : 1u)));
      if (!valid) break;
      completed++;
    }
    CHECK(valid);
    CHECK(my_pal_screen_test_post_count(window) ==
          accepted_before + SCREEN_BENCH_FRAMES * SCREEN_BENCH_ROUNDS);
    if (valid) {
      qsort(rounds, completed, sizeof(rounds[0]), uint64_compare);
      printf("screen_present_summary,mode=%s,frames_per_round=%u,rounds=%u,"
             "median_us=%llu,median_accepted_per_second=%llu,max_frame_us=%llu,"
             "pointer_queries=%u,stride_queries=%u,post_calls=%u\n",
             mode == 0u ? "small_damage" : "full_damage", SCREEN_BENCH_FRAMES,
             completed, (unsigned long long)rounds[completed / 2u],
             (unsigned long long)(SCREEN_BENCH_FRAMES * 1000000u /
                                  (rounds[completed / 2u] != 0u
                                       ? rounds[completed / 2u]
                                       : 1u)),
             (unsigned long long)max_frame_us, pointer_queries, stride_queries,
             post_calls);
    } else {
      printf("screen_present_summary,mode=%s,status=failed,"
             "completed_rounds=%u\n",
             mode == 0u ? "small_damage" : "full_damage", completed);
    }
  }
  CHECK(rect_errors == 0u);
  CHECK(content_errors == 0u);
  my_pal_window_destroy(window);
  my_pal_destroy(pal);
}

int main(void)
{
  my_pal_t* probe;
  setvbuf(stdout, NULL, _IONBF, 0);
  time_init();
  probe = my_pal_create(NULL);
  if (probe == NULL || my_pal_screen_native_context(probe) == NULL) {
    if (probe != NULL) my_pal_destroy(probe);
    printf("SKIP: no usable QNX Screen service\n");
    return getenv("BREAK_QNX_SCREEN_REQUIRED") != NULL ? 1 : 77;
  }
  my_pal_destroy(probe);
  printf("=== Running Tests ===\n");
  RUN_TEST(screen_damage_and_buffer_reuse);
  RUN_TEST(screen_history_survives_alternating_damage);
  RUN_TEST(screen_present_throughput);
  printf("\n=== Results: %d passed, %d failed, %d total ===\n",
         g_test_pass, g_test_fail, g_test_count);
  return g_test_fail > 0 ? 1 : 0;
}
