/**
 * @file my_event.h
 * @brief Unified input/window event structure for all PAL ports.
 *
 * Key codes: printable ASCII characters (32..126) map to themselves;
 * non-printable keys use named values from MY_KEY_RETURN (0x100) up.
 * Ports translate native codes with a small table (see x11 keymap).
 */
#ifndef MY_EVENT_H
#define MY_EVENT_H

#include "myc/my_types.h"

#include <string.h>

/** @brief Event type tag. */
typedef enum my_event_type_t {
  MY_EVENT_NONE = 0,
  MY_EVENT_QUIT,         /**< window close requested / app quit */
  MY_EVENT_POINTER_DOWN, /**< mouse/touch press */
  MY_EVENT_POINTER_MOVE,
  MY_EVENT_POINTER_UP,
  MY_EVENT_POINTER_WHEEL, /**< wheel/scroll: pointer.delta (rows, +up -down) */
  MY_EVENT_KEY_DOWN,
  MY_EVENT_KEY_UP,
  MY_EVENT_IME_PREEDIT, /**< IME composing text update (M13a) */
  MY_EVENT_IME_COMMIT,  /**< IME committed text (M13a) */
  MY_EVENT_IME_DELETE_SURROUNDING, /**< delete UTF-8 bytes around caret */
  MY_EVENT_RESIZE, /**< window size changed */
  MY_EVENT_PAINT,  /**< window needs redraw */
  MY_EVENT_USER    /**< app-defined, posted via main loop */
} my_event_type_t;

/**
 * @brief Key code. Printable ASCII (32..126) maps to itself.
 */
typedef enum my_key_t {
  MY_KEY_UNKNOWN = 0,
  /* 32..126: printable ASCII, identity mapping */
  MY_KEY_RETURN = 0x100,
  MY_KEY_ESCAPE,
  MY_KEY_BACKSPACE,
  MY_KEY_TAB,
  MY_KEY_LEFT,
  MY_KEY_RIGHT,
  MY_KEY_UP,
  MY_KEY_DOWN,
  MY_KEY_HOME,
  MY_KEY_END,
  MY_KEY_PAGE_UP,
  MY_KEY_PAGE_DOWN,
  MY_KEY_INSERT,
  MY_KEY_DELETE,
  MY_KEY_F1,
  MY_KEY_F2,
  MY_KEY_F3,
  MY_KEY_F4,
  MY_KEY_F5,
  MY_KEY_F6,
  MY_KEY_F7,
  MY_KEY_F8,
  MY_KEY_F9,
  MY_KEY_F10,
  MY_KEY_F11,
  MY_KEY_F12
} my_key_t;

/** @brief Modifier bitmask for key/pointer events. */
typedef enum my_keymod_t {
  MY_KEYMOD_NONE = 0,
  MY_KEYMOD_SHIFT = 1,
  MY_KEYMOD_CTRL = 2,
  MY_KEYMOD_ALT = 4
} my_keymod_t;

/** @brief Unified event. Payload union is a named member (C99/-pedantic). */
typedef struct my_event_t {
  my_event_type_t type;
  uint64_t time_ms; /**< event time, monotonic clock */
  union my_event_payload_t {
    struct {
      int32_t x;
      int32_t y;
      uint8_t button; /**< 1 = left, 2 = middle, 3 = right */
      uint8_t modifiers; /**< my_keymod_t bitmask */
      int32_t delta; /**< POINTER_WHEEL: scroll delta in rows */
    } pointer;
    struct {
      uint32_t key;       /**< my_key_t or ASCII */
      uint8_t modifiers;  /**< my_keymod_t bitmask */
    } key;
    struct {
      const char* text; /**< UTF-8, borrowed: valid during dispatch */
      int32_t cursor;   /**< PREEDIT: caret in codepoints (else unused) */
      int32_t before;   /**< DELETE_SURROUNDING: UTF-8 bytes before caret */
      int32_t after;    /**< DELETE_SURROUNDING: UTF-8 bytes after caret */
    } ime;
    struct {
      int32_t w;
      int32_t h;
    } resize;
    struct {
      void* data; /**< app-defined payload for MY_EVENT_USER */
    } user;
  } u;
} my_event_t;

/** @brief Initialize an event of the given type (payload zeroed). */
static inline my_event_t my_event_init(my_event_type_t type) {
  my_event_t e;
  e.type = type;
  e.time_ms = 0;
  memset(&e.u, 0, sizeof(e.u)); /* M20b: the union must start zeroed —
                                 * garbage modifiers otherwise */
  return e;
}

#endif /* MY_EVENT_H */
