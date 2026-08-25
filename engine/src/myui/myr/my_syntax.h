/**
 * @file my_syntax.h
 * @brief Bounded, incremental lexical highlighting for editor line models.
 */
#ifndef MY_SYNTAX_H
#define MY_SYNTAX_H

#include "myc/my_error.h"
#include "myc/my_mem.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MY_SYNTAX_MAX_SOURCE_BYTES (4u * 1024u * 1024u)
#define MY_SYNTAX_MAX_LINE_BYTES (1u * 1024u * 1024u)
#define MY_SYNTAX_MAX_TOKENS_PER_LINE 4096u

typedef enum my_syntax_language_t {
  MY_SYNTAX_NONE = 0,
  MY_SYNTAX_C_LIKE,
  MY_SYNTAX_YAML
} my_syntax_language_t;

typedef enum my_syntax_state_t {
  MY_SYNTAX_STATE_NORMAL = 0,
  MY_SYNTAX_STATE_BLOCK_COMMENT
} my_syntax_state_t;

typedef enum my_syntax_token_kind_t {
  MY_SYNTAX_TOKEN_TEXT = 0,
  MY_SYNTAX_TOKEN_KEYWORD,
  MY_SYNTAX_TOKEN_IDENTIFIER,
  MY_SYNTAX_TOKEN_NUMBER,
  MY_SYNTAX_TOKEN_STRING,
  MY_SYNTAX_TOKEN_COMMENT,
  MY_SYNTAX_TOKEN_PUNCTUATION
} my_syntax_token_kind_t;

typedef struct my_syntax_token_t {
  size_t start_cp;
  size_t len_cp;
  my_syntax_token_kind_t kind;
} my_syntax_token_t;

typedef struct my_syntax_cache_t my_syntax_cache_t;

my_syntax_cache_t* my_syntax_cache_create(const my_allocator_t* allocator,
                                          my_syntax_language_t language);
void my_syntax_cache_destroy(my_syntax_cache_t* cache);
my_ret_t my_syntax_cache_set_text(my_syntax_cache_t* cache, const char* text);
my_ret_t my_syntax_cache_replace_line(my_syntax_cache_t* cache, size_t row,
                                      const char* text);
my_ret_t my_syntax_cache_replace_line_n(my_syntax_cache_t* cache, size_t row,
                                        const char* text, size_t len);
my_ret_t my_syntax_cache_set_language(my_syntax_cache_t* cache,
                                       my_syntax_language_t language);
size_t my_syntax_cache_line_count(const my_syntax_cache_t* cache);

/**
 * Rebuild at most `line_budget` invalid lines. A zero budget is a no-op.
 * Returning OK does not imply all lines are ready; query each line first.
 */
my_ret_t my_syntax_cache_ensure(my_syntax_cache_t* cache,
                                size_t line_budget);
bool my_syntax_cache_line_ready(const my_syntax_cache_t* cache, size_t row);
const my_syntax_token_t* my_syntax_cache_line_tokens(
    const my_syntax_cache_t* cache, size_t row, size_t* count);

#endif /* MY_SYNTAX_H */
