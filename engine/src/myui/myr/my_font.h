/**
 * @file my_font.h
 * @brief Font abstraction: metrics + glyph bitmaps (8bpp alpha).
 *
 * A font provides glyph rasterization for the vgcanvas backends.
 * Implementations: my_font_bitmap (built-in 8x8, zero-dependency
 * fallback) and my_font_stb (TrueType via stb_truetype, optional).
 * Text is UTF-8; decode with myc's my_str helpers.
 */
#ifndef MY_FONT_H
#define MY_FONT_H

#include <string.h>

#include "myc/my_error.h"
#include "myc/my_mem.h"

/** @brief One rasterized glyph (8bpp alpha coverage, row-major). */
typedef struct my_glyph_t {
  const uint8_t* bitmap; /**< w*h alpha bytes; NULL for blank (space) */
  int32_t w;             /**< bitmap width */
  int32_t h;             /**< bitmap height */
  int32_t bearing_x;     /**< left side bearing (pixels from pen x) */
  int32_t bearing_y;     /**< ascent offset: pixels above the baseline */
  int32_t advance;       /**< pen advance */
  /** @brief Internal lease; do not copy a live glyph value. */
  void* lease;
  void (*release_lease)(void* lease);
} my_glyph_t;

typedef struct my_font_t my_font_t;

#define MY_FONT_SCRIPT_TAG(a, b, c, d) \
  (((uint32_t)(a) << 24) | ((uint32_t)(b) << 16) | \
   ((uint32_t)(c) << 8) | (uint32_t)(d))
#define MY_FONT_SCRIPT_LATN MY_FONT_SCRIPT_TAG('L', 'a', 't', 'n')
#define MY_FONT_SCRIPT_ARAB MY_FONT_SCRIPT_TAG('A', 'r', 'a', 'b')
#define MY_FONT_SCRIPT_HEBR MY_FONT_SCRIPT_TAG('H', 'e', 'b', 'r')
#define MY_FONT_SCRIPT_HANI MY_FONT_SCRIPT_TAG('H', 'a', 'n', 'i')
#define MY_FONT_SCRIPT_GREK MY_FONT_SCRIPT_TAG('G', 'r', 'e', 'k')
#define MY_FONT_SCRIPT_CYRL MY_FONT_SCRIPT_TAG('C', 'y', 'r', 'l')
#define MY_FONT_SCRIPT_DEVA MY_FONT_SCRIPT_TAG('D', 'e', 'v', 'a')
#define MY_FONT_SCRIPT_BENG MY_FONT_SCRIPT_TAG('B', 'e', 'n', 'g')
#define MY_FONT_SCRIPT_THAA MY_FONT_SCRIPT_TAG('T', 'h', 'a', 'a')
#define MY_FONT_SCRIPT_THAI MY_FONT_SCRIPT_TAG('T', 'h', 'a', 'i')
#define MY_FONT_SCRIPT_HANG MY_FONT_SCRIPT_TAG('H', 'a', 'n', 'g')
#define MY_FONT_SCRIPT_HIRA MY_FONT_SCRIPT_TAG('H', 'i', 'r', 'a')
#define MY_FONT_SCRIPT_KANA MY_FONT_SCRIPT_TAG('K', 'a', 'n', 'a')
#define MY_FONT_SCRIPT_ARMN MY_FONT_SCRIPT_TAG('A', 'r', 'm', 'n')
#define MY_FONT_SCRIPT_GEOR MY_FONT_SCRIPT_TAG('G', 'e', 'o', 'r')
#define MY_FONT_SCRIPT_ETHI MY_FONT_SCRIPT_TAG('E', 't', 'h', 'i')
#define MY_FONT_SCRIPT_MYMR MY_FONT_SCRIPT_TAG('M', 'y', 'm', 'r')
#define MY_FONT_SCRIPT_KHMR MY_FONT_SCRIPT_TAG('K', 'h', 'm', 'r')
#define MY_FONT_SCRIPT_LAOO MY_FONT_SCRIPT_TAG('L', 'a', 'o', 'o')
#define MY_FONT_SCRIPT_TAML MY_FONT_SCRIPT_TAG('T', 'a', 'm', 'l')
#define MY_FONT_SCRIPT_TELU MY_FONT_SCRIPT_TAG('T', 'e', 'l', 'u')
#define MY_FONT_SCRIPT_KNDA MY_FONT_SCRIPT_TAG('K', 'n', 'd', 'a')
#define MY_FONT_SCRIPT_MLYM MY_FONT_SCRIPT_TAG('M', 'l', 'y', 'm')

