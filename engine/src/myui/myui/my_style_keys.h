/**
 * @file my_style_keys.h
 * @brief Central constants for the style property keys (M24b).
 *
 * Macros expanding to the same string literals as before — pure source
 * cleanup, no ABI change. The full set actually used under src/ (verify
 * with grep before adding more; do not speculate).
 */
#ifndef MY_STYLE_KEYS_H
#define MY_STYLE_KEYS_H

#define MY_STYLE_BG_COLOR "bg_color"
#define MY_STYLE_FG_COLOR "fg_color"
#define MY_STYLE_BORDER_COLOR "border_color"
#define MY_STYLE_ROUND_RADIUS "round_radius"
#define MY_STYLE_FONT_SIZE "font_size"
#define MY_STYLE_BORDER_WIDTH "border_width"

#endif /* MY_STYLE_KEYS_H */
