/**
 * @file my_text_layout.c
 * @brief Text layout implementation (M11a): decode -> fast path ->
 * Arabic shaping -> SheenBidi UBA reorder; LRU-cached masters.
 */
#include "myr/my_text_layout.h"

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

static uint32_t* tl_decode(const my_allocator_t* alloc, const char* text,
                           size_t* out_len) {
  size_t cap = strlen(text) + 1, n = 0;
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
  char* s = (char*)my_mem_alloc(alloc, len * 4 + 1);
  size_t i, n = 0;
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

/* ---------------- layout master (cache payload) ---------------- */

typedef struct tl_master_t {
  char* text;  /**< key (owned copy) */
  uint32_t* cps;
  uint32_t* map;
  uint32_t* inv;   /**< logical_to_visual */
  uint8_t* vrtl;   /**< per visual cp: run is RTL */
  char* utf8;
  size_t len;
  bool has_rtl;
  bool rtl_base; /**< paragraph base direction is RTL (M13b) */
  uint64_t tick;
} tl_master_t;

static void tl_master_free(tl_master_t* m) {
  my_mem_free(NULL, m->text);
  my_mem_free(NULL, m->cps);
  my_mem_free(NULL, m->map);
  my_mem_free(NULL, m->inv);
  my_mem_free(NULL, m->vrtl);
  my_mem_free(NULL, m->utf8);
  memset(m, 0, sizeof(*m));
}

/** @brief Compute the master: decode, shape (BIDI), reorder (BIDI). */
static bool tl_master_compute(tl_master_t* m, const char* text) {
  size_t len = 0, i;
  bool may;
  memset(m, 0, sizeof(*m));
  m->text = my_strdup(NULL, text);
  m->cps = tl_decode(NULL, text, &len);
  if (m->text == NULL || m->cps == NULL) {
    tl_master_free(m);
    return false;
  }
  m->len = len;
  m->map = (uint32_t*)my_mem_alloc(NULL, (len > 0 ? len : 1) * sizeof(uint32_t));
  m->inv = (uint32_t*)my_mem_alloc(NULL, (len > 0 ? len : 1) * sizeof(uint32_t));
  m->vrtl = (uint8_t*)my_mem_calloc(NULL, (len > 0 ? len : 1), 1);
  if (m->map == NULL || m->inv == NULL || m->vrtl == NULL) {
    tl_master_free(m);
    return false;
  }
  may = false;
  for (i = 0; i < len; i++) {
    if (tl_cp_needs_bidi(m->cps[i])) {
      may = true;
      break;
    }
  }
#if defined(MYUI_BIDI)
  if (may && len > 0) {
    /* Arabic joining first (context = logical neighbours), then UBA;
     * lam-alef ligatures compact the sequence (M12b) */
    len = my_arabic_shape(m->cps, len);
    m->len = len;
    {
      SBCodepointSequence seq = {SBStringEncodingUTF32, m->cps, len};
      SBAlgorithmRef alg = SBAlgorithmCreate(&seq);
      SBParagraphRef para = NULL;
      SBLineRef line = NULL;
      const SBRun* runs = NULL;
      size_t run_count = 0, vi = 0, ri;
      bool has_rtl = false;
      bool base_rtl = false;
      if (alg != NULL) {
        para = SBAlgorithmCreateParagraph(alg, 0, len, SBLevelDefaultLTR);
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
          uint32_t* tmp = (uint32_t*)my_mem_alloc(NULL, len * sizeof(uint32_t));
          if (tmp == NULL) {
            SBLineRelease(line);
            SBParagraphRelease(para);
            SBAlgorithmRelease(alg);
            tl_master_free(m);
            return false;
          }
          memcpy(tmp, m->cps, len * sizeof(uint32_t));
          for (ri = 0; ri < run_count; ri++) {
            SBUInteger k;
            bool rtl = (runs[ri].level & 1u) != 0;
            has_rtl = has_rtl || rtl;
            for (k = 0; k < runs[ri].length; k++) {
              SBUInteger logical =
                  runs[ri].offset + (rtl ? runs[ri].length - 1u - k : k);
              m->cps[vi] = tmp[logical];
              m->map[vi] = (uint32_t)logical;
              m->vrtl[vi] = rtl ? 1u : 0u;
              vi++;
            }
          }
          my_mem_free(NULL, tmp);
        }
        SBLineRelease(line);
        /* UBA L4 (M12b): mirror glyphs at RTL embedding levels */
        for (i = 0; i < len; i++) {
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
      if (vi != len) { /* SheenBidi failure: fall back to identity */
        may = false;
      } else {
        m->has_rtl = has_rtl;
        m->rtl_base = base_rtl;
      }
    }
  }
#else
  may = false; /* BIDI compiled out: always the identity layout */
#endif
  if (!may || m->len == 0) {
    /* identity: visual == logical */
    for (i = 0; i < len; i++) {
      m->map[i] = (uint32_t)i;
    }
    m->has_rtl = false;
  }
  for (i = 0; i < len; i++) { /* inverse map (valid for both paths) */
    m->inv[m->map[i]] = (uint32_t)i;
  }
  m->utf8 = tl_encode_all(NULL, m->cps, len);
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
  l->has_rtl = m->has_rtl;
  l->rtl_base = m->rtl_base;
  if (m->len > 0) {
    l->visual_cps = (uint32_t*)my_mem_alloc(alloc, m->len * sizeof(uint32_t));
    l->visual_to_logical =
        (uint32_t*)my_mem_alloc(alloc, m->len * sizeof(uint32_t));
    l->logical_to_visual =
        (uint32_t*)my_mem_alloc(alloc, m->len * sizeof(uint32_t));
    l->visual_rtl = (uint8_t*)my_mem_alloc(alloc, m->len);
    if (l->visual_cps == NULL || l->visual_to_logical == NULL ||
        l->logical_to_visual == NULL || l->visual_rtl == NULL) {
      my_text_layout_destroy(l);
      return NULL;
    }
    memcpy(l->visual_cps, m->cps, m->len * sizeof(uint32_t));
    memcpy(l->visual_to_logical, m->map, m->len * sizeof(uint32_t));
    memcpy(l->logical_to_visual, m->inv, m->len * sizeof(uint32_t));
    memcpy(l->visual_rtl, m->vrtl, m->len);
  }
  l->visual_utf8 = my_strdup(alloc, m->utf8 != NULL ? m->utf8 : "");
  if (l->visual_utf8 == NULL) {
    my_text_layout_destroy(l);
    return NULL;
  }
  return l;
}

my_text_layout_t* my_text_layout_process(const my_allocator_t* allocator,
                                         const char* text) {
  size_t i, slot = 0;
  uint64_t oldest;
  if (text == NULL) {
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
  if (!tl_master_compute(&g_cache[slot], text)) {
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
    my_mem_free(alloc, layout->logical_to_visual);
    my_mem_free(alloc, layout->visual_rtl);
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

/* ---------------- boundary <-> visual (M12a) ---------------- */

/** @brief Width of one visual codepoint (glyph advance; 8px cell when
 * font is NULL). */
static float tl_cp_w(const my_font_t* font, int32_t size, uint32_t cp) {
  my_glyph_t g;
  if (font == NULL) {
    return 8.0f;
  }
  if (my_font_get_glyph((my_font_t*)font, cp, size, &g) != MY_RET_OK) {
    return 0.0f;
  }
  return (float)g.advance;
}

/** @brief Visual boundary index (0..len) of a logical boundary:
 * previous logical codepoint's logical-trailing edge. */
static size_t tl_vb_of_lb(const my_text_layout_t* l, size_t b) {
  size_t vi;
  if (l->len == 0) {
    return 0;
  }
  if (b == 0) {
    /* leading edge of logical cp 0 */
    vi = l->logical_to_visual[0];
    return l->visual_rtl[vi] != 0 ? vi + 1 : vi;
  }
  if (b > l->len) {
    b = l->len;
  }
  vi = l->logical_to_visual[b - 1];
  return l->visual_rtl[vi] != 0 ? vi : vi + 1;
}

/** @brief Logical boundary at a visual boundary (previous visual
 * codepoint's trailing edge). */
static size_t tl_lb_of_vb(const my_text_layout_t* l, size_t v) {
  size_t prev;
  if (l->len == 0 || v == 0) {
    if (l->len == 0) {
      return 0;
    }
    return l->visual_rtl[0] != 0 ? l->visual_to_logical[0] + 1
                                 : l->visual_to_logical[0];
  }
  if (v > l->len) {
    v = l->len;
  }
  prev = v - 1;
  return l->visual_rtl[prev] != 0 ? l->visual_to_logical[prev]
                                  : l->visual_to_logical[prev] + 1;
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
  for (i = 0; i < v; i++) {
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
    return tl_lb_of_vb(l, 0);
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
  if (l == NULL || out == NULL || cap == 0 || l0 >= l1 || l0 >= l->len) {
    return 0;
  }
  if (l1 > l->len) {
    l1 = l->len;
  }
  for (j = 0; j < l->len; j++) {
    float w = tl_cp_w(font, size, l->visual_cps[j]);
    bool in_sel = l->visual_to_logical[j] >= l0 &&
                  l->visual_to_logical[j] < l1;
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
    }
    x += w;
  }
  return n;
}
