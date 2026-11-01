#include <game/break_game.h>
#include <math.h>

static f32 clampf(f32 v, f32 lo, f32 hi) {
    if (v < lo) {
        return lo;
    }
    if (v > hi) {
        return hi;
    }
    return v;
}

BreakGameError break_game_move_wish(const BreakGameMoveInput *in, BreakGameMoveOutput *out) {
    if (!in || !out) {
        return BREAK_GAME_INVALID;
    }
    if (!isfinite(in->forward) || !isfinite(in->strafe) || !isfinite(in->camera_yaw)) {
        return BREAK_GAME_INVALID;
    }
    f32 forward = clampf(in->forward, -1.0f, 1.0f);
    f32 strafe = clampf(in->strafe, -1.0f, 1.0f);
    f32 sy = sinf(in->camera_yaw);
    f32 cy = cosf(in->camera_yaw);
    Vec3 wish = vec3(forward * sy + strafe * cy, 0.0f, forward * cy - strafe * sy);
    f32 len_sq = wish.e[0] * wish.e[0] + wish.e[2] * wish.e[2];
    if (len_sq > 1.0f) {
        f32 inv = 1.0f / sqrtf(len_sq);
        wish.e[0] *= inv;
        wish.e[2] *= inv;
    }
    out->wish = wish;
    out->jump = in->jump;
    out->yaw = in->camera_yaw;
    return BREAK_GAME_OK;
}
