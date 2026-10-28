#include "rhi/dispatch/rhi_api.h"
#include "core/log.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(rhi_device_create) || defined(rhi_device_create_compiled) || \
    defined(rhi_cmd_draw)
#error "RHI dispatch must expose functions, not public macros"
#endif

static unsigned checks;
static unsigned failures;
static unsigned stub_log_count;

#define CHECK(condition) check((condition), #condition, __LINE__)

static void check(int condition, const char *expression, int line) {
    checks++;
    if (!condition) {
        fprintf(stderr, "FAIL line %d: %s\n", line, expression);
        failures++;
    }
}

void log_write(LogLevel level, const char *file, int line, const char *fmt, ...) {
    (void)level;
    (void)file;
    (void)line;
    (void)fmt;
    stub_log_count++;
}

static int fake_cmd;
static int fake_device;
static int fake_timer;
static int map_a;
static int map_b;
static unsigned draw_a_calls;
static unsigned draw_b_calls;
static u32 draw_a_vertices;
static u32 draw_b_vertices;

static void mock_draw_a(RHICmdBuffer *cmd, u32 vertices, u32 instances) {
    CHECK(cmd == (RHICmdBuffer *)&fake_cmd);
    CHECK(instances == 7u);
    draw_a_calls++;
    draw_a_vertices = vertices;
}

static void mock_draw_b(RHICmdBuffer *cmd, u32 vertices, u32 instances) {
    CHECK(cmd == (RHICmdBuffer *)&fake_cmd);
    CHECK(instances == 9u);
    draw_b_calls++;
    draw_b_vertices = vertices;
}

static u32 mock_frame_index_a(RHIDevice *dev) {
    CHECK(dev == (RHIDevice *)&fake_device);
    return 31u;
}

static u32 mock_frame_index_b(RHIDevice *dev) {
    CHECK(dev == (RHIDevice *)&fake_device);
    return 32u;
}

static RHIBuffer mock_buffer_create_a(RHIDevice *dev, const RHIBufferDesc *desc) {
    RHIBuffer handle = { 11u, 12u };
    CHECK(dev == (RHIDevice *)&fake_device);
    CHECK(desc != NULL && desc->size == 4096u);
    return handle;
}

static RHIBuffer mock_buffer_create_b(RHIDevice *dev, const RHIBufferDesc *desc) {
    RHIBuffer handle = { 21u, 22u };
    CHECK(dev == (RHIDevice *)&fake_device);
    CHECK(desc != NULL && desc->size == 4096u);
    return handle;
}

static void *mock_map_a(RHIDevice *dev, RHIBuffer buffer) {
    CHECK(dev == (RHIDevice *)&fake_device);
    CHECK(buffer.index == 11u && buffer.generation == 12u);
    return &map_a;
}

static void *mock_map_b(RHIDevice *dev, RHIBuffer buffer) {
    CHECK(dev == (RHIDevice *)&fake_device);
    CHECK(buffer.index == 21u && buffer.generation == 22u);
    return &map_b;
}

static f64 mock_elapsed_a(RHIGPUTimer *timer) {
    CHECK(timer == (RHIGPUTimer *)&fake_timer);
    return 1.25;
}

static f64 mock_elapsed_b(RHIGPUTimer *timer) {
    CHECK(timer == (RHIGPUTimer *)&fake_timer);
    return 2.5;
}

static char *read_dispatch_source(void) {
    FILE *file;
    long size;
    char *text;
    file = fopen(TEST_RHI_DISPATCH_SOURCE, "rb");
    if (file == NULL) return NULL;
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return NULL;
    }
    size = ftell(file);
    if (size < 0 || fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return NULL;
    }
    text = (char *)malloc((size_t)size + 1u);
    if (text == NULL) {
        fclose(file);
        return NULL;
    }
    if (fread(text, 1u, (size_t)size, file) != (size_t)size) {
        free(text);
        fclose(file);
        return NULL;
    }
    text[size] = '\0';
    fclose(file);
    return text;
}

