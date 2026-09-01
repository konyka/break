/**
 * @file my_text_layout.c
 * @brief Text layout implementation (M11a): decode -> fast path ->
 * Arabic shaping -> SheenBidi UBA reorder; LRU-cached masters.
 */
#include "myr/my_text_layout.h"

#include <limits.h>
#include <stdint.h>
#include <string.h>

#include "myc/my_str.h" /* my_strdup */
#include "myr/my_font.h" /* my_utf8_next */

#if defined(MYUI_BIDI)
#include <SheenBidi/SBAlgorithm.h>
#include <SheenBidi/SBCodepointSequence.h>
#include <SheenBidi/SBLine.h>
#include <SheenBidi/SBParagraph.h>
#include <SheenBidi/SBRun.h>

#include "myr/my_arabic_shape.h"
#include "myr/my_bidi_mirror_data.h"

/** @brief Mirror glyph of a codepoint (UBA L4, M12b), or cp itself. */
static uint32_t tl_mirror_cp(uint32_t cp) {
  size_t lo = 0, hi = sizeof(MY_BIDI_MIRRORS) / sizeof(MY_BIDI_MIRRORS[0]);
  while (lo < hi) {
    size_t mid = lo + (hi - lo) / 2;
    const my_bidi_mirror_t* e = &MY_BIDI_MIRRORS[mid];
    if (cp == e->cp) {
      return e->mirror;
    }
    if (cp < e->cp) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }
  return cp;
}
#endif

/* ---------------- utf-8 helpers ---------------- */

static bool tl_bounded_text_len(const char* text, size_t* out_len) {
  size_t text_len = 0;
  while (text_len <= MY_TEXT_LAYOUT_MAX_BYTES && text[text_len] != '\0') {
    text_len++;
  }
  if (text_len > MY_TEXT_LAYOUT_MAX_BYTES) {
    return false;
  }
  *out_len = text_len;
  return true;
}

static uint32_t* tl_decode(const my_allocator_t* alloc, const char* text,
                           size_t text_len, size_t* out_len) {
  size_t cap;
  size_t n = 0;
  if (text_len == SIZE_MAX || text_len + 1 > SIZE_MAX / sizeof(uint32_t)) {
    return NULL;
  }
  cap = text_len + 1;
  uint32_t* cps = (uint32_t*)my_mem_alloc(alloc, cap * sizeof(uint32_t));
  const char* p = text;
  if (cps == NULL) {
    return NULL;
  }
  while (*p != '\0') {
    cps[n++] = my_utf8_next(&p);
  }
  *out_len = n;
  return cps;
}

static size_t tl_utf8_encode(uint32_t cp, char out[4]) {
  if (cp < 0x80u) {
    out[0] = (char)cp;
    return 1;
  }
  if (cp < 0x800u) {
    out[0] = (char)(0xC0u | (cp >> 6));
    out[1] = (char)(0x80u | (cp & 0x3Fu));
    return 2;
  }
  if (cp < 0x10000u) {
    out[0] = (char)(0xE0u | (cp >> 12));
    out[1] = (char)(0x80u | ((cp >> 6) & 0x3Fu));
    out[2] = (char)(0x80u | (cp & 0x3Fu));
    return 3;
  }
  out[0] = (char)(0xF0u | (cp >> 18));
  out[1] = (char)(0x80u | ((cp >> 12) & 0x3Fu));
  out[2] = (char)(0x80u | ((cp >> 6) & 0x3Fu));
  out[3] = (char)(0x80u | (cp & 0x3Fu));
  return 4;
}

static char* tl_encode_all(const my_allocator_t* alloc, const uint32_t* cps,
                           size_t len) {
  char* s;
  size_t i, n = 0;
  if (len > (SIZE_MAX - 1) / 4) {
    return NULL;
  }
  s = (char*)my_mem_alloc(alloc, len * 4 + 1);
  if (s == NULL) {
    return NULL;
  }
  for (i = 0; i < len; i++) {
    n += tl_utf8_encode(cps[i], s + n);
  }
  s[n] = '\0';
  return s;
}

static bool tl_cp_needs_bidi(uint32_t cp) {
  return (cp >= 0x0590u && cp <= 0x08FFu) || /* Hebrew, Arabic, Syriac... */
         (cp >= 0xFB1Du && cp <= 0xFEFCu) || /* presentation forms */
         cp == 0x061Cu ||                    /* Arabic letter mark */
         cp == 0x200Eu || cp == 0x200Fu ||   /* LRM/RLM */
         (cp >= 0x202Au && cp <= 0x202Eu) || /* embeddings/overrides */
         (cp >= 0x2066u && cp <= 0x2069u);   /* isolates */
}

static uint32_t tl_script_tag(uint32_t cp) {
  if ((cp >= 0x0041u && cp <= 0x024Fu) ||
      (cp >= 0x1E00u && cp <= 0x1EFFu)) {
    return MY_FONT_SCRIPT_LATN;
  }
  if (cp >= 0x0370u && cp <= 0x03FFu) return MY_FONT_SCRIPT_GREK;
  if (cp >= 0x0400u && cp <= 0x052Fu) return MY_FONT_SCRIPT_CYRL;
  if (cp >= 0x0590u && cp <= 0x05FFu) return MY_FONT_SCRIPT_HEBR;
  if ((cp >= 0x0600u && cp <= 0x08FFu) ||
      (cp >= 0xFB50u && cp <= 0xFEFFu)) {
    return MY_FONT_SCRIPT_ARAB;
  }
  if (cp >= 0x0900u && cp <= 0x097Fu) return MY_FONT_SCRIPT_DEVA;
  if (cp >= 0x0980u && cp <= 0x09FFu) return MY_FONT_SCRIPT_BENG;
  if (cp >= 0x0780u && cp <= 0x07BFu) return MY_FONT_SCRIPT_THAA;
  if (cp >= 0x0E00u && cp <= 0x0E7Fu) return MY_FONT_SCRIPT_THAI;
  if (cp >= 0xAC00u && cp <= 0xD7AFu) return MY_FONT_SCRIPT_HANG;
  if ((cp >= 0x3400u && cp <= 0x4DBFu) ||
      (cp >= 0x4E00u && cp <= 0x9FFFu) ||
      (cp >= 0xF900u && cp <= 0xFAFFu)) {
    return MY_FONT_SCRIPT_HANI;
  }
  return 0u;
}

bool my_text_layout_may_need_bidi(const char* text) {
  const char* p = text;
  if (text == NULL) {
    return false;
  }
  while (*p != '\0') {
    if (tl_cp_needs_bidi(my_utf8_next(&p))) {
      return true;
    }
  }
  return false;
}

bool my_text_layout_may_need_bidi_n(const char* text, size_t byte_len) {
  size_t consumed = 0;
  if (text == NULL) {
    return false;
  }
  while (consumed < byte_len) {
    const char* p = text + consumed;
    const char* next = p;
    if (tl_cp_needs_bidi(my_utf8_next(&next))) {
      return true;
    }
    if (next <= p || (size_t)(next - p) > byte_len - consumed) {
      return false;
    }
    consumed += (size_t)(next - p);
  }
  return false;
}

