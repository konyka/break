/**
 * @file my_font_ft.c
 * @brief FreeType font backend (M16): hinted glyph rendering with an
 * LRU cache (same structure as the stb backend).
 */
#include "myr/my_font_ft.h"
#include "myr/my_ui_metrics.h"

#ifdef MYUI_FONT_FREETYPE

#include <string.h>
#include <stdatomic.h>

#include "core/platform_thread.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MULTIPLE_MASTERS_H
#ifdef MYUI_FONT_HARFBUZZ
#include <hb.h>
#include <hb-ft.h>
#include <hb-ot.h>
#endif

#define MY_FONT_FT_DEFAULT_CACHE 256
#define MY_FONT_FT_SHAPE_SUPPORT_CACHE_CAPACITY 16

typedef struct my_font_ft_t my_font_ft_t;

typedef struct ft_shape_support_cache_entry_t {
  uint32_t script;
  char language[MY_FONT_SHAPE_MAX_LANGUAGE_BYTES + 1u];
  char features[MY_FONT_SHAPE_MAX_FEATURE_BYTES + 1u];
  my_font_shape_support_t support;
  uint64_t last_used;
  bool occupied;
} ft_shape_support_cache_entry_t;

typedef struct ft_cache_entry_t {
  uint32_t codepoint;
  bool key_is_glyph_id;
  int32_t size;
  uint8_t* bitmap; /**< owned, w*h bytes (NULL for blank) */
  int32_t w, h, bearing_x, bearing_y, advance;
  uint64_t last_used;
  size_t references;
  bool occupied;
  bool cached;
  const my_allocator_t* allocator;
  PlatformMutex* mutex;
  my_font_ft_t* owner;
  struct ft_cache_entry_t* next_overflow;
} ft_cache_entry_t;

struct my_font_ft_t {
  my_font_t base;
  const my_allocator_t* allocator;
  FT_Face face;
  int32_t cur_size; /**< last FT_Set_Pixel_Sizes size (0 = unset) */
  ft_cache_entry_t* cache;
  size_t cache_capacity;
  uint64_t tick;
  size_t hits;
  size_t misses;
  ft_shape_support_cache_entry_t shape_support_cache
      [MY_FONT_FT_SHAPE_SUPPORT_CACHE_CAPACITY];
  uint64_t shape_support_tick;
  size_t shape_support_cache_hits;
  ft_cache_entry_t* overflow_entries;
  size_t overflow_count;
  size_t lease_count;
  bool destroy_requested;
  PlatformMutex mutex;
};

#ifdef MYUI_FONT_HARFBUZZ
static char ft_ascii_lower(char value) {
  return value >= 'A' && value <= 'Z' ? (char)(value - 'A' + 'a') : value;
}

static bool ft_normalize_language_tag(const char* input, char* output,
                                      size_t output_size) {
  size_t length;
  size_t i;
  if (input == NULL || output == NULL || output_size == 0u) return false;
  length = strlen(input);
  if (length + 1u > output_size) return false;
  for (i = 0u; i < length; i++) {
    output[i] = ft_ascii_lower(input[i]);
  }
  output[length] = '\0';
  return true;
}
#endif

/** @brief One process-wide library is initialized once for all faces. */
static FT_Library s_ft_lib;
static int s_ft_lib_state; /**< 0 = untried, 1 = ready, -1 = failed */
static atomic_flag s_ft_lib_lock = ATOMIC_FLAG_INIT;

static FT_Library ft_library(void) {
  while (atomic_flag_test_and_set_explicit(&s_ft_lib_lock,
                                            memory_order_acquire)) {
    platform_thread_yield();
  }
  if (s_ft_lib_state == 0) {
    s_ft_lib_state = FT_Init_FreeType(&s_ft_lib) == 0 ? 1 : -1;
  }
  {
    FT_Library library = s_ft_lib_state == 1 ? s_ft_lib : NULL;
    atomic_flag_clear_explicit(&s_ft_lib_lock, memory_order_release);
    return library;
  }
}

static my_ret_t ft_set_size(my_font_ft_t* f, int32_t size) {
  if (f->cur_size != size) {
    if (FT_Set_Pixel_Sizes(f->face, 0, (FT_UInt)size) != 0) {
      return MY_RET_FAIL;
    }
    f->cur_size = size;
  }
  return MY_RET_OK;
}

static bool ft_shape_text_length(const char* text, size_t* length_out) {
  size_t length;
  if (text == NULL || length_out == NULL) return false;
  for (length = 0u; length <= MY_FONT_SHAPE_MAX_BYTES; length++) {
    if (text[length] == '\0') {
      *length_out = length;
      return true;
    }
  }
  return false;
}

/* ---------------- vtable ---------------- */

