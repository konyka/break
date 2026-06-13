#include <core/profiler.h>
#include <platform/time.h>
#include <stdio.h>
#include <string.h>

Profiler g_profiler = {0};

void profiler_set_enabled(bool enabled) {
    g_profiler.enabled = enabled;
}

void profiler_begin_frame(void) {
    if (!g_profiler.enabled) return;
    ProfilerFrame *f = &g_profiler.frames[g_profiler.frame_index];
    f->region_count = 0;
    f->frame_start_us = time_microseconds();
}

void profiler_end_frame(void) {
    if (!g_profiler.enabled) return;
    ProfilerFrame *f = &g_profiler.frames[g_profiler.frame_index];
    f->frame_end_us = time_microseconds();
    g_profiler.frame_index = (g_profiler.frame_index + 1) % PROFILER_MAX_FRAMES;
    if (g_profiler.frame_count < PROFILER_MAX_FRAMES) g_profiler.frame_count++;
}

void profiler_push(const char *name) {
    if (!g_profiler.enabled) return;
    ProfilerFrame *f = &g_profiler.frames[g_profiler.frame_index];
    if (f->region_count >= PROFILER_MAX_REGIONS) return;
    ProfilerRegion *r = &f->regions[f->region_count++];
    r->name = name;
    r->start_us = time_microseconds();
    r->elapsed_us = 0;
}

void profiler_pop(void) {
    if (!g_profiler.enabled) return;
    ProfilerFrame *f = &g_profiler.frames[g_profiler.frame_index];
    if (f->region_count == 0) return;
    ProfilerRegion *r = &f->regions[f->region_count - 1];
    r->elapsed_us = time_microseconds() - r->start_us;
}

const ProfilerFrame *profiler_last_frame(void) {
    if (g_profiler.frame_count == 0) return NULL;
    u32 idx = (g_profiler.frame_index + PROFILER_MAX_FRAMES - 1) % PROFILER_MAX_FRAMES;
    return &g_profiler.frames[idx];
}

static void profiler_json_escape_name(const char *name, char *out, usize out_sz) {
    if (!out || out_sz == 0) return;
    if (!name) name = "?";
    usize j = 0;
    for (usize i = 0; name[i] != '\0' && j + 2 < out_sz; i++) {
        char c = name[i];
        if (c == '"' || c == '\\') {
            if (j + 2 >= out_sz) break;
            out[j++] = '\\';
        }
        out[j++] = c;
    }
    out[j] = '\0';
}

bool profiler_export_chrome_trace(const char *path,
                                  const ProfilerFrame *frame,
                                  const ProfilerGpuRegion *gpu_regions,
                                  u32 gpu_count,
                                  const ProfilerMetaInstant *meta,
                                  u32 meta_count) {
    if (!path || !frame) return false;
    FILE *f = fopen(path, "w");
    if (!f) return false;

    fprintf(f, "{\"traceEvents\":[\n");
    bool first = true;
    u64 t0 = frame->frame_start_us;

    for (u32 i = 0; i < frame->region_count; i++) {
        const ProfilerRegion *r = &frame->regions[i];
        char ename[128];
        profiler_json_escape_name(r->name, ename, sizeof(ename));
        u64 ts = (r->start_us >= t0) ? (r->start_us - t0) : 0u;
        if (!first) fprintf(f, ",\n");
        first = false;
        fprintf(f,
            "{\"name\":\"%s\",\"cat\":\"cpu\",\"ph\":\"X\",\"ts\":%llu,\"dur\":%llu,"
            "\"pid\":1,\"tid\":1,\"args\":{\"thread\":\"main\"}}",
            ename,
            (unsigned long long)ts,
            (unsigned long long)r->elapsed_us);
    }

    if (gpu_regions) {
        for (u32 i = 0; i < gpu_count; i++) {
            char ename[128];
            profiler_json_escape_name(gpu_regions[i].name, ename, sizeof(ename));
            u64 dur_us = (u64)(gpu_regions[i].elapsed_ms * 1000.0);
            if (!first) fprintf(f, ",\n");
            first = false;
            fprintf(f,
                "{\"name\":\"%s\",\"cat\":\"gpu\",\"ph\":\"X\",\"ts\":0,\"dur\":%llu,"
                "\"pid\":1,\"tid\":2,\"args\":{\"thread\":\"gpu\"}}",
                ename, (unsigned long long)dur_us);
        }
    }

    /* Frame boundary marker for chrome://tracing navigation. */
    if (!first) fprintf(f, ",\n");
    u64 frame_dur = (frame->frame_end_us >= frame->frame_start_us)
        ? (frame->frame_end_us - frame->frame_start_us) : 0u;
    fprintf(f,
        "{\"name\":\"frame\",\"cat\":\"meta\",\"ph\":\"X\",\"ts\":0,\"dur\":%llu,"
        "\"pid\":1,\"tid\":1}",
        (unsigned long long)frame_dur);

    if (meta) {
        for (u32 i = 0; i < meta_count; i++) {
            if (!meta[i].key || !meta[i].value) continue;
            char ekey[128], eval[128];
            profiler_json_escape_name(meta[i].key, ekey, sizeof(ekey));
            profiler_json_escape_name(meta[i].value, eval, sizeof(eval));
            fprintf(f, ",\n");
            fprintf(f,
                "{\"name\":\"%s\",\"cat\":\"meta\",\"ph\":\"i\",\"ts\":0,"
                "\"pid\":1,\"tid\":1,\"args\":{\"value\":\"%s\"}}",
                ekey, eval);
        }
    }

    fprintf(f, "\n]}\n");
    fclose(f);
    return true;
}