/* ---------------- layout master (cache payload) ---------------- */

typedef struct tl_master_t {
  char* text;  /**< key (owned copy) */
  uint32_t* cps;
  uint32_t* map;
  uint32_t* vspan;
  uint32_t* inv;   /**< logical_to_visual */
  uint8_t* vrtl;   /**< per visual cp: run is RTL */
  char* utf8;
  size_t len;
  size_t logical_len;
  bool has_rtl;
  bool rtl_base; /**< paragraph base direction is RTL (M13b) */
  uint64_t tick;
} tl_master_t;

static void tl_master_free(tl_master_t* m) {
  my_mem_free(NULL, m->text);
  my_mem_free(NULL, m->cps);
  my_mem_free(NULL, m->map);
  my_mem_free(NULL, m->vspan);
  my_mem_free(NULL, m->inv);
  my_mem_free(NULL, m->vrtl);
  my_mem_free(NULL, m->utf8);
  memset(m, 0, sizeof(*m));
}

/** @brief Compute the master: decode, shape (BIDI), reorder (BIDI). */
static bool tl_master_compute(tl_master_t* m, const char* text,
                              size_t text_len) {
  size_t source_len = 0, i;
  bool may = false;
  memset(m, 0, sizeof(*m));
  m->text = my_strdup(NULL, text);
  m->cps = tl_decode(NULL, text, text_len, &source_len);
  if (m->text == NULL || m->cps == NULL) {
    tl_master_free(m);
    return false;
  }
  m->len = source_len;
  m->logical_len = source_len;
  if (source_len > SIZE_MAX / sizeof(uint32_t) || source_len > UINT32_MAX) {
    tl_master_free(m);
    return false;
  }
  m->map = (uint32_t*)my_mem_alloc(NULL,
                                   (source_len > 0 ? source_len : 1) *
                                       sizeof(uint32_t));
  m->vspan = (uint32_t*)my_mem_alloc(NULL,
                                     (source_len > 0 ? source_len : 1) *
                                         sizeof(uint32_t));
  m->inv = (uint32_t*)my_mem_alloc(NULL,
                                   (source_len > 0 ? source_len : 1) *
                                       sizeof(uint32_t));
  m->vrtl = (uint8_t*)my_mem_calloc(NULL, source_len > 0 ? source_len : 1, 1);
  if (m->map == NULL || m->vspan == NULL || m->inv == NULL ||
      m->vrtl == NULL) {
    tl_master_free(m);
    return false;
  }
  for (i = 0; i < source_len; i++) {
    m->map[i] = (uint32_t)i;
    m->vspan[i] = 1u;
    if (tl_cp_needs_bidi(m->cps[i])) {
      may = true;
    }
  }
#if defined(MYUI_BIDI)
  if (may && source_len > 0) {
    uint32_t* shaped_map = (uint32_t*)my_mem_alloc(
        NULL, source_len * sizeof(uint32_t));
    uint32_t* shaped_span = (uint32_t*)my_mem_alloc(
        NULL, source_len * sizeof(uint32_t));
    size_t visual_len;
    bool reordered = false;
    if (shaped_map == NULL || shaped_span == NULL) {
      my_mem_free(NULL, shaped_map);
      my_mem_free(NULL, shaped_span);
      tl_master_free(m);
      return false;
    }
    for (i = 0; i < source_len; i++) {
      shaped_map[i] = (uint32_t)i;
      shaped_span[i] = 1u;
    }
    visual_len = my_arabic_shape_with_map(m->cps, source_len, shaped_map,
                                          shaped_span);
    if (visual_len > source_len) {
      my_mem_free(NULL, shaped_map);
      my_mem_free(NULL, shaped_span);
      tl_master_free(m);
      return false;
    }
    m->len = visual_len;
    memcpy(m->map, shaped_map, visual_len * sizeof(uint32_t));
    memcpy(m->vspan, shaped_span, visual_len * sizeof(uint32_t));
    {
      SBCodepointSequence seq = {SBStringEncodingUTF32, m->cps, visual_len};
      SBAlgorithmRef alg = SBAlgorithmCreate(&seq);
      SBParagraphRef para = NULL;
      SBLineRef line = NULL;
      const SBRun* runs = NULL;
      size_t run_count = 0, vi = 0, ri;
      bool has_rtl = false;
      bool base_rtl = false;
      if (alg != NULL) {
        para = SBAlgorithmCreateParagraph(alg, 0, visual_len,
                                          SBLevelDefaultLTR);
      }
      if (para != NULL) {
        base_rtl = SBParagraphGetBaseLevel(para) != 0;
        line = SBParagraphCreateLine(para, 0, SBParagraphGetLength(para));
      }
      if (line != NULL) {
        runs = SBLineGetRunsPtr(line);
        run_count = SBLineGetRunCount(line);
        has_rtl = SBParagraphGetBaseLevel(para) != 0;
        /* runs are already in VISUAL order; odd level = RTL -> reverse */
        {
          uint32_t* tmp = (uint32_t*)my_mem_alloc(NULL,
                                                  visual_len * sizeof(uint32_t));
          if (tmp == NULL) {
            SBLineRelease(line);
            SBParagraphRelease(para);
            SBAlgorithmRelease(alg);
            tl_master_free(m);
            return false;
          }
          memcpy(tmp, m->cps, visual_len * sizeof(uint32_t));
          for (ri = 0; ri < run_count; ri++) {
            SBUInteger k;
            bool rtl = (runs[ri].level & 1u) != 0;
            has_rtl = has_rtl || rtl;
            for (k = 0; k < runs[ri].length; k++) {
              SBUInteger logical =
                  runs[ri].offset + (rtl ? runs[ri].length - 1u - k : k);
              m->cps[vi] = tmp[logical];
              m->map[vi] = shaped_map[logical];
              m->vspan[vi] = shaped_span[logical];
              m->vrtl[vi] = rtl ? 1u : 0u;
              vi++;
            }
          }
          if (vi != visual_len) {
            memcpy(m->cps, tmp, visual_len * sizeof(uint32_t));
            memcpy(m->map, shaped_map, visual_len * sizeof(uint32_t));
            memcpy(m->vspan, shaped_span, visual_len * sizeof(uint32_t));
            memset(m->vrtl, 0, visual_len);
          }
          my_mem_free(NULL, tmp);
        }
        SBLineRelease(line);
        /* UBA L4 (M12b): mirror glyphs at RTL embedding levels */
        for (i = 0; i < visual_len; i++) {
          if (m->vrtl[i] != 0) {
            m->cps[i] = tl_mirror_cp(m->cps[i]);
          }
        }
      }
      if (para != NULL) {
        SBParagraphRelease(para);
      }
      if (alg != NULL) {
        SBAlgorithmRelease(alg);
      }
      if (vi == visual_len) {
        m->has_rtl = has_rtl;
        m->rtl_base = base_rtl;
        reordered = true;
      }
    }
    if (!reordered) {
      m->has_rtl = false;
      m->rtl_base = false;
    }
    my_mem_free(NULL, shaped_map);
    my_mem_free(NULL, shaped_span);
  }
#else
  may = false; /* BIDI compiled out: always the identity layout */
#endif
  if (!may) {
    m->len = source_len;
    m->has_rtl = false;
    m->rtl_base = false;
  }
  for (i = 0; i < m->len; i++) {
    size_t k;
    for (k = 0; k < m->vspan[i]; k++) {
      if ((size_t)m->map[i] + k < m->logical_len) {
        m->inv[m->map[i] + k] = (uint32_t)i;
      }
    }
  }
  m->utf8 = tl_encode_all(NULL, m->cps, m->len);
  if (m->utf8 == NULL) {
    tl_master_free(m);
    return false;
  }
  return true;
}

