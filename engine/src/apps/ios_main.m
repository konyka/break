#import <UIKit/UIKit.h>
#import <QuartzCore/CAMetalLayer.h>

#include <apps/engine_demo.h>
#include <core/log.h>
#include <platform/input.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define IOS_DEMO_EVENT_CAPACITY 128u
#define IOS_DEMO_STACK_SIZE (16u * 1024u * 1024u)

typedef enum {
    IOS_DEMO_TOUCH_MOVE,
    IOS_DEMO_TOUCH_DOWN,
    IOS_DEMO_TOUCH_UP,
} IOSDemoEventType;

typedef struct {
    IOSDemoEventType type;
    f32 x, y;
} IOSDemoEvent;

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t condition;
    bool sync_ready;
    bool suspended;
    bool surface_suspended;
    bool stop;
    bool input_reset_pending;
    u32 logical_width, logical_height;
    u32 drawable_width, drawable_height;
    f32 content_scale;
    u64 viewport_generation;
    u64 applied_generation;
    IOSDemoEvent events[IOS_DEMO_EVENT_CAPACITY];
    u32 event_head, event_count;
    u32 dropped_events;
    EngineHost engine_host;
    EngineConfig config;
} IOSDemoHost;

typedef struct {
    IOSDemoHost *host;
    int argc;
    char **argv;
} IOSDemoThreadArgs;

static BOOL ios_prepare_working_directory(void)
{
    @autoreleasepool {
        NSFileManager *files = [NSFileManager defaultManager];
        NSArray<NSString *> *paths = NSSearchPathForDirectoriesInDomains(
            NSCachesDirectory, NSUserDomainMask, YES);
        if ([paths count] == 0u) {
            NSLog(@"iOS demo: Caches directory is unavailable");
            return NO;
        }
        NSString *cache = [[paths objectAtIndex:0]
            stringByAppendingPathComponent:@"PureCEngine"];
        NSString *staging = [[cache stringByDeletingLastPathComponent]
            stringByAppendingPathComponent:[NSString stringWithFormat:
                @"PureCEngine-staging-%@", [[NSUUID UUID] UUIDString]]];
        NSError *error = nil;
        if (![files createDirectoryAtPath:staging withIntermediateDirectories:YES
                               attributes:nil error:&error]) {
            NSLog(@"iOS demo: cannot create working directory %@: %@", staging, error);
            return NO;
        }
        NSString *resources = [[NSBundle mainBundle] resourcePath];
        for (NSString *name in @[@"assets", @"shaders"]) {
            NSString *source = [resources stringByAppendingPathComponent:name];
            NSString *destination = [staging stringByAppendingPathComponent:name];
            if (![files copyItemAtPath:source toPath:destination error:&error]) {
                NSLog(@"iOS demo: cannot stage %@: %@", source, error);
                [files removeItemAtPath:staging error:nil];
                return NO;
            }
        }
        if ([files fileExistsAtPath:cache] &&
            ![files removeItemAtPath:cache error:&error]) {
            NSLog(@"iOS demo: cannot replace old working directory %@: %@", cache, error);
            [files removeItemAtPath:staging error:nil];
            return NO;
        }
        if (![files moveItemAtPath:staging toPath:cache error:&error]) {
            NSLog(@"iOS demo: cannot publish working directory %@: %@", cache, error);
            [files removeItemAtPath:staging error:nil];
            return NO;
        }
        if (chdir([cache fileSystemRepresentation]) != 0) {
            NSLog(@"iOS demo: chdir(%@) failed: %s", cache, strerror(errno));
            return NO;
        }
        LOG_INFO("iOS demo working directory: %s", [cache fileSystemRepresentation]);
        return YES;
    }
}

static BOOL ios_host_init(IOSDemoHost *host)
{
    memset(host, 0, sizeof(*host));
    if (pthread_mutex_init(&host->mutex, NULL) != 0) return NO;
    if (pthread_cond_init(&host->condition, NULL) != 0) {
        pthread_mutex_destroy(&host->mutex);
        return NO;
    }
    host->sync_ready = true;
    host->content_scale = 1.0f;
    host->engine_host.context = host;
    return YES;
}

