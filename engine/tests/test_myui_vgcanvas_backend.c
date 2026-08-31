#include "test_framework.h"

#include <string.h>

#include "myr/my_gl.h"
#include "myr/my_lcd_mem.h"
#include "myr/my_vgcanvas_gles2.h"
#include "myr/my_vgcanvas_quality_transaction.h"
#include "myr/my_vgcanvas_soft.h"
#include "myr/my_vgcanvas_vulkan.h"

typedef struct mock_gl_t {
  my_gl_t gl;
  float textured_vertices[24];
  int32_t textured_count;
  uint32_t next_program;
  uint32_t next_texture;
  const uint8_t* uploaded_alpha[8];
  int32_t uploaded_alpha_count;
  bool last_image_filter_linear;
  int32_t image_filter_call_count;
  int32_t viewport_w;
  int32_t viewport_h;
  float resolution_w;
  float resolution_h;
  bool multisample_enabled;
  bool multisample_available;
  int32_t multisample_calls;
} mock_gl_t;

static void mock_viewport(void* ctx, int32_t w, int32_t h) {
  mock_gl_t* mock = (mock_gl_t*)ctx;
  mock->viewport_w = w;
  mock->viewport_h = h;
}

static void mock_enable_scissor(void* ctx, bool enabled) {
  (void)ctx;
  (void)enabled;
}

static void mock_scissor(void* ctx, int32_t x, int32_t y, int32_t w,
                          int32_t h) {
  (void)ctx;
  (void)x;
  (void)y;
  (void)w;
  (void)h;
}

static uint32_t mock_create_program(void* ctx, const char* vertex_source,
                                    const char* fragment_source) {
  mock_gl_t* mock = (mock_gl_t*)ctx;
  (void)vertex_source;
  (void)fragment_source;
  return ++mock->next_program;
}

static void mock_delete_program(void* ctx, uint32_t program) {
  (void)ctx;
  (void)program;
}

static void mock_use_program(void* ctx, uint32_t program) {
  (void)ctx;
  (void)program;
}

static void mock_uniform2f(void* ctx, uint32_t program, const char* name,
                           float a, float b) {
  mock_gl_t* mock = (mock_gl_t*)ctx;
  (void)program;
  if (strcmp(name, "u_resolution") == 0) {
    mock->resolution_w = a;
    mock->resolution_h = b;
  }
}

static void mock_uniform4f(void* ctx, uint32_t program, const char* name,
                           float r, float g, float b, float a) {
  (void)ctx;
  (void)program;
  (void)name;
  (void)r;
  (void)g;
  (void)b;
  (void)a;
}

static void mock_draw_arrays(void* ctx, uint32_t program, const float* xy,
                             int32_t count) {
  (void)ctx;
  (void)program;
  (void)xy;
  (void)count;
}

static uint32_t mock_create_texture_rgba(void* ctx, const uint8_t* rgba,
                                         int32_t w, int32_t h) {
  (void)ctx;
  (void)rgba;
  (void)w;
  (void)h;
  return 1;
}

static uint32_t mock_create_texture_rgba_filtered(void* ctx,
                                                  const uint8_t* rgba,
                                                  int32_t w, int32_t h,
                                                  bool linear) {
  mock_gl_t* mock = (mock_gl_t*)ctx;
  (void)rgba;
  (void)w;
  (void)h;
  mock->last_image_filter_linear = linear;
  mock->image_filter_call_count++;
  return ++mock->next_texture;
}

static uint32_t mock_create_texture(void* ctx, const uint8_t* alpha, int32_t w,
                                    int32_t h) {
  mock_gl_t* mock = (mock_gl_t*)ctx;
  (void)w;
  (void)h;
  if (mock->uploaded_alpha_count <
      (int32_t)(sizeof(mock->uploaded_alpha) /
                sizeof(mock->uploaded_alpha[0]))) {
    mock->uploaded_alpha[mock->uploaded_alpha_count++] = alpha;
  }
  return ++mock->next_texture;
}

static void mock_delete_texture(void* ctx, uint32_t texture) {
  (void)ctx;
  (void)texture;
}

static void mock_draw_textured(void* ctx, uint32_t program, uint32_t texture,
                               const float* xyuv, int32_t count) {
  mock_gl_t* mock = (mock_gl_t*)ctx;
  (void)program;
  (void)texture;
  ASSERT_TRUE(count <= 6);
  memcpy(mock->textured_vertices, xyuv,
         (size_t)count * 4u * sizeof(float));
  mock->textured_count = count;
}

static void mock_set_multisample(void* ctx, bool enabled) {
  mock_gl_t* mock = (mock_gl_t*)ctx;
  mock->multisample_enabled = enabled;
  mock->multisample_calls++;
}

static bool mock_has_multisample(void* ctx) {
  return ((mock_gl_t*)ctx)->multisample_available;
}

static void mock_gl_init(mock_gl_t* mock) {
  memset(mock, 0, sizeof(*mock));
  mock->gl.viewport = mock_viewport;
  mock->gl.enable_scissor = mock_enable_scissor;
  mock->gl.scissor = mock_scissor;
  mock->gl.create_program = mock_create_program;
  mock->gl.delete_program = mock_delete_program;
  mock->gl.use_program = mock_use_program;
  mock->gl.uniform2f = mock_uniform2f;
  mock->gl.uniform4f = mock_uniform4f;
  mock->gl.draw_arrays_triangles = mock_draw_arrays;
  mock->gl.create_texture = mock_create_texture;
  mock->gl.create_texture_rgba = mock_create_texture_rgba;
  mock->gl.create_texture_rgba_filtered = mock_create_texture_rgba_filtered;
  mock->gl.delete_texture = mock_delete_texture;
  mock->gl.draw_textured_quads = mock_draw_textured;
  mock->gl.set_multisample = mock_set_multisample;
  mock->gl.ctx = mock;
}

