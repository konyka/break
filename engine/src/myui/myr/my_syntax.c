#include "myr/my_syntax.h"

#include <ctype.h>
#include <string.h>

typedef struct syntax_line_t {
  char* text;
  size_t text_len;
  my_syntax_token_t* tokens;
  size_t token_count;
  size_t token_capacity;
  my_syntax_state_t in_state;
  my_syntax_state_t out_state;
  bool ready;
} syntax_line_t;

struct my_syntax_cache_t {
  const my_allocator_t* allocator;
  my_syntax_language_t language;
  syntax_line_t* lines;
  size_t line_count;
  size_t line_capacity;
  size_t dirty_from;
};

static void syntax_line_clear(const my_allocator_t* allocator,
                              syntax_line_t* line) {
  if (line == NULL) return;
  my_mem_free(allocator, line->text);
  my_mem_free(allocator, line->tokens);
  memset(line, 0, sizeof(*line));
}

static bool syntax_is_word_start(unsigned char c) {
  return isalpha(c) || c == '_' || c == '$' || c >= 0x80u;
}

static bool syntax_is_word_continue(unsigned char c) {
  return isalnum(c) || c == '_' || c == '$' || c >= 0x80u;
}

static size_t syntax_cp_len(const char* text, size_t len, size_t at) {
  unsigned char c;
  if (at >= len) return 0;
  c = (unsigned char)text[at];
  if (c < 0x80u) return 1;
  if ((c & 0xE0u) == 0xC0u && at + 1 < len) return 2;
  if ((c & 0xF0u) == 0xE0u && at + 2 < len) return 3;
  if ((c & 0xF8u) == 0xF0u && at + 3 < len) return 4;
  return 1;
}

static bool syntax_keyword(my_syntax_language_t language, const char* text,
                           size_t len) {
  static const char* const c_words[] = {
      "auto", "break", "case", "const", "else", "enum", "for", "if",
      "int", "return", "static", "struct", "switch", "typedef", "void",
      "while", "bool", "true", "false", "NULL"};
  static const char* const yaml_words[] = {"true", "false", "null", "yes",
                                             "no", "on", "off"};
  const char* const* words = language == MY_SYNTAX_YAML ? yaml_words : c_words;
  size_t count = language == MY_SYNTAX_YAML
                     ? sizeof(yaml_words) / sizeof(yaml_words[0])
                     : sizeof(c_words) / sizeof(c_words[0]);
  size_t i;
  if (language == MY_SYNTAX_NONE) return false;
  for (i = 0; i < count; i++) {
    if (strlen(words[i]) == len && memcmp(words[i], text, len) == 0) {
      return true;
    }
  }
  return false;
}

static my_ret_t syntax_token_push(const my_allocator_t* allocator,
                                  syntax_line_t* line, size_t start_cp,
                                  size_t len_cp,
                                  my_syntax_token_kind_t kind) {
  my_syntax_token_t* grown;
  size_t capacity;
  if (line->token_count >= MY_SYNTAX_MAX_TOKENS_PER_LINE) {
    return MY_RET_INVALID_PARAMS;
  }
  if (line->token_count == line->token_capacity) {
    capacity = line->token_capacity == 0 ? 16 : line->token_capacity * 2;
    if (capacity > MY_SYNTAX_MAX_TOKENS_PER_LINE) {
      capacity = MY_SYNTAX_MAX_TOKENS_PER_LINE;
    }
    grown = (my_syntax_token_t*)my_mem_realloc(
        allocator, line->tokens, capacity * sizeof(*grown));
    if (grown == NULL) return MY_RET_OOM;
    line->tokens = grown;
    line->token_capacity = capacity;
  }
  line->tokens[line->token_count++] =
      (my_syntax_token_t){start_cp, len_cp, kind};
  return MY_RET_OK;
}