/* ---------------- LRU cache ---------------- */

#define TL_CACHE_CAP 64u

static tl_master_t g_cache[TL_CACHE_CAP];
static uint64_t g_tick;

static my_text_layout_t* tl_copy(const my_allocator_t* alloc,
                                 const tl_master_t* m) {
  my_text_layout_t* l =
      (my_text_layout_t*)my_mem_calloc(alloc, 1, sizeof(my_text_layout_t));
  if (l == NULL) {
    return NULL;
  }
  l->allocator = alloc;
  l->len = m->len;
  l->logical_len = m->logical_len;
  l->has_rtl = m->has_rtl;
  l->rtl_base = m->rtl_base;
  if (m->len > 0) {
    l->visual_cps = (uint32_t*)my_mem_alloc(alloc, m->len * sizeof(uint32_t));
    l->visual_to_logical =
        (uint32_t*)my_mem_alloc(alloc, m->len * sizeof(uint32_t));
    l->visual_logical_span =
        (uint32_t*)my_mem_alloc(alloc, m->len * sizeof(uint32_t));
    l->logical_to_visual =
        (uint32_t*)my_mem_alloc(alloc, m->logical_len * sizeof(uint32_t));
    l->visual_rtl = (uint8_t*)my_mem_alloc(alloc, m->len);
    if (l->visual_cps == NULL || l->visual_to_logical == NULL ||
        l->visual_logical_span == NULL ||
        l->logical_to_visual == NULL || l->visual_rtl == NULL) {
      my_text_layout_destroy(l);
      return NULL;
    }
    memcpy(l->visual_cps, m->cps, m->len * sizeof(uint32_t));
    memcpy(l->visual_to_logical, m->map, m->len * sizeof(uint32_t));
    memcpy(l->visual_logical_span, m->vspan,
           m->len * sizeof(uint32_t));
    memcpy(l->logical_to_visual, m->inv,
           m->logical_len * sizeof(uint32_t));
    memcpy(l->visual_rtl, m->vrtl, m->len);
  }
  l->visual_utf8 = my_strdup(alloc, m->utf8 != NULL ? m->utf8 : "");
  l->logical_utf8 = my_strdup(alloc, m->text != NULL ? m->text : "");
  if (l->visual_utf8 == NULL || l->logical_utf8 == NULL) {
    my_text_layout_destroy(l);
    return NULL;
  }
  return l;
}

my_text_layout_t* my_text_layout_process(const my_allocator_t* allocator,
                                         const char* text) {
  size_t i, slot = 0, text_len;
  uint64_t oldest;
  if (text == NULL) {
    return NULL;
  }
  if (!tl_bounded_text_len(text, &text_len)) {
    return NULL;
  }
  g_tick++;
  for (i = 0; i < TL_CACHE_CAP; i++) {
    if (g_cache[i].text != NULL && strcmp(g_cache[i].text, text) == 0) {
      g_cache[i].tick = g_tick;
      return tl_copy(allocator, &g_cache[i]);
    }
  }
  /* miss: compute into the LRU slot (empty slot or oldest entry) */
  oldest = UINT64_MAX;
  for (i = 0; i < TL_CACHE_CAP; i++) {
    if (g_cache[i].text == NULL) {
      slot = i;
      break;
    }
    if (g_cache[i].tick < oldest) {
      oldest = g_cache[i].tick;
      slot = i;
    }
  }
  tl_master_free(&g_cache[slot]);
  if (!tl_master_compute(&g_cache[slot], text, text_len)) {
    return NULL;
  }
  g_cache[slot].tick = g_tick;
  return tl_copy(allocator, &g_cache[slot]);
}

void my_text_layout_destroy(my_text_layout_t* layout) {
  if (layout != NULL) {
    const my_allocator_t* alloc = layout->allocator;
    my_mem_free(alloc, layout->visual_cps);
    my_mem_free(alloc, layout->visual_to_logical);
    my_mem_free(alloc, layout->visual_logical_span);
    my_mem_free(alloc, layout->logical_to_visual);
    my_mem_free(alloc, layout->visual_rtl);
    my_mem_free(alloc, layout->visual_boundaries);
    my_mem_free(alloc, layout->logical_utf8);
    my_mem_free(alloc, layout->logical_byte_offsets);
    my_mem_free(alloc, layout->visual_shaped_span);
    my_mem_free(alloc, layout->visual_utf8);
    my_mem_free(alloc, layout);
  }
}

void my_text_layout_cache_flush(void) {
  size_t i;
  for (i = 0; i < TL_CACHE_CAP; i++) {
    tl_master_free(&g_cache[i]);
  }
}

size_t my_text_layout_cache_size(void) {
  size_t i, n = 0;
  for (i = 0; i < TL_CACHE_CAP; i++) {
    if (g_cache[i].text != NULL) {
      n++;
    }
  }
  return n;
}

