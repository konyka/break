/**
 * @file my_line_break.c
 * @brief Simplified line-break class lookup (M12d).
 */
#include "myr/my_line_break.h"

#include <stddef.h>
#include <string.h>

#include "myr/generated/my_combining_marks_data.h"
#include "myr/generated/my_east_asian_width_data.h"
#include "myr/generated/my_extended_pictographic_data.h"
#include "myr/my_line_break_data.h"

typedef struct my_builtin_sa_word_t {
  const uint32_t* codepoints;
  size_t count;
} my_builtin_sa_word_t;

static const uint32_t MY_BUILTIN_TH_LANGUAGE[] = {
    0x0E20u, 0x0E32u, 0x0E29u, 0x0E32u};
static const uint32_t MY_BUILTIN_TH_THAI[] = {0x0E44u, 0x0E17u, 0x0E22u};
static const uint32_t MY_BUILTIN_TH_KAN[] = {0x0E01u, 0x0E32u, 0x0E23u};
static const uint32_t MY_BUILTIN_TH_LAE[] = {0x0E41u, 0x0E25u, 0x0E30u};
static const uint32_t MY_BUILTIN_TH_KHONG[] = {0x0E02u, 0x0E2Du, 0x0E07u};
static const uint32_t MY_BUILTIN_TH_THI[] = {0x0E17u, 0x0E35u};
static const uint32_t MY_BUILTIN_TH_PEN[] = {0x0E40u, 0x0E1Bu, 0x0E47u, 0x0E19u};
static const uint32_t MY_BUILTIN_TH_NAI[] = {0x0E43u, 0x0E19u};
static const uint32_t MY_BUILTIN_TH_MAI[] = {0x0E44u, 0x0E21u, 0x0E48u};
static const uint32_t MY_BUILTIN_TH_SAWATDEE[] = {
    0x0E2Au, 0x0E27u, 0x0E31u, 0x0E2Au, 0x0E14u, 0x0E35u};

static const my_builtin_sa_word_t MY_BUILTIN_TH_WORDS[] = {
    {MY_BUILTIN_TH_LANGUAGE, sizeof(MY_BUILTIN_TH_LANGUAGE) /
                                  sizeof(MY_BUILTIN_TH_LANGUAGE[0])},
    {MY_BUILTIN_TH_THAI, sizeof(MY_BUILTIN_TH_THAI) /
                              sizeof(MY_BUILTIN_TH_THAI[0])},
    {MY_BUILTIN_TH_KAN, sizeof(MY_BUILTIN_TH_KAN) /
                           sizeof(MY_BUILTIN_TH_KAN[0])},
    {MY_BUILTIN_TH_LAE, sizeof(MY_BUILTIN_TH_LAE) /
                           sizeof(MY_BUILTIN_TH_LAE[0])},
    {MY_BUILTIN_TH_KHONG, sizeof(MY_BUILTIN_TH_KHONG) /
                              sizeof(MY_BUILTIN_TH_KHONG[0])},
    {MY_BUILTIN_TH_THI, sizeof(MY_BUILTIN_TH_THI) /
                           sizeof(MY_BUILTIN_TH_THI[0])},
    {MY_BUILTIN_TH_PEN, sizeof(MY_BUILTIN_TH_PEN) /
                           sizeof(MY_BUILTIN_TH_PEN[0])},
    {MY_BUILTIN_TH_NAI, sizeof(MY_BUILTIN_TH_NAI) /
                           sizeof(MY_BUILTIN_TH_NAI[0])},
    {MY_BUILTIN_TH_MAI, sizeof(MY_BUILTIN_TH_MAI) /
                           sizeof(MY_BUILTIN_TH_MAI[0])},
    {MY_BUILTIN_TH_SAWATDEE, sizeof(MY_BUILTIN_TH_SAWATDEE) /
                                  sizeof(MY_BUILTIN_TH_SAWATDEE[0])}};

my_line_break_class_t my_line_break_class(uint32_t cp) {
  size_t lo = 0, hi = sizeof(MY_LINE_BREAKS) / sizeof(MY_LINE_BREAKS[0]);
  while (lo < hi) {
    size_t mid = lo + (hi - lo) / 2;
    const my_lb_entry_t* e = &MY_LINE_BREAKS[mid];
    if (cp < e->lo) {
      hi = mid;
    } else if (cp > e->hi) {
      lo = mid + 1;
    } else {
      return (my_line_break_class_t)e->cls;
    }
  }
  return MY_LB_ID; /* gaps default to ideographic (break allowed) */
}

size_t my_line_break_hard_break_len(const char* text, size_t remaining) {
  if (text == NULL || remaining == 0u) return 0u;
  if ((unsigned char)text[0] == 0x0Au ||
      (unsigned char)text[0] == 0x0Bu ||
      (unsigned char)text[0] == 0x0Cu) return 1u;
  if ((unsigned char)text[0] == 0x0Du) {
    return remaining >= 2u && (unsigned char)text[1] == 0x0Au ? 2u : 1u;
  }
  if (remaining >= 2u && (unsigned char)text[0] == 0xC2u &&
      (unsigned char)text[1] == 0x85u) return 2u;
  if (remaining >= 3u && (unsigned char)text[0] == 0xE2u &&
      (unsigned char)text[1] == 0x80u &&
      ((unsigned char)text[2] == 0xA8u ||
       (unsigned char)text[2] == 0xA9u)) return 3u;
  return 0u;
}

