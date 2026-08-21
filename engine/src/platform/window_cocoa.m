#ifdef ENGINE_PLATFORM_MACOS

/* macOS Cocoa window backend.
 *
 * Creates an NSWindow whose content view is backed by a CAMetalLayer, then
 * exposes that layer through platform_window_native() so the existing Vulkan
 * RHI can build a surface via MoltenVK (VK_EXT_metal_surface). This avoids a
 * separate native Metal RHI while giving macOS a real, linkable window.
 */

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>

#include <platform/platform.h>
#include <platform/input.h>
#include <platform/platform_text.h>
#include <core/log.h>
#include <stdlib.h>
#include <string.h>

/* ---- Engine-facing window object ---- */

@class BreakView;

struct Platform {
    NSWindow   *window;
    BreakView  *view;
    CAMetalLayer *layer;
    InputState  input;
    u32         width, height;
    bool        should_close;
    bool        is_fullscreen;
    bool        mouse_relative;
    bool        mouse_visible;
    PlatformCursor cursor;
    bool        caps_lock_latched; /* R367: track CapsLock LED for press pulses */
    PlatformTextQueue text_queue;
    PlatformImeSurrounding ime_surrounding;
    bool        ime_enabled;
    i32         ime_spot_x;
    i32         ime_spot_y;
    NSUInteger  marked_length;
};

/* ---- Key mapping (Carbon virtual key codes) ---- */

static i32 cocoa_keycode_to_index(unsigned short kc, NSString *chars) {
    /* R365: KP keyCodes first — charsIgnoringModifiers often yields '0'..'9'
     * for the keypad and would steal boom/tornado/CG bindings. */
    switch (kc) {
        case 82:  return 305; /* KP 0 — particle boom */
        case 83:  return 306; /* KP 1 — tornado */
        case 84:  return 307; /* KP 2 — particle trail */
        case 85:  return 308; /* KP 3 — layout */
        case 86:  return 309; /* KP 4 — AA cycle */
        case 87:  return 310; /* KP 5 — temp- */
        case 88:  return 311; /* KP 6 — temp+ */
        case 89:  return 312; /* KP 7 — tint- */
        case 91:  return 313; /* KP 8 — tint+ */
        case 92:  return 314; /* KP 9 — color grade */
        case 65:  return 315; /* KP Decimal — lensfx cycle */
        case 67:  return 296; /* KP Multiply — SSS */
        case 75:  return 297; /* KP Divide — lens flare */
        case 78:  return 298; /* KP Minus — sharpen */
        case 69:  return 299; /* KP Plus — contact shadow */
        case 50:  return 96;  /* Grave / backtick — ImUI */
        default:  break;
    }
    /* R366: letters/digits/printable punctuation from characters when available. */
    if (chars && [chars length] > 0) {
        unichar c = [chars characterAtIndex:0];
        if (c >= 'A' && c <= 'Z') return (i32)(c - 'A' + 'a');
        if (c >= 'a' && c <= 'z') return (i32)c;
        if (c >= '0' && c <= '9') return (i32)c;
        if (c >= 33 && c <= 126) return (i32)c; /* punctuation used by Help hotkeys */
    }
    switch (kc) {
        case 53:  return 256; /* Escape */
        case 49:  return 32;  /* Space  */
        case 36:  return 257; /* Return */
        case 76:  return 257; /* KP Enter — Select (R371) */
        case 48:  return 259; /* Tab    */
        case 51:  return 260; /* Delete/Backspace */
        case 117: return 288; /* Forward Delete */
        case 114: return 287; /* Insert — GPU frustum cull */
        case 115: return 285; /* Home */
        case 119: return 286; /* End */
        case 116: return 283; /* Page Up */
        case 121: return 284; /* Page Down */
        case 123: return 261; /* Left   */
        case 124: return 262; /* Right  */
        case 126: return 263; /* Up     */
        case 125: return 264; /* Down   */
        case 27:  return (i32)'-';
        case 24:  return (i32)'=';
        case 33:  return (i32)'[';
        case 30:  return (i32)']';
        case 41:  return (i32)';';
        case 39:  return (i32)'\'';
        case 43:  return (i32)',';
        case 47:  return (i32)'.';
        case 44:  return (i32)'/';
        case 42:  return (i32)'\\';
        case 122: return 271; /* F1 */
        case 120: return 272; /* F2 */
        case 99:  return 273; /* F3 */
        case 118: return 274; /* F4 */
        case 96:  return 275; /* F5 */
        case 97:  return 276; /* F6 */
        case 98:  return 277; /* F7 */
        case 100: return 278; /* F8 */
        case 101: return 279; /* F9 */
        case 109: return 280; /* F10 */
        case 103: return 281; /* F11 */
        case 111: return 282; /* F12 */
        case 113: return 291; /* Pause / F15 */
        case 107: return 292; /* Scroll Lock / F14 */
        case 71:  return 293; /* Clear ≈ NumLock */
        case 57:  return 294; /* Caps Lock */
        case 110: return 295; /* Application / Menu */
        default:  return -1;
    }
}

