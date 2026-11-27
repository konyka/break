/* Verify MyUI CSS conditional media against a golden corpus.
 *
 * Line format (blank lines and '#' comments are ignored):
 *   ctx NAME key=value...   defines a media context
 *       keys: w h (px), screen dark motion (0|1),
 *             caps=a,b,...  (hover pointer-coarse pointer-fine
 *                            any-pointer-coarse any-pointer-fine
 *                            srgb p3 rec2020 hdr | none)
 *             known=a,b,... (hover pointer any-pointer gamut hdr
 *                            scheme motion | all | legacy)
 *   case CTX EXPECT QUERY   EXPECT is match, nomatch or reject; QUERY is
 *                           the @media prelude, evaluated in strict mode.
 * Every case parses "@media QUERY { button { color: red; } }" and checks
 * the rule count (match = 1, nomatch = 0) or that parsing fails (reject). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myui/my_css.h"

#define CSS_MEDIA_LINE_BYTES 1024u
#define CSS_MEDIA_MAX_CONTEXTS 32u
#define CSS_MEDIA_NAME_BYTES 32u

typedef struct named_context_t {
  char name[CSS_MEDIA_NAME_BYTES];
  my_css_media_context_ex_t media;
} named_context_t;

typedef struct flag_name_t {
  const char* name;
  uint32_t bit;
} flag_name_t;

static const flag_name_t kCaps[] = {
    {"hover", MY_CSS_MEDIA_CAP_HOVER},
    {"pointer-coarse", MY_CSS_MEDIA_CAP_POINTER_COARSE},
    {"pointer-fine", MY_CSS_MEDIA_CAP_POINTER_FINE},
    {"any-pointer-coarse", MY_CSS_MEDIA_CAP_ANY_POINTER_COARSE},
    {"any-pointer-fine", MY_CSS_MEDIA_CAP_ANY_POINTER_FINE},
    {"srgb", MY_CSS_MEDIA_CAP_COLOR_SRGB},
    {"p3", MY_CSS_MEDIA_CAP_COLOR_P3},
    {"rec2020", MY_CSS_MEDIA_CAP_COLOR_REC2020},
    {"hdr", MY_CSS_MEDIA_CAP_HDR},
};

static const flag_name_t kKnown[] = {
    {"hover", MY_CSS_MEDIA_KNOWN_HOVER},
    {"pointer", MY_CSS_MEDIA_KNOWN_POINTER},
    {"any-pointer", MY_CSS_MEDIA_KNOWN_ANY_POINTER},
    {"gamut", MY_CSS_MEDIA_KNOWN_COLOR_GAMUT},
    {"hdr", MY_CSS_MEDIA_KNOWN_HDR},
    {"scheme", MY_CSS_MEDIA_KNOWN_COLOR_SCHEME},
    {"motion", MY_CSS_MEDIA_KNOWN_REDUCED_MOTION},
    {"all", MY_CSS_MEDIA_KNOWN_ALL},
    {"legacy", 0u},
};

/* Portable strtok_r replacement: splits *cursor in place at any byte of
 * seps, skipping leading separators. Returns NULL when no token remains. */
static char* next_token(char** cursor, const char* seps) {
  char* start = *cursor;
  char* end;
  start += strspn(start, seps);
  if (*start == '\0') {
    *cursor = start;
    return NULL;
  }
  end = start + strcspn(start, seps);
  if (*end != '\0') {
    *end = '\0';
    *cursor = end + 1;
  } else {
    *cursor = end;
  }
  return start;
}

static int parse_flags(const char* text, const flag_name_t* names,
                       size_t count, uint32_t* out) {
  char buf[CSS_MEDIA_LINE_BYTES];
  char* cursor = buf;
  char* item;
  *out = 0u;
  if (strcmp(text, "none") == 0) return 1;
  snprintf(buf, sizeof(buf), "%s", text);
  while ((item = next_token(&cursor, ",")) != NULL) {
    size_t i;
    int found = 0;
    for (i = 0u; i < count; i++) {
      if (strcmp(item, names[i].name) == 0) {
        *out |= names[i].bit;
        found = 1;
        break;
      }
    }
    if (!found) return 0;
  }
  return 1;
}

static int parse_u32(const char* text, uint32_t max, uint32_t* out) {
  char* end = NULL;
  unsigned long value;
  if (text[0] < '0' || text[0] > '9') return 0;
  value = strtoul(text, &end, 10);
  if (end == text || *end != '\0' || value > max) return 0;
  *out = (uint32_t)value;
  return 1;
}

static int parse_context(char* rest, named_context_t* out) {
  char* cursor = rest;
  char* token = next_token(&cursor, " \t");
  int has_known = 0;
  memset(out, 0, sizeof(*out));
  if (token == NULL || strlen(token) >= sizeof(out->name)) return 0;
  snprintf(out->name, sizeof(out->name), "%s", token);
  while ((token = next_token(&cursor, " \t")) != NULL) {
    char* eq = strchr(token, '=');
    uint32_t value = 0u;
    if (eq == NULL) return 0;
    *eq++ = '\0';
    if (strcmp(token, "w") == 0 || strcmp(token, "h") == 0) {
      if (!parse_u32(eq, 1000000u, &value)) return 0;
      if (token[0] == 'w') {
        out->media.base.viewport_width_px = value;
      } else {
        out->media.base.viewport_height_px = value;
      }
    } else if (strcmp(token, "screen") == 0 || strcmp(token, "dark") == 0 ||
               strcmp(token, "motion") == 0) {
      if (!parse_u32(eq, 1u, &value)) return 0;
      if (token[0] == 's') {
        out->media.base.screen = value != 0u;
      } else if (token[0] == 'd') {
        out->media.base.prefers_dark = value != 0u;
      } else {
        out->media.base.prefers_reduced_motion = value != 0u;
      }
    } else if (strcmp(token, "caps") == 0) {
      if (!parse_flags(eq, kCaps, sizeof(kCaps) / sizeof(kCaps[0]),
                       &out->media.base.capabilities)) {
        return 0;
      }
    } else if (strcmp(token, "known") == 0) {
      if (!parse_flags(eq, kKnown, sizeof(kKnown) / sizeof(kKnown[0]),
                       &out->media.known)) {
        return 0;
      }
      has_known = 1;
    } else {
      return 0;
    }
  }
  return has_known;
}

