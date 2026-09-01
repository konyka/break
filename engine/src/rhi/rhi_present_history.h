#pragma once

#include <rhi/rhi.h>

#define RHI_PRESENT_HISTORY_MAX_IMAGES 16u
#define RHI_PRESENT_HISTORY_CAPACITY 64u
#define RHI_PRESENT_DAMAGE_HISTORY_CAPACITY 16u

typedef struct {
    u64 generation;
    u32 count;
    RHIPresentRect rects[RHI_MAX_PRESENT_DAMAGE_RECTS];
} RHIPresentHistoryEntry;

typedef struct {
    u32 width;
    u32 height;
    u32 image_count;
    u64 generation;
    u64 image_generation[RHI_PRESENT_HISTORY_MAX_IMAGES];
    u32 entry_count;
    RHIPresentHistoryEntry entries[RHI_PRESENT_HISTORY_CAPACITY];
} RHIPresentHistory;

/* Fixed-size history for APIs such as EGL_EXT_buffer_age. Entries are ordered
 * from oldest to newest and contain only the damage drawn in that frame. */
typedef struct {
    u32 width;
    u32 height;
    u32 entry_count;
    RHIPresentHistoryEntry entries[RHI_PRESENT_DAMAGE_HISTORY_CAPACITY];
} RHIPresentDamageHistory;

bool rhi_present_history_init(RHIPresentHistory *history, u32 image_count,
                              u32 width, u32 height);
bool rhi_present_history_reset(RHIPresentHistory *history);
void rhi_present_history_abort(RHIPresentHistory *history);
bool rhi_present_history_prepare(const RHIPresentHistory *history,
                                 u32 image_index,
                                 const RHIPresentRect *current, u32 count,
                                 RHIPresentRect *out, u32 out_capacity,
                                 u32 *out_count, bool *out_full);
bool rhi_present_history_commit(RHIPresentHistory *history, u32 image_index,
                               const RHIPresentRect *current, u32 count);
u64 rhi_present_history_generation(const RHIPresentHistory *history);
u64 rhi_present_history_image_generation(const RHIPresentHistory *history,
                                         u32 image_index);

bool rhi_present_damage_history_init(RHIPresentDamageHistory *history,
                                     u32 width, u32 height);
bool rhi_present_damage_history_reset(RHIPresentDamageHistory *history);
bool rhi_present_damage_history_prepare_age(
    const RHIPresentDamageHistory *history, u32 buffer_age,
    const RHIPresentRect *current, u32 count, RHIPresentRect *out,
    u32 out_capacity, u32 *out_count, bool *out_full);
bool rhi_present_damage_history_commit(RHIPresentDamageHistory *history,
                                       const RHIPresentRect *current,
                                       u32 count);
