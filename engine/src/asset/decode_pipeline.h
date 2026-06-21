#pragma once
#include <core/types.h>

/* ---- Asynchronous texture decode pipeline ----
 *
 * Offloads stb_image decode + mipmap chain generation from the I/O workers
 * to a dedicated 2-thread worker pool. Raw file bytes are submitted by the
 * async loader after a disk read; decoded results are polled by the main
 * thread via async_loader_tick().
 */

/* Result of a completed decode job. Ownership of `data` is transferred to
 * the caller of decode_pipeline_poll(). */
typedef struct {
    void *data;      /* decoded data (AsyncTextureHeader + mip chain) or NULL on failure */
    u32   size;
    u64   slot;      /* async loader request slot associated with this job */
    u64   request_id;/* async loader request id (protects against slot reuse) */
    bool  success;
} DecodeResult;

/* Initialize the decode pipeline with 2 worker threads. */
bool decode_pipeline_init(void);

/* Shut down the pipeline, joining workers and freeing queued jobs. */
void decode_pipeline_shutdown(void);

/* Submit raw encoded image bytes for decoding. Ownership of raw_data is
 * transferred; the caller must not access it after this call. */
bool decode_pipeline_submit(void *raw_data, u32 raw_size, u64 slot, u64 request_id, i32 priority);

/* Poll one completed decode job. Returns true if `out_result` was filled.
 * The caller must free out_result->data when non-NULL. */
bool decode_pipeline_poll(DecodeResult *out_result);

/* Number of jobs waiting in the decode input queue (does not include jobs
 * currently being decoded). */
u32 decode_pipeline_queue_count(void);