static my_ret_t syntax_lex_line(const my_allocator_t* allocator,
                                my_syntax_language_t language,
                                const char* text, size_t len,
                                my_syntax_state_t in_state,
                                syntax_line_t* line) {
  size_t at = 0;
  size_t cp = 0;
  my_syntax_state_t state = in_state;
  my_ret_t status;
  if (len > MY_SYNTAX_MAX_LINE_BYTES) return MY_RET_INVALID_PARAMS;
  line->token_count = 0;
  line->in_state = in_state;
  while (at < len) {
    size_t start = at;
    size_t start_cp = cp;
    size_t step;
    my_syntax_token_kind_t kind;
    if (state == MY_SYNTAX_STATE_BLOCK_COMMENT) {
      while (at < len) {
        if (at + 1 < len && text[at] == '*' && text[at + 1] == '/') {
          at += 2;
          cp += 2;
          state = MY_SYNTAX_STATE_NORMAL;
          break;
        }
        step = syntax_cp_len(text, len, at);
        at += step;
        cp++;
      }
      status = syntax_token_push(allocator, line, start_cp, cp - start_cp,
                                 MY_SYNTAX_TOKEN_COMMENT);
      if (status != MY_RET_OK) return status;
      continue;
    }
    if (isspace((unsigned char)text[at])) {
      do {
        step = syntax_cp_len(text, len, at);
        at += step;
        cp++;
      } while (at < len && isspace((unsigned char)text[at]));
      kind = MY_SYNTAX_TOKEN_TEXT;
    } else if ((language == MY_SYNTAX_YAML && text[at] == '#') ||
               (language != MY_SYNTAX_YAML && at + 1 < len &&
                text[at] == '/' && text[at + 1] == '/')) {
      while (at < len) {
        step = syntax_cp_len(text, len, at);
        at += step;
        cp++;
      }
      kind = MY_SYNTAX_TOKEN_COMMENT;
    } else if (language != MY_SYNTAX_YAML && at + 1 < len &&
               text[at] == '/' && text[at + 1] == '*') {
      at += 2;
      cp += 2;
      state = MY_SYNTAX_STATE_BLOCK_COMMENT;
      kind = MY_SYNTAX_TOKEN_COMMENT;
      while (at < len) {
        if (at + 1 < len && text[at] == '*' && text[at + 1] == '/') {
          at += 2;
          cp += 2;
          state = MY_SYNTAX_STATE_NORMAL;
          break;
        }
        step = syntax_cp_len(text, len, at);
        at += step;
        cp++;
      }
    } else if (text[at] == '"' || text[at] == '\'') {
      unsigned char quote = (unsigned char)text[at++];
      cp++;
      while (at < len) {
        step = syntax_cp_len(text, len, at);
        if ((unsigned char)text[at] == '\\' && at + step < len) {
          at += step;
          cp++;
          step = syntax_cp_len(text, len, at);
        } else if ((unsigned char)text[at] == quote) {
          at += step;
          cp++;
          break;
        }
        at += step;
        cp++;
      }
      kind = MY_SYNTAX_TOKEN_STRING;
    } else if (isdigit((unsigned char)text[at])) {
      do {
        step = syntax_cp_len(text, len, at);
        at += step;
        cp++;
      } while (at < len &&
               (isalnum((unsigned char)text[at]) || text[at] == '.' ||
                text[at] == '_' || text[at] == '+' || text[at] == '-'));
      kind = MY_SYNTAX_TOKEN_NUMBER;
    } else if (syntax_is_word_start((unsigned char)text[at])) {
      do {
        step = syntax_cp_len(text, len, at);
        at += step;
        cp++;
      } while (at < len && syntax_is_word_continue((unsigned char)text[at]));
      kind = syntax_keyword(language, text + start, at - start)
                 ? MY_SYNTAX_TOKEN_KEYWORD
                 : MY_SYNTAX_TOKEN_IDENTIFIER;
    } else {
      step = syntax_cp_len(text, len, at);
      at += step;
      cp++;
      kind = MY_SYNTAX_TOKEN_PUNCTUATION;
    }
    status = syntax_token_push(allocator, line, start_cp, cp - start_cp, kind);
    if (status != MY_RET_OK) return status;
  }
  line->out_state = state;
  line->ready = true;
  return MY_RET_OK;
}

