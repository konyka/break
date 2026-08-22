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
 * @return 1-4 for a valid lead byte, 1 for an invalid lead byte (skip
 *         strategy), 0 for NULL or empty string.
 */
size_t my_str_utf8_char_len(const char* s);

/** @brief Number of UTF-8 characters (code points) in s (0 for NULL). */
size_t my_str_utf8_strlen(const char* s);

#endif /* MY_STR_H */