/* ---- Content view: forwards events to the InputState ---- */

@interface BreakView : NSView <NSTextInputClient>
@property (nonatomic, assign) Platform *platform;
@end

@implementation BreakView
- (BOOL)wantsUpdateLayer { return YES; }
- (BOOL)acceptsFirstResponder { return YES; }
- (BOOL)isFlipped { return YES; }

- (void)resetCursorRects {
    NSCursor *cursor = [NSCursor arrowCursor];
    switch (self.platform->cursor) {
        case PLATFORM_CURSOR_TEXT:
            cursor = [NSCursor IBeamCursor];
            break;
        case PLATFORM_CURSOR_HAND:
            cursor = [NSCursor pointingHandCursor];
            break;
        case PLATFORM_CURSOR_ARROW:
        default:
            break;
    }
    [self addCursorRect:self.bounds cursor:cursor];
}

- (CALayer *)makeBackingLayer {
    return self.platform->layer;
}

- (void)keyDown:(NSEvent *)e {
    if (self.platform->input.frame_number == 0 && e.isARepeat) return;
    i32 idx = cocoa_keycode_to_index(e.keyCode, e.charactersIgnoringModifiers);
    if (idx >= 0) input_set_key(&self.platform->input, idx, true);
    if (self.platform->ime_enabled) {
        [self interpretKeyEvents:@[e]];
    }
}
- (void)keyUp:(NSEvent *)e {
    i32 idx = cocoa_keycode_to_index(e.keyCode, e.charactersIgnoringModifiers);
    if (idx >= 0) input_set_key(&self.platform->input, idx, false);
}
/* R365/R366/R367: modifiers arrive via flagsChanged, not keyDown/keyUp. */
- (void)flagsChanged:(NSEvent *)e {
    NSUInteger flags = e.modifierFlags;
    Platform *p = self.platform;
    input_set_key(&p->input, 289,
                  (flags & NSEventModifierFlagShift) != 0);
    input_set_key(&p->input, 290,
                  (flags & NSEventModifierFlagControl) != 0);
    /* CapsLock is sticky LED state — pulse a press edge on every polarity change
     * so CapsLock:AutoExp toggles once per keypress (not every other). */
    bool caps = (flags & NSEventModifierFlagCapsLock) != 0;
    if (caps != p->caps_lock_latched) {
        input_set_key(&p->input, 294, false);
        input_set_key(&p->input, 294, true);
        p->caps_lock_latched = caps;
    }
    (void)e;
}

- (void)mouseMovedCommon:(NSEvent *)e {
    Platform *p = self.platform;
    if (p->mouse_relative) {
        p->input.mouse_dx += (f32)e.deltaX;
        p->input.mouse_dy += (f32)e.deltaY;
    } else {
        NSPoint pt = [self convertPoint:e.locationInWindow fromView:nil];
        input_set_mouse(&p->input, (f32)pt.x, (f32)pt.y);
    }
}
- (void)mouseMoved:(NSEvent *)e        { [self mouseMovedCommon:e]; }
- (void)mouseDragged:(NSEvent *)e      { [self mouseMovedCommon:e]; }
- (void)rightMouseDragged:(NSEvent *)e { [self mouseMovedCommon:e]; }
- (void)otherMouseDragged:(NSEvent *)e { [self mouseMovedCommon:e]; }

