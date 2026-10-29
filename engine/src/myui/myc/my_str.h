/**
 * @file my_str.h
 * @brief UTF-8 aware string utilities with pluggable allocation.
 */
#ifndef MY_STR_H
#define MY_STR_H

#include "myc/my_error.h"
#include "myc/my_mem.h"

/** @brief Duplicate s via allocator (NULL allocator = default). NULL s -> NULL. */
char* my_strdup(const my_allocator_t* allocator, const char* s);

/**
 * @brief Duplicate at most n bytes of s, always NUL-terminated.
 * NULL s -> NULL.
 */
char* my_strndup(const my_allocator_t* allocator, const char* s, size_t n);

/** @brief Byte length of s (0 for NULL). */
size_t my_str_len(const char* s);

/** @brief NULL-safe string equality (NULL == NULL is true). */
bool my_str_eq(const char* a, const char* b);

/** @brief Whether s starts with prefix (NULL/empty rules: NULL args -> false). */
bool my_str_start_with(const char* s, const char* prefix);

/** @brief Whether s ends with suffix (NULL args -> false). */
bool my_str_end_with(const char* s, const char* suffix);

/**
 * @brief Byte length of the UTF-8 character starting at s.
 * @return 1-4 for a valid scalar UTF-8 sequence, 1 for malformed input
 *         (skip one byte), 0 for NULL or empty string.
 */
size_t my_str_utf8_char_len(const char* s);

/** @brief Number of UTF-8 characters (code points) in s (0 for NULL). */
size_t my_str_utf8_strlen(const char* s);

/**
 * @brief strtod that always uses '.' as the decimal point, whatever
 * LC_NUMERIC the process set. Reads the number-shaped prefix of text
 * (sign, digits, '.', exponent, inf/nan/hex letters; at most 255 bytes);
 * *end (when non-NULL) points into text past the consumed characters.
 * The locale's own point (',' under de_DE) is never accepted.
 */
double my_strtod_c(const char* text, char** end);

/** @brief strtof counterpart of my_strtod_c. */
float my_strtof_c(const char* text, char** end);

/**
 * @brief In-place: replace the locale decimal point that snprintf wrote
 * into buf with '.', so "%g"/"%f" output is locale-independent. buf must
 * be NUL-terminated; a multi-byte locale point is collapsed to one '.'.
 */
void my_str_c_decimal(char* buf);

#endif /* MY_STR_H */
