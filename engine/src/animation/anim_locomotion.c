#include <animation/animation.h>
#include <math.h>
#include <string.h>

bool anim_loco1d_init(AnimLoco1D *loco, u32 layer,
                      const AnimLocoSample *samples, u32 count) {
    if (!loco || !samples || count < 2u || count > ANIM_LOCO_SAMPLES) {
        return false;
    }
    if (layer + 1u >= ANIM_MAX_LAYERS) {
        return false;
    }
    for (u32 i = 0; i < count; i++) {
        if (!isfinite(samples[i].speed)) {
            return false;
        }
        if (i > 0 && !(samples[i].speed > samples[i - 1u].speed)) {
            return false;
        }
    }
    memset(loco, 0, sizeof(*loco));
    memcpy(loco->samples, samples, sizeof(AnimLocoSample) * count);
    loco->count = count;
    loco->layer = layer;
    return true;
}

void anim_loco1d_apply(const AnimLoco1D *loco, AnimBlendState *state, f32 speed) {
    if (!loco || !state || loco->count < 2u || !isfinite(speed)) {
        return;
    }
    if (loco->layer + 1u >= ANIM_MAX_LAYERS) {
        return;
    }
    u32 i0 = 0;
    u32 i1 = 1;
    f32 w1 = 0.0f;
    if (speed <= loco->samples[0].speed) {
        w1 = 0.0f;
    } else if (speed >= loco->samples[loco->count - 1u].speed) {
        i0 = loco->count - 2u;
        i1 = loco->count - 1u;
        w1 = 1.0f;
    } else {
        while (i1 + 1u < loco->count && speed > loco->samples[i1].speed) {
            i0++;
            i1++;
        }
        f32 s0 = loco->samples[i0].speed;
        f32 s1 = loco->samples[i1].speed;
        w1 = (speed - s0) / (s1 - s0);
    }
    f32 w0 = 1.0f - w1;
    u32 high = w1 > w0 ? i1 : i0;
    u32 low = high == i0 ? i1 : i0;
    f32 high_w = high == i0 ? w0 : w1;
    f32 low_w = high == i0 ? w1 : w0;
    if (w0 == w1) {
        high = i0;
        low = i1;
        high_w = w0;
        low_w = w1;
    }
    AnimationLayer *primary = &state->layers[loco->layer];
    AnimationLayer *secondary = &state->layers[loco->layer + 1u];
    primary->clip_index = loco->samples[high].clip_index;
    primary->weight = high_w;
    primary->active = high_w > 0.0f;
    secondary->clip_index = loco->samples[low].clip_index;
    secondary->weight = low_w;
    secondary->active = low_w > 0.0f;
}
