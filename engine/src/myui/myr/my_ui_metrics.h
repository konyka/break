/**
 * @file my_ui_metrics.h
 * @brief Optional, bounded per-frame MyUI performance counters.
 *
 * This is an owner-loop component, not a cross-thread profiler. Callers must
 * not read or modify the public state concurrently with recording.
 */
#ifndef MY_UI_METRICS_H
#define MY_UI_METRICS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MY_UI_METRICS_MAX_FRAMES 8u

typedef struct my_ui_frame_metrics_sample_t {
  uint64_t draw_calls;
  uint64_t layout_passes;
  uint64_t damage_rects;
  uint64_t damage_area_pixels;
  uint64_t atlas_misses;
  uint64_t image_cache_misses;
  uint64_t fallbacks;
} my_ui_frame_metrics_sample_t;

typedef struct my_ui_metrics_t {
  my_ui_frame_metrics_sample_t samples[MY_UI_METRICS_MAX_FRAMES];
  my_ui_frame_metrics_sample_t current;
  size_t frame_index;
  size_t frame_count;
  size_t frame_depth;
  bool enabled;
  bool in_frame;
} my_ui_metrics_t;

extern my_ui_metrics_t g_myui_metrics;

/** @brief Enable or disable recording; disabled recording performs no writes. */
void my_ui_metrics_set_enabled(bool enabled);

/** @brief Start a bounded metrics frame. No allocation or locking occurs. */
void my_ui_metrics_begin_frame(void);

/** @brief Publish the current sample to the fixed-size ring. */
void my_ui_metrics_end_frame(void);

/** @brief Discard the current frame, including nested frame scopes. */
void my_ui_metrics_abort_frame(void);

/** @brief Copy the newest completed sample. Returns false when none exists. */
bool my_ui_metrics_get_last(my_ui_frame_metrics_sample_t* out);

/** @brief Record one logical MyUI draw operation, not a backend GPU call. */
void my_ui_metrics_record_draw_call(void);
void my_ui_metrics_record_layout_pass(void);
/** @brief Record a logical dirty rectangle and its logical-pixel area. */
void my_ui_metrics_record_damage(uint64_t area_pixels);
/** @brief Record a glyph atlas/cache miss. */
void my_ui_metrics_record_atlas_miss(void);
void my_ui_metrics_record_image_cache_miss(void);
/** @brief Record a font-chain fallback selection. */
void my_ui_metrics_record_fallback(void);

#endif /* MY_UI_METRICS_H */