#define MY_FONT_SHAPE_MAX_LANGUAGE_BYTES 64u
#define MY_FONT_SHAPE_MAX_FEATURE_BYTES 1024u
#define MY_FONT_SHAPE_MAX_FEATURE_COUNT 32u
#define MY_FONT_SHAPE_MAX_BYTES (4u * 1024u * 1024u)
/* Bound provider output independently from input bytes and allocator size. */
#define MY_FONT_SHAPE_MAX_GLYPHS (1024u * 1024u)
#define MY_FONT_STB_MAX_FILE_BYTES (64u * 1024u * 1024u)
/* Keep fallback-chain setup bounded; shaping remains linear in loaded faces. */
#define MY_FONT_CHAIN_MAX_SOURCES 256u
/* Bound retained cache entries while callers hold glyph leases. */
#define MY_FONT_MAX_GLYPH_OVERFLOW_ENTRIES 1024u

typedef struct my_font_shape_params_t {
  bool rtl;
  uint32_t script;
  const char* language;
  const char* features;
} my_font_shape_params_t;

typedef enum my_font_shape_support_t {
  MY_FONT_SHAPE_SUPPORT_UNKNOWN = 0,
  MY_FONT_SHAPE_SUPPORTED = 1,
  MY_FONT_SHAPE_UNSUPPORTED = 2
} my_font_shape_support_t;

typedef enum my_font_variation_support_t {
  MY_FONT_VARIATION_SUPPORT_UNKNOWN = 0,
  MY_FONT_VARIATION_SUPPORTED = 1,
  MY_FONT_VARIATION_UNSUPPORTED = 2
} my_font_variation_support_t;

/** @brief Validate bounded shaping parameters before changing layout state. */
bool my_font_shape_params_valid(const my_font_shape_params_t* params);

/**
 * @brief Normalize a bounded comma-separated OpenType feature list.
 *
 * Tags are sorted, duplicate or overlapping ranges use the last declaration,
 * and the result is written to caller-owned storage. No heap allocation is
 * performed. NULL and empty input normalize to an empty string.
 */
bool my_font_shape_features_normalize(const char* features, char* output,
                                      size_t output_size);

/**
 * @brief Query bounded script/language and requested feature support.
 *
 * A provider reports supported only when the script/language system exists
 * and every requested feature tag is present in a compatible shaping table.
 * Unknown providers return SUPPORT_UNKNOWN so callers can retain a safe
 * best-effort fallback.
 */
my_ret_t my_font_shape_support_query(
    my_font_t* font, const my_font_shape_params_t* params,
    my_font_shape_support_t* support);

typedef struct my_font_shape_glyph_t {
  /** @brief Face that owns glyph_id; providers must initialize this field. */
  my_font_t* font;
  uint32_t glyph_id;
  uint32_t cluster;
  int32_t advance_x_26_6;
  int32_t offset_x_26_6;
  int32_t offset_y_26_6;
} my_font_shape_glyph_t;

typedef struct my_font_shape_result_t {
  const my_allocator_t* allocator;
  my_font_shape_glyph_t* glyphs;
  size_t count;
  bool rtl;
  bool used_complex_shaping;
} my_font_shape_result_t;

typedef my_ret_t (*my_font_shape_fn)(my_font_t* font, const char* text,
                                     int32_t size, bool rtl,
                                     const my_allocator_t* allocator,
                                     my_font_shape_result_t* result);
typedef my_ret_t (*my_font_shape_ex_fn)(
    my_font_t* font, const char* text, int32_t size,
    const my_font_shape_params_t* params, const my_allocator_t* allocator,
    my_font_shape_result_t* result);
typedef my_ret_t (*my_font_shape_support_fn)(
    my_font_t* font, const my_font_shape_params_t* params,
    my_font_shape_support_t* support);