static bool is_combining_mark(uint32_t cp) {
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

static bool is_line_break_combining_mark(uint32_t cp) {
  my_line_break_class_t cls = my_line_break_class(cp);
  return cls == MY_LB_CM || (cls != MY_LB_GL && is_combining_mark(cp));
}

static bool is_wide_east_asian(uint32_t cp) {
  size_t lo = 0u;
  size_t hi = sizeof(MY_EAST_ASIAN_WIDTH_WIDE) /
              sizeof(MY_EAST_ASIAN_WIDTH_WIDE[0]);
  while (lo < hi) {
    size_t mid = lo + (hi - lo) / 2u;
    const my_east_asian_width_range_t* range =
        &MY_EAST_ASIAN_WIDTH_WIDE[mid];
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

static bool is_non_break_extension(uint32_t cp) {
  return (cp >= 0xFE00u && cp <= 0xFE0Fu) ||
         (cp >= 0xE0100u && cp <= 0xE01EFu) ||
         (cp >= 0xE0020u && cp <= 0xE007Fu) || cp == 0x200Cu ||
         cp == 0x200Du;
}

static bool is_non_break_glue(uint32_t cp) {
  return my_line_break_class(cp) != MY_LB_GL &&
         (cp == 0x00A0u || cp == 0x2007u || cp == 0x202Fu ||
          cp == 0x2011u || cp == 0x2060u || cp == 0xFEFFu);
}

static bool is_regional_indicator(uint32_t cp) {
  return cp >= 0x1F1E6u && cp <= 0x1F1FFu;
}

static bool is_decimal_digit(uint32_t cp) {
  return (cp >= '0' && cp <= '9') ||
         (cp >= 0x0660u && cp <= 0x0669u) ||
         (cp >= 0x06F0u && cp <= 0x06F9u) ||
         (cp >= 0xFF10u && cp <= 0xFF19u);
}

static bool is_decimal_separator(uint32_t cp) {
  return cp == '.' || cp == ',' || cp == 0x066Bu || cp == 0x066Cu ||
         cp == 0xFF0Eu || cp == 0xFF0Cu;
}

static bool is_numeric_value(uint32_t cp) {
  return is_decimal_digit(cp) || my_line_break_class(cp) == MY_LB_NU;
}

static bool is_numeric_separator(uint32_t cp) {
  return is_decimal_separator(cp) || my_line_break_class(cp) == MY_LB_IS;
}

static bool is_exponent_marker(uint32_t cp) {
  return cp == 'e' || cp == 'E';
}

static bool is_exponent_sign(uint32_t cp) {
  return cp == '+' || cp == '-';
}

static bool is_numeric_operator(uint32_t cp) {
  return cp == '/' || cp == 0x2044u || my_line_break_class(cp) == MY_LB_SY;
}

static bool is_currency_symbol(uint32_t cp) {
  return cp == '$' || cp == 0x00A2u || cp == 0x00A3u || cp == 0x00A4u ||
         cp == 0x00A5u || (cp >= 0x20A0u && cp <= 0x20CFu) ||
         cp == 0xFFE5u;
}

static bool is_percent_symbol(uint32_t cp) {
  return cp == '%' || cp == 0x2030u || cp == 0x2031u || cp == 0x066Au;
}

static bool is_hebrew_letter(uint32_t cp) {
  return my_line_break_class(cp) == MY_LB_HL;
}

static bool is_hebrew_quote(uint32_t cp) {
  return cp == '\'' || cp == '"' || cp == 0x05F3u || cp == 0x05F4u;
}

static bool is_closing_quote(uint32_t cp) {
  return cp == 0x00BBu || cp == 0x2019u || cp == 0x201Du ||
         cp == 0x203Au || cp == 0x2E03u || cp == 0x2E05u ||
         cp == 0x2E0Au || cp == 0x2E0Du || cp == 0x2E1Du ||
         cp == 0x2E21u;
}

static bool is_opening_quote(uint32_t cp) {
  return cp == 0x00ABu;
}

static bool is_hebrew_maqaf(uint32_t cp) {
  return cp == 0x05BEu;
}

static bool is_break_both(uint32_t cp) {
  return my_line_break_class(cp) == MY_LB_B2;
}

static bool is_hard_break_cp(uint32_t cp) {
  return cp == 0x000Au || cp == 0x000Bu || cp == 0x000Cu ||
         cp == 0x000Du || cp == 0x0085u || cp == 0x2028u ||
         cp == 0x2029u;
}

static bool is_bidi_format_cp(uint32_t cp) {
  return cp == 0x061Cu || (cp >= 0x200Eu && cp <= 0x200Fu) ||
         (cp >= 0x202Au && cp <= 0x202Eu) ||
         (cp >= 0x2066u && cp <= 0x2069u);
}

static bool is_zero_width_space(uint32_t cp) {
  return cp == 0x200Bu;
}

static bool is_batak_vowel_mark(uint32_t cp) {
  return cp == 0x1BE7u || (cp >= 0x1BEAu && cp <= 0x1BEEu);
}

bool my_line_break_is_breaking_space(uint32_t cp) {
  return cp == 0x0020u || (cp >= 0x2000u && cp <= 0x2006u) ||
         (cp >= 0x2008u && cp <= 0x200Au) || cp == 0x205Fu ||
         cp == 0x3000u;
}

bool my_line_break_dictionary_profile_valid(
    const my_line_break_dictionary_profile_t* profile) {
  size_t length = 0u;
  size_t subtag_length = 0u;
  bool at_start = true;
  bool first_subtag = true;
  if (profile == NULL || profile->version !=
                              MY_LINE_BREAK_DICTIONARY_PROFILE_VERSION ||
      profile->locale == NULL) {
    return false;
  }
  while (length <= MY_LINE_BREAK_DICTIONARY_MAX_LOCALE_BYTES) {
    unsigned char ch = (unsigned char)profile->locale[length];
    if (ch == '\0') {
      return length >= 2u && subtag_length >= 2u && !at_start;
    }
    if (ch == '-') {
      if (at_start || subtag_length < 2u || subtag_length > 8u) {
        return false;
      }
      first_subtag = false;
      at_start = true;
      subtag_length = 0u;
    } else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ||
               (!first_subtag && ch >= '0' && ch <= '9')) {
      at_start = false;
      subtag_length++;
      if (subtag_length > 8u) return false;
    } else {
      return false;
    }
    length++;
  }
  return false;
}

static bool my_builtin_dictionary_profile_is_thai(
    const my_line_break_dictionary_profile_t* profile) {
  return profile != NULL && my_line_break_dictionary_profile_valid(profile) &&
         strcmp(profile->locale, "th-Thai") == 0;
}

bool my_line_break_builtin_dictionary_supports(
    const my_line_break_dictionary_profile_t* profile) {
  return my_builtin_dictionary_profile_is_thai(profile);
}

static bool my_builtin_sa_word_matches(const my_builtin_sa_word_t* word,
                                       const uint32_t* codepoints,
                                       size_t count, size_t offset) {
  size_t i;
  if (word == NULL || codepoints == NULL || offset > count ||
      word->count > count - offset) {
    return false;
  }
  for (i = 0u; i < word->count; ++i) {
    if (word->codepoints[i] != codepoints[offset + i]) return false;
  }
  return true;
}

my_ret_t my_line_break_apply_builtin_dictionary(
    const uint32_t* codepoints, size_t count, bool* allow_before,
    const my_line_break_dictionary_profile_t* profile) {
  bool scratch[MY_LINE_BREAK_MAX_DICTIONARY_CODEPOINTS];
  bool reachable[MY_LINE_BREAK_MAX_DICTIONARY_CODEPOINTS + 1u];
  size_t i;
  size_t word_index;
  size_t word_count = sizeof(MY_BUILTIN_TH_WORDS) /
                      sizeof(MY_BUILTIN_TH_WORDS[0]);

  if (!my_line_break_dictionary_profile_valid(profile)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (!my_builtin_dictionary_profile_is_thai(profile)) {
    return MY_RET_NOT_SUPPORTED;
  }
  if (count != 0u && (codepoints == NULL || allow_before == NULL)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (count > MY_LINE_BREAK_MAX_DICTIONARY_CODEPOINTS) {
    return MY_RET_INVALID_PARAMS;
  }
  for (i = 0u; i < count; ++i) {
    if (codepoints[i] > 0x10FFFFu ||
        (codepoints[i] >= 0xD800u && codepoints[i] <= 0xDFFFu)) {
      return MY_RET_INVALID_PARAMS;
    }
    if (my_line_break_class(codepoints[i]) != MY_LB_SA) {
      return MY_RET_INVALID_PARAMS;
    }
    scratch[i] = allow_before[i];
  }
  if (count < 2u) return MY_RET_OK;

  memset(reachable, 0, sizeof(reachable));
  reachable[0] = true;
  for (i = 0u; i < count; ++i) {
    if (!reachable[i]) continue;
    for (word_index = 0u; word_index < word_count; ++word_index) {
      const my_builtin_sa_word_t* word = &MY_BUILTIN_TH_WORDS[word_index];
      if (my_builtin_sa_word_matches(word, codepoints, count, i)) {
        reachable[i + word->count] = true;
      }
    }
  }
  if (!reachable[count]) {
    for (i = 1u; i < count; ++i) scratch[i] = false;
  } else {
    size_t offset = 0u;
    for (i = 1u; i < count; ++i) scratch[i] = false;
    while (offset < count) {
      const my_builtin_sa_word_t* best = NULL;
      for (word_index = 0u; word_index < word_count; ++word_index) {
        const my_builtin_sa_word_t* word = &MY_BUILTIN_TH_WORDS[word_index];
        if (my_builtin_sa_word_matches(word, codepoints, count, offset) &&
            reachable[offset + word->count] &&
            (best == NULL || word->count > best->count)) {
          best = word;
        }
      }
      if (best == NULL) return MY_RET_FAIL;
      offset += best->count;
      if (offset < count) scratch[offset] = true;
    }
  }
  for (i = 1u; i < count; ++i) allow_before[i] = scratch[i];
  return MY_RET_OK;
}

my_ret_t my_line_break_builtin_dictionary_callback(
    void* context, const my_line_break_dictionary_profile_t* profile,
    const uint32_t* codepoints, size_t count, bool* allow_before) {
  (void)context;
  return my_line_break_apply_builtin_dictionary(codepoints, count,
                                                allow_before, profile);
}

static bool is_numeric_class(my_line_break_class_t cls) {
  return cls == MY_LB_NU || cls == MY_LB_IS;
}

static bool is_alphabetic_class(my_line_break_class_t cls) {
  return cls == MY_LB_AL || cls == MY_LB_AI || cls == MY_LB_HL ||
         cls == MY_LB_SA;
}

static bool is_indic_aksara_or_dotted_circle(uint32_t cp,
                                             my_line_break_class_t cls) {
  return cls == MY_LB_AK || cls == MY_LB_AS || cp == 0x25CCu;
}

static bool is_indic_aksara_or_dotted_circle_target(
    uint32_t cp, my_line_break_class_t cls) {
  return cls == MY_LB_AK || cp == 0x25CCu;
}

typedef enum my_hangul_class_t {
  MY_HANGUL_NONE = 0,
  MY_HANGUL_JL,
  MY_HANGUL_JV,
  MY_HANGUL_JT,
  MY_HANGUL_LV,
  MY_HANGUL_LVT
} my_hangul_class_t;

static my_hangul_class_t hangul_class(uint32_t cp) {
  uint32_t syllable_index;
  if ((cp >= 0x1100u && cp <= 0x115Fu) ||
      (cp >= 0xA960u && cp <= 0xA97Cu)) {
    return MY_HANGUL_JL;
  }
  if ((cp >= 0x1160u && cp <= 0x11A7u) ||
      (cp >= 0xD7B0u && cp <= 0xD7C6u)) {
    return MY_HANGUL_JV;
  }
  if ((cp >= 0x11A8u && cp <= 0x11FFu) ||
      (cp >= 0xD7CBu && cp <= 0xD7FBu)) {
    return MY_HANGUL_JT;
  }
  if (cp >= 0xAC00u && cp <= 0xD7A3u) {
    syllable_index = cp - 0xAC00u;
    return syllable_index % 28u == 0u ? MY_HANGUL_LV : MY_HANGUL_LVT;
  }
  return MY_HANGUL_NONE;
}

static bool is_non_hangul_alphabetic(uint32_t cp,
                                     my_line_break_class_t cls) {
  return !is_regional_indicator(cp) && hangul_class(cp) == MY_HANGUL_NONE &&
         is_alphabetic_class(cls);
}

static bool is_extended_pictographic_in_ranges(
    uint32_t cp, const my_extended_pictographic_range_t* ranges,
    size_t count) {
  size_t lo = 0u;
  size_t hi = count;
  while (lo < hi) {
    size_t mid = lo + (hi - lo) / 2u;
    if (cp < ranges[mid].first) {
      hi = mid;
    } else if (cp > ranges[mid].last) {
      lo = mid + 1u;
    } else {
      return true;
    }
  }
  return false;
}

static bool is_xx_extended_pictographic_unassigned(uint32_t cp) {
  return is_extended_pictographic_in_ranges(
      cp, MY_XX_EXTENDED_PICTOGRAPHIC_UNASSIGNED,
      sizeof(MY_XX_EXTENDED_PICTOGRAPHIC_UNASSIGNED) /
          sizeof(MY_XX_EXTENDED_PICTOGRAPHIC_UNASSIGNED[0]));
}

static bool is_id_extended_pictographic_unassigned(uint32_t cp) {
  return is_extended_pictographic_in_ranges(
      cp, MY_ID_EXTENDED_PICTOGRAPHIC_UNASSIGNED,
      sizeof(MY_ID_EXTENDED_PICTOGRAPHIC_UNASSIGNED) /
          sizeof(MY_ID_EXTENDED_PICTOGRAPHIC_UNASSIGNED[0]));
}

static bool is_extended_pictographic(uint32_t cp) {
  return is_extended_pictographic_in_ranges(
      cp, MY_EXTENDED_PICTOGRAPHIC,
      sizeof(MY_EXTENDED_PICTOGRAPHIC) /
          sizeof(MY_EXTENDED_PICTOGRAPHIC[0]));
}

static bool hangul_no_break(my_hangul_class_t prev, my_hangul_class_t cur) {
  if (prev == MY_HANGUL_JL) {
    return cur == MY_HANGUL_JL || cur == MY_HANGUL_JV ||
           cur == MY_HANGUL_LV || cur == MY_HANGUL_LVT;
  }
  if (prev == MY_HANGUL_JV || prev == MY_HANGUL_LV) {
    return cur == MY_HANGUL_JV || cur == MY_HANGUL_JT;
  }
  if (prev == MY_HANGUL_JT || prev == MY_HANGUL_LVT) {
    return cur == MY_HANGUL_JT;
  }
  return false;
}

static bool my_line_break_allowed_with_ri_run(uint32_t prev_cp,
                                              uint32_t cur_cp,
                                              size_t ri_run) {
  my_line_break_class_t prev = my_line_break_class(prev_cp);
  my_line_break_class_t cur = my_line_break_class(cur_cp);
  my_hangul_class_t prev_hangul = hangul_class(prev_cp);
  my_hangul_class_t cur_hangul = hangul_class(cur_cp);

  /* UAX #14 LB4-LB6: hard breaks are boundaries on both sides, except CRLF. */
  if (is_hard_break_cp(prev_cp)) {
    if (prev_cp == 0x000Du && cur_cp == 0x000Au) return false;
    return true;
  }
  if (is_hard_break_cp(cur_cp)) {
    return false;
  }
  /* UAX #14 LB8/LB8a: ZWSP creates a break after itself, never before it. */
  if (cur == MY_LB_ZW || is_zero_width_space(cur_cp)) {
    return false;
  }
  if ((prev == MY_LB_ZW || is_zero_width_space(prev_cp)) &&
      cur != MY_LB_SP) {
    return true;
  }
  if (prev == MY_LB_SP && is_line_break_combining_mark(cur_cp)) {
    return true;
  }
  if (prev == MY_LB_SP && cur != MY_LB_SP && cur != MY_LB_IS &&
      cur != MY_LB_SY &&
      cur != MY_LB_QU && cur != MY_LB_CL &&
      cur != MY_LB_CP && cur != MY_LB_EX && cur_cp != 0x2060u &&
      cur_cp != 0xFEFFu) {
    return true;
  }
  if (prev == MY_LB_SP && cur == MY_LB_QU &&
      !is_closing_quote(cur_cp)) {
    return true;
  }
  if (prev == MY_LB_B2 &&
      (cur == MY_LB_VF || cur == MY_LB_VI)) {
    return true;
  }
  /* UAX #14 LB12/LB12a: glue stays attached except after BA or HY. */
  if (prev == MY_LB_GL) {
    return false;
  }
  if (cur == MY_LB_GL && prev != MY_LB_BA && prev != MY_LB_HY &&
      prev != MY_LB_HH) {
    return false;
  }
  if ((is_line_break_combining_mark(prev_cp) && prev != MY_LB_VF &&
       prev != MY_LB_VI) ||
      (is_line_break_combining_mark(cur_cp) && cur != MY_LB_VF &&
       cur != MY_LB_VI)) {
    return false;
  }
  if (is_non_break_extension(prev_cp) || is_non_break_extension(cur_cp)) {
    return false;
  }
  if (is_non_break_glue(prev_cp) || is_non_break_glue(cur_cp)) {
    return false;
  }
  if (is_regional_indicator(cur_cp)) {
    if (is_regional_indicator(prev_cp)) {
      return (ri_run % 2u) == 0u;
    }
    if (prev == MY_LB_QU) return false;
    if (prev == MY_LB_BB) return false;
    return true;
  }
  if (cur == MY_LB_IS && prev != MY_LB_SP) {
    return false;
  }
  if (prev == MY_LB_SP && cur == MY_LB_IS) {
    return false;
  }
  if (prev == MY_LB_CB &&
      (cur == MY_LB_SP || cur == MY_LB_CL ||
       cur == MY_LB_CP || cur == MY_LB_EX || cur == MY_LB_SY ||
       cur == MY_LB_QU ||
       (is_line_break_combining_mark(cur_cp) && cur != MY_LB_VF &&
        cur != MY_LB_VI) ||
       is_non_break_extension(cur_cp))) {
    return false;
  }
  if (prev == MY_LB_ID &&
      (is_opening_quote(cur_cp) || cur_cp == 0x201Cu) &&
      !is_extended_pictographic(prev_cp) &&
      !is_id_extended_pictographic_unassigned(prev_cp) &&
      !is_xx_extended_pictographic_unassigned(prev_cp)) {
    return true;
  }
  if (prev_cp == 0xFF1Au &&
      (cur_cp == 0x2018u || cur_cp == 0x201Cu)) {
    return true;
  }
  if (prev == MY_LB_QU || cur == MY_LB_QU) {
    return false;
  }
  if (prev == MY_LB_CB || cur == MY_LB_CB) {
    return true;
  }
  if (cur == MY_LB_BA || cur == MY_LB_IN || cur == MY_LB_CJ ||
      cur == MY_LB_HH || cur == MY_LB_SY || cur == MY_LB_CL ||
      cur == MY_LB_CP || cur == MY_LB_EX) {
    return false;
  }
  if (prev == MY_LB_BA && cur == MY_LB_HY) {
    return false;
  }
  if (prev == MY_LB_IN && cur == MY_LB_HY) {
    return false;
  }
  if (prev == MY_LB_EB && cur == MY_LB_EM) {
    return false;
  }
  if (prev == MY_LB_AP &&
      is_indic_aksara_or_dotted_circle(cur_cp, cur)) {
    return false;
  }
  if (is_indic_aksara_or_dotted_circle(prev_cp, prev) &&
      (cur == MY_LB_VF || cur == MY_LB_VI)) {
    return false;
  }
  if (hangul_no_break(prev_hangul, cur_hangul)) {
    return false;
  }
  if ((prev_hangul != MY_HANGUL_NONE && cur == MY_LB_PO) ||
      (prev == MY_LB_PR && cur_hangul != MY_HANGUL_NONE) ||
      (prev == MY_LB_PR &&
       (cur == MY_LB_ID || cur == MY_LB_EB || cur == MY_LB_EM))) {
    return false;
  }
  if ((prev == MY_LB_B2 && cur == MY_LB_B2) ||
      (is_break_both(prev_cp) && is_break_both(cur_cp))) {
    return false;
  }
  if (prev_hangul != MY_HANGUL_NONE && cur_hangul != MY_HANGUL_NONE) {
    return true;
  }
  if ((is_hebrew_letter(prev_cp) && is_hebrew_quote(cur_cp)) ||
      (is_hebrew_quote(prev_cp) && is_hebrew_letter(cur_cp))) {
    return false;
  }
  if ((is_hebrew_letter(prev_cp) && is_hebrew_maqaf(cur_cp)) ||
      (is_hebrew_maqaf(prev_cp) && is_hebrew_letter(cur_cp))) {
    return false;
  }
  if (is_numeric_operator(prev_cp) && is_hebrew_letter(cur_cp)) {
    return false;
  }
  if ((prev == MY_LB_HL && cur == MY_LB_HH) ||
      (prev == MY_LB_HH && cur == MY_LB_HL) ||
      (prev == MY_LB_HY && cur == MY_LB_HL) ||
      (prev == MY_LB_HH && cur == MY_LB_AI) ||
      (prev == MY_LB_HY && cur == MY_LB_AI) ||
      (prev == MY_LB_HH && cur == MY_LB_AL &&
       cur_hangul == MY_HANGUL_NONE && !is_regional_indicator(cur_cp)) ||
      (prev == MY_LB_HY && cur == MY_LB_AL &&
       cur_hangul == MY_HANGUL_NONE && is_wide_east_asian(cur_cp)) ||
      (prev == MY_LB_HY && cur_cp == 0x25CCu) ||
      (prev == MY_LB_HY && cur_cp == 0x0023u) ||
      (prev == MY_LB_HY && cur == MY_LB_HY) ||
      (prev == MY_LB_HH && cur_cp == 0x25CCu) ||
      ((prev == MY_LB_HY || prev == MY_LB_HH) && cur == MY_LB_SA)) {
    return false;
  }
  if (is_decimal_separator(cur_cp) && is_decimal_digit(prev_cp)) {
    return false;
  }
  if (is_decimal_separator(prev_cp) && is_decimal_digit(cur_cp)) {
    return false;
  }
  if (is_decimal_separator(prev_cp) &&
      (is_non_hangul_alphabetic(cur_cp, cur) ||
       is_hebrew_letter(cur_cp))) {
    return false;
  }
  if (is_numeric_operator(cur_cp) && is_decimal_digit(prev_cp)) {
    return false;
  }
  if (prev == MY_LB_HY && cur == MY_LB_NU) {
    return false;
  }
  if ((is_currency_symbol(cur_cp) || is_percent_symbol(cur_cp)) &&
      is_decimal_digit(prev_cp)) {
    return false;
  }
  if (is_currency_symbol(prev_cp) && is_decimal_digit(cur_cp)) {
    return false;
  }
  if ((is_non_hangul_alphabetic(prev_cp, prev) && cur == MY_LB_NU) ||
      (prev == MY_LB_NU && is_non_hangul_alphabetic(cur_cp, cur))) {
    return false;
  }
  if ((prev == MY_LB_PR || prev == MY_LB_PO) &&
      is_non_hangul_alphabetic(cur_cp, cur)) {
    return false;
  }
  if (is_non_hangul_alphabetic(prev_cp, prev) &&
      (cur == MY_LB_PR || cur == MY_LB_PO)) {
    return false;
  }
  if (prev == MY_LB_PR && cur == MY_LB_NU) {
    return false;
  }
  if (prev == MY_LB_PO && cur == MY_LB_NU) {
    return false;
  }
  if ((prev == MY_LB_OP || prev == MY_LB_NU ||
       prev == MY_LB_QU) &&
      (cur == MY_LB_PR || cur == MY_LB_PO)) {
    return false;
  }
  if (is_numeric_class(prev) && is_numeric_class(cur)) {
    return false;
  }
  if ((prev == MY_LB_ID || prev == MY_LB_EB || prev == MY_LB_EM) &&
      cur == MY_LB_PO) {
    return false;
  }
  if (prev == MY_LB_CP && cur_hangul == MY_HANGUL_NONE &&
      !is_xx_extended_pictographic_unassigned(cur_cp) &&
      !is_regional_indicator(cur_cp) &&
      (cur == MY_LB_AL || cur == MY_LB_HL || cur == MY_LB_NU ||
       cur == MY_LB_SA || cur == MY_LB_AI)) {
    return false;
  }
  if (prev == MY_LB_CP && is_xx_extended_pictographic_unassigned(cur_cp)) {
    return false;
  }
  if (is_xx_extended_pictographic_unassigned(prev_cp) &&
      is_xx_extended_pictographic_unassigned(cur_cp)) {
    return false;
  }
  if (is_xx_extended_pictographic_unassigned(cur_cp) &&
      ((prev == MY_LB_AL && prev_hangul == MY_HANGUL_NONE &&
        !is_regional_indicator(prev_cp)) ||
       prev == MY_LB_AI ||
       prev == MY_LB_HL || prev == MY_LB_SA)) {
    return false;
  }
  if (is_xx_extended_pictographic_unassigned(cur_cp) &&
      (prev == MY_LB_HY || prev == MY_LB_HH || prev == MY_LB_NU ||
       prev == MY_LB_IS || prev == MY_LB_PO)) {
    return false;
  }
  if ((is_id_extended_pictographic_unassigned(prev_cp) ||
       (is_xx_extended_pictographic_unassigned(prev_cp) &&
        prev_cp != 0xEFFFDu)) && cur == MY_LB_EM) {
    return false;
  }
  if (is_xx_extended_pictographic_unassigned(prev_cp) &&
      (cur == MY_LB_AL || cur == MY_LB_AI || cur == MY_LB_HL ||
       cur == MY_LB_NU || cur == MY_LB_PR || cur == MY_LB_SA ||
       (cur == MY_LB_OP && cur_cp != 0x2329u)) &&
      cur_hangul == MY_HANGUL_NONE) {
    return false;
  }
  if (prev == MY_LB_BB) {
    return false;
  }
  if (prev == MY_LB_PO && cur == MY_LB_OP &&
      is_wide_east_asian(prev_cp)) {
    return true;
  }
  if (prev == MY_LB_IS && is_non_hangul_alphabetic(cur_cp, cur) &&
      !is_regional_indicator(cur_cp) && cur != MY_LB_AI) {
    return false;
  }
  if (cur == MY_LB_SP) {
    return false;
  }
  if (cur == MY_LB_NS && prev != MY_LB_SP) {
    return false;
  }
  if (cur == MY_LB_OP && cur_cp != 0x2329u &&
      !is_wide_east_asian(cur_cp) && prev != MY_LB_SP &&
      prev != MY_LB_AK && prev != MY_LB_AP && prev != MY_LB_AS &&
      prev != MY_LB_B2 && prev != MY_LB_BA && prev != MY_LB_CL &&
      prev != MY_LB_CP && prev != MY_LB_EX &&
      prev != MY_LB_HY && prev != MY_LB_HH &&
      prev != MY_LB_ID && prev != MY_LB_IN && prev != MY_LB_IS &&
      prev != MY_LB_CJ &&
      prev != MY_LB_EB &&
      prev != MY_LB_EM &&
      prev != MY_LB_NS && prev != MY_LB_PR &&
      prev != MY_LB_PO && prev != MY_LB_SY &&
      prev != MY_LB_VF &&
      prev != MY_LB_VI &&
      !is_regional_indicator(prev_cp) &&
      prev_hangul == MY_HANGUL_NONE) {
    return false;
  }
  if (prev == MY_LB_SP || prev == MY_LB_HY || prev == MY_LB_BA ||
      prev == MY_LB_IN) {
    return true;
  }
  if (cur == MY_LB_HY || prev == MY_LB_OP) {
    return false;
  }
  if (is_non_hangul_alphabetic(prev_cp, prev) &&
      is_non_hangul_alphabetic(cur_cp, cur)) {
    return false;
  }
  if ((prev == MY_LB_SA && cur == MY_LB_SA) ||
      (is_non_hangul_alphabetic(prev_cp, prev) && cur == MY_LB_SA) ||
      (prev == MY_LB_SA && is_non_hangul_alphabetic(cur_cp, cur))) {
    return false;
  }
  return true;
}

bool my_line_break_allowed(uint32_t prev_cp, uint32_t cur_cp) {
  return my_line_break_allowed_with_ri_run(
      prev_cp, cur_cp, is_regional_indicator(prev_cp) ? 1u : 0u);
}

void my_line_break_state_init(my_line_break_state_t* state) {
  if (state == NULL) return;
  state->previous_cp = 0u;
  state->previous_starter_cp = 0u;
  state->regional_indicator_run = 0u;
  state->numeric_context = 0u;
  state->opening_space_context = false;
  state->opening_punctuation_context = false;
  state->indic_virama_context = false;
  state->has_previous = false;
  state->has_starter = false;
  state->closing_space_context = false;
  state->separator_space_context = false;
  state->quote_space_context = false;
  state->break_both_after_quote_context = false;
  state->closing_space_after_opening_context = false;
  state->alphabetic_space_separator_context = false;
  state->opening_quote_space_context = false;
  state->opening_quote_after_alphabetic_context = false;
  state->closing_quote_after_ex_context = false;
  state->closing_quote_after_cl_context = false;
  state->closing_quote_after_id_context = false;
  state->id_after_closing_context = false;
  state->hyphen_after_hebrew_context = false;
  state->hyphen_after_bidi_format_context = false;
  state->opening_quote_at_start = false;
  state->quote_content_context = false;
  state->starter_after_hard_break = false;
  state->synthetic_starter_after_space = false;
  state->zero_width_space_combining_context = false;
  state->zero_width_space_context = false;
  state->zero_width_space_space_context = false;
}

bool my_line_break_state_feed(my_line_break_state_t* state, uint32_t cp) {
  bool allowed;
  bool previous_is_indic_virama;
  uint32_t previous_raw_cp;
  uint32_t previous_sequence_cp;
  uint32_t previous_starter_cp;
  uint8_t previous_numeric_context;
  if (state == NULL) return false;
  previous_raw_cp = state->previous_cp;
  previous_sequence_cp = previous_raw_cp;
  previous_starter_cp = state->previous_starter_cp;
  previous_is_indic_virama = state->indic_virama_context ||
                            my_line_break_class(previous_sequence_cp) == MY_LB_VI;
  if (is_line_break_combining_mark(previous_sequence_cp) &&
      (my_line_break_class(previous_sequence_cp) != MY_LB_VF &&
       (my_line_break_class(previous_sequence_cp) != MY_LB_VI ||
        state->has_starter))) {
    if (state->has_starter &&
        my_line_break_class(state->previous_starter_cp) != MY_LB_ZW &&
        !is_zero_width_space(state->previous_starter_cp) &&
        state->previous_starter_cp != 0x200Du) {
      previous_sequence_cp = state->previous_starter_cp;
    } else {
      previous_sequence_cp = 0x0041u;
    }
  }
  previous_numeric_context = state->numeric_context;
  if (!state->has_previous) {
    allowed = true;
  } else {
    allowed = my_line_break_allowed_with_ri_run(
        previous_sequence_cp, cp, state->regional_indicator_run);
    if (is_hard_break_cp(state->previous_cp) &&
        is_line_break_combining_mark(cp)) {
      allowed = true;
    }
    if (previous_is_indic_virama &&
        is_indic_aksara_or_dotted_circle(
            previous_sequence_cp,
            my_line_break_class(previous_sequence_cp)) &&
        is_indic_aksara_or_dotted_circle_target(
            cp, my_line_break_class(cp))) {
      allowed = false;
    }
    if (is_batak_vowel_mark(state->previous_cp) && cp == 0x1BC9u) {
      allowed = false;
    }
    /* UAX #14 LB18: an opening punctuation and following spaces stay with
     * the next character, so the consumed-space boundary cannot split them. */
    if (state->opening_space_context &&
        !(state->opening_quote_space_context &&
          my_line_break_class(cp) == MY_LB_OP && cp != 0x2329u) &&
        (!my_line_break_is_breaking_space(cp) ||
         my_line_break_class(cp) == MY_LB_BA)) {
      allowed = false;
    }
    if (state->opening_quote_space_context &&
        state->opening_quote_after_alphabetic_context &&
        is_non_hangul_alphabetic(cp, my_line_break_class(cp))) {
      allowed = true;
    }
    if (state->closing_space_context &&
        (my_line_break_class(cp) == MY_LB_NS ||
         my_line_break_class(cp) == MY_LB_CJ)) {
      allowed = false;
    }
    if (state->closing_space_context &&
        state->closing_space_after_opening_context && is_closing_quote(cp)) {
      allowed = true;
    }
    if (state->separator_space_context && is_closing_quote(cp)) {
      allowed = true;
    }
    if (state->break_both_after_quote_context &&
        state->previous_cp == 0x0020u && is_closing_quote(cp)) {
      allowed = true;
    }
    if (state->closing_quote_after_ex_context &&
        my_line_break_class(cp) == MY_LB_ID) {
      allowed = true;
    }
    if (state->closing_quote_after_cl_context &&
        my_line_break_class(cp) == MY_LB_ID) {
      allowed = true;
    }
    if (state->closing_quote_after_id_context &&
        my_line_break_class(cp) == MY_LB_ID) {
      allowed = true;
    }
    if (my_line_break_class(previous_sequence_cp) == MY_LB_ID &&
        (is_opening_quote(cp) || cp == 0x201Cu) &&
        !is_extended_pictographic(previous_sequence_cp) &&
        !is_id_extended_pictographic_unassigned(previous_sequence_cp) &&
        !is_xx_extended_pictographic_unassigned(previous_sequence_cp)) {
      allowed = true;
    }
    if (state->id_after_closing_context &&
        (is_opening_quote(cp) || cp == 0x201Cu)) {
      allowed = false;
    }
    if (state->zero_width_space_space_context &&
        !my_line_break_is_breaking_space(cp) && !is_hard_break_cp(cp) &&
        my_line_break_class(cp) != MY_LB_ZW && !is_zero_width_space(cp)) {
      if (!state->zero_width_space_combining_context ||
          (my_line_break_class(cp) != MY_LB_CL &&
           my_line_break_class(cp) != MY_LB_CP &&
           my_line_break_class(cp) != MY_LB_EX &&
           my_line_break_class(cp) != MY_LB_NS &&
           my_line_break_class(cp) != MY_LB_OP &&
           my_line_break_class(cp) != MY_LB_IS &&
           my_line_break_class(cp) != MY_LB_QU &&
           my_line_break_class(cp) != MY_LB_SY &&
           !is_non_break_glue(cp))) {
        allowed = true;
      }
    }
    if (state->alphabetic_space_separator_context &&
        (my_line_break_class(cp) == MY_LB_IS ||
         (is_closing_quote(cp) && !state->quote_content_context))) {
      allowed = true;
    }
    if (state->alphabetic_space_separator_context &&
        (my_line_break_class(state->previous_cp) == MY_LB_HY ||
         my_line_break_class(state->previous_cp) == MY_LB_HH) &&
        is_non_hangul_alphabetic(cp, my_line_break_class(cp))) {
      allowed = false;
    }
    if ((previous_numeric_context == 1u && is_exponent_marker(cp)) ||
        (previous_numeric_context == 2u &&
         (is_exponent_sign(cp) || is_numeric_value(cp))) ||
        (previous_numeric_context == 3u && is_numeric_value(cp)) ||
        (previous_numeric_context == 4u && is_numeric_value(cp))) {
      allowed = false;
    }
    if ((previous_numeric_context == 1u || previous_numeric_context == 4u) &&
        (my_line_break_class(cp) == MY_LB_PR ||
         my_line_break_class(cp) == MY_LB_PO)) {
      allowed = false;
    }
    if (previous_numeric_context == 5u &&
        is_non_hangul_alphabetic(cp, my_line_break_class(cp))) {
      allowed = true;
    }
    if (previous_numeric_context == 5u &&
        is_numeric_value(cp)) {
      allowed = false;
    }
    if (previous_numeric_context == 6u &&
        (my_line_break_class(cp) == MY_LB_PR ||
         my_line_break_class(cp) == MY_LB_PO)) {
      allowed = false;
    }
    if (previous_numeric_context == 7u && is_break_both(cp)) {
      allowed = false;
    }
    if (previous_numeric_context == 8u &&
        my_line_break_class(cp) == MY_LB_HL) {
      allowed = true;
    }
    if (state->hyphen_after_bidi_format_context &&
        my_line_break_class(cp) == MY_LB_HL) {
      allowed = true;
    }
    if (previous_numeric_context == 8u &&
        (my_line_break_class(cp) == MY_LB_AL ||
         my_line_break_class(cp) == MY_LB_AI ||
         my_line_break_class(cp) == MY_LB_SA)) {
      allowed = false;
    }
    if (previous_numeric_context == 9u && my_line_break_class(cp) == MY_LB_OP) {
      allowed = false;
    }
  }
  if (!is_line_break_combining_mark(cp) ||
      my_line_break_class(cp) == MY_LB_VF ||
      (my_line_break_class(cp) == MY_LB_VI && !state->has_starter)) {
    state->previous_starter_cp = cp;
    state->has_starter = true;
  } else if (state->has_previous &&
             (is_hard_break_cp(state->previous_cp) ||
              my_line_break_class(state->previous_cp) == MY_LB_SP ||
              my_line_break_class(state->previous_cp) == MY_LB_ZW ||
              is_zero_width_space(state->previous_cp))) {
    state->previous_starter_cp = 0x0041u;
    state->has_starter = true;
    state->synthetic_starter_after_space =
        my_line_break_class(state->previous_cp) == MY_LB_SP;
  }
  if (my_line_break_is_breaking_space(cp)) {
    uint32_t previous_cp = state->previous_cp;
    if (is_line_break_combining_mark(previous_cp) && state->has_starter) {
      previous_cp = previous_starter_cp;
    }
    if (my_line_break_class(previous_cp) == MY_LB_OP ||
        is_opening_quote(previous_cp)) {
      state->opening_space_context = true;
      state->opening_quote_space_context =
          is_opening_quote(previous_cp) && !state->opening_quote_at_start;
    }
    if (my_line_break_class(previous_cp) == MY_LB_CL ||
        my_line_break_class(previous_cp) == MY_LB_CP) {
      state->closing_space_context = true;
    }
    state->quote_space_context = is_closing_quote(previous_cp);
    state->separator_space_context = previous_cp == 0x003Au;
    if (state->zero_width_space_context) {
      state->zero_width_space_space_context = true;
    }
    if (state->zero_width_space_combining_context) {
      state->zero_width_space_space_context = true;
    }
    state->alphabetic_space_separator_context =
        my_line_break_class(previous_cp) == MY_LB_AL &&
        hangul_class(previous_cp) == MY_HANGUL_NONE &&
        !is_regional_indicator(previous_cp) &&
        !is_wide_east_asian(previous_cp) && previous_cp != 0x25CCu &&
        previous_cp != 0x0023u &&
        !is_non_break_extension(previous_cp) &&
        !is_non_break_glue(previous_cp) &&
        !is_hard_break_cp(state->previous_cp) &&
        !state->synthetic_starter_after_space &&
        !state->starter_after_hard_break &&
        !state->zero_width_space_context &&
        !state->zero_width_space_combining_context;
  } else if (!is_line_break_combining_mark(cp)) {
    state->zero_width_space_space_context = false;
    if (my_line_break_class(cp) != MY_LB_HY &&
        my_line_break_class(cp) != MY_LB_HH) {
      state->alphabetic_space_separator_context = false;
    }
    state->starter_after_hard_break = false;
    if (!my_line_break_is_breaking_space(cp)) {
      state->zero_width_space_combining_context = false;
    }
    state->opening_space_context =
        my_line_break_class(cp) == MY_LB_OP ||
        (state->opening_space_context &&
         (my_line_break_class(cp) == MY_LB_HY ||
          my_line_break_class(cp) == MY_LB_HH));
    state->opening_quote_space_context = false;
    state->opening_quote_after_alphabetic_context = false;
    state->opening_quote_at_start = false;
    state->closing_space_context = false;
    state->separator_space_context = false;
    state->synthetic_starter_after_space = false;
  }
  if (!is_line_break_combining_mark(cp)) {
    if (!my_line_break_is_breaking_space(cp)) {
      state->opening_quote_after_alphabetic_context = false;
      if (is_opening_quote(cp) && state->has_previous &&
          is_non_hangul_alphabetic(
              previous_sequence_cp, my_line_break_class(previous_sequence_cp))) {
        state->opening_quote_after_alphabetic_context = true;
      }
    }
    state->closing_quote_after_ex_context =
        is_closing_quote(cp) && state->has_previous &&
        (my_line_break_class(previous_sequence_cp) == MY_LB_EX ||
         my_line_break_class(previous_sequence_cp) == MY_LB_NS);
    state->closing_quote_after_cl_context =
        is_closing_quote(cp) && state->has_previous &&
        (my_line_break_class(previous_sequence_cp) == MY_LB_CL ||
         my_line_break_class(previous_sequence_cp) == MY_LB_CP);
    state->closing_quote_after_id_context =
        is_closing_quote(cp) && state->has_previous &&
        my_line_break_class(previous_sequence_cp) == MY_LB_ID;
    state->id_after_closing_context =
        my_line_break_class(cp) == MY_LB_ID && state->has_previous &&
        (my_line_break_class(previous_sequence_cp) == MY_LB_CL ||
         my_line_break_class(previous_sequence_cp) == MY_LB_CP ||
         my_line_break_class(previous_sequence_cp) == MY_LB_EX);
    if (is_opening_quote(cp)) {
      state->quote_content_context = true;
    } else if (is_closing_quote(cp)) {
      state->quote_content_context = false;
    }
    if (is_break_both(cp) &&
        state->quote_space_context) {
      state->break_both_after_quote_context = true;
    } else if (!my_line_break_is_breaking_space(cp) &&
               !is_break_both(cp)) {
      state->break_both_after_quote_context = false;
    }
    if (my_line_break_class(cp) == MY_LB_OP) {
      state->opening_punctuation_context = true;
      state->closing_space_after_opening_context = false;
    } else if ((my_line_break_class(cp) == MY_LB_CL ||
                my_line_break_class(cp) == MY_LB_CP) &&
               state->opening_punctuation_context) {
      state->closing_space_after_opening_context = true;
      state->opening_punctuation_context = false;
    } else if (my_line_break_class(cp) != MY_LB_SP) {
      state->opening_punctuation_context = false;
      state->closing_space_after_opening_context = false;
    }
    state->opening_quote_at_start =
        is_opening_quote(cp) && !state->has_previous;
    state->zero_width_space_context =
        my_line_break_class(cp) == MY_LB_ZW || is_zero_width_space(cp);
    state->starter_after_hard_break = is_hard_break_cp(cp);
  }
  if (is_line_break_combining_mark(cp)) {
    if (state->zero_width_space_context) {
      state->zero_width_space_combining_context = true;
      state->zero_width_space_context = false;
    }
    if (my_line_break_class(cp) == MY_LB_VI) {
      state->indic_virama_context = true;
    }
    state->previous_cp = cp;
    state->has_previous = true;
    return allowed;
  }
  state->indic_virama_context = my_line_break_class(cp) == MY_LB_VI;
  if (is_regional_indicator(cp)) {
    if (state->regional_indicator_run < SIZE_MAX) {
      state->regional_indicator_run++;
    }
  } else {
    state->regional_indicator_run = 0u;
  }
  state->previous_cp = cp;
  state->hyphen_after_hebrew_context =
      my_line_break_class(cp) == MY_LB_HY &&
      my_line_break_class(previous_sequence_cp) == MY_LB_HL;
  state->hyphen_after_bidi_format_context =
      my_line_break_class(cp) == MY_LB_HY &&
      is_bidi_format_cp(previous_raw_cp);
  if (is_numeric_value(cp)) {
    state->numeric_context = 1u;
  } else if (is_exponent_marker(cp) && previous_numeric_context == 1u) {
    state->numeric_context = 2u;
  } else if (is_exponent_sign(cp) && previous_numeric_context == 2u) {
    state->numeric_context = 3u;
  } else if (is_numeric_operator(cp) &&
             (previous_numeric_context == 1u ||
              previous_numeric_context == 4u)) {
    state->numeric_context = 4u;
  } else if (is_numeric_separator(cp) &&
             (previous_numeric_context == 1u ||
              previous_numeric_context == 4u)) {
    state->numeric_context = 1u;
  } else if ((is_percent_symbol(cp) ||
              my_line_break_class(cp) == MY_LB_PR ||
              my_line_break_class(cp) == MY_LB_PO) &&
             (previous_numeric_context == 1u || previous_numeric_context == 4u)) {
    state->numeric_context = 5u;
  } else if ((previous_numeric_context == 1u ||
                previous_numeric_context == 5u ||
                previous_numeric_context == 4u) &&
               (my_line_break_class(cp) == MY_LB_NS ||
                my_line_break_class(cp) == MY_LB_CL ||
                my_line_break_class(cp) == MY_LB_CP ||
                my_line_break_class(cp) == MY_LB_EX ||
                my_line_break_class(cp) == MY_LB_OP)) {
    state->numeric_context = 6u;
  } else if ((my_line_break_class(previous_sequence_cp) == MY_LB_PR ||
              my_line_break_class(previous_sequence_cp) == MY_LB_PO) &&
             my_line_break_class(cp) == MY_LB_OP) {
    state->numeric_context = 6u;
  } else if (is_break_both(cp) ||
             (previous_numeric_context == 7u &&
              my_line_break_is_breaking_space(cp))) {
    state->numeric_context = 7u;
  } else if (my_line_break_class(previous_sequence_cp) == MY_LB_HL &&
             (my_line_break_class(cp) == MY_LB_HY ||
              my_line_break_class(cp) == MY_LB_HH)) {
    state->numeric_context = 8u;
  } else if ((my_line_break_class(previous_sequence_cp) == MY_LB_CL ||
              my_line_break_class(previous_sequence_cp) == MY_LB_CP) &&
             previous_numeric_context == 6u && cp == '+') {
    state->numeric_context = 9u;
  } else if ((my_line_break_class(previous_sequence_cp) == MY_LB_CL ||
              my_line_break_class(previous_sequence_cp) == MY_LB_CP) &&
             previous_numeric_context == 6u && cp == 0x2212u) {
    state->numeric_context = 9u;
  } else {
    state->numeric_context = 0u;
  }
  state->has_previous = true;
  return allowed;
}

bool my_line_break_state_feed_with_lookahead(my_line_break_state_t* state,
                                             uint32_t cp, uint32_t next_cp,
                                             bool has_next) {
  uint32_t previous_cp;
  bool allowed;
  if (state == NULL) return false;
  previous_cp = state->previous_cp;
  allowed = my_line_break_state_feed(state, cp);
  if (has_next && my_line_break_class(previous_cp) == MY_LB_PR &&
      my_line_break_class(cp) == MY_LB_OP && is_numeric_value(next_cp)) {
    allowed = false;
  }
  if (has_next && my_line_break_class(previous_cp) == MY_LB_SP &&
      my_line_break_class(cp) == MY_LB_IS) {
    allowed = is_numeric_value(next_cp);
  }
  return allowed;
}

my_ret_t my_line_break_apply_dictionary(
    const uint32_t* codepoints, size_t count, bool* allow_before,
    const my_line_break_options_t* options) {
  return my_line_break_apply_dictionary_ex(codepoints, count, allow_before,
                                           options, NULL);
}

my_ret_t my_line_break_apply_dictionary_ex(
    const uint32_t* codepoints, size_t count, bool* allow_before,
    const my_line_break_options_t* options,
    const my_line_break_dictionary_profile_t* profile) {
  size_t i;
  if (count != 0u && (codepoints == NULL || allow_before == NULL)) {
    return MY_RET_INVALID_PARAMS;
  }
  for (i = 0u; i < count; ++i) {
    if (codepoints[i] > 0x10FFFFu ||
        (codepoints[i] >= 0xD800u && codepoints[i] <= 0xDFFFu)) {
      return MY_RET_INVALID_PARAMS;
    }
  }
  if (profile != NULL && !my_line_break_dictionary_profile_valid(profile)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (profile != NULL &&
      (options == NULL || options->dictionary == NULL)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (options == NULL || options->dictionary == NULL || count == 0u) {
    return MY_RET_OK;
  }
  if (options->max_codepoints == 0u ||
      options->max_codepoints > MY_LINE_BREAK_MAX_DICTIONARY_CODEPOINTS) {
    return MY_RET_INVALID_PARAMS;
  }
  for (i = 0u; i < count;) {
    size_t start;
    size_t end;
    size_t run_count;
    size_t boundary;
    bool scratch[MY_LINE_BREAK_MAX_DICTIONARY_CODEPOINTS];
    my_ret_t ret;
    if (my_line_break_class(codepoints[i]) != MY_LB_SA) {
      i++;
      continue;
    }
    start = i;
    end = start + 1u;
    while (end < count && my_line_break_class(codepoints[end]) == MY_LB_SA) {
      end++;
    }
    if (end - start > options->max_codepoints) {
      return MY_RET_INVALID_PARAMS;
    }
    run_count = end - start;
    for (boundary = 0u; boundary < run_count; boundary++) {
      scratch[boundary] = allow_before[start + boundary];
    }
    ret = options->dictionary(options->context, codepoints + start,
                              run_count, scratch);
    if (ret != MY_RET_OK) {
      return ret;
    }
    for (boundary = 1u; boundary < run_count; boundary++) {
      allow_before[start + boundary] = scratch[boundary];
    }
    i = end;
  }
  return MY_RET_OK;
}

my_ret_t my_line_break_apply_dictionary_profile(
    const uint32_t* codepoints, size_t count, bool* allow_before,
    const my_line_break_profile_options_t* options,
    const my_line_break_dictionary_profile_t* profile) {
  size_t i;
  if (count != 0u && (codepoints == NULL || allow_before == NULL)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (profile == NULL || !my_line_break_dictionary_profile_valid(profile) ||
      options == NULL || options->dictionary == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  for (i = 0u; i < count; ++i) {
    if (codepoints[i] > 0x10FFFFu ||
        (codepoints[i] >= 0xD800u && codepoints[i] <= 0xDFFFu)) {
      return MY_RET_INVALID_PARAMS;
    }
  }
  if (count == 0u) return MY_RET_OK;
  if (options->max_codepoints == 0u ||
      options->max_codepoints > MY_LINE_BREAK_MAX_DICTIONARY_CODEPOINTS) {
    return MY_RET_INVALID_PARAMS;
  }
  for (i = 0u; i < count;) {
    size_t start;
    size_t end;
    size_t run_count;
    size_t boundary;
    bool scratch[MY_LINE_BREAK_MAX_DICTIONARY_CODEPOINTS];
    my_ret_t ret;
    if (my_line_break_class(codepoints[i]) != MY_LB_SA) {
      i++;
      continue;
    }
    start = i;
    end = start + 1u;
    while (end < count && my_line_break_class(codepoints[end]) == MY_LB_SA) {
      end++;
    }
    run_count = end - start;
    if (run_count > options->max_codepoints) {
      return MY_RET_INVALID_PARAMS;
    }
    for (boundary = 0u; boundary < run_count; ++boundary) {
      scratch[boundary] = allow_before[start + boundary];
    }
    ret = options->dictionary(options->context, profile, codepoints + start,
                              run_count, scratch);
    if (ret != MY_RET_OK) return ret;
    for (boundary = 1u; boundary < run_count; ++boundary) {
      allow_before[start + boundary] = scratch[boundary];
    }
    i = end;
  }
  return MY_RET_OK;
}
