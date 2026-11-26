#pragma once
/* runtime_metrics_push_http — pushes the BRKM1 encoding of a metrics registry
 * to a collector over break_http (docs/design/runtime_metrics.md section 20).
 *
 * Kept out of the runtime_core archive on purpose: runtime_core has no
 * network dependency; the transport is opted into by linking this separate
 * library, exactly like break_crash_upload_http.
 *
 * One call = one POST: the current snapshot to <base_url>/metrics
 * (text/x-break-metrics), or alert transitions to <base_url>/alerts
 * (text/x-break-alerts). The transport rules of break_http apply
 * unchanged: https needs a CA file, plain http only to a loopback address, no
 * redirects. POSIX only, like break_http. */

#include <core/types.h>
#include <net_http/break_http.h>
#include <runtime/runtime_metrics.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_RUNTIME_METRICS_PUSH_HTTP_CONTENT_TYPE "text/x-break-metrics"
#define BREAK_RUNTIME_METRICS_PUSH_HTTP_ALERTS_CONTENT_TYPE "text/x-break-alerts"
#define BREAK_RUNTIME_METRICS_PUSH_HTTP_MAX_BYTES 65536u

typedef struct BreakRuntimeMetricsPushHttp {
    BreakHttpConfig cfg;
    char base_url[256]; /* e.g. "https://metrics.example.com" (no trailing '/') */
} BreakRuntimeMetricsPushHttp;

/* Encodes `metrics` and POSTs it. Must run on the registry's owner thread
 * (encode is owner-only) and blocks for at most the break_http budgets, so
 * call it from a diagnostics thread step, never a hot path.
 *   OK       — the collector answered HTTP 200.
 *   INVALID  — NULL ctx/metrics, empty, unterminated or '/'-terminated base
 *              URL, or a URL that does not fit; nothing is sent.
 *   REJECTED — called off the registry's owner thread; nothing is sent.
 *   OVERLOAD — the encoding exceeds BREAK_RUNTIME_METRICS_PUSH_HTTP_MAX_BYTES;
 *              nothing is sent.
 *   OOM      — the encode buffer could not be allocated; nothing is sent.
 *   FAILED   — any transport outcome other than a complete 200 answer
 *              (connect/TLS failure, timeout, refused URL, non-200 status,
 *              malformed answer). The caller may retry on its own schedule. */
BreakRuntimeError break_runtime_metrics_push_http(const BreakRuntimeMetricsPushHttp *ctx,
                                                  BreakRuntimeMetrics *metrics);

/* Delivers alert transitions: encodes `edges` with
 * break_runtime_metrics_encode_alert_edges and POSTs the result to
 * <base_url>/alerts with Content-Type text/x-break-alerts. When every edge is
 * STEADY nothing is sent and the call returns OK. Any thread (no registry is
 * touched); blocks like break_runtime_metrics_push_http.
 *   OK       — no transition, or the collector answered HTTP 200.
 *   INVALID  — NULL ctx, a bad base URL, or input the encoder rejects
 *              (bad rule name or op, unknown edge, NULL arrays); nothing is
 *              sent.
 *   OVERLOAD — the encoding exceeds BREAK_RUNTIME_METRICS_PUSH_HTTP_MAX_BYTES;
 *              nothing is sent.
 *   OOM      — the encode buffer could not be allocated; nothing is sent.
 *   FAILED   — any transport outcome other than a complete 200 answer. */
BreakRuntimeError break_runtime_metrics_push_alerts_http(const BreakRuntimeMetricsPushHttp *ctx,
                                                         const BreakRuntimeMetricAlertRule *rules,
                                                         const BreakRuntimeMetricAlertEdge *edges,
                                                         u32 count);

#ifdef __cplusplus
} /* extern "C" */
#endif