typedef struct failing_canvas_t {
  my_vgcanvas_t base;
  bool fail;
  int32_t calls;
  int32_t filter_calls;
} failing_canvas_t;

static my_ret_t failing_set_antialias(my_vgcanvas_t* vg, int level) {
  failing_canvas_t* canvas = (failing_canvas_t*)vg;
  (void)level;
  canvas->calls++;
  return canvas->fail ? MY_RET_FAIL : MY_RET_OK;
}

static my_ret_t failing_set_scale_filter(my_vgcanvas_t* vg,
                                         my_scale_filter_t filter) {
  failing_canvas_t* canvas = (failing_canvas_t*)vg;
  (void)filter;
  canvas->filter_calls++;
  return canvas->fail ? MY_RET_FAIL : MY_RET_OK;
}

static const my_vgcanvas_vtable_t s_failing_vtable = {
    .set_antialias_level = failing_set_antialias,
    .set_scale_filter = failing_set_scale_filter};

typedef struct test_font_t {
  my_font_t base;
  const uint8_t* bitmap;
  const uint8_t* shaped_bitmap;
} test_font_t;

static my_ret_t test_font_measure(my_font_t* font, const char* text,
                                  int32_t size, int32_t* w, int32_t* h) {
  (void)font;
  if (text == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (w != NULL) {
    *w = size;
  }
  if (h != NULL) {
    *h = size;
  }
  return MY_RET_OK;
}

static my_ret_t test_font_get_glyph(my_font_t* font, uint32_t codepoint,
                                    int32_t size, my_glyph_t* glyph) {
  test_font_t* test_font = (test_font_t*)font;
  (void)codepoint;
  if (glyph == NULL || size <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  glyph->bitmap = test_font->bitmap;
  glyph->w = 1;
  glyph->h = 1;
  glyph->bearing_x = 0;
  glyph->bearing_y = 1;
  glyph->advance = size;
  return MY_RET_OK;
}

static my_ret_t test_font_shape(my_font_t* font, const char* text,
                                int32_t size, bool rtl,
                                const my_allocator_t* allocator,
                                my_font_shape_result_t* result) {
  (void)font;
  (void)rtl;
  if (text == NULL || text[0] == '\0' || size <= 0 || result == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  result->allocator = allocator;
  result->glyphs = (my_font_shape_glyph_t*)my_mem_alloc(
      allocator, sizeof(my_font_shape_glyph_t));
  if (result->glyphs == NULL) {
    return MY_RET_OOM;
  }
  result->count = 1;
  result->glyphs[0].glyph_id = 7;
  result->glyphs[0].cluster = 0;
  result->glyphs[0].advance_x_26_6 = 3 * 64;
  result->glyphs[0].offset_x_26_6 = 1 * 64;
  result->glyphs[0].offset_y_26_6 = 0;
  return MY_RET_OK;
}

static my_ret_t test_font_get_glyph_id(my_font_t* font, uint32_t glyph_id,
                                       int32_t size, my_glyph_t* glyph) {
  test_font_t* test_font = (test_font_t*)font;
  if (glyph_id != 7 || glyph == NULL || size <= 0) {
    return MY_RET_NOT_FOUND;
  }
  glyph->bitmap = test_font->shaped_bitmap;
  glyph->w = 1;
  glyph->h = 1;
  glyph->bearing_x = 0;
  glyph->bearing_y = 1;
  glyph->advance = 99;
  return MY_RET_OK;
}

static int32_t test_font_ascent(my_font_t* font, int32_t size) {
  (void)font;
  return size;
}

static int32_t test_font_descent(my_font_t* font, int32_t size) {
  (void)font;
  (void)size;
  return 0;
}

static int32_t test_font_line_height(my_font_t* font, int32_t size) {
  (void)font;
  return size;
}

static void test_font_destroy(my_font_t* font) {
  (void)font;
}

static const my_font_vtable_t s_test_font_vtable = {
    test_font_measure,     test_font_get_glyph, test_font_ascent,
    test_font_descent,     test_font_line_height, test_font_destroy, NULL,
    test_font_shape,       test_font_get_glyph_id};

TEST(gles2_image_vertices_apply_canvas_scale)
{
  static const uint8_t image[4] = {255, 255, 255, 255};
  mock_gl_t mock;
  my_vgcanvas_t* canvas;

  mock_gl_init(&mock);
  canvas = my_vgcanvas_gles2_create_with_gl(NULL, 100, 80, &mock.gl);
  ASSERT_TRUE(canvas != NULL);
  ASSERT_EQ(my_vgcanvas_set_scale(canvas, 2.0f), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_translate(canvas, 3.0f, 4.0f), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_draw_image(
                canvas, image, 1, 1,
                &(my_rectf_t){5.0f, 6.0f, 7.0f, 8.0f}, NULL),
            MY_RET_OK);

  ASSERT_EQ(mock.textured_count, 6);
  ASSERT_FLOAT_EQ(mock.textured_vertices[0], 16.0f, 0.001f);
  ASSERT_FLOAT_EQ(mock.textured_vertices[1], 20.0f, 0.001f);
  ASSERT_FLOAT_EQ(mock.textured_vertices[4], 30.0f, 0.001f);
  ASSERT_FLOAT_EQ(mock.textured_vertices[9], 36.0f, 0.001f);
  ASSERT_EQ(my_vgcanvas_set_antialias_level(canvas, 0), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_set_scale_filter(canvas, MY_SCALE_FILTER_BILINEAR),
            MY_RET_OK);

  my_vgcanvas_destroy(canvas);
}

TEST(gles2_image_filter_reaches_texture_backend)
{
  static const uint8_t image[4] = {255, 255, 255, 255};
  mock_gl_t mock;
  my_vgcanvas_t* canvas;
  my_rectf_t dst = {0, 0, 4, 4};

  mock_gl_init(&mock);
  canvas = my_vgcanvas_gles2_create_with_gl(NULL, 32, 32, &mock.gl);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_vgcanvas_set_scale_filter(canvas, MY_SCALE_FILTER_NEAREST),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_draw_image(canvas, image, 1, 1, &dst, NULL),
            MY_RET_OK);
  ASSERT_EQ(mock.image_filter_call_count, 1);
  ASSERT_FALSE(mock.last_image_filter_linear);
  ASSERT_EQ(my_vgcanvas_set_scale_filter(canvas, MY_SCALE_FILTER_BILINEAR),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_draw_image(canvas, image, 1, 1, &dst, NULL),
            MY_RET_OK);
  ASSERT_EQ(mock.image_filter_call_count, 2);
  ASSERT_TRUE(mock.last_image_filter_linear);

  my_vgcanvas_destroy(canvas);
}

TEST(gles2_accepts_filtered_upload_without_legacy_callback)
{
  static const uint8_t image[4] = {255, 255, 255, 255};
  mock_gl_t mock;
  my_vgcanvas_t* canvas;

  mock_gl_init(&mock);
  mock.gl.create_texture_rgba = NULL;
  canvas = my_vgcanvas_gles2_create_with_gl(NULL, 32, 32, &mock.gl);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_vgcanvas_set_scale_filter(canvas, MY_SCALE_FILTER_NEAREST),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_draw_image(canvas, image, 1, 1,
                                   &(my_rectf_t){0, 0, 4, 4}, NULL),
            MY_RET_OK);
  ASSERT_EQ(mock.image_filter_call_count, 1);
  ASSERT_FALSE(mock.last_image_filter_linear);

  my_vgcanvas_destroy(canvas);
}

TEST(gles2_resize_uses_drawable_pixels)
{
  mock_gl_t mock;
  my_vgcanvas_t* canvas;

  mock_gl_init(&mock);
  canvas = my_vgcanvas_gles2_create_with_gl(NULL, 100, 80, &mock.gl);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_vgcanvas_set_scale(canvas, 2.0f), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_gles2_resize(canvas, 200, 160), MY_RET_OK);
  ASSERT_EQ(mock.viewport_w, 200);
  ASSERT_EQ(mock.viewport_h, 160);
  ASSERT_FLOAT_EQ(mock.resolution_w, 200.0f, 0.001f);
  ASSERT_FLOAT_EQ(mock.resolution_h, 160.0f, 0.001f);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  ASSERT_EQ(mock.viewport_w, 200);
  ASSERT_EQ(mock.viewport_h, 160);
  my_vgcanvas_destroy(canvas);
}

