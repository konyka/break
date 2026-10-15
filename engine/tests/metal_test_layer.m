/* Test-only offscreen CAMetalLayer factory so test_rhi_metal_device_contract.c
 * can stay C11. Manual reference counting (-fno-objc-arc), matching
 * window_cocoa.m: [CAMetalLayer layer] is autoreleased, so retain it and hand
 * ownership to the caller (released by metal_test_layer_destroy). */
#import <QuartzCore/CAMetalLayer.h>
#import <Metal/Metal.h>

#include <core/types.h>

void *metal_test_layer_create(u32 w, u32 h) {
    CAMetalLayer *layer = nil;
    @autoreleasepool {
        layer = [[CAMetalLayer layer] retain];
        if (layer != nil) {
            /* Same pixel format window_cocoa.m installs on its layer; the RHI
             * device derives swapchain_format from it. An explicit drawable
             * size lets the layer acquire drawables without a window. */
            layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
            layer.drawableSize = CGSizeMake((double)w, (double)h);
        }
    }
    return (void *)layer;
}

void metal_test_layer_destroy(void *layer) {
    [(CAMetalLayer *)layer release];
}
