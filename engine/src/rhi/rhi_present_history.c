#include "rhi/rhi_present_history.h"

#include <string.h>

static bool history_rects_valid(const RHIPresentHistory *history,
                                const RHIPresentRect *rects, u32 count) {
    u32 i;
    if (history == NULL || count > RHI_MAX_PRESENT_DAMAGE_RECTS ||
        (count != 0u && rects == NULL)) {
        return false;
    }
    for (i = 0u; i < count; ++i) {
        const RHIPresentRect *rect = &rects[i];
        if (rect->x < 0 || rect->y < 0 || rect->w == 0u || rect->h == 0u ||
            (u64)rect->x + (u64)rect->w > history->width ||
            (u64)rect->y + (u64)rect->h > history->height) {
            return false;
        }
    }
    return true;
}

static void history_full_rect(const RHIPresentHistory *history,
                              RHIPresentRect *out) {
    *out = (RHIPresentRect){0, 0, history->width, history->height};
}

static bool history_output_full(const RHIPresentHistory *history,
                                RHIPresentRect *out, u32 out_capacity,
                                u32 *out_count, bool *out_full) {
    if (out == NULL || out_count == NULL || out_full == NULL ||
        out_capacity == 0u) {
        return false;
    }
    history_full_rect(history, &out[0]);
    *out_count = 1u;
    *out_full = true;
    return true;
}

static bool history_append_output(RHIPresentRect *out, u32 out_capacity,
                                  u32 *out_count,
                                  const RHIPresentRect *rects, u32 count) {
    if (count > out_capacity - *out_count) return false;
    if (count != 0u) {
        memcpy(&out[*out_count], rects, count * sizeof(*rects));
        *out_count += count;
    }
    return true;
}

bool rhi_present_history_init(RHIPresentHistory *history, u32 image_count,
                              u32 width, u32 height) {
    if (history == NULL || image_count == 0u ||
        image_count > RHI_PRESENT_HISTORY_MAX_IMAGES || width == 0u ||
        height == 0u) {
        return false;
    }
    memset(history, 0, sizeof(*history));
    history->image_count = image_count;
    history->width = width;
    history->height = height;
    return true;
}

bool rhi_present_history_reset(RHIPresentHistory *history) {
    u32 image_count;
    u32 width;
    u32 height;
    if (history == NULL || history->image_count == 0u ||
        history->image_count > RHI_PRESENT_HISTORY_MAX_IMAGES ||
        history->width == 0u || history->height == 0u) {
        return false;
    }
    image_count = history->image_count;
    width = history->width;
    height = history->height;
    memset(history, 0, sizeof(*history));
    history->image_count = image_count;
    history->width = width;
    history->height = height;
    return true;
}

void rhi_present_history_abort(RHIPresentHistory *history) {
    (void)rhi_present_history_reset(history);
}

bool rhi_present_history_prepare(const RHIPresentHistory *history,
                                 u32 image_index,
                                 const RHIPresentRect *current, u32 count,
                                 RHIPresentRect *out, u32 out_capacity,
                                 u32 *out_count, bool *out_full) {
    u64 last_generation;
    u64 expected_generation;
    u32 i;
    if (history == NULL || out_count == NULL || out_full == NULL ||
        image_index >= history->image_count ||
        !history_rects_valid(history, current, count)) {
        return false;
    }
    *out_count = 0u;
    *out_full = false;
    last_generation = history->image_generation[image_index];
    if (last_generation == 0u || last_generation > history->generation) {
        return history_output_full(history, out, out_capacity, out_count,
                                    out_full);
    }
    if (last_generation == history->generation) {
        if (!history_append_output(out, out_capacity, out_count, current,
                                   count)) {
            return history_output_full(history, out, out_capacity, out_count,
                                        out_full);
        }
        return true;
    }
    if (history->entry_count == 0u ||
        last_generation + 1u < history->entries[0].generation) {
        return history_output_full(history, out, out_capacity, out_count,
                                   out_full);
    }
    expected_generation = last_generation + 1u;
    for (i = 0u; i < history->entry_count; ++i) {
        const RHIPresentHistoryEntry *entry = &history->entries[i];
        if (entry->generation < expected_generation) continue;
        if (entry->generation != expected_generation) {
            return history_output_full(history, out, out_capacity, out_count,
                                       out_full);
        }
        if (!history_append_output(out, out_capacity, out_count, entry->rects,
                                   entry->count)) {
            return history_output_full(history, out, out_capacity, out_count,
                                        out_full);
        }
        expected_generation++;
    }
    if (expected_generation != history->generation + 1u) {
        return history_output_full(history, out, out_capacity, out_count,
                                   out_full);
    }
    if (!history_append_output(out, out_capacity, out_count, current, count)) {
        return history_output_full(history, out, out_capacity, out_count,
                                   out_full);
    }
    return true;
}