static const named_context_t* find_context(const named_context_t* contexts,
                                           size_t count, const char* name) {
  size_t i;
  for (i = 0u; i < count; i++) {
    if (strcmp(contexts[i].name, name) == 0) return &contexts[i];
  }
  return NULL;
}

/* Returns 1 when the case holds, 0 on mismatch, -1 on a malformed line. */
static int run_case(char* rest, const named_context_t* contexts,
                    size_t context_count, size_t line_number) {
  char css[CSS_MEDIA_LINE_BYTES + 64u];
  char* cursor = rest;
  char* ctx_name = next_token(&cursor, " \t");
  char* expect = next_token(&cursor, " \t");
  char* query = cursor;
  const named_context_t* ctx;
  my_css_error_t error;
  my_css_sheet_t* sheet;
  const char* actual;
  if (ctx_name == NULL || expect == NULL || query == NULL) return -1;
  while (*query == ' ' || *query == '\t') query++;
  if (*query == '\0') return -1;
  if (strcmp(expect, "match") != 0 && strcmp(expect, "nomatch") != 0 &&
      strcmp(expect, "reject") != 0) {
    return -1;
  }
  ctx = find_context(contexts, context_count, ctx_name);
  if (ctx == NULL) return -1;
  snprintf(css, sizeof(css), "@media %s { button { color: red; } }", query);
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex2(NULL, css, strlen(css),
                                 MY_CSS_PARSE_STRICT_AT_RULES, &ctx->media,
                                 &error);
  if (sheet == NULL) {
    actual = "reject";
  } else {
    actual = my_css_rule_count(sheet) == 1u ? "match" : "nomatch";
    my_css_sheet_destroy(sheet);
  }
  if (strcmp(actual, expect) != 0) {
    fprintf(stderr, "css_media:%zu: [%s] %s: expected %s, got %s\n",
            line_number, ctx_name, query, expect, actual);
    return 0;
  }
  return 1;
}

int main(int argc, char** argv) {
  static named_context_t contexts[CSS_MEDIA_MAX_CONTEXTS];
  size_t context_count = 0u;
  FILE* input;
  char line[CSS_MEDIA_LINE_BYTES];
  size_t line_number = 0u;
  size_t cases = 0u;
  int ok = 1;

  if (argc != 2) {
    fprintf(stderr, "usage: %s corpus.txt\n", argv[0]);
    return 2;
  }
  input = fopen(argv[1], "rb");
  if (input == NULL) {
    fprintf(stderr, "cannot open '%s'\n", argv[1]);
    return 2;
  }
  while (ok && fgets(line, sizeof(line), input) != NULL) {
    size_t length = strlen(line);
    char* text = line;
    line_number++;
    if (length > 0u && line[length - 1u] != '\n' && !feof(input)) {
      fprintf(stderr, "css_media:%zu: line exceeds %u bytes\n", line_number,
              (unsigned)CSS_MEDIA_LINE_BYTES - 1u);
      ok = 0;
      break;
    }
    while (length > 0u &&
           (line[length - 1u] == '\n' || line[length - 1u] == '\r')) {
      line[--length] = '\0';
    }
    while (*text == ' ' || *text == '\t') text++;
    if (*text == '\0' || *text == '#') continue;
    if (strncmp(text, "ctx ", 4u) == 0) {
      if (context_count >= CSS_MEDIA_MAX_CONTEXTS ||
          !parse_context(text + 4, &contexts[context_count]) ||
          find_context(contexts, context_count,
                       contexts[context_count].name) != NULL) {
        fprintf(stderr, "css_media:%zu: malformed context\n", line_number);
        ok = 0;
        break;
      }
      context_count++;
    } else if (strncmp(text, "case ", 5u) == 0) {
      int result = run_case(text + 5, contexts, context_count, line_number);
      if (result < 0) {
        fprintf(stderr, "css_media:%zu: malformed case\n", line_number);
      }
      if (result != 1) {
        ok = 0;
        break;
      }
      cases++;
    } else {
      fprintf(stderr, "css_media:%zu: unknown directive\n", line_number);
      ok = 0;
      break;
    }
  }
  if (ferror(input)) {
    fprintf(stderr, "cannot read '%s'\n", argv[1]);
    ok = 0;
  }
  fclose(input);
  if (ok && cases == 0u) {
    fprintf(stderr, "css_media: corpus has no cases\n");
    ok = 0;
  }
  if (ok) {
    printf("verified %zu css media cases across %zu contexts\n", cases,
           context_count);
    return 0;
  }
  return 1;
}
