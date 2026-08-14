#ifndef MOTION_HISTORY_H
#define MOTION_HISTORY_H

#include <core/types.h>
#include <math/math.h>

/* Dense, slot-indexed history avoids hash lookups in the render hot path. */
typedef struct {
    Mat4 previous;
    Mat4 current;
    u32 generation;
    bool valid;
    bool previous_seen;
    bool touched;
} MotionHistorySlot;

typedef struct {
    MotionHistorySlot *slots;
    u32 capacity;
} MotionHistory;

bool motion_history_init(MotionHistory *history, u32 capacity);
void motion_history_destroy(MotionHistory *history);
void motion_history_begin_frame(MotionHistory *history);
bool motion_history_set_current(MotionHistory *history, u32 slot, u32 generation,
                                const Mat4 *current);
bool motion_history_get_pair(const MotionHistory *history, u32 slot, u32 generation,
                             Mat4 *previous, Mat4 *current);
void motion_history_commit(MotionHistory *history);

#endif
