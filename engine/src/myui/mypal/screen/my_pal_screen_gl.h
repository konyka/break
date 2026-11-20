#ifndef MY_PAL_SCREEN_GL_H
#define MY_PAL_SCREEN_GL_H

#include "mypal/my_pal.h"

my_pal_gl_t* my_screen_gl_create(my_pal_window_t* owner,
                                 const my_allocator_t* allocator,
                                 my_pal_gl_t** owner_link);
my_ret_t my_screen_gl_resize(my_pal_gl_t* gl, int32_t width, int32_t height);
void my_screen_gl_destroy(my_pal_gl_t* gl);

#endif
