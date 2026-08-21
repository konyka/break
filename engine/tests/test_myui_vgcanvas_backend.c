#include "test_framework.h"

#include <string.h>

#include "myr/my_gl.h"
#include "myr/my_lcd_mem.h"
#include "myr/my_vgcanvas_gles2.h"
#include "myr/my_vgcanvas_soft.h"

typedef struct mock_gl_t {
  my_gl_t gl;
  float textured_vertices[24];
  int32_t textured_count;
  uint32_t next_program;
  int32_t viewport_w;
  int32_t viewport_h;
  float resolution_w;
  float resolution_h;
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
  mock->gl.create_texture_rgba = mock_create_texture_rgba;
  mock->gl.delete_texture = mock_delete_texture;
  mock->gl.draw_textured_quads = mock_draw_textured;
  mock->gl.ctx = mock;
}

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
            MY_RET_NOT_SUPPORTED);

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

TEST_MAIN_BEGIN()
    RUN_TEST(gles2_image_vertices_apply_canvas_scale);
    RUN_TEST(gles2_resize_uses_drawable_pixels);
    RUN_TEST(soft_canvas_public_capabilities_apply_scale);
TEST_MAIN_END()
