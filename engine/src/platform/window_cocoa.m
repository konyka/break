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
};

/* ---- Key mapping (Carbon virtual key codes) ---- */

static i32 cocoa_keycode_to_index(unsigned short kc, NSString *chars) {
    /* Letters/digits: derive from the produced character when available. */
    if (chars && [chars length] > 0) {
        unichar c = [chars characterAtIndex:0];
        if (c >= 'A' && c <= 'Z') return (i32)(c - 'A' + 'a');
        if (c >= 'a' && c <= 'z') return (i32)c;
        if (c >= '0' && c <= '9') return (i32)c;
    }
    switch (kc) {
        case 53:  return 256; /* Escape */
        case 49:  return 32;  /* Space  */
        case 36:  return 257; /* Return */
        case 48:  return 259; /* Tab    */
        case 51:  return 260; /* Delete/Backspace */
        case 123: return 261; /* Left   */
        case 124: return 262; /* Right  */
        case 126: return 263; /* Up     */
        case 125: return 264; /* Down   */
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
        /* R363: align Pause/locks/Menu/KP with X11/WL/Win32 (291–309) */
        case 113: return 291; /* Pause / F15 */
        case 107: return 292; /* Scroll Lock / F14 */
        case 71:  return 293; /* Clear ≈ NumLock */
        case 57:  return 294; /* Caps Lock */
        case 110: return 295; /* Application / Menu */
        case 67:  return 296; /* KP Multiply — SSS */
        case 75:  return 297; /* KP Divide — lens flare */
        case 78:  return 298; /* KP Minus — sharpen */
        case 69:  return 299; /* KP Plus — contact shadow */
        case 82:  return 305; /* KP 0 — particle boom (not 300=MOUSE_LEFT) */
        case 83:  return 306; /* KP 1 — tornado */
        case 84:  return 307; /* KP 2 — particle trail */
        case 85:  return 308; /* KP 3 — layout */
        case 86:  return 309; /* KP 4 — AA cycle */
        default:  return -1;
    }
}

/* ---- Content view: forwards events to the InputState ---- */

@interface BreakView : NSView
@property (nonatomic, assign) Platform *platform;
@end

@implementation BreakView
- (BOOL)wantsUpdateLayer { return YES; }
- (BOOL)acceptsFirstResponder { return YES; }
- (BOOL)isFlipped { return YES; }

- (CALayer *)makeBackingLayer {
    return self.platform->layer;
}

- (void)keyDown:(NSEvent *)e {
    if (self.platform->input.frame_number == 0 && e.isARepeat) return;
    i32 idx = cocoa_keycode_to_index(e.keyCode, e.charactersIgnoringModifiers);
    if (idx >= 0) input_set_key(&self.platform->input, idx, true);
}
- (void)keyUp:(NSEvent *)e {
    i32 idx = cocoa_keycode_to_index(e.keyCode, e.charactersIgnoringModifiers);
    if (idx >= 0) input_set_key(&self.platform->input, idx, false);
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
@end

/* ---- Window delegate: tracks close ---- */

@interface BreakWindowDelegate : NSObject <NSWindowDelegate>
@property (nonatomic, assign) Platform *platform;
@end

@implementation BreakWindowDelegate
- (BOOL)windowShouldClose:(id)sender { (void)sender; self.platform->should_close = true; return NO; }
- (void)windowDidResize:(NSNotification *)n {
    (void)n;
    Platform *p = self.platform;
    NSSize sz = p->view.bounds.size;
    p->width  = (u32)sz.width;
    p->height = (u32)sz.height;
    p->layer.drawableSize = CGSizeMake(sz.width, sz.height);
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
        p->layer.drawableSize = CGSizeMake(cfg->width, cfg->height);

        p->view = [[BreakView alloc] initWithFrame:frame];
        p->view.platform = p;
        p->view.wantsLayer = YES;
        [p->window setContentView:p->view];
        [p->window makeFirstResponder:p->view];

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

InputState *platform_input(Platform *p)        { return &p->input; }
void *platform_window_native(Platform *p)      { return (void *)p->layer; }
void *platform_display_native(Platform *p)     { (void)p; return NULL; }
void *platform_surface_native(Platform *p)     { return (void *)p->layer; }

void platform_get_size(Platform *p, u32 *w, u32 *h) {
    if (w) *w = p->width;
    if (h) *h = p->height;
}

f32 platform_get_dpi(Platform *p) {
    f32 scale = (f32)[p->window backingScaleFactor];
    return 96.0f * scale;
}

i32 platform_get_scale_factor(Platform *p) {
    return (i32)[p->window backingScaleFactor];
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

void platform_mouse_set_relative(Platform *p, bool relative) {
    p->mouse_relative = relative;
    /* Decouple the hardware cursor from deltas so relative motion is unbounded. */
    CGAssociateMouseAndMouseCursorPosition(relative ? false : true);
    platform_mouse_set_visible(p, !relative);
}

#endif /* ENGINE_PLATFORM_MACOS */
