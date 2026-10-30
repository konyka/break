#define _POSIX_C_SOURCE 199309L

/* Lua backend micro-benchmark (docs/design/luajit_evaluation.md, Workstream D).
 *
 * Standalone and NOT part of the CMake graph: it is built by hand against one
 * backend at a time so the evaluation never adds LuaJIT to the repository.
 *
 *   Lua 5.4 (vendored):
 *     gcc -std=c11 -O2 -w -DMAKE_LIB -I engine/external -c \
 *         engine/external/lua/onelua.c -o lua54.o
 *     gcc -std=c11 -O2 -I engine/external engine/tests/bench_lua_backends.c \
 *         lua54.o -lm -o bench_lua54
 *   LuaJIT (scratch checkout, never committed):
 *     gcc -std=c11 -O2 -DBREAK_BENCH_LUAJIT -I /tmp/luajit-eval/src \
 *         engine/tests/bench_lua_backends.c /tmp/luajit-eval/src/libluajit.a \
 *         -lm -ldl -o bench_luajit
 *
 * A CMake hook would be an EXCLUDE_FROM_ALL executable that links `lua` (5.4)
 * and, when -DBREAK_LUAJIT_EVAL_DIR=<dir> is given, a second executable
 * compiled with BREAK_BENCH_LUAJIT that links <dir>/src/libluajit.a.
 *
 * Usage: bench [--runs N] [--jit on|off] [--hook] [--only fib|table|string]
 *   --jit only affects LuaJIT; "off" runs jit.off() before each benchmark
 *   (interpreter mode). --hook arms lua_sethook(LUA_MASKCOUNT, INT_MAX) with
 *   a callback that errors if it ever fires, which is how break_lua arms its
 *   instruction budget; the benchmark fails if the budget is exhausted.
 *   Every run uses a fresh lua_State created through
 *   lua_newstate with a byte-counting allocator, so JIT warm-up and
 *   compilation are part of the measured time, and the allocator-accounted
 *   peak is reported per run. */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(BREAK_BENCH_LUAJIT)
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#define BENCH_BACKEND "luajit"
#define BENCH_MODE(jit_on) ((jit_on) ? "jit" : "interp")
#else
#include <lua/lua.h>
#include <lua/lauxlib.h>
#include <lua/lualib.h>
#define BENCH_BACKEND "lua54"
#define BENCH_MODE(jit_on) ((void)(jit_on), "interp")
#endif

typedef struct {
    size_t live;
    size_t peak;
} BenchAlloc;

/* When ptr is NULL, Lua 5.4 passes a type tag in osize, not a size. */
static void *bench_alloc(void *ud, void *ptr, size_t osize, size_t nsize)
{
    BenchAlloc *a = (BenchAlloc *)ud;
    size_t old_size = ptr != NULL ? osize : 0u;
    void *out;
    if (nsize == 0u) {
        free(ptr);
        a->live -= old_size;
        return NULL;
    }
    out = realloc(ptr, nsize);
    if (out == NULL) {
        return NULL;
    }
    a->live = a->live - old_size + nsize;
    if (a->live > a->peak) {
        a->peak = a->live;
    }
    return out;
}

static void bench_hook(lua_State *L, lua_Debug *ar)
{
    (void)ar;
    luaL_error(L, "bench: instruction hook fired");
}

typedef struct {
    const char *name;
    const char *label;
    const char *source;
} BenchCase;

static const BenchCase kCases[] = {
    {"fib", "fib(32)",
     "local function fib(n) if n < 2 then return n end"
     " return fib(n - 1) + fib(n - 2) end\n"
     "return fib(32)\n"},
    {"table", "table insert/sum 1e6",
     "local t = {}\n"
     "for i = 1, 1000000 do table.insert(t, i) end\n"
     "local s = 0\n"
     "for i = 1, #t do s = s + t[i] end\n"
     "return s\n"},
    {"string", "string concat/format 2e5",
     "local parts = {}\n"
     "for i = 1, 200000 do\n"
     "  local k = 'k' .. i\n"
     "  parts[i] = string.format('%s=%d', k, i)\n"
     "end\n"
     "return #table.concat(parts, ',')\n"},
};

static double now_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec * 1000.0 + (double)ts.tv_nsec / 1.0e6;
}

static int cmp_double(const void *a, const void *b)
{
    double x = *(const double *)a;
    double y = *(const double *)b;
    return (x > y) - (x < y);
}

