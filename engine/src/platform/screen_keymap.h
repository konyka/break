#ifndef SCREEN_KEYMAP_H
#define SCREEN_KEYMAP_H

/*
 * screen_keymap.h — QNX Screen key symbol -> engine key code mapping.
 *
 * Pure inline integer mapping with no QNX headers, so it is unit-testable on
 * every host lane (tests/test_screen_keymap.c). Symbols mirror
 * <sys/keycodes.h>: printable keys arrive as Unicode code points (ASCII for
 * the engine's printable set) and non-printables as KEYCODE_PC_KEYS + an
 * offset. window_screen.c static-asserts the mirrored base against the real
 * header on QNX cross builds, so drift is a compile error there.
 *
 * Engine key codes are the same ones x11_key_to_index produces
 * (engine/src/platform/window_x11.c): letters 'a'..'z', digits, ASCII
 * punctuation, ESC 256, RETURN 257, TAB 259, BACKSPACE 260, arrows
 * 261-264, F1-F12 271-282, PgUp/PgDn/Home/End/Insert/Delete 283-288,
 * Shift 289, Ctrl 290, Pause 291, ScrollLock 292, NumLock 293,
 * CapsLock 294, Menu 295.
 */

#include <core/types.h>

/* KEYCODE_PC_KEYS = UNICODE_PRIVATE_USE_AREA_FIRST (0xE000) + 0x1000 */
#define SCREEN_KEYMAP_PC_KEYS 0xF000u
#define SCREEN_KEYMAP_PC(offset) (SCREEN_KEYMAP_PC_KEYS + (u32)(offset))

static inline i32 screen_keymap_sym_to_engine(u32 sym)
{
    if (sym >= (u32)'a' && sym <= (u32)'z') return (i32)sym;
    if (sym >= (u32)'A' && sym <= (u32)'Z') return (i32)(sym - (u32)'A' + (u32)'a');
    if (sym >= (u32)'0' && sym <= (u32)'9') return (i32)sym;
    switch (sym) {
    /* Printable Unicode == ASCII for the engine's punctuation set. */
    case (u32)' ':  return 32;
    case (u32)'-':  case (u32)'=':
    case (u32)'(':  case (u32)')':
    case (u32)'[':  case (u32)']':
    case (u32)'/':  case (u32)'\\':
    case (u32)'`':  case (u32)';':
    case (u32)'\'': case (u32)',':  case (u32)'.':
        return (i32)sym;
    /* Non-printables: KEYCODE_PC_KEYS + offset (sys/keycodes.h values). */
    case SCREEN_KEYMAP_PC(0x1B): return 256; /* ESCAPE */
    case SCREEN_KEYMAP_PC(0x0D): return 257; /* RETURN */
    case SCREEN_KEYMAP_PC(0x09): return 259; /* TAB */
    case SCREEN_KEYMAP_PC(0x08): return 260; /* BACKSPACE */
    case SCREEN_KEYMAP_PC(0x51): return 261; /* LEFT */
    case SCREEN_KEYMAP_PC(0x53): return 262; /* RIGHT */
    case SCREEN_KEYMAP_PC(0x52): return 263; /* UP */
    case SCREEN_KEYMAP_PC(0x54): return 264; /* DOWN */
    case SCREEN_KEYMAP_PC(0xBE): return 271; /* F1 */
    case SCREEN_KEYMAP_PC(0xBF): return 272; /* F2 */
    case SCREEN_KEYMAP_PC(0xC0): return 273; /* F3 */
    case SCREEN_KEYMAP_PC(0xC1): return 274; /* F4 */
    case SCREEN_KEYMAP_PC(0xC2): return 275; /* F5 */
    case SCREEN_KEYMAP_PC(0xC3): return 276; /* F6 */
    case SCREEN_KEYMAP_PC(0xC4): return 277; /* F7 */
    case SCREEN_KEYMAP_PC(0xC5): return 278; /* F8 */
    case SCREEN_KEYMAP_PC(0xC6): return 279; /* F9 */
    case SCREEN_KEYMAP_PC(0xC7): return 280; /* F10 */
    case SCREEN_KEYMAP_PC(0xC8): return 281; /* F11 */
    case SCREEN_KEYMAP_PC(0xC9): return 282; /* F12 */
    case SCREEN_KEYMAP_PC(0x55): return 283; /* PG_UP */
    case SCREEN_KEYMAP_PC(0x56): return 284; /* PG_DOWN */
    case SCREEN_KEYMAP_PC(0x50): return 285; /* HOME */
    case SCREEN_KEYMAP_PC(0x57): return 286; /* END */
    case SCREEN_KEYMAP_PC(0x63): return 287; /* INSERT */
    case SCREEN_KEYMAP_PC(0xFF): return 288; /* DELETE */
    case SCREEN_KEYMAP_PC(0xE1): return 289; /* LEFT_SHIFT */
    case SCREEN_KEYMAP_PC(0xE2): return 289; /* RIGHT_SHIFT */
    case SCREEN_KEYMAP_PC(0xE3): return 290; /* LEFT_CTRL */
    case SCREEN_KEYMAP_PC(0xE4): return 290; /* RIGHT_CTRL */
    case SCREEN_KEYMAP_PC(0x13): return 291; /* PAUSE */
    case SCREEN_KEYMAP_PC(0x14): return 292; /* SCROLL_LOCK */
    case SCREEN_KEYMAP_PC(0x7F): return 293; /* NUM_LOCK */
    case SCREEN_KEYMAP_PC(0xE5): return 294; /* CAPS_LOCK */
    case SCREEN_KEYMAP_PC(0x67): return 295; /* MENU */
    default:
        return -1;
    }
}

#endif /* SCREEN_KEYMAP_H */