TEST(gles2_glyph_cache_separates_font_identity)
{
  static const uint8_t font_a_bitmap[] = {0x11};
  static const uint8_t font_b_bitmap[] = {0xEE};
  test_font_t font_a = {{&s_test_font_vtable}, font_a_bitmap, font_a_bitmap};
  test_font_t font_b = {{&s_test_font_vtable}, font_b_bitmap, font_b_bitmap};
  mock_gl_t mock;
  my_vgcanvas_t* canvas;

  mock_gl_init(&mock);
  canvas = my_vgcanvas_gles2_create_with_gl(NULL, 100, 80, &mock.gl);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_vgcanvas_set_font(canvas, (my_font_t*)&font_a, 12), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_draw_text(canvas, "A", 0, 16), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_set_font(canvas, (my_font_t*)&font_b, 12), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_draw_text(canvas, "A", 0, 16), MY_RET_OK);
  ASSERT_EQ(mock.uploaded_alpha_count, 2);
  ASSERT_TRUE(mock.uploaded_alpha[0] == font_a_bitmap);
  ASSERT_TRUE(mock.uploaded_alpha[1] == font_b_bitmap);

  my_vgcanvas_destroy(canvas);
}

TEST(gles2_draws_shaped_glyph_id_and_advance)
{
  static const uint8_t codepoint_bitmap[] = {0x11};
  static const uint8_t shaped_bitmap[] = {0xEE};
  test_font_t font = {{&s_test_font_vtable}, codepoint_bitmap, shaped_bitmap};
  mock_gl_t mock;
  my_vgcanvas_t* canvas;

  mock_gl_init(&mock);
  canvas = my_vgcanvas_gles2_create_with_gl(NULL, 100, 80, &mock.gl);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_vgcanvas_set_font(canvas, (my_font_t*)&font, 12), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_draw_text(canvas, "A", 0, 16), MY_RET_OK);
  ASSERT_EQ(mock.uploaded_alpha_count, 1);
  ASSERT_TRUE(mock.uploaded_alpha[0] == shaped_bitmap);
  ASSERT_FLOAT_EQ(mock.textured_vertices[0], 1.0f, 0.001f);
  {
    int32_t width = 0;
    ASSERT_EQ(my_vgcanvas_measure_text(canvas, "A", &width, NULL), MY_RET_OK);
    ASSERT_EQ(width, 3);
  }
  my_vgcanvas_destroy(canvas);
}

TEST(soft_draws_shaped_glyph_id_and_advance)
{
  static const uint8_t codepoint_bitmap[] = {0x00};
  static const uint8_t shaped_bitmap[] = {0xFF};
  test_font_t font = {{&s_test_font_vtable}, codepoint_bitmap, shaped_bitmap};
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 16, 16, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas;
  uint8_t* pixels;
  uint32_t stride;

  ASSERT_NOT_NULL(lcd);
  canvas = my_vgcanvas_soft_create(NULL, lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_vgcanvas_set_fill_color(canvas, my_color_rgb(255, 255, 255)),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_set_font(canvas, (my_font_t*)&font, 12), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_draw_text(canvas, "A", 0, 0), MY_RET_OK);
  {
    int32_t width = 0;
    ASSERT_EQ(my_vgcanvas_measure_text(canvas, "A", &width, NULL), MY_RET_OK);
    ASSERT_EQ(width, 3);
  }
  pixels = my_lcd_mem_get_buffer(lcd);
  stride = my_lcd_mem_get_stride(lcd);
  ASSERT_EQ(pixels[(size_t)11 * stride + 1u * 4u + 2u], 255);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
}