typedef my_font_variation_support_t (*my_font_variation_support_fn)(
    my_font_t* font, uint32_t codepoint, uint32_t selector);
typedef my_ret_t (*my_font_get_glyph_id_fn)(my_font_t* font,
                                            uint32_t glyph_id, int32_t size,
                                            my_glyph_t* glyph);

/** @brief A font source plus an optional face index for TTC collections. */
typedef struct my_font_source_t {
  const char* path;
  int32_t face_index;
} my_font_source_t;

/** @brief Font vtable. */
typedef struct my_font_vtable_t {
  /** @brief Metrics of a UTF-8 string at size (pixels). */
  my_ret_t (*measure)(my_font_t* font, const char* text, int32_t size,
                      int32_t* w, int32_t* h);
  /** @brief Rasterize one codepoint; blank glyph for missing/space. */
  my_ret_t (*get_glyph)(my_font_t* font, uint32_t codepoint, int32_t size,
                        my_glyph_t* glyph);
  int32_t (*ascent)(my_font_t* font, int32_t size);
  int32_t (*descent)(my_font_t* font, int32_t size); /**< negative or 0 */
  int32_t (*line_height)(my_font_t* font, int32_t size);
  void (*destroy)(my_font_t* font);
  /** @brief Whether the face has a glyph for cp (M16; appended slot,
   * NULL = "assume yes"). Used by the fallback chain. */
  bool (*has_glyph)(my_font_t* font, uint32_t codepoint);
  my_font_shape_fn shape;
  my_font_get_glyph_id_fn get_glyph_id;
  my_font_shape_ex_fn shape_ex;
  my_font_shape_support_fn shape_support;
  /** @brief Optional exact base/selector coverage query; NULL = unknown. */
  my_font_variation_support_fn variation_support;
} my_font_vtable_t;

/** @brief Font base "class". */
struct my_font_t {
  const my_font_vtable_t* vtable;
};

