/* Verify a bounded, versioned SA dictionary golden corpus. */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myc/myconf/my_conf.h"
#include "myr/my_line_break.h"

#define SA_CORPUS_MAX_BYTES (64u * 1024u)
#define SA_CORPUS_MAX_CODEPOINTS MY_LINE_BREAK_MAX_DICTIONARY_CODEPOINTS
#define SA_CORPUS_MAX_CASES 256u
#define SA_CORPUS_MAX_CODEPOINT_TEXT 4096u

typedef struct sa_case_t {
  uint32_t codepoints[SA_CORPUS_MAX_CODEPOINTS];
  bool expected[SA_CORPUS_MAX_CODEPOINTS];
  size_t count;
} sa_case_t;

typedef struct sa_context_t {
  size_t calls;
  const char* expected_locale;
} sa_context_t;

static char* trim(char* text) {
  char* end;
  while (*text == ' ' || *text == '\t') text++;
  end = text + strlen(text);
  while (end > text && (end[-1] == ' ' || end[-1] == '\t')) end--;
  *end = '\0';
  return text;
}

static int parse_u32(const char* text, uint32_t* value) {
  char* end = NULL;
  unsigned long parsed;
  if (text == NULL || value == NULL || text[0] == '\0' || text[0] == '-') {
    return 0;
  }
  errno = 0;
  parsed = strtoul(text, &end, 16);
  if (errno != 0 || end == text || *end != '\0' || parsed > 0x10FFFFu ||
      (parsed >= 0xD800u && parsed <= 0xDFFFu)) {
    return 0;
  }
  *value = (uint32_t)parsed;
  return 1;
}

static int parse_boundaries(const char* text, bool* values, size_t count) {
  size_t i;
  const char* p = text;
  if (text == NULL || values == NULL || count == 0u) return 0;
  for (i = 0u; i < count; ++i) {
    if (p[0] != '0' && p[0] != '1') return 0;
    values[i] = p[0] == '1';
    p++;
    if (i + 1u < count) {
      if (*p != ',') return 0;
      p++;
    }
  }
  return *p == '\0';
}

static my_ret_t corpus_dictionary(
    void* context, const my_line_break_dictionary_profile_t* profile,
    const uint32_t* codepoints, size_t count, bool* allow_before) {
  sa_context_t* state = (sa_context_t*)context;
  size_t i;
  if (state == NULL || profile == NULL || profile->version != 1u ||
      profile->locale == NULL || state->expected_locale == NULL ||
      strcmp(profile->locale, state->expected_locale) != 0 ||
      codepoints == NULL || allow_before == NULL || count < 2u) {
    return MY_RET_INVALID_PARAMS;
  }
  state->calls++;
  /* The fixture rule is independent of the corpus: U+0E02 starts a word. */
  for (i = 1u; i < count; ++i) {
    allow_before[i] = codepoints[i] == 0x0E02u;
  }
  return MY_RET_OK;
}

static int verify_case(const sa_case_t* test, const char* locale) {
  my_line_break_dictionary_profile_t profile = {1u, locale};
  my_line_break_profile_options_t options;
  bool actual[SA_CORPUS_MAX_CODEPOINTS];
  sa_context_t context = {0u, locale};
  size_t i;
  my_ret_t result;
  if (test == NULL || locale == NULL || test->count < 2u ||
      !my_line_break_dictionary_profile_valid(&profile)) {
    return 0;
  }
  options.dictionary = corpus_dictionary;
  options.context = &context;
  options.max_codepoints = SA_CORPUS_MAX_CODEPOINTS;
  for (i = 0u; i < test->count; ++i) {
    if (my_line_break_class(test->codepoints[i]) != MY_LB_SA) return 0;
    actual[i] = false;
  }
  result = my_line_break_apply_dictionary_profile(
      test->codepoints, test->count, actual, &options, &profile);
  if (result != MY_RET_OK || context.calls != 1u) return 0;
  for (i = 1u; i < test->count; ++i) {
    if (actual[i] != test->expected[i - 1u]) return 0;
  }
  return true;
}

