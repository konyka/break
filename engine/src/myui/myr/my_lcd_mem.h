/**
 * @file my_lcd_mem.h
 * @brief In-memory framebuffer lcd backend (test/offscreen rendering).
 *
 * The buffer is a tightly packed row-major array in the lcd's pixel format
 * (MONO rows are byte-aligned: stride = (w + 7) / 8 bytes). No blending:
 * fill_rect/draw_pixels replace destination pixels.
 */
#ifndef MY_LCD_MEM_H
#define MY_LCD_MEM_H

#include "myc/my_mem.h"
#include "myr/my_lcd.h"

/**
 * @brief Create an in-memory lcd (NULL allocator = default).
 * @return the lcd, or NULL on OOM/invalid args (w or h == 0).
 */
my_lcd_t* my_lcd_mem_create(const my_allocator_t* allocator, uint32_t w, uint32_t h,
                            my_pixel_format_t format);

/**
 * @brief Create an lcd over an EXISTING buffer (not owned by the lcd;
 * destroy does NOT free it). Used by framebuffer ports (mmap'd /dev/fb).
 */
my_lcd_t* my_lcd_mem_create_from_buffer(const my_allocator_t* allocator,
                                        uint32_t w, uint32_t h,
                                        my_pixel_format_t format,
                                        uint8_t* buffer, uint32_t stride);

/** @brief Raw framebuffer pointer (NULL if lcd is not a mem lcd). */
uint8_t* my_lcd_mem_get_buffer(my_lcd_t* lcd);

/** @brief Bytes per row (NULL-safe: 0 if lcd is not a mem lcd). */
uint32_t my_lcd_mem_get_stride(my_lcd_t* lcd);

#endif /* MY_LCD_MEM_H */