- (void)mouseDown:(NSEvent *)e        { (void)e; input_set_key(&self.platform->input, INPUT_MOUSE_LEFT,  true); }
- (void)mouseUp:(NSEvent *)e          { (void)e; input_set_key(&self.platform->input, INPUT_MOUSE_LEFT,  false); }
- (void)rightMouseDown:(NSEvent *)e   { (void)e; input_set_key(&self.platform->input, INPUT_MOUSE_RIGHT, true); }
- (void)rightMouseUp:(NSEvent *)e     { (void)e; input_set_key(&self.platform->input, INPUT_MOUSE_RIGHT, false); }
- (void)otherMouseDown:(NSEvent *)e   { (void)e; input_set_key(&self.platform->input, INPUT_MOUSE_MIDDLE, true); }
- (void)otherMouseUp:(NSEvent *)e     { (void)e; input_set_key(&self.platform->input, INPUT_MOUSE_MIDDLE, false); }

- (void)scrollWheel:(NSEvent *)e {
    input_set_scroll(&self.platform->input, (f32)e.scrollingDeltaX / 10.0f,
                     (f32)e.scrollingDeltaY / 10.0f);
}

- (void)insertText:(id)string replacementRange:(NSRange)replacementRange {
    NSString *text;
    NSUInteger utf8_bytes;
    (void)replacementRange;
    if ([string isKindOfClass:[NSAttributedString class]]) {
        text = [(NSAttributedString *)string string];
    } else {
        text = (NSString *)string;
    }
    utf8_bytes = text != nil ? [text lengthOfBytesUsingEncoding:NSUTF8StringEncoding]
                             : 0;
    if (self.platform->ime_enabled && text != nil &&
        utf8_bytes <= (NSUInteger)PLATFORM_TEXT_MAX_BYTES) {
        (void)platform_text_queue_push(&self.platform->text_queue,
                                       PLATFORM_TEXT_COMMIT,
                                       [text UTF8String], 0);
    }
    self.platform->marked_length = 0;
}

- (void)setMarkedText:(id)string selectedRange:(NSRange)selectedRange
      replacementRange:(NSRange)replacementRange {
    NSString *text;
    NSUInteger count;
    unichar *units;
    char *utf8;
    i32 cursor;
    (void)replacementRange;
    if ([string isKindOfClass:[NSAttributedString class]]) {
        text = [(NSAttributedString *)string string];
    } else {
        text = (NSString *)string;
    }
    if (!self.platform->ime_enabled || text == nil) return;
    count = [text length];
    if (count > (NSUInteger)PLATFORM_TEXT_MAX_BYTES ||
        count > SIZE_MAX / sizeof(*units)) return;
    units = count > 0 ? malloc(count * sizeof(*units)) : NULL;
    if (count > 0 && units == NULL) return;
    if (count > 0) [text getCharacters:units range:NSMakeRange(0, count)];
    utf8 = platform_utf16_to_utf8_alloc((const uint16_t *)units, count);
    if (utf8 == NULL) {
        free(units);
        return;
    }
    cursor = platform_utf16_units_to_codepoints(
        (const uint16_t *)units,
        selectedRange.location < count ? (i32)selectedRange.location : (i32)count);
    (void)platform_text_queue_push(&self.platform->text_queue,
                                   PLATFORM_TEXT_PREEDIT, utf8, cursor);
    self.platform->marked_length = count;
    free(utf8);
    free(units);
}

- (void)unmarkText {
    if (self.platform->marked_length != 0) {
        (void)platform_text_queue_push(&self.platform->text_queue,
                                       PLATFORM_TEXT_PREEDIT, "", 0);
    }
    self.platform->marked_length = 0;
}

- (NSRange)selectedRange {
    i32 cursor = platform_utf8_byte_to_utf16_units(
        self.platform->ime_surrounding.utf8, self.platform->ime_surrounding.cursor);
    i32 anchor = platform_utf8_byte_to_utf16_units(
        self.platform->ime_surrounding.utf8, self.platform->ime_surrounding.anchor);
    NSUInteger start = (NSUInteger)(cursor < anchor ? cursor : anchor);
    NSUInteger length = (NSUInteger)(cursor < anchor ? anchor - cursor
                                                      : cursor - anchor);
    return NSMakeRange(start, length);
}