static BOOL ios_host_update_view(UIView *view, IOSDemoHost *host)
{
    CAMetalLayer *layer = (CAMetalLayer *)[view layer];
    CGSize bounds = [view bounds].size;
    CGFloat scale = [view traitCollection].displayScale;
    if ([view window].windowScene != nil)
        scale = [view window].windowScene.screen.scale;
    double logical_width = ceil((double)bounds.width);
    double logical_height = ceil((double)bounds.height);
    double drawable_width = ceil((double)bounds.width * (double)scale);
    double drawable_height = ceil((double)bounds.height * (double)scale);
    if (!isfinite(scale) || scale <= 0.0 ||
        !isfinite(logical_width) || !isfinite(logical_height) ||
        !isfinite(drawable_width) || !isfinite(drawable_height) ||
        logical_width < 1.0 || logical_height < 1.0 ||
        drawable_width < 1.0 || drawable_height < 1.0 ||
        logical_width > PLATFORM_MAX_WINDOW_DIMENSION ||
        logical_height > PLATFORM_MAX_WINDOW_DIMENSION ||
        drawable_width > PLATFORM_MAX_WINDOW_DIMENSION ||
        drawable_height > PLATFORM_MAX_WINDOW_DIMENSION) return NO;

    if ([view contentScaleFactor] != scale) [view setContentScaleFactor:scale];
    if ([layer contentsScale] != scale) [layer setContentsScale:scale];
    CGSize drawable_size = CGSizeMake((CGFloat)drawable_width, (CGFloat)drawable_height);
    if (!CGSizeEqualToSize([layer drawableSize], drawable_size))
        [layer setDrawableSize:drawable_size];

    pthread_mutex_lock(&host->mutex);
    if (host->logical_width != (u32)logical_width ||
        host->logical_height != (u32)logical_height ||
        host->drawable_width != (u32)drawable_width ||
        host->drawable_height != (u32)drawable_height ||
        host->content_scale != (f32)scale) {
        host->logical_width = (u32)logical_width;
        host->logical_height = (u32)logical_height;
        host->drawable_width = (u32)drawable_width;
        host->drawable_height = (u32)drawable_height;
        host->content_scale = (f32)scale;
        host->viewport_generation++;
        if (host->viewport_generation == 0u) host->viewport_generation++;
    }
    pthread_mutex_unlock(&host->mutex);
    return YES;
}

static void ios_host_set_suspended(IOSDemoHost *host, bool suspended)
{
    bool changed;
    if (host == NULL || !host->sync_ready) return;
    pthread_mutex_lock(&host->mutex);
    changed = host->suspended != suspended;
    host->suspended = suspended;
    if (suspended) {
        host->input_reset_pending = true;
        host->event_head = 0u;
        host->event_count = 0u;
    }
    pthread_cond_broadcast(&host->condition);
    pthread_mutex_unlock(&host->mutex);
    if (changed) LOG_INFO("iOS host: %s", suspended ? "suspended" : "resumed");
}

static void ios_host_request_stop(IOSDemoHost *host)
{
    if (host == NULL || !host->sync_ready) return;
    pthread_mutex_lock(&host->mutex);
    host->stop = true;
    pthread_cond_broadcast(&host->condition);
    pthread_mutex_unlock(&host->mutex);
}

static void ios_host_push_event(IOSDemoHost *host, IOSDemoEventType type,
                                UITouch *touch, UIView *view)
{
    CGPoint point = [touch locationInView:view];
    IOSDemoEvent event = { type, (f32)point.x, (f32)point.y };
    pthread_mutex_lock(&host->mutex);
    if (host->stop || host->suspended) {
        pthread_mutex_unlock(&host->mutex);
        return;
    }
    if (host->event_count == IOS_DEMO_EVENT_CAPACITY) {
        host->dropped_events += host->event_count;
        host->event_head = 0u;
        host->event_count = 0u;
        host->input_reset_pending = true;
    }
    u32 index = (host->event_head + host->event_count) % IOS_DEMO_EVENT_CAPACITY;
    host->events[index] = event;
    host->event_count++;
    pthread_mutex_unlock(&host->mutex);
}

