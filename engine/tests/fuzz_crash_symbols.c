/* Mutation fuzzer for break_crash_symbols_open, the untrusted binary parser the
 * crash symbol store runs on server-side symbol files (64-bit LE ELF or Mach-O,
 * thin or universal). Usage:
 *   fuzz_crash_symbols [iterations] [seed] [seed_binary_path]
 * With CRASH_SYMBOLS_LIBFUZZER=1 the same check is exported to libFuzzer.
 * Invariants, enforced on every input:
 *  - open never reads out of bounds (ASan/UBSan); it returns NULL for a file
 *    that is not a supported format or is structurally inconsistent, or a
 *    usable handle otherwise, and never crashes on hostile bytes;
 *  - on a handle, count/build_id/is_exec and lookups across a wide address
 *    range never read or write out of bounds and respect the caller's out_cap
 *    (a deliberately short buffer must always be NUL-terminated within it). */

#include <crash/break_crash_symbolize.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#include <process.h>
#define FUZZ_GETPID _getpid
#else
#include <unistd.h>
#define FUZZ_GETPID getpid
#endif

static unsigned long long rng_state = 0x9E3779B97F4A7C15ULL;

static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

/* Large enough to hold a whole test binary: ELF keeps its section header
 * table at the END of the file, so a truncated seed would only ever exercise
 * the reject path. The parser itself caps input at 256 MiB. */
enum { k_seed_cap = 8u * 1024u * 1024u };

static unsigned char *read_seed(const char *path, size_t *out_size) {
    FILE *f = fopen(path, "rb");
    unsigned char *buf;
    size_t n;
    if (!f) return NULL;
    buf = (unsigned char *)malloc(k_seed_cap);
    if (!buf) {
        fclose(f);
        return NULL;
    }
    n = fread(buf, 1u, k_seed_cap, f);
    fclose(f);
    *out_size = n;
    return buf;
}

/* Structural fields live in the first few KiB (ELF/Mach-O headers, load
 * commands, fat entry table) and, for ELF, the last few KiB (section header
 * table); uniform offsets would mostly hit machine code. Bias half the picks
 * toward those two regions. */
static size_t pick_offset(size_t size) {
    const size_t edge = 4096u;
    unsigned r = rnd() % 4u;
    if (size <= 2u * edge || r >= 2u) return rnd() % size;
    if (r == 0u) return rnd() % edge;
    return size - 1u - (rnd() % edge);
}

static size_t mutate(unsigned char *buf, size_t size, size_t capacity) {
    unsigned ops = rnd() % 8u + 1u;
    for (unsigned i = 0u; i < ops; ++i) {
        unsigned choice = rnd() % 4u;
        if (choice == 0u && size != 0u) {
            buf[pick_offset(size)] = (unsigned char)(rnd() & 0xFFu); /* flip a byte */
        } else if (choice == 1u && size < capacity) {
            size_t at = rnd() % (size + 1u);
            memmove(buf + at + 1u, buf + at, size - at);
            buf[at] = (unsigned char)(rnd() & 0xFFu); /* insert */
            ++size;
        } else if (choice == 2u && size != 0u) {
            size_t at = rnd() % size;
            memmove(buf + at, buf + at + 1u, size - at - 1u);
            --size; /* delete */
        } else if (size != 0u) {
            /* overwrite a short run, biased toward the structural regions */
            size_t at = pick_offset(size);
            size_t span = 1u + rnd() % 8u;
            for (size_t j = 0u; j < span && at + j < size; ++j)
                buf[at + j] = (unsigned char)(rnd() & 0xFFu);
        }
    }
    return size;
}

static void fuzz_tmp_path(char *out, size_t cap) {
    const char *dir = getenv("TMPDIR");
    if (!dir || !*dir) dir = "/tmp";
    snprintf(out, cap, "%s/fuzz_crash_symbols_%ld.bin", dir, (long)FUZZ_GETPID());
}