- (NSRange)markedRange {
    NSRange selected = [self selectedRange];
    return self.platform->marked_length == 0 ? NSMakeRange(NSNotFound, 0)
                                             : NSMakeRange(selected.location,
                                                           self.platform->marked_length);
}

- (BOOL)hasMarkedText {
    return self.platform->marked_length != 0;
}

- (NSArray<NSAttributedStringKey> *)validAttributesForMarkedText {
    return [NSArray array];
}

- (NSAttributedString *)attributedSubstringForProposedRange:(NSRange)range
                                                 actualRange:(NSRangePointer)actualRange {
    NSString *text = [NSString stringWithUTF8String:self.platform->ime_surrounding.utf8];
    NSRange bounded;
    if (text == nil) return nil;
    bounded = NSIntersectionRange(range, NSMakeRange(0, [text length]));
    if (actualRange != NULL) *actualRange = bounded;
    return [[[NSAttributedString alloc] initWithString:[text substringWithRange:bounded]]
        autorelease];
}

- (NSUInteger)characterIndexForPoint:(NSPoint)point {
    (void)point;
    return [self selectedRange].location;
}

- (NSRect)firstRectForCharacterRange:(NSRange)range actualRange:(NSRangePointer)actualRange {
    NSRect local = NSMakeRect(self.platform->ime_spot_x, self.platform->ime_spot_y,
                              1.0, 16.0);
    NSRect window_rect = [self convertRect:local toView:nil];
    if (actualRange != NULL) *actualRange = range;
    return [self.window convertRectToScreen:window_rect];
}

- (void)doCommandBySelector:(SEL)selector {
    (void)selector;
}
@end

/* ---- Window delegate: tracks close ---- */

@interface BreakWindowDelegate : NSObject <NSWindowDelegate>
@property (nonatomic, assign) Platform *platform;
@end

static void cocoa_update_drawable_size(Platform *p) {
    NSSize size;
    CGFloat scale;
    if (p == NULL || p->window == nil || p->layer == nil) return;
    size = p->view != nil ? p->view.bounds.size : p->window.contentView.bounds.size;
    scale = [p->window backingScaleFactor];
    if (scale <= 0.0) scale = 1.0;
    p->width = (u32)ceil(size.width);
    p->height = (u32)ceil(size.height);
    p->layer.contentsScale = scale;
    p->layer.drawableSize = CGSizeMake(ceil(size.width * scale),
                                       ceil(size.height * scale));
}

@implementation BreakWindowDelegate
- (BOOL)windowShouldClose:(id)sender { (void)sender; self.platform->should_close = true; return NO; }
- (void)windowDidResize:(NSNotification *)n {
    (void)n;
    cocoa_update_drawable_size(self.platform);
}
- (void)windowDidChangeBackingProperties:(NSNotification *)n {
    (void)n;
    cocoa_update_drawable_size(self.platform);
}
/* R368: match X11 FocusOut / Wayland keyboard_leave — release stuck keys. */
- (void)windowDidResignKey:(NSNotification *)n {
    (void)n;
    input_release_all(&self.platform->input);
}
@end

/* ---- Platform API ---- */

Platform *platform_create(const PlatformConfig *cfg) {
    @autoreleasepool {
        Platform *p = calloc(1, sizeof(Platform));
        if (!p) { LOG_FATAL("Failed to allocate Platform"); return NULL; }

        p->width = cfg->width;
        p->height = cfg->height;
        p->mouse_visible = true;
        p->cursor = PLATFORM_CURSOR_ARROW;

        [NSApplication sharedApplication];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

        NSRect frame = NSMakeRect(0, 0, cfg->width, cfg->height);
        NSWindowStyleMask style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
                                  NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable;
        p->window = [[NSWindow alloc] initWithContentRect:frame
                                                styleMask:style
                                                  backing:NSBackingStoreBuffered
                                                    defer:NO];
        [p->window setTitle:[NSString stringWithUTF8String:cfg->title]];

        /* Retain explicitly: [CAMetalLayer layer] is autoreleased and would die
         * with the autoreleasepool below (no ARC in this translation unit). */
        p->layer = [[CAMetalLayer layer] retain];
        p->layer.pixelFormat = MTLPixelFormatBGRA8Unorm;

        p->view = [[BreakView alloc] initWithFrame:frame];
        p->view.platform = p;
        p->view.wantsLayer = YES;
        [p->window setContentView:p->view];
        [p->window makeFirstResponder:p->view];
        cocoa_update_drawable_size(p);

        BreakWindowDelegate *del = [[BreakWindowDelegate alloc] init];
        del.platform = p;
        [p->window setDelegate:del];

        [p->window center];
        [p->window makeKeyAndOrderFront:nil];
        [NSApp activateIgnoringOtherApps:YES];

        input_init(&p->input);

        LOG_INFO("Platform initialized (Cocoa/MoltenVK): %ux%u \"%s\"",
                 cfg->width, cfg->height, cfg->title);
        return p;
    }
}