TEST(soft_canvas_public_capabilities_apply_scale)
{
  my_lcd_t* lcd;
  my_vgcanvas_t* canvas;
  uint8_t* pixels;
  uint32_t stride;

  lcd = my_lcd_mem_create(NULL, 40, 20, MY_PIXEL_FORMAT_BGRA8888);
  ASSERT_NOT_NULL(lcd);
  canvas = my_vgcanvas_soft_create(NULL, lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_vgcanvas_set_scale(canvas, 2.0f), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_set_antialias_level(canvas, 2), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_set_scale_filter(canvas, MY_SCALE_FILTER_NEAREST),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_set_scale(canvas, 0.0f), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_set_fill_color(canvas, my_color_rgb(255, 0, 0)),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_fill_rect(canvas, &(my_rectf_t){0, 0, 10, 10}),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  stride = my_lcd_mem_get_stride(lcd);
  ASSERT_NOT_NULL(pixels);
  ASSERT_EQ(pixels[(size_t)5 * stride + (size_t)15 * 4 + 2], 255);

  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
}

TEST(vgcanvas_capabilities_are_explicit)
{
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 16, 16, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas;
  my_vgcanvas_capabilities_t caps;

  ASSERT_NOT_NULL(lcd);
  canvas = my_vgcanvas_soft_create(NULL, lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_vgcanvas_get_capabilities(canvas, &caps), MY_RET_OK);
  ASSERT_TRUE((caps.antialias_levels & MY_VGCANVAS_AA_LEVEL_BIT(0)) != 0u);
  ASSERT_TRUE((caps.antialias_levels & MY_VGCANVAS_AA_LEVEL_BIT(1)) != 0u);
  ASSERT_TRUE((caps.antialias_levels & MY_VGCANVAS_AA_LEVEL_BIT(2)) != 0u);
  ASSERT_EQ(caps.active_antialias_level, 2u);
  ASSERT_TRUE((caps.scale_filters & MY_VGCANVAS_FILTER_BIT(
                                      MY_SCALE_FILTER_NEAREST)) != 0u);
  ASSERT_TRUE((caps.scale_filters & MY_VGCANVAS_FILTER_BIT(
                                      MY_SCALE_FILTER_BILINEAR)) != 0u);
  ASSERT_EQ(my_vgcanvas_set_antialias_level(canvas, 0), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_get_capabilities(canvas, &caps), MY_RET_OK);
  ASSERT_EQ(caps.active_antialias_level, 0u);
  ASSERT_EQ(my_vgcanvas_set_antialias_level(canvas, 3), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_vgcanvas_get_capabilities(canvas, NULL), MY_RET_INVALID_PARAMS);

  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
}

TEST(gles_capabilities_reject_unsupported_surface_aa)
{
  mock_gl_t mock;
  my_vgcanvas_t* canvas;
  my_vgcanvas_capabilities_t caps;

  mock_gl_init(&mock);
  canvas = my_vgcanvas_gles2_create_with_gl(NULL, 16, 16, &mock.gl);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_vgcanvas_get_capabilities(canvas, &caps), MY_RET_OK);
  ASSERT_EQ(caps.antialias_levels, MY_VGCANVAS_AA_LEVEL_BIT(0));
  ASSERT_EQ(my_vgcanvas_set_antialias_level(canvas, 2),
            MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_vgcanvas_get_capabilities(canvas, &caps), MY_RET_OK);
  ASSERT_EQ(caps.active_antialias_level, 0u);

  my_vgcanvas_destroy(canvas);
}

TEST(gles_capabilities_enable_supported_surface_aa)
{
  mock_gl_t mock;
  my_vgcanvas_t* canvas;
  my_vgcanvas_capabilities_t caps;

  mock_gl_init(&mock);
  mock.multisample_available = true;
  mock.gl.has_multisample = mock_has_multisample;
  canvas = my_vgcanvas_gles2_create_with_gl(NULL, 16, 16, &mock.gl);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_vgcanvas_set_antialias_level(canvas, 2), MY_RET_OK);
  ASSERT_TRUE(mock.multisample_enabled);
  ASSERT_EQ(mock.multisample_calls, 1);
  ASSERT_EQ(my_vgcanvas_get_capabilities(canvas, &caps), MY_RET_OK);
  ASSERT_EQ(caps.active_antialias_level, 2u);
  ASSERT_EQ(my_vgcanvas_set_antialias_level(canvas, 0), MY_RET_OK);
  ASSERT_FALSE(mock.multisample_enabled);
  ASSERT_EQ(mock.multisample_calls, 2);

  my_vgcanvas_destroy(canvas);
}

