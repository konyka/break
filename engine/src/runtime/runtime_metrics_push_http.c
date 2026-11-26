#define _POSIX_C_SOURCE 200809L
#include <runtime/runtime_metrics_push_http.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BreakRuntimeError break_runtime_metrics_push_http(const BreakRuntimeMetricsPushHttp *ctx,
                                                  BreakRuntimeMetrics *metrics) {
    char url[BREAK_HTTP_MAX_URL];
    u8 resp[256];
    usize resp_len = 0u;
    usize needed = 0u;
    usize len = 0u;
    usize base_len;
    int status = 0;
    int n;
    char *body;
    BreakRuntimeError err;
    BreakHttpError http;
    if (!ctx || !metrics) return BREAK_RUNTIME_INVALID;
    base_len = strnlen(ctx->base_url, sizeof(ctx->base_url));
    if (base_len == 0u || base_len >= sizeof(ctx->base_url) ||
        ctx->base_url[base_len - 1u] == '/')
        return BREAK_RUNTIME_INVALID;
    n = snprintf(url, sizeof(url), "%s/metrics", ctx->base_url);
    if (n <= 0 || (usize)n >= sizeof(url)) return BREAK_RUNTIME_INVALID;
    /* Sizing pass: an empty registry encodes OK into zero bytes. */
    err = break_runtime_metrics_encode(metrics, NULL, 0u, &needed);
    if (err != BREAK_RUNTIME_OK && err != BREAK_RUNTIME_OVERLOAD) return err;
    if (needed > BREAK_RUNTIME_METRICS_PUSH_HTTP_MAX_BYTES) return BREAK_RUNTIME_OVERLOAD;
    body = (char *)malloc(needed + 1u);
    if (!body) return BREAK_RUNTIME_OOM;
    /* Same thread as the sizing pass, so only this thread could have grown
     * the snapshot in between; a racing producer on another thread can, and
     * then the second encode reports OVERLOAD, which is returned as is. */
    err = break_runtime_metrics_encode(metrics, body, needed + 1u, &len);
    if (err != BREAK_RUNTIME_OK) {
        free(body);
        return err;
    }
    http = break_http_post(&ctx->cfg, url, body, len,
                           BREAK_RUNTIME_METRICS_PUSH_HTTP_CONTENT_TYPE, resp, sizeof(resp),
                           &resp_len, &status);
    free(body);
    return http == BHTTP_OK && status == 200 ? BREAK_RUNTIME_OK : BREAK_RUNTIME_FAILED;
}
