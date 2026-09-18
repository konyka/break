#include "test_framework.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifndef TEST_SOURCE_ROOT
#error "TEST_SOURCE_ROOT must point to the engine source tree"
#endif

static bool read_shader(const char *name, char *buffer, size_t capacity) {
  char path[1024];
  FILE *file;
  size_t length;
  if (snprintf(path, sizeof(path), "%s/shaders/%s", TEST_SOURCE_ROOT, name) >=
      (int)sizeof(path)) return false;
  file = fopen(path, "rb");
  if (file == NULL) return false;
  length = fread(buffer, 1, capacity - 1, file);
  fclose(file);
  buffer[length] = '\0';
  return length > 0;
}

static void strip_glsl_comments(char *source) {
  char *cursor = source;
  while (*cursor != '\0') {
    if (cursor[0] == '/' && cursor[1] == '/') {
      while (*cursor != '\0' && *cursor != '\n') *cursor++ = ' ';
    } else if (cursor[0] == '/' && cursor[1] == '*') {
      *cursor++ = ' '; *cursor++ = ' ';
      while (*cursor != '\0' && !(cursor[0] == '*' && cursor[1] == '/')) *cursor++ = ' ';
      if (*cursor != '\0') { *cursor++ = ' '; *cursor++ = ' '; }
    } else {
      cursor++;
    }
  }
}

TEST(font_shaders_use_raw_coverage_sampling) {
  const char *shaders[] = {"font.frag", "font_vk.frag"};
  size_t i;
  for (i = 0; i < sizeof(shaders) / sizeof(shaders[0]); i++) {
    char source[4096];
    ASSERT_TRUE(read_shader(shaders[i], source, sizeof(source)));
    strip_glsl_comments(source);
    ASSERT_NOT_NULL(strstr(source, "texture(u_atlas, vUV).a"));
    ASSERT_NOT_NULL(strstr(source, "vColor.a * cov"));
    ASSERT_TRUE(strstr(source, "smoothstep(") == NULL);
    ASSERT_TRUE(strstr(source, "fwidth(") == NULL);
  }
}

TEST_MAIN_BEGIN()
  RUN_TEST(font_shaders_use_raw_coverage_sampling);
TEST_MAIN_END()