static my_ret_t syntax_lines_reserve(my_syntax_cache_t* cache, size_t count) {
  syntax_line_t* lines;
  size_t capacity;
  if (count <= cache->line_capacity) return MY_RET_OK;
  capacity = cache->line_capacity == 0 ? 8 : cache->line_capacity;
  while (capacity < count) {
    if (capacity > (size_t)-1 / 2) return MY_RET_OOM;
    capacity *= 2;
  }
  if (capacity > (size_t)-1 / sizeof(*lines)) return MY_RET_OOM;
  lines = (syntax_line_t*)my_mem_realloc(cache->allocator, cache->lines,
                                          capacity * sizeof(*lines));
  if (lines == NULL) return MY_RET_OOM;
  memset(lines + cache->line_capacity, 0,
         (capacity - cache->line_capacity) * sizeof(*lines));
  cache->lines = lines;
  cache->line_capacity = capacity;
  return MY_RET_OK;
}

static my_ret_t syntax_set_line(syntax_line_t* line,
                                const my_allocator_t* allocator,
                                const char* text, size_t len) {
  char* copy = (char*)my_mem_alloc(allocator, len + 1);
  if (copy == NULL) return MY_RET_OOM;
  if (len > 0) memcpy(copy, text, len);
  copy[len] = '\0';
  my_mem_free(allocator, line->text);
  my_mem_free(allocator, line->tokens);
  line->text = copy;
  line->text_len = len;
  line->tokens = NULL;
  line->token_count = 0;
  line->token_capacity = 0;
  line->ready = false;
  return MY_RET_OK;
}

static void syntax_cache_lines_destroy(my_syntax_cache_t* cache) {
  size_t i;
  for (i = 0; i < cache->line_count; i++) {
    syntax_line_clear(cache->allocator, &cache->lines[i]);
  }
  my_mem_free(cache->allocator, cache->lines);
  cache->lines = NULL;
  cache->line_count = 0;
  cache->line_capacity = 0;
}

my_syntax_cache_t* my_syntax_cache_create(const my_allocator_t* allocator,
                                          my_syntax_language_t language) {
  my_syntax_cache_t* cache =
      (my_syntax_cache_t*)my_mem_calloc(allocator, 1, sizeof(*cache));
  if (cache == NULL) return NULL;
  cache->allocator = allocator;
  cache->language = language;
  cache->dirty_from = 0;
  if (my_syntax_cache_set_text(cache, "") != MY_RET_OK) {
    my_syntax_cache_destroy(cache);
    return NULL;
  }
  return cache;
}

void my_syntax_cache_destroy(my_syntax_cache_t* cache) {
  if (cache == NULL) return;
  syntax_cache_lines_destroy(cache);
  my_mem_free(cache->allocator, cache);
}

static my_ret_t syntax_cache_set_text_inplace(my_syntax_cache_t* cache,
                                              const char* text) {
  size_t len;
  size_t at = 0;
  size_t row = 0;
  if (cache == NULL || text == NULL) return MY_RET_INVALID_PARAMS;
  len = strlen(text);
  if (len > MY_SYNTAX_MAX_SOURCE_BYTES) return MY_RET_INVALID_PARAMS;
  while (at <= len) {
    size_t end = at;
    while (end < len && text[end] != '\n') end++;
    if (end - at > MY_SYNTAX_MAX_LINE_BYTES) return MY_RET_INVALID_PARAMS;
    if (syntax_lines_reserve(cache, row + 1) != MY_RET_OK) return MY_RET_OOM;
    if (row >= cache->line_count) {
      memset(&cache->lines[row], 0, sizeof(cache->lines[row]));
      cache->line_count = row + 1;
    }
    if (syntax_set_line(&cache->lines[row], cache->allocator, text + at,
                        end - at) != MY_RET_OK) {
      return MY_RET_OOM;
    }
    row++;
    if (end == len) break;
    at = end + 1;
  }
  while (cache->line_count > row) {
    syntax_line_clear(cache->allocator, &cache->lines[cache->line_count - 1]);
    cache->line_count--;
  }
  cache->dirty_from = 0;
  return MY_RET_OK;
}

