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
 *
 * A loaded face may be queried concurrently from multiple threads. Provider
 * state and caches are serialized per face; callers must still keep the font
 * object alive until every call has returned. A glyph bitmap is leased: call
 * my_font_glyph_release() after consuming it, and before destroying the font.
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

/** @brief Test/diagnostics: cached script/language capability query hits. */
size_t my_font_ft_shape_support_cache_hits(my_font_t* font);

/** @brief Test/diagnostics: number of required LangSys features. */
size_t my_font_ft_required_feature_count(
    my_font_t* font, const my_font_shape_params_t* params);

/** @brief Test/diagnostics: required feature tag at index, or 0 when absent. */
uint32_t my_font_ft_required_feature_tag(
    my_font_t* font, const my_font_shape_params_t* params, size_t index);

#endif /* MY_FONT_FT_H */