static long vm_hwm_kb(void)
{
    char line[256];
    long kb = -1;
    FILE *f = fopen("/proc/self/status", "r");
    if (!f) {
        return -1;
    }
    while (fgets(line, sizeof line, f)) {
        if (strncmp(line, "VmHWM:", 6) == 0) {
            kb = strtol(line + 6, NULL, 10);
            break;
        }
    }
    fclose(f);
    return kb;
}

#define MAX_RUNS 64

static int run_case(const BenchCase *c, int runs, int jit_on, int hook_on)
{
    double ms[MAX_RUNS];
    size_t peaks[MAX_RUNS];
    double check = 0.0;
    int i;
    for (i = 0; i < runs; i++) {
        BenchAlloc alloc = {0u, 0u};
        lua_State *L = lua_newstate(bench_alloc, &alloc);
        double t0;
        int rc;
        if (!L) {
            fprintf(stderr, "lua_newstate failed\n");
            return 1;
        }
        luaL_openlibs(L);
#if defined(BREAK_BENCH_LUAJIT)
        if (!jit_on) {
            if (luaL_dostring(L, "jit.off()") != 0) {
                fprintf(stderr, "jit.off failed: %s\n", lua_tostring(L, -1));
                return 1;
            }
        }
#else
        (void)jit_on;
#endif
        if (hook_on) {
            lua_sethook(L, bench_hook, LUA_MASKCOUNT, INT_MAX);
        }
        t0 = now_ms();
        rc = luaL_loadstring(L, c->source) || lua_pcall(L, 0, 1, 0);
        ms[i] = now_ms() - t0;
        if (rc != 0) {
            fprintf(stderr, "%s failed: %s\n", c->name, lua_tostring(L, -1));
            return 1;
        }
        check = lua_tonumber(L, -1);
        lua_close(L);
        peaks[i] = alloc.peak;
        printf("RUN %s %s hook=%s %s run=%d ms=%.2f peak_bytes=%zu\n",
               BENCH_BACKEND, BENCH_MODE(jit_on), hook_on ? "on" : "off",
               c->name, i + 1, ms[i], peaks[i]);
    }
    {
        double sorted[MAX_RUNS];
        double median;
        size_t peak_max = 0u;
        memcpy(sorted, ms, sizeof(double) * (size_t)runs);
        qsort(sorted, (size_t)runs, sizeof(double), cmp_double);
        median = (runs % 2) ? sorted[runs / 2]
                            : (sorted[runs / 2 - 1] + sorted[runs / 2]) / 2.0;
        for (i = 0; i < runs; i++) {
            if (peaks[i] > peak_max) {
                peak_max = peaks[i];
            }
        }
        printf("SUMMARY %s %s hook=%s \"%s\" runs=%d median_ms=%.2f "
               "min_ms=%.2f max_ms=%.2f spread_pct=%.1f alloc_peak_bytes=%zu "
               "check=%.0f vm_hwm_kb=%ld\n",
               BENCH_BACKEND, BENCH_MODE(jit_on), hook_on ? "on" : "off",
               c->label, runs, median,
               sorted[0], sorted[runs - 1],
               median > 0.0 ? 100.0 * (sorted[runs - 1] - sorted[0]) / median
                            : 0.0,
               peak_max, check, vm_hwm_kb());
    }
    return 0;
}

int main(int argc, char **argv)
{
    int runs = 5;
    int jit_on = 1;
    int hook_on = 0;
    const char *only = NULL;
    size_t i;
    int a;
    for (a = 1; a < argc; a++) {
        if (strcmp(argv[a], "--runs") == 0 && a + 1 < argc) {
            runs = atoi(argv[++a]);
        } else if (strcmp(argv[a], "--jit") == 0 && a + 1 < argc) {
            jit_on = strcmp(argv[++a], "off") != 0;
        } else if (strcmp(argv[a], "--hook") == 0) {
            hook_on = 1;
        } else if (strcmp(argv[a], "--only") == 0 && a + 1 < argc) {
            only = argv[++a];
        } else {
            fprintf(stderr,
                    "usage: %s [--runs N] [--jit on|off] [--hook] [--only "
                    "fib|table|string]\n",
                    argv[0]);
            return 2;
        }
    }
    if (runs < 1 || runs > MAX_RUNS) {
        fprintf(stderr, "--runs must be 1..%d\n", MAX_RUNS);
        return 2;
    }
    for (i = 0; i < sizeof kCases / sizeof kCases[0]; i++) {
        if (only && strcmp(only, kCases[i].name) != 0) {
            continue;
        }
        if (run_case(&kCases[i], runs, jit_on, hook_on) != 0) {
            return 1;
        }
    }
    return 0;
}
