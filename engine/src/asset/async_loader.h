#pragma once
#include <core/types.h>

/* ---- Async Resource Loader ----
 * Provides non-blocking file I/O through a dedicated thread pool.
 * Requests are submitted from the main thread and completed callbacks
 * are dispatched via async_loader_tick() each frame.
 */

typedef enum {
    ASSET_UNLOADED = 0,
    ASSET_LOADING,
    ASSET_READY,
    ASSET_FAILED,
    ASSET_CANCELLED
} AssetState;

/* Callback invoked on the main thread when data is ready (or NULL on failure) */
typedef void (*AsyncLoadCallback)(void *user_data, void *data, u32 size);

/* Priority bands (lower value = processed sooner). */
#define ASYNC_PRIORITY_HIGH     0
#define ASYNC_PRIORITY_MIP(l) ((l) < 0 ? 0 : (l))
#define ASYNC_PRIORITY_DEFAULT  50
#define ASYNC_PRIORITY_LOW      100

/* When async_loader_request_texture completes successfully, `data` points at
 * an AsyncTextureHeader followed by RGBA8 pixels (size = header + w*h*4). */
typedef struct {
    u32 width;
    u32 height;
    u32 pixel_bytes; /* always 4 (RGBA) */
    u32 mip_count;   /* number of mipmap levels following the header */
} AsyncTextureHeader;

typedef struct VFS VFS;

/* Initialize the async loader with the given I/O thread count (recommend 2).
 * The VFS pointer is used for all file reads. */
void async_loader_init(u32 io_thread_count, VFS *vfs);

/* Shut down the loader, joining all I/O threads. */
void async_loader_shutdown(void);

/* Submit an async load request. Returns a unique request ID. */
u64 async_loader_request(const char *path, AsyncLoadCallback callback, void *user_data);

/* Main-thread tick: dispatches completed callbacks. Call once per frame. */
void async_loader_tick(void);

/* Query the state of a request by ID. */
AssetState async_loader_status(u64 request_id);

/* Cancel a pending (not yet started) request. Returns true if cancelled. */
bool async_loader_cancel(u64 request_id);

/* Get the number of pending (queued + in-flight) requests. */
u32 async_loader_pending_count(void);

/* ---- Chunked / Range Loading ---- */

/* Submit a range-based load request (for streaming mipmap levels, etc.).
 * offset: byte offset into the file
 * length: number of bytes to read (0 = read to end)
 * Returns a unique request ID. */
u64 async_loader_request_range(const char *path, usize offset, usize length,
                                AsyncLoadCallback callback, void *user_data);

/* Range load with explicit priority (see ASYNC_PRIORITY_*). */
u64 async_loader_request_range_priority(const char *path, usize offset, usize length,
                                         AsyncLoadCallback callback, void *user_data,
                                         i32 priority);

/* ---- Priority-based loading ---- */

/* Submit a prioritized load request. Lower priority value = higher priority.
 * Workers will process higher-priority requests first. */
u64 async_loader_request_priority(const char *path, AsyncLoadCallback callback,
                                   void *user_data, i32 priority);

/* Full-file load + stb decode on an I/O worker (RGBA8). Callback receives
 * AsyncTextureHeader + pixel bytes. */
u64 async_loader_request_texture(const char *path, AsyncLoadCallback callback,
                                  void *user_data, i32 priority);