bool rhi_present_history_commit(RHIPresentHistory *history, u32 image_index,
                               const RHIPresentRect *current, u32 count) {
    RHIPresentHistoryEntry *entry;
    if (history == NULL || image_index >= history->image_count ||
        !history_rects_valid(history, current, count)) {
        return false;
    }
    if (history->generation == UINT64_MAX) {
        if (!rhi_present_history_reset(history)) return false;
    }
    if (history->entry_count == RHI_PRESENT_HISTORY_CAPACITY) {
        if (!rhi_present_history_reset(history)) return false;
    }
    entry = &history->entries[history->entry_count++];
    entry->generation = ++history->generation;
    entry->count = count;
    if (count != 0u) {
        memcpy(entry->rects, current, count * sizeof(*current));
    }
    history->image_generation[image_index] = entry->generation;
    return true;
}

u64 rhi_present_history_generation(const RHIPresentHistory *history) {
    return history == NULL ? 0u : history->generation;
}

u64 rhi_present_history_image_generation(const RHIPresentHistory *history,
                                         u32 image_index) {
    if (history == NULL || image_index >= history->image_count) return 0u;
    return history->image_generation[image_index];
}

static bool damage_history_rects_valid(const RHIPresentDamageHistory *history,
                                       const RHIPresentRect *rects,
                                       u32 count) {
    u32 i;
    if (history == NULL || count > RHI_MAX_PRESENT_DAMAGE_RECTS ||
        (count != 0u && rects == NULL)) {
        return false;
    }
    for (i = 0u; i < count; ++i) {
        const RHIPresentRect *rect = &rects[i];
        if (rect->x < 0 || rect->y < 0 || rect->w == 0u || rect->h == 0u ||
            (u64)rect->x + (u64)rect->w > history->width ||
            (u64)rect->y + (u64)rect->h > history->height) {
            return false;
        }
    }
    return true;
}

static bool damage_history_output_full(const RHIPresentDamageHistory *history,
                                        RHIPresentRect *out, u32 out_capacity,
                                        u32 *out_count, bool *out_full) {
    if (history == NULL || out == NULL || out_capacity == 0u ||
        out_count == NULL || out_full == NULL) {
        return false;
    }
    out[0] = (RHIPresentRect){0, 0, history->width, history->height};
    *out_count = 1u;
    *out_full = true;
    return true;
}

bool rhi_present_damage_history_init(RHIPresentDamageHistory *history,
                                     u32 width, u32 height) {
    if (history == NULL || width == 0u || height == 0u) return false;
    memset(history, 0, sizeof(*history));
    history->width = width;
    history->height = height;
    return true;
}

bool rhi_present_damage_history_reset(RHIPresentDamageHistory *history) {
    u32 width;
    u32 height;
    if (history == NULL || history->width == 0u || history->height == 0u) {
        return false;
    }
    width = history->width;
    height = history->height;
    memset(history, 0, sizeof(*history));
    history->width = width;
    history->height = height;
    return true;
}

bool rhi_present_damage_history_prepare_age(
    const RHIPresentDamageHistory *history, u32 buffer_age,
    const RHIPresentRect *current, u32 count, RHIPresentRect *out,
    u32 out_capacity, u32 *out_count, bool *out_full) {
    u32 first;
    u32 i;
    if (history == NULL || out_count == NULL || out_full == NULL ||
        !damage_history_rects_valid(history, current, count)) {
        return false;
    }
    *out_count = 0u;
    *out_full = false;
    if (buffer_age == 0u || buffer_age > history->entry_count ||
        buffer_age > RHI_PRESENT_DAMAGE_HISTORY_CAPACITY) {
        return damage_history_output_full(history, out, out_capacity,
                                           out_count, out_full);
    }
    first = history->entry_count - (buffer_age - 1u);
    for (i = first; i < history->entry_count; ++i) {
        const RHIPresentHistoryEntry *entry = &history->entries[i];
        if (entry->count > out_capacity - *out_count) {
            return damage_history_output_full(history, out, out_capacity,
                                               out_count, out_full);
        }
        if (entry->count != 0u) {
            memcpy(&out[*out_count], entry->rects,
                   entry->count * sizeof(entry->rects[0]));
            *out_count += entry->count;
        }
    }
    if (count > out_capacity - *out_count) {
        return damage_history_output_full(history, out, out_capacity,
                                           out_count, out_full);
    }
    if (count != 0u) {
        memcpy(&out[*out_count], current, count * sizeof(current[0]));
        *out_count += count;
    }
    return true;
}

bool rhi_present_damage_history_commit(RHIPresentDamageHistory *history,
                                       const RHIPresentRect *current,
                                       u32 count) {
    if (!damage_history_rects_valid(history, current, count)) return false;
    if (history->entry_count == RHI_PRESENT_DAMAGE_HISTORY_CAPACITY) {
        memmove(&history->entries[0], &history->entries[1],
                (RHI_PRESENT_DAMAGE_HISTORY_CAPACITY - 1u) *
                    sizeof(history->entries[0]));
        history->entry_count--;
    }
    history->entries[history->entry_count].count = count;
    if (count != 0u) {
        memcpy(history->entries[history->entry_count].rects, current,
               count * sizeof(current[0]));
    }
    history->entry_count++;
    return true;
}
