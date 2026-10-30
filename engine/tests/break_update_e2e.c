#define _POSIX_C_SOURCE 200809L
/* break_update_e2e — the CLIENT half of the update end-to-end test. It uses the
 * real update client (break_update) and the real HTTP transport (break_http);
 * the cmake script test_break_update_e2e.cmake drives the release tool and the
 * reference server around it.
 *
 *   break_update_e2e <state root> <base url> <ca pem|-> <64 hex pubkey> <step> [percent_bp|device]
 *
 * steps (exit 0 = success, 1 = a documented failure, 2 = usage):
 *   rollout          print the advertised rollout share
 *   stage            fetch + verify the manifest, stage_rollout, print the result
 *   stage-activate   stage, activate, confirm; print the installed slot and version
 *   status           print current slot / pending / version
 * Stdout carries `key=value` lines for the script to check. */
#include <net_http/break_http.h>
#include <update/break_update.h>
#include <update/break_update_client.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int hexv(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}

static const char *err_name(BreakUpdateClientError e) {
    switch (e) {
    case BREAK_UPDATE_CLIENT_OK: return "ok";
    case BREAK_UPDATE_CLIENT_INVALID: return "invalid";
    case BREAK_UPDATE_CLIENT_IO: return "io";
    case BREAK_UPDATE_CLIENT_PARSE: return "parse";
    case BREAK_UPDATE_CLIENT_POLICY: return "policy";
    case BREAK_UPDATE_CLIENT_FETCH: return "fetch";
    case BREAK_UPDATE_CLIENT_VERIFY: return "verify";
    case BREAK_UPDATE_CLIENT_STATE: return "state";
    case BREAK_UPDATE_CLIENT_ROLLOUT: return "rollout";
    }
    return "?";
}

int main(int argc, char **argv) {
    BreakHttpUpdateCtx ctx;
    BreakUpdateClient *c = NULL;
    BreakUpdateManifest *m = NULL;
    static u8 body[1024 * 1024 + 1];
    u8 pub[32];
    u64 got = 0;
    char url[600];
    u32 v[3];
    int rc = 1;
    const char *step;
    if (argc < 6 || strlen(argv[4]) != 64u) {
        fprintf(stderr, "usage: break_update_e2e <root> <base url> <ca|-> <pubkey hex> <step> [arg]\n");
        return 2;
    }
    step = argv[5];
    memset(&ctx, 0, sizeof(ctx));
    snprintf(ctx.base_url, sizeof(ctx.base_url), "%s", argv[2]);
    ctx.cfg.ca_file = strcmp(argv[3], "-") == 0 ? NULL : argv[3];
    ctx.cfg.io_timeout_ms = 8000;
    for (int i = 0; i < 32; i++) {
        int hi = hexv(argv[4][2 * i]), lo = hexv(argv[4][2 * i + 1]);
        if (hi < 0 || lo < 0) return 2;
        pub[i] = (u8)((hi << 4) | lo);
    }
    c = break_update_client_open(argv[1]);
    if (c == NULL) {
        fprintf(stderr, "cannot open the update root\n");
        return 1;
    }
    if (strcmp(step, "status") == 0) {
        break_update_client_current_version(c, v);
        printf("slot=%c pending=%d version=%u.%u.%u\n", break_update_client_current_slot(c),
               break_update_client_pending(c) ? 1 : 0, v[0], v[1], v[2]);
        rc = 0;
        goto out;
    }
    if (strcmp(step, "rollout") == 0) {
        u32 bp = 0;
        if (!break_http_rollout_percent_bp(&ctx.cfg, ctx.base_url, &bp)) {
            printf("rollout=error\n");
            goto out;
        }
        printf("rollout=%u\n", bp);
        rc = 0;
        goto out;
    }
    snprintf(url, sizeof(url), "%s/manifest", ctx.base_url);
    if (break_http_get(&ctx.cfg, url, body, sizeof(body) - 1u, &got) != BHTTP_OK) {
        printf("manifest=fetch-failed\n");
        goto out;
    }
    m = break_update_manifest_parse(body, (usize)got);
    if (m == NULL) {
        printf("manifest=not-canonical\n");
        goto out;
    }
    if (strcmp(step, "stage") == 0 || strcmp(step, "stage-activate") == 0) {
        const char *device = argc > 6 ? argv[6] : "device-1";
        u32 bp = argc > 7 ? (u32)atoi(argv[7]) : 10000u;
        bool ok = break_update_client_stage_rollout(c, m, pub, "stable", "linux-x86-64", device, bp,
                                                    break_http_update_fetch, &ctx);
        printf("stage=%s error=%s\n", ok ? "ok" : "failed", err_name(break_update_client_last_error(c)));
        if (!ok) goto out;
        if (strcmp(step, "stage-activate") == 0) {
            if (!break_update_client_activate(c) || !break_update_client_confirm_boot(c)) {
                printf("activate=failed\n");
                goto out;
            }
            break_update_client_current_version(c, v);
            printf("slot=%c version=%u.%u.%u\n", break_update_client_current_slot(c), v[0], v[1], v[2]);
        }
        rc = 0;
    }
out:
    if (m != NULL) break_update_manifest_destroy(m);
    break_update_client_destroy(c);
    return rc;
}