static my_ret_t ft_measure(my_font_t* font, const char* text, int32_t size,
                           int32_t* w, int32_t* h) {
  my_font_ft_t* f = (my_font_ft_t*)font;
  const char* p = text;
  int64_t width = 0;
  size_t text_length = 0u;
  if (text == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (!ft_shape_text_length(text, &text_length)) {
    return MY_RET_INVALID_PARAMS;
  }
  (void)text_length;
  platform_mutex_lock(&f->mutex);
  if (ft_set_size(f, size) != MY_RET_OK) {
    platform_mutex_unlock(&f->mutex);
    return MY_RET_FAIL;
  }
  while (*p != '\0') {
    uint32_t cp = my_utf8_next(&p);
    if (my_font_is_variation_selector(cp)) continue;
    if (FT_Load_Char(f->face, cp, FT_LOAD_DEFAULT) == 0) {
      width += (int32_t)(f->face->glyph->advance.x >> 6);
    }
  }
  if (w != NULL) {
    *w = width > INT32_MAX ? INT32_MAX : width < 0 ? 0 : (int32_t)width;
  }
  if (h != NULL) {
    *h = (int32_t)(f->face->size->metrics.height >> 6);
  }
  platform_mutex_unlock(&f->mutex);
  return MY_RET_OK;
}

static ft_cache_entry_t* ft_cache_lookup(my_font_ft_t* f, uint32_t cp,
                                         int32_t size) {
  size_t i;
  for (i = 0; i < f->cache_capacity; i++) {
    ft_cache_entry_t* e = &f->cache[i];
    if (e->occupied && !e->key_is_glyph_id && e->codepoint == cp &&
        e->size == size) {
      e->last_used = ++f->tick;
      f->hits++;
      return e;
    }
  }
  f->misses++;
  my_ui_metrics_record_atlas_miss();
  return NULL;
}

static ft_cache_entry_t* ft_cache_slot(my_font_ft_t* f);
static void ft_finalize(my_font_ft_t* f);

static void ft_release_glyph(void* lease) {
  ft_cache_entry_t* entry = (ft_cache_entry_t*)lease;
  ft_cache_entry_t** link;
  my_font_ft_t* owner;
  const my_allocator_t* allocator;
  bool finalize = false;
  bool free_entry = false;
  if (entry == NULL || entry->owner == NULL) return;
  owner = entry->owner;
  allocator = entry->allocator;
  platform_mutex_lock(&owner->mutex);
  if (entry->references == 0u) {
    platform_mutex_unlock(&owner->mutex);
    return;
  }
  entry->references--;
  if (owner->lease_count != 0u) owner->lease_count--;
  if (!entry->cached && entry->references == 0u) {
    link = &owner->overflow_entries;
    while (*link != NULL && *link != entry) link = &(*link)->next_overflow;
    if (*link == entry) {
      *link = entry->next_overflow;
      free_entry = true;
      if (owner->overflow_count != 0u) owner->overflow_count--;
    }
  }
  if (owner->destroy_requested && owner->lease_count == 0u) {
    finalize = true;
  }
  platform_mutex_unlock(&owner->mutex);
  if (free_entry) {
    my_mem_free(allocator, entry->bitmap);
    my_mem_free(allocator, entry);
  }
  if (finalize) ft_finalize(owner);
}

static ft_cache_entry_t* ft_cache_lookup_glyph(my_font_ft_t* f,
                                                uint32_t glyph_id,
                                                int32_t size) {
  size_t i;
  for (i = 0; i < f->cache_capacity; i++) {
    ft_cache_entry_t* e = &f->cache[i];
    if (e->occupied && e->key_is_glyph_id && e->codepoint == glyph_id &&
        e->size == size) {
      e->last_used = ++f->tick;
      f->hits++;
      return e;
    }
  }
  f->misses++;
  my_ui_metrics_record_atlas_miss();
  return NULL;
}

static my_ret_t ft_raster_glyph(my_font_ft_t* f, uint32_t cache_key,
                                uint32_t glyph_id, int32_t size,
                                bool key_is_glyph_id,
                                my_glyph_t* glyph) {
  if (f->lease_count == SIZE_MAX) return MY_RET_OOM;
  ft_cache_entry_t* e = key_is_glyph_id
                            ? ft_cache_lookup_glyph(f, cache_key, size)
                            : ft_cache_lookup(f, cache_key, size);
  if (e == NULL) {
    FT_GlyphSlot slot;
    uint8_t* bitmap = NULL;
    int32_t w;
    int32_t h;
    if (ft_set_size(f, size) != MY_RET_OK) return MY_RET_FAIL;
    if (FT_Load_Glyph(f->face, glyph_id, FT_LOAD_DEFAULT) != 0 ||
        FT_Render_Glyph(f->face->glyph, FT_RENDER_MODE_NORMAL) != 0) {
      return MY_RET_FAIL;
    }
    slot = f->face->glyph;
    w = (int32_t)slot->bitmap.width;
    h = (int32_t)slot->bitmap.rows;
    if (w > 0 && h > 0) {
      size_t bytes;
      if ((size_t)w > SIZE_MAX / (size_t)h) {
        return MY_RET_OOM;
      }
      bytes = (size_t)w * (size_t)h;
      bitmap = (uint8_t*)my_mem_alloc(f->allocator, bytes);
      if (bitmap == NULL) {
        return MY_RET_OOM;
      }
      {
        int32_t row;
        for (row = 0; row < h; row++) {
          memcpy(bitmap + (size_t)row * (size_t)w,
                 slot->bitmap.buffer + (size_t)row * (size_t)slot->bitmap.pitch,
                 (size_t)w);
        }
      }
    }
    /* Allocate the bitmap before evicting an existing entry. */
    e = ft_cache_slot(f);
    if (e == NULL) {
      if (f->overflow_count >= f->cache_capacity ||
          f->overflow_count >= MY_FONT_MAX_GLYPH_OVERFLOW_ENTRIES) {
        my_mem_free(f->allocator, bitmap);
        return MY_RET_OOM;
      }
      e = (ft_cache_entry_t*)my_mem_calloc(f->allocator, 1u, sizeof(*e));
      if (e == NULL) {
        my_mem_free(f->allocator, bitmap);
        return MY_RET_OOM;
      }
      e->cached = false;
      e->allocator = f->allocator;
      e->mutex = &f->mutex;
      e->owner = f;
      e->next_overflow = f->overflow_entries;
      f->overflow_entries = e;
      f->overflow_count++;
    } else {
      e->cached = true;
      e->allocator = f->allocator;
      e->mutex = &f->mutex;
      e->owner = f;
    }
    e->occupied = true;
    e->key_is_glyph_id = key_is_glyph_id;
    e->codepoint = cache_key;
    e->size = size;
    e->w = w;
    e->h = h;
    e->bearing_x = slot->bitmap_left;
    e->bearing_y = slot->bitmap_top;
    e->advance = (int32_t)(slot->advance.x >> 6);
    e->bitmap = bitmap;
    e->last_used = ++f->tick;
  }
  if (e->references == SIZE_MAX) {
    return MY_RET_OOM;
  }
  e->references++;
  f->lease_count++;
  glyph->bitmap = e->bitmap;
  glyph->w = e->w;
  glyph->h = e->h;
  glyph->bearing_x = e->bearing_x;
  glyph->bearing_y = e->bearing_y;
  glyph->advance = e->advance;
  glyph->lease = e;
  glyph->release_lease = ft_release_glyph;
  return MY_RET_OK;
}

static ft_cache_entry_t* ft_cache_slot(my_font_ft_t* f) {
  size_t i;
  ft_cache_entry_t* lru = &f->cache[0];
  bool found = false;
  for (i = 0; i < f->cache_capacity; i++) {
    if (!f->cache[i].occupied) {
      return &f->cache[i];
    }
    if (f->cache[i].references == 0u &&
        (!found || f->cache[i].last_used < lru->last_used)) {
      lru = &f->cache[i];
      found = true;
    }
  }
  if (!found) return NULL;
  my_mem_free(f->allocator, lru->bitmap); /* evict LRU */
  lru->bitmap = NULL;
  return lru;
}

static my_ret_t ft_get_glyph(my_font_t* font, uint32_t codepoint, int32_t size,
                             my_glyph_t* glyph) {
  my_font_ft_t* f = (my_font_ft_t*)font;
  my_ret_t ret;
  if (glyph == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (my_font_is_variation_selector(codepoint)) {
    memset(glyph, 0, sizeof(*glyph));
    return MY_RET_OK;
  }
  {
    platform_mutex_lock(&f->mutex);
    if (f->destroy_requested) {
      platform_mutex_unlock(&f->mutex);
      return MY_RET_FAIL;
    }
    FT_UInt glyph_id = FT_Get_Char_Index(f->face, codepoint);
    ret = glyph_id == 0u ? MY_RET_NOT_FOUND
                         : ft_raster_glyph(f, codepoint, glyph_id, size, false,
                                           glyph);
    platform_mutex_unlock(&f->mutex);
    return ret;
  }
}

static my_ret_t ft_get_glyph_id(my_font_t* font, uint32_t glyph_id,
                                int32_t size, my_glyph_t* glyph) {
  my_font_ft_t* f = (my_font_ft_t*)font;
  my_ret_t ret;
  if (glyph_id == 0u) return MY_RET_NOT_FOUND;
  if (glyph == NULL || size <= 0) return MY_RET_INVALID_PARAMS;
  platform_mutex_lock(&f->mutex);
  if (f->destroy_requested) {
    platform_mutex_unlock(&f->mutex);
    return MY_RET_FAIL;
  }
  ret = ft_raster_glyph(f, glyph_id, glyph_id, size, true, glyph);
  platform_mutex_unlock(&f->mutex);
  return ret;
}

#ifdef MYUI_FONT_HARFBUZZ
static bool ft_required_tag_contains(const hb_tag_t* required_tags,
                                     unsigned int required_count,
                                     hb_tag_t tag) {
  unsigned int i;
  for (i = 0u; i < required_count; i++) {
    if (required_tags[i] == tag) return true;
  }
  return false;
}

static void ft_collect_required_tags(
    hb_face_t* face, const my_font_shape_params_t* params,
    hb_tag_t* required_tags, unsigned int* required_count) {
  hb_script_t script;
  hb_language_t language = NULL;
  char script_name[5];
  hb_tag_t script_tags[HB_OT_MAX_TAGS_PER_SCRIPT];
  hb_tag_t language_tags[HB_OT_MAX_TAGS_PER_LANGUAGE];
  unsigned int script_count = HB_OT_MAX_TAGS_PER_SCRIPT;
  unsigned int language_count = HB_OT_MAX_TAGS_PER_LANGUAGE;
  const hb_tag_t tables[] = {HB_OT_TAG_GSUB, HB_OT_TAG_GPOS};
  unsigned int table_index;
  unsigned int script_tag_index;

  if (face == NULL || params == NULL || required_tags == NULL ||
      required_count == NULL || params->script == 0u) {
    return;
  }
  script_name[0] = (char)(params->script >> 24);
  script_name[1] = (char)(params->script >> 16);
  script_name[2] = (char)(params->script >> 8);
  script_name[3] = (char)params->script;
  script_name[4] = '\0';
  script = hb_script_from_string(script_name, 4);
  if (script == HB_SCRIPT_INVALID) return;
  if (params->language != NULL) {
    language = hb_language_from_string(params->language, -1);
  }
  hb_ot_tags_from_script_and_language(
      script, language, &script_count, script_tags, &language_count,
      language_tags);
  if (script_count > HB_OT_MAX_TAGS_PER_SCRIPT) {
    script_count = HB_OT_MAX_TAGS_PER_SCRIPT;
  }
  if (language_count > HB_OT_MAX_TAGS_PER_LANGUAGE) {
    language_count = HB_OT_MAX_TAGS_PER_LANGUAGE;
  }
  for (table_index = 0u; table_index < sizeof(tables) / sizeof(tables[0]);
       table_index++) {
    for (script_tag_index = 0u; script_tag_index < script_count;
         script_tag_index++) {
      unsigned int script_index;
      unsigned int language_index = HB_OT_LAYOUT_DEFAULT_LANGUAGE_INDEX;
      bool language_supported = params->language == NULL;
      hb_tag_t available_languages[HB_OT_MAX_TAGS_PER_LANGUAGE];
      unsigned int available_count = HB_OT_MAX_TAGS_PER_LANGUAGE;
      unsigned int available_index;
      unsigned int requested_index;
      unsigned int required_index;
      hb_tag_t required_tag;

      if (!hb_ot_layout_table_find_script(face, tables[table_index],
                                          script_tags[script_tag_index],
                                          &script_index)) {
        continue;
      }
      if (params->language != NULL) {
        (void)hb_ot_layout_script_get_language_tags(
            face, tables[table_index], script_index, 0u, &available_count,
            available_languages);
        if (available_count > HB_OT_MAX_TAGS_PER_LANGUAGE) {
          available_count = HB_OT_MAX_TAGS_PER_LANGUAGE;
        }
        for (available_index = 0u; available_index < available_count &&
                                    !language_supported;
             available_index++) {
          for (requested_index = 0u; requested_index < language_count;
               requested_index++) {
            if (available_languages[available_index] ==
                    language_tags[requested_index] &&
                hb_ot_layout_script_select_language(
                    face, tables[table_index], script_index, 1u,
                    &available_languages[available_index], &language_index)) {
              language_supported = true;
              break;
            }
          }
        }
      }
      if (!language_supported ||
          !hb_ot_layout_language_get_required_feature(
              face, tables[table_index], script_index, language_index,
              &required_index, &required_tag)) {
        continue;
      }
      if (!ft_required_tag_contains(required_tags, *required_count,
                                    required_tag) &&
          *required_count < MY_FONT_SHAPE_MAX_FEATURE_COUNT) {
        required_tags[(*required_count)++] = required_tag;
      }
    }
  }
}
#endif

static my_ret_t ft_shape_support_unlocked(
    my_font_t* font, const my_font_shape_params_t* params,
    my_font_shape_support_t* support) {
#ifdef MYUI_FONT_HARFBUZZ
  my_font_ft_t* f = (my_font_ft_t*)font;
  my_font_shape_params_t effective_params;
  char normalized_language[MY_FONT_SHAPE_MAX_LANGUAGE_BYTES + 1u];
  char normalized_features[MY_FONT_SHAPE_MAX_FEATURE_BYTES + 1u];
  hb_face_t* face;
  hb_script_t script;
  hb_language_t language = NULL;
  char script_name[5];
  hb_tag_t script_tags[HB_OT_MAX_TAGS_PER_SCRIPT];
  hb_tag_t language_tags[HB_OT_MAX_TAGS_PER_LANGUAGE];
  unsigned int script_count = HB_OT_MAX_TAGS_PER_SCRIPT;
  unsigned int language_count = HB_OT_MAX_TAGS_PER_LANGUAGE;
  unsigned int table_index;
  const hb_tag_t tables[] = {HB_OT_TAG_GSUB, HB_OT_TAG_GPOS};
  hb_tag_t feature_tags[MY_FONT_SHAPE_MAX_FEATURE_COUNT];
  unsigned int requested_feature_count = 0u;
  bool feature_supported[MY_FONT_SHAPE_MAX_FEATURE_COUNT] = {false};
  bool system_supported = false;
  size_t cache_index;
  size_t cache_slot = 0u;
  uint64_t oldest = UINT64_MAX;

  if (font == NULL || params == NULL || support == NULL ||
      !my_font_shape_params_valid(params)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (params->script == 0u) {
    *support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
    return MY_RET_OK;
  }
  effective_params = *params;
  if (params->language != NULL) {
    if (!ft_normalize_language_tag(
            params->language, normalized_language,
            sizeof(normalized_language))) {
      return MY_RET_INVALID_PARAMS;
    }
    effective_params.language = normalized_language;
  }
  if (params->features != NULL) {
    if (!my_font_shape_features_normalize(
            params->features, normalized_features,
            sizeof(normalized_features))) {
      return MY_RET_INVALID_PARAMS;
    }
    effective_params.features = normalized_features[0] != '\0'
                                    ? normalized_features
                                    : NULL;
  }
  for (cache_index = 0u;
       cache_index < MY_FONT_FT_SHAPE_SUPPORT_CACHE_CAPACITY; cache_index++) {
    ft_shape_support_cache_entry_t* entry = &f->shape_support_cache[cache_index];
    if (entry->occupied && entry->script == effective_params.script &&
        ((effective_params.language == NULL && entry->language[0] == '\0') ||
         (effective_params.language != NULL &&
          strcmp(entry->language, effective_params.language) == 0)) &&
        ((effective_params.features == NULL && entry->features[0] == '\0') ||
         (effective_params.features != NULL &&
          strcmp(entry->features, effective_params.features) == 0))) {
      entry->last_used = ++f->shape_support_tick;
      f->shape_support_cache_hits++;
      *support = entry->support;
      return MY_RET_OK;
    }
    if (!entry->occupied || entry->last_used < oldest) {
      oldest = entry->last_used;
      cache_slot = cache_index;
    }
  }
  script_name[0] = (char)(effective_params.script >> 24);
  script_name[1] = (char)(effective_params.script >> 16);
  script_name[2] = (char)(effective_params.script >> 8);
  script_name[3] = (char)effective_params.script;
  script_name[4] = '\0';
  script = hb_script_from_string(script_name, 4);
  if (script == HB_SCRIPT_INVALID) {
    *support = MY_FONT_SHAPE_UNSUPPORTED;
    return MY_RET_OK;
  }
  if (effective_params.language != NULL) {
    language = hb_language_from_string(effective_params.language, -1);
  }
  hb_ot_tags_from_script_and_language(
      script, language, &script_count, script_tags, &language_count,
      language_tags);
  if (script_count > HB_OT_MAX_TAGS_PER_SCRIPT) {
    script_count = HB_OT_MAX_TAGS_PER_SCRIPT;
  }
  if (language_count > HB_OT_MAX_TAGS_PER_LANGUAGE) {
    language_count = HB_OT_MAX_TAGS_PER_LANGUAGE;
  }
  if (effective_params.features != NULL && effective_params.features[0] != '\0') {
    size_t feature_start = 0u;
    size_t feature_length = strlen(effective_params.features);
    while (feature_start < feature_length) {
      size_t feature_end = feature_start;
      hb_tag_t feature_tag;
      unsigned int feature_index;
      while (feature_end < feature_length &&
             effective_params.features[feature_end] != ',') {
        feature_end++;
      }
      if (feature_end - feature_start < 4u ||
          requested_feature_count >= MY_FONT_SHAPE_MAX_FEATURE_COUNT) {
        return MY_RET_INVALID_PARAMS;
      }
      feature_tag = hb_tag_from_string(effective_params.features + feature_start, 4);
      for (feature_index = 0u; feature_index < requested_feature_count;
           feature_index++) {
        if (feature_tags[feature_index] == feature_tag) break;
      }
      if (feature_index == requested_feature_count) {
        feature_tags[requested_feature_count++] = feature_tag;
      }
      feature_start = feature_end + 1u;
    }
  }
  face = hb_ft_face_create_referenced(f->face);
  if (face == NULL) return MY_RET_OOM;

  *support = MY_FONT_SHAPE_UNSUPPORTED;
  for (table_index = 0u; table_index < sizeof(tables) / sizeof(tables[0]);
       table_index++) {
    unsigned int script_tag_index;
    for (script_tag_index = 0u; script_tag_index < script_count;
         script_tag_index++) {
      unsigned int script_index;
      if (!hb_ot_layout_table_find_script(face, tables[table_index],
                                          script_tags[script_tag_index],
                                          &script_index)) {
        continue;
      }
      {
        unsigned int language_index = HB_OT_LAYOUT_DEFAULT_LANGUAGE_INDEX;
        bool language_supported = params->language == NULL;
        hb_tag_t available_languages[HB_OT_MAX_TAGS_PER_LANGUAGE];
        unsigned int available_count = HB_OT_MAX_TAGS_PER_LANGUAGE;
        unsigned int available_index;
        unsigned int requested_index;
        if (params->language != NULL) {
          (void)hb_ot_layout_script_get_language_tags(
              face, tables[table_index], script_index, 0u, &available_count,
              available_languages);
          if (available_count > HB_OT_MAX_TAGS_PER_LANGUAGE) {
            available_count = HB_OT_MAX_TAGS_PER_LANGUAGE;
          }
          for (available_index = 0u; available_index < available_count &&
                                      !language_supported;
               available_index++) {
            for (requested_index = 0u; requested_index < language_count;
                 requested_index++) {
              if (available_languages[available_index] ==
                  language_tags[requested_index] &&
                  hb_ot_layout_script_select_language(
                      face, tables[table_index], script_index, 1u,
                      &available_languages[available_index], &language_index)) {
                language_supported = true;
                break;
              }
            }
          }
        }
        if (!language_supported) continue;
        system_supported = true;
        if (requested_feature_count == 0u) {
          *support = MY_FONT_SHAPE_SUPPORTED;
          break;
        }
        for (requested_index = 0u; requested_index < requested_feature_count;
             requested_index++) {
          unsigned int feature_index;
          if (hb_ot_layout_language_find_feature(
                  face, tables[table_index], script_index, language_index,
                  feature_tags[requested_index], &feature_index)) {
            feature_supported[requested_index] = true;
          } else {
            unsigned int required_index;
            hb_tag_t required_tag;
            if (hb_ot_layout_language_get_required_feature(
                    face, tables[table_index], script_index, language_index,
                    &required_index, &required_tag) &&
                required_tag == feature_tags[requested_index]) {
              feature_supported[requested_index] = true;
            }
          }
        }
      }
    }
    if (*support == MY_FONT_SHAPE_SUPPORTED) break;
  }
  if (*support != MY_FONT_SHAPE_SUPPORTED && system_supported) {
    unsigned int feature_index;
    *support = MY_FONT_SHAPE_SUPPORTED;
    for (feature_index = 0u; feature_index < requested_feature_count;
         feature_index++) {
      if (!feature_supported[feature_index]) {
        *support = MY_FONT_SHAPE_UNSUPPORTED;
        break;
      }
    }
  }
  hb_face_destroy(face);
  {
    ft_shape_support_cache_entry_t* entry =
        &f->shape_support_cache[cache_slot];
    entry->script = effective_params.script;
    if (effective_params.language == NULL) {
      entry->language[0] = '\0';
    } else {
      size_t language_length = strlen(effective_params.language);
      memcpy(entry->language, effective_params.language, language_length + 1u);
    }
    if (effective_params.features == NULL) {
      entry->features[0] = '\0';
    } else {
      size_t feature_length = strlen(effective_params.features);
      memcpy(entry->features, effective_params.features, feature_length + 1u);
    }
    entry->support = *support;
    entry->last_used = ++f->shape_support_tick;
    entry->occupied = true;
  }
  return MY_RET_OK;
#else
  (void)font;
  (void)params;
  if (support == NULL) return MY_RET_INVALID_PARAMS;
  *support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
  return MY_RET_OK;
#endif
}

static my_ret_t ft_shape_support(my_font_t* font,
                                 const my_font_shape_params_t* params,
                                 my_font_shape_support_t* support) {
  my_ret_t ret;
  my_font_ft_t* f = (my_font_ft_t*)font;
  if (f == NULL) return MY_RET_INVALID_PARAMS;
  platform_mutex_lock(&f->mutex);
  ret = ft_shape_support_unlocked(font, params, support);
  platform_mutex_unlock(&f->mutex);
  return ret;
}

static int32_t ft_ascent(my_font_t* font, int32_t size) {
  my_font_ft_t* f = (my_font_ft_t*)font;
  int32_t result;
  platform_mutex_lock(&f->mutex);
  if (ft_set_size(f, size) != MY_RET_OK) {
    platform_mutex_unlock(&f->mutex);
    return 0;
  }
  result = (int32_t)(f->face->size->metrics.ascender >> 6);
  platform_mutex_unlock(&f->mutex);
  return result;
}

static int32_t ft_descent(my_font_t* font, int32_t size) {
  my_font_ft_t* f = (my_font_ft_t*)font;
  int32_t result;
  platform_mutex_lock(&f->mutex);
  if (ft_set_size(f, size) != MY_RET_OK) {
    platform_mutex_unlock(&f->mutex);
    return 0;
  }
  result = (int32_t)(f->face->size->metrics.descender >> 6);
  platform_mutex_unlock(&f->mutex);
  return result;
}

static int32_t ft_line_height(my_font_t* font, int32_t size) {
  my_font_ft_t* f = (my_font_ft_t*)font;
  int32_t result;
  platform_mutex_lock(&f->mutex);
  if (ft_set_size(f, size) != MY_RET_OK) {
    platform_mutex_unlock(&f->mutex);
    return 0;
  }
  result = (int32_t)(f->face->size->metrics.height >> 6);
  platform_mutex_unlock(&f->mutex);
  return result;
}

static my_ret_t ft_shape_ex_unlocked(
    my_font_t* font, const char* text, int32_t size,
    const my_font_shape_params_t* params, const my_allocator_t* allocator,
    my_font_shape_result_t* result) {
#ifdef MYUI_FONT_HARFBUZZ
  my_font_ft_t* f = (my_font_ft_t*)font;
  hb_font_t* hb_font;
  hb_buffer_t* buffer;
  hb_face_t* face = NULL;
  unsigned int count = 0;
  const hb_glyph_info_t* infos;
  const hb_glyph_position_t* positions;
  unsigned int i;
  char script_name[5];
  hb_feature_t features[32];
  unsigned int feature_count = 0;
  hb_tag_t required_tags[MY_FONT_SHAPE_MAX_FEATURE_COUNT];
  unsigned int required_count = 0u;
  my_font_shape_params_t required_params;
  size_t text_length = 0u;
  if (result == NULL) return MY_RET_INVALID_PARAMS;
  memset(result, 0, sizeof(*result));
  result->allocator = allocator;
  result->rtl = params != NULL && params->rtl;
  if (font == NULL || text == NULL || size <= 0 || params == NULL ||
      !ft_shape_text_length(text, &text_length) ||
      !my_font_shape_params_valid(params)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (ft_set_size(f, size) != MY_RET_OK) return MY_RET_FAIL;
  hb_font = hb_ft_font_create_referenced(f->face);
  buffer = hb_buffer_create();
  if (hb_font == NULL || buffer == NULL ||
      !hb_buffer_allocation_successful(buffer)) {
    if (buffer != NULL) hb_buffer_destroy(buffer);
    if (hb_font != NULL) hb_font_destroy(hb_font);
    return MY_RET_OOM;
  }
  hb_buffer_add_utf8(buffer, text, (int)text_length, 0, (int)text_length);
  if (!hb_buffer_allocation_successful(buffer)) {
    hb_buffer_destroy(buffer);
    hb_font_destroy(hb_font);
    return MY_RET_OOM;
  }
  hb_buffer_set_flags(buffer, HB_BUFFER_FLAG_REMOVE_DEFAULT_IGNORABLES);
  hb_buffer_set_direction(buffer,
                          params->rtl ? HB_DIRECTION_RTL : HB_DIRECTION_LTR);
  if (params->script != 0u) {
    script_name[0] = (char)(params->script >> 24);
    script_name[1] = (char)(params->script >> 16);
    script_name[2] = (char)(params->script >> 8);
    script_name[3] = (char)params->script;
    script_name[4] = '\0';
    hb_buffer_set_script(buffer, hb_script_from_string(script_name, 4));
  }
  if (params->language != NULL) {
    hb_buffer_set_language(
        buffer, hb_language_from_string(params->language, -1));
  }
  hb_buffer_guess_segment_properties(buffer);
  required_params = *params;
  if (required_params.script == 0u) {
    required_params.script = hb_script_to_iso15924_tag(
        hb_buffer_get_script(buffer));
  }
  if (required_params.script != 0u) {
    face = hb_ft_face_create_referenced(f->face);
    if (face == NULL) {
      hb_buffer_destroy(buffer);
      hb_font_destroy(hb_font);
      return MY_RET_OOM;
    }
    ft_collect_required_tags(face, &required_params, required_tags,
                             &required_count);
  }
  if (params->features != NULL && params->features[0] != '\0') {
    size_t feature_start = 0u;
    size_t feature_length = strlen(params->features);
    while (feature_start < feature_length) {
      size_t feature_end = feature_start;
      if (feature_count >= MY_FONT_SHAPE_MAX_FEATURE_COUNT) {
        if (face != NULL) hb_face_destroy(face);
        hb_buffer_destroy(buffer);
        hb_font_destroy(hb_font);
        return MY_RET_INVALID_PARAMS;
      }
      while (feature_end < feature_length &&
             params->features[feature_end] != ',') {
        feature_end++;
      }
      if (feature_end == feature_start ||
          !hb_feature_from_string(params->features + feature_start,
                                  (int)(feature_end - feature_start),
                                  &features[feature_count])) {
        if (face != NULL) hb_face_destroy(face);
        hb_buffer_destroy(buffer);
        hb_font_destroy(hb_font);
        return MY_RET_INVALID_PARAMS;
      }
      if (features[feature_count].value == 0u &&
          ft_required_tag_contains(required_tags, required_count,
                                   features[feature_count].tag)) {
        features[feature_count].value = 1u;
      }
      feature_count++;
      feature_start = feature_end + 1u;
    }
  }
  hb_shape(hb_font, buffer, features, feature_count);
  if (!hb_buffer_allocation_successful(buffer)) {
    if (face != NULL) hb_face_destroy(face);
    hb_buffer_destroy(buffer);
    hb_font_destroy(hb_font);
    return MY_RET_OOM;
  }
  infos = hb_buffer_get_glyph_infos(buffer, &count);
  positions = hb_buffer_get_glyph_positions(buffer, &count);
  if (count > MY_FONT_SHAPE_MAX_GLYPHS) {
    if (face != NULL) hb_face_destroy(face);
    hb_buffer_destroy(buffer);
    hb_font_destroy(hb_font);
    return MY_RET_FAIL;
  }
  if (count > 0) {
    result->glyphs = (my_font_shape_glyph_t*)my_mem_alloc(
        allocator, (size_t)count * sizeof(*result->glyphs));
    if (result->glyphs == NULL) {
      if (face != NULL) hb_face_destroy(face);
      hb_buffer_destroy(buffer);
      hb_font_destroy(hb_font);
      return MY_RET_OOM;
    }
  }
  result->allocator = allocator;
  result->count = count;
  result->used_complex_shaping = true;
  for (i = 0; i < count; i++) {
    result->glyphs[i].font = font;
    result->glyphs[i].glyph_id = infos[i].codepoint;
    result->glyphs[i].cluster = infos[i].cluster;
    result->glyphs[i].advance_x_26_6 = positions[i].x_advance;
    result->glyphs[i].offset_x_26_6 = positions[i].x_offset;
    result->glyphs[i].offset_y_26_6 = positions[i].y_offset;
  }
  if (face != NULL) hb_face_destroy(face);
  hb_buffer_destroy(buffer);
  hb_font_destroy(hb_font);
  return MY_RET_OK;
#else
  (void)font; (void)text; (void)size; (void)params; (void)allocator;
  (void)result;
  return MY_RET_NOT_SUPPORTED;
#endif
}

static my_ret_t ft_shape_ex(
    my_font_t* font, const char* text, int32_t size,
    const my_font_shape_params_t* params, const my_allocator_t* allocator,
    my_font_shape_result_t* result) {
  my_ret_t ret;
  my_font_ft_t* f = (my_font_ft_t*)font;
  if (f == NULL) return MY_RET_INVALID_PARAMS;
  platform_mutex_lock(&f->mutex);
  ret = ft_shape_ex_unlocked(font, text, size, params, allocator, result);
  platform_mutex_unlock(&f->mutex);
  return ret;
}

static my_ret_t ft_shape(my_font_t* font, const char* text, int32_t size,
                         bool rtl, const my_allocator_t* allocator,
                         my_font_shape_result_t* result) {
  my_font_shape_params_t params = {rtl, 0u, NULL, NULL};
  return ft_shape_ex(font, text, size, &params, allocator, result);
}

static void ft_finalize(my_font_ft_t* f) {
  ft_cache_entry_t* overflow;
  ft_cache_entry_t* next;
  size_t i;
  for (i = 0; i < f->cache_capacity; i++) {
    my_mem_free(f->allocator, f->cache[i].bitmap);
  }
  overflow = f->overflow_entries;
  while (overflow != NULL) {
    next = overflow->next_overflow;
    my_mem_free(f->allocator, overflow->bitmap);
    my_mem_free(f->allocator, overflow);
    overflow = next;
  }
  my_mem_free(f->allocator, f->cache);
  if (f->face != NULL) {
    FT_Done_Face(f->face);
  }
  platform_mutex_destroy(&f->mutex);
  my_mem_free(f->allocator, f);
}

static void ft_destroy(my_font_t* font) {
  my_font_ft_t* f = (my_font_ft_t*)font;
  bool finalize = false;
  if (f == NULL) return;
  platform_mutex_lock(&f->mutex);
  if (!f->destroy_requested) {
    f->destroy_requested = true;
    finalize = f->lease_count == 0u;
  }
  platform_mutex_unlock(&f->mutex);
  if (finalize) ft_finalize(f);
}

size_t my_font_ft_required_feature_count(
    my_font_t* font, const my_font_shape_params_t* params) {
#ifdef MYUI_FONT_HARFBUZZ
  my_font_ft_t* f = (my_font_ft_t*)font;
  hb_face_t* face;
  hb_tag_t required_tags[MY_FONT_SHAPE_MAX_FEATURE_COUNT];
  unsigned int required_count = 0u;
  if (font == NULL || params == NULL || !my_font_shape_params_valid(params) ||
      params->script == 0u) {
    return 0u;
  }
  platform_mutex_lock(&f->mutex);
  face = hb_ft_face_create_referenced(f->face);
  if (face == NULL) {
    platform_mutex_unlock(&f->mutex);
    return 0u;
  }
  ft_collect_required_tags(face, params, required_tags, &required_count);
  hb_face_destroy(face);
  platform_mutex_unlock(&f->mutex);
  return (size_t)required_count;
#else
  (void)font;
  (void)params;
  return 0u;
#endif
}

uint32_t my_font_ft_required_feature_tag(
    my_font_t* font, const my_font_shape_params_t* params, size_t index) {
#ifdef MYUI_FONT_HARFBUZZ
  my_font_ft_t* f = (my_font_ft_t*)font;
  hb_face_t* face;
  hb_tag_t required_tags[MY_FONT_SHAPE_MAX_FEATURE_COUNT];
  unsigned int required_count = 0u;
  uint32_t result = 0u;
  if (font == NULL || params == NULL || !my_font_shape_params_valid(params) ||
      params->script == 0u || index >= MY_FONT_SHAPE_MAX_FEATURE_COUNT) {
    return 0u;
  }
  platform_mutex_lock(&f->mutex);
  face = hb_ft_face_create_referenced(f->face);
  if (face == NULL) {
    platform_mutex_unlock(&f->mutex);
    return 0u;
  }
  ft_collect_required_tags(face, params, required_tags, &required_count);
  if (index < (size_t)required_count) result = required_tags[index];
  hb_face_destroy(face);
  platform_mutex_unlock(&f->mutex);
  return result;
#else
  (void)font;
  (void)params;
  (void)index;
  return 0u;
#endif
}

static bool ft_has_glyph(my_font_t* font, uint32_t codepoint) {
  my_font_ft_t* f = (my_font_ft_t*)font;
  bool result;
  if (my_font_is_variation_selector(codepoint)) return false;
  platform_mutex_lock(&f->mutex);
  result = FT_Get_Char_Index(f->face, codepoint) != 0;
  platform_mutex_unlock(&f->mutex);
  return result;
}

static my_font_variation_support_t ft_variation_support(
    my_font_t* font, uint32_t codepoint, uint32_t selector) {
  my_font_ft_t* f = (my_font_ft_t*)font;
  FT_UInt32* selectors;
  my_font_variation_support_t result = MY_FONT_VARIATION_UNSUPPORTED;
  size_t i;
  if (my_font_is_variation_selector(codepoint) ||
      !my_font_is_variation_selector(selector)) {
    return MY_FONT_VARIATION_UNSUPPORTED;
  }
  platform_mutex_lock(&f->mutex);
  selectors = FT_Face_GetVariantSelectors(f->face);
  if (selectors == NULL) {
    platform_mutex_unlock(&f->mutex);
    return MY_FONT_VARIATION_SUPPORT_UNKNOWN;
  }
  for (i = 0u; selectors[i] != 0u; ++i) {
    if (selectors[i] == selector) {
      result = FT_Face_GetCharVariantIndex(f->face, codepoint, selector) != 0u
                   ? MY_FONT_VARIATION_SUPPORTED
                   : MY_FONT_VARIATION_UNSUPPORTED;
      break;
    }
  }
  platform_mutex_unlock(&f->mutex);
  return result;
}

static const my_font_vtable_t s_ft_vtable = {ft_measure,  ft_get_glyph,
                                             ft_ascent,   ft_descent,
                                             ft_line_height, ft_destroy,
                                             ft_has_glyph, ft_shape,
                                             ft_get_glyph_id, ft_shape_ex,
                                             ft_shape_support,
                                             ft_variation_support};

my_font_t* my_font_ft_create_ex(const my_allocator_t* allocator,
                                const char* path, int32_t face_index,
                                int32_t weight, size_t cache_capacity) {
  my_font_ft_t* f;
  FT_Library lib = ft_library();
  if (lib == NULL || path == NULL) {
    return NULL;
  }
  f = (my_font_ft_t*)my_mem_calloc(allocator, 1, sizeof(my_font_ft_t));
  if (f == NULL) {
    return NULL;
  }
  platform_mutex_init(&f->mutex);
  if (FT_New_Face(lib, path, face_index, &f->face) != 0) {
    platform_mutex_destroy(&f->mutex);
    my_mem_free(allocator, f);
    return NULL;
  }
  if (weight > 0) { /* variable font: pin the wght axis (0 = font default) */
    FT_MM_Var* mm = NULL;
    if (FT_Get_MM_Var(f->face, &mm) == 0 && mm != NULL) {
      FT_Fixed* coords = (FT_Fixed*)my_mem_calloc(allocator, mm->num_axis,
                                                  sizeof(FT_Fixed));
      FT_UInt i;
      if (coords == NULL) {
        FT_Done_MM_Var(lib, mm);
        FT_Done_Face(f->face);
        platform_mutex_destroy(&f->mutex);
        my_mem_free(allocator, f);
        return NULL;
      }
      for (i = 0; i < mm->num_axis; i++) {
        coords[i] = mm->axis[i].def;
        if (mm->axis[i].tag == 0x77676874u) { /* 'wght' */
          FT_Fixed w = weight > 32767
                           ? (FT_Fixed)INT32_MAX
                           : (FT_Fixed)((int64_t)weight * 65536);
          if (w < mm->axis[i].minimum) {
            w = mm->axis[i].minimum;
          }
          if (w > mm->axis[i].maximum) {
            w = mm->axis[i].maximum;
          }
          coords[i] = w;
        }
      }
      FT_Set_Var_Design_Coordinates(f->face, mm->num_axis, coords);
      my_mem_free(allocator, coords);
      FT_Done_MM_Var(lib, mm);
    }
  }
  f->base.vtable = &s_ft_vtable;
  f->allocator = allocator;
  f->cache_capacity = cache_capacity > 0 ? cache_capacity
                                         : MY_FONT_FT_DEFAULT_CACHE;
  f->cache = (ft_cache_entry_t*)my_mem_calloc(allocator, f->cache_capacity,
                                              sizeof(ft_cache_entry_t));
  if (f->cache == NULL) {
    FT_Done_Face(f->face);
    platform_mutex_destroy(&f->mutex);
    my_mem_free(allocator, f);
    return NULL;
  }
  return (my_font_t*)f;
}

my_font_t* my_font_ft_create(const my_allocator_t* allocator,
                             const char* path, int32_t face_index,
                             size_t cache_capacity) {
  return my_font_ft_create_ex(allocator, path, face_index, 0, cache_capacity);
}

#else /* !MYUI_FONT_FREETYPE */

my_font_t* my_font_ft_create_ex(const my_allocator_t* allocator,
                                const char* path, int32_t face_index,
                                int32_t weight, size_t cache_capacity) {
  (void)allocator;
  (void)weight;
  (void)path;
  (void)face_index;
  (void)cache_capacity;
  return NULL;
}

my_font_t* my_font_ft_create(const my_allocator_t* allocator,
                             const char* path, int32_t face_index,
                             size_t cache_capacity) {
  return my_font_ft_create_ex(allocator, path, face_index, 0, cache_capacity);
}

#endif /* MYUI_FONT_FREETYPE */

size_t my_font_ft_cache_hits(my_font_t* font) {
#ifdef MYUI_FONT_FREETYPE
  my_font_ft_t* f = (my_font_ft_t*)font;
  size_t result = 0u;
  if (f == NULL || f->base.vtable != &s_ft_vtable) return 0u;
  platform_mutex_lock(&f->mutex);
  result = f->hits;
  platform_mutex_unlock(&f->mutex);
  return result;
#else
  (void)font;
  return 0;
#endif
}

size_t my_font_ft_cache_misses(my_font_t* font) {
#ifdef MYUI_FONT_FREETYPE
  my_font_ft_t* f = (my_font_ft_t*)font;
  size_t result = 0u;
  if (f == NULL || f->base.vtable != &s_ft_vtable) return 0u;
  platform_mutex_lock(&f->mutex);
  result = f->misses;
  platform_mutex_unlock(&f->mutex);
  return result;
#else
  (void)font;
  return 0;
#endif
}

size_t my_font_ft_shape_support_cache_hits(my_font_t* font) {
#ifdef MYUI_FONT_FREETYPE
  my_font_ft_t* f = (my_font_ft_t*)font;
  size_t result = 0u;
  if (f == NULL || f->base.vtable != &s_ft_vtable) return 0u;
  platform_mutex_lock(&f->mutex);
  result = f->shape_support_cache_hits;
  platform_mutex_unlock(&f->mutex);
  return result;
#else
  (void)font;
  return 0u;
#endif
}