static my_ret_t tl_shape_append(
    const my_allocator_t* allocator, my_font_shape_result_t* result,
    size_t* capacity, const my_font_shape_result_t* shaped,
    const size_t* run_offsets, const uint32_t* source_bytes,
    size_t run_count, size_t run_text_base, size_t run_text_len) {
  size_t required;
  size_t next_capacity;
  size_t i;
  my_font_shape_glyph_t* glyphs;

  if (shaped->count > SIZE_MAX - result->count) return MY_RET_OOM;
  required = result->count + shaped->count;
  if (required > *capacity) {
    next_capacity = *capacity > 0 ? *capacity : 8u;
    while (next_capacity < required) {
      if (next_capacity > SIZE_MAX / 2u) {
        next_capacity = required;
        break;
      }
      next_capacity *= 2u;
    }
    if (next_capacity > SIZE_MAX / sizeof(*result->glyphs)) {
      return MY_RET_OOM;
    }
    glyphs = (my_font_shape_glyph_t*)my_mem_realloc(
        allocator, result->glyphs,
        next_capacity * sizeof(*result->glyphs));
    if (glyphs == NULL) return MY_RET_OOM;
    result->glyphs = glyphs;
    *capacity = next_capacity;
  }
  for (i = 0; i < shaped->count; i++) {
    my_font_shape_glyph_t glyph = shaped->glyphs[i];
    size_t lo = 0;
    size_t hi = run_count;
    if (glyph.cluster > SIZE_MAX - run_text_base || run_count == 0) {
      return MY_RET_FAIL;
    }
    {
      size_t cluster = run_text_base + glyph.cluster;
      if (run_text_len > SIZE_MAX - run_text_base ||
          cluster < run_text_base ||
          cluster >= run_text_base + run_text_len) {
        return MY_RET_FAIL;
      }
      while (lo + 1u < hi) {
        size_t mid = lo + (hi - lo) / 2u;
        if (run_offsets[mid] <= cluster) {
          lo = mid;
        } else {
          hi = mid;
        }
      }
      if (cluster != run_offsets[lo]) return MY_RET_FAIL;
    }
    glyph.cluster = source_bytes[lo];
    result->glyphs[result->count++] = glyph;
  }
  return MY_RET_OK;
}

static my_ret_t tl_shape_run(my_font_t* font, const char* text, int32_t size,
                             const my_font_shape_params_t* params,
                             const my_allocator_t* allocator,
                             my_font_shape_result_t* result) {
  my_ret_t ret = my_font_shape_ex(font, text, size, params, allocator, result);
  if (ret == MY_RET_NOT_SUPPORTED && params->script != 0u &&
      params->language == NULL && params->features == NULL) {
    ret = my_font_shape(font, text, size, params->rtl, allocator, result);
  }
  return ret;
}