int main(void) {
    static RHIApi api_a;
    static RHIApi api_b;
    RHIBufferDesc desc = { 0 };
    RHIBuffer buffer;
    RHIOffscreenFBO fbo;
    char *source;

    rhi_dispatch_set_api(NULL);
    rhi_device_destroy(NULL);
    rhi_cmd_draw(NULL, 1u, 1u);
    CHECK(rhi_frame_begin(NULL) == NULL);
    CHECK(rhi_frame_index(NULL) == 0u);
    CHECK(rhi_gpu_timer_create(NULL) == NULL);
    CHECK(rhi_gpu_timer_elapsed_ms(NULL) == 0.0);
    CHECK(rhi_buffer_map(NULL, RHI_HANDLE_NULL) == NULL);
    CHECK(!rhi_buffer_read(NULL, RHI_HANDLE_NULL, NULL, 0u, 0u));
    buffer = rhi_buffer_create(NULL, NULL);
    CHECK(!rhi_handle_valid(buffer));
    fbo = rhi_offscreen_fbo_create(NULL, 64u, 64u);
    CHECK(!rhi_handle_valid(fbo.fb));
    CHECK(!rhi_handle_valid(fbo.color_tex));
    CHECK(fbo.width == 0u && fbo.height == 0u);
    CHECK(stub_log_count == 1u);

    desc.size = 4096u;
    api_a.rhi_cmd_draw = mock_draw_a;
    api_a.rhi_frame_index = mock_frame_index_a;
    api_a.rhi_buffer_create = mock_buffer_create_a;
    api_a.rhi_buffer_map = mock_map_a;
    api_a.rhi_gpu_timer_elapsed_ms = mock_elapsed_a;
    api_b.rhi_cmd_draw = mock_draw_b;
    api_b.rhi_frame_index = mock_frame_index_b;
    api_b.rhi_buffer_create = mock_buffer_create_b;
    api_b.rhi_buffer_map = mock_map_b;
    api_b.rhi_gpu_timer_elapsed_ms = mock_elapsed_b;

    rhi_dispatch_set_api(&api_a);
    rhi_cmd_draw((RHICmdBuffer *)&fake_cmd, 5u, 7u);
    CHECK(draw_a_calls == 1u && draw_a_vertices == 5u);
    CHECK(draw_b_calls == 0u);
    CHECK(rhi_frame_index((RHIDevice *)&fake_device) == 31u);
    buffer = rhi_buffer_create((RHIDevice *)&fake_device, &desc);
    CHECK(buffer.index == 11u && buffer.generation == 12u);
    CHECK(rhi_buffer_map((RHIDevice *)&fake_device, buffer) == &map_a);
    CHECK(rhi_gpu_timer_elapsed_ms((RHIGPUTimer *)&fake_timer) == 1.25);

    rhi_dispatch_set_api(&api_b);
    rhi_cmd_draw((RHICmdBuffer *)&fake_cmd, 6u, 9u);
    CHECK(draw_b_calls == 1u && draw_b_vertices == 6u);
    CHECK(draw_a_calls == 1u);
    CHECK(rhi_frame_index((RHIDevice *)&fake_device) == 32u);
    buffer = rhi_buffer_create((RHIDevice *)&fake_device, &desc);
    CHECK(buffer.index == 21u && buffer.generation == 22u);
    CHECK(rhi_buffer_map((RHIDevice *)&fake_device, buffer) == &map_b);
    CHECK(rhi_gpu_timer_elapsed_ms((RHIGPUTimer *)&fake_timer) == 2.5);
    CHECK(stub_log_count == 1u);

    source = read_dispatch_source();
    CHECK(source != NULL);
    if (source != NULL) {
        char *begin = strstr(source, "/* RHI_FORWARDERS_BEGIN */");
        char *end = strstr(source, "/* RHI_FORWARDERS_END */");
        CHECK(begin != NULL && end != NULL && end > begin);
        if (begin != NULL && end != NULL && end > begin) {
            *end = '\0';
            CHECK(strstr(begin, "rhi_device_create(") == NULL);
            CHECK(strstr(begin, "rhi_device_create_compiled(") == NULL);
        }
        free(source);
    }
    rhi_dispatch_set_api(NULL);

    if (failures != 0u) {
        fprintf(stderr, "%u of %u checks failed\n", failures, checks);
        return 1;
    }
    printf("OK: %u dispatch checks\n", checks);
    return 0;
}