my_ret_t my_syntax_cache_set_text(my_syntax_cache_t* cache, const char* text) {
  my_syntax_cache_t candidate;
  my_ret_t status;
  if (cache == NULL || text == NULL) return MY_RET_INVALID_PARAMS;
  memset(&candidate, 0, sizeof(candidate));
  candidate.allocator = cache->allocator;
  candidate.language = cache->language;
  status = syntax_cache_set_text_inplace(&candidate, text);
  if (status != MY_RET_OK) {
    syntax_cache_lines_destroy(&candidate);
    return status;
  }
  syntax_cache_lines_destroy(cache);
  cache->lines = candidate.lines;
  cache->line_count = candidate.line_count;
  cache->line_capacity = candidate.line_capacity;
  cache->dirty_from = 0;
  return MY_RET_OK;
}

my_ret_t my_syntax_cache_replace_line(my_syntax_cache_t* cache, size_t row,
                                      const char* text) {
  if (text == NULL) return MY_RET_INVALID_PARAMS;
  return my_syntax_cache_replace_line_n(cache, row, text, strlen(text));
}

my_ret_t my_syntax_cache_replace_line_n(my_syntax_cache_t* cache, size_t row,
                                        const char* text, size_t len) {
  size_t index;
  if (cache == NULL || text == NULL || row >= cache->line_count) {
    return MY_RET_INVALID_PARAMS;
  }
  if (len > MY_SYNTAX_MAX_LINE_BYTES) return MY_RET_INVALID_PARAMS;
  if (syntax_set_line(&cache->lines[row], cache->allocator, text, len) !=
      MY_RET_OK) {
    return MY_RET_OOM;
  }
  for (index = row + 1; index < cache->line_count; index++) {
    cache->lines[index].ready = false;
  }
  if (row < cache->dirty_from) cache->dirty_from = row;
  return MY_RET_OK;
}

my_ret_t my_syntax_cache_set_language(my_syntax_cache_t* cache,
                                       my_syntax_language_t language) {
  size_t i;
  if (cache == NULL) return MY_RET_INVALID_PARAMS;
  cache->language = language;
  cache->dirty_from = 0;
  for (i = 0; i < cache->line_count; i++) cache->lines[i].ready = false;
  return MY_RET_OK;
}

size_t my_syntax_cache_line_count(const my_syntax_cache_t* cache) {
  return cache != NULL ? cache->line_count : 0;
}

my_ret_t my_syntax_cache_ensure(my_syntax_cache_t* cache, size_t line_budget) {
  size_t row;
  my_syntax_state_t state = MY_SYNTAX_STATE_NORMAL;
  if (cache == NULL) return MY_RET_INVALID_PARAMS;
  if (line_budget == 0) return MY_RET_OK;
  for (row = cache->dirty_from; row < cache->line_count && line_budget > 0;
       row++, line_budget--) {
    if (row > 0) state = cache->lines[row - 1].out_state;
    {
      my_ret_t status = syntax_lex_line(
          cache->allocator, cache->language, cache->lines[row].text,
          cache->lines[row].text_len, state, &cache->lines[row]);
      if (status != MY_RET_OK) {
      cache->lines[row].ready = false;
        return status;
      }
    }
  }
  cache->dirty_from = row < cache->line_count ? row : cache->line_count;
  return MY_RET_OK;
}

bool my_syntax_cache_line_ready(const my_syntax_cache_t* cache, size_t row) {
  return cache != NULL && row < cache->line_count && cache->lines[row].ready;
}

const my_syntax_token_t* my_syntax_cache_line_tokens(
    const my_syntax_cache_t* cache, size_t row, size_t* count) {
  if (count != NULL) *count = 0;
  if (cache == NULL || row >= cache->line_count || !cache->lines[row].ready) {
    return NULL;
  }
  if (count != NULL) *count = cache->lines[row].token_count;
  return cache->lines[row].tokens;
}
