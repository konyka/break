#include "test_framework.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>

#include "core/platform_thread.h"
#include "myr/my_font.h"
#include "myr/my_font_ft.h"

static void release_failed_provider_glyph(void* lease);

TEST(font_public_api_defaults_missing_metric_slots)
{
  my_font_t font = {0};
  my_font_vtable_t vtable = {0};
  my_glyph_t glyph = {0};

  ASSERT_EQ(my_font_descent(NULL, 16), 0);
  font.vtable = &vtable;
  ASSERT_EQ(my_font_descent(&font, 16), 0);
  ASSERT_EQ(my_font_get_glyph(&font, 'A', 16, &glyph), MY_RET_NOT_SUPPORTED);
  ASSERT_TRUE(glyph.bitmap == NULL);
  ASSERT_TRUE(glyph.lease == NULL);
  ASSERT_TRUE(glyph.release_lease == NULL);
  glyph.bitmap = (const uint8_t *)1;
  glyph.lease = (void *)1;
  glyph.release_lease = release_failed_provider_glyph;
  ASSERT_EQ(my_font_get_glyph_id(&font, 1, 16, &glyph), MY_RET_NOT_SUPPORTED);
  ASSERT_TRUE(glyph.bitmap == NULL);
  ASSERT_TRUE(glyph.lease == NULL);
  ASSERT_TRUE(glyph.release_lease == NULL);
}

#ifdef MYUI_FONT_FREETYPE
typedef struct {
  const char *path;
  int face_index;
} CjkFontCandidate;

static const CjkFontCandidate *find_cjk_font(void) {
  static const CjkFontCandidate candidates[] = {
#if defined(_WIN32)
      {"C:/Windows/Fonts/msyh.ttc", 0},
#elif defined(__APPLE__)
      {"/System/Library/Fonts/PingFang.ttc", 0},
#else
      {"/usr/share/fonts/google-noto-sans-cjk-vf-fonts/NotoSansCJK-VF.ttc", 2},
      {"/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc", 2},
#endif
      {NULL, 0},
  };
  size_t i;

  for (i = 0; candidates[i].path != NULL; i++) {
    FILE *file = fopen(candidates[i].path, "rb");
    if (file != NULL) {
      fclose(file);
      return &candidates[i];
    }
  }
  return NULL;
}
#endif

typedef struct shape_allocator_state_t {
  size_t calls;
  size_t fail_at;
  size_t live;
} shape_allocator_state_t;

static unsigned int s_failed_glyph_release_calls;

static void release_failed_provider_glyph(void* lease) {
  if (lease != NULL) s_failed_glyph_release_calls++;
}

static my_ret_t glyph_provider_writes_then_fails(
    my_font_t* font, uint32_t codepoint, int32_t size, my_glyph_t* glyph) {
  (void)font;
  (void)codepoint;
  (void)size;
  glyph->bitmap = (const uint8_t*)1;
  glyph->lease = (void*)1;
  glyph->release_lease = release_failed_provider_glyph;
  return MY_RET_FAIL;
}

static my_ret_t glyph_id_provider_writes_then_fails(
    my_font_t* font, uint32_t glyph_id, int32_t size, my_glyph_t* glyph) {
  (void)font;
  (void)glyph_id;
  (void)size;
  glyph->bitmap = (const uint8_t*)1;
  glyph->lease = (void*)1;
  glyph->release_lease = release_failed_provider_glyph;
  return MY_RET_FAIL;
}

static const my_font_vtable_t s_failed_glyph_provider_vtable = {
    .get_glyph = glyph_provider_writes_then_fails,
    .get_glyph_id = glyph_id_provider_writes_then_fails};

TEST(font_glyph_wrappers_rollback_failed_provider_output)
{
  my_font_t font = {&s_failed_glyph_provider_vtable};
  my_glyph_t glyph = {0};

  s_failed_glyph_release_calls = 0u;
  ASSERT_EQ(my_font_get_glyph(&font, 'A', 16, &glyph), MY_RET_FAIL);
  ASSERT_EQ(s_failed_glyph_release_calls, 1u);
  ASSERT_TRUE(glyph.bitmap == NULL);
  ASSERT_TRUE(glyph.lease == NULL);
  ASSERT_TRUE(glyph.release_lease == NULL);

  ASSERT_EQ(my_font_get_glyph_id(&font, 1u, 16, &glyph), MY_RET_FAIL);
  ASSERT_EQ(s_failed_glyph_release_calls, 2u);
  ASSERT_TRUE(glyph.bitmap == NULL);
  ASSERT_TRUE(glyph.lease == NULL);
  ASSERT_TRUE(glyph.release_lease == NULL);
}

static bool shape_allocator_should_fail(shape_allocator_state_t* state) {
  state->calls++;
  return state->fail_at != 0 && state->calls == state->fail_at;
}

static void* shape_alloc(void* context, size_t size) {
  shape_allocator_state_t* state = (shape_allocator_state_t*)context;
  void* memory;
  if (shape_allocator_should_fail(state)) return NULL;
  memory = malloc(size);
  if (memory != NULL) state->live++;
  return memory;
}

static void* shape_calloc(void* context, size_t count, size_t size) {
  shape_allocator_state_t* state = (shape_allocator_state_t*)context;
  void* memory;
  if (shape_allocator_should_fail(state)) return NULL;
  memory = calloc(count, size);
  if (memory != NULL) state->live++;
  return memory;
}

static void* shape_realloc(void* context, void* old_memory, size_t size) {
  shape_allocator_state_t* state = (shape_allocator_state_t*)context;
  void* memory;
  if (shape_allocator_should_fail(state)) return NULL;
  memory = realloc(old_memory, size);
  if (memory != NULL && old_memory == NULL) state->live++;
  return memory;
}

static void shape_free(void* context, void* memory) {
  shape_allocator_state_t* state = (shape_allocator_state_t*)context;
  if (memory != NULL) {
    free(memory);
    state->live--;
  }
}

static my_ret_t shape_alloc_then_fail(my_font_t* font, const char* text,
                                      int32_t size, bool rtl,
                                      const my_allocator_t* allocator,
                                      my_font_shape_result_t* result) {
  (void)font;
  (void)text;
  (void)size;
  (void)rtl;
  result->allocator = allocator;
  result->glyphs = (my_font_shape_glyph_t*)my_mem_alloc(
      allocator, sizeof(*result->glyphs));
  if (result->glyphs == NULL) return MY_RET_OOM;
  result->allocator = NULL;
  result->count = 1;
  return MY_RET_FAIL;
}

static const my_font_vtable_t s_shape_failure_vtable = {
    .shape = shape_alloc_then_fail};

typedef struct shape_params_font_t {
  my_font_t base;
  my_font_shape_params_t received;
  char received_features[MY_FONT_SHAPE_MAX_FEATURE_BYTES + 1u];
  bool called;
} shape_params_font_t;

