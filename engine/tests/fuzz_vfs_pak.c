/* Mutation fuzzer for the PAK archive mount path.
 *
 * Builds a valid multi-entry PAK, then repeatedly applies random byte mutations
 * and feeds the result through vfs_mount_pak + vfs_open + vfs_read under
 * ASan+UBSan. The loader is allowed to reject anything; it is not allowed to
 * crash, read or write out of bounds, or leak. */

#include <asset/vfs.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long rng_state = 0x9E3779B9u;
static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

static u32 fnv1a_name(const char *s) {
    u32 h = 2166136261u;
    while (*s) { h ^= (u8)*s++; h *= 16777619u; }
    return h;
}

#define SEED_FILES 4
static const char *seed_names[SEED_FILES] = {
    "greet.txt", "a/b/deep.bin", "shader.glsl", "x"
};
static const char *seed_data[SEED_FILES] = {
    "PAK DATA!", "\x01\x02\x03\x04binary", "void main(){}", "q"
};

/* Serialize a valid PAK into a heap buffer. */
static unsigned char *build_seed_pak(long *out_len) {
    u32 name_sizes[SEED_FILES], data_sizes[SEED_FILES];
    u32 name_table_size = 0, data_total = 0;
    for (int i = 0; i < SEED_FILES; i++) {
        name_sizes[i] = (u32)strlen(seed_names[i]) + 1u;
        data_sizes[i] = (u32)strlen(seed_data[i]);
        name_table_size += name_sizes[i];
        data_total += data_sizes[i];
    }

    u32 table_off = (u32)(sizeof(PakHeader) + SEED_FILES * sizeof(PakEntry));
    u32 data_off = table_off + name_table_size;
    long total = (long)data_off + (long)data_total;

    unsigned char *buf = (unsigned char *)calloc(1, (size_t)total);
    if (!buf) return NULL;

    PakHeader hdr = { .magic = VFS_PAK_MAGIC,
                      .version = VFS_PAK_VERSION,
                      .entry_count = SEED_FILES,
                      .name_table_size = name_table_size };
    memcpy(buf, &hdr, sizeof(hdr));

    u32 name_cursor = 0, data_cursor = 0;
    for (int i = 0; i < SEED_FILES; i++) {
        PakEntry e = { .name_hash = fnv1a_name(seed_names[i]),
                       .name_offset = name_cursor,
                       .data_offset = data_off + data_cursor,
                       .size = data_sizes[i] };
        memcpy(buf + sizeof(PakHeader) + (size_t)i * sizeof(PakEntry), &e, sizeof(e));
        memcpy(buf + table_off + name_cursor, seed_names[i], name_sizes[i]);
        memcpy(buf + data_off + data_cursor, seed_data[i], data_sizes[i]);
        name_cursor += name_sizes[i];
        data_cursor += data_sizes[i];
    }

    *out_len = total;
    return buf;
}

static int write_file(const char *p, const unsigned char *b, long n) {
    FILE *f = fopen(p, "wb");
    if (!f) return 0;
    int ok = fwrite(b, 1, (size_t)n, f) == (size_t)n;
    fclose(f);
    return ok;
}

/* Boundary values for the u32 count/offset/size fields. Byte-level flips alone
 * essentially never produce these, yet they are exactly where wraparound and
 * overflow bugs live. */
static const u32 interesting_u32[] = {
    0u, 1u, 2u,
    0x7FFFFFFFu, 0x80000000u,
    0xFFFFFFFDu, 0xFFFFFFFEu, 0xFFFFFFFFu,
    0x40000000u, 0x40000001u, /* straddles the entry_count > 1<<30 bound */
    0x00010000u, 0x0000FFFFu,
};

/* Random mutations biased toward the header + entry table, where the counts and
 * offsets that drive allocations live. Mixes byte-level flips with word-level
 * writes of boundary values. */
static void mutate(unsigned char *buf, long n, unsigned nmut) {
    long hot = (long)(sizeof(PakHeader) + SEED_FILES * sizeof(PakEntry));
    if (hot > n) hot = n;
    unsigned nwords = (unsigned)(hot / 4);
    for (unsigned m = 0; m < nmut; m++) {
        /* Half the time, overwrite a whole u32 field with a boundary value. */
        if (nwords > 0 && rnd() % 2 == 0) {
            u32 v = interesting_u32[rnd() % (sizeof(interesting_u32) / sizeof(interesting_u32[0]))];
            memcpy(buf + (size_t)(rnd() % nwords) * 4u, &v, sizeof(v));
            continue;
        }
        long pos = (rnd() % 4 != 0) ? (long)(rnd() % (unsigned)hot)
                                    : (long)(rnd() % (unsigned)n);
        switch (rnd() % 4) {
        case 0: buf[pos] = (unsigned char)(rnd() & 0xFF); break;
        case 1: buf[pos] ^= (unsigned char)(1u << (rnd() % 8)); break;
        case 2: buf[pos] = 0xFF; break;
        default: buf[pos] = 0x00; break;
        }
    }
}

int main(int argc, char **argv) {
    unsigned iters = argc > 1 ? (unsigned)atoi(argv[1]) : 20000;
    if (argc > 2) rng_state = (unsigned long)atoi(argv[2]);
    log_set_level(LOG_FATAL);

    const char *mut_pak = "/tmp/fuzz_mut.pak";

    long plen = 0;
    unsigned char *base = build_seed_pak(&plen);
    if (!base) { fprintf(stderr, "seed pak failed\n"); return 2; }

    /* The unmutated seed must mount and read back correctly, otherwise the
     * fuzzer is only exercising the reject paths. */
    if (!write_file(mut_pak, base, plen)) { fprintf(stderr, "write seed failed\n"); return 2; }
    {
        VFS *vfs = vfs_create();
        if (!vfs_mount_pak(vfs, mut_pak)) { fprintf(stderr, "seed pak rejected\n"); return 2; }
        for (int i = 0; i < SEED_FILES; i++) {
            VFSFile *f = vfs_open(vfs, seed_names[i]);
            if (!f) { fprintf(stderr, "seed open '%s' failed\n", seed_names[i]); return 2; }
            vfs_close(f);
        }
        vfs_destroy(vfs);
    }

    unsigned char *scratch = (unsigned char *)malloc((size_t)plen);
    if (!scratch) return 2;
    unsigned mounted = 0, opened = 0;

    for (unsigned it = 0; it < iters; it++) {
        memcpy(scratch, base, (size_t)plen);
        mutate(scratch, plen, 1 + rnd() % 6);
        if (!write_file(mut_pak, scratch, plen)) continue;

        VFS *vfs = vfs_create();
        if (vfs_mount_pak(vfs, mut_pak)) {
            mounted++;
            for (int i = 0; i < SEED_FILES; i++) {
                VFSFile *f = vfs_open(vfs, seed_names[i]);
                if (f) {
                    opened++;
                    /* Drain through the read API so size/pos bookkeeping on a
                     * mutated entry size is exercised too. */
                    unsigned char sink[64];
                    while (vfs_read(f, sink, sizeof(sink)) > 0) { }
                    vfs_close(f);
                }
            }
            /* Names from a mutated table must not be trusted either. */
            VFSFile *miss = vfs_open(vfs, "definitely/not/present.dat");
            if (miss) vfs_close(miss);
        }
        vfs_destroy(vfs);
    }

    printf("fuzz done: %u iters, mounted %u, opened %u\n", iters, mounted, opened);
    free(base); free(scratch);
    remove(mut_pak);
    return 0;
}
