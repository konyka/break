/**
 * @file my_line_break.h
 * @brief Simplified line-break classes for word wrap (M12d, a UAX#14
 * practical subset).
 *
 * Classes (data: my_line_break_data.h, generated from Unicode UCD):
 *  - MY_LB_AL: letters/digits/marks -- no break inside a run;
 *  - MY_LB_SA: complex-script letters requiring dictionary/locale tailoring;
 *  - MY_LB_SP: ASCII space -- a break consumes it (space semantics of
 *    M10b: no visual line starts with whitespace);
 *  - MY_LB_HY: hyphen / soft hyphen -- break AFTER it;
 *  - MY_LB_ID: ideographic and everything else -- break allowed between
 *    chars (CJK word wrap);
 *  - MY_LB_NS: no-start (，。！？；：、）」』 etc.) -- a visual line may
 *    NOT start with it (break before it is forbidden);
 *  - MY_LB_OP: open bracket （「『 etc.) -- a visual line may NOT end
 *    with it (break after it is forbidden);
 *  - MY_LB_BK: hard breaks (\n, \v, \f, etc.) -- handled by the physical-line
 *    logic, never reached by the table in practice.
 *
 * This is a SUBSET: the built-in SA corpus is intentionally small, and the
 * full set of locale-specific tailoring remains out of scope. The contextual helper
 * below covers UnicodeData Mn/Mc/Me combining marks, numeric punctuation,
 * Hebrew quotes, regional indicators, Unicode glue and emoji/joiner extensions
 * including ZWNJ, non-breaking hyphen and BOM/WJ glue. B2 break-both pairs and
 * Hebrew solidus sequences are also protected. Numeric affix, Hangul LB27 and
 * sequence-sensitive regional-indicator pairing are exposed
 * through my_line_break_state_t. Numeric streaming context uses generated
 * Unicode NU/IS/SY classes in addition to compatibility codepoint checks.
 * Hangul Jamo and LV/LVT syllable composition
 * follows the UAX #14 LB26 rules; streaming context also preserves LB17
 * B2-space-B2 and LB21.1 Hebrew hyphen sequences. The generated table also
 * preserves QU, HH, BB, B2,
 * HL, SY, NU, PR, PO and IS so contextual rules do not depend on ASCII-only
 * codepoint checks.
 * Unicode 17 `AP/AK/AS/VF/VI` classes are not folded into the generic
 * alphabetic rule: LB28.11-LB28.14 are directional, and callers processing
 * a stream must use my_line_break_state_feed() so virama context is retained.
 */
#ifndef MY_LINE_BREAK_H
#define MY_LINE_BREAK_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "myc/my_error.h"

typedef enum my_line_break_class_t {
  MY_LB_AL = 0, /**< letter/number run: no break inside */
  MY_LB_SA,     /**< complex-script run: dictionary tailoring required */
  MY_LB_SP,     /**< space: break here, consumed */
  MY_LB_HY,     /**< hyphen: break after */
  MY_LB_ID,     /**< ideographic / default: break allowed */
  MY_LB_NS,     /**< no-start punctuation: line must not start with it */
  MY_LB_OP,     /**< open bracket: line must not end with it */
  MY_LB_ZW,     /**< zero-width space: break after it, never before it */
  MY_LB_BK,     /**< hard break (physical line, outside the table) */
  MY_LB_QU,     /**< quotation mark: no break on either side */
  MY_LB_HH,     /**< Hebrew hyphen */
  MY_LB_B2,     /**< break-before-and-after punctuation */
  MY_LB_HL,     /**< Hebrew letter */
  MY_LB_SY,     /**< solidus */
  MY_LB_NU,     /**< numeric */
  MY_LB_PR,     /**< prefix numeric punctuation */
  MY_LB_PO,     /**< postfix numeric punctuation */
  MY_LB_IS,     /**< numeric separator */
  MY_LB_BA,     /**< break-after punctuation or spacing */
  MY_LB_BB,     /**< break-before punctuation */
  MY_LB_IN,     /**< inseparable punctuation */
  MY_LB_CB,     /**< contingent break / object boundary */
  MY_LB_EB,     /**< emoji base */
  MY_LB_EM,     /**< emoji modifier */
  MY_LB_CJ,     /**< conditional Japanese starter */
  MY_LB_AP,     /**< alphabetic prefix */
  MY_LB_AK,     /**< alphabetic consonant */
  MY_LB_AS,     /**< alphabetic syllable */
  MY_LB_VF,     /**< virama final */
  MY_LB_VI,      /**< virama */
  MY_LB_CL,      /**< closing punctuation */
  MY_LB_CP,      /**< closing parenthesis */
  MY_LB_EX,      /**< exclamation or interrogation punctuation */
  MY_LB_CM,      /**< combining mark: inherits the preceding class */
  MY_LB_GL,       /**< non-breaking glue, with BA/HY exception */
  MY_LB_AI        /**< ambiguous East Asian character */
} my_line_break_class_t;

/**
 * @brief Bounded dictionary callback for one contiguous SA run.
 *
 * `allow_before[0]` is ignored; entries 1..count-1 describe boundaries
 * inside the run. The callback must fill every entry it handles. It must not
 * retain the input or output pointers. The caller enforces max_codepoints.
 */
typedef my_ret_t (*my_line_break_dictionary_fn)(
    void* context, const uint32_t* codepoints, size_t count,
    bool* allow_before);

#define MY_LINE_BREAK_DICTIONARY_PROFILE_VERSION 1u
#define MY_LINE_BREAK_DICTIONARY_MAX_LOCALE_BYTES 64u