static my_ret_t shape_params_probe(
    my_font_t* font, const char* text, int32_t size,
    const my_font_shape_params_t* params, const my_allocator_t* allocator,
    my_font_shape_result_t* result) {
  shape_params_font_t* probe = (shape_params_font_t*)font;
  if (text == NULL || size <= 0 || params == NULL || result == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  probe->received = *params;
  if (params->features != NULL) {
    strncpy(probe->received_features, params->features,
            sizeof(probe->received_features) - 1u);
    probe->received_features[sizeof(probe->received_features) - 1u] = '\0';
    probe->received.features = probe->received_features;
  }
  probe->called = true;
  result->allocator = allocator;
  return MY_RET_OK;
}

static const my_font_vtable_t s_shape_params_vtable = {
    .shape_ex = shape_params_probe};

static my_ret_t shape_oversized_result_probe(
    my_font_t* font, const char* text, int32_t size,
    const my_font_shape_params_t* params, const my_allocator_t* allocator,
    my_font_shape_result_t* result) {
  (void)font;
  (void)text;
  (void)size;
  (void)params;
  if (result == NULL) return MY_RET_INVALID_PARAMS;
  result->allocator = allocator;
  result->glyphs = (my_font_shape_glyph_t*)my_mem_alloc(
      allocator, sizeof(*result->glyphs));
  if (result->glyphs == NULL) return MY_RET_OOM;
  result->count = MY_FONT_SHAPE_MAX_GLYPHS + 1u;
  return MY_RET_OK;
}

static const my_font_vtable_t s_oversized_result_vtable = {
    .shape_ex = shape_oversized_result_probe};

typedef struct shape_support_font_t {
  my_font_t base;
  my_font_shape_support_t support;
  size_t query_calls;
  size_t shape_ex_calls;
  char queried_features[MY_FONT_SHAPE_MAX_FEATURE_BYTES + 1u];
  uint32_t last_script;
  const char* last_language;
} shape_support_font_t;

static my_ret_t shape_support_probe(
    my_font_t* font, const my_font_shape_params_t* params,
    my_font_shape_support_t* support) {
  shape_support_font_t* probe = (shape_support_font_t*)font;
  if (params == NULL || support == NULL) return MY_RET_INVALID_PARAMS;
  probe->query_calls++;
  if (params->features != NULL) {
    strncpy(probe->queried_features, params->features,
            sizeof(probe->queried_features) - 1u);
    probe->queried_features[sizeof(probe->queried_features) - 1u] = '\0';
  }
  *support = probe->support;
  return MY_RET_OK;
}

static my_ret_t shape_support_shape_ex(
    my_font_t* font, const char* text, int32_t size,
    const my_font_shape_params_t* params, const my_allocator_t* allocator,
    my_font_shape_result_t* result) {
  shape_support_font_t* probe = (shape_support_font_t*)font;
  if (text == NULL || size <= 0 || params == NULL || result == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  probe->shape_ex_calls++;
  probe->last_script = params->script;
  probe->last_language = params->language;
  if (params->language != NULL || params->script != 0u) {
    return MY_RET_NOT_SUPPORTED;
  }
  result->allocator = allocator;
  return MY_RET_OK;
}

static my_ret_t shape_support_shape(
    my_font_t* font, const char* text, int32_t size, bool rtl,
    const my_allocator_t* allocator, my_font_shape_result_t* result) {
  (void)font;
  (void)rtl;
  if (text == NULL || size <= 0 || result == NULL) return MY_RET_INVALID_PARAMS;
  result->allocator = allocator;
  return MY_RET_OK;
}

static const my_font_vtable_t s_shape_support_vtable = {
    .shape = shape_support_shape,
    .shape_ex = shape_support_shape_ex,
    .shape_support = shape_support_probe};

#if defined(MYUI_FONT_FREETYPE) || defined(MYUI_FONT_STB)
static bool glyph_has_coverage(const my_glyph_t *glyph) {
  size_t i;
  size_t count;

  if (glyph->bitmap == NULL || glyph->w <= 0 || glyph->h <= 0) {
    return false;
  }
  count = (size_t)glyph->w * (size_t)glyph->h;
  for (i = 0; i < count; i++) {
    if (glyph->bitmap[i] != 0) {
      return true;
    }
  }
  return false;
}
#endif

#ifdef MYUI_FONT_STB
static bool write_u32_be(FILE *file, uint32_t value) {
  unsigned char bytes[4];
  bytes[0] = (unsigned char)(value >> 24);
  bytes[1] = (unsigned char)(value >> 16);
  bytes[2] = (unsigned char)(value >> 8);
  bytes[3] = (unsigned char)value;
  return fwrite(bytes, 1, sizeof(bytes), file) == sizeof(bytes);
}

static uint32_t read_u32_be(const unsigned char *bytes) {
  return ((uint32_t)bytes[0] << 24) | ((uint32_t)bytes[1] << 16) |
         ((uint32_t)bytes[2] << 8) | (uint32_t)bytes[3];
}

static uint16_t read_u16_be(const unsigned char *bytes) {
  return (uint16_t)(((uint16_t)bytes[0] << 8) | bytes[1]);
}

static void write_u16_be(unsigned char *bytes, uint16_t value) {
  bytes[0] = (unsigned char)(value >> 8);
  bytes[1] = (unsigned char)value;
}

static void write_u32_be_bytes(unsigned char *bytes, uint32_t value) {
  bytes[0] = (unsigned char)(value >> 24);
  bytes[1] = (unsigned char)(value >> 16);
  bytes[2] = (unsigned char)(value >> 8);
  bytes[3] = (unsigned char)value;
}

static void add_font_base_offset(unsigned char *font, size_t size,
                                 uint32_t base) {
  uint16_t table_count = (uint16_t)(((uint16_t)font[4] << 8) | font[5]);
  uint16_t table_index;
  for (table_index = 0u; table_index < table_count; table_index++) {
    size_t record = 12u + (size_t)table_index * 16u;
    uint32_t offset;
    if (record > size || size - record < 16u) return;
    offset = read_u32_be(font + record + 8u);
    if (offset > UINT32_MAX - base) return;
    font[record + 8u] = (unsigned char)((offset + base) >> 24);
    font[record + 9u] = (unsigned char)((offset + base) >> 16);
    font[record + 10u] = (unsigned char)((offset + base) >> 8);
    font[record + 11u] = (unsigned char)(offset + base);
  }
}

static bool create_stb_ttc_fixture(const char *source_path,
                                   const char *fixture_path) {
  FILE *source = NULL;
  FILE *fixture = NULL;
  unsigned char *data = NULL;
  unsigned char *first = NULL;
  unsigned char *second = NULL;
  long source_size;
  size_t size;
  size_t padded_size;
  size_t second_offset;
  unsigned char padding[3] = {0, 0, 0};
  bool success = false;

  source = fopen(source_path, "rb");
  if (source == NULL || fseek(source, 0, SEEK_END) != 0) goto cleanup;
  source_size = ftell(source);
  if (source_size <= 0 || fseek(source, 0, SEEK_SET) != 0) goto cleanup;
  size = (size_t)source_size;
  if (size > UINT32_MAX - 20u || size > SIZE_MAX - 3u) goto cleanup;
  padded_size = (size + 3u) & ~(size_t)3u;
  second_offset = 20u + padded_size;
  if (second_offset > UINT32_MAX || size > SIZE_MAX / 2u) goto cleanup;
  data = (unsigned char *)malloc(size);
  first = (unsigned char *)malloc(size);
  second = (unsigned char *)malloc(size);
  if (data == NULL || first == NULL || second == NULL ||
      fread(data, 1, size, source) != size)
    goto cleanup;
  memcpy(first, data, size);
  memcpy(second, data, size);
  add_font_base_offset(first, size, 20u);
  add_font_base_offset(second, size, (uint32_t)second_offset);

  fixture = fopen(fixture_path, "wb");
  if (fixture == NULL || fwrite("ttcf", 1, 4, fixture) != 4u ||
      !write_u32_be(fixture, 0x00010000u) || !write_u32_be(fixture, 2u) ||
      !write_u32_be(fixture, 20u) ||
      !write_u32_be(fixture, (uint32_t)second_offset) ||
      fwrite(first, 1, size, fixture) != size ||
      fwrite(padding, 1, padded_size - size, fixture) != padded_size - size ||
      fwrite(second, 1, size, fixture) != size) {
    goto cleanup;
  }
  success = fflush(fixture) == 0;

cleanup:
  if (fixture != NULL) fclose(fixture);
  if (source != NULL) fclose(source);
  free(data);
  free(first);
  free(second);
  if (!success) remove(fixture_path);
  return success;
}

static bool create_stb_bad_table_fixture(const char *source_path,
                                         const char *fixture_path) {
  FILE *source = NULL;
  FILE *fixture = NULL;
  unsigned char *data = NULL;
  long source_size;
  size_t size;
  uint16_t table_count;
  uint16_t table_index;
  bool success = false;

  source = fopen(source_path, "rb");
  if (source == NULL || fseek(source, 0, SEEK_END) != 0) goto cleanup;
  source_size = ftell(source);
  if (source_size < 12 || fseek(source, 0, SEEK_SET) != 0) goto cleanup;
  size = (size_t)source_size;
  data = (unsigned char *)malloc(size);
  if (data == NULL || fread(data, 1, size, source) != size) goto cleanup;
  table_count = (uint16_t)(((uint16_t)data[4] << 8) | data[5]);
  if ((size_t)table_count > (size - 12u) / 16u) goto cleanup;
  for (table_index = 0u; table_index < table_count; table_index++) {
    size_t record = 12u + (size_t)table_index * 16u;
    if (memcmp(data + record, "cmap", 4u) == 0) {
      data[record + 8u] = 0xffu;
      data[record + 9u] = 0xffu;
      data[record + 10u] = 0xffu;
      data[record + 11u] = 0xf0u;
      break;
    }
  }
  if (table_index == table_count) goto cleanup;
  fixture = fopen(fixture_path, "wb");
  if (fixture == NULL || fwrite(data, 1, size, fixture) != size) goto cleanup;
  success = fflush(fixture) == 0;

cleanup:
  if (fixture != NULL) fclose(fixture);
  if (source != NULL) fclose(source);
  free(data);
  if (!success) remove(fixture_path);
  return success;
}

static bool create_stb_short_table_fixture(const char *source_path,
                                           const char *fixture_path,
                                           const char tag[4],
                                           uint32_t table_size) {
  FILE *source = NULL;
  FILE *fixture = NULL;
  unsigned char *data = NULL;
  long source_size;
  size_t size;
  uint16_t table_count;
  uint16_t table_index;
  bool success = false;

  source = fopen(source_path, "rb");
  if (source == NULL || fseek(source, 0, SEEK_END) != 0) goto cleanup;
  source_size = ftell(source);
  if (source_size < 12 || fseek(source, 0, SEEK_SET) != 0) goto cleanup;
  size = (size_t)source_size;
  data = (unsigned char *)malloc(size);
  if (data == NULL || fread(data, 1, size, source) != size) goto cleanup;
  table_count = (uint16_t)(((uint16_t)data[4] << 8) | data[5]);
  if ((size_t)table_count > (size - 12u) / 16u) goto cleanup;
  for (table_index = 0u; table_index < table_count; table_index++) {
    size_t record = 12u + (size_t)table_index * 16u;
    if (memcmp(data + record, tag, 4u) == 0) {
      data[record + 12u] = (unsigned char)(table_size >> 24);
      data[record + 13u] = (unsigned char)(table_size >> 16);
      data[record + 14u] = (unsigned char)(table_size >> 8);
      data[record + 15u] = (unsigned char)table_size;
      break;
    }
  }
  if (table_index == table_count) goto cleanup;
  fixture = fopen(fixture_path, "wb");
  if (fixture == NULL || fwrite(data, 1, size, fixture) != size) goto cleanup;
  success = fflush(fixture) == 0;

cleanup:
  if (fixture != NULL) fclose(fixture);
  if (source != NULL) fclose(source);
  free(data);
  if (!success) remove(fixture_path);
  return success;
}

static bool create_stb_bad_cmap_range_fixture(const char *source_path,
                                              const char *fixture_path) {
  FILE *source = NULL;
  FILE *fixture = NULL;
  unsigned char *data = NULL;
  long source_size;
  size_t size;
  uint16_t table_count;
  uint16_t table_index;
  bool success = false;

  source = fopen(source_path, "rb");
  if (source == NULL || fseek(source, 0, SEEK_END) != 0) goto cleanup;
  source_size = ftell(source);
  if (source_size < 12 || fseek(source, 0, SEEK_SET) != 0) goto cleanup;
  size = (size_t)source_size;
  data = (unsigned char *)malloc(size);
  if (data == NULL || fread(data, 1, size, source) != size) goto cleanup;
  table_count = read_u16_be(data + 4u);
  if ((size_t)table_count > (size - 12u) / 16u) goto cleanup;
  for (table_index = 0u; table_index < table_count; table_index++) {
    size_t record = 12u + (size_t)table_index * 16u;
    size_t cmap_offset;
    size_t cmap_length;
    uint16_t record_count;
    uint16_t record_index;
    if (memcmp(data + record, "cmap", 4u) != 0) continue;
    cmap_offset = (size_t)read_u32_be(data + record + 8u);
    cmap_length = (size_t)read_u32_be(data + record + 12u);
    if (cmap_offset > size || cmap_length > size - cmap_offset ||
        cmap_length < 4u) goto cleanup;
    record_count = read_u16_be(data + cmap_offset + 2u);
    if ((size_t)record_count > (cmap_length - 4u) / 8u) goto cleanup;
    for (record_index = 0u; record_index < record_count; record_index++) {
      size_t encoding = cmap_offset + 4u + (size_t)record_index * 8u;
      size_t subtable = cmap_offset +
                        (size_t)read_u32_be(data + encoding + 4u);
      uint16_t format;
      uint16_t segment_count;
      size_t id_range_offset;
      if ((uint64_t)read_u32_be(data + encoding + 4u) >=
          (uint64_t)cmap_length || subtable > size || size - subtable < 8u)
        continue;
      format = read_u16_be(data + subtable);
      if (format != 4u) continue;
      segment_count = (uint16_t)(read_u16_be(data + subtable + 6u) / 2u);
      if (segment_count == 0u || (size_t)segment_count >
          (cmap_length - (subtable - cmap_offset) - 16u) / 8u)
        continue;
      id_range_offset = subtable + 14u + (size_t)segment_count * 6u + 2u;
      if (id_range_offset > size || size - id_range_offset < 2u) continue;
      write_u16_be(data + id_range_offset, 0xffffu);
      fixture = fopen(fixture_path, "wb");
      if (fixture == NULL || fwrite(data, 1, size, fixture) != size) goto cleanup;
      success = fflush(fixture) == 0;
      goto cleanup;
    }
  }

cleanup:
  if (fixture != NULL) fclose(fixture);
  if (source != NULL) fclose(source);
  free(data);
  if (!success) remove(fixture_path);
  return success;
}

static bool create_stb_short_glyph_fixture(const char *source_path,
                                           const char *fixture_path) {
  FILE *source = NULL;
  FILE *fixture = NULL;
  unsigned char *data = NULL;
  long source_size;
  size_t size;
  uint16_t table_count;
  uint16_t table_index;
  size_t head_offset = 0u;
  size_t loca_offset = 0u;
  size_t loca_length = 0u;
  bool success = false;

  source = fopen(source_path, "rb");
  if (source == NULL || fseek(source, 0, SEEK_END) != 0) goto cleanup;
  source_size = ftell(source);
  if (source_size < 12 || fseek(source, 0, SEEK_SET) != 0) goto cleanup;
  size = (size_t)source_size;
  data = (unsigned char *)malloc(size);
  if (data == NULL || fread(data, 1, size, source) != size) goto cleanup;
  table_count = read_u16_be(data + 4u);
  if ((size_t)table_count > (size - 12u) / 16u) goto cleanup;
  for (table_index = 0u; table_index < table_count; table_index++) {
    size_t record = 12u + (size_t)table_index * 16u;
    size_t offset = (size_t)read_u32_be(data + record + 8u);
    size_t length = (size_t)read_u32_be(data + record + 12u);
    if (memcmp(data + record, "head", 4u) == 0) head_offset = offset;
    if (memcmp(data + record, "loca", 4u) == 0) {
      loca_offset = offset;
      loca_length = length;
    }
  }
  if (head_offset > size || size - head_offset < 52u ||
      loca_offset > size || loca_length < 4u || loca_length > size - loca_offset)
    goto cleanup;
  if (read_u16_be(data + head_offset + 50u) == 0u) {
    write_u16_be(data + loca_offset + 2u, 1u);
  } else if (read_u16_be(data + head_offset + 50u) == 1u) {
    data[loca_offset + 4u] = 0u;
    data[loca_offset + 5u] = 0u;
    data[loca_offset + 6u] = 0u;
    data[loca_offset + 7u] = 1u;
  } else {
    goto cleanup;
  }
  fixture = fopen(fixture_path, "wb");
  if (fixture == NULL || fwrite(data, 1, size, fixture) != size) goto cleanup;
  success = fflush(fixture) == 0;

cleanup:
  if (fixture != NULL) fclose(fixture);
  if (source != NULL) fclose(source);
  free(data);
  if (!success) remove(fixture_path);
  return success;
}

static bool create_stb_bad_instruction_fixture(const char *source_path,
                                               const char *fixture_path) {
  FILE *source = NULL;
  FILE *fixture = NULL;
  unsigned char *data = NULL;
  long source_size;
  size_t size;
  size_t head_offset = 0u, loca_offset = 0u, loca_length = 0u;
  size_t glyf_offset = 0u, glyf_length = 0u;
  uint16_t table_count, table_index, glyph_count = 0u;
  bool success = false;

  source = fopen(source_path, "rb");
  if (source == NULL || fseek(source, 0, SEEK_END) != 0) goto cleanup;
  source_size = ftell(source);
  if (source_size < 12 || fseek(source, 0, SEEK_SET) != 0) goto cleanup;
  size = (size_t)source_size;
  data = (unsigned char *)malloc(size);
  if (data == NULL || fread(data, 1, size, source) != size) goto cleanup;
  table_count = read_u16_be(data + 4u);
  if ((size_t)table_count > (size - 12u) / 16u) goto cleanup;
  for (table_index = 0u; table_index < table_count; table_index++) {
    size_t record = 12u + (size_t)table_index * 16u;
    size_t offset = (size_t)read_u32_be(data + record + 8u);
    size_t length = (size_t)read_u32_be(data + record + 12u);
    if (memcmp(data + record, "head", 4u) == 0) head_offset = offset;
    if (memcmp(data + record, "loca", 4u) == 0) {
      loca_offset = offset;
      loca_length = length;
    }
    if (memcmp(data + record, "glyf", 4u) == 0) {
      glyf_offset = offset;
      glyf_length = length;
    }
    if (memcmp(data + record, "maxp", 4u) == 0 && length >= 6u)
      glyph_count = read_u16_be(data + offset + 4u);
  }
  if (head_offset > size || size - head_offset < 52u ||
      loca_offset > size || loca_length > size - loca_offset ||
      glyf_offset > size || glyf_length > size - glyf_offset)
    goto cleanup;
  {
    uint16_t format = read_u16_be(data + head_offset + 50u);
    size_t entry_size = format == 0u ? 2u : format == 1u ? 4u : 0u;
    uint16_t glyph;
    if (entry_size == 0u || (size_t)(glyph_count + 1u) * entry_size > loca_length)
      goto cleanup;
    for (glyph = 0u; glyph < glyph_count; glyph++) {
      uint32_t start = entry_size == 2u
                           ? (uint32_t)read_u16_be(data + loca_offset +
                                                    (size_t)glyph * 2u) * 2u
                           : read_u32_be(data + loca_offset + (size_t)glyph * 4u);
      uint32_t end = entry_size == 2u
                         ? (uint32_t)read_u16_be(data + loca_offset +
                                                  (size_t)(glyph + 1u) * 2u) * 2u
                         : read_u32_be(data + loca_offset +
                                        (size_t)(glyph + 1u) * 4u);
      uint16_t contours;
      size_t instruction;
      if (end <= start || end > glyf_length || end - start < 14u) continue;
      contours = read_u16_be(data + glyf_offset + start);
      if (contours == 0u || contours >= 0x8000u) continue;
      instruction = (size_t)start + 10u + (size_t)contours * 2u;
      if (instruction > end || end - instruction < 2u) continue;
      write_u16_be(data + glyf_offset + instruction, 0xffffu);
      fixture = fopen(fixture_path, "wb");
      if (fixture == NULL || fwrite(data, 1, size, fixture) != size) goto cleanup;
      success = fflush(fixture) == 0;
      goto cleanup;
    }
  }

cleanup:
  if (fixture != NULL) fclose(fixture);
  if (source != NULL) fclose(source);
  free(data);
  if (!success) remove(fixture_path);
  return success;
}

static bool create_stb_short_coordinate_fixture(const char *source_path,
                                                 const char *fixture_path) {
  FILE *source = NULL;
  FILE *fixture = NULL;
  unsigned char *data = NULL;
  long source_size;
  size_t size;
  size_t head_offset = 0u, loca_offset = 0u, glyf_offset = 0u;
  size_t loca_length = 0u, glyf_length = 0u;
  uint16_t table_count, table_index, glyph_count = 0u;
  bool success = false;

  source = fopen(source_path, "rb");
  if (source == NULL || fseek(source, 0, SEEK_END) != 0) goto cleanup;
  source_size = ftell(source);
  if (source_size < 12 || fseek(source, 0, SEEK_SET) != 0) goto cleanup;
  size = (size_t)source_size;
  data = (unsigned char *)malloc(size);
  if (data == NULL || fread(data, 1, size, source) != size) goto cleanup;
  table_count = read_u16_be(data + 4u);
  if ((size_t)table_count > (size - 12u) / 16u) goto cleanup;
  for (table_index = 0u; table_index < table_count; table_index++) {
    size_t record = 12u + (size_t)table_index * 16u;
    size_t offset = (size_t)read_u32_be(data + record + 8u);
    size_t length = (size_t)read_u32_be(data + record + 12u);
    if (memcmp(data + record, "head", 4u) == 0) head_offset = offset;
    if (memcmp(data + record, "loca", 4u) == 0) {
      loca_offset = offset;
      loca_length = length;
    }
    if (memcmp(data + record, "glyf", 4u) == 0) {
      glyf_offset = offset;
      glyf_length = length;
    }
    if (memcmp(data + record, "maxp", 4u) == 0 && length >= 6u)
      glyph_count = read_u16_be(data + offset + 4u);
  }
  if (head_offset > size || size - head_offset < 52u ||
      loca_offset > size || loca_length > size - loca_offset ||
      glyf_offset > size || glyf_length > size - glyf_offset)
    goto cleanup;
  {
    uint16_t format = read_u16_be(data + head_offset + 50u);
    size_t entry_size = format == 0u ? 2u : format == 1u ? 4u : 0u;
    uint16_t glyph;
    if (entry_size == 0u || (size_t)(glyph_count + 1u) * entry_size > loca_length)
      goto cleanup;
    for (glyph = 0u; glyph < glyph_count; glyph++) {
      uint32_t start = entry_size == 2u
                           ? (uint32_t)read_u16_be(data + loca_offset +
                                                    (size_t)glyph * 2u) * 2u
                           : read_u32_be(data + loca_offset + (size_t)glyph * 4u);
      uint32_t end = entry_size == 2u
                         ? (uint32_t)read_u16_be(data + loca_offset +
                                                  (size_t)(glyph + 1u) * 2u) * 2u
                         : read_u32_be(data + loca_offset +
                                        (size_t)(glyph + 1u) * 4u);
      uint16_t contours;
      size_t instruction, points;
      if (end <= start || end > glyf_length || end - start < 14u) continue;
      contours = read_u16_be(data + glyf_offset + start);
      if (contours == 0u || contours >= 0x8000u ||
          (size_t)contours > ((size_t)(end - start) - 12u) / 2u)
        continue;
      instruction = (size_t)start + 10u + (size_t)contours * 2u;
      if (instruction + 2u > end) continue;
      points = instruction + 2u + read_u16_be(data + glyf_offset + instruction);
      if (points >= end) continue;
      data[glyf_offset + points] = 0u;
      if (entry_size == 2u)
        write_u16_be(data + loca_offset + (size_t)(glyph + 1u) * 2u,
                     (uint16_t)((points + 1u) / 2u));
      else {
        data[loca_offset + (size_t)(glyph + 1u) * 4u] = (unsigned char)((points + 1u) >> 24);
        data[loca_offset + (size_t)(glyph + 1u) * 4u + 1u] = (unsigned char)((points + 1u) >> 16);
        data[loca_offset + (size_t)(glyph + 1u) * 4u + 2u] = (unsigned char)((points + 1u) >> 8);
        data[loca_offset + (size_t)(glyph + 1u) * 4u + 3u] = (unsigned char)(points + 1u);
      }
      fixture = fopen(fixture_path, "wb");
      if (fixture == NULL || fwrite(data, 1, size, fixture) != size) goto cleanup;
      success = fflush(fixture) == 0;
      goto cleanup;
    }
  }

cleanup:
  if (fixture != NULL) fclose(fixture);
  if (source != NULL) fclose(source);
  free(data);
  if (!success) remove(fixture_path);
  return success;
}

static bool create_stb_bad_component_fixture(const char *source_path,
                                             const char *fixture_path) {
  FILE *source = NULL;
  FILE *fixture = NULL;
  unsigned char *data = NULL;
  long source_size;
  size_t size;
  uint16_t table_count;
  uint16_t table_index;
  size_t head_offset = 0u, loca_offset = 0u, glyf_offset = 0u;
  size_t loca_length = 0u, glyf_length = 0u;
  uint16_t glyph_count = 0u;
  uint16_t glyph_index;
  bool success = false;

  source = fopen(source_path, "rb");
  if (source == NULL || fseek(source, 0, SEEK_END) != 0) goto cleanup;
  source_size = ftell(source);
  if (source_size < 12 || fseek(source, 0, SEEK_SET) != 0) goto cleanup;
  size = (size_t)source_size;
  data = (unsigned char *)malloc(size);
  if (data == NULL || fread(data, 1, size, source) != size) goto cleanup;
  table_count = read_u16_be(data + 4u);
  if ((size_t)table_count > (size - 12u) / 16u) goto cleanup;
  for (table_index = 0u; table_index < table_count; table_index++) {
    size_t record = 12u + (size_t)table_index * 16u;
    size_t offset = (size_t)read_u32_be(data + record + 8u);
    size_t length = (size_t)read_u32_be(data + record + 12u);
    if (memcmp(data + record, "head", 4u) == 0) head_offset = offset;
    if (memcmp(data + record, "loca", 4u) == 0) {
      loca_offset = offset;
      loca_length = length;
    }
    if (memcmp(data + record, "glyf", 4u) == 0) {
      glyf_offset = offset;
      glyf_length = length;
    }
    if (memcmp(data + record, "maxp", 4u) == 0 && length >= 6u) {
      glyph_count = read_u16_be(data + offset + 4u);
    }
  }
  if (head_offset > size || size - head_offset < 52u ||
      loca_offset > size || loca_length > size - loca_offset ||
      glyf_offset > size || glyf_length > size - glyf_offset ||
      glyph_count < 2u)
    goto cleanup;
  for (glyph_index = 0u; glyph_index + 1u < glyph_count; glyph_index++) {
    uint16_t format = read_u16_be(data + head_offset + 50u);
    size_t entry_size = format == 0u ? 2u : format == 1u ? 4u : 0u;
    uint32_t start, end;
    if (entry_size == 0u || (size_t)(glyph_index + 2u) * entry_size > loca_length)
      goto cleanup;
    start = entry_size == 2u
                ? (uint32_t)read_u16_be(data + loca_offset +
                                         (size_t)glyph_index * 2u) * 2u
                : read_u32_be(data + loca_offset + (size_t)glyph_index * 4u);
    end = entry_size == 2u
              ? (uint32_t)read_u16_be(data + loca_offset +
                                       (size_t)(glyph_index + 1u) * 2u) * 2u
              : read_u32_be(data + loca_offset +
                             (size_t)(glyph_index + 1u) * 4u);
    if (end <= start || (uint64_t)end > (uint64_t)glyf_length ||
        end - start < 14u)
      continue;
    if (read_u16_be(data + glyf_offset + start) >= 0x8000u) {
      write_u16_be(data + glyf_offset + start + 12u, 0xffffu);
      fixture = fopen(fixture_path, "wb");
      if (fixture == NULL || fwrite(data, 1, size, fixture) != size) goto cleanup;
      success = fflush(fixture) == 0;
      goto cleanup;
    }
  }

cleanup:
  if (fixture != NULL) fclose(fixture);
  if (source != NULL) fclose(source);
  free(data);
  if (!success) remove(fixture_path);
  return success;
}

static bool create_stb_component_cycle_fixture(const char *source_path,
                                               const char *fixture_path) {
  FILE *source = NULL;
  FILE *fixture = NULL;
  unsigned char *data = NULL;
  long source_size;
  size_t size;
  uint16_t table_count;
  uint16_t table_index;
  size_t head_offset = 0u, loca_offset = 0u, glyf_offset = 0u;
  size_t loca_length = 0u, glyf_length = 0u;
  uint16_t glyph_count = 0u;
  uint16_t first = 0u, second = 0u;
  uint16_t found = 0u;
  bool success = false;

  source = fopen(source_path, "rb");
  if (source == NULL || fseek(source, 0, SEEK_END) != 0) goto cleanup;
  source_size = ftell(source);
  if (source_size < 12 || fseek(source, 0, SEEK_SET) != 0) goto cleanup;
  size = (size_t)source_size;
  data = (unsigned char *)malloc(size);
  if (data == NULL || fread(data, 1, size, source) != size) goto cleanup;
  table_count = read_u16_be(data + 4u);
  if ((size_t)table_count > (size - 12u) / 16u) goto cleanup;
  for (table_index = 0u; table_index < table_count; table_index++) {
    size_t record = 12u + (size_t)table_index * 16u;
    size_t offset = (size_t)read_u32_be(data + record + 8u);
    size_t length = (size_t)read_u32_be(data + record + 12u);
    if (memcmp(data + record, "head", 4u) == 0) head_offset = offset;
    if (memcmp(data + record, "loca", 4u) == 0) {
      loca_offset = offset;
      loca_length = length;
    }
    if (memcmp(data + record, "glyf", 4u) == 0) {
      glyf_offset = offset;
      glyf_length = length;
    }
    if (memcmp(data + record, "maxp", 4u) == 0 && length >= 6u)
      glyph_count = read_u16_be(data + offset + 4u);
  }
  if (head_offset > size || size - head_offset < 52u ||
      loca_offset > size || loca_length > size - loca_offset ||
      glyf_offset > size || glyf_length > size - glyf_offset)
    goto cleanup;
  {
    uint16_t format = read_u16_be(data + head_offset + 50u);
    size_t entry_size = format == 0u ? 2u : format == 1u ? 4u : 0u;
    if (entry_size == 0u || (size_t)(glyph_count + 1u) * entry_size > loca_length)
      goto cleanup;
    for (uint16_t glyph = 0u; glyph < glyph_count; glyph++) {
      uint32_t start = entry_size == 2u
                           ? (uint32_t)read_u16_be(data + loca_offset +
                                                    (size_t)glyph * 2u) * 2u
                           : read_u32_be(data + loca_offset +
                                          (size_t)glyph * 4u);
      uint32_t end = entry_size == 2u
                         ? (uint32_t)read_u16_be(data + loca_offset +
                                                  (size_t)(glyph + 1u) * 2u) * 2u
                         : read_u32_be(data + loca_offset +
                                        (size_t)(glyph + 1u) * 4u);
      if (end > start && end - start >= 14u &&
          end <= glyf_length && read_u16_be(data + glyf_offset + start) >= 0x8000u) {
        if (found == 0u) first = glyph;
        else if (found == 1u) second = glyph;
        found++;
        if (found == 2u) break;
      }
    }
    if (found < 2u) goto cleanup;
    {
      uint32_t start_first = entry_size == 2u
                                 ? (uint32_t)read_u16_be(
                                       data + loca_offset + (size_t)first * 2u) * 2u
                                 : read_u32_be(data + loca_offset + (size_t)first * 4u);
      uint32_t start_second = entry_size == 2u
                                  ? (uint32_t)read_u16_be(
                                        data + loca_offset + (size_t)second * 2u) * 2u
                                  : read_u32_be(data + loca_offset +
                                                (size_t)second * 4u);
      write_u16_be(data + glyf_offset + start_first + 12u, second);
      write_u16_be(data + glyf_offset + start_second + 12u, first);
    }
  }
  fixture = fopen(fixture_path, "wb");
  if (fixture == NULL || fwrite(data, 1, size, fixture) != size) goto cleanup;
  success = fflush(fixture) == 0;

cleanup:
  if (fixture != NULL) fclose(fixture);
  if (source != NULL) fclose(source);
  free(data);
  if (!success) remove(fixture_path);
  return success;
}

static bool create_stb_deep_component_fixture(const char *source_path,
                                               const char *fixture_path) {
  enum { minimum_chain_length = 128 };
  FILE *source = NULL;
  FILE *fixture = NULL;
  unsigned char *data = NULL;
  uint16_t *chain = NULL;
  long source_size;
  size_t size;
  uint16_t table_count;
  uint16_t table_index;
  size_t head_offset = 0u, loca_offset = 0u, glyf_offset = 0u;
  size_t loca_length = 0u, glyf_length = 0u;
  uint16_t glyph_count = 0u;
  uint16_t terminal = 0u;
  bool terminal_set = false;
  size_t chain_count = 0u;
  bool success = false;

  source = fopen(source_path, "rb");
  if (source == NULL || fseek(source, 0, SEEK_END) != 0) goto cleanup;
  source_size = ftell(source);
  if (source_size < 12 || fseek(source, 0, SEEK_SET) != 0) goto cleanup;
  size = (size_t)source_size;
  data = (unsigned char *)malloc(size);
  if (data == NULL || fread(data, 1, size, source) != size) goto cleanup;
  table_count = read_u16_be(data + 4u);
  if ((size_t)table_count > (size - 12u) / 16u) goto cleanup;
  for (table_index = 0u; table_index < table_count; table_index++) {
    size_t record = 12u + (size_t)table_index * 16u;
    size_t offset = (size_t)read_u32_be(data + record + 8u);
    size_t length = (size_t)read_u32_be(data + record + 12u);
    if (offset > size || length > size - offset) goto cleanup;
    if (memcmp(data + record, "head", 4u) == 0) head_offset = offset;
    if (memcmp(data + record, "loca", 4u) == 0) {
      loca_offset = offset;
      loca_length = length;
    }
    if (memcmp(data + record, "glyf", 4u) == 0) {
      glyf_offset = offset;
      glyf_length = length;
    }
    if (memcmp(data + record, "maxp", 4u) == 0 && length >= 6u)
      glyph_count = read_u16_be(data + offset + 4u);
  }
  if (head_offset > size || size - head_offset < 52u || glyph_count == 0u ||
      loca_offset > size || loca_length > size - loca_offset ||
      glyf_offset > size || glyf_length > size - glyf_offset)
    goto cleanup;
  chain = (uint16_t *)malloc((size_t)glyph_count * sizeof(*chain));
  if (chain == NULL) goto cleanup;
  {
    uint16_t format = read_u16_be(data + head_offset + 50u);
    size_t entry_size = format == 0u ? 2u : format == 1u ? 4u : 0u;
    uint16_t glyph;
    if (entry_size == 0u ||
        (size_t)(glyph_count + 1u) * entry_size > loca_length)
      goto cleanup;
    for (glyph = 0u; glyph < glyph_count; glyph++) {
      uint32_t start = entry_size == 2u
                           ? (uint32_t)read_u16_be(data + loca_offset +
                                                    (size_t)glyph * 2u) * 2u
                           : read_u32_be(data + loca_offset +
                                          (size_t)glyph * 4u);
      uint32_t end = entry_size == 2u
                         ? (uint32_t)read_u16_be(data + loca_offset +
                                                  (size_t)(glyph + 1u) * 2u) * 2u
                         : read_u32_be(data + loca_offset +
                                        (size_t)(glyph + 1u) * 4u);
      if (end < start || end > glyf_length) goto cleanup;
      if (end > start && end - start < 26u) {
        write_u16_be(data + glyf_offset + start, 0u);
      }
      if (!terminal_set && end > start && end - start < 26u) {
        terminal = glyph;
        terminal_set = true;
      }
      if (end - start >= 26u) {
        chain[chain_count++] = glyph;
      }
    }
    if (!terminal_set || chain_count < minimum_chain_length) goto cleanup;
    for (glyph = 0u; glyph < chain_count; glyph++) {
      uint32_t start = entry_size == 2u
                           ? (uint32_t)read_u16_be(
                                 data + loca_offset + (size_t)chain[glyph] * 2u) *
                                 2u
                           : read_u32_be(data + loca_offset +
                                          (size_t)chain[glyph] * 4u);
      uint16_t next = glyph + 1u < chain_count ? chain[glyph + 1u] : terminal;
      unsigned char *record = data + glyf_offset + start;
      write_u16_be(record, 0xffffu);
      write_u16_be(record + 10u, 0x0023u);
      write_u16_be(record + 12u, next);
      write_u16_be(record + 14u, 0u);
      write_u16_be(record + 16u, 0u);
      write_u16_be(record + 18u, 0x0002u);
      write_u16_be(record + 20u, terminal);
      write_u16_be(record + 22u, 0u);
      write_u16_be(record + 24u, 0u);
    }
  }
  fixture = fopen(fixture_path, "wb");
  if (fixture == NULL || fwrite(data, 1, size, fixture) != size) goto cleanup;
  success = fflush(fixture) == 0;

cleanup:
  if (fixture != NULL) fclose(fixture);
  if (source != NULL) fclose(source);
  free(data);
  free(chain);
  if (!success) remove(fixture_path);
  return success;
}

static bool create_stb_bad_compound_instruction_fixture(
    const char *source_path, const char *fixture_path) {
  FILE *source = NULL;
  FILE *fixture = NULL;
  unsigned char *data = NULL;
  long source_size;
  size_t size;
  size_t head_offset = 0u, loca_offset = 0u, glyf_offset = 0u;
  size_t loca_length = 0u, glyf_length = 0u;
  uint16_t table_count;
  uint16_t table_index;
  uint16_t glyph_count = 0u;
  bool success = false;

  source = fopen(source_path, "rb");
  if (source == NULL || fseek(source, 0, SEEK_END) != 0) goto cleanup;
  source_size = ftell(source);
  if (source_size < 12 || fseek(source, 0, SEEK_SET) != 0) goto cleanup;
  size = (size_t)source_size;
  data = (unsigned char *)malloc(size);
  if (data == NULL || fread(data, 1, size, source) != size) goto cleanup;
  table_count = read_u16_be(data + 4u);
  if ((size_t)table_count > (size - 12u) / 16u) goto cleanup;
  for (table_index = 0u; table_index < table_count; table_index++) {
    size_t record = 12u + (size_t)table_index * 16u;
    size_t offset = (size_t)read_u32_be(data + record + 8u);
    size_t length = (size_t)read_u32_be(data + record + 12u);
    if (offset > size || length > size - offset) goto cleanup;
    if (memcmp(data + record, "head", 4u) == 0) head_offset = offset;
    if (memcmp(data + record, "loca", 4u) == 0) {
      loca_offset = offset;
      loca_length = length;
    }
    if (memcmp(data + record, "glyf", 4u) == 0) {
      glyf_offset = offset;
      glyf_length = length;
    }
    if (memcmp(data + record, "maxp", 4u) == 0 && length >= 6u)
      glyph_count = read_u16_be(data + offset + 4u);
  }
  if (head_offset > size || size - head_offset < 52u || glyph_count == 0u ||
      loca_offset > size || loca_length > size - loca_offset ||
      glyf_offset > size || glyf_length > size - glyf_offset)
    goto cleanup;
  {
    uint16_t format = read_u16_be(data + head_offset + 50u);
    size_t entry_size = format == 0u ? 2u : format == 1u ? 4u : 0u;
    uint16_t glyph;
    if (entry_size == 0u ||
        (size_t)(glyph_count + 1u) * entry_size > loca_length)
      goto cleanup;
    for (glyph = 0u; glyph < glyph_count; glyph++) {
      uint32_t start = entry_size == 2u
                           ? (uint32_t)read_u16_be(data + loca_offset +
                                                    (size_t)glyph * 2u) * 2u
                           : read_u32_be(data + loca_offset +
                                          (size_t)glyph * 4u);
      uint32_t end = entry_size == 2u
                         ? (uint32_t)read_u16_be(data + loca_offset +
                                                  (size_t)(glyph + 1u) * 2u) * 2u
                         : read_u32_be(data + loca_offset +
                                        (size_t)(glyph + 1u) * 4u);
      size_t cursor = 10u;
      bool more = true;
      if (end <= start || end > glyf_length || end - start < 14u ||
          read_u16_be(data + glyf_offset + start) < 0x8000u)
        continue;
      while (more) {
        uint16_t flags;
        size_t component_size;
        if (cursor > end - start || end - start - cursor < 4u) break;
        flags = read_u16_be(data + glyf_offset + start + cursor);
        component_size = 4u + ((flags & 1u) != 0u ? 4u : 2u);
        if ((flags & 8u) != 0u)
          component_size += 2u;
        else if ((flags & 64u) != 0u)
          component_size += 4u;
        else if ((flags & 128u) != 0u)
          component_size += 8u;
        if (component_size > end - start - cursor) break;
        if ((flags & 32u) == 0u) {
          write_u16_be(data + glyf_offset + start + cursor, flags | 0x0100u);
          cursor += component_size;
          if (cursor + 2u <= end - start)
            write_u16_be(data + glyf_offset + start + cursor, 0xffffu);
          fixture = fopen(fixture_path, "wb");
          if (fixture == NULL || fwrite(data, 1, size, fixture) != size)
            goto cleanup;
          success = fflush(fixture) == 0;
          goto cleanup;
        }
        cursor += component_size;
        more = true;
      }
    }
  }

cleanup:
  if (fixture != NULL) fclose(fixture);
  if (source != NULL) fclose(source);
  free(data);
  if (!success) remove(fixture_path);
  return success;
}

static bool create_stb_truncated_cff_fixture(const char *source_path,
                                             const char *fixture_path) {
  FILE *source = NULL;
  FILE *fixture = NULL;
  unsigned char *data = NULL;
  long source_size;
  size_t size;
  uint16_t table_count;
  uint16_t table_index;
  bool success = false;

  source = fopen(source_path, "rb");
  if (source == NULL || fseek(source, 0, SEEK_END) != 0) goto cleanup;
  source_size = ftell(source);
  if (source_size < 12 || fseek(source, 0, SEEK_SET) != 0) goto cleanup;
  size = (size_t)source_size;
  data = (unsigned char *)malloc(size);
  if (data == NULL || fread(data, 1, size, source) != size) goto cleanup;
  table_count = read_u16_be(data + 4u);
  if ((size_t)table_count > (size - 12u) / 16u) goto cleanup;
  for (table_index = 0u; table_index < table_count; table_index++) {
    size_t record = 12u + (size_t)table_index * 16u;
    if (memcmp(data + record, "CFF ", 4u) == 0) {
      write_u32_be_bytes(data + record + 12u, 4u);
      fixture = fopen(fixture_path, "wb");
      if (fixture == NULL || fwrite(data, 1, size, fixture) != size)
        goto cleanup;
      success = fflush(fixture) == 0;
      goto cleanup;
    }
  }

cleanup:
  if (fixture != NULL) fclose(fixture);
  if (source != NULL) fclose(source);
  free(data);
  if (!success) remove(fixture_path);
  return success;
}

static bool create_stb_cid_cff_fixture(const char *source_path,
                                       const char *fixture_path, int mode) {
  FILE *source = NULL;
  FILE *fixture = NULL;
  unsigned char *data = NULL;
  long source_size;
  size_t size;
  size_t maxp_offset = 0u;
  size_t hhea_offset = 0u;
  uint16_t table_count;
  uint16_t table_index;
  bool found_cff = false;
  bool found_maxp = false;
  bool found_hhea = false;
  bool success = false;
  static const unsigned char valid_cff[] = {
      1u, 0u, 4u, 4u,
      0u, 1u, 1u, 1u, 2u, 'x',
      0u, 1u, 1u, 1u, 9u,
      178u, 17u, 166u, 12u, 36u, 176u, 12u, 37u,
      0u, 0u,
      0u, 0u,
      0u, 1u, 1u, 1u, 4u, 141u, 174u, 18u,
      0u, 0u,
      0u, 0u,
      0u, 1u, 1u, 1u, 2u, 14u};
  unsigned char cff[sizeof(valid_cff)];

  if (mode < 0 || mode > 10) return false;
  memcpy(cff, valid_cff, sizeof(cff));
  if (mode == 1) {
    cff[33u] = 239u;
  } else if (mode == 2) {
    cff[32u] = 159u;
  } else if (mode == 3) {
    cff[33u] = 174u;
    cff[35u] = 149u;
    cff[36u] = 19u;
  } else if (mode == 4) {
    cff[sizeof(cff) - 1u] = 28u;
  } else if (mode == 5) {
    cff[sizeof(cff) - 1u] = 2u;
  } else if (mode == 6) {
    cff[15u] = 255u;
  } else if (mode == 7) {
    cff[sizeof(cff) - 1u] = 4u;
  } else if (mode == 8) {
    cff[sizeof(cff) - 1u] = 5u;
  } else if (mode == 9) {
    cff[sizeof(cff) - 1u] = 12u;
  } else if (mode == 10) {
    cff[17u] = 12u;
    cff[18u] = 32u;
    cff[19u] = 12u;
    cff[20u] = 32u;
    cff[21u] = 12u;
    cff[22u] = 32u;
  }
  source = fopen(source_path, "rb");
  if (source == NULL || fseek(source, 0, SEEK_END) != 0) goto cleanup;
  source_size = ftell(source);
  if (source_size < 12 || fseek(source, 0, SEEK_SET) != 0) goto cleanup;
  size = (size_t)source_size;
  data = (unsigned char *)malloc(size);
  if (data == NULL || fread(data, 1, size, source) != size) goto cleanup;
  table_count = read_u16_be(data + 4u);
  if ((size_t)table_count > (size - 12u) / 16u) goto cleanup;
  for (table_index = 0u; table_index < table_count; table_index++) {
    size_t record = 12u + (size_t)table_index * 16u;
    size_t offset = (size_t)read_u32_be(data + record + 8u);
    size_t length = (size_t)read_u32_be(data + record + 12u);
    if (offset > size || length > size - offset) goto cleanup;
    if (memcmp(data + record, "CFF ", 4u) == 0) {
      found_cff = true;
      write_u32_be_bytes(data + record + 8u, (uint32_t)size);
      write_u32_be_bytes(data + record + 12u, (uint32_t)sizeof(cff));
    } else if (memcmp(data + record, "maxp", 4u) == 0) {
      maxp_offset = offset;
      found_maxp = length >= 6u;
    } else if (memcmp(data + record, "hhea", 4u) == 0) {
      hhea_offset = offset;
      found_hhea = length >= 36u;
    }
  }
  if (!found_cff || !found_maxp || !found_hhea ||
      size > UINT32_MAX - sizeof(cff))
    goto cleanup;
  write_u16_be(data + maxp_offset + 4u, 1u);
  write_u16_be(data + hhea_offset + 34u, 1u);
  fixture = fopen(fixture_path, "wb");
  if (fixture == NULL || fwrite(data, 1, size, fixture) != size ||
      fwrite(cff, 1, sizeof(cff), fixture) != sizeof(cff))
    goto cleanup;
  success = fflush(fixture) == 0;

cleanup:
  if (fixture != NULL) fclose(fixture);
  if (source != NULL) fclose(source);
  free(data);
  if (!success) remove(fixture_path);
  return success;
}
#endif

TEST(utf8_decodes_chinese_codepoints)
{
  const char *text = "\xE7\x9F\xAD\xE7\xBA\xBF\xE4\xBE\xA0";

  ASSERT_EQ(my_utf8_next(&text), 0x77EDu);
  ASSERT_EQ(my_utf8_next(&text), 0x7EBFu);
  ASSERT_EQ(my_utf8_next(&text), 0x4FA0u);
  ASSERT_EQ(*text, '\0');
}

TEST(utf8_rejects_non_scalar_and_truncated_sequences)
{
  const char overlong[] = "\xC0\x80";
  const char surrogate[] = "\xED\xA0\x80";
  const char too_large[] = "\xF4\x90\x80\x80";
  const char truncated[] = "\xE2\x82";
  const char *text;

  text = overlong;
  ASSERT_EQ(my_utf8_next(&text), 0xFFFDu);
  ASSERT_EQ((unsigned char)*text, 0x80u);
  text = surrogate;
  ASSERT_EQ(my_utf8_next(&text), 0xFFFDu);
  ASSERT_EQ((unsigned char)*text, 0xA0u);
  text = too_large;
  ASSERT_EQ(my_utf8_next(&text), 0xFFFDu);
  ASSERT_EQ((unsigned char)*text, 0x90u);
  text = truncated;
  ASSERT_EQ(my_utf8_next(&text), 0xFFFDu);
  ASSERT_EQ((unsigned char)*text, 0x82u);
}

TEST(bitmap_variation_selector_has_no_standalone_glyph_or_advance)
{
  my_font_t* font = my_font_bitmap_create(NULL);
  my_glyph_t glyph = {0};
  int32_t width = 0;

  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_measure(font, "a\xEF\xB8\x8F" "b", 12, &width, NULL),
            MY_RET_OK);
  ASSERT_EQ(width, 24);
  ASSERT_EQ(my_font_get_glyph(font, 0xFE0Fu, 12, &glyph), MY_RET_OK);
  ASSERT_TRUE(glyph.bitmap == NULL);
  ASSERT_EQ(glyph.w, 0);
  ASSERT_EQ(glyph.h, 0);
  ASSERT_EQ(glyph.advance, 0);
  my_font_glyph_release(&glyph);
  my_font_destroy(font);
}

TEST(bitmap_destroy_is_deferred_until_glyph_lease_release)
{
  shape_allocator_state_t state = {0};
  const my_allocator_t allocator = {&state, shape_alloc, shape_calloc,
                                    shape_realloc, shape_free};
  my_font_t* font = my_font_bitmap_create(&allocator);
  my_glyph_t glyph = {0};
  my_glyph_t rejected = {0};

  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_get_glyph(font, 'A', 16, &glyph), MY_RET_OK);
  ASSERT_TRUE(glyph.bitmap != NULL);
  my_font_destroy(font);
  ASSERT_EQ(state.live, 1u);
  ASSERT_TRUE(glyph.bitmap != NULL);
  ASSERT_EQ(my_font_get_glyph(font, 'B', 16, &rejected), MY_RET_FAIL);
  ASSERT_TRUE(rejected.bitmap == NULL);
  ASSERT_EQ(my_font_get_glyph(font, 0xFE0Fu, 16, &rejected), MY_RET_FAIL);
  ASSERT_TRUE(rejected.bitmap == NULL);
  my_font_glyph_release(&glyph);
  ASSERT_EQ(state.live, 0u);
}