static int parse_codepoints(const char* text, sa_case_t* test) {
  char copy[SA_CORPUS_MAX_CODEPOINT_TEXT];
  char* token;
  size_t length;
  if (text == NULL || test == NULL || strlen(text) >= sizeof(copy)) return 0;
  length = strlen(text);
  if (length == 0u || text[0] == ',' || text[length - 1u] == ',' ||
      strstr(text, ",,") != NULL) {
    return 0;
  }
  strcpy(copy, text);
  test->count = 0u;
  token = strtok(copy, ",");
  while (token != NULL && test->count < SA_CORPUS_MAX_CODEPOINTS) {
    token = trim(token);
    if (!parse_u32(token, &test->codepoints[test->count++])) return 0;
    token = strtok(NULL, ",");
  }
  return token == NULL && test->count >= 2u;
}

static int object_keys_valid(const my_conf_node_t* object,
                             const char* const* keys, size_t key_count) {
  size_t i;
  if (object == NULL || my_conf_type(object) != MY_CONF_OBJECT) return 0;
  for (i = 0u; i < my_conf_child_count(object); ++i) {
    const char* key = my_conf_key(my_conf_child(object, i));
    size_t k;
    int known = 0;
    size_t matches = 0u;
    for (k = 0u; k < key_count; ++k) {
      if (key != NULL && strcmp(key, keys[k]) == 0) {
        known = 1;
        matches++;
        break;
      }
    }
    if (!known || matches != 1u) return 0;
  }
  return 1;
}

static int verify_file(const char* path) {
  FILE* file;
  char data[SA_CORPUS_MAX_BYTES + 1u];
  size_t length;
  my_conf_node_t* root;
  my_conf_node_t* cases;
  const char* locale;
  my_conf_error_t error;
  const char* const root_keys[] = {"version", "locale", "cases"};
  const char* const case_keys[] = {"codepoints", "expected"};
  size_t i;
  size_t root_key_count;
  if (path == NULL) return 2;
  file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "cannot open %s\n", path);
    return 2;
  }
  length = fread(data, 1u, sizeof(data), file);
  if (ferror(file) || length == sizeof(data)) {
    fprintf(stderr, "%s: corpus exceeds resource budget\n", path);
    fclose(file);
    return 1;
  }
  fclose(file);
  if (memchr(data, '\0', length) != NULL) {
    fprintf(stderr, "%s: embedded NUL is not allowed\n", path);
    return 1;
  }
  data[length] = '\0';
  root = my_conf_parse_yaml(NULL, data, length, &error);
  root_key_count = sizeof(root_keys) / sizeof(root_keys[0]);
  if (root == NULL || my_conf_child_count(root) != root_key_count ||
      !object_keys_valid(root, root_keys, root_key_count) ||
      my_conf_get_int64(root, "version", -1) != 1) {
    my_conf_destroy(root);
    fprintf(stderr, "%s: invalid corpus header\n", path);
    return 1;
  }
  locale = my_conf_get_str(root, "locale", NULL);
  cases = my_conf_get(root, "cases");
  if (locale == NULL || !my_line_break_dictionary_profile_valid(
                            &(my_line_break_dictionary_profile_t){1u, locale}) ||
      cases == NULL || my_conf_type(cases) != MY_CONF_ARRAY ||
      my_conf_child_count(cases) == 0u ||
      my_conf_child_count(cases) > SA_CORPUS_MAX_CASES) {
    my_conf_destroy(root);
    fprintf(stderr, "%s: invalid corpus metadata\n", path);
    return 1;
  }
  for (i = 0u; i < my_conf_child_count(cases); ++i) {
    my_conf_node_t* item = my_conf_child(cases, i);
    const char* codepoints = my_conf_get_str(item, "codepoints", NULL);
    const char* expected = my_conf_get_str(item, "expected", NULL);
    sa_case_t test = {{0}, {0}, 0u};
    if (my_conf_child_count(item) != sizeof(case_keys) / sizeof(case_keys[0]) ||
        !object_keys_valid(item, case_keys,
                           sizeof(case_keys) / sizeof(case_keys[0])) ||
        codepoints == NULL || expected == NULL ||
        !parse_codepoints(codepoints, &test) ||
        !parse_boundaries(expected, test.expected, test.count - 1u) ||
        !verify_case(&test, locale)) {
      my_conf_destroy(root);
      fprintf(stderr, "%s: invalid SA corpus case %zu\n", path, i);
      return 1;
    }
  }
  my_conf_destroy(root);
  return 0;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s corpus.yaml\n", argv[0]);
    return 2;
  }
  return verify_file(argv[1]);
}
