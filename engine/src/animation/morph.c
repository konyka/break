#include <animation/morph.h>
#include <string.h>

bool anim_morph_init(AnimMorphSet *set, u32 vertex_count) {
    if (!set || vertex_count == 0u || vertex_count > ANIM_MORPH_MAX_VERTICES) return false;
    memset(set, 0, sizeof(*set));
    set->vertex_count = vertex_count;
    return true;
}

bool anim_morph_add_target(AnimMorphSet *set, const char *name,
                           const Vec3 *position_deltas) {
    if (!set || !name || !position_deltas || set->target_count >= ANIM_MORPH_MAX_TARGETS)
        return false;
    usize length = 0u;
    while (length < ANIM_MORPH_NAME_CAP && name[length] != '\0') ++length;
    if (length == 0u || length == ANIM_MORPH_NAME_CAP) return false;
    for (u32 i = 0; i < set->target_count; ++i)
        if (strcmp(set->targets[i].name, name) == 0) return false;
    for (u32 v = 0; v < set->vertex_count; ++v)
        for (u32 a = 0; a < 3u; ++a)
            if (!isfinite(position_deltas[v].e[a])) return false;
    AnimMorphTarget *target = &set->targets[set->target_count];
    memcpy(target->name, name, length + 1u);
    target->position_deltas = position_deltas;
    ++set->target_count;
    return true;
}

bool anim_morph_evaluate(const AnimMorphSet *set, const f32 *base_xyz,
                         const f32 *weights, u32 weight_count, f32 *out_xyz) {
    if (!set || !base_xyz || !out_xyz || weight_count != set->target_count ||
        (weight_count > 0u && !weights)) return false;
    for (u32 t = 0; t < weight_count; ++t)
        if (!isfinite(weights[t]) || weights[t] < 0.0f || weights[t] > 1.0f)
            return false;
    for (u32 pass = 0; pass < 2u; ++pass) {
        for (u32 v = 0; v < set->vertex_count; ++v) {
            for (u32 a = 0; a < 3u; ++a) {
                f32 value = base_xyz[(usize)v * 3u + a];
                for (u32 t = 0; t < set->target_count; ++t)
                    value += set->targets[t].position_deltas[v].e[a] * weights[t];
                if (!isfinite(value)) return false;
                if (pass == 1u) out_xyz[(usize)v * 3u + a] = value;
            }
        }
    }
    return true;
}

bool anim_morph_evaluate_skinned(const AnimMorphSet *set, const void *base_vertices,
                                 const f32 *weights, u32 weight_count,
                                 void *out_vertices, usize out_bytes) {
    if (!set || !base_vertices || !out_vertices) return false;
    if (out_bytes / ANIM_MORPH_SKIN_VERTEX_BYTES < set->vertex_count) return false;
    AnimMorphSet view = *set;
    view.vertex_count = 1u;
    for (u32 pass = 0; pass < 2u; ++pass) {
        for (u32 v = 0; v < set->vertex_count; ++v) {
            for (u32 t = 0; t < set->target_count; ++t)
                view.targets[t].position_deltas = set->targets[t].position_deltas + v;
            const u8 *source = (const u8 *)base_vertices +
                               (usize)v * ANIM_MORPH_SKIN_VERTEX_BYTES;
            f32 base_xyz[3];
            f32 morphed_xyz[3];
            memcpy(base_xyz, source, sizeof(base_xyz));
            if (!anim_morph_evaluate(&view, base_xyz, weights, weight_count, morphed_xyz))
                return false;
            if (pass == 1u) {
                u8 *destination = (u8 *)out_vertices +
                                  (usize)v * ANIM_MORPH_SKIN_VERTEX_BYTES;
                if (destination != source) memcpy(destination, source, ANIM_MORPH_SKIN_VERTEX_BYTES);
                memcpy(destination, morphed_xyz, sizeof(morphed_xyz));
            }
        }
    }
    return true;
}