TEST(font_shape_cleans_partial_provider_results)
{
  shape_allocator_state_t state = {0};
  const my_allocator_t allocator = {&state, shape_alloc, shape_calloc,
                                    shape_realloc, shape_free};
  my_font_t font = {&s_shape_failure_vtable};
  my_font_shape_result_t result = {0};

  ASSERT_EQ(my_font_shape(&font, "a", 12, false, &allocator, &result),
            MY_RET_FAIL);
  ASSERT_EQ(result.count, 0u);
  ASSERT_TRUE(result.glyphs == NULL);
  ASSERT_EQ(state.live, 0u);
}

TEST(font_shape_ex_forwards_script_language_and_features)
{
  shape_params_font_t font = {{&s_shape_params_vtable}, {0}, {0}, false};
  const my_font_shape_params_t params = {
      true, MY_FONT_SCRIPT_ARAB, "ar", "liga=0,kern=1"};
  my_font_shape_result_t result = {0};

  ASSERT_EQ(my_font_shape_ex((my_font_t*)&font, "abc", 16, &params, NULL,
                             &result), MY_RET_OK);
  ASSERT_TRUE(font.called);
  ASSERT_TRUE(font.received.rtl);
  ASSERT_EQ(font.received.script, MY_FONT_SCRIPT_ARAB);
  ASSERT_STR_EQ(font.received.language, "ar");
  ASSERT_STR_EQ(font.received.features, "kern=1,liga=0");
  my_font_shape_destroy(&result);
}

