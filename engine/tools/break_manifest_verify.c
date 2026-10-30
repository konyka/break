/* break_manifest_verify — checks a signed update manifest with the CLIENT
 * verifier (break_update_manifest_parse + break_update_manifest_verify),
 * so release tooling can prove its output is what clients accept.
 *
 *   break_manifest_verify <manifest file> <64 hex public key>
 *
 * Exit 0 = parses and the Ed25519 signature verifies; 1 = rejected;
 * 2 = usage error. Prints version/channel/platform/chunk count on success. */
#include <update/break_update.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MV_MAX (1024u * 1024u)

static int mv_hex(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

int main(int argc, char **argv) {
    u8 pub[32];
    u32 version[3];
    char *text;
    size_t n, i;
    FILE *f;
    BreakUpdateManifest *m;
    int rc = 1;
    if (argc != 3 || strlen(argv[2]) != 64u) {
        fprintf(stderr, "usage: break_manifest_verify <manifest> <64 hex public key>\n");
        return 2;
    }
    for (i = 0u; i < 32u; i++) {
        int hi = mv_hex(argv[2][2u * i]), lo = mv_hex(argv[2][2u * i + 1u]);
        if (hi < 0 || lo < 0) {
            fprintf(stderr, "break_manifest_verify: public key is not hex\n");
            return 2;
        }
        pub[i] = (u8)((hi << 4) | lo);
    }
    f = fopen(argv[1], "rb");
    if (f == NULL) {
        fprintf(stderr, "break_manifest_verify: cannot open '%s'\n", argv[1]);
        return 1;
    }
    text = (char *)malloc(MV_MAX + 1u);
    if (text == NULL) {
        fclose(f);
        return 1;
    }
    n = fread(text, 1u, MV_MAX + 1u, f);
    fclose(f);
    if (n > MV_MAX) {
        fprintf(stderr, "break_manifest_verify: manifest exceeds 1 MiB\n");
        free(text);
        return 1;
    }
    m = break_update_manifest_parse(text, n);
    free(text);
    if (m == NULL) {
        fprintf(stderr, "break_manifest_verify: not a canonical break-manifest-v1\n");
        return 1;
    }
    if (break_update_manifest_verify(m, pub)) {
        break_update_manifest_version(m, version);
        printf("break_manifest_verify: OK %u.%u.%u channel=%s platform=%s chunks=%llu\n",
               version[0], version[1], version[2], break_update_manifest_channel(m),
               break_update_manifest_platform(m),
               (unsigned long long)break_update_manifest_chunk_count(m));
        rc = 0;
    } else {
        fprintf(stderr, "break_manifest_verify: signature does not verify\n");
    }
    break_update_manifest_destroy(m);
    return rc;
}