static inline my_ret_t my_font_measure(my_font_t* font, const char* text,
                                       int32_t size, int32_t* w, int32_t* h) {
  if (font == NULL || font->vtable == NULL || font->vtable->measure == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  return font->vtable->measure(font, text, size, w, h);
}

static inline void my_font_glyph_release(my_glyph_t* glyph);

/**
 * @brief Rasterize a codepoint and acquire a bitmap lease.
 *
 * On success, consume the bitmap before calling my_font_glyph_release().
 */
static inline my_ret_t my_font_get_glyph(my_font_t* font, uint32_t codepoint,
                                         int32_t size, my_glyph_t* glyph) {
  if (glyph == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  memset(glyph, 0, sizeof(*glyph));
  if (font == NULL || font->vtable == NULL ||
      font->vtable->get_glyph == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  {
    my_ret_t result = font->vtable->get_glyph(font, codepoint, size, glyph);
    if (result != MY_RET_OK) my_font_glyph_release(glyph);
    return result;
  }
}

/**
 * @brief Release a glyph returned by my_font_get_glyph or get_glyph_id.
 *
 * The bitmap is borrowed through this lease. It remains valid until this
 * function is called, and the font must remain alive until then. Do not copy
 * a live glyph value; call this function exactly once for every successful
 * glyph lookup.
 */
static inline void my_font_glyph_release(my_glyph_t* glyph) {
  if (glyph == NULL) return;
  if (glyph->release_lease != NULL && glyph->lease != NULL) {
    glyph->release_lease(glyph->lease);
  }
  memset(glyph, 0, sizeof(*glyph));
}

static inline int32_t my_font_ascent(my_font_t* font, int32_t size) {
  if (font == NULL || font->vtable == NULL || font->vtable->ascent == NULL) {
    return 0;
  }
  return font->vtable->ascent(font, size);
}

static inline int32_t my_font_descent(my_font_t* font, int32_t size) {
  if (font == NULL || font->vtable == NULL ||
      font->vtable->descent == NULL) {
    return 0;
  }
  return font->vtable->descent(font, size);
}

static inline int32_t my_font_line_height(my_font_t* font, int32_t size) {
  if (font == NULL || font->vtable == NULL ||
      font->vtable->line_height == NULL) {
    return 0;
  }
  return font->vtable->line_height(font, size);
}

static inline void my_font_destroy(my_font_t* font) {
  if (font != NULL && font->vtable != NULL && font->vtable->destroy != NULL) {
    font->vtable->destroy(font);
  }
}

/** @brief Whether the face has a glyph for codepoint (M16; NULL vtable
 * slot = assume yes). */
static inline bool my_font_has_glyph(my_font_t* font, uint32_t codepoint) {
  return font != NULL && font->vtable != NULL &&
         (font->vtable->has_glyph == NULL ||
          font->vtable->has_glyph(font, codepoint));
}

/** @brief Shape UTF-8 text within MY_FONT_SHAPE_MAX_BYTES. */
my_ret_t my_font_shape(my_font_t* font, const char* text, int32_t size,
                       bool rtl, const my_allocator_t* allocator,
                       my_font_shape_result_t* result);

/** @brief Shape bounded UTF-8 text with direction, script, language/features. */
my_ret_t my_font_shape_ex(my_font_t* font, const char* text, int32_t size,
                          const my_font_shape_params_t* params,
                          const my_allocator_t* allocator,
                          my_font_shape_result_t* result);

/** @brief Release a result returned by my_font_shape. */
void my_font_shape_destroy(my_font_shape_result_t* result);

/** @brief Rasterize a backend glyph id and acquire a bitmap lease. */
my_ret_t my_font_get_glyph_id(my_font_t* font, uint32_t glyph_id,
                              int32_t size, my_glyph_t* glyph);

/**
 * @brief Fallback chain (M14b; backend-neutral since M16): load several
 * faces (FreeType preferred when built with MYUI_FONT_FREETYPE, stb
 * otherwise); each codepoint is routed to the first face containing it.
 * Faces that fail to load are skipped; NULL when no face loads.
 */
my_font_t* my_font_create_chain(const my_allocator_t* allocator,
                                const char* const* paths, size_t path_count,
                                size_t cache_capacity);

/**
 * @brief Like my_font_create_chain, but supports selecting a face from a
 * TrueType Collection. Use this for locale-specific CJK faces in a TTC.
 */
my_font_t* my_font_create_chain_ex(const my_allocator_t* allocator,
                                   const my_font_source_t* sources,
                                   size_t source_count,
                                   size_t cache_capacity);

/**
 * @brief Decode the first UTF-8 codepoint of s and advance the pointer.
 * Invalid, truncated, overlong, surrogate, and out-of-range sequences decode
 * as 0xFFFD and advance one byte. s must not be empty.
 */
uint32_t my_utf8_next(const char** s);

/** @brief Whether cp is a Unicode variation selector, not a standalone glyph. */
static inline bool my_font_is_variation_selector(uint32_t cp) {
  return (cp >= 0xFE00u && cp <= 0xFE0Fu) ||
         (cp >= 0xE0100u && cp <= 0xE01EFu);
}

/* ---------------- built-in 8x8 bitmap font ---------------- */

/** @brief Built-in monospaced 8x8 font (ASCII 32..126), zero-dependency. */
my_font_t* my_font_bitmap_create(const my_allocator_t* allocator);

/* ---------------- stb_truetype backend ---------------- */

/**
 * @brief Load a TrueType font from a file path, with an LRU glyph cache
 * of cache_capacity entries (0 = default 256). NULL when the file
 * cannot be read/parsed, or when built without MYUI_FONT_STB.
 */
my_font_t* my_font_stb_create(const my_allocator_t* allocator, const char* path,
                              size_t cache_capacity);

/** @brief Load a STB TrueType/TTC face with an explicit face index. */
my_font_t* my_font_stb_create_ex(const my_allocator_t* allocator,
                                 const char* path, int32_t face_index,
                                 size_t cache_capacity);

/** @brief Test/diagnostics: glyph cache hit counter (0 without STB). */
size_t my_font_stb_cache_hits(my_font_t* font);

/** @brief Test/diagnostics: glyph cache miss counter (0 without STB). */
size_t my_font_stb_cache_misses(my_font_t* font);

/** @brief FreeType backend (M16, hinted): see my_font_ft.h. */
my_font_t* my_font_ft_create(const my_allocator_t* allocator,
                             const char* path, int32_t face_index,
                             size_t cache_capacity);

#endif /* MY_FONT_H */
