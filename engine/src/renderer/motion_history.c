#include <renderer/motion_history.h>
#include <stdlib.h>
#include <string.h>

bool motion_history_init(MotionHistory *history, u32 capacity) {
    if (!history || capacity == 0u) return false;
    memset(history, 0, sizeof(*history));
    history->slots = calloc(capacity, sizeof(*history->slots));
    if (!history->slots) return false;
    history->capacity = capacity;
    return true;
}

void motion_history_destroy(MotionHistory *history) {
    if (!history) return;
    free(history->slots);
    memset(history, 0, sizeof(*history));
}

void motion_history_begin_frame(MotionHistory *history) {
    if (!history || !history->slots) return;
    for (u32 i = 0; i < history->capacity; i++) history->slots[i].touched = false;
}

bool motion_history_set_current(MotionHistory *history, u32 slot, u32 generation,
                                const Mat4 *current) {
    if (!history || !history->slots || !current || slot >= history->capacity || generation == 0u)
        return false;
    MotionHistorySlot *entry = &history->slots[slot];
    if (entry->generation != generation || !entry->previous_seen) {
        entry->generation = generation;
        entry->valid = false;
        entry->previous = *current;
    } else {
        entry->valid = true;
    }
    entry->current = *current;
    entry->touched = true;
    return true;
}

bool motion_history_get_pair(const MotionHistory *history, u32 slot, u32 generation,
                             Mat4 *previous, Mat4 *current) {
    if (!history || !history->slots || slot >= history->capacity || generation == 0u)
        return false;
    const MotionHistorySlot *entry = &history->slots[slot];
    if (!entry->valid || entry->generation != generation || !entry->touched)
        return false;
    if (previous) *previous = entry->previous;
    if (current) *current = entry->current;
    return true;
}

void motion_history_commit(MotionHistory *history) {
    if (!history || !history->slots) return;
    for (u32 i = 0; i < history->capacity; i++) {
        MotionHistorySlot *entry = &history->slots[i];
        if (entry->touched) {
            entry->previous = entry->current;
            entry->valid = entry->previous_seen;
        } else {
            /* A missing render object must not reuse stale history when it
             * reappears at the same slot/generation. */
            entry->valid = false;
        }
        entry->previous_seen = entry->touched;
    }
}