/* Returns non-zero on an invariant violation. When out_opened is non-NULL it
 * receives 1 if the file parsed into a handle, 0 otherwise. */
static int check_payload_ex(const unsigned char *data, size_t size, int *out_opened) {
    char path[512];
    FILE *f;
    BreakElfSymbols *s;
    if (out_opened) *out_opened = 0;
    fuzz_tmp_path(path, sizeof(path));
    f = fopen(path, "wb");
    if (!f) return 0; /* cannot write scratch: not a parser fault */
    if (size != 0u && fwrite(data, 1u, size, f) != size) {
        fclose(f);
        remove(path);
        return 0;
    }
    fclose(f);

    s = break_crash_symbols_open(path);
    if (s) {
        if (out_opened) *out_opened = 1;
        u32 count = break_elf_symbols_count(s);
        const char *bid = break_elf_symbols_build_id(s);
        char name[8];
        char big[256];
        u64 off = 0u;
        /* build_id must always be a readable C string. */
        if (bid) (void)strlen(bid);
        (void)break_elf_symbols_is_exec(s);
        /* Probe a wide address range with both a tiny and a roomy buffer; the
         * short buffer must never be written past out_cap. */
        for (unsigned k = 0u; k < 64u; ++k) {
            u64 vaddr = ((u64)rnd() << 20) ^ ((u64)rnd() * 0x100u) ^ (u64)k;
            name[0] = '\0';
            if (break_elf_symbols_lookup(s, vaddr, name, sizeof(name), &off)) {
                if (name[sizeof(name) - 1u] != '\0') {
                    fprintf(stderr, "fuzz_crash_symbols: lookup overran short buffer\n");
                    break_elf_symbols_destroy(s);
                    remove(path);
                    return 1;
                }
            }
            (void)break_elf_symbols_lookup(s, vaddr, big, sizeof(big), &off);
        }
        (void)count;
        break_elf_symbols_destroy(s);
    }
    remove(path);
    return 0;
}

#ifdef CRASH_SYMBOLS_LIBFUZZER
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (check_payload_ex((const unsigned char *)data, size, NULL) != 0) abort();
    return 0;
}
#else
int main(int argc, char **argv) {
    long iterations = argc > 1 ? strtol(argv[1], NULL, 10) : 2000L;
    const char *seed_path = argc > 3 ? argv[3] : NULL;
    unsigned char *seed;
    size_t seed_size = 0u;
    unsigned char *buf;
    unsigned opened = 0u;
    unsigned rejected = 0u;
#if defined(__linux__)
    const char *fallback = "/proc/self/exe";
#else
    const char *fallback = argv[0];
#endif
    if (argc > 2) rng_state = (unsigned long long)strtoull(argv[2], NULL, 10) + 1u;
    if (iterations <= 0L) iterations = 2000L;
    if (!seed_path) seed_path = fallback;
    seed = read_seed(seed_path, &seed_size);
    if (!seed || seed_size == 0u) {
        fprintf(stderr, "fuzz_crash_symbols: cannot read seed %s\n", seed_path);
        free(seed);
        return 2;
    }
    buf = (unsigned char *)malloc(k_seed_cap);
    if (!buf) {
        free(seed);
        return 2;
    }
    for (long iteration = 0; iteration < iterations; ++iteration) {
        size_t size;
        int did_open = 0;
        memcpy(buf, seed, seed_size);
        size = mutate(buf, seed_size, k_seed_cap);
        if (check_payload_ex(buf, size, &did_open) != 0) {
            fprintf(stderr, "fuzz_crash_symbols: failed at iteration %ld, size %lu\n", iteration,
                    (unsigned long)size);
            free(buf);
            free(seed);
            return 1;
        }
        if (did_open) {
            ++opened;
        } else {
            ++rejected;
        }
    }
    free(buf);
    free(seed);
    printf("fuzz_crash_symbols: iterations=%ld opened=%u rejected=%u\n", iterations, opened,
           rejected);
    return 0;
}
#endif
