/**
 * @file my_text_layout.h
 * @brief Text layout: logical-order UTF-8 -> shaped + visually reordered
 * codepoints (M11a).
 *
 * Pipeline: UTF-8 decode -> pure-LTR fast path (no RTL/Arabic codepoint:
 * identity, SheenBidi untouched) -> Arabic joining (my_arabic_shape,
 * presentation forms) -> SheenBidi paragraph direction + UBA reorder.
 * The result is a visual-order codepoint array plus a visual->logical
 * index map and a re-encoded visual UTF-8 string (for font-vtable
 * measure, which is order-insensitive but shaping-sensitive).
 *
 * Results are cached in a process-global LRU (64 entries, key = text;
 * the layout is font-independent). my_text_layout_process returns a
 * CALLER-OWNED copy (destroy with my_text_layout_destroy).
 *
 * Built with MYUI_BIDI=OFF: shaping/reorder compile out, process always
 * returns the identity layout (still cached).
 *
 * Boundaries: single paragraph (draw_text strings); mirroring (UBA rule
 * L4) not applied (TODO); editing widgets' RTL cursor mapping is a TODO.
 */
#ifndef MY_TEXT_LAYOUT_H
#define MY_TEXT_LAYOUT_H

#include "myc/my_mem.h"
#include "myc/my_types.h"
#include "myr/my_font.h"
#include "myr/my_rect.h"

/** @brief One laid-out string (caller-owned copy). */
typedef struct my_text_layout_t {
  const my_allocator_t* allocator;
  uint32_t* visual_cps;        /**< len items: shaped + reordered */
  uint32_t* visual_to_logical; /**< len items: visual i -> logical index */
  uint32_t* logical_to_visual; /**< len items: logical i -> visual index */
  uint8_t* visual_rtl;         /**< len items: visual cp's run is RTL */
  char* visual_utf8;           /**< visual_cps re-encoded as UTF-8 */
  size_t len;
  bool has_rtl;   /**< any RTL-level run (or RTL base) */
  bool rtl_base;  /**< paragraph base direction is RTL (M13b) */
} my_text_layout_t;

/**
 * @brief Lay out a logical-order UTF-8 string. NULL text -> NULL. The
 * returned layout is owned by the caller (a copy of the cached master).
 */
my_text_layout_t* my_text_layout_process(const my_allocator_t* allocator,
                                         const char* text);

/** @brief Destroy a layout returned by my_text_layout_process. */
void my_text_layout_destroy(my_text_layout_t* layout);

/**
 * @brief Cheap pre-scan: true when the text contains any codepoint that
 * could need shaping or reordering (Arabic/Hebrew blocks, presentation
 * forms, bidi controls). Backends use it to keep a zero-overhead legacy
 * path for plain LTR text.
 */
bool my_text_layout_may_need_bidi(const char* text);

/** @brief Drop all cached layouts (tests / shutdown). */
void my_text_layout_cache_flush(void);

/** @brief Occupied cache slots (tests). */
size_t my_text_layout_cache_size(void);

/* ---------------- editing support: boundary <-> visual (M12a) --------
 * A CURSOR always sits between two logical codepoints (a "logical
 * boundary", 0..len). Its visual position is defined by ONE consistent
 * rule -- the previous logical codepoint's logical-trailing edge (RTL
 * codepoints trail to the LEFT visually). No dual/secondary cursors:
 * at run transitions a boundary has one canonical visual spot, and a
 * newly typed char may appear elsewhere (documented quirk of every
 * single-cursor model). Width math uses `font` (glyph advances); NULL
 * font = 8px cell per codepoint (the widgets' no-font fallback). */

/** @brief Visual x (px) of a logical boundary. */
int32_t my_text_layout_visual_x(const my_text_layout_t* l,
                                const my_font_t* font, int32_t size,
                                size_t logical_boundary);

/** @brief Nearest logical boundary for a click at visual x. */
size_t my_text_layout_logical_at_x(const my_text_layout_t* l,
                                   const my_font_t* font, int32_t size,
                                   int32_t x);

/** @brief Left/Right keys move VISUALLY (RTL run: Left = logical +1). */
size_t my_text_layout_boundary_left(const my_text_layout_t* l,
                                    size_t logical_boundary);
size_t my_text_layout_boundary_right(const my_text_layout_t* l,
                                     size_t logical_boundary);

/** @brief Home/End: visual line start/end boundaries. */
size_t my_text_layout_boundary_home(const my_text_layout_t* l);
size_t my_text_layout_boundary_end(const my_text_layout_t* l);

/** @brief Raw boundary conversions (canonical rules above; used for
 * goal-column style vertical navigation). */
size_t my_text_layout_visual_of_logical(const my_text_layout_t* l,
                                        size_t logical_boundary);
size_t my_text_layout_logical_at_visual(const my_text_layout_t* l,
                                        size_t visual_boundary);

/**
 * @brief Selection highlight segments: visual x/w rects for a logical
 * range [l0, l1) (contiguous logical text may appear as several visual
 * segments at run boundaries). y/h left to the caller (0.0f here).
 * @return segment count (0..cap).
 */
size_t my_text_layout_visual_rects(const my_text_layout_t* l,
                                   const struct my_font_t* font, int32_t size,
                                   size_t l0, size_t l1, my_rectf_t* out,
                                   size_t cap);

#endif /* MY_TEXT_LAYOUT_H */
