#pragma once

/* Host stand-in for QNX <sys/keycodes.h>: the subset window_screen.c
 * static-asserts and reads (values match the real header). */

#define KEYCODE_PC_KEYS 0xF000
#define KEYCODE_ESCAPE (KEYCODE_PC_KEYS + 0x1B)
#define KEYCODE_RETURN (KEYCODE_PC_KEYS + 0x0D)
#define KEYCODE_HOME (KEYCODE_PC_KEYS + 0x50)
#define KEYCODE_LEFT (KEYCODE_PC_KEYS + 0x51)
#define KEYCODE_UP (KEYCODE_PC_KEYS + 0x52)
#define KEYCODE_RIGHT (KEYCODE_PC_KEYS + 0x53)
#define KEYCODE_DOWN (KEYCODE_PC_KEYS + 0x54)
#define KEYCODE_PG_UP (KEYCODE_PC_KEYS + 0x55)
#define KEYCODE_INSERT (KEYCODE_PC_KEYS + 0x63)
#define KEYCODE_F1 (KEYCODE_PC_KEYS + 0xBE)
#define KEYCODE_F12 (KEYCODE_PC_KEYS + 0xC9)
#define KEYCODE_LEFT_SHIFT (KEYCODE_PC_KEYS + 0xE1)
#define KEYCODE_LEFT_CTRL (KEYCODE_PC_KEYS + 0xE3)
#define KEYCODE_DELETE (KEYCODE_PC_KEYS + 0xFF)

#define KEY_DOWN 0x01
#define KEY_REPEAT 0x02
#define KEY_SYM_VALID 0x40
