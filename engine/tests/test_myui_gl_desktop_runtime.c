/* Real-WGL runtime smoke for the myr desktop GL backend on Windows
 * (graphics label: requires a machine with a GL installable client
 * driver; headless CI excludes it).
 *
 * Creates a hidden window, a legacy WGL context, and then exercises the
 * resolved desktop table end-to-end: trivial "#version 120" program
 * compile+link, alpha texture upload, and table teardown slots. When
 * the host only offers the GDI generic software implementation (GL 1.1,
 * no shader entry points), my_gl_desktop_default() legitimately returns
 * NULL and the test reports SKIP instead of claiming coverage. */
#include "test_framework.h"

#include "myr/my_gl.h"
#include "myr/my_gl_desktop.h"

#include <windows.h>
#include <string.h>

static void required_slots_are_populated(const my_gl_t* gl) {
    ASSERT_NOT_NULL(gl->viewport);
    ASSERT_NOT_NULL(gl->create_program);
    ASSERT_NOT_NULL(gl->delete_program);
    ASSERT_NOT_NULL(gl->use_program);
    ASSERT_NOT_NULL(gl->uniform2f);
    ASSERT_NOT_NULL(gl->uniform4f);
    ASSERT_NOT_NULL(gl->draw_arrays_triangles);
    ASSERT_NOT_NULL(gl->create_texture);
    ASSERT_NOT_NULL(gl->create_texture_rgba);
    ASSERT_NOT_NULL(gl->delete_texture);
    ASSERT_NOT_NULL(gl->draw_textured_quads);
    ASSERT_NOT_NULL(gl->shader_header_vs);
    ASSERT_NOT_NULL(gl->shader_header_fs);
}

TEST(desktop_gl_compiles_program_on_a_real_wgl_context)
{
    static const char vs_source[] =
        "#version 120\n"
        "void main() { gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }\n";
    static const char fs_source[] =
        "#version 120\n"
        "void main() { gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0); }\n";
    static const uint8_t alpha_pixels[4] = {1u, 2u, 3u, 4u};

    WNDCLASSA wc;
    PIXELFORMATDESCRIPTOR pfd;
    HINSTANCE instance = GetModuleHandleA(NULL);
    const char* class_name = "break_gldesk_smoke";
    HWND hwnd = NULL;
    HDC dc = NULL;
    HGLRC ctx = NULL;
    int pixel_format = 0;
    const my_gl_t* gl = NULL;
    uint32_t program = 0;
    uint32_t texture = 0;
    bool class_registered = false;

    memset(&wc, 0, sizeof(wc));
    wc.lpfnWndProc = DefWindowProcA;
    wc.lpszClassName = class_name;
    wc.hInstance = instance;
    class_registered = RegisterClassA(&wc) != 0;
    if (!class_registered && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
        ASSERT_TRUE(false);
    }
    hwnd = CreateWindowExA(0, class_name, "break gl desktop smoke",
                           WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                           64, 64, NULL, NULL, instance, NULL);
    ASSERT_NOT_NULL(hwnd);
    dc = GetDC(hwnd);
    ASSERT_NOT_NULL(dc);

    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pixel_format = ChoosePixelFormat(dc, &pfd);
    ASSERT_NEQ(pixel_format, 0);
    ASSERT_TRUE(SetPixelFormat(dc, pixel_format, &pfd));

    ctx = wglCreateContext(dc);
    ASSERT_NOT_NULL(ctx);
    ASSERT_TRUE(wglMakeCurrent(dc, ctx));

    gl = my_gl_desktop_default();
    if (gl == NULL) {
        /* GDI generic / GL 1.1-only driver: resolution contract says
         * the table stays unavailable; report the boundary instead of
         * fabricating a pass. */
        printf("  SKIP: no GL 2.0 desktop entry points on this driver\n");
    } else {
        required_slots_are_populated(gl);
        program = gl->create_program(gl->ctx, vs_source, fs_source);
        ASSERT_NEQ(program, 0);
        texture = gl->create_texture(gl->ctx, alpha_pixels, 2, 2);
        ASSERT_NEQ(texture, 0);
        gl->delete_texture(gl->ctx, texture);
        gl->delete_program(gl->ctx, program);
    }

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(ctx);
    ReleaseDC(hwnd, dc);
    DestroyWindow(hwnd);
    if (class_registered) {
        UnregisterClassA(class_name, instance);
    }
}

TEST_MAIN_BEGIN()
RUN_TEST(desktop_gl_compiles_program_on_a_real_wgl_context);
TEST_MAIN_END()
