#include "ui/myui_break_input.h"

#include "mypal/my_event.h"
#include "platform/platform_text.h"

uint32_t break_ui_map_key(i32 key) {
  if (key >= 32 && key <= 126) {
    return (uint32_t)key;
  }
  switch (key) {
  case 256: return MY_KEY_ESCAPE;
  case 257: return MY_KEY_RETURN;
  case 259: return MY_KEY_TAB;
  case 260: return MY_KEY_BACKSPACE;
  case 261: return MY_KEY_LEFT;
  case 262: return MY_KEY_RIGHT;
  case 263: return MY_KEY_UP;
  case 264: return MY_KEY_DOWN;
  case 271: return MY_KEY_F1;
  case 272: return MY_KEY_F2;
  case 273: return MY_KEY_F3;
  case 274: return MY_KEY_F4;
  case 275: return MY_KEY_F5;
  case 276: return MY_KEY_F6;
  case 277: return MY_KEY_F7;
  case 278: return MY_KEY_F8;
  case 279: return MY_KEY_F9;
  case 280: return MY_KEY_F10;
  case 281: return MY_KEY_F11;
  case 282: return MY_KEY_F12;
  case 283: return MY_KEY_PAGE_UP;
  case 284: return MY_KEY_PAGE_DOWN;
  case 285: return MY_KEY_HOME;
  case 286: return MY_KEY_END;
  case 287: return MY_KEY_INSERT;
  case 288: return MY_KEY_DELETE;
  default: return MY_KEY_UNKNOWN;
  }
}

bool break_ui_should_dispatch_key(i32 key, uint8_t modifiers,
                                  bool ime_enabled) {
  if (!ime_enabled || (modifiers & MY_KEYMOD_CTRL) != 0) {
    return true;
  }
  return key < 32 || key > 126;
}

i32 break_utf8_byte_to_cp(const char* s, i32 byte) {
  return platform_utf8_byte_to_codepoints(s, byte);
}

i32 break_utf16_units_to_cp(const uint16_t* s, i32 units) {
  return platform_utf16_units_to_codepoints(s, units);
}