TEST(vgcanvas_quality_change_is_transactional_and_idempotent)
{
  failing_canvas_t canvas;
  my_vgcanvas_capabilities_t caps;

  memset(&canvas, 0, sizeof(canvas));
  canvas.base.vtable = &s_failing_vtable;
  canvas.base.capabilities.antialias_levels =
      MY_VGCANVAS_AA_LEVEL_BIT(0) | MY_VGCANVAS_AA_LEVEL_BIT(2);
  canvas.base.capabilities.scale_filters =
      MY_VGCANVAS_FILTER_BIT(MY_SCALE_FILTER_NEAREST) |
      MY_VGCANVAS_FILTER_BIT(MY_SCALE_FILTER_BILINEAR);
  canvas.base.capabilities.active_antialias_level = 0u;
  canvas.base.capabilities.active_scale_filter = MY_SCALE_FILTER_BILINEAR;
  canvas.fail = true;

  ASSERT_EQ(my_vgcanvas_set_antialias_level(&canvas.base, 0), MY_RET_OK);
  ASSERT_EQ(canvas.calls, 0);
  ASSERT_EQ(my_vgcanvas_set_antialias_level(&canvas.base, 2), MY_RET_FAIL);
  ASSERT_EQ(canvas.calls, 1);
  ASSERT_EQ(my_vgcanvas_get_capabilities(&canvas.base, &caps), MY_RET_OK);
  ASSERT_EQ(caps.active_antialias_level, 0u);

  canvas.fail = false;
  ASSERT_EQ(my_vgcanvas_set_antialias_level(&canvas.base, 2), MY_RET_OK);
  ASSERT_EQ(canvas.calls, 2);
  ASSERT_EQ(my_vgcanvas_set_antialias_level(&canvas.base, 2), MY_RET_OK);
  ASSERT_EQ(canvas.calls, 2);
  ASSERT_EQ(my_vgcanvas_get_capabilities(&canvas.base, &caps), MY_RET_OK);
  ASSERT_EQ(caps.active_antialias_level, 2u);

  canvas.fail = true;
  ASSERT_EQ(my_vgcanvas_set_scale_filter(&canvas.base,
                                         MY_SCALE_FILTER_NEAREST), MY_RET_FAIL);
  ASSERT_EQ(canvas.filter_calls, 1);
  ASSERT_EQ(my_vgcanvas_get_capabilities(&canvas.base, &caps), MY_RET_OK);
  ASSERT_EQ(caps.active_scale_filter, MY_SCALE_FILTER_BILINEAR);
  canvas.fail = false;
  ASSERT_EQ(my_vgcanvas_set_scale_filter(&canvas.base,
                                         MY_SCALE_FILTER_NEAREST), MY_RET_OK);
  ASSERT_EQ(canvas.filter_calls, 2);
  ASSERT_EQ(my_vgcanvas_set_scale_filter(&canvas.base,
                                         MY_SCALE_FILTER_NEAREST), MY_RET_OK);
  ASSERT_EQ(canvas.filter_calls, 2);
}

typedef struct sample_transaction_fake_t {
  int create_calls;
  int validate_calls;
  int submit_calls;
  int retire_calls;
  int activate_calls;
  int destroy_calls;
  my_ret_t create_result;
  my_ret_t validate_result;
  my_ret_t submit_result;
  bool return_null_candidate;
  void* old_candidate;
  void* new_candidate;
  void* activated_candidate;
  void* retired_candidate;
} sample_transaction_fake_t;

static my_ret_t sample_fake_create(void* ctx, uint32_t sample_count,
                                   uint32_t width, uint32_t height,
                                   void** out_candidate) {
  sample_transaction_fake_t* fake = (sample_transaction_fake_t*)ctx;
  fake->create_calls++;
  (void)sample_count;
  (void)width;
  (void)height;
  if (fake->create_result != MY_RET_OK) {
    return fake->create_result;
  }
  if (fake->return_null_candidate) {
    *out_candidate = NULL;
    return MY_RET_OK;
  }
  *out_candidate = fake->new_candidate;
  return MY_RET_OK;
}

static my_ret_t sample_fake_validate(void* ctx, void* candidate) {
  sample_transaction_fake_t* fake = (sample_transaction_fake_t*)ctx;
  fake->validate_calls++;
  if (candidate != fake->new_candidate) {
    return MY_RET_FAIL;
  }
  return fake->validate_result;
}

static my_ret_t sample_fake_submit(void* ctx, void* candidate) {
  sample_transaction_fake_t* fake = (sample_transaction_fake_t*)ctx;
  fake->submit_calls++;
  if (candidate != fake->new_candidate) {
    return MY_RET_FAIL;
  }
  return fake->submit_result;
}

static void sample_fake_retire(void* ctx, void* candidate) {
  sample_transaction_fake_t* fake = (sample_transaction_fake_t*)ctx;
  fake->retire_calls++;
  fake->retired_candidate = candidate;
}

static void sample_fake_activate(void* ctx, void* candidate) {
  sample_transaction_fake_t* fake = (sample_transaction_fake_t*)ctx;
  fake->activate_calls++;
  fake->activated_candidate = candidate;
}

static void sample_fake_destroy(void* ctx, void* candidate) {
  sample_transaction_fake_t* fake = (sample_transaction_fake_t*)ctx;
  fake->destroy_calls++;
  ASSERT_TRUE(candidate == fake->new_candidate);
}

static const my_vgcanvas_sample_transaction_ops_t s_sample_fake_ops = {
    sample_fake_create, sample_fake_validate, sample_fake_submit,
    sample_fake_activate, sample_fake_retire, sample_fake_destroy};

static void sample_fake_init(sample_transaction_fake_t* fake) {
  memset(fake, 0, sizeof(*fake));
  fake->create_result = MY_RET_OK;
  fake->validate_result = MY_RET_OK;
  fake->submit_result = MY_RET_OK;
  fake->old_candidate = fake;
  fake->new_candidate = (char*)fake + 1;
}