TEST(font_shape_rejects_oversized_provider_result_transactionally)
{
  my_font_t font = {&s_oversized_result_vtable};
  my_font_shape_result_t result = {0};

  ASSERT_EQ(my_font_shape_ex(&font, "a", 12, NULL, NULL, &result),
            MY_RET_FAIL);
  ASSERT_EQ(result.count, 0u);
  ASSERT_TRUE(result.glyphs == NULL);
}

TEST(freetype_provider_rejects_oversized_direct_shape_input)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *path =
      "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_font_shape_params_t params = {false, MY_FONT_SCRIPT_LATN, NULL, NULL};
  my_font_shape_result_t result = {0};
  char *text;
  size_t i;

  if (file == NULL) {
    printf("  SKIP: no shaping test font\n");
    return;
  }
  fclose(file);
  text = (char *)malloc((size_t)MY_FONT_SHAPE_MAX_BYTES + 2u);
  ASSERT_NOT_NULL(text);
  for (i = 0u; i <= (size_t)MY_FONT_SHAPE_MAX_BYTES; i++) text[i] = 'A';
  text[MY_FONT_SHAPE_MAX_BYTES + 1u] = '\0';
  font = my_font_ft_create(NULL, path, 0, 32);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(font->vtable->shape_ex(font, text, 24, &params, NULL, &result),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(result.count, 0u);
  ASSERT_TRUE(result.glyphs == NULL);
  my_font_destroy(font);
  free(text);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

#if defined(MYUI_FONT_FREETYPE)
typedef struct freetype_shared_face_worker_t {
  my_font_t *font;
  atomic_int *failures;
  unsigned int worker_index;
} freetype_shared_face_worker_t;

static PLATFORM_THREAD_RET freetype_shared_face_worker(
    PLATFORM_THREAD_ARG argument) {
  freetype_shared_face_worker_t *worker =
      (freetype_shared_face_worker_t *)argument;
  unsigned int iteration;
  for (iteration = 0u; iteration < 200u; iteration++) {
    my_glyph_t glyph;
    int32_t size = (iteration + worker->worker_index) % 2u != 0u ? 13 : 24;
    uint32_t codepoint = (iteration + worker->worker_index) % 2u != 0u
                             ? (uint32_t)'A'
                             : (uint32_t)'g';
    my_ret_t ret = my_font_get_glyph(worker->font, codepoint, size, &glyph);
    if (ret != MY_RET_OK || glyph.advance <= 0) {
      my_font_glyph_release(&glyph);
      atomic_fetch_add(worker->failures, 1);
      break;
    }
    {
      int32_t measured_width = 0;
      int32_t measured_height = 0;
      my_font_shape_support_t support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
      if (my_font_measure(worker->font, "Ag", size, &measured_width,
                          &measured_height) != MY_RET_OK ||
          measured_width <= 0 || measured_height <= 0 ||
          my_font_shape_support_query(worker->font, NULL, &support) !=
              MY_RET_OK ||
          my_font_ft_cache_hits(worker->font) == SIZE_MAX ||
          my_font_ft_cache_misses(worker->font) == SIZE_MAX ||
          my_font_ft_shape_support_cache_hits(worker->font) == SIZE_MAX) {
        my_font_glyph_release(&glyph);
        atomic_fetch_add(worker->failures, 1);
        break;
      }
    }
#if defined(MYUI_FONT_HARFBUZZ)
    {
      my_font_shape_result_t result = {0};
      ret = my_font_shape(worker->font, "office", size, false, NULL,
                          &result);
      if (ret != MY_RET_OK || result.count == 0u) {
        my_font_glyph_release(&glyph);
        atomic_fetch_add(worker->failures, 1);
        my_font_shape_destroy(&result);
        break;
      }
      my_font_shape_destroy(&result);
    }
#endif
    my_font_glyph_release(&glyph);
  }
  return PLATFORM_THREAD_RETURN;
}
#endif

TEST(freetype_shared_face_operations_are_thread_safe)
{
#if defined(MYUI_FONT_FREETYPE)
  const char *path =
      "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  PlatformThread threads[4];
  freetype_shared_face_worker_t workers[4];
  atomic_int failures = 0;
  unsigned int created = 0u;
  unsigned int i;

  if (file == NULL) {
    printf("  SKIP: no FreeType concurrency test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(NULL, path, 0, 8);
  ASSERT_NOT_NULL(font);
  for (i = 0u; i < 4u; i++) {
    workers[i].font = font;
    workers[i].failures = &failures;
    workers[i].worker_index = i;
    ASSERT_TRUE(platform_thread_create(&threads[i], freetype_shared_face_worker,
                                       &workers[i]));
    created++;
  }
  for (i = 0u; i < created; i++) platform_thread_join(threads[i]);
  ASSERT_EQ(atomic_load(&failures), 0);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType is unavailable\n");
#endif
}

#if defined(MYUI_FONT_STB)
typedef struct stb_shared_face_worker_t {
  my_font_t *font;
  atomic_int *failures;
  unsigned int worker_index;
} stb_shared_face_worker_t;

static PLATFORM_THREAD_RET stb_shared_face_worker(PLATFORM_THREAD_ARG argument) {
  stb_shared_face_worker_t *worker = (stb_shared_face_worker_t *)argument;
  unsigned int iteration;
  for (iteration = 0u; iteration < 200u; iteration++) {
    my_glyph_t glyph;
    int32_t size = (iteration + worker->worker_index) % 2u != 0u ? 13 : 24;
    uint32_t codepoint = (iteration + worker->worker_index) % 2u != 0u
                             ? (uint32_t)'A'
                             : (uint32_t)'g';
    int32_t width = 0;
    int32_t height = 0;
    if (my_font_get_glyph(worker->font, codepoint, size, &glyph) != MY_RET_OK ||
        glyph.advance <= 0 ||
        my_font_measure(worker->font, "Ag", size, &width, &height) !=
            MY_RET_OK ||
        width <= 0 || height <= 0 || my_font_ascent(worker->font, size) <= 0 ||
        my_font_line_height(worker->font, size) <= 0 ||
        !my_font_has_glyph(worker->font, codepoint) ||
        my_font_stb_cache_hits(worker->font) == SIZE_MAX ||
        my_font_stb_cache_misses(worker->font) == SIZE_MAX) {
      my_font_glyph_release(&glyph);
      atomic_fetch_add(worker->failures, 1);
      break;
    }
    my_font_glyph_release(&glyph);
  }
  return PLATFORM_THREAD_RETURN;
}
#endif

TEST(stb_shared_face_operations_are_thread_safe)
{
#if defined(MYUI_FONT_STB)
  const char *path =
      "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  PlatformThread threads[4];
  stb_shared_face_worker_t workers[4];
  atomic_int failures = 0;
  unsigned int created = 0u;
  unsigned int i;

  if (file == NULL) {
    printf("  SKIP: no STB concurrency test font\n");
    return;
  }
  fclose(file);
  font = my_font_stb_create(NULL, path, 8u);
  ASSERT_NOT_NULL(font);
  for (i = 0u; i < 4u; i++) {
    workers[i].font = font;
    workers[i].failures = &failures;
    workers[i].worker_index = i;
    ASSERT_TRUE(platform_thread_create(&threads[i], stb_shared_face_worker,
                                       &workers[i]));
    created++;
  }
  for (i = 0u; i < created; i++) platform_thread_join(threads[i]);
  ASSERT_EQ(atomic_load(&failures), 0);
  my_font_destroy(font);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(font_shape_support_query_is_explicit_and_normalized)
{
  shape_support_font_t font = {{&s_shape_support_vtable},
                               MY_FONT_SHAPE_SUPPORTED, 0u, 0u, {0}, 0u,
                               NULL};
  my_font_shape_params_t params = {false, MY_FONT_SCRIPT_LATN, "en",
                                   "liga=0,kern=1"};
  my_font_shape_support_t support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;

  ASSERT_EQ(my_font_shape_support_query(&font.base, &params, &support),
            MY_RET_OK);
  ASSERT_EQ(support, MY_FONT_SHAPE_SUPPORTED);
  ASSERT_EQ(font.query_calls, 1u);
  ASSERT_STR_EQ(font.queried_features, "kern=1,liga=0");
}

TEST(font_shape_support_query_reports_unknown_without_provider)
{
  my_font_t font = {&s_shape_params_vtable};
  my_font_shape_support_t support = MY_FONT_SHAPE_SUPPORTED;
  my_font_shape_params_t params = {false, 0u, NULL, NULL};

  ASSERT_EQ(my_font_shape_support_query(&font, &params, &support), MY_RET_OK);
  ASSERT_EQ(support, MY_FONT_SHAPE_SUPPORT_UNKNOWN);
}

TEST(font_shape_ex_falls_back_from_unsupported_language_system)
{
  shape_support_font_t font = {{&s_shape_support_vtable},
                               MY_FONT_SHAPE_UNSUPPORTED, 0u, 0u, {0}, 0u,
                               NULL};
  my_font_shape_params_t params = {false, MY_FONT_SCRIPT_LATN, "ZH-CN", NULL};
  my_font_shape_result_t result = {0};

  ASSERT_EQ(my_font_shape_ex(&font.base, "abc", 16, &params, NULL, &result),
            MY_RET_OK);
  ASSERT_EQ(font.query_calls, 2u);
  ASSERT_EQ(font.shape_ex_calls, 1u);
  ASSERT_EQ(font.last_script, 0u);
  ASSERT_TRUE(font.last_language == NULL);
  my_font_shape_destroy(&result);
}

TEST(font_shape_ex_falls_back_from_unsupported_script)
{
  shape_support_font_t font = {{&s_shape_support_vtable},
                               MY_FONT_SHAPE_UNSUPPORTED, 0u, 0u, {0}, 0u,
                               NULL};
  my_font_shape_params_t params = {false, MY_FONT_SCRIPT_LATN, NULL, NULL};
  my_font_shape_result_t result = {0};

  ASSERT_EQ(my_font_shape_ex(&font.base, "abc", 16, &params, NULL, &result),
            MY_RET_OK);
  ASSERT_EQ(font.query_calls, 1u);
  ASSERT_EQ(font.shape_ex_calls, 1u);
  ASSERT_EQ(font.last_script, 0u);
  ASSERT_TRUE(font.last_language == NULL);
  my_font_shape_destroy(&result);
}

TEST(font_shape_ex_rejects_explicitly_unsupported_features)
{
  shape_support_font_t font = {{&s_shape_support_vtable},
                               MY_FONT_SHAPE_UNSUPPORTED, 0u, 0u, {0}, 0u,
                               NULL};
  my_font_shape_params_t params = {false, 0u, NULL, "liga=1"};
  my_font_shape_result_t result = {0};

  ASSERT_EQ(my_font_shape_ex(&font.base, "abc", 16, &params, NULL, &result),
            MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(font.query_calls, 1u);
  ASSERT_EQ(font.shape_ex_calls, 0u);
  ASSERT_EQ(result.count, 0u);
  ASSERT_TRUE(result.glyphs == NULL);
}

TEST(font_features_normalize_resolves_duplicate_tags)
{
  char normalized[MY_FONT_SHAPE_MAX_FEATURE_BYTES + 1u];

  ASSERT_TRUE(my_font_shape_features_normalize(
      "liga=1,kern=0,liga=0", normalized, sizeof(normalized)));
  ASSERT_STR_EQ(normalized, "kern=0,liga=0");
  ASSERT_TRUE(my_font_shape_features_normalize(
      "liga=0,liga=1", normalized, sizeof(normalized)));
  ASSERT_STR_EQ(normalized, "liga=1");
}

TEST(font_features_normalize_makes_order_equivalent)
{
  char first[MY_FONT_SHAPE_MAX_FEATURE_BYTES + 1u];
  char second[MY_FONT_SHAPE_MAX_FEATURE_BYTES + 1u];

  ASSERT_TRUE(my_font_shape_features_normalize(
      "liga=0,kern=1", first, sizeof(first)));
  ASSERT_TRUE(my_font_shape_features_normalize(
      " kern = 1 , liga = 0 ", second, sizeof(second)));
  ASSERT_STR_EQ(first, second);
  ASSERT_STR_EQ(first, "kern=1,liga=0");
}

TEST(font_features_normalize_splits_overlapping_ranges)
{
  char normalized[MY_FONT_SHAPE_MAX_FEATURE_BYTES + 1u];

  ASSERT_TRUE(my_font_shape_features_normalize(
      "-kern,liga[2:5]=1,liga[4:7]=0", normalized,
      sizeof(normalized)));
  ASSERT_STR_EQ(normalized, "kern=0,liga[2:4]=1,liga[4:7]=0");
}

TEST(font_features_normalize_rejects_invalid_or_small_output)
{
  char normalized[8];
  char large[MY_FONT_SHAPE_MAX_FEATURE_BYTES + 1u];

  ASSERT_FALSE(my_font_shape_features_normalize(
      "liga=1,,kern=0", large, sizeof(large)));
  ASSERT_FALSE(my_font_shape_features_normalize(
      "liga=1,kern=0", normalized, sizeof(normalized)));
  ASSERT_TRUE(my_font_shape_features_normalize(NULL, large, sizeof(large)));
  ASSERT_STR_EQ(large, "");
}

TEST(font_shape_ex_rejects_oversized_feature_parameters)
{
  my_font_t font = {&s_shape_failure_vtable};
  my_font_shape_params_t params = {false, 0, NULL, NULL};
  my_font_shape_result_t result = {0};
  char features[MY_FONT_SHAPE_MAX_FEATURE_BYTES + 2u];

  memset(features, 'a', sizeof(features));
  features[sizeof(features) - 1u] = '\0';
  params.features = features;
  ASSERT_EQ(my_font_shape_ex(&font, "a", 12, &params, NULL, &result),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(result.count, 0u);
  ASSERT_TRUE(result.glyphs == NULL);
}

TEST(font_shape_ex_rejects_invalid_feature_list_before_provider)
{
  shape_params_font_t font = {{&s_shape_params_vtable}, {0}, {0}, false};
  my_font_shape_params_t params = {false, 0u, NULL, "kern=1,,liga=1"};
  my_font_shape_result_t result = {0};

  ASSERT_EQ(my_font_shape_ex(&font.base, "a", 12, &params, NULL, &result),
            MY_RET_INVALID_PARAMS);
  ASSERT_FALSE(font.called);
  ASSERT_EQ(result.count, 0u);
  ASSERT_TRUE(result.glyphs == NULL);
}

TEST(font_shape_ex_rejects_more_than_feature_policy_limit)
{
  shape_params_font_t font = {{&s_shape_params_vtable}, {0}, {0}, false};
  my_font_shape_params_t params = {false, 0u, NULL, NULL};
  my_font_shape_result_t result = {0};
  char features[MY_FONT_SHAPE_MAX_FEATURE_BYTES + 1u];
  size_t i;

  memset(features, 0, sizeof(features));
  for (i = 0; i < MY_FONT_SHAPE_MAX_FEATURE_COUNT + 1u; ++i) {
    if (i != 0u) strcat(features, ",");
    features[strlen(features)] = (char)('a' + (i / 26u));
    features[strlen(features)] = (char)('a' + (i % 26u));
    features[strlen(features)] = '0';
    features[strlen(features)] = '0';
    features[strlen(features)] = '=';
    features[strlen(features)] = '1';
    features[strlen(features)] = '\0';
  }
  params.features = features;
  ASSERT_EQ(my_font_shape_ex(&font.base, "a", 12, &params, NULL, &result),
            MY_RET_INVALID_PARAMS);
  ASSERT_FALSE(font.called);
  ASSERT_EQ(result.count, 0u);
  ASSERT_TRUE(result.glyphs == NULL);
}

TEST(font_shape_rejects_oversized_text_before_provider)
{
  shape_params_font_t font = {{&s_shape_params_vtable}, {0}, {0}, false};
  my_font_shape_result_t result = {0};
  size_t length = (size_t)MY_FONT_SHAPE_MAX_BYTES + 1u;
  char* text = (char*)malloc(length + 1u);

  ASSERT_NOT_NULL(text);
  memset(text, 'x', length);
  text[length] = '\0';
  ASSERT_EQ(my_font_shape(&font.base, text, 12, false, NULL, &result),
            MY_RET_INVALID_PARAMS);
  ASSERT_FALSE(font.called);
  ASSERT_EQ(result.count, 0u);
  ASSERT_TRUE(result.glyphs == NULL);
  free(text);
}

TEST(freetype_direct_measure_rejects_oversized_text)
{
#ifdef MYUI_FONT_FREETYPE
  const char *path = "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  char *text;
  int32_t width = 0;
  size_t length = (size_t)MY_FONT_SHAPE_MAX_BYTES + 1u;

  if (file == NULL) {
    printf("  SKIP: no FreeType measure test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(NULL, path, 0, 16u);
  text = (char *)malloc(length + 1u);
  ASSERT_NOT_NULL(font);
  ASSERT_NOT_NULL(text);
  memset(text, 'x', length);
  text[length] = '\0';
  ASSERT_EQ(font->vtable->measure(font, text, 12, &width, NULL),
            MY_RET_INVALID_PARAMS);
  free(text);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType is unavailable\n");
#endif
}

TEST(stb_direct_measure_rejects_oversized_text)
{
#ifdef MYUI_FONT_STB
  const char *path = "/usr/share/fonts/liberation-serif-fonts/LiberationSerif-Regular.ttf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  char *text;
  int32_t width = 0;
  size_t length = (size_t)MY_FONT_SHAPE_MAX_BYTES + 1u;

  if (file == NULL) {
    printf("  SKIP: no STB measure test font\n");
    return;
  }
  fclose(file);
  font = my_font_stb_create(NULL, path, 16u);
  text = (char *)malloc(length + 1u);
  ASSERT_NOT_NULL(font);
  ASSERT_NOT_NULL(text);
  memset(text, 'x', length);
  text[length] = '\0';
  ASSERT_EQ(font->vtable->measure(font, text, 12, &width, NULL),
            MY_RET_INVALID_PARAMS);
  free(text);
  my_font_destroy(font);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(font_measure_saturates_width_instead_of_wrapping)
{
  my_font_t *font = my_font_bitmap_create(NULL);
  char *text = (char *)malloc(MY_FONT_SHAPE_MAX_BYTES);
  int32_t width = 0;
  size_t i;

  ASSERT_NOT_NULL(font);
  ASSERT_NOT_NULL(text);
  for (i = 0; i + 1u < MY_FONT_SHAPE_MAX_BYTES; i++) text[i] = 'A';
  text[MY_FONT_SHAPE_MAX_BYTES - 1u] = '\0';
  ASSERT_EQ(my_font_measure(font, text, INT32_MAX, &width, NULL), MY_RET_OK);
  ASSERT_EQ(width, INT32_MAX);
  free(text);
  my_font_destroy(font);
}

TEST(stb_glyph_oom_does_not_poison_cache)
{
#ifdef MYUI_FONT_STB
  const char *path = "/usr/share/fonts/liberation-serif-fonts/LiberationSerif-Regular.ttf";
  FILE *file = fopen(path, "rb");
  shape_allocator_state_t state = {0};
  const my_allocator_t allocator = {&state, shape_alloc, shape_calloc,
                                    shape_realloc, shape_free};
  my_font_t *font;
  my_glyph_t glyph = {0};

  if (file == NULL) {
    printf("  SKIP: no STB test font\n");
    return;
  }
  fclose(file);
  font = my_font_stb_create(&allocator, path, 8);
  ASSERT_NOT_NULL(font);
  state.calls = 0;
  ASSERT_EQ(my_font_get_glyph(font, 'Q', 24, &glyph), MY_RET_OK);
  ASSERT_TRUE(glyph_has_coverage(&glyph));
  my_font_glyph_release(&glyph);
  state.calls = 0;
  state.fail_at = 1;
  memset(&glyph, 0, sizeof(glyph));
  ASSERT_EQ(my_font_get_glyph(font, 'R', 24, &glyph), MY_RET_OOM);
  ASSERT_TRUE(glyph.bitmap == NULL);
  state.fail_at = 0;
  memset(&glyph, 0, sizeof(glyph));
  ASSERT_EQ(my_font_get_glyph(font, 'R', 24, &glyph), MY_RET_OK);
  ASSERT_TRUE(glyph_has_coverage(&glyph));
  my_font_glyph_release(&glyph);
  memset(&glyph, 0, sizeof(glyph));
  ASSERT_EQ(my_font_get_glyph(font, 'Q', 24, &glyph), MY_RET_OK);
  ASSERT_TRUE(glyph_has_coverage(&glyph));
  my_font_glyph_release(&glyph);
  my_font_destroy(font);
  ASSERT_EQ(state.live, 0u);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_glyph_lease_survives_cache_eviction)
{
#ifdef MYUI_FONT_STB
  const char *path = "/usr/share/fonts/liberation-serif-fonts/LiberationSerif-Regular.ttf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_glyph_t first = {0};
  my_glyph_t second = {0};
  uint8_t first_sample;

  if (file == NULL) {
    printf("  SKIP: no STB test font\n");
    return;
  }
  fclose(file);
  font = my_font_stb_create(NULL, path, 1u);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_get_glyph(font, 'Q', 24, &first), MY_RET_OK);
  ASSERT_TRUE(glyph_has_coverage(&first));
  first_sample = first.bitmap[0];
  ASSERT_EQ(my_font_get_glyph(font, 'R', 24, &second), MY_RET_OK);
  ASSERT_TRUE(glyph_has_coverage(&second));
  ASSERT_EQ(first.bitmap[0], first_sample);
  ASSERT_TRUE(glyph_has_coverage(&first));
  my_font_glyph_release(&second);
  my_font_glyph_release(&first);
  my_font_destroy(font);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_destroy_is_deferred_until_glyph_lease_release)
{
#ifdef MYUI_FONT_STB
  const char *path = "/usr/share/fonts/liberation-serif-fonts/LiberationSerif-Regular.ttf";
  FILE *file = fopen(path, "rb");
  shape_allocator_state_t state = {0};
  const my_allocator_t allocator = {&state, shape_alloc, shape_calloc,
                                    shape_realloc, shape_free};
  my_font_t *font;
  my_glyph_t glyph = {0};

  if (file == NULL) {
    printf("  SKIP: no STB test font\n");
    return;
  }
  fclose(file);
  font = my_font_stb_create(&allocator, path, 1u);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_get_glyph(font, 'Q', 24, &glyph), MY_RET_OK);
  ASSERT_TRUE(glyph_has_coverage(&glyph));
  my_font_destroy(font);
  ASSERT_TRUE(state.live > 0u);
  ASSERT_TRUE(glyph_has_coverage(&glyph));
  my_font_glyph_release(&glyph);
  ASSERT_EQ(state.live, 0u);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_glyph_lease_overflow_is_bounded)
{
#ifdef MYUI_FONT_STB
  const char *path = "/usr/share/fonts/liberation-serif-fonts/LiberationSerif-Regular.ttf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_glyph_t first = {0};
  my_glyph_t second = {0};
  my_glyph_t third = {0};

  if (file == NULL) {
    printf("  SKIP: no STB test font\n");
    return;
  }
  fclose(file);
  font = my_font_stb_create(NULL, path, 1u);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_get_glyph(font, 'Q', 24, &first), MY_RET_OK);
  ASSERT_EQ(my_font_get_glyph(font, 'R', 24, &second), MY_RET_OK);
  ASSERT_EQ(my_font_get_glyph(font, 'S', 24, &third), MY_RET_OOM);
  ASSERT_TRUE(third.bitmap == NULL);
  my_font_glyph_release(&second);
  ASSERT_EQ(my_font_get_glyph(font, 'S', 24, &third), MY_RET_OK);
  my_font_glyph_release(&third);
  my_font_glyph_release(&first);
  my_font_destroy(font);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_ttc_selects_requested_face)
{
#ifdef MYUI_FONT_STB
  static const char *const candidates[] = {
      "../engine/assets/LiberationSans-Regular.ttf",
      "engine/assets/LiberationSans-Regular.ttf",
      "assets/LiberationSans-Regular.ttf",
#if defined(_WIN32)
      "C:/Windows/Fonts/arial.ttf",
#elif defined(__APPLE__)
      "/System/Library/Fonts/Supplemental/Arial.ttf",
#else
      "/usr/share/fonts/liberation-serif-fonts/LiberationSerif-Regular.ttf",
#endif
      NULL};
  const char *source_path = NULL;
  char fixture_path[128];
  FILE *file;
  my_font_t *font;
  my_font_t *chain;
  my_font_source_t source;
  my_glyph_t glyph = {0};
  size_t candidate_index;

  for (candidate_index = 0u; candidates[candidate_index] != NULL;
       candidate_index++) {
    file = fopen(candidates[candidate_index], "rb");
    if (file != NULL) {
      fclose(file);
      source_path = candidates[candidate_index];
      break;
    }
  }
  if (source_path == NULL) {
    printf("  SKIP: no STB TTC test font\n");
    return;
  }
  test_tmp(fixture_path, sizeof(fixture_path), "myui_stb_face_index.ttc");
  ASSERT_TRUE(create_stb_ttc_fixture(source_path, fixture_path));
  ASSERT_TRUE(my_font_stb_create_ex(NULL, source_path, 1, 16) == NULL);
  font = my_font_stb_create_ex(NULL, fixture_path, 1, 16);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_get_glyph(font, 'Q', 18, &glyph), MY_RET_OK);
  ASSERT_TRUE(glyph_has_coverage(&glyph));
  my_font_glyph_release(&glyph);
  my_font_destroy(font);
  source.path = fixture_path;
  source.face_index = 1;
  chain = my_font_create_chain_ex(NULL, &source, 1u, 16u);
  ASSERT_NOT_NULL(chain);
  memset(&glyph, 0, sizeof(glyph));
  ASSERT_EQ(my_font_get_glyph(chain, 'Q', 18, &glyph), MY_RET_OK);
  ASSERT_TRUE(glyph_has_coverage(&glyph));
  my_font_glyph_release(&glyph);
  my_font_destroy(chain);
  remove(fixture_path);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_rejects_oversized_file_before_allocation)
{
#ifdef MYUI_FONT_STB
  char path[128];
  FILE *file;
  shape_allocator_state_t state = {0};
  const my_allocator_t allocator = {&state, shape_alloc, shape_calloc,
                                    shape_realloc, shape_free};

  test_tmp(path, sizeof(path), "myui_stb_oversized.ttf");
  file = fopen(path, "wb");
  ASSERT_NOT_NULL(file);
  ASSERT_EQ(fseek(file, (long)MY_FONT_STB_MAX_FILE_BYTES, SEEK_SET), 0);
  ASSERT_NEQ(fputc('x', file), EOF);
  fclose(file);
  ASSERT_TRUE(my_font_stb_create(&allocator, path, 8) == NULL);
  ASSERT_EQ(state.calls, 1u);
  remove(path);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_rejects_truncated_ttc_header)
{
#ifdef MYUI_FONT_STB
  char path[128];
  FILE *file;
  const unsigned char truncated_ttc[] = {'t', 't', 'c', 'f', 0, 1, 0, 0};

  test_tmp(path, sizeof(path), "myui_stb_truncated.ttc");
  file = fopen(path, "wb");
  ASSERT_NOT_NULL(file);
  ASSERT_EQ(fwrite(truncated_ttc, 1, sizeof(truncated_ttc), file),
            sizeof(truncated_ttc));
  ASSERT_EQ(fclose(file), 0);
  ASSERT_TRUE(my_font_stb_create(NULL, path, 8) == NULL);
  remove(path);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_rejects_out_of_range_table_offset)
{
#ifdef MYUI_FONT_STB
  static const char *const candidates[] = {
      "../engine/assets/LiberationSans-Regular.ttf",
      "engine/assets/LiberationSans-Regular.ttf",
      "assets/LiberationSans-Regular.ttf",
#if defined(_WIN32)
      "C:/Windows/Fonts/arial.ttf",
#elif defined(__APPLE__)
      "/System/Library/Fonts/Supplemental/Arial.ttf",
#else
      "/usr/share/fonts/liberation-serif-fonts/LiberationSerif-Regular.ttf",
#endif
      NULL};
  const char *source_path = NULL;
  char fixture_path[128];
  FILE *file;
  my_font_t *font;
  size_t candidate_index;

  for (candidate_index = 0u; candidates[candidate_index] != NULL;
       candidate_index++) {
    file = fopen(candidates[candidate_index], "rb");
    if (file != NULL) {
      fclose(file);
      source_path = candidates[candidate_index];
      break;
    }
  }
  if (source_path == NULL) {
    printf("  SKIP: no STB table-validation font\n");
    return;
  }
  test_tmp(fixture_path, sizeof(fixture_path), "myui_stb_bad_table.ttf");
  ASSERT_TRUE(create_stb_bad_table_fixture(source_path, fixture_path));
  font = my_font_stb_create(NULL, fixture_path, 8);
  ASSERT_TRUE(font == NULL);
  remove(fixture_path);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_rejects_short_required_table)
{
#ifdef MYUI_FONT_STB
  static const char *const candidates[] = {
      "../engine/assets/LiberationSans-Regular.ttf",
      "engine/assets/LiberationSans-Regular.ttf",
      "assets/LiberationSans-Regular.ttf",
#if defined(_WIN32)
      "C:/Windows/Fonts/arial.ttf",
#elif defined(__APPLE__)
      "/System/Library/Fonts/Supplemental/Arial.ttf",
#else
      "/usr/share/fonts/liberation-serif-fonts/LiberationSerif-Regular.ttf",
#endif
      NULL};
  const char *source_path = NULL;
  char fixture_path[128];
  FILE *file;
  size_t candidate_index;

  for (candidate_index = 0u; candidates[candidate_index] != NULL;
       candidate_index++) {
    file = fopen(candidates[candidate_index], "rb");
    if (file != NULL) {
      fclose(file);
      source_path = candidates[candidate_index];
      break;
    }
  }
  if (source_path == NULL) {
    printf("  SKIP: no STB table-validation font\n");
    return;
  }
  test_tmp(fixture_path, sizeof(fixture_path), "myui_stb_short_head.ttf");
  ASSERT_TRUE(create_stb_short_table_fixture(source_path, fixture_path,
                                             "head", 2u));
  ASSERT_TRUE(my_font_stb_create(NULL, fixture_path, 8) == NULL);
  remove(fixture_path);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_rejects_out_of_range_cmap_glyph_index)
{
#ifdef MYUI_FONT_STB
  static const char *const candidates[] = {
      "../engine/assets/LiberationSans-Regular.ttf",
      "engine/assets/LiberationSans-Regular.ttf",
      "assets/LiberationSans-Regular.ttf",
#if defined(_WIN32)
      "C:/Windows/Fonts/arial.ttf",
#elif defined(__APPLE__)
      "/System/Library/Fonts/Supplemental/Arial.ttf",
#else
      "/usr/share/fonts/liberation-serif-fonts/LiberationSerif-Regular.ttf",
#endif
      NULL};
  const char *source_path = NULL;
  char fixture_path[128];
  FILE *file;
  size_t candidate_index;

  for (candidate_index = 0u; candidates[candidate_index] != NULL;
       candidate_index++) {
    file = fopen(candidates[candidate_index], "rb");
    if (file != NULL) {
      fclose(file);
      source_path = candidates[candidate_index];
      break;
    }
  }
  if (source_path == NULL) {
    printf("  SKIP: no STB cmap-validation font\n");
    return;
  }
  test_tmp(fixture_path, sizeof(fixture_path), "myui_stb_bad_cmap.ttf");
  ASSERT_TRUE(create_stb_bad_cmap_range_fixture(source_path, fixture_path));
  ASSERT_TRUE(my_font_stb_create(NULL, fixture_path, 8) == NULL);
  remove(fixture_path);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_rejects_short_glyph_record)
{
#ifdef MYUI_FONT_STB
  const char *source_path = "engine/assets/LiberationSans-Regular.ttf";
  char fixture_path[128];
  FILE *file = fopen(source_path, "rb");
  if (file == NULL) {
    printf("  SKIP: no STB glyph-validation font\n");
    return;
  }
  fclose(file);
  test_tmp(fixture_path, sizeof(fixture_path), "myui_stb_short_glyph.ttf");
  ASSERT_TRUE(create_stb_short_glyph_fixture(source_path, fixture_path));
  ASSERT_TRUE(my_font_stb_create(NULL, fixture_path, 8) == NULL);
  remove(fixture_path);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_rejects_out_of_range_simple_glyph_instruction)
{
#ifdef MYUI_FONT_STB
  const char *source_path = "engine/assets/LiberationSans-Regular.ttf";
  char fixture_path[128];
  FILE *file = fopen(source_path, "rb");
  if (file == NULL) {
    printf("  SKIP: no STB simple-glyph validation font\n");
    return;
  }
  fclose(file);
  test_tmp(fixture_path, sizeof(fixture_path), "myui_stb_bad_instruction.ttf");
  ASSERT_TRUE(create_stb_bad_instruction_fixture(source_path, fixture_path));
  ASSERT_TRUE(my_font_stb_create(NULL, fixture_path, 8) == NULL);
  remove(fixture_path);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_rejects_truncated_simple_glyph_coordinates)
{
#ifdef MYUI_FONT_STB
  const char *source_path = "engine/assets/LiberationSans-Regular.ttf";
  char fixture_path[128];
  FILE *file = fopen(source_path, "rb");
  if (file == NULL) {
    printf("  SKIP: no STB coordinate-validation font\n");
    return;
  }
  fclose(file);
  test_tmp(fixture_path, sizeof(fixture_path), "myui_stb_short_coordinates.ttf");
  ASSERT_TRUE(create_stb_short_coordinate_fixture(source_path, fixture_path));
  ASSERT_TRUE(my_font_stb_create(NULL, fixture_path, 8) == NULL);
  remove(fixture_path);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_rejects_out_of_range_component_glyph)
{
#ifdef MYUI_FONT_STB
  const char *source_path = "engine/assets/LiberationSans-Regular.ttf";
  char fixture_path[128];
  FILE *file = fopen(source_path, "rb");
  if (file == NULL) {
    printf("  SKIP: no STB component-validation font\n");
    return;
  }
  fclose(file);
  test_tmp(fixture_path, sizeof(fixture_path), "myui_stb_bad_component.ttf");
  ASSERT_TRUE(create_stb_bad_component_fixture(source_path, fixture_path));
  ASSERT_TRUE(my_font_stb_create(NULL, fixture_path, 8) == NULL);
  remove(fixture_path);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_rejects_component_cycle)
{
#ifdef MYUI_FONT_STB
  const char *source_path = "engine/assets/LiberationSans-Regular.ttf";
  char fixture_path[128];
  FILE *file = fopen(source_path, "rb");
  if (file == NULL) {
    printf("  SKIP: no STB cycle-validation font\n");
    return;
  }
  fclose(file);
  test_tmp(fixture_path, sizeof(fixture_path), "myui_stb_component_cycle.ttf");
  ASSERT_TRUE(create_stb_component_cycle_fixture(source_path, fixture_path));
  ASSERT_TRUE(my_font_stb_create(NULL, fixture_path, 8) == NULL);
  remove(fixture_path);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_accepts_deep_component_chain_without_recursion)
{
#ifdef MYUI_FONT_STB
  const char *source_path = "engine/assets/LiberationSans-Regular.ttf";
  char fixture_path[128];
  FILE *file = fopen(source_path, "rb");
  my_font_t *font;
  if (file == NULL) {
    printf("  SKIP: no STB deep-component font\n");
    return;
  }
  fclose(file);
  test_tmp(fixture_path, sizeof(fixture_path), "myui_stb_deep_components.ttf");
  ASSERT_TRUE(create_stb_deep_component_fixture(source_path, fixture_path));
  font = my_font_stb_create(NULL, fixture_path, 8);
  ASSERT_NOT_NULL(font);
  my_font_destroy(font);
  remove(fixture_path);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_rejects_out_of_range_compound_instructions)
{
#ifdef MYUI_FONT_STB
  const char *source_path = "engine/assets/LiberationSans-Regular.ttf";
  char fixture_path[128];
  FILE *file = fopen(source_path, "rb");
  if (file == NULL) {
    printf("  SKIP: no STB compound-instruction font\n");
    return;
  }
  fclose(file);
  test_tmp(fixture_path, sizeof(fixture_path),
           "myui_stb_bad_compound_instructions.ttf");
  ASSERT_TRUE(create_stb_bad_compound_instruction_fixture(source_path,
                                                           fixture_path));
  ASSERT_TRUE(my_font_stb_create(NULL, fixture_path, 8) == NULL);
  remove(fixture_path);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_rejects_truncated_cff_table)
{
#ifdef MYUI_FONT_STB
  static const char *const candidates[] = {
      "/usr/share/fonts/aajohan-comfortaa-fonts/Comfortaa-Regular.otf",
      "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf",
      NULL};
  const char *source_path = NULL;
  char fixture_path[128];
  FILE *file;
  size_t candidate_index;
  for (candidate_index = 0u; candidates[candidate_index] != NULL;
       candidate_index++) {
    file = fopen(candidates[candidate_index], "rb");
    if (file != NULL) {
      fclose(file);
      source_path = candidates[candidate_index];
      break;
    }
  }
  if (source_path == NULL) {
    printf("  SKIP: no STB CFF validation font\n");
    return;
  }
  test_tmp(fixture_path, sizeof(fixture_path), "myui_stb_truncated_cff.otf");
  ASSERT_TRUE(create_stb_truncated_cff_fixture(source_path, fixture_path));
  ASSERT_TRUE(my_font_stb_create(NULL, fixture_path, 8) == NULL);
  remove(fixture_path);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_loads_bounded_cff_font)
{
#ifdef MYUI_FONT_STB
  static const char *const candidates[] = {
      "/usr/share/fonts/aajohan-comfortaa-fonts/Comfortaa-Regular.otf",
      "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf",
      NULL};
  FILE *file;
  size_t candidate_index;
  my_font_t *font;
  my_glyph_t glyph;
  size_t loaded_count = 0u;
  for (candidate_index = 0u; candidates[candidate_index] != NULL;
       candidate_index++) {
    file = fopen(candidates[candidate_index], "rb");
    if (file != NULL) {
      fclose(file);
      font = my_font_stb_create(NULL, candidates[candidate_index], 8);
      ASSERT_NOT_NULL(font);
      ASSERT_EQ(my_font_get_glyph(font, 'A', 18, &glyph), MY_RET_OK);
      ASSERT_TRUE(glyph.advance > 0);
      my_font_glyph_release(&glyph);
      my_font_destroy(font);
      loaded_count++;
    }
  }
  if (loaded_count == 0u) {
    printf("  SKIP: no STB CFF font\n");
    return;
  }
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_loads_bounded_cid_cff_font)
{
#ifdef MYUI_FONT_STB
  const char *source_path =
      "/usr/share/fonts/aajohan-comfortaa-fonts/Comfortaa-Regular.otf";
  char fixture_path[128];
  FILE *file = fopen(source_path, "rb");
  my_font_t *font;
  if (file == NULL) {
    printf("  SKIP: no STB CID CFF source font\n");
    return;
  }
  fclose(file);
  test_tmp(fixture_path, sizeof(fixture_path), "myui_stb_cid_cff.otf");
  ASSERT_TRUE(create_stb_cid_cff_fixture(source_path, fixture_path, 0));
  font = my_font_stb_create(NULL, fixture_path, 8);
  ASSERT_NOT_NULL(font);
  my_font_destroy(font);
  remove(fixture_path);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_rejects_invalid_cid_font_dict_private_data)
{
#ifdef MYUI_FONT_STB
  const char *source_path =
      "/usr/share/fonts/aajohan-comfortaa-fonts/Comfortaa-Regular.otf";
  char fixture_path[128];
  FILE *file = fopen(source_path, "rb");
  int mode;
  if (file == NULL) {
    printf("  SKIP: no STB CID CFF source font\n");
    return;
  }
  fclose(file);
  for (mode = 1; mode <= 3; mode++) {
    test_tmp(fixture_path, sizeof(fixture_path), "myui_stb_bad_cid_cff.otf");
    ASSERT_TRUE(create_stb_cid_cff_fixture(source_path, fixture_path, mode));
    ASSERT_TRUE(my_font_stb_create(NULL, fixture_path, 8) == NULL);
    remove(fixture_path);
  }
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_rejects_malformed_type2_charstrings)
{
#ifdef MYUI_FONT_STB
  const char *source_path =
      "/usr/share/fonts/aajohan-comfortaa-fonts/Comfortaa-Regular.otf";
  char fixture_path[128];
  FILE *file = fopen(source_path, "rb");
  int mode;
  if (file == NULL) {
    printf("  SKIP: no STB CFF source font\n");
    return;
  }
  fclose(file);
  for (mode = 4; mode <= 9; mode++) {
    test_tmp(fixture_path, sizeof(fixture_path), "myui_stb_bad_charstring.otf");
    ASSERT_TRUE(create_stb_cid_cff_fixture(source_path, fixture_path, mode));
    ASSERT_TRUE(my_font_stb_create(NULL, fixture_path, 8) == NULL);
    remove(fixture_path);
  }
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(stb_rejects_malformed_cff_dict_operands)
{
#ifdef MYUI_FONT_STB
  const char *source_path =
      "/usr/share/fonts/aajohan-comfortaa-fonts/Comfortaa-Regular.otf";
  char fixture_path[128];
  FILE *file = fopen(source_path, "rb");
  if (file == NULL) {
    printf("  SKIP: no STB CFF source font\n");
    return;
  }
  fclose(file);
  test_tmp(fixture_path, sizeof(fixture_path), "myui_stb_bad_cff_dict.otf");
  ASSERT_TRUE(create_stb_cid_cff_fixture(source_path, fixture_path, 10));
  ASSERT_TRUE(my_font_stb_create(NULL, fixture_path, 8) == NULL);
  remove(fixture_path);
#else
  printf("  SKIP: STB is unavailable\n");
#endif
}

TEST(cjk_ttc_face_rasterizes_chinese_glyphs)
{
#ifdef MYUI_FONT_FREETYPE
  const CjkFontCandidate *candidate = find_cjk_font();
  const uint32_t codepoints[] = {0x77EDu, 0x7EBFu, 0x4FA0u};
  my_font_t *font;
  size_t i;

  if (candidate == NULL) {
    printf("  SKIP: no system CJK font\n");
    return;
  }
  {
    const my_font_source_t source = {candidate->path, candidate->face_index};
    font = my_font_create_chain_ex(NULL, &source, 1, 32);
  }
  ASSERT_NOT_NULL(font);
  for (i = 0; i < sizeof(codepoints) / sizeof(codepoints[0]); i++) {
    my_glyph_t glyph;
    ASSERT_TRUE(my_font_has_glyph(font, codepoints[i]));
    ASSERT_EQ(my_font_get_glyph(font, codepoints[i], 18, &glyph), MY_RET_OK);
    ASSERT_TRUE(glyph.advance > 0);
    ASSERT_TRUE(glyph_has_coverage(&glyph));
    my_font_glyph_release(&glyph);
  }
  my_font_destroy(font);
#else
  printf("  SKIP: MYUI_FONT_FREETYPE is unavailable\n");
#endif
}

TEST(optional_opentype_shaping_has_explicit_fallback)
{
  my_font_shape_result_t result;
  my_font_t *font;
  const char *path = "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  memset(&result, 0, sizeof(result));
  if (file == NULL) {
    printf("  SKIP: no shaping test font\n");
    return;
  }
  fclose(file);
#ifdef MYUI_FONT_FREETYPE
  font = my_font_ft_create(NULL, path, 0, 32);
#else
  font = my_font_bitmap_create(NULL);
#endif
  ASSERT_NOT_NULL(font);
#ifdef MYUI_FONT_HARFBUZZ
  ASSERT_EQ(my_font_shape(font, "office", 24, false, NULL, &result),
            MY_RET_OK);
  ASSERT_EQ(result.count, 5u);
  ASSERT_TRUE(result.used_complex_shaping);
  ASSERT_EQ(result.glyphs[0].cluster, 0u);
  ASSERT_EQ(result.glyphs[1].cluster, 1u);
  ASSERT_EQ(result.glyphs[2].cluster, 2u);
  ASSERT_EQ(result.glyphs[3].cluster, 4u);
  ASSERT_EQ(result.glyphs[4].cluster, 5u);
  ASSERT_TRUE(result.glyphs[2].advance_x_26_6 > 0);
  my_font_shape_destroy(&result);
#else
  ASSERT_EQ(my_font_shape(font, "office", 24, false, NULL, &result),
            MY_RET_NOT_SUPPORTED);
#endif
  my_font_destroy(font);
}

TEST(freetype_script_capability_query)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *path = "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_font_shape_params_t params = {false, MY_FONT_SCRIPT_LATN, NULL, NULL};
  my_font_shape_support_t support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
  if (file == NULL) {
    printf("  SKIP: no shaping test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(NULL, path, 0, 32);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape_support_query(font, &params, &support), MY_RET_OK);
  ASSERT_EQ(support, MY_FONT_SHAPE_SUPPORTED);
  ASSERT_EQ(my_font_shape_support_query(font, &params, &support), MY_RET_OK);
  ASSERT_EQ(my_font_ft_shape_support_cache_hits(font), 1u);
  params.features = "liga=1";
  support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
  ASSERT_EQ(my_font_shape_support_query(font, &params, &support), MY_RET_OK);
  ASSERT_EQ(support, MY_FONT_SHAPE_SUPPORTED);
  ASSERT_EQ(my_font_ft_shape_support_cache_hits(font), 1u);
  params.features = "zzzz=1";
  support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
  ASSERT_EQ(my_font_shape_support_query(font, &params, &support), MY_RET_OK);
  ASSERT_EQ(support, MY_FONT_SHAPE_UNSUPPORTED);
  ASSERT_EQ(my_font_ft_shape_support_cache_hits(font), 1u);
  params.language = "zz";
  params.features = NULL;
  support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
  ASSERT_EQ(my_font_shape_support_query(font, &params, &support), MY_RET_OK);
  ASSERT_EQ(support, MY_FONT_SHAPE_UNSUPPORTED);
  {
    my_font_shape_result_t result = {0};
    ASSERT_EQ(my_font_shape_ex(font, "office", 24, &params, NULL, &result),
              MY_RET_OK);
    ASSERT_TRUE(result.count > 0u);
    my_font_shape_destroy(&result);
  }
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(freetype_language_specific_locl_golden)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *path =
      "/usr/share/fonts/adobe-source-code-pro-fonts/SourceCodePro-Black.otf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_font_shape_params_t russian = {false, MY_FONT_SCRIPT_CYRL, "ru", NULL};
  my_font_shape_params_t serbian = {false, MY_FONT_SCRIPT_CYRL, "sr", NULL};
  my_font_shape_params_t serbian_without_locl = {
      false, MY_FONT_SCRIPT_CYRL, "sr", "locl=0"};
  my_font_shape_result_t ru_result = {0};
  my_font_shape_result_t sr_result = {0};
  my_font_shape_result_t sr_disabled_result = {0};
  my_ret_t ru_status;
  my_ret_t sr_status;
  my_ret_t sr_disabled_status;
  uint32_t ru_glyph = 0u;
  uint32_t sr_glyph = 0u;
  uint32_t sr_disabled_glyph = 0u;
  uint32_t ru_cluster = 0u;
  uint32_t sr_cluster = 0u;
  size_t ru_count = 0u;
  size_t sr_count = 0u;
  size_t sr_disabled_count = 0u;
  int32_t ru_advance = 0;
  int32_t sr_advance = 0;

  if (file == NULL) {
    printf("  SKIP: no language-specific shaping test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(NULL, path, 0, 32);
  ASSERT_NOT_NULL(font);
  ru_status = my_font_shape_ex(
      font, "\xD0\xB1\xD0\xB3\xD0\xB4\xD0\xBF\xD1\x82", 24, &russian,
      NULL, &ru_result);
  sr_status = my_font_shape_ex(
      font, "\xD0\xB1\xD0\xB3\xD0\xB4\xD0\xBF\xD1\x82", 24, &serbian,
      NULL, &sr_result);
  sr_disabled_status = my_font_shape_ex(
      font, "\xD0\xB1\xD0\xB3\xD0\xB4\xD0\xBF\xD1\x82", 24,
      &serbian_without_locl, NULL, &sr_disabled_result);
  if (ru_status == MY_RET_OK && sr_status == MY_RET_OK &&
      sr_disabled_status == MY_RET_OK && ru_result.count > 0u &&
      sr_result.count > 0u && sr_disabled_result.count > 0u) {
    ru_count = ru_result.count;
    sr_count = sr_result.count;
    sr_disabled_count = sr_disabled_result.count;
    ru_glyph = ru_result.glyphs[0].glyph_id;
    sr_glyph = sr_result.glyphs[0].glyph_id;
    sr_disabled_glyph = sr_disabled_result.glyphs[0].glyph_id;
    ru_cluster = ru_result.glyphs[0].cluster;
    sr_cluster = sr_result.glyphs[0].cluster;
    ru_advance = ru_result.glyphs[0].advance_x_26_6;
    sr_advance = sr_result.glyphs[0].advance_x_26_6;
  }
  my_font_shape_destroy(&sr_disabled_result);
  my_font_shape_destroy(&sr_result);
  my_font_shape_destroy(&ru_result);
  my_font_destroy(font);
  ASSERT_EQ(ru_status, MY_RET_OK);
  ASSERT_EQ(sr_status, MY_RET_OK);
  ASSERT_EQ(sr_disabled_status, MY_RET_OK);
  ASSERT_EQ(ru_count, 5u);
  ASSERT_EQ(sr_count, 5u);
  ASSERT_EQ(sr_disabled_count, 5u);
  ASSERT_EQ(ru_glyph, 795u);
  ASSERT_EQ(sr_glyph, 871u);
  ASSERT_EQ(sr_disabled_glyph, 795u);
  ASSERT_EQ(ru_cluster, 0u);
  ASSERT_EQ(sr_cluster, 0u);
  ASSERT_TRUE(ru_advance > 0);
  ASSERT_EQ(ru_advance, sr_advance);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(freetype_rtl_arabic_gsub_gpos_golden)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *path =
      "/usr/share/fonts/google-noto-vf/NotoSansArabic[wght].ttf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_font_shape_params_t params = {true, MY_FONT_SCRIPT_ARAB, "ar", NULL};
  my_font_shape_result_t result = {0};
  const uint32_t expected_glyphs[] = {74u, 11u, 71u, 37u};
  const uint32_t expected_clusters[] = {6u, 4u, 2u, 0u};
  size_t i;

  if (file == NULL) {
    printf("  SKIP: no Arabic RTL shaping test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(NULL, path, 0, 32);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape_ex(font, "\xD8\xB3\xD9\x84\xD8\xA7\xD9\x85",
                             24, &params, NULL, &result),
            MY_RET_OK);
  ASSERT_EQ(result.count, sizeof(expected_glyphs) / sizeof(expected_glyphs[0]));
  ASSERT_TRUE(result.rtl);
  ASSERT_TRUE(result.used_complex_shaping);
  for (i = 0u; i < result.count; i++) {
    ASSERT_EQ(result.glyphs[i].glyph_id, expected_glyphs[i]);
    ASSERT_EQ(result.glyphs[i].cluster, expected_clusters[i]);
    ASSERT_TRUE(result.glyphs[i].advance_x_26_6 > 0);
    ASSERT_NOT_NULL(result.glyphs[i].font);
  }
  my_font_shape_destroy(&result);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(freetype_rtl_hebrew_gpos_golden)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *path =
      "/usr/share/fonts/google-noto-vf/NotoSansHebrew[wght].ttf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_font_shape_params_t params = {true, MY_FONT_SCRIPT_HEBR, "he", NULL};
  my_font_shape_result_t result = {0};
  const uint32_t expected_glyphs[] = {23u, 124u, 55u, 96u};
  const uint32_t expected_clusters[] = {6u, 4u, 2u, 0u};
  size_t i;

  if (file == NULL) {
    printf("  SKIP: no Hebrew RTL shaping test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(NULL, path, 0, 32);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape_ex(font, "\xD7\xA9\xD7\x9C\xD7\x95\xD7\x9D",
                             24, &params, NULL, &result),
            MY_RET_OK);
  ASSERT_EQ(result.count, sizeof(expected_glyphs) / sizeof(expected_glyphs[0]));
  ASSERT_TRUE(result.rtl);
  ASSERT_TRUE(result.used_complex_shaping);
  for (i = 0u; i < result.count; i++) {
    ASSERT_EQ(result.glyphs[i].glyph_id, expected_glyphs[i]);
    ASSERT_EQ(result.glyphs[i].cluster, expected_clusters[i]);
    ASSERT_TRUE(result.glyphs[i].advance_x_26_6 > 0);
    ASSERT_NOT_NULL(result.glyphs[i].font);
  }
  my_font_shape_destroy(&result);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(freetype_rtl_arabic_marks_numbers_golden)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *path =
      "/usr/share/fonts/google-noto-vf/NotoSansArabic[wght].ttf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_font_shape_params_t params = {true, MY_FONT_SCRIPT_ARAB, "ar", NULL};
  my_font_shape_result_t marks = {0};
  my_font_shape_result_t numbers = {0};
  const uint32_t mark_glyphs[] = {368u, 69u, 368u, 79u};
  const uint32_t mark_clusters[] = {4u, 4u, 0u, 0u};
  const uint32_t number_glyphs[] = {129u, 128u, 127u, 174u,
                                    74u, 11u, 71u, 37u};
  const uint32_t number_clusters[] = {14u, 12u, 10u, 8u, 6u, 4u, 2u, 0u};
  size_t i;

  if (file == NULL) {
    printf("  SKIP: no Arabic RTL shaping test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(NULL, path, 0, 32);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape_ex(font,
                             "\xD9\x85\xD9\x8E\xD9\x84\xD9\x8E", 24,
                             &params, NULL, &marks),
            MY_RET_OK);
  ASSERT_EQ(my_font_shape_ex(font,
                             "\xD8\xB3\xD9\x84\xD8\xA7\xD9\x85"
                             "\xD8\x8C\xD9\xA1\xD9\xA2\xD9\xA3",
                             24, &params, NULL, &numbers),
            MY_RET_OK);
  ASSERT_EQ(marks.count, 4u);
  ASSERT_EQ(numbers.count, 8u);
  for (i = 0u; i < marks.count; ++i) {
    ASSERT_EQ(marks.glyphs[i].glyph_id, mark_glyphs[i]);
    ASSERT_EQ(marks.glyphs[i].cluster, mark_clusters[i]);
    ASSERT_NOT_NULL(marks.glyphs[i].font);
  }
  ASSERT_TRUE(marks.glyphs[0].advance_x_26_6 == 0);
  ASSERT_TRUE(marks.glyphs[2].advance_x_26_6 == 0);
  ASSERT_TRUE(marks.glyphs[0].offset_x_26_6 != 0 ||
              marks.glyphs[0].offset_y_26_6 != 0);
  for (i = 0u; i < numbers.count; ++i) {
    ASSERT_EQ(numbers.glyphs[i].glyph_id, number_glyphs[i]);
    ASSERT_EQ(numbers.glyphs[i].cluster, number_clusters[i]);
    ASSERT_TRUE(numbers.glyphs[i].advance_x_26_6 > 0);
    ASSERT_NOT_NULL(numbers.glyphs[i].font);
  }
  my_font_shape_destroy(&numbers);
  my_font_shape_destroy(&marks);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(freetype_rtl_variable_weight_changes_advance)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *path =
      "/usr/share/fonts/google-noto-vf/NotoSansArabic[wght].ttf";
  FILE *file = fopen(path, "rb");
  my_font_t *light;
  my_font_t *heavy;
  my_font_shape_params_t params = {true, MY_FONT_SCRIPT_ARAB, "ar", NULL};
  my_font_shape_result_t light_result = {0};
  my_font_shape_result_t heavy_result = {0};
  size_t i;
  int64_t light_advance = 0;
  int64_t heavy_advance = 0;

  if (file == NULL) {
    printf("  SKIP: no Arabic variable shaping test font\n");
    return;
  }
  fclose(file);
  light = my_font_ft_create_ex(NULL, path, 0, 300, 32);
  heavy = my_font_ft_create_ex(NULL, path, 0, 900, 32);
  ASSERT_NOT_NULL(light);
  ASSERT_NOT_NULL(heavy);
  ASSERT_EQ(my_font_shape_ex(light, "\xD8\xB3\xD9\x84\xD8\xA7\xD9\x85",
                             24, &params, NULL, &light_result),
            MY_RET_OK);
  ASSERT_EQ(my_font_shape_ex(heavy, "\xD8\xB3\xD9\x84\xD8\xA7\xD9\x85",
                             24, &params, NULL, &heavy_result),
            MY_RET_OK);
  ASSERT_EQ(light_result.count, heavy_result.count);
  ASSERT_TRUE(light_result.count > 0u);
  for (i = 0u; i < light_result.count; i++) {
    ASSERT_EQ(light_result.glyphs[i].glyph_id,
              heavy_result.glyphs[i].glyph_id);
    ASSERT_EQ(light_result.glyphs[i].cluster,
              heavy_result.glyphs[i].cluster);
    light_advance += light_result.glyphs[i].advance_x_26_6;
    heavy_advance += heavy_result.glyphs[i].advance_x_26_6;
  }
  ASSERT_TRUE(light_advance > 0);
  ASSERT_TRUE(heavy_advance > light_advance);
  my_font_shape_destroy(&heavy_result);
  my_font_shape_destroy(&light_result);
  my_font_destroy(heavy);
  my_font_destroy(light);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(freetype_feature_support_query_normalizes_disable_syntax)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *path = "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_font_shape_params_t params = {false, MY_FONT_SCRIPT_LATN, NULL,
                                   "-liga"};
  my_font_shape_support_t support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
  if (file == NULL) {
    printf("  SKIP: no shaping test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(NULL, path, 0, 32);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape_support_query(font, &params, &support), MY_RET_OK);
  ASSERT_EQ(support, MY_FONT_SHAPE_SUPPORTED);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(freetype_capability_cache_normalizes_language_tag_case)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *path = "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_font_shape_params_t params = {false, MY_FONT_SCRIPT_LATN, "ZH-CN", NULL};
  my_font_shape_support_t support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;

  if (file == NULL) {
    printf("  SKIP: no shaping test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(NULL, path, 0, 32);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape_support_query(font, &params, &support), MY_RET_OK);
  ASSERT_EQ(support, MY_FONT_SHAPE_UNSUPPORTED);
  params.language = "zh-cn";
  ASSERT_EQ(my_font_shape_support_query(font, &params, &support), MY_RET_OK);
  ASSERT_EQ(my_font_ft_shape_support_cache_hits(font), 1u);
  params.language = NULL;
  params.features = "liga=1,kern=0";
  ASSERT_EQ(my_font_shape_support_query(font, &params, &support), MY_RET_OK);
  params.features = " kern = 0 , liga = 1 ";
  ASSERT_EQ(my_font_shape_support_query(font, &params, &support), MY_RET_OK);
  ASSERT_EQ(my_font_ft_shape_support_cache_hits(font), 2u);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(freetype_required_feature_cannot_be_disabled)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *path = "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_font_shape_params_t params = {false, MY_FONT_SCRIPT_LATN, NULL, NULL};
  my_font_shape_result_t default_result = {0};
  my_font_shape_result_t disabled_result = {0};
  my_font_shape_support_t support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
  uint32_t tag;
  char disabled[6];
  size_t i;

  if (file == NULL) {
    printf("  SKIP: no shaping test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(NULL, path, 0, 32);
  ASSERT_NOT_NULL(font);
  if (my_font_ft_required_feature_count(font, &params) == 0u) {
    printf("  SKIP: shaping test font has no required LangSys feature\n");
    my_font_destroy(font);
    return;
  }
  tag = my_font_ft_required_feature_tag(font, &params, 0u);
  ASSERT_TRUE(tag != 0u);
  disabled[0] = '-';
  for (i = 0u; i < 4u; i++) {
    disabled[i + 1u] = (char)(tag >> (24u - 8u * i));
  }
  disabled[5] = '\0';
  params.features = disabled;
  ASSERT_EQ(my_font_shape_support_query(font, &params, &support), MY_RET_OK);
  ASSERT_EQ(support, MY_FONT_SHAPE_SUPPORTED);
  params.features = NULL;
  ASSERT_EQ(my_font_shape_ex(font, "office", 24, &params, NULL,
                             &default_result), MY_RET_OK);
  params.features = disabled;
  ASSERT_EQ(my_font_shape_ex(font, "office", 24, &params, NULL,
                             &disabled_result), MY_RET_OK);
  ASSERT_EQ(disabled_result.count, default_result.count);
  for (i = 0u; i < default_result.count; i++) {
    ASSERT_EQ(disabled_result.glyphs[i].glyph_id,
              default_result.glyphs[i].glyph_id);
    ASSERT_EQ(disabled_result.glyphs[i].cluster,
              default_result.glyphs[i].cluster);
    ASSERT_EQ(disabled_result.glyphs[i].advance_x_26_6,
              default_result.glyphs[i].advance_x_26_6);
    ASSERT_EQ(disabled_result.glyphs[i].offset_x_26_6,
              default_result.glyphs[i].offset_x_26_6);
    ASSERT_EQ(disabled_result.glyphs[i].offset_y_26_6,
              default_result.glyphs[i].offset_y_26_6);
  }
  my_font_shape_destroy(&disabled_result);
  my_font_shape_destroy(&default_result);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(freetype_glyph_oom_does_not_poison_cache)
{
#ifdef MYUI_FONT_FREETYPE
  const char *path = "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  shape_allocator_state_t state = {0};
  const my_allocator_t allocator = {&state, shape_alloc, shape_calloc,
                                    shape_realloc, shape_free};
  my_font_t *font;
  my_glyph_t glyph = {0};

  if (file == NULL) {
    printf("  SKIP: no shaping test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(&allocator, path, 0, 8);
  ASSERT_NOT_NULL(font);
  state.calls = 0;
  ASSERT_EQ(my_font_get_glyph(font, 'Q', 24, &glyph), MY_RET_OK);
  ASSERT_TRUE(glyph_has_coverage(&glyph));
  my_font_glyph_release(&glyph);
  state.calls = 0;
  state.fail_at = 1;
  memset(&glyph, 0, sizeof(glyph));
  ASSERT_EQ(my_font_get_glyph(font, 'R', 24, &glyph), MY_RET_OOM);
  ASSERT_TRUE(glyph.bitmap == NULL);
  state.fail_at = 0;
  memset(&glyph, 0, sizeof(glyph));
  ASSERT_EQ(my_font_get_glyph(font, 'R', 24, &glyph), MY_RET_OK);
  ASSERT_TRUE(glyph_has_coverage(&glyph));
  my_font_glyph_release(&glyph);
  memset(&glyph, 0, sizeof(glyph));
  my_font_destroy(font);
  ASSERT_EQ(state.live, 0u);
#else
  printf("  SKIP: FreeType is unavailable\n");
#endif
}

TEST(freetype_glyph_lease_survives_cache_eviction)
{
#ifdef MYUI_FONT_FREETYPE
  const char *path = "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_glyph_t first = {0};
  my_glyph_t second = {0};
  uint8_t first_sample;

  if (file == NULL) {
    printf("  SKIP: no FreeType test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(NULL, path, 0, 1u);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_get_glyph(font, 'Q', 24, &first), MY_RET_OK);
  ASSERT_TRUE(glyph_has_coverage(&first));
  first_sample = first.bitmap[0];
  ASSERT_EQ(my_font_get_glyph(font, 'R', 24, &second), MY_RET_OK);
  ASSERT_TRUE(glyph_has_coverage(&second));
  ASSERT_EQ(first.bitmap[0], first_sample);
  ASSERT_TRUE(glyph_has_coverage(&first));
  my_font_glyph_release(&second);
  my_font_glyph_release(&first);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType is unavailable\n");
#endif
}

TEST(freetype_destroy_is_deferred_until_glyph_lease_release)
{
#ifdef MYUI_FONT_FREETYPE
  const char *path = "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  shape_allocator_state_t state = {0};
  const my_allocator_t allocator = {&state, shape_alloc, shape_calloc,
                                    shape_realloc, shape_free};
  my_font_t *font;
  my_glyph_t glyph = {0};

  if (file == NULL) {
    printf("  SKIP: no FreeType test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(&allocator, path, 0, 1u);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_get_glyph(font, 'Q', 24, &glyph), MY_RET_OK);
  ASSERT_TRUE(glyph_has_coverage(&glyph));
  my_font_destroy(font);
  ASSERT_TRUE(state.live > 0u);
  ASSERT_TRUE(glyph_has_coverage(&glyph));
  my_font_glyph_release(&glyph);
  ASSERT_EQ(state.live, 0u);
#else
  printf("  SKIP: FreeType is unavailable\n");
#endif
}

TEST(freetype_glyph_lease_overflow_is_bounded)
{
#ifdef MYUI_FONT_FREETYPE
  const char *path = "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_glyph_t first = {0};
  my_glyph_t second = {0};
  my_glyph_t third = {0};

  if (file == NULL) {
    printf("  SKIP: no FreeType test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(NULL, path, 0, 1u);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_get_glyph(font, 'Q', 24, &first), MY_RET_OK);
  ASSERT_EQ(my_font_get_glyph(font, 'R', 24, &second), MY_RET_OK);
  ASSERT_EQ(my_font_get_glyph(font, 'S', 24, &third), MY_RET_OOM);
  ASSERT_TRUE(third.bitmap == NULL);
  my_font_glyph_release(&second);
  ASSERT_EQ(my_font_get_glyph(font, 'S', 24, &third), MY_RET_OK);
  my_font_glyph_release(&third);
  my_font_glyph_release(&first);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType is unavailable\n");
#endif
}

TEST(freetype_variable_font_oom_rolls_back)
{
#ifdef MYUI_FONT_FREETYPE
  const char *path = "/usr/share/fonts/abattis-cantarell-vf-fonts/Cantarell-VF.otf";
  FILE *file = fopen(path, "rb");
  shape_allocator_state_t state = {0};
  const my_allocator_t allocator = {&state, shape_alloc, shape_calloc,
                                    shape_realloc, shape_free};
  my_font_t *font;

  if (file == NULL) {
    printf("  SKIP: no variable test font\n");
    return;
  }
  fclose(file);
  state.fail_at = 2;
  font = my_font_ft_create_ex(&allocator, path, 0, 400, 8);
  ASSERT_TRUE(font == NULL);
  ASSERT_EQ(state.live, 0u);
#else
  printf("  SKIP: FreeType is unavailable\n");
#endif
}

TEST(freetype_shaping_attaches_variation_selector_to_base)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *path = "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_font_shape_result_t result = {0};
  if (file == NULL) {
    printf("  SKIP: no shaping test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(NULL, path, 0, 32);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape(font, "a\xEF\xB8\x8E" "b\xEF\xB8\x8F" "c", 24, false, NULL,
                          &result), MY_RET_OK);
  ASSERT_EQ(result.count, 3u);
  ASSERT_EQ(result.glyphs[0].cluster, 0u);
  ASSERT_EQ(result.glyphs[1].cluster, 4u);
  ASSERT_EQ(result.glyphs[2].cluster, 8u);
  my_font_shape_destroy(&result);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(freetype_shaping_preserves_zwj_sequence)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *path = "/usr/share/fonts/google-noto-color-emoji-fonts/Noto-COLRv1.ttf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_font_shape_result_t result = {0};
  if (file == NULL) {
    printf("  SKIP: no emoji shaping test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(NULL, path, 0, 8);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape(font,
                          "\xF0\x9F\x91\xA9" "\xE2\x80\x8D"
                          "\xF0\x9F\x92\xBB",
                          24, false, NULL, &result), MY_RET_OK);
  ASSERT_EQ(result.count, 1u);
  ASSERT_EQ(result.glyphs[0].cluster, 0u);
  ASSERT_TRUE(result.glyphs[0].advance_x_26_6 > 0);
  my_font_shape_destroy(&result);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(freetype_shaping_selects_cjk_variation_glyph)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *path = "/usr/share/fonts/google-noto-sans-cjk-vf-fonts/NotoSansCJK-VF.ttc";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_font_shape_result_t base = {0};
  my_font_shape_result_t variant = {0};
  if (file == NULL) {
    printf("  SKIP: no CJK variation test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(NULL, path, 0, 8);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape(font, "\xE9\x82\x89", 24, false, NULL, &base),
            MY_RET_OK);
  ASSERT_EQ(my_font_shape(font,
                          "\xE9\x82\x89" "\xF3\xA0\x84\x81",
                          24, false, NULL, &variant), MY_RET_OK);
  ASSERT_EQ(base.count, 1u);
  ASSERT_EQ(variant.count, 1u);
  ASSERT_EQ(base.glyphs[0].cluster, 0u);
  ASSERT_EQ(variant.glyphs[0].cluster, 0u);
  ASSERT_TRUE(base.glyphs[0].glyph_id != variant.glyphs[0].glyph_id);
  my_font_shape_destroy(&variant);
  my_font_shape_destroy(&base);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(font_chain_selects_face_with_cjk_variation_glyph)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *path =
      "/usr/share/fonts/google-noto-sans-cjk-vf-fonts/NotoSansCJK-VF.ttc";
  const my_font_source_t sources[] = {{path, 1}, {path, 0}};
  my_font_t *fallback;
  my_font_t *chain;
  my_font_shape_result_t expected = {0};
  my_font_shape_result_t actual = {0};
  FILE *file = fopen(path, "rb");

  if (file == NULL) {
    printf("  SKIP: no CJK variation test font\n");
    return;
  }
  fclose(file);
  fallback = my_font_ft_create(NULL, path, 0, 8);
  chain = my_font_create_chain_ex(NULL, sources, 2u, 8u);
  ASSERT_NOT_NULL(fallback);
  ASSERT_NOT_NULL(chain);
  ASSERT_EQ(my_font_shape(fallback, "\xE9\x82\x89" "\xF3\xA0\x84\x81",
                          24, false, NULL, &expected),
            MY_RET_OK);
  ASSERT_EQ(my_font_shape(chain, "\xE9\x82\x89" "\xF3\xA0\x84\x81", 24,
                          false, NULL, &actual),
            MY_RET_OK);
  ASSERT_EQ(expected.count, 1u);
  ASSERT_EQ(actual.count, 1u);
  ASSERT_EQ(actual.glyphs[0].glyph_id, expected.glyphs[0].glyph_id);
  ASSERT_EQ(actual.glyphs[0].cluster, 0u);
  my_font_shape_destroy(&actual);
  my_font_shape_destroy(&expected);
  my_font_destroy(chain);
  my_font_destroy(fallback);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(shaped_glyph_id_rasterization_is_separate_from_unicode)
{
#ifdef MYUI_FONT_FREETYPE
  const char *path = "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  my_font_t *font;
  my_glyph_t glyph;
  if (file == NULL) {
    printf("  SKIP: no shaping test font\n");
    return;
  }
  fclose(file);
  font = my_font_ft_create(NULL, path, 0, 32);
  ASSERT_NOT_NULL(font);
#ifdef MYUI_FONT_HARFBUZZ
  my_font_shape_result_t shaped = {0};
  ASSERT_EQ(my_font_shape(font, "office", 24, false, NULL, &shaped),
            MY_RET_OK);
  ASSERT_TRUE(shaped.count > 0);
  ASSERT_EQ(my_font_get_glyph_id(font, shaped.glyphs[0].glyph_id, 24, &glyph),
            MY_RET_OK);
  ASSERT_TRUE(glyph.advance > 0);
  ASSERT_TRUE(glyph_has_coverage(&glyph));
  ASSERT_EQ(my_font_get_glyph_id(font, 0u, 24, &glyph), MY_RET_NOT_FOUND);
  my_font_glyph_release(&glyph);
  my_font_shape_destroy(&shaped);
#else
  ASSERT_EQ(my_font_get_glyph_id(font, 1u, 24, &glyph), MY_RET_OK);
  ASSERT_TRUE(glyph.advance > 0);
  my_font_glyph_release(&glyph);
#endif
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType is unavailable\n");
#endif
}

TEST(font_chain_preserves_face_identity_in_shaped_runs)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const CjkFontCandidate *cjk = find_cjk_font();
  const char *latin_path =
      "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  const my_font_source_t sources[] = {{latin_path, 0},
                                      {cjk != NULL ? cjk->path : NULL,
                                       cjk != NULL ? cjk->face_index : 0}};
  my_font_shape_result_t result = {0};
  my_font_t *font;
  FILE *file = fopen(latin_path, "rb");
  size_t i;

  if (file == NULL || cjk == NULL) {
    if (file != NULL) fclose(file);
    printf("  SKIP: no Latin/CJK shaping font pair\n");
    return;
  }
  fclose(file);
  font = my_font_create_chain_ex(NULL, sources, 2, 32);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape(font, "office\xE7\x9F\xAD", 24, false, NULL,
                          &result),
            MY_RET_OK);
  ASSERT_TRUE(result.count > 0);
  ASSERT_TRUE(result.used_complex_shaping);
  for (i = 0; i < result.count; i++) {
    ASSERT_NOT_NULL(result.glyphs[i].font);
    if (result.glyphs[i].cluster < 6u) {
      ASSERT_TRUE(result.glyphs[i].font == result.glyphs[0].font);
    } else {
      ASSERT_TRUE(result.glyphs[i].font != result.glyphs[0].font);
    }
  }
  my_font_shape_destroy(&result);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(font_chain_aggregates_script_capability)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *latin_path =
      "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(latin_path, "rb");
  my_font_source_t source;
  my_font_t *font;
  my_font_shape_params_t params = {false, MY_FONT_SCRIPT_LATN, NULL, NULL};
  my_font_shape_support_t support = MY_FONT_SHAPE_SUPPORT_UNKNOWN;
  if (file == NULL) {
    printf("  SKIP: no shaping test font\n");
    return;
  }
  fclose(file);
  source.path = latin_path;
  source.face_index = 0;
  font = my_font_create_chain_ex(NULL, &source, 1u, 32u);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape_support_query(font, &params, &support), MY_RET_OK);
  ASSERT_EQ(support, MY_FONT_SHAPE_SUPPORTED);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(font_chain_rejects_excessive_source_count_before_allocation)
{
  my_font_source_t sources[MY_FONT_CHAIN_MAX_SOURCES + 1u] = {{0}};
  shape_allocator_state_t state = {0};
  const my_allocator_t allocator = {&state, shape_alloc, shape_calloc,
                                    shape_realloc, shape_free};

  ASSERT_TRUE(my_font_create_chain_ex(
                  &allocator, sources, MY_FONT_CHAIN_MAX_SOURCES + 1u, 16u) ==
              NULL);
  ASSERT_EQ(state.calls, 0u);
}

TEST(font_chain_prefers_shape_capable_face_for_explicit_features)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *first_path =
      "/usr/share/fonts/adobe-source-code-pro-fonts/SourceCodePro-Regular.otf";
  const char *second_path =
      "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *first_file = fopen(first_path, "rb");
  FILE *second_file = fopen(second_path, "rb");
  const my_font_source_t sources[] = {{first_path, 0}, {second_path, 0}};
  my_font_shape_params_t params = {false, MY_FONT_SCRIPT_LATN, NULL,
                                   "liga=1"};
  my_font_shape_result_t result = {0};
  my_font_t *chain;

  if (first_file == NULL || second_file == NULL) {
    if (first_file != NULL) fclose(first_file);
    if (second_file != NULL) fclose(second_file);
    printf("  SKIP: no explicit-feature fallback font pair\n");
    return;
  }
  fclose(first_file);
  fclose(second_file);
  chain = my_font_create_chain_ex(NULL, sources, 2u, 32u);
  ASSERT_NOT_NULL(chain);
  ASSERT_EQ(my_font_shape_ex(chain, "office", 24, &params, NULL, &result),
            MY_RET_OK);
  /* Cantarell's liga feature produces the fi ligature; Source Code Pro is
   * first in the chain and still covers every codepoint. */
  ASSERT_EQ(result.count, 5u);
  my_font_shape_destroy(&result);
  my_font_destroy(chain);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(font_chain_shaping_rolls_back_allocator_failures)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const CjkFontCandidate *cjk = find_cjk_font();
  const char *latin_path =
      "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  const my_font_source_t sources[] = {{latin_path, 0},
                                      {cjk != NULL ? cjk->path : NULL,
                                       cjk != NULL ? cjk->face_index : 0}};
  shape_allocator_state_t state = {0};
  const my_allocator_t allocator = {&state, shape_alloc, shape_calloc,
                                    shape_realloc, shape_free};
  my_font_shape_result_t result = {0};
  my_font_t *font;
  FILE *file = fopen(latin_path, "rb");
  size_t successful_calls;
  size_t fail_at;

  if (file == NULL || cjk == NULL) {
    if (file != NULL) fclose(file);
    printf("  SKIP: no Latin/CJK shaping font pair\n");
    return;
  }
  fclose(file);
  font = my_font_create_chain_ex(NULL, sources, 2, 32);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape(font, "office\xE7\x9F\xAD", 24, false,
                          &allocator, &result), MY_RET_OK);
  successful_calls = state.calls;
  ASSERT_TRUE(successful_calls > 0);
  my_font_shape_destroy(&result);
  ASSERT_EQ(state.live, 0u);

  for (fail_at = 1; fail_at <= successful_calls; fail_at++) {
    state.calls = 0;
    state.fail_at = fail_at;
    ASSERT_EQ(my_font_shape(font, "office\xE7\x9F\xAD", 24, false,
                            &allocator, &result), MY_RET_OOM);
    ASSERT_EQ(result.count, 0u);
    ASSERT_TRUE(result.glyphs == NULL);
    ASSERT_EQ(state.live, 0u);
  }
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(font_chain_rtl_reverses_cross_face_runs)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const CjkFontCandidate *cjk = find_cjk_font();
  const char *latin_path =
      "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  const my_font_source_t sources[] = {{latin_path, 0},
                                      {cjk != NULL ? cjk->path : NULL,
                                       cjk != NULL ? cjk->face_index : 0}};
  my_font_shape_result_t result = {0};
  my_font_t *font;
  FILE *file = fopen(latin_path, "rb");
  size_t i;
  bool saw_latin = false;
  bool saw_cjk_after_latin = false;

  if (file == NULL || cjk == NULL) {
    if (file != NULL) fclose(file);
    printf("  SKIP: no Latin/CJK shaping font pair\n");
    return;
  }
  fclose(file);
  font = my_font_create_chain_ex(NULL, sources, 2, 32);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape(font, "\xE7\x9F\xADoffice", 24, true, NULL,
                          &result), MY_RET_OK);
  ASSERT_TRUE(result.count > 0);
  for (i = 0; i < result.count; i++) {
    if (result.glyphs[i].cluster >= 3u) saw_latin = true;
    if (saw_latin && result.glyphs[i].cluster < 3u) {
      saw_cjk_after_latin = true;
    }
  }
  ASSERT_TRUE(saw_latin);
  ASSERT_TRUE(saw_cjk_after_latin);
  my_font_shape_destroy(&result);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(font_chain_direct_shape_provider_initializes_result)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *path = "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  FILE *file = fopen(path, "rb");
  const my_font_source_t source = {path, 0};
  my_font_shape_params_t params = {true, MY_FONT_SCRIPT_LATN, "en", NULL};
  my_font_shape_result_t result = {0};
  my_font_t *font;

  if (file == NULL) {
    printf("  SKIP: no font-chain shaping test font\n");
    return;
  }
  fclose(file);
  font = my_font_create_chain_ex(NULL, &source, 1u, 16u);
  ASSERT_NOT_NULL(font);
  ASSERT_NOT_NULL(font->vtable);
  ASSERT_NOT_NULL(font->vtable->shape_ex);
  ASSERT_EQ(font->vtable->shape_ex(font, "ab", 24, &params, NULL, &result),
            MY_RET_OK);
  ASSERT_TRUE(result.rtl);
  ASSERT_EQ(result.count, 2u);
  ASSERT_NOT_NULL(result.glyphs);
  my_font_shape_destroy(&result);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(font_chain_keeps_combining_cluster_on_one_face)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *primary_path =
      "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  const char *fallback_path =
      "/usr/share/fonts/google-noto-vf/NotoSans[wght].ttf";
  FILE *primary_file = fopen(primary_path, "rb");
  FILE *fallback_file = fopen(fallback_path, "rb");
  const my_font_source_t sources[] = {{primary_path, 0}, {fallback_path, 0}};
  my_font_shape_result_t result = {0};
  my_font_t *font;

  if (primary_file == NULL || fallback_file == NULL) {
    if (primary_file != NULL) fclose(primary_file);
    if (fallback_file != NULL) fclose(fallback_file);
    printf("  SKIP: no combining-cluster font pair\n");
    return;
  }
  fclose(primary_file);
  fclose(fallback_file);
  font = my_font_create_chain_ex(NULL, sources, 2u, 16u);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape(font, "a\xCC\x85", 24, false, NULL, &result),
            MY_RET_OK);
  ASSERT_EQ(result.count, 2u);
  ASSERT_EQ(result.glyphs[0].cluster, 0u);
  ASSERT_EQ(result.glyphs[1].cluster, 0u);
  ASSERT_TRUE(result.glyphs[0].font == result.glyphs[1].font);
  ASSERT_TRUE(result.glyphs[1].advance_x_26_6 == 0);
  my_font_shape_destroy(&result);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(font_chain_measure_keeps_combining_cluster_width)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *primary_path =
      "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  const char *fallback_path =
      "/usr/share/fonts/google-noto-vf/NotoSans[wght].ttf";
  FILE *primary_file = fopen(primary_path, "rb");
  FILE *fallback_file = fopen(fallback_path, "rb");
  const my_font_source_t sources[] = {{primary_path, 0}, {fallback_path, 0}};
  my_font_t *chain;
  my_font_t *fallback;
  int32_t chain_width = 0;
  int32_t fallback_width = 0;

  if (primary_file == NULL || fallback_file == NULL) {
    if (primary_file != NULL) fclose(primary_file);
    if (fallback_file != NULL) fclose(fallback_file);
    printf("  SKIP: no combining-cluster font pair\n");
    return;
  }
  fclose(primary_file);
  fclose(fallback_file);
  chain = my_font_create_chain_ex(NULL, sources, 2u, 16u);
  fallback = my_font_ft_create(NULL, fallback_path, 0, 16u);
  ASSERT_NOT_NULL(chain);
  ASSERT_NOT_NULL(fallback);
  ASSERT_EQ(my_font_measure(fallback, "a\xCC\x85", 24, &fallback_width,
                            NULL),
            MY_RET_OK);
  ASSERT_EQ(my_font_measure(chain, "a\xCC\x85", 24, &chain_width, NULL),
            MY_RET_OK);
  ASSERT_EQ(chain_width, fallback_width);
  my_font_destroy(fallback);
  my_font_destroy(chain);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST(font_chain_keeps_zwj_sequence_on_one_face)
{
#if defined(MYUI_FONT_FREETYPE) && defined(MYUI_FONT_HARFBUZZ)
  const char *primary_path =
      "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf";
  const char *fallback_path =
      "/usr/share/fonts/google-noto-color-emoji-fonts/Noto-COLRv1.ttf";
  FILE *primary_file = fopen(primary_path, "rb");
  FILE *fallback_file = fopen(fallback_path, "rb");
  const my_font_source_t sources[] = {{primary_path, 0}, {fallback_path, 0}};
  my_font_shape_result_t result = {0};
  my_font_t *font;

  if (primary_file == NULL || fallback_file == NULL) {
    if (primary_file != NULL) fclose(primary_file);
    if (fallback_file != NULL) fclose(fallback_file);
    printf("  SKIP: no ZWJ-cluster font pair\n");
    return;
  }
  fclose(primary_file);
  fclose(fallback_file);
  font = my_font_create_chain_ex(NULL, sources, 2u, 16u);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_font_shape(font,
                          "\xF0\x9F\x91\xA9" "\xE2\x80\x8D"
                          "\xF0\x9F\x92\xBB",
                          24, false, NULL, &result),
            MY_RET_OK);
  ASSERT_EQ(result.count, 1u);
  ASSERT_EQ(result.glyphs[0].cluster, 0u);
  ASSERT_TRUE(result.glyphs[0].advance_x_26_6 > 0);
  ASSERT_TRUE(result.glyphs[0].font != NULL);
  my_font_shape_destroy(&result);
  my_font_destroy(font);
#else
  printf("  SKIP: FreeType/HarfBuzz shaping is unavailable\n");
#endif
}

TEST_MAIN_BEGIN()
    RUN_TEST(font_public_api_defaults_missing_metric_slots);
    RUN_TEST(font_glyph_wrappers_rollback_failed_provider_output);
    RUN_TEST(utf8_decodes_chinese_codepoints);
    RUN_TEST(utf8_rejects_non_scalar_and_truncated_sequences);
    RUN_TEST(bitmap_variation_selector_has_no_standalone_glyph_or_advance);
    RUN_TEST(bitmap_destroy_is_deferred_until_glyph_lease_release);
    RUN_TEST(font_shape_cleans_partial_provider_results);
    RUN_TEST(font_shape_ex_forwards_script_language_and_features);
    RUN_TEST(font_shape_rejects_oversized_provider_result_transactionally);
    RUN_TEST(freetype_provider_rejects_oversized_direct_shape_input);
    RUN_TEST(freetype_shared_face_operations_are_thread_safe);
    RUN_TEST(stb_shared_face_operations_are_thread_safe);
    RUN_TEST(font_shape_support_query_is_explicit_and_normalized);
    RUN_TEST(font_shape_support_query_reports_unknown_without_provider);
    RUN_TEST(font_shape_ex_falls_back_from_unsupported_language_system);
    RUN_TEST(font_shape_ex_falls_back_from_unsupported_script);
    RUN_TEST(font_shape_ex_rejects_explicitly_unsupported_features);
    RUN_TEST(font_features_normalize_resolves_duplicate_tags);
    RUN_TEST(font_features_normalize_makes_order_equivalent);
    RUN_TEST(font_features_normalize_splits_overlapping_ranges);
    RUN_TEST(font_features_normalize_rejects_invalid_or_small_output);
    RUN_TEST(font_shape_ex_rejects_oversized_feature_parameters);
    RUN_TEST(font_shape_ex_rejects_invalid_feature_list_before_provider);
    RUN_TEST(font_shape_ex_rejects_more_than_feature_policy_limit);
    RUN_TEST(font_shape_rejects_oversized_text_before_provider);
    RUN_TEST(freetype_direct_measure_rejects_oversized_text);
    RUN_TEST(stb_direct_measure_rejects_oversized_text);
    RUN_TEST(font_measure_saturates_width_instead_of_wrapping);
    RUN_TEST(stb_glyph_oom_does_not_poison_cache);
    RUN_TEST(stb_glyph_lease_survives_cache_eviction);
    RUN_TEST(stb_destroy_is_deferred_until_glyph_lease_release);
    RUN_TEST(stb_glyph_lease_overflow_is_bounded);
    RUN_TEST(stb_ttc_selects_requested_face);
    RUN_TEST(stb_rejects_oversized_file_before_allocation);
    RUN_TEST(stb_rejects_truncated_ttc_header);
    RUN_TEST(stb_rejects_out_of_range_table_offset);
    RUN_TEST(stb_rejects_short_required_table);
    RUN_TEST(stb_rejects_out_of_range_cmap_glyph_index);
    RUN_TEST(stb_rejects_short_glyph_record);
    RUN_TEST(stb_rejects_out_of_range_simple_glyph_instruction);
    RUN_TEST(stb_rejects_truncated_simple_glyph_coordinates);
    RUN_TEST(stb_rejects_out_of_range_component_glyph);
    RUN_TEST(stb_rejects_component_cycle);
    RUN_TEST(stb_accepts_deep_component_chain_without_recursion);
    RUN_TEST(stb_rejects_out_of_range_compound_instructions);
    RUN_TEST(stb_rejects_truncated_cff_table);
    RUN_TEST(stb_loads_bounded_cff_font);
    RUN_TEST(stb_loads_bounded_cid_cff_font);
    RUN_TEST(stb_rejects_invalid_cid_font_dict_private_data);
    RUN_TEST(stb_rejects_malformed_type2_charstrings);
    RUN_TEST(stb_rejects_malformed_cff_dict_operands);
    RUN_TEST(cjk_ttc_face_rasterizes_chinese_glyphs);
    RUN_TEST(optional_opentype_shaping_has_explicit_fallback);
    RUN_TEST(freetype_script_capability_query);
    RUN_TEST(freetype_language_specific_locl_golden);
    RUN_TEST(freetype_rtl_arabic_gsub_gpos_golden);
    RUN_TEST(freetype_rtl_hebrew_gpos_golden);
    RUN_TEST(freetype_rtl_arabic_marks_numbers_golden);
    RUN_TEST(freetype_rtl_variable_weight_changes_advance);
    RUN_TEST(freetype_feature_support_query_normalizes_disable_syntax);
    RUN_TEST(freetype_capability_cache_normalizes_language_tag_case);
    RUN_TEST(freetype_required_feature_cannot_be_disabled);
    RUN_TEST(freetype_glyph_oom_does_not_poison_cache);
    RUN_TEST(freetype_glyph_lease_survives_cache_eviction);
    RUN_TEST(freetype_destroy_is_deferred_until_glyph_lease_release);
    RUN_TEST(freetype_glyph_lease_overflow_is_bounded);
    RUN_TEST(freetype_variable_font_oom_rolls_back);
    RUN_TEST(freetype_shaping_attaches_variation_selector_to_base);
    RUN_TEST(freetype_shaping_preserves_zwj_sequence);
    RUN_TEST(freetype_shaping_selects_cjk_variation_glyph);
    RUN_TEST(font_chain_selects_face_with_cjk_variation_glyph);
    RUN_TEST(shaped_glyph_id_rasterization_is_separate_from_unicode);
    RUN_TEST(font_chain_preserves_face_identity_in_shaped_runs);
    RUN_TEST(font_chain_aggregates_script_capability);
    RUN_TEST(font_chain_rejects_excessive_source_count_before_allocation);
    RUN_TEST(font_chain_prefers_shape_capable_face_for_explicit_features);
    RUN_TEST(font_chain_shaping_rolls_back_allocator_failures);
    RUN_TEST(font_chain_rtl_reverses_cross_face_runs);
    RUN_TEST(font_chain_direct_shape_provider_initializes_result);
    RUN_TEST(font_chain_keeps_combining_cluster_on_one_face);
    RUN_TEST(font_chain_measure_keeps_combining_cluster_width);
    RUN_TEST(font_chain_keeps_zwj_sequence_on_one_face);
TEST_MAIN_END()