static bool ios_host_poll(void *context, Engine *engine)
{
    IOSDemoHost *host = context;
    IOSDemoEvent events[IOS_DEMO_EVENT_CAPACITY];
    u32 count, dropped;
    bool reset_input;
    InputState *input = platform_input(engine->platform);

    pthread_mutex_lock(&host->mutex);
    while (host->suspended && !host->stop) {
        if (!host->surface_suspended) {
            platform_mobile_notify_suspend(engine->platform);
            input_release_all(input);
            host->surface_suspended = true;
        }
        int result = pthread_cond_wait(&host->condition, &host->mutex);
        if (result != 0) {
            pthread_mutex_unlock(&host->mutex);
            LOG_ERROR("iOS demo: condition wait failed: %s", strerror(result));
            return false;
        }
    }
    if (host->stop) {
        pthread_mutex_unlock(&host->mutex);
        return false;
    }
    if (host->surface_suspended) {
        platform_mobile_notify_resume(engine->platform);
        host->surface_suspended = false;
    }
    if (host->applied_generation != host->viewport_generation) {
        if (!platform_mobile_resize(engine->platform,
                                    host->logical_width, host->logical_height,
                                    host->drawable_width, host->drawable_height,
                                    host->content_scale)) {
            pthread_mutex_unlock(&host->mutex);
            LOG_ERROR("iOS demo: invalid viewport or suspended surface");
            return false;
        }
        host->applied_generation = host->viewport_generation;
        LOG_INFO("iOS viewport: logical=%ux%u drawable=%ux%u scale=%.2f",
                 host->logical_width, host->logical_height,
                 host->drawable_width, host->drawable_height,
                 (f64)host->content_scale);
    }
    reset_input = host->input_reset_pending;
    host->input_reset_pending = false;
    dropped = host->dropped_events;
    host->dropped_events = 0u;
    count = host->event_count;
    for (u32 i = 0u; i < count; ++i)
        events[i] = host->events[(host->event_head + i) % IOS_DEMO_EVENT_CAPACITY];
    host->event_head = 0u;
    host->event_count = 0u;
    pthread_mutex_unlock(&host->mutex);

    if (dropped > 0u)
        LOG_WARN("iOS demo: coalesced %u touch events after queue overflow", dropped);
    if (reset_input) input_release_all(input);
    for (u32 i = 0u; i < count; ++i) {
        input_set_mouse(input, events[i].x, events[i].y);
        if (events[i].type != IOS_DEMO_TOUCH_MOVE)
            input_set_key(input, INPUT_MOUSE_LEFT,
                          events[i].type == IOS_DEMO_TOUCH_DOWN);
    }
    return true;
}

@interface IOSDemoView : UIView {
    IOSDemoHost *_host;
    __unsafe_unretained UITouch *_activeTouch;
}
- (instancetype)initWithFrame:(CGRect)frame host:(IOSDemoHost *)host;
@end

@implementation IOSDemoView
+ (Class)layerClass { return [CAMetalLayer class]; }

- (instancetype)initWithFrame:(CGRect)frame host:(IOSDemoHost *)host
{
    self = [super initWithFrame:frame];
    if (self != nil) {
        _host = host;
        CAMetalLayer *layer = (CAMetalLayer *)[self layer];
        [layer setPixelFormat:MTLPixelFormatBGRA8Unorm];
        [layer setOpaque:YES];
        [layer setPresentsWithTransaction:NO];
        [self setMultipleTouchEnabled:NO];
        [self setAutoresizingMask:UIViewAutoresizingFlexibleWidth |
                                  UIViewAutoresizingFlexibleHeight];
    }
    return self;
}

