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
    return (u64)((counter.QuadPart * 1000000000ULL) / freq.QuadPart);
}

void time_init(void) {
    /* Pre-cache the frequency on Windows */
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
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
    if (microseconds >= 1000) {
        Sleep((DWORD)(microseconds / 1000));
    } else if (microseconds > 0) {
        Sleep(0);  /* yield */
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