/** @brief Immutable identity for a dictionary tailoring implementation. */
typedef struct my_line_break_dictionary_profile_t {
  uint32_t version;
  const char* locale;
} my_line_break_dictionary_profile_t;

typedef my_ret_t (*my_line_break_dictionary_profile_fn)(
    void* context, const my_line_break_dictionary_profile_t* profile,
    const uint32_t* codepoints, size_t count, bool* allow_before);

typedef struct my_line_break_profile_options_t {
  my_line_break_dictionary_profile_fn dictionary;
  void* context;
  size_t max_codepoints;
} my_line_break_profile_options_t;

typedef struct my_line_break_options_t {
  my_line_break_dictionary_fn dictionary;
  void* context;
  size_t max_codepoints;
} my_line_break_options_t;

#define MY_LINE_BREAK_MAX_DICTIONARY_CODEPOINTS 256u

/** @brief Return whether the bounded built-in dictionary supports a profile. */
bool my_line_break_builtin_dictionary_supports(
    const my_line_break_dictionary_profile_t* profile);

/**
 * @brief Apply the fixed, allocation-free built-in SA dictionary.
 *
 * The built-in corpus is intentionally bounded and currently covers the
 * version-1 `th-Thai` profile only. Unknown words remain unbreakable; this
 * avoids inventing unsafe boundaries when a word is outside the corpus.
 */
my_ret_t my_line_break_apply_builtin_dictionary(
    const uint32_t* codepoints, size_t count, bool* allow_before,
    const my_line_break_dictionary_profile_t* profile);

/** @brief Profile callback adapter for paragraph wrapping. */
my_ret_t my_line_break_builtin_dictionary_callback(
    void* context, const my_line_break_dictionary_profile_t* profile,
    const uint32_t* codepoints, size_t count, bool* allow_before);

/** @brief Validate a bounded dictionary profile without allocation. */
bool my_line_break_dictionary_profile_valid(
    const my_line_break_dictionary_profile_t* profile);

/** @brief Streaming context for sequence-sensitive line-break rules. */
typedef struct my_line_break_state_t {
  uint32_t previous_cp;
  uint32_t previous_starter_cp;
  size_t regional_indicator_run;
  uint8_t numeric_context;
  bool opening_space_context;
  bool opening_punctuation_context;
  bool indic_virama_context;
  bool has_previous;
  bool has_starter;
  bool closing_space_context;
  bool separator_space_context;
  bool quote_space_context;
  bool break_both_after_quote_context;
  bool closing_space_after_opening_context;
  bool alphabetic_space_separator_context;
  bool opening_quote_space_context;
  bool opening_quote_after_alphabetic_context;
  bool closing_quote_after_ex_context;
  bool closing_quote_after_cl_context;
  bool closing_quote_after_id_context;
  bool id_after_closing_context;
  bool hyphen_after_hebrew_context;
  bool hyphen_after_bidi_format_context;
  bool opening_quote_at_start;
  bool quote_content_context;
  bool starter_after_hard_break;
  bool synthetic_starter_after_space;
  bool zero_width_space_combining_context;
  bool zero_width_space_context;
  bool zero_width_space_space_context;
} my_line_break_state_t;

/** @brief Simplified line-break class of a codepoint (binary search,
 * default MY_LB_ID for gaps in the table). */
my_line_break_class_t my_line_break_class(uint32_t cp);

/** @brief Return the UTF-8 byte length of a hard line separator at `text`.
 * Includes LF, VT, FF, CR/CRLF, NEL, LS and PS. */
size_t my_line_break_hard_break_len(const char* text, size_t remaining);

/** @brief Whether a codepoint is a breakable space consumed by wrapping. */
bool my_line_break_is_breaking_space(uint32_t cp);

/** @brief Whether a line break is allowed between adjacent codepoints. */
bool my_line_break_allowed(uint32_t prev_cp, uint32_t cur_cp);

/** @brief Reset sequence context before feeding a codepoint stream. */
void my_line_break_state_init(my_line_break_state_t* state);

/** @brief Consume one codepoint and decide whether a break may precede it. */
bool my_line_break_state_feed(my_line_break_state_t* state, uint32_t cp);

/** @brief Feed one codepoint with one-codepoint right lookahead. */
bool my_line_break_state_feed_with_lookahead(my_line_break_state_t* state,
                                             uint32_t cp, uint32_t next_cp,
                                             bool has_next);

/**
 * @brief Resolve SA boundaries in a precomputed boundary array.
 *
 * The default NULL options preserve the no-break-then-emergency-split
 * behavior. Non-NULL dictionaries are called only for contiguous SA runs and
 * are subject to the explicit run-size budget. A failing callback does not
 * commit changes for its current run.
 */
my_ret_t my_line_break_apply_dictionary(
    const uint32_t* codepoints, size_t count, bool* allow_before,
    const my_line_break_options_t* options);

/** @brief Apply a dictionary with an explicit versioned locale contract. */
my_ret_t my_line_break_apply_dictionary_ex(
    const uint32_t* codepoints, size_t count, bool* allow_before,
    const my_line_break_options_t* options,
    const my_line_break_dictionary_profile_t* profile);

my_ret_t my_line_break_apply_dictionary_profile(
    const uint32_t* codepoints, size_t count, bool* allow_before,
    const my_line_break_profile_options_t* options,
    const my_line_break_dictionary_profile_t* profile);

#endif /* MY_LINE_BREAK_H */
