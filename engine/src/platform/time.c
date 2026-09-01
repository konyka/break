#include <platform/time.h>

#ifdef ENGINE_PLATFORM_WINDOWS
#include <windows.h>

static u64 time_base_ns(void) {
    static LARGE_INTEGER freq = {0};
    LARGE_INTEGER counter;
    if (freq.QuadPart == 0) {
        QueryPerformanceFrequency(&freq);
    }
    QueryPerformanceCounter(&counter);
    /* R423: divide before multiplying — (counter * 1e9) overflows u64 after
     * ~15 min uptime at a 10 MHz QPC (counter * 1e9 needs 74 bits). Splitting
     * into whole seconds + remainder keeps every intermediate in range. */
    u64 c = (u64)counter.QuadPart;
    u64 f = (u64)freq.QuadPart;
    return (c / f) * 1000000000ULL + ((c % f) * 1000000000ULL) / f;
}

void time_init(void) {
    /* R571: the old "pre-cache" queried into a local and discarded it -
     * a no-op. Prime time_base_ns so its function-local static frequency
     * is populated through the same (idempotent, same-value) path first-
     * use would take. */
    (void)time_base_ns();
}

f64 time_seconds(void) {
    return (f64)time_base_ns() / 1e9;
}

u64 time_microseconds(void) {
    return time_base_ns() / 1000;
}

f64 time_delta_since(u64 last_us) {
    u64 now = time_microseconds();
    return (f64)(now - last_us) / 1e6;
}

void time_sleep_us(u64 microseconds) {
    if (microseconds == 0) return;

    u64 deadline = time_base_ns() + microseconds * 1000ULL;
    if (microseconds >= 1000) {
        Sleep((DWORD)(microseconds / 1000));
    }
    while (time_base_ns() < deadline) {
        /* Sleep(0) only yields and does not provide a sub-millisecond delay. */
        SwitchToThread();
    }
}

#else /* Linux / POSIX */
#include <time.h>

static u64 time_base_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (u64)ts.tv_sec * 1000000000ULL + (u64)ts.tv_nsec;
}

void time_init(void) {
}

f64 time_seconds(void) {
    return (f64)time_base_ns() / 1e9;
}

u64 time_microseconds(void) {
    return time_base_ns() / 1000;
}

f64 time_delta_since(u64 last_us) {
    u64 now = time_microseconds();
    return (f64)(now - last_us) / 1e6;
}

void time_sleep_us(u64 microseconds) {
    struct timespec ts = {
        .tv_sec  = (time_t)(microseconds / 1000000),
        .tv_nsec = (long)((microseconds % 1000000) * 1000),
    };
    nanosleep(&ts, NULL);
}

#endif
