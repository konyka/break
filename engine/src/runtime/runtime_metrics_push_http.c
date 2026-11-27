#define _POSIX_C_SOURCE 200809L
#include <runtime/runtime_metrics_push_http.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Builds <base_url><path> into `url`; false on an empty, unterminated or
 * '/'-terminated base URL or a result that does not fit. */
static bool push_http_url(const BreakRuntimeMetricsPushHttp *ctx, const char *path, char *url,
                          usize cap) {
    usize base_len = strnlen(ctx->base_url, sizeof(ctx->base_url));
    int n;
    if (base_len == 0u || base_len >= sizeof(ctx->base_url) ||
        ctx->base_url[base_len - 1u] == '/')
        return false;
    n = snprintf(url, cap, "%s%s", ctx->base_url, path);
    return n > 0 && (usize)n < cap;
}

static BreakRuntimeError push_http_post(const BreakRuntimeMetricsPushHttp *ctx, const char *url,
                                        const char *body, usize len, const char *content_type) {
    u8 resp[256];
    usize resp_len = 0u;
    int status = 0;
    BreakHttpError http = break_http_post(&ctx->cfg, url, body, len, content_type, resp,
                                          sizeof(resp), &resp_len, &status);
    /* The answer body carries nothing the push needs: a 200 whose body does
     * not fit the buffer (TOO_BIG is decided after the status line) is still
     * a delivery. */
    if (status == 200 && (http == BHTTP_OK || http == BHTTP_ERR_TOO_BIG)) return BREAK_RUNTIME_OK;
    return BREAK_RUNTIME_FAILED;
}

BreakRuntimeError break_runtime_metrics_push_http(const BreakRuntimeMetricsPushHttp *ctx,
                                                  BreakRuntimeMetrics *metrics) {
    char url[BREAK_HTTP_MAX_URL];
    usize needed = 0u;
    usize len = 0u;
    char *body;
    BreakRuntimeError err;
    if (!ctx || !metrics) return BREAK_RUNTIME_INVALID;
    if (!push_http_url(ctx, "/metrics", url, sizeof(url))) return BREAK_RUNTIME_INVALID;
    /* Sizing pass: an empty registry encodes OK into zero bytes. */
    err = break_runtime_metrics_encode(metrics, NULL, 0u, &needed);
    if (err != BREAK_RUNTIME_OK && err != BREAK_RUNTIME_OVERLOAD) return err;
    if (needed > BREAK_RUNTIME_METRICS_PUSH_HTTP_MAX_BYTES) return BREAK_RUNTIME_OVERLOAD;
    body = (char *)malloc(needed + 1u);
    if (!body) return BREAK_RUNTIME_OOM;
    /* A producer on another thread may add a metric between the two passes;
     * the second encode then reports OVERLOAD, which is returned as is. */
    err = break_runtime_metrics_encode(metrics, body, needed + 1u, &len);
    if (err == BREAK_RUNTIME_OK)
        err = push_http_post(ctx, url, body, len, BREAK_RUNTIME_METRICS_PUSH_HTTP_CONTENT_TYPE);
    free(body);
    return err;
}

BreakRuntimeError break_runtime_metrics_push_alerts_http(const BreakRuntimeMetricsPushHttp *ctx,
                                                         const BreakRuntimeMetricAlertRule *rules,
                                                         const BreakRuntimeMetricAlertEdge *edges,
                                                         u32 count) {
    char url[BREAK_HTTP_MAX_URL];
    usize needed = 0u;
    usize len = 0u;
    char *body;
    BreakRuntimeError err;
    if (!ctx) return BREAK_RUNTIME_INVALID;
    if (!push_http_url(ctx, "/alerts", url, sizeof(url))) return BREAK_RUNTIME_INVALID;
    err = break_runtime_metrics_encode_alert_edges(rules, edges, count, NULL, 0u, &needed);
    if (err != BREAK_RUNTIME_OK && err != BREAK_RUNTIME_OVERLOAD) return err;
    if (needed == 0u) return BREAK_RUNTIME_OK; /* no transition: nothing to deliver */
    if (needed > BREAK_RUNTIME_METRICS_PUSH_HTTP_MAX_BYTES) return BREAK_RUNTIME_OVERLOAD;
    body = (char *)malloc(needed + 1u);
    if (!body) return BREAK_RUNTIME_OOM;
    err = break_runtime_metrics_encode_alert_edges(rules, edges, count, body, needed + 1u, &len);
    if (err == BREAK_RUNTIME_OK)
        err = push_http_post(ctx, url, body, len,
                             BREAK_RUNTIME_METRICS_PUSH_HTTP_ALERTS_CONTENT_TYPE);
    free(body);
    return err;
}