- (void)layoutSubviews
{
    [super layoutSubviews];
    (void)ios_host_update_view(self, _host);
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    (void)event;
    if (_activeTouch != nil) return;
    _activeTouch = [touches anyObject];
    ios_host_push_event(_host, IOS_DEMO_TOUCH_DOWN, _activeTouch, self);
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    (void)event;
    if (_activeTouch != nil && [touches containsObject:_activeTouch])
        ios_host_push_event(_host, IOS_DEMO_TOUCH_MOVE, _activeTouch, self);
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    (void)event;
    if (_activeTouch != nil && [touches containsObject:_activeTouch]) {
        ios_host_push_event(_host, IOS_DEMO_TOUCH_UP, _activeTouch, self);
        _activeTouch = nil;
    }
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [self touchesEnded:touches withEvent:event];
}
@end

static void ios_thread_args_destroy(IOSDemoThreadArgs *args)
{
    if (args == NULL) return;
    for (int i = 0; i < args->argc; ++i) free(args->argv[i]);
    free(args->argv);
    free(args);
}

static IOSDemoThreadArgs *ios_thread_args_create(IOSDemoHost *host)
{
    NSArray<NSString *> *arguments = [[NSProcessInfo processInfo] arguments];
    if ([arguments count] > (NSUInteger)INT_MAX) return NULL;
    IOSDemoThreadArgs *args = calloc(1u, sizeof(*args));
    if (args == NULL) return NULL;
    args->host = host;
    args->argc = (int)[arguments count];
    args->argv = calloc((size_t)args->argc + 1u, sizeof(*args->argv));
    if (args->argv == NULL) {
        ios_thread_args_destroy(args);
        return NULL;
    }
    for (int i = 0; i < args->argc; ++i) {
        const char *value = [[arguments objectAtIndex:(NSUInteger)i] UTF8String];
        if (value == NULL || (args->argv[i] = strdup(value)) == NULL) {
            ios_thread_args_destroy(args);
            return NULL;
        }
    }
    return args;
}

static void *ios_demo_thread(void *opaque)
{
    IOSDemoThreadArgs *args = opaque;
    int result;
    @autoreleasepool {
        result = engine_demo_main(args->argc, args->argv, &args->host->config);
    }
    ios_thread_args_destroy(args);
    dispatch_async(dispatch_get_main_queue(), ^{
        exit(result);
    });
    return NULL;
}

@class IOSDemoSceneDelegate;
static __unsafe_unretained IOSDemoSceneDelegate *ios_current_scene_delegate;

@interface IOSDemoSceneDelegate : NSObject <UISceneDelegate, UIWindowSceneDelegate> {
    IOSDemoHost *_host;
    pthread_t _thread;
    BOOL _started;
}
@property(nonatomic, retain) UIWindow *window;
- (void)shutdownEngine;
- (void)disposeHost;
@end

@implementation IOSDemoSceneDelegate
@synthesize window = _window;

- (void)shutdownEngine
{
    ios_host_request_stop(_host);
    if (_started) {
        int result = pthread_join(_thread, NULL);
        if (result != 0)
            NSLog(@"iOS demo: render thread join failed: %s", strerror(result));
        _started = NO;
    }
}

- (void)disposeHost
{
    [self shutdownEngine];
    [_window release];
    _window = nil;
    if (_host != NULL) {
        if (_host->sync_ready) {
            pthread_cond_destroy(&_host->condition);
            pthread_mutex_destroy(&_host->mutex);
        }
        free(_host);
        _host = NULL;
    }
}

