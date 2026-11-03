#include <animation/facial.h>
#include <string.h>

static bool facial_name_copy(char *destination, const char *source) {
    if (!source) return false;
    memset(destination, 0, ANIM_FACIAL_NAME_CAP);
    usize length = 0u;
    while (length < ANIM_FACIAL_NAME_CAP && source[length] != '\0') ++length;
    if (length == 0u || length == ANIM_FACIAL_NAME_CAP) return false;
    memcpy(destination, source, length + 1u);
    return true;
}

void anim_facial_library_init(AnimFacialLibrary *library) {
    if (library) memset(library, 0, sizeof(*library));
}

bool anim_facial_add_expression(AnimFacialLibrary *library, const char *name) {
    if (!library || library->expression_count >= ANIM_FACIAL_MAX_EXPRESSIONS) return false;
    char copied_name[ANIM_FACIAL_NAME_CAP];
    if (!facial_name_copy(copied_name, name)) return false;
    for (u32 i = 0; i < library->expression_count; ++i)
        if (strcmp(library->expressions[i].name, copied_name) == 0) return false;
    AnimFacialExpression *expression = &library->expressions[library->expression_count];
    memcpy(expression->name, copied_name, sizeof(copied_name));
    ++library->expression_count;
    return true;
}

bool anim_facial_add_curve(AnimFacialLibrary *library,
                           const char *expression_name, const char *curve_name,
                           const char *morph_target_name, u32 keyframe_count,
                           const f32 *times, const f32 *values) {
    if (!library || !expression_name || !times || !values ||
        keyframe_count == 0u || keyframe_count > ANIM_FACIAL_MAX_KEYS) return false;
    char copied_curve[ANIM_FACIAL_NAME_CAP];
    char copied_target[ANIM_MORPH_NAME_CAP];
    if (!facial_name_copy(copied_curve, curve_name) ||
        !facial_name_copy(copied_target, morph_target_name)) return false;
    AnimFacialExpression *expression = NULL;
    for (u32 i = 0; i < library->expression_count; ++i)
        if (strcmp(library->expressions[i].name, expression_name) == 0)
            expression = &library->expressions[i];
    if (!expression || expression->curve_count >= ANIM_FACIAL_MAX_CURVES) return false;
    for (u32 i = 0; i < expression->curve_count; ++i)
        if (strcmp(expression->curves[i].name, copied_curve) == 0 ||
            strcmp(expression->curves[i].morph_target, copied_target) == 0) return false;
    for (u32 i = 0; i < keyframe_count; ++i) {
        if (!isfinite(times[i]) || !isfinite(values[i]) ||
            values[i] < 0.0f || values[i] > 1.0f ||
            (i > 0u && times[i] < times[i - 1u])) return false;
    }
    AnimFacialCurve *curve = &expression->curves[expression->curve_count];
    memcpy(curve->name, copied_curve, sizeof(copied_curve));
    memcpy(curve->morph_target, copied_target, sizeof(copied_target));
    curve->keyframe_count = keyframe_count;
    memcpy(curve->times, times, keyframe_count * sizeof(f32));
    memcpy(curve->values, values, keyframe_count * sizeof(f32));
    ++expression->curve_count;
    return true;
}

bool anim_facial_evaluate(const AnimFacialLibrary *library,
                          const AnimMorphSet *morphs, const char *expression_name,
                          f32 time, f32 *out_weights, u32 weight_count) {
    if (!library || !morphs || !expression_name || !out_weights || !isfinite(time) ||
        weight_count != morphs->target_count) return false;
    const AnimFacialExpression *expression = NULL;
    for (u32 i = 0; i < library->expression_count; ++i)
        if (strcmp(library->expressions[i].name, expression_name) == 0)
            expression = &library->expressions[i];
    if (!expression) return false;
    u32 resolved_targets[ANIM_FACIAL_MAX_CURVES];
    for (u32 c = 0; c < expression->curve_count; ++c) {
        const AnimFacialCurve *curve = &expression->curves[c];
        u32 target = 0u;
        while (target < morphs->target_count &&
               strcmp(morphs->targets[target].name, curve->morph_target) != 0) ++target;
        if (target == morphs->target_count) return false;
        resolved_targets[c] = target;
    }
    for (u32 i = 0; i < weight_count; ++i) out_weights[i] = 0.0f;
    for (u32 c = 0; c < expression->curve_count; ++c) {
        const AnimFacialCurve *curve = &expression->curves[c];
        u32 target = resolved_targets[c];
        u32 key = 0u;
        while (key + 1u < curve->keyframe_count && curve->times[key + 1u] <= time) ++key;
        if (time <= curve->times[0]) {
            out_weights[target] = curve->values[0];
        } else if (key + 1u >= curve->keyframe_count) {
            out_weights[target] = curve->values[key];
        } else {
            f32 span = curve->times[key + 1u] - curve->times[key];
            f32 fraction = span > 0.0f ? (time - curve->times[key]) / span : 1.0f;
            out_weights[target] = curve->values[key] +
                (curve->values[key + 1u] - curve->values[key]) * fraction;
        }
    }
    return true;
}
