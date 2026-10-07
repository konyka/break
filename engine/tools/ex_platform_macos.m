/**
 * @file ex_platform_macos.m
 * @brief macOS runner: Cocoa window with an NSBitmapImageRep software
 *        path and an NSOpenGLContext desktop-GL path.
 */
#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#include "explorer_internal.h"

#if defined(__APPLE__)

static app_t* g_app;
static int g_gl;
static NSOpenGLContext* g_gl_ctx;

@interface ExView : NSView
- (void)tick:(NSTimer*)timer;
@end

@implementation ExView

- (BOOL)isFlipped {
  return YES;
}

- (void)drawRect:(NSRect)rect {
  (void)rect;
  if (g_gl) {
    ex_frame_gl(g_app);
    [g_gl_ctx flush];
    return;
  }
  {
    NSBitmapImageRep* rep =
        [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:NULL
                                                pixelsWide:EX_W
                                                pixelsHigh:EX_H
                                             bitsPerSample:8
                                           samplesPerPixel:4
                                                  hasAlpha:YES
                                                  isPlanar:NO
                                            colorSpaceName:NSDeviceRGBColorSpace
                                              bitmapFormat:NSAlphaFirstBitmapFormat
                                               bytesPerRow:ex_lcd_stride(g_app)
                                                bitsPerPixel:32];
    memcpy([rep bitmapData], ex_lcd_pixels(g_app),
           (size_t)EX_H * ex_lcd_stride(g_app));
    [rep drawInRect:[self bounds]];
    [rep release];
  }
}

- (void)mouseMoved:(NSEvent*)ev {
  NSPoint p = [self convertPoint:[ev locationInWindow] fromView:nil];
  ex_pointer(g_app, (int32_t)p.x, (int32_t)p.y, 0);
}

- (void)mouseDragged:(NSEvent*)ev {
  [self mouseMoved:ev];
}

- (void)mouseDown:(NSEvent*)ev {
  NSPoint p = [self convertPoint:[ev locationInWindow] fromView:nil];
  ex_pointer(g_app, (int32_t)p.x, (int32_t)p.y, 1);
}

- (void)scrollWheel:(NSEvent*)ev {
  ex_wheel(g_app, [ev deltaY] > 0 ? 1 : -1);
}

- (void)keyDown:(NSEvent*)ev {
  const char* chars = [[ev characters] UTF8String];
  if (chars != NULL && (unsigned char)chars[0] >= ' ' &&
      (unsigned char)chars[0] <= '~')
    ex_key(g_app, chars[0]);
}

- (void)tick:(NSTimer*)timer {
  (void)timer;
  [self setNeedsDisplay:YES];
}

@end

@interface ExDelegate : NSObject <NSApplicationDelegate>
@end

@implementation ExDelegate
- (void)applicationDidFinishLaunching:(NSNotification*)n {
  (void)n;
  NSWindow* win =
      [[NSWindow alloc] initWithContentRect:NSMakeRect(100, 100, EX_W, EX_H)
                                  styleMask:NSWindowStyleMaskTitled |
                                            NSWindowStyleMaskClosable |
                                            NSWindowStyleMaskMiniaturizable |
                                            NSWindowStyleMaskResizable
                                    backing:NSBackingStoreBuffered
                                      defer:NO];
  [win setTitle:g_gl ? @"MyUI explorer [cocoa/gl]"
                     : @"MyUI explorer [cocoa/soft]"];
  ExView* view = [[ExView alloc] initWithFrame:NSMakeRect(0, 0, EX_W, EX_H)];
  [win setContentView:view];
  [win makeFirstResponder:view];
  [win setAcceptsMouseMovedEvents:YES];
  [win makeKeyAndOrderFront:nil];
  if (g_gl) {
    NSOpenGLPixelFormatAttribute attrs[] = {NSOpenGLPFAAccelerated,
                                            NSOpenGLPFADoubleBuffer, 0};
    NSOpenGLPixelFormat* pf =
        [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
    g_gl_ctx = [[NSOpenGLContext alloc] initWithFormat:pf shareContext:nil];
    [g_gl_ctx setView:view];
    [g_gl_ctx makeCurrentContext];
    ex_gl_vg_create(g_app);
  }
  [NSTimer scheduledTimerWithTimeInterval:0.008
                                   target:view
                                 selector:@selector(tick:)
                                 userInfo:nil
                                  repeats:YES];
}
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)a {
  (void)a;
  return YES;
}
@end

int ex_run_cocoa(app_t* app, int gl) {
  NSApplication* nsapp = [NSApplication sharedApplication];
  ExDelegate* delegate = [[ExDelegate alloc] init];
  g_app = app;
  g_gl = gl;
  [nsapp setDelegate:delegate];
  [nsapp run];
  return 0;
}

#endif
