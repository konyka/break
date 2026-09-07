/* Verify MyUI line breaking against the Unicode LineBreakTest format. */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "myr/my_line_break.h"

#define MYUI_LINE_BREAK_LINE_BYTES 65536u

typedef struct line_cursor_t {
  const char* current;
  const char* end;
} line_cursor_t;

static void skip_space_and_comment(line_cursor_t* cursor) {
  while (cursor->current < cursor->end) {
    unsigned char byte = (unsigned char)*cursor->current;
    if (byte == '#') {
      cursor->current = cursor->end;
      return;
    }
    if (byte == ' ' || byte == '\t' || byte == '\r' || byte == '\n') {
      cursor->current++;
      continue;
    }
    break;
  }
}

static int parse_marker(line_cursor_t* cursor, int* marker) {
  if (cursor == NULL || marker == NULL) return 0;
  skip_space_and_comment(cursor);
  if ((size_t)(cursor->end - cursor->current) >= 2u &&
      (unsigned char)cursor->current[0] == 0xC3u &&
      (unsigned char)cursor->current[1] == 0xB7u) {
    *marker = 1;
    cursor->current += 2;
    return 1;
  }
  if ((size_t)(cursor->end - cursor->current) >= 2u &&
      (unsigned char)cursor->current[0] == 0xC3u &&
      (unsigned char)cursor->current[1] == 0x97u) {
    *marker = 0;
    cursor->current += 2;
    return 1;
  }
  return 0;
}

static int parse_codepoint(line_cursor_t* cursor, uint32_t* codepoint) {
  uint32_t value = 0u;
  size_t digits = 0u;
  if (cursor == NULL || codepoint == NULL) return 0;
  skip_space_and_comment(cursor);
  while (cursor->current < cursor->end) {
    unsigned char byte = (unsigned char)*cursor->current;
    uint32_t digit;
    if (byte >= '0' && byte <= '9') {
      digit = (uint32_t)(byte - '0');
    } else if (byte >= 'A' && byte <= 'F') {
      digit = (uint32_t)(byte - 'A') + 10u;
    } else if (byte >= 'a' && byte <= 'f') {
      digit = (uint32_t)(byte - 'a') + 10u;
    } else {
      break;
    }
    if (digits == 6u || value > 0x10FFFFu / 16u ||
        (value * 16u) + digit > 0x10FFFFu) {
      return 0;
    }
    value = value * 16u + digit;
    digits++;
    cursor->current++;
  }
  if (digits == 0u || (value >= 0xD800u && value <= 0xDFFFu)) return 0;
  *codepoint = value;
  return 1;
}

static int line_has_more(line_cursor_t* cursor) {
  skip_space_and_comment(cursor);
  return cursor->current < cursor->end;
}

static int verify_line(const char* line, size_t length, size_t line_number,
                       size_t* checked_boundaries) {
  line_cursor_t cursor = {line, line + length};
  my_line_break_state_t state;
  uint32_t* codepoints = NULL;
  unsigned char* expected = NULL;
  size_t capacity = length / 2u + 2u;
  size_t count = 0u;
  size_t i;
  int marker;
  int complete = 0;

  if (length > (SIZE_MAX - 2u) / 2u ||
      capacity > SIZE_MAX / sizeof(*codepoints)) {
    fprintf(stderr, "LineBreakTest:%zu: line is too large\n", line_number);
    goto fail;
  }
  codepoints = (uint32_t*)malloc(capacity * sizeof(*codepoints));
  expected = (unsigned char*)malloc(capacity * sizeof(*expected));
  if (codepoints == NULL || expected == NULL) goto fail;
  skip_space_and_comment(&cursor);
  if (cursor.current == cursor.end) {
    free(codepoints);
    free(expected);
    return 1;
  }
  if (!parse_marker(&cursor, &marker) || !line_has_more(&cursor)) {
    fprintf(stderr, "%s:%zu: expected an opening marker and code point\n",
            "LineBreakTest", line_number);
    goto fail;
  }
  if (!parse_codepoint(&cursor, &codepoints[count++])) {
    fprintf(stderr, "LineBreakTest:%zu: invalid first code point\n",
            line_number);
    goto fail;
  }
  while (!complete) {
    if (!parse_marker(&cursor, &marker)) {
      fprintf(stderr, "LineBreakTest:%zu: missing boundary marker\n",
              line_number);
      goto fail;
    }
    if (!line_has_more(&cursor)) {
      if (marker != 1) {
        fprintf(stderr, "LineBreakTest:%zu: final boundary must allow a break\n",
                line_number);
        goto fail;
      }
      complete = 1;
      break;
    }
    if (count == capacity || !parse_codepoint(&cursor, &codepoints[count])) {
      fprintf(stderr, "LineBreakTest:%zu: invalid code point\n", line_number);
      goto fail;
    }
    expected[count++] = (unsigned char)marker;
  }
  my_line_break_state_init(&state);
  (void)my_line_break_state_feed(&state, codepoints[0]);
  for (i = 1u; i < count; i++) {
    int actual = my_line_break_state_feed_with_lookahead(
        &state, codepoints[i], i + 1u < count ? codepoints[i + 1u] : 0u,
        i + 1u < count) ? 1 : 0;
    if (actual != expected[i]) {
      fprintf(stderr,
              "LineBreakTest:%zu: boundary %zu mismatch before U+%04X "
              "(expected %s, got %s)\n",
              line_number, i, codepoints[i], expected[i] ? "break" : "no-break",
              actual ? "break" : "no-break");
      goto fail;
    }
  }
  if (checked_boundaries != NULL) *checked_boundaries += count;
  free(codepoints);
  free(expected);
  return 1;

fail:
  free(codepoints);
  free(expected);
  return 0;
}

int main(int argc, char** argv) {
  FILE* input;
  char line[MYUI_LINE_BREAK_LINE_BYTES];
  size_t line_number = 0u;
  size_t checked_boundaries = 0u;
  int ok = 1;

  if (argc != 2) {
    fprintf(stderr, "usage: %s LineBreakTest.txt\n", argv[0]);
    return 2;
  }
  input = fopen(argv[1], "rb");
  if (input == NULL) {
    fprintf(stderr, "cannot open '%s'\n", argv[1]);
    return 2;
  }
  while (fgets(line, sizeof(line), input) != NULL) {
    size_t length;
    int complete;
    line_number++;
    length = strlen(line);
    complete = length > 0u && line[length - 1u] == '\n';
    if (!complete && !feof(input)) {
      int byte;
      while ((byte = fgetc(input)) != EOF && byte != '\n') {
      }
      fprintf(stderr, "LineBreakTest:%zu: line exceeds %u bytes\n",
              line_number, (unsigned)MYUI_LINE_BREAK_LINE_BYTES - 1u);
      ok = 0;
      break;
    }
    if (!verify_line(line, length, line_number, &checked_boundaries)) {
      ok = 0;
      break;
    }
  }
  if (ferror(input)) {
    fprintf(stderr, "cannot read '%s'\n", argv[1]);
    ok = 0;
  }
  fclose(input);
  if (ok) {
    printf("verified %zu line-break boundaries\n", checked_boundaries);
    return 0;
  }
  return 1;
}