TEST(sample_transaction_rejects_unsupported_without_touching_active)
{
  sample_transaction_fake_t fake;
  my_vgcanvas_sample_transaction_t tx;
  sample_fake_init(&fake);
  my_vgcanvas_sample_transaction_init(&tx, 1, 640, 480, fake.old_candidate,
                                      my_vgcanvas_sample_count_bit(1u) |
                                          my_vgcanvas_sample_count_bit(2u) |
                                          my_vgcanvas_sample_count_bit(4u));

  ASSERT_EQ(my_vgcanvas_sample_transaction_set(&tx, 8, 640, 480,
                                               &s_sample_fake_ops, &fake),
            MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(tx.active_sample_count, 1u);
  ASSERT_TRUE(tx.active_candidate == fake.old_candidate);
  ASSERT_EQ(fake.create_calls, 0);
}

TEST(sample_transaction_rolls_back_create_validate_and_submit_failures)
{
  sample_transaction_fake_t fake;
  my_vgcanvas_sample_transaction_t tx;
  sample_fake_init(&fake);
  my_vgcanvas_sample_transaction_init(&tx, 1, 640, 480, fake.old_candidate,
                                      my_vgcanvas_sample_count_bit(1u) |
                                          my_vgcanvas_sample_count_bit(2u) |
                                          my_vgcanvas_sample_count_bit(4u));

  fake.create_result = MY_RET_FAIL;
  ASSERT_EQ(my_vgcanvas_sample_transaction_set(&tx, 2, 640, 480,
                                               &s_sample_fake_ops, &fake),
            MY_RET_FAIL);
  ASSERT_EQ(tx.active_sample_count, 1u);
  ASSERT_TRUE(tx.active_candidate == fake.old_candidate);
  ASSERT_EQ(fake.destroy_calls, 0);

  fake.create_result = MY_RET_OK;
  fake.validate_result = MY_RET_FAIL;
  ASSERT_EQ(my_vgcanvas_sample_transaction_set(&tx, 2, 640, 480,
                                               &s_sample_fake_ops, &fake),
            MY_RET_FAIL);
  ASSERT_EQ(tx.active_sample_count, 1u);
  ASSERT_TRUE(tx.active_candidate == fake.old_candidate);
  ASSERT_EQ(fake.destroy_calls, 1);

  fake.validate_result = MY_RET_OK;
  fake.submit_result = MY_RET_FAIL;
  ASSERT_EQ(my_vgcanvas_sample_transaction_set(&tx, 2, 640, 480,
                                               &s_sample_fake_ops, &fake),
            MY_RET_FAIL);
  ASSERT_EQ(tx.active_sample_count, 1u);
  ASSERT_TRUE(tx.active_candidate == fake.old_candidate);
  ASSERT_EQ(fake.destroy_calls, 2);
  ASSERT_EQ(fake.retire_calls, 0);
}

TEST(sample_transaction_commits_only_after_submit_and_is_idempotent)
{
  sample_transaction_fake_t fake;
  my_vgcanvas_sample_transaction_t tx;
  sample_fake_init(&fake);
  my_vgcanvas_sample_transaction_init(&tx, 1, 640, 480, fake.old_candidate,
                                      my_vgcanvas_sample_count_bit(1u) |
                                          my_vgcanvas_sample_count_bit(2u) |
                                          my_vgcanvas_sample_count_bit(4u));

  ASSERT_EQ(my_vgcanvas_sample_transaction_set(&tx, 2, 640, 480,
                                               &s_sample_fake_ops, &fake),
            MY_RET_OK);
  ASSERT_EQ(tx.active_sample_count, 2u);
  ASSERT_TRUE(tx.active_candidate == fake.new_candidate);
  ASSERT_EQ(fake.create_calls, 1);
  ASSERT_EQ(fake.validate_calls, 1);
  ASSERT_EQ(fake.submit_calls, 1);
  ASSERT_EQ(fake.activate_calls, 1);
  ASSERT_TRUE(fake.activated_candidate == fake.new_candidate);
  ASSERT_EQ(fake.retire_calls, 1);
  ASSERT_TRUE(fake.retired_candidate == fake.old_candidate);
  ASSERT_EQ(fake.destroy_calls, 0);

  ASSERT_EQ(my_vgcanvas_sample_transaction_set(&tx, 2, 640, 480,
                                               &s_sample_fake_ops, &fake),
            MY_RET_OK);
  ASSERT_EQ(fake.create_calls, 1);
  ASSERT_EQ(fake.submit_calls, 1);

  fake.new_candidate = (char*)&fake + 2;
  ASSERT_EQ(my_vgcanvas_sample_transaction_set(&tx, 2, 800, 600,
                                               &s_sample_fake_ops, &fake),
            MY_RET_OK);
  ASSERT_EQ(tx.active_width, 800u);
  ASSERT_EQ(tx.active_height, 600u);
  ASSERT_EQ(fake.create_calls, 2);
  ASSERT_EQ(fake.submit_calls, 2);
}

TEST(sample_transaction_rejects_invalid_inputs_without_callbacks)
{
  sample_transaction_fake_t fake;
  my_vgcanvas_sample_transaction_t tx;
  sample_fake_init(&fake);
  my_vgcanvas_sample_transaction_init(&tx, 1, 640, 480, fake.old_candidate,
                                      my_vgcanvas_sample_count_bit(1u) |
                                          my_vgcanvas_sample_count_bit(2u) |
                                          my_vgcanvas_sample_count_bit(4u));

  ASSERT_EQ(my_vgcanvas_sample_transaction_set(&tx, 0, 640, 480,
                                               &s_sample_fake_ops, &fake),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_vgcanvas_sample_transaction_set(&tx, 3, 640, 480,
                                               &s_sample_fake_ops, &fake),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_vgcanvas_sample_transaction_set(&tx, 2, 640, 480, NULL, &fake),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_vgcanvas_sample_transaction_set(&tx, 2, 0, 480,
                                               &s_sample_fake_ops, &fake),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(fake.create_calls, 0);
  ASSERT_EQ(tx.active_sample_count, 1u);
}

TEST(sample_transaction_uses_explicit_power_of_two_capability_bits)
{
  sample_transaction_fake_t fake;
  my_vgcanvas_sample_transaction_t tx;
  sample_fake_init(&fake);
  my_vgcanvas_sample_transaction_init(
      &tx, 1, 640, 480, fake.old_candidate,
      my_vgcanvas_sample_count_bit(1u) |
          my_vgcanvas_sample_count_bit(8u) |
          my_vgcanvas_sample_count_bit(16u));

  ASSERT_EQ(my_vgcanvas_sample_count_bit(0u), 0u);
  ASSERT_EQ(my_vgcanvas_sample_count_bit(3u), 0u);
  ASSERT_EQ(my_vgcanvas_sample_count_bit(8u), 8u);
  ASSERT_EQ(my_vgcanvas_sample_transaction_set(
                &tx, 8, 640, 480, &s_sample_fake_ops, &fake),
            MY_RET_OK);
  ASSERT_EQ(tx.active_sample_count, 8u);
  ASSERT_EQ(my_vgcanvas_sample_transaction_set(
                &tx, 32, 640, 480, &s_sample_fake_ops, &fake),
            MY_RET_NOT_SUPPORTED);
}

TEST(sample_transaction_rejects_successful_empty_candidate_without_touching_active)
{
  sample_transaction_fake_t fake;
  my_vgcanvas_sample_transaction_t tx;
  sample_fake_init(&fake);
  fake.return_null_candidate = true;
  my_vgcanvas_sample_transaction_init(
      &tx, 1, 640, 480, fake.old_candidate,
      my_vgcanvas_sample_count_bit(1u) |
          my_vgcanvas_sample_count_bit(2u));

  ASSERT_EQ(my_vgcanvas_sample_transaction_set(
                &tx, 2, 640, 480, &s_sample_fake_ops, &fake),
            MY_RET_FAIL);
  ASSERT_TRUE(tx.active_candidate == fake.old_candidate);
  ASSERT_EQ(tx.active_sample_count, 1u);
  ASSERT_EQ(fake.validate_calls, 0);
  ASSERT_EQ(fake.destroy_calls, 0);
}

TEST(sample_transaction_rejects_candidate_alias_without_destroying_active)
{
  sample_transaction_fake_t fake;
  my_vgcanvas_sample_transaction_t tx;
  sample_fake_init(&fake);
  fake.new_candidate = fake.old_candidate;
  my_vgcanvas_sample_transaction_init(
      &tx, 1, 640, 480, fake.old_candidate,
      my_vgcanvas_sample_count_bit(1u) |
          my_vgcanvas_sample_count_bit(2u));

  ASSERT_EQ(my_vgcanvas_sample_transaction_set(
                &tx, 2, 640, 480, &s_sample_fake_ops, &fake),
            MY_RET_FAIL);
  ASSERT_TRUE(tx.active_candidate == fake.old_candidate);
  ASSERT_EQ(tx.active_sample_count, 1u);
  ASSERT_EQ(fake.validate_calls, 0);
  ASSERT_EQ(fake.destroy_calls, 0);
  ASSERT_EQ(fake.retire_calls, 0);
}

TEST(sample_transaction_builds_missing_initial_candidate)
{
  sample_transaction_fake_t fake;
  my_vgcanvas_sample_transaction_t tx;
  sample_fake_init(&fake);
  my_vgcanvas_sample_transaction_init(
      &tx, 2, 640, 480, NULL,
      my_vgcanvas_sample_count_bit(1u) |
          my_vgcanvas_sample_count_bit(2u));

  ASSERT_EQ(my_vgcanvas_sample_transaction_set(
                &tx, 2, 640, 480, &s_sample_fake_ops, &fake),
            MY_RET_OK);
  ASSERT_EQ(fake.create_calls, 1);
  ASSERT_TRUE(tx.active_candidate == fake.new_candidate);
  ASSERT_EQ(tx.active_sample_count, 2u);
  ASSERT_EQ(fake.retire_calls, 0);
}

TEST(vgcanvas_antialias_levels_use_explicit_sample_contract)
{
  ASSERT_EQ(my_vgcanvas_antialias_level_sample_count(0), 1u);
  ASSERT_EQ(my_vgcanvas_antialias_level_sample_count(1), 2u);
  ASSERT_EQ(my_vgcanvas_antialias_level_sample_count(2), 4u);
  ASSERT_EQ(my_vgcanvas_antialias_level_sample_count(-1), 0u);
  ASSERT_EQ(my_vgcanvas_antialias_level_sample_count(3), 0u);

  ASSERT_EQ(my_vgcanvas_antialias_levels_for_sample_counts(
                my_vgcanvas_sample_count_bit(1u)),
            MY_VGCANVAS_AA_LEVEL_BIT(0));
  ASSERT_EQ(my_vgcanvas_antialias_levels_for_sample_counts(
                my_vgcanvas_sample_count_bit(1u) |
                my_vgcanvas_sample_count_bit(2u) |
                my_vgcanvas_sample_count_bit(4u)),
            MY_VGCANVAS_AA_LEVEL_BIT(0) |
                MY_VGCANVAS_AA_LEVEL_BIT(1) |
                MY_VGCANVAS_AA_LEVEL_BIT(2));
}

#ifdef MYUI_HAS_VULKAN
TEST(vulkan_offscreen_quality_and_resize_commit_as_one_transaction)
{
  my_vgcanvas_t* canvas;
  my_vgcanvas_capabilities_t caps;

  canvas = my_vgcanvas_vulkan_create_offscreen(NULL, 32, 24);
  if (canvas == NULL) {
    printf("  SKIP: no usable Vulkan offscreen device\n");
    return;
  }
  ASSERT_EQ(my_vgcanvas_get_capabilities(canvas, &caps), MY_RET_OK);
  ASSERT_TRUE((caps.antialias_levels & MY_VGCANVAS_AA_LEVEL_BIT(0)) != 0u);
  if ((caps.antialias_levels & MY_VGCANVAS_AA_LEVEL_BIT(2)) != 0u) {
    ASSERT_EQ(my_vgcanvas_set_antialias_level(canvas, 0), MY_RET_OK);
  }
  ASSERT_EQ(my_vgcanvas_vulkan_resize(canvas, 48, 40), MY_RET_OK);
  if ((caps.antialias_levels & MY_VGCANVAS_AA_LEVEL_BIT(2)) != 0u) {
    ASSERT_EQ(my_vgcanvas_set_antialias_level(canvas, 2), MY_RET_OK);
  }
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_get_capabilities(canvas, &caps), MY_RET_OK);
  ASSERT_EQ(caps.active_antialias_level,
            (caps.antialias_levels & MY_VGCANVAS_AA_LEVEL_BIT(2)) != 0u
                ? 2u
                : 0u);
  my_vgcanvas_destroy(canvas);
}
#endif

TEST(soft_fill_closes_open_subpaths)
{
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 16, 16, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas;
  uint8_t* pixels;
  uint32_t stride;

  ASSERT_NOT_NULL(lcd);
  canvas = my_vgcanvas_soft_create(NULL, lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_vgcanvas_set_fill_color(canvas, my_color_rgb(255, 0, 0)),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_path(canvas), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_move_to(canvas, 2, 2), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_line_to(canvas, 12, 2), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_line_to(canvas, 2, 12), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_fill(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  stride = my_lcd_mem_get_stride(lcd);
  ASSERT_NOT_NULL(pixels);
  ASSERT_EQ(pixels[(size_t)4 * stride + (size_t)4 * 4 + 2], 255);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
}

TEST(soft_mono_image_uses_ordered_dither)
{
  static const uint8_t image[4 * 4 * 4] = {
      128, 128, 128, 255, 128, 128, 128, 255,
      128, 128, 128, 255, 128, 128, 128, 255,
      128, 128, 128, 255, 128, 128, 128, 255,
      128, 128, 128, 255, 128, 128, 128, 255,
  };
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 4, 4, MY_PIXEL_FORMAT_MONO);
  my_vgcanvas_t* canvas;
  uint8_t* pixels;
  uint8_t nonzero = 0;
  size_t i;

  ASSERT_NOT_NULL(lcd);
  canvas = my_vgcanvas_soft_create(NULL, lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_vgcanvas_draw_image(canvas, image, 4, 4,
                                   &(my_rectf_t){0, 0, 4, 4}, NULL),
            MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  ASSERT_NOT_NULL(pixels);
  for (i = 0; i < 4; i++) {
    if (pixels[i] != 0) {
      nonzero++;
    }
  }
  ASSERT_TRUE(nonzero > 0);
  ASSERT_TRUE(nonzero < 4);

  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
}

TEST(lcd_rejects_dimension_and_stride_overflow)
{
  uint8_t buffer[8] = {0};
  my_lcd_t* lcd;

  ASSERT_TRUE(my_lcd_mem_create(NULL, UINT32_MAX, 1,
                                MY_PIXEL_FORMAT_MONO) == NULL);
  ASSERT_TRUE(my_lcd_mem_create(NULL, (uint32_t)INT32_MAX + 1u, 1,
                                MY_PIXEL_FORMAT_RGB888) == NULL);
  ASSERT_TRUE(my_lcd_mem_create_from_buffer(
                  NULL, 8, 1, MY_PIXEL_FORMAT_MONO, buffer, 0) == NULL);
  ASSERT_TRUE(my_lcd_mem_create_from_buffer(
                  NULL, (uint32_t)INT32_MAX, 1, MY_PIXEL_FORMAT_RGB888,
                  buffer, UINT32_MAX) == NULL);
  lcd = my_lcd_mem_create(NULL, 1, 1, MY_PIXEL_FORMAT_MONO);
  ASSERT_NOT_NULL(lcd);
  ASSERT_EQ(my_lcd_draw_pixels(lcd, buffer, 0, 0, UINT32_MAX, 1),
            MY_RET_INVALID_PARAMS);
  my_lcd_destroy(lcd);
}

TEST_MAIN_BEGIN()
    RUN_TEST(gles2_image_vertices_apply_canvas_scale);
    RUN_TEST(gles2_image_filter_reaches_texture_backend);
    RUN_TEST(gles2_accepts_filtered_upload_without_legacy_callback);
    RUN_TEST(gles2_resize_uses_drawable_pixels);
    RUN_TEST(gles2_glyph_cache_separates_font_identity);
    RUN_TEST(gles2_draws_shaped_glyph_id_and_advance);
    RUN_TEST(soft_draws_shaped_glyph_id_and_advance);
    RUN_TEST(soft_canvas_public_capabilities_apply_scale);
    RUN_TEST(vgcanvas_capabilities_are_explicit);
    RUN_TEST(gles_capabilities_reject_unsupported_surface_aa);
    RUN_TEST(gles_capabilities_enable_supported_surface_aa);
    RUN_TEST(vgcanvas_quality_change_is_transactional_and_idempotent);
    RUN_TEST(sample_transaction_rejects_unsupported_without_touching_active);
    RUN_TEST(sample_transaction_rolls_back_create_validate_and_submit_failures);
    RUN_TEST(sample_transaction_commits_only_after_submit_and_is_idempotent);
    RUN_TEST(sample_transaction_rejects_invalid_inputs_without_callbacks);
    RUN_TEST(sample_transaction_uses_explicit_power_of_two_capability_bits);
    RUN_TEST(sample_transaction_rejects_successful_empty_candidate_without_touching_active);
    RUN_TEST(sample_transaction_rejects_candidate_alias_without_destroying_active);
    RUN_TEST(sample_transaction_builds_missing_initial_candidate);
    RUN_TEST(vgcanvas_antialias_levels_use_explicit_sample_contract);
#ifdef MYUI_HAS_VULKAN
    RUN_TEST(vulkan_offscreen_quality_and_resize_commit_as_one_transaction);
#endif
    RUN_TEST(soft_fill_closes_open_subpaths);
    RUN_TEST(soft_mono_image_uses_ordered_dither);
    RUN_TEST(lcd_rejects_dimension_and_stride_overflow);
TEST_MAIN_END()
