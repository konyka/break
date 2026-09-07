#include "myr/my_ui_metrics.h"

my_ui_metrics_t g_myui_metrics;

static void metrics_add(uint64_t* value, uint64_t increment) {
  if (*value > UINT64_MAX - increment) {
    *value = UINT64_MAX;
  } else {
    *value += increment;
  }
}

void my_ui_metrics_set_enabled(bool enabled) {
  g_myui_metrics.enabled = enabled;
  if (!enabled) {
    g_myui_metrics.frame_depth = 0u;
    g_myui_metrics.in_frame = false;
  }
}

void my_ui_metrics_begin_frame(void) {
  if (!g_myui_metrics.enabled) return;
  if (g_myui_metrics.frame_depth == 0u) {
    g_myui_metrics.current = (my_ui_frame_metrics_sample_t){0};
    g_myui_metrics.in_frame = true;
  }
  if (g_myui_metrics.frame_depth < SIZE_MAX) {
    g_myui_metrics.frame_depth++;
  }
}

void my_ui_metrics_end_frame(void) {
  size_t index;
  if (!g_myui_metrics.enabled || !g_myui_metrics.in_frame ||
      g_myui_metrics.frame_depth == 0u) return;
  g_myui_metrics.frame_depth--;
  if (g_myui_metrics.frame_depth != 0u) return;
  index = g_myui_metrics.frame_index;
  g_myui_metrics.samples[index] = g_myui_metrics.current;
  g_myui_metrics.frame_index = (index + 1u) % MY_UI_METRICS_MAX_FRAMES;
  if (g_myui_metrics.frame_count < MY_UI_METRICS_MAX_FRAMES) {
    g_myui_metrics.frame_count++;
  }
  g_myui_metrics.in_frame = false;
}

void my_ui_metrics_abort_frame(void) {
  if (!g_myui_metrics.enabled) return;
  g_myui_metrics.frame_depth = 0u;
  g_myui_metrics.in_frame = false;
}

bool my_ui_metrics_get_last(my_ui_frame_metrics_sample_t* out) {
  size_t index;
  if (out == NULL || g_myui_metrics.frame_count == 0u) return false;
  index = (g_myui_metrics.frame_index + MY_UI_METRICS_MAX_FRAMES - 1u) %
          MY_UI_METRICS_MAX_FRAMES;
  *out = g_myui_metrics.samples[index];
  return true;
}

void my_ui_metrics_record_draw_call(void) {
  if (g_myui_metrics.enabled && g_myui_metrics.in_frame)
    metrics_add(&g_myui_metrics.current.draw_calls, 1u);
}

void my_ui_metrics_record_layout_pass(void) {
  if (g_myui_metrics.enabled && g_myui_metrics.in_frame)
    metrics_add(&g_myui_metrics.current.layout_passes, 1u);
}

void my_ui_metrics_record_damage(uint64_t area_pixels) {
  if (!g_myui_metrics.enabled || !g_myui_metrics.in_frame) return;
  metrics_add(&g_myui_metrics.current.damage_rects, 1u);
  metrics_add(&g_myui_metrics.current.damage_area_pixels, area_pixels);
}

void my_ui_metrics_record_atlas_miss(void) {
  if (g_myui_metrics.enabled && g_myui_metrics.in_frame)
    metrics_add(&g_myui_metrics.current.atlas_misses, 1u);
}

void my_ui_metrics_record_image_cache_miss(void) {
  if (g_myui_metrics.enabled && g_myui_metrics.in_frame)
    metrics_add(&g_myui_metrics.current.image_cache_misses, 1u);
}

void my_ui_metrics_record_fallback(void) {
  if (g_myui_metrics.enabled && g_myui_metrics.in_frame)
    metrics_add(&g_myui_metrics.current.fallbacks, 1u);
}