void platform_destroy(Platform *p) {
    if (!p) return;
    @autoreleasepool {
        if (p->window) [p->window close];
    }
    platform_text_queue_destroy(&p->text_queue);
    free(p);
    LOG_INFO("Platform destroyed (Cocoa)");
}

PlatformEventResult platform_poll(Platform *p) {
    input_new_frame(&p->input);
    @autoreleasepool {
        NSEvent *e;
        while ((e = [NSApp nextEventMatchingMask:NSEventMaskAny
                                       untilDate:[NSDate distantPast]
                                          inMode:NSDefaultRunLoopMode
                                         dequeue:YES])) {
            [NSApp sendEvent:e];
        }
    }
    if (p->should_close) return PLATFORM_EVENT_QUIT;
    return PLATFORM_EVENT_NONE;
}

u32 platform_poll_text(Platform *p, PlatformTextEvent *out, u32 max_events) {
    return p != NULL ? platform_text_queue_pop(&p->text_queue, out, max_events)
                     : 0;
}

void platform_ime_set_enabled(Platform *p, bool enabled) {
    if (p == NULL || p->ime_enabled == enabled) return;
    p->ime_enabled = enabled;
    if (!enabled) [p->view unmarkText];
}

bool platform_ime_is_enabled(Platform *p) {
    return p != NULL && p->ime_enabled;
}

void platform_ime_set_surrounding(Platform *p, const char *utf8, i32 cursor,
                                  i32 anchor) {
    if (p != NULL) {
        platform_ime_surrounding_set(&p->ime_surrounding, utf8,
                                     cursor > 0 ? (usize)cursor : 0,
                                     anchor > 0 ? (usize)anchor : 0);
    }
}

void platform_ime_set_spot(Platform *p, i32 x, i32 y) {
    if (p != NULL) {
        p->ime_spot_x = x;
        p->ime_spot_y = y;
    }
}

InputState *platform_input(Platform *p)        { return &p->input; }
void *platform_window_native(Platform *p)      { return (void *)p->layer; }
void *platform_display_native(Platform *p)     { (void)p; return NULL; }
void *platform_surface_native(Platform *p)     { return (void *)p->layer; }

void platform_get_size(Platform *p, u32 *w, u32 *h) {
    if (w) *w = p->width;
    if (h) *h = p->height;
}

void platform_get_logical_size(Platform *p, u32 *w, u32 *h) {
    if (w) *w = p != NULL ? p->width : 0;
    if (h) *h = p != NULL ? p->height : 0;
}

void platform_get_drawable_size(Platform *p, u32 *w, u32 *h) {
    if (p == NULL) {
        if (w) *w = 0;
        if (h) *h = 0;
        return;
    }
    if (w) *w = (u32)ceil(p->layer.drawableSize.width);
    if (h) *h = (u32)ceil(p->layer.drawableSize.height);
}

f32 platform_get_dpi(Platform *p) {
    f32 scale = (f32)[p->window backingScaleFactor];
    return 96.0f * scale;
}

f32 platform_get_content_scale(Platform *p) {
    return p != NULL ? (f32)[p->window backingScaleFactor] : 1.0f;
}

f32 platform_get_input_scale(Platform *p) {
    (void)p;
    return 1.0f;
}

i32 platform_get_scale_factor(Platform *p) {
    return (i32)(platform_get_content_scale(p) + 0.5f);
}