- (void)scene:(UIScene *)scene willConnectToSession:(UISceneSession *)session
      options:(UISceneConnectionOptions *)connectionOptions
{
    (void)session;
    (void)connectionOptions;
    if (![scene isKindOfClass:[UIWindowScene class]]) {
        NSLog(@"iOS demo: expected a UIWindowScene");
        exit(1);
    }
    if (ios_current_scene_delegate != nil && ios_current_scene_delegate != self) {
        NSLog(@"iOS demo: multiple scenes are not supported");
        exit(1);
    }
    if (_host != NULL) [self disposeHost];
    if (!ios_prepare_working_directory()) exit(1);
    ios_current_scene_delegate = self;

    _host = calloc(1u, sizeof(*_host));
    if (_host == NULL || !ios_host_init(_host)) {
        NSLog(@"iOS demo: cannot initialize host synchronization");
        exit(1);
    }
    _host->suspended = [scene activationState] != UISceneActivationStateForegroundActive;
    _host->config.title = "Pure C Engine - iOS";
    _host->config.target_fps = 60.0;
    _host->config.start_fullscreen = true;
    _host->engine_host.poll = ios_host_poll;
    _host->config.host = &_host->engine_host;

    UIWindowScene *window_scene = (UIWindowScene *)scene;
    UIWindow *window = [[UIWindow alloc] initWithWindowScene:window_scene];
    UIViewController *controller = [[UIViewController alloc] init];
    IOSDemoView *view = [[IOSDemoView alloc] initWithFrame:[window bounds] host:_host];
    [controller setView:view];
    [window setRootViewController:controller];
    [self setWindow:window];
    [[self window] makeKeyAndVisible];
    [view layoutIfNeeded];
    if (!ios_host_update_view(view, _host)) {
        NSLog(@"iOS demo: native view has an invalid drawable size");
        exit(1);
    }
    CAMetalLayer *layer = (CAMetalLayer *)[view layer];
    _host->config.native_window = (__bridge void *)layer;
    _host->config.native_display = (__bridge void *)view;
    _host->config.width = _host->drawable_width;
    _host->config.height = _host->drawable_height;
    _host->config.native_content_scale = _host->content_scale;
    [window release];
    [controller release];
    [view release];

    IOSDemoThreadArgs *args = ios_thread_args_create(_host);
    if (args == NULL) {
        NSLog(@"iOS demo: cannot copy process arguments");
        exit(1);
    }
    pthread_attr_t attributes;
    int result = pthread_attr_init(&attributes);
    if (result == 0) {
        result = pthread_attr_setstacksize(&attributes, IOS_DEMO_STACK_SIZE);
        if (result == 0) result = pthread_create(&_thread, &attributes, ios_demo_thread, args);
        pthread_attr_destroy(&attributes);
    }
    if (result != 0) {
        NSLog(@"iOS demo: cannot create render thread: %s", strerror(result));
        ios_thread_args_destroy(args);
        exit(1);
    }
    _started = YES;
}

- (void)sceneDidDisconnect:(UIScene *)scene
{
    (void)scene;
    if (ios_current_scene_delegate == self) ios_current_scene_delegate = nil;
    [self disposeHost];
}

- (void)sceneWillResignActive:(UIScene *)scene
{
    (void)scene;
    ios_host_set_suspended(_host, true);
}

- (void)sceneDidBecomeActive:(UIScene *)scene
{
    (void)scene;
    ios_host_set_suspended(_host, false);
}

- (void)sceneDidEnterBackground:(UIScene *)scene
{
    (void)scene;
    ios_host_set_suspended(_host, true);
}

- (void)dealloc
{
    [self disposeHost];
    if (ios_current_scene_delegate == self) ios_current_scene_delegate = nil;
    [super dealloc];
}
@end

@interface IOSDemoAppDelegate : NSObject <UIApplicationDelegate>
@end

@implementation IOSDemoAppDelegate
- (UISceneConfiguration *)application:(UIApplication *)application
    configurationForConnectingSceneSession:(UISceneSession *)connectingSceneSession
                                   options:(UISceneConnectionOptions *)options
{
    (void)application;
    (void)options;
    UISceneConfiguration *configuration = [[UISceneConfiguration alloc]
        initWithName:@"Default Configuration" sessionRole:[connectingSceneSession role]];
    [configuration setSceneClass:[UIWindowScene class]];
    [configuration setDelegateClass:[IOSDemoSceneDelegate class]];
    return [configuration autorelease];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    (void)application;
    [ios_current_scene_delegate shutdownEngine];
}
@end

int main(int argc, char **argv)
{
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil,
                                 NSStringFromClass([IOSDemoAppDelegate class]));
    }
}
