/**
 * @file my_grapheme.c
 * @brief Allocation-free byte-space grapheme-cluster boundaries (R659).
 */
#include "myr/my_grapheme.h"

#include "myr/generated/my_combining_marks_data.h"
#include "myr/generated/my_extended_pictographic_data.h"

static bool gr_is_extend(uint32_t cp) {
  size_t lo = 0u;
  size_t hi = sizeof(MY_COMBINING_MARKS) / sizeof(MY_COMBINING_MARKS[0]);
  while (lo < hi) {
    size_t mid = lo + (hi - lo) / 2u;
    const my_combining_mark_range_t* range = &MY_COMBINING_MARKS[mid];
    if (cp < range->first) {
      hi = mid;
    } else if (cp > range->last) {
      lo = mid + 1u;
    } else {
      return true;
    }
  }
  return false;
}

static bool gr_is_extended_pictographic(uint32_t cp) {
  size_t lo = 0u;
  size_t hi = sizeof(MY_EXTENDED_PICTOGRAPHIC) /
              sizeof(MY_EXTENDED_PICTOGRAPHIC[0]);
  while (lo < hi) {
    size_t mid = lo + (hi - lo) / 2u;
    const my_extended_pictographic_range_t* range =
        &MY_EXTENDED_PICTOGRAPHIC[mid];
    if (cp < range->first) {
      hi = mid;
    } else if (cp > range->last) {
      lo = mid + 1u;
    } else {
      return true;
    }
  }
  return false;
}

static bool gr_is_regional_indicator(uint32_t cp) {
  return cp >= 0x1F1E6u && cp <= 0x1F1FFu;
}

/* R661: bounded GB9c — the Indic virama set and the script blocks whose
 * consonants it links into one cluster. */
static bool gr_is_virama(uint32_t cp) {
  switch (cp) {
    case 0x094Du: case 0x09CDu: case 0x0A4Du: case 0x0ACDu:
    case 0x0BCDu: case 0x0C4Du: case 0x0CCDu: case 0x0D4Du:
    case 0x0DCAu: case 0x0F84u: case 0x1039u: case 0x103Au:
    case 0x17D2u: case 0x1B44u:
      return true;
    default:
      return false;
  }
}

static bool gr_is_indic_script_cp(uint32_t cp) {
  return (cp >= 0x0900u && cp <= 0x0DFFu) ||
         (cp >= 0x0F00u && cp <= 0x0FFFu) ||
         (cp >= 0x1000u && cp <= 0x109Fu) ||
         (cp >= 0x1780u && cp <= 0x17FFu) ||
         (cp >= 0x1B00u && cp <= 0x1B7Fu);
}

static size_t gr_cp_bytes(uint8_t lead) {
  if (lead < 0x80u) return 1u;
  if (lead < 0xC0u) return 1u; /* stray continuation: treat as one byte */
  if (lead < 0xE0u) return 2u;
  if (lead < 0xF0u) return 3u;
  return 4u;
}

/** @brief Decode the codepoint starting at text[pos] (pos < len). */
static uint32_t gr_cp_at(const char* text, size_t len, size_t pos) {
  const uint8_t* s = (const uint8_t*)text + pos;
  size_t left = len - pos;
  size_t bytes = gr_cp_bytes(s[0]);
  uint32_t cp;
  if (bytes == 1u) return s[0];
  if (bytes > left) bytes = (size_t)left;
  cp = (uint32_t)(s[0] & (uint8_t)(0xFFu >> (bytes + 1u)));
  {
    size_t i;
    for (i = 1u; i < bytes; ++i) {
      if ((s[i] & 0xC0u) != 0x80u) return s[0]; /* malformed: lead byte */
      cp = (cp << 6u) | (uint32_t)(s[i] & 0x3Fu);
    }
  }
  return cp;
}

/** @brief Start of the codepoint immediately before `offset` (offset>0). */
static size_t gr_prev_start(const char* text, size_t offset) {
  size_t prev = offset - 1u;
  while (prev > 0u && ((uint8_t)text[prev] & 0xC0u) == 0x80u) {
    prev--;
  }
  return prev;
}

static bool gr_cluster_interior(const char* text, size_t len, size_t b) {
  uint32_t cp;
  if (b == 0u || b >= len) return false;
  cp = gr_cp_at(text, len, b);
  if (gr_is_extend(cp) || cp == 0x200Du) return true;
  if (gr_is_regional_indicator(cp)) {
    size_t run = 0u;
    size_t i = b;
    while (i > 0u) {
      size_t prev_start = gr_prev_start(text, i);
      if (!gr_is_regional_indicator(gr_cp_at(text, len, prev_start))) break;
      run++;
      i = prev_start;
    }
    return (run & 1u) != 0u;
  }
  /* GB11 bounded: a pictograph right after a ZWJ joins the chain. */
  if (gr_is_extended_pictographic(cp) &&
      gr_cp_at(text, len, gr_prev_start(text, b)) == 0x200Du) {
    return true;
  }
  /* R661: bounded GB9c — virama + consonant conjuncts. */
  return gr_is_indic_script_cp(cp) &&
         gr_is_virama(gr_cp_at(text, len, gr_prev_start(text, b)));
}

size_t my_grapheme_boundary_right(const char* text, size_t len,
                                  size_t offset) {
  size_t candidate;
  if (text == NULL) return 0u;
  if (offset >= len) return len;
  candidate = offset + gr_cp_bytes((uint8_t)text[offset]);
  if (candidate > len) candidate = len;
  while (candidate < len && gr_cluster_interior(text, len, candidate)) {
    candidate += gr_cp_bytes((uint8_t)text[candidate]);
    if (candidate > len) candidate = len;
  }
  return candidate;
}

size_t my_grapheme_boundary_left(const char* text, size_t len,
                                 size_t offset) {
  size_t candidate;
  if (text == NULL || len == 0u || offset == 0u) return 0u;
  if (offset > len) offset = len;
  candidate = gr_prev_start(text, offset);
  while (candidate > 0u && gr_cluster_interior(text, len, candidate)) {
    candidate = gr_prev_start(text, candidate);
  }
  return candidate;
}
