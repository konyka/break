/**
 * @file my_font_ft.h
 * @brief FreeType font backend (M16): hinted TrueType rendering via
 * libfreetype — noticeably sharper than stb_truetype at small sizes
 * (stb has no hinting). Implements the frozen my_font vtable (M7a).
 * Build option MYUI_FONT_FREETYPE (auto-OFF when freetype2 is absent).
 */
#ifndef MY_FONT_FT_H
#define MY_FONT_FT_H

#include "myr/my_font.h"

/**
 * @brief Load a font face via FreeType (face_index selects inside a
 * TTC). LRU glyph cache of cache_capacity entries (0 = default 256).
 * NULL when the file cannot be parsed, or when built without
 * MYUI_FONT_FREETYPE.
 */
my_font_t* my_font_ft_create(const my_allocator_t* allocator,
                             const char* path, int32_t face_index,
                             size_t cache_capacity);

/**
 * @brief Like my_font_ft_create, plus an optional variable-font weight
 * (wght axis, e.g. 400 = Regular; 0 = the font's default instance).
 */
my_font_t* my_font_ft_create_ex(const my_allocator_t* allocator,
                                const char* path, int32_t face_index,
                                int32_t weight, size_t cache_capacity);

/** @brief Test/diagnostics: glyph cache hit counter (0 without FT). */
size_t my_font_ft_cache_hits(my_font_t* font);

/** @brief Test/diagnostics: glyph cache miss counter (0 without FT). */
size_t my_font_ft_cache_misses(my_font_t* font);

#endif /* MY_FONT_FT_H */
