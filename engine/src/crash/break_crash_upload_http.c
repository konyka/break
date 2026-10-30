#define _POSIX_C_SOURCE 200809L
#include <crash/break_crash_upload_http.h>

#include <stdio.h>
#include <string.h>

bool break_crash_upload_http(void *user, const void *record_bytes, usize len) {
    const BreakCrashUploadHttp *ctx = (const BreakCrashUploadHttp *)user;
    char url[BREAK_HTTP_MAX_URL];
    u8 resp[256];
    usize resp_len = 0u;
    int status = 0;
    usize base_len;
    int n;
    if (ctx == NULL || record_bytes == NULL || len == 0u || len > BREAK_CRASH_UPLOAD_HTTP_MAX_BYTES) return false;
    base_len = strnlen(ctx->base_url, sizeof(ctx->base_url));
    if (base_len == 0u || base_len >= sizeof(ctx->base_url) || ctx->base_url[base_len - 1u] == '/') return false;
    n = snprintf(url, sizeof(url), "%s/crash", ctx->base_url);
    if (n <= 0 || (usize)n >= sizeof(url)) return false;
    if (break_http_post(&ctx->cfg, url, record_bytes, len, BREAK_CRASH_UPLOAD_HTTP_CONTENT_TYPE, resp,
                        sizeof(resp), &resp_len, &status) != BHTTP_OK) {
        return false;
    }
    return status == 200;
}