u32 platform_get_monitor_count(Platform *p) {
    (void)p;
    return (u32)[[NSScreen screens] count];
}

bool platform_get_monitor_info(Platform *p, u32 index, MonitorInfo *out) {
    (void)p;
    if (!out) return false;
    NSArray<NSScreen *> *screens = [NSScreen screens];
    if (index >= [screens count]) return false;
    NSScreen *s = screens[index];
    NSRect fr = [s frame];
    memset(out, 0, sizeof(*out));
    snprintf(out->name, sizeof(out->name), "%s",
             [[s localizedName] UTF8String] ?: "Display");
    out->x = (i32)fr.origin.x;
    out->y = (i32)fr.origin.y;
    out->width  = (u32)fr.size.width;
    out->height = (u32)fr.size.height;
    out->scale  = (i32)[s backingScaleFactor];
    out->dpi    = 96.0f * (f32)out->scale;
    out->primary = (index == 0);
    return true;
}

void platform_toggle_fullscreen(Platform *p) {
    [p->window toggleFullScreen:nil];
    p->is_fullscreen = !p->is_fullscreen;
}

void platform_mouse_capture(Platform *p, bool capture) {
    (void)p; (void)capture;
}

void platform_mouse_set_visible(Platform *p, bool visible) {
    if (visible == p->mouse_visible) return;
    p->mouse_visible = visible;
    if (visible) [NSCursor unhide];
    else         [NSCursor hide];
}

bool platform_cursor_set(Platform *p, PlatformCursor cursor) {
    if (p == NULL || cursor > PLATFORM_CURSOR_HAND) return false;
    p->cursor = cursor;
    if (p->window != nil && p->view != nil)
        [p->window invalidateCursorRectsForView:p->view];
    return true;
}

bool platform_window_begin_move(Platform *p) {
    NSEvent *event;
    if (p == NULL || p->window == nil) return false;
    event = [NSApp currentEvent];
    if (event == nil || event.type != NSEventTypeLeftMouseDown) return false;
    [p->window performWindowDragWithEvent:event];
    return true;
}

bool platform_needs_client_decoration(Platform *p) {
    (void)p;
    return false;
}

bool platform_clipboard_set_text(Platform *p, const char *utf8) {
    NSString *text;
    NSPasteboard *pasteboard;
    (void)p;
    if (utf8 == NULL) return false;
    text = [NSString stringWithUTF8String:utf8];
    if (text == nil) return false;
    pasteboard = [NSPasteboard generalPasteboard];
    [pasteboard clearContents];
    return [pasteboard setString:text forType:NSPasteboardTypeString];
}

bool platform_clipboard_get_text(Platform *p, char *out, usize out_size) {
    NSString *text;
    const char *utf8;
    (void)p;
    if (out == NULL || out_size == 0) return false;
    text = [[NSPasteboard generalPasteboard] stringForType:NSPasteboardTypeString];
    utf8 = text != nil ? [text UTF8String] : NULL;
    if (utf8 == NULL) return false;
    (void)platform_utf8_copy(out, out_size, utf8);
    return true;
}

PlatformClipboardResult platform_clipboard_get_text_alloc(Platform *p,
                                                           char **out) {
    NSString *text;
    const char *utf8;
    (void)p;
    if (out == NULL) return PLATFORM_CLIPBOARD_EMPTY;
    *out = NULL;
    text = [[NSPasteboard generalPasteboard] stringForType:NSPasteboardTypeString];
    utf8 = text != nil ? [text UTF8String] : NULL;
    if (utf8 == NULL) return PLATFORM_CLIPBOARD_EMPTY;
    *out = malloc(strlen(utf8) + 1);
    if (*out != NULL) strcpy(*out, utf8);
    return *out != NULL ? PLATFORM_CLIPBOARD_READY : PLATFORM_CLIPBOARD_EMPTY;
}

void platform_mouse_set_relative(Platform *p, bool relative) {
    p->mouse_relative = relative;
    /* Decouple the hardware cursor from deltas so relative motion is unbounded. */
    CGAssociateMouseAndMouseCursorPosition(relative ? false : true);
    platform_mouse_set_visible(p, !relative);
}

#endif /* ENGINE_PLATFORM_MACOS */