my_ret_t my_text_layout_shape_ex(
    const my_text_layout_t* layout, const char* logical_text, my_font_t* font,
    int32_t size, const my_font_shape_params_t* params,
    const my_allocator_t* allocator, my_font_shape_result_t* result) {
  uint32_t* source_cps = NULL;
  uint32_t* source_bytes = NULL;
  bool* seen = NULL;
  size_t text_len;
  size_t source_count = 0;
  size_t capacity = 0;
  size_t visual_start = 0;
  size_t i;
  my_ret_t ret = MY_RET_OK;
  my_font_shape_params_t default_params = {false, 0u, NULL, NULL};
  const my_font_shape_params_t* effective_params =
      params != NULL ? params : &default_params;

  if (result == NULL) return MY_RET_INVALID_PARAMS;
  memset(result, 0, sizeof(*result));
  result->allocator = allocator;
  result->rtl = layout != NULL ? layout->rtl_base : false;
  if (layout == NULL || logical_text == NULL || font == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (!tl_bounded_text_len(logical_text, &text_len)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (layout->logical_utf8 == NULL || strcmp(layout->logical_utf8,
                                             logical_text) != 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (layout->logical_len > SIZE_MAX / sizeof(*source_cps) ||
      layout->logical_len > SIZE_MAX / sizeof(*source_bytes) ||
      layout->logical_len > SIZE_MAX / sizeof(*seen)) {
    return MY_RET_OOM;
  }
  if (layout->logical_len > 0) {
    source_cps = (uint32_t*)my_mem_alloc(
        allocator, layout->logical_len * sizeof(*source_cps));
    source_bytes = (uint32_t*)my_mem_alloc(
        allocator, layout->logical_len * sizeof(*source_bytes));
    seen = (bool*)my_mem_calloc(allocator, layout->logical_len,
                                sizeof(*seen));
    if (source_cps == NULL || source_bytes == NULL || seen == NULL) {
      ret = MY_RET_OOM;
      goto done;
    }
  }
  {
    const char* p = logical_text;
    while (*p != '\0') {
      const char* next = p;
      if (source_count >= layout->logical_len) {
        ret = MY_RET_INVALID_PARAMS;
        goto done;
      }
      source_bytes[source_count] = (uint32_t)(p - logical_text);
      source_cps[source_count++] = my_utf8_next(&next);
      p = next;
    }
  }
  if (source_count != layout->logical_len || text_len > UINT32_MAX) {
    ret = MY_RET_INVALID_PARAMS;
    goto done;
  }
  if (layout->len == 0) {
    if (layout->logical_len != 0) ret = MY_RET_INVALID_PARAMS;
    goto done;
  }
  if (layout->visual_to_logical == NULL ||
      layout->visual_logical_span == NULL || layout->visual_rtl == NULL) {
    ret = MY_RET_INVALID_PARAMS;
    goto done;
  }

  while (visual_start < layout->len) {
    size_t visual_end = visual_start + 1u;
    bool rtl = layout->visual_rtl[visual_start] != 0;
    size_t run_count = 0;
    size_t units = 0;
    size_t run_text_len = 0;
    size_t run_bytes_capacity;
    char* run_text = NULL;
    size_t* run_offsets = NULL;
    uint32_t* run_sources = NULL;
    uint32_t* run_logical = NULL;
    uint32_t* run_scripts = NULL;
    my_font_shape_result_t shaped = {0};
    bool split_scripts = effective_params->script == 0u &&
                         font->vtable != NULL &&
                         font->vtable->shape_ex != NULL;

    while (visual_end < layout->len &&
           (layout->visual_rtl[visual_end] != 0) == rtl) {
      visual_end++;
    }
    for (i = visual_start; i < visual_end; i++) {
      size_t span = layout->visual_logical_span[i];
      if (span == 0 || layout->visual_to_logical[i] > layout->logical_len ||
          span > layout->logical_len - layout->visual_to_logical[i] ||
          run_count > SIZE_MAX - span) {
        ret = MY_RET_INVALID_PARAMS;
        goto run_done;
      }
      run_count += span;
    }
    if (run_count == 0 || run_count > SIZE_MAX / 4u ||
        run_count + 1u < run_count) {
      ret = MY_RET_OOM;
      goto run_done;
    }
    run_bytes_capacity = run_count * 4u + 1u;
    if (run_count > SIZE_MAX / sizeof(*run_offsets) ||
        run_count > SIZE_MAX / sizeof(*run_sources)) {
      ret = MY_RET_OOM;
      goto run_done;
    }
    run_text = (char*)my_mem_alloc(allocator, run_bytes_capacity);
    run_offsets = (size_t*)my_mem_alloc(allocator,
                                        run_count * sizeof(*run_offsets));
    run_sources = (uint32_t*)my_mem_alloc(allocator,
                                          run_count * sizeof(*run_sources));
    if (split_scripts) {
      run_logical = (uint32_t*)my_mem_alloc(
          allocator, run_count * sizeof(*run_logical));
      run_scripts = (uint32_t*)my_mem_alloc(
          allocator, run_count * sizeof(*run_scripts));
    }
    if (run_text == NULL || run_offsets == NULL || run_sources == NULL ||
        (split_scripts && (run_logical == NULL || run_scripts == NULL))) {
      ret = MY_RET_OOM;
      goto run_done;
    }
    if (rtl) {
      for (i = visual_end; i > visual_start; i--) {
        size_t vi = i - 1u;
        size_t logical = layout->visual_to_logical[vi];
        size_t k;
        for (k = 0; k < layout->visual_logical_span[vi]; k++) {
          size_t source = logical + k;
          size_t encoded;
          if (seen[source]) {
            ret = MY_RET_INVALID_PARAMS;
            goto run_done;
          }
          seen[source] = true;
          run_offsets[units] = run_text_len;
          run_sources[units] = source_bytes[source];
          if (split_scripts) run_logical[units] = (uint32_t)source;
          encoded = tl_utf8_encode(source_cps[source],
                                   run_text + run_text_len);
          if (encoded > run_bytes_capacity - run_text_len - 1u) {
            ret = MY_RET_OOM;
            goto run_done;
          }
          run_text_len += encoded;
          units++;
        }
      }
    } else {
      for (i = visual_start; i < visual_end; i++) {
        size_t logical = layout->visual_to_logical[i];
        size_t k;
        for (k = 0; k < layout->visual_logical_span[i]; k++) {
          size_t source = logical + k;
          size_t encoded;
          if (seen[source]) {
            ret = MY_RET_INVALID_PARAMS;
            goto run_done;
          }
          seen[source] = true;
          run_offsets[units] = run_text_len;
          run_sources[units] = source_bytes[source];
          if (split_scripts) run_logical[units] = (uint32_t)source;
          encoded = tl_utf8_encode(source_cps[source],
                                   run_text + run_text_len);
          if (encoded > run_bytes_capacity - run_text_len - 1u) {
            ret = MY_RET_OOM;
            goto run_done;
          }
          run_text_len += encoded;
          units++;
        }
      }
    }
    if (units != run_count) {
      ret = MY_RET_INVALID_PARAMS;
      goto run_done;
    }
    if (split_scripts) {
      for (i = 0u; i < units; ++i) {
        run_scripts[i] = tl_script_tag(source_cps[run_logical[i]]);
      }
      {
        uint32_t previous_script = 0u;
        for (i = 0u; i < units; ++i) {
          if (run_scripts[i] != 0u) {
            previous_script = run_scripts[i];
          } else if (previous_script != 0u) {
            run_scripts[i] = previous_script;
          }
        }
      }
      {
        uint32_t next_script = 0u;
        for (i = units; i > 0u; --i) {
          size_t index = i - 1u;
          if (run_scripts[index] != 0u) {
            next_script = run_scripts[index];
          } else {
            run_scripts[index] = next_script;
          }
        }
      }
    }
    run_text[run_text_len] = '\0';
    if (!split_scripts) {
      my_font_shape_params_t run_params = *effective_params;
      run_params.rtl = rtl;
      ret = tl_shape_run(font, run_text, size, &run_params, allocator,
                         &shaped);
      if (ret == MY_RET_OK) {
        ret = tl_shape_append(allocator, result, &capacity, &shaped,
                              run_offsets, run_sources, run_count, 0u,
                              run_text_len);
      }
      my_font_shape_destroy(&shaped);
    } else {
      size_t segment_cursor = rtl ? units : 0u;
      while ((rtl && segment_cursor > 0u) ||
             (!rtl && segment_cursor < units)) {
        size_t segment_start;
        size_t segment_end;
        uint32_t script;
        my_font_shape_params_t run_params = *effective_params;
        if (rtl) {
          segment_end = segment_cursor;
          script = run_scripts[segment_cursor - 1u];
          segment_start = segment_cursor - 1u;
          while (segment_start > 0u &&
                 run_scripts[segment_start - 1u] == script) {
            segment_start--;
          }
        } else {
          segment_start = segment_cursor;
          segment_end = segment_start + 1u;
          script = run_scripts[segment_start];
          while (segment_end < units && run_scripts[segment_end] == script) {
            segment_end++;
          }
        }
        run_params.rtl = rtl;
        run_params.script = script;
        {
          size_t segment_base = run_offsets[segment_start];
          size_t segment_limit = segment_end < units
                                     ? run_offsets[segment_end]
                                     : run_text_len;
          char saved = run_text[segment_limit];
          run_text[segment_limit] = '\0';
          ret = tl_shape_run(font, run_text + segment_base, (int32_t)size,
                             &run_params, allocator, &shaped);
          if (ret == MY_RET_OK) {
            ret = tl_shape_append(
                allocator, result, &capacity, &shaped,
                run_offsets + segment_start, run_sources + segment_start,
                segment_end - segment_start, segment_base,
                segment_limit - segment_base);
          }
          run_text[segment_limit] = saved;
        }
        my_font_shape_destroy(&shaped);
        if (ret != MY_RET_OK) break;
        segment_cursor = rtl ? segment_start : segment_end;
      }
    }

  run_done:
    my_mem_free(allocator, run_scripts);
    my_mem_free(allocator, run_logical);
    my_mem_free(allocator, run_sources);
    my_mem_free(allocator, run_offsets);
    my_mem_free(allocator, run_text);
    if (ret != MY_RET_OK) goto done;
    visual_start = visual_end;
  }
  for (i = 0; i < layout->logical_len; i++) {
    if (!seen[i]) {
      ret = MY_RET_INVALID_PARAMS;
      goto done;
    }
  }
  result->used_complex_shaping = true;

done:
  my_mem_free(allocator, seen);
  my_mem_free(allocator, source_bytes);
  my_mem_free(allocator, source_cps);
  if (ret != MY_RET_OK) my_font_shape_destroy(result);
  return ret;
}

my_ret_t my_text_layout_shape(const my_text_layout_t* layout,
                              const char* logical_text, my_font_t* font,
                              int32_t size, const my_allocator_t* allocator,
                              my_font_shape_result_t* result) {
  my_font_shape_params_t params = {
      layout != NULL && layout->rtl_base, 0u, NULL, NULL};
  return my_text_layout_shape_ex(layout, logical_text, font, size, &params,
                                 allocator, result);
}

/* ---------------- boundary <-> visual (M12a) ---------------- */

/** @brief Width of one visual codepoint (glyph advance; 8px cell when
 * font is NULL). */
static float tl_cp_w(const my_font_t* font, int32_t size, uint32_t cp) {
  my_glyph_t g;
  if (font == NULL) {
    return 8.0f;
  }
  if (font->vtable == NULL || font->vtable->get_glyph == NULL) {
    return 0.0f;
  }
  if (my_font_get_glyph((my_font_t*)font, cp, size, &g) != MY_RET_OK) {
    return 0.0f;
  }
  return (float)g.advance;
}

static bool tl_logical_offsets_ensure(my_text_layout_t* l) {
  size_t i;
  const char* p;
  uint32_t* offsets;
  if (l == NULL || l->logical_utf8 == NULL) return false;
  if (l->logical_byte_offsets != NULL &&
      l->logical_byte_offsets_capacity >= l->logical_len) {
    return true;
  }
  if (l->logical_len > SIZE_MAX / sizeof(*offsets)) return false;
  offsets = (uint32_t*)my_mem_realloc(
      l->allocator, l->logical_byte_offsets,
      (l->logical_len > 0 ? l->logical_len : 1) * sizeof(*offsets));
  if (offsets == NULL) return false;
  l->logical_byte_offsets = offsets;
  l->logical_byte_offsets_capacity = 0;
  p = l->logical_utf8;
  for (i = 0; i < l->logical_len; i++) {
    const char* next = p;
    size_t byte = (size_t)(p - l->logical_utf8);
    if (byte > UINT32_MAX) {
      my_mem_free(l->allocator, offsets);
      l->logical_byte_offsets = NULL;
      return false;
    }
    offsets[i] = (uint32_t)byte;
    (void)my_utf8_next(&next);
    if (next <= p) {
      my_mem_free(l->allocator, offsets);
      l->logical_byte_offsets = NULL;
      return false;
    }
    p = next;
  }
  if (*p != '\0') {
    my_mem_free(l->allocator, offsets);
    l->logical_byte_offsets = NULL;
    return false;
  }
  l->logical_byte_offsets_capacity = l->logical_len;
  return true;
}

static size_t tl_logical_index_for_byte(const my_text_layout_t* l,
                                        uint32_t byte) {
  size_t lo = 0;
  size_t hi = l->logical_len;
  while (lo < hi) {
    size_t mid = lo + (hi - lo) / 2u;
    if (l->logical_byte_offsets[mid] < byte) {
      lo = mid + 1u;
    } else if (l->logical_byte_offsets[mid] > byte) {
      hi = mid;
    } else {
      return mid;
    }
  }
  return l->logical_len;
}

static bool tl_boundaries_from_shaping(my_text_layout_t* l,
                                       const my_font_t* font, int32_t size) {
  my_font_shape_result_t shaped = {0};
  int64_t* advances = NULL;
  uint8_t* cluster_starts = NULL;
  uint32_t* shaped_span = NULL;
  int64_t width;
  my_ret_t ret;
  size_t i;
  if (font == NULL || l->logical_utf8 == NULL ||
      !tl_logical_offsets_ensure(l)) {
    return false;
  }
  ret = my_text_layout_shape(l, l->logical_utf8, (my_font_t*)font, size,
                             l->allocator, &shaped);
  if (ret != MY_RET_OK) return false;
  if (l->len > 0) {
    if (l->len > SIZE_MAX / sizeof(*advances)) {
      my_font_shape_destroy(&shaped);
      return false;
    }
    advances = (int64_t*)my_mem_calloc(l->allocator, l->len,
                                       sizeof(*advances));
    if (advances == NULL) {
      my_font_shape_destroy(&shaped);
      return false;
    }
  }
  if (l->logical_len > 0) {
    if (l->logical_len > SIZE_MAX / sizeof(*cluster_starts)) {
      my_mem_free(l->allocator, advances);
      my_font_shape_destroy(&shaped);
      return false;
    }
    cluster_starts = (uint8_t*)my_mem_calloc(l->allocator, l->logical_len,
                                             sizeof(*cluster_starts));
    if (cluster_starts == NULL) {
      my_mem_free(l->allocator, advances);
      my_font_shape_destroy(&shaped);
      return false;
    }
  }
  for (i = 0; i < shaped.count; i++) {
    size_t logical = tl_logical_index_for_byte(l,
                                               shaped.glyphs[i].cluster);
    size_t visual;
    if (logical >= l->logical_len) {
      my_mem_free(l->allocator, cluster_starts);
      my_mem_free(l->allocator, advances);
      my_font_shape_destroy(&shaped);
      return false;
    }
    cluster_starts[logical] = 1;
    visual = l->logical_to_visual[logical];
    if (visual >= l->len) {
      my_mem_free(l->allocator, cluster_starts);
      my_mem_free(l->allocator, advances);
      my_font_shape_destroy(&shaped);
      return false;
    }
    if ((shaped.glyphs[i].advance_x_26_6 > 0 &&
         advances[visual] > INT64_MAX -
                              shaped.glyphs[i].advance_x_26_6) ||
        (shaped.glyphs[i].advance_x_26_6 < 0 &&
        advances[visual] < INT64_MIN -
                              shaped.glyphs[i].advance_x_26_6)) {
      my_mem_free(l->allocator, cluster_starts);
      my_mem_free(l->allocator, advances);
      my_font_shape_destroy(&shaped);
      return false;
    }
    advances[visual] += shaped.glyphs[i].advance_x_26_6;
  }
  if (l->len > 0) {
    if (l->len > SIZE_MAX / sizeof(*shaped_span)) {
      my_mem_free(l->allocator, cluster_starts);
      my_mem_free(l->allocator, advances);
      my_font_shape_destroy(&shaped);
      return false;
    }
    shaped_span = (uint32_t*)my_mem_alloc(
        l->allocator, l->len * sizeof(*shaped_span));
    if (shaped_span == NULL) {
      my_mem_free(l->allocator, cluster_starts);
      my_mem_free(l->allocator, advances);
      my_font_shape_destroy(&shaped);
      return false;
    }
    for (i = 0; i < l->len; i++) {
      shaped_span[i] = l->visual_logical_span[i];
    }
    {
      size_t next_start = l->logical_len;
      for (i = l->logical_len; i > 0; i--) {
        size_t logical = i - 1u;
        if (cluster_starts[logical] != 0) {
          size_t visual = l->logical_to_visual[logical];
          size_t span = next_start - logical;
          if (visual < l->len && span > shaped_span[visual]) {
            shaped_span[visual] = span > UINT32_MAX ? UINT32_MAX
                                                    : (uint32_t)span;
          }
          next_start = logical;
        }
      }
    }
  }
  for (i = 0; i < l->len; i++) {
    if (advances[i] > INT64_MAX - 32) {
      width = INT64_MAX;
    } else if (advances[i] < INT64_MIN + 32) {
      width = INT64_MIN;
    } else {
      width = advances[i] >= 0 ? (advances[i] + 32) / 64
                               : (advances[i] - 32) / 64;
    }
    if (width > INT32_MAX) width = INT32_MAX;
    if (width < INT32_MIN) width = INT32_MIN;
    if (width < 0) width = 0;
    l->visual_boundaries[i + 1] = (int32_t)width;
  }
  my_mem_free(l->allocator, cluster_starts);
  my_mem_free(l->allocator, advances);
  my_mem_free(l->allocator, l->visual_shaped_span);
  l->visual_shaped_span = shaped_span;
  l->visual_shaped_span_capacity = l->len;
  l->visual_shaped_span_font = font;
  l->visual_shaped_span_size = size;
  my_font_shape_destroy(&shaped);
  return true;
}

static bool tl_boundaries_ensure(const my_text_layout_t* layout,
                                 const my_font_t* font, int32_t size) {
  my_text_layout_t* l = (my_text_layout_t*)layout;
  size_t required;
  size_t i;
  int32_t* grown;
  int64_t total = 0;
  if (l == NULL || l->len == SIZE_MAX) return false;
  required = l->len + 1;
  if (l->visual_boundaries != NULL &&
      l->visual_boundaries_capacity >= required &&
      l->visual_boundaries_font == font &&
      l->visual_boundaries_size == size) {
    return true;
  }
  if (required > SIZE_MAX / sizeof(*l->visual_boundaries)) return false;
  grown = (int32_t*)my_mem_realloc(l->allocator, l->visual_boundaries,
                                   required * sizeof(*grown));
  if (grown == NULL) return false;
  l->visual_boundaries = grown;
  l->visual_boundaries[0] = 0;
  my_mem_free(l->allocator, l->visual_shaped_span);
  l->visual_shaped_span = NULL;
  l->visual_shaped_span_capacity = 0;
  l->visual_shaped_span_font = NULL;
  l->visual_shaped_span_size = 0;
  if (!tl_boundaries_from_shaping(l, font, size)) {
    for (i = 0; i < l->len; i++) {
      total += (int64_t)tl_cp_w(font, size, l->visual_cps[i]);
      if (total > INT32_MAX) total = INT32_MAX;
      if (total < 0) total = 0;
      l->visual_boundaries[i + 1] = (int32_t)total;
    }
  } else {
    total = 0;
    for (i = 0; i < l->len; i++) {
      total += (int64_t)l->visual_boundaries[i + 1];
      if (total > INT32_MAX) total = INT32_MAX;
      if (total < 0) total = 0;
      l->visual_boundaries[i + 1] = (int32_t)total;
    }
  }
  l->visual_boundaries_capacity = required;
  l->visual_boundaries_font = font;
  l->visual_boundaries_size = size;
  return true;
}

static size_t tl_visual_span_for(const my_text_layout_t* layout,
                                 const my_font_t* font, int32_t size,
                                 size_t visual) {
  if (layout->visual_shaped_span != NULL &&
      layout->visual_shaped_span_capacity > visual &&
      layout->visual_shaped_span_font == font &&
      layout->visual_shaped_span_size == size) {
    return layout->visual_shaped_span[visual];
  }
  return layout->visual_logical_span[visual];
}

/** @brief Visual boundary index (0..len) of a logical boundary:
 * previous logical codepoint's logical-trailing edge. */
static size_t tl_vb_of_lb(const my_text_layout_t* l, size_t b) {
  size_t vi;
  size_t end;
  if (l->logical_len == 0 || l->len == 0) {
    return 0;
  }
  if (b == 0) {
    /* leading edge of logical cp 0 */
    vi = l->logical_to_visual[0];
    return l->visual_rtl[vi] != 0 ? vi + 1 : vi;
  }
  if (b > l->logical_len) {
    b = l->logical_len;
  }
  vi = l->logical_to_visual[b - 1];
  end = (size_t)l->visual_to_logical[vi];
  if (l->visual_logical_span[vi] > SIZE_MAX - end) {
    end = SIZE_MAX;
  } else {
    end += l->visual_logical_span[vi];
  }
  if (l->visual_logical_span[vi] > 1u && b < end) {
    return l->visual_rtl[vi] != 0 ? vi : vi + 1;
  }
  return l->visual_rtl[vi] != 0 ? vi : vi + 1;
}

/** @brief Logical boundary at a visual boundary (previous visual
 * codepoint's trailing edge). */
static size_t tl_lb_of_vb(const my_text_layout_t* l, size_t v) {
  size_t prev;
  size_t end;
  if (l->len == 0 || v == 0) {
    if (l->len == 0) {
      return 0;
    }
    if (l->visual_rtl[0] != 0) {
      end = l->visual_to_logical[0];
      if (l->visual_logical_span[0] > SIZE_MAX - end) {
        return l->logical_len;
      }
      end += l->visual_logical_span[0];
      return end > l->logical_len ? l->logical_len : end;
    }
    return l->visual_to_logical[0];
  }
  if (v > l->len) {
    v = l->len;
  }
  prev = v - 1;
  if (l->visual_rtl[prev] != 0) {
    return l->visual_to_logical[prev];
  }
  end = l->visual_to_logical[prev];
  if (l->visual_logical_span[prev] > SIZE_MAX - end) {
    return l->logical_len;
  }
  end += l->visual_logical_span[prev];
  return end > l->logical_len ? l->logical_len : end;
}

static size_t tl_lb_of_vb_font(const my_text_layout_t* l, size_t v,
                               const my_font_t* font, int32_t size) {
  size_t prev;
  size_t end;
  size_t span;
  if (l->len == 0 || v == 0) {
    if (l->len == 0) return 0;
    if (l->visual_rtl[0] != 0) {
      end = l->visual_to_logical[0];
      span = tl_visual_span_for(l, font, size, 0);
      if (span > SIZE_MAX - end) return l->logical_len;
      end += span;
      return end > l->logical_len ? l->logical_len : end;
    }
    return l->visual_to_logical[0];
  }
  if (v > l->len) v = l->len;
  prev = v - 1u;
  if (l->visual_rtl[prev] != 0) return l->visual_to_logical[prev];
  end = l->visual_to_logical[prev];
  span = tl_visual_span_for(l, font, size, prev);
  if (span > SIZE_MAX - end) return l->logical_len;
  end += span;
  return end > l->logical_len ? l->logical_len : end;
}

/* At run transitions two logical boundaries can share one visual spot
 * (the classic dual-cursor situation -- we stay single-cursor, so only
 * one of them is "canonical" there). Arrow keys and clicks therefore
 * walk CANONICAL visual boundaries only: a visual boundary v is
 * canonical when the round trip lands back on v. Alias boundaries
 * remain reachable via logical ops (typing, Backspace, Home/End). */
static bool tl_canonical(const my_text_layout_t* l, size_t v) {
  return tl_vb_of_lb(l, tl_lb_of_vb(l, v)) == v;
}

/** @brief Nearest canonical visual boundary at or after v (<= len). */
static size_t tl_canon_right(const my_text_layout_t* l, size_t v) {
  while (v < l->len && !tl_canonical(l, v)) {
    v++;
  }
  return v;
}

/** @brief Nearest canonical visual boundary at or before v. */
static size_t tl_canon_left(const my_text_layout_t* l, size_t v) {
  while (v > 0 && !tl_canonical(l, v)) {
    v--;
  }
  return v;
}

int32_t my_text_layout_visual_x(const my_text_layout_t* l,
                                const my_font_t* font, int32_t size,
                                size_t logical_boundary) {
  size_t v, i;
  float x = 0.0f;
  if (l == NULL) {
    return 0;
  }
  v = tl_vb_of_lb(l, logical_boundary);
  if (tl_boundaries_ensure(l, font, size) && v <= l->len) {
    return l->visual_boundaries[v];
  }
  for (i = 0; i < v; i++) {
    x += tl_cp_w(font, size, l->visual_cps[i]);
  }
  return (int32_t)(x + 0.5f);
}

int32_t my_text_layout_visual_boundary_x(const my_text_layout_t* l,
                                         const my_font_t* font, int32_t size,
                                         size_t visual_boundary) {
  float x = 0.0f;
  size_t i;
  if (l == NULL) return 0;
  if (visual_boundary > l->len) visual_boundary = l->len;
  if (tl_boundaries_ensure(l, font, size)) {
    return l->visual_boundaries[visual_boundary];
  }
  for (i = 0; i < visual_boundary; i++) {
    x += tl_cp_w(font, size, l->visual_cps[i]);
  }
  return (int32_t)(x + 0.5f);
}

size_t my_text_layout_logical_at_x(const my_text_layout_t* l,
                                   const my_font_t* font, int32_t size,
                                   int32_t x) {
  float acc = 0.0f;
  size_t i;
  if (l == NULL || l->len == 0) {
    return 0;
  }
  if (x <= 0) {
    return tl_lb_of_vb_font(l, 0, font, size);
  }
  if (tl_boundaries_ensure(l, font, size)) {
    size_t lo = 0;
    size_t hi = l->len;
    while (lo < hi) {
      size_t mid = lo + (hi - lo) / 2;
      if ((int64_t)x < l->visual_boundaries[mid]) {
        hi = mid;
      } else if ((int64_t)x >= l->visual_boundaries[mid + 1]) {
        lo = mid + 1;
      } else {
        int32_t width = l->visual_boundaries[mid + 1] -
                        l->visual_boundaries[mid];
        int64_t midpoint = (int64_t)l->visual_boundaries[mid] +
                           ((int64_t)width + 1) / 2;
        if ((int64_t)x < midpoint) {
          return tl_lb_of_vb_font(l, tl_canon_left(l, mid), font, size);
        }
        return tl_lb_of_vb_font(l, tl_canon_right(l, mid + 1), font,
                                size);
      }
    }
    return tl_lb_of_vb_font(l, l->len, font, size);
  }
  for (i = 0; i < l->len; i++) {
    float w = tl_cp_w(font, size, l->visual_cps[i]);
    if ((float)x < acc + w / 2.0f) {
      /* left half: nearest canonical boundary at or before visual i */
      return tl_lb_of_vb(l, tl_canon_left(l, i));
    }
    if ((float)x < acc + w) {
      /* right half: nearest canonical boundary at or after visual i+1 */
      return tl_lb_of_vb(l, tl_canon_right(l, i + 1));
    }
    acc += w;
  }
  return tl_lb_of_vb(l, l->len);
}

size_t my_text_layout_boundary_left(const my_text_layout_t* l,
                                    size_t logical_boundary) {
  size_t v;
  if (l == NULL || l->len == 0) {
    return 0;
  }
  v = tl_vb_of_lb(l, logical_boundary);
  if (v == 0) {
    return tl_lb_of_vb(l, 0); /* already at the visual start */
  }
  return tl_lb_of_vb(l, tl_canon_left(l, v - 1));
}

size_t my_text_layout_boundary_right(const my_text_layout_t* l,
                                     size_t logical_boundary) {
  size_t v;
  if (l == NULL || l->len == 0) {
    return 0;
  }
  v = tl_vb_of_lb(l, logical_boundary);
  if (v >= l->len) {
    return tl_lb_of_vb(l, l->len); /* already at the visual end */
  }
  return tl_lb_of_vb(l, tl_canon_right(l, v + 1));
}

size_t my_text_layout_boundary_home(const my_text_layout_t* l) {
  if (l == NULL) {
    return 0;
  }
  return tl_lb_of_vb(l, 0);
}

size_t my_text_layout_boundary_end(const my_text_layout_t* l) {
  if (l == NULL) {
    return 0;
  }
  return tl_lb_of_vb(l, l->len);
}

size_t my_text_layout_visual_of_logical(const my_text_layout_t* l,
                                        size_t logical_boundary) {
  if (l == NULL) {
    return 0;
  }
  return tl_vb_of_lb(l, logical_boundary);
}

size_t my_text_layout_logical_at_visual(const my_text_layout_t* l,
                                        size_t visual_boundary) {
  if (l == NULL) {
    return 0;
  }
  return tl_lb_of_vb(l, visual_boundary);
}

size_t my_text_layout_visual_rects(const my_text_layout_t* l,
                                   const my_font_t* font, int32_t size,
                                   size_t l0, size_t l1, my_rectf_t* out,
                                   size_t cap) {
  size_t j, n = 0;
  float x = 0.0f;
  bool open = false;
  float seg_x = 0.0f, seg_w = 0.0f;
  if (l == NULL || out == NULL || cap == 0 || l0 >= l1 ||
      l0 >= l->logical_len) {
    return 0;
  }
  if (l1 > l->logical_len) {
    l1 = l->logical_len;
  }
  if (tl_boundaries_ensure(l, font, size)) {
    for (j = 0; j < l->len; j++) {
      int32_t width = l->visual_boundaries[j + 1] -
                      l->visual_boundaries[j];
      size_t start = l->visual_to_logical[j];
      size_t end = start;
      bool in_sel;
      size_t span = tl_visual_span_for(l, font, size, j);
      if (span > SIZE_MAX - end) {
        end = SIZE_MAX;
      } else {
        end += span;
      }
      if (end > l->logical_len) end = l->logical_len;
      in_sel = start < l1 && end > l0;
      if (in_sel && !open) {
        open = true;
        seg_x = x;
        seg_w = 0.0f;
      }
      if (in_sel) seg_w += (float)width;
      if (open && (!in_sel || j + 1 == l->len)) {
        if (n < cap) out[n] = my_rectf_init(seg_x, 0.0f, seg_w, 0.0f);
        n++;
        open = false;
        if (n == cap) return cap;
      }
      x += (float)width;
    }
    return n;
  }
  for (j = 0; j < l->len; j++) {
    float w = tl_cp_w(font, size, l->visual_cps[j]);
    size_t start = l->visual_to_logical[j];
    size_t end = start;
    {
      size_t span = tl_visual_span_for(l, font, size, j);
      if (span > SIZE_MAX - end) {
        end = SIZE_MAX;
      } else {
        end += span;
      }
    }
    if (end > l->logical_len) {
      end = l->logical_len;
    }
    bool in_sel = start < l1 && end > l0;
    if (in_sel && !open) {
      open = true;
      seg_x = x;
      seg_w = 0.0f;
    }
    if (in_sel) {
      seg_w += w;
    }
    if (open && (!in_sel || j + 1 == l->len)) {
      if (n < cap) {
        out[n] = my_rectf_init(seg_x, 0.0f, seg_w, 0.0f);
      }
      n++;
      open = false;
      if (n == cap) return cap;
    }
    x += w;
  }
  return n;
}
