/* Editor component registry + inspector data model — see
 * editor_components.h for the contract (registry-gated queries, undoable
 * byte-exact commands, strict locale-independent parse_f32). */

#include <editor/editor_components.h>

#include <editor/editor_internal.h>
#include <editor/editor_test_hooks.h>

#include <float.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* EditorTransform is tightly packed f32[9]: no padding, offsets match the
 * field table below. */
_Static_assert(sizeof(EditorTransform) == 36u, "EditorTransform must be 36 bytes");
_Static_assert(offsetof(EditorTransform, rot) == 12u, "rot offset");
_Static_assert(offsetof(EditorTransform, scale) == 24u, "scale offset");
_Static_assert(sizeof(EditorTransform) <= BREAK_EDITOR_COMPONENT_SNAPSHOT_CAPACITY,
               "transform fits the command snapshot cap");

static Entity ecs_id(BreakEditorEntityId id) {
    Entity e;
    e.index = id.index;
    e.generation = id.generation;
    return e;
}

/* ---------------------------------------------------------------- */
/* Registry                                                         */
/* ---------------------------------------------------------------- */

/* Field table for EditorTransform: pos.x..scale.z, type 0 = f32. Static
 * initializer keeps the strings zero-padded to 32 bytes. */
static const BreakEditorField k_transform_fields[9] = {
    { "pos.x", offsetof(EditorTransform, pos) + 0u * sizeof(f32), 0u },
    { "pos.y", offsetof(EditorTransform, pos) + 1u * sizeof(f32), 0u },
    { "pos.z", offsetof(EditorTransform, pos) + 2u * sizeof(f32), 0u },
    { "rot.x", offsetof(EditorTransform, rot) + 0u * sizeof(f32), 0u },
    { "rot.y", offsetof(EditorTransform, rot) + 1u * sizeof(f32), 0u },
    { "rot.z", offsetof(EditorTransform, rot) + 2u * sizeof(f32), 0u },
    { "scale.x", offsetof(EditorTransform, scale) + 0u * sizeof(f32), 0u },
    { "scale.y", offsetof(EditorTransform, scale) + 1u * sizeof(f32), 0u },
    { "scale.z", offsetof(EditorTransform, scale) + 2u * sizeof(f32), 0u },
};

/* A new transform is the identity, not all-zero: a zero scale renders
 * nothing and cannot be scaled up by the gizmo (its factor multiplies). */
static const EditorTransform k_transform_default = {
    {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};

static const BreakEditorField k_light_fields[6] = {
    { "color.r", offsetof(EditorLight, color) + 0u * sizeof(f32), 0u },
    { "color.g", offsetof(EditorLight, color) + 1u * sizeof(f32), 0u },
    { "color.b", offsetof(EditorLight, color) + 2u * sizeof(f32), 0u },
    { "intensity", offsetof(EditorLight, intensity), 0u },
    { "range", offsetof(EditorLight, range), 0u },
    { "enabled", offsetof(EditorLight, enabled), BREAK_EDITOR_FIELD_BOOL },
};

static const EditorLight k_light_default = {{1.0f, 1.0f, 1.0f}, 1.0f, 10.0f, 1u};

_Static_assert(sizeof(EditorLight) == 24u, "EditorLight is six packed 4-byte fields");
_Static_assert(sizeof(EditorLight) <= BREAK_EDITOR_COMPONENT_SNAPSHOT_CAPACITY,
               "light fits the command snapshot cap");

void break_editor_doc_init_components(BreakEditorDoc *doc) {
    /* World registration is what makes the component survive save/load
     * (BSCN COMPONENTS chunk stores raw bytes per registered type, and the
     * load path re-registers the doc's component set into the staging
     * world). world_register_component cannot fail for a fresh world. */
    world_register_component(break_editor_doc_world_raw(doc),
                             BREAK_EDITOR_COMPONENT_TRANSFORM,
                             (u32)sizeof(EditorTransform));

    BreakEditorComponentReg *reg = &doc->components[0];
    reg->component_id = BREAK_EDITOR_COMPONENT_TRANSFORM;
    memcpy(reg->display_name, "Transform", sizeof("Transform"));
    reg->size = (u32)sizeof(EditorTransform);
    memcpy(reg->fields, k_transform_fields, sizeof(k_transform_fields));
    reg->field_count = 9u;
    reg->default_bytes = (const u8 *)&k_transform_default;

    world_register_component(break_editor_doc_world_raw(doc),
                             BREAK_EDITOR_COMPONENT_LIGHT,
                             (u32)sizeof(EditorLight));
    reg = &doc->components[1];
    reg->component_id = BREAK_EDITOR_COMPONENT_LIGHT;
    memcpy(reg->display_name, "Light", sizeof("Light"));
    reg->size = (u32)sizeof(EditorLight);
    memcpy(reg->fields, k_light_fields, sizeof(k_light_fields));
    reg->field_count = 6u;
    reg->default_bytes = (const u8 *)&k_light_default;
    doc->component_count = 2u;
}

const BreakEditorComponentReg *break_editor_doc_find_component(
    const BreakEditorDoc *doc, u32 component_id) {
    if (!doc) return NULL;
    for (u32 i = 0; i < doc->component_count; i++) {
        if (doc->components[i].component_id == component_id) {
            return &doc->components[i];
        }
    }
    return NULL;
}

/* ---------------------------------------------------------------- */
/* Public queries                                                   */
/* ---------------------------------------------------------------- */

usize break_editor_doc_component_count(const BreakEditorDoc *doc) {
    return doc ? (usize)doc->component_count : 0u;
}

bool break_editor_doc_component_info(const BreakEditorDoc *doc, usize i,
                                     BreakEditorComponentInfo *out) {
    if (!doc || !out || i >= doc->component_count) return false;
    const BreakEditorComponentReg *reg = &doc->components[i];
    memset(out, 0, sizeof(*out)); /* deterministic: unused fields zeroed */
    out->component_id = reg->component_id;
    memcpy(out->display_name, reg->display_name, sizeof(out->display_name));
    memcpy(out->fields, reg->fields, sizeof(out->fields));
    out->field_count = reg->field_count;
    return true;
}

bool break_editor_doc_has_component(const BreakEditorDoc *doc,
                                    BreakEditorEntityId id,
                                    u32 component_id) {
    if (!doc || !break_editor_doc_has_entity(doc, id)) return false;
    if (!break_editor_doc_find_component(doc, component_id)) return false;
    return world_get_component(break_editor_doc_world_raw((BreakEditorDoc *)doc),
                               ecs_id(id), component_id) != NULL;
}

/* Shared validation for get/set: returns the registry entry and the field
 * descriptor, or NULL (bounded false for the caller). */
static const BreakEditorField *validate_field(const BreakEditorDoc *doc,
                                              BreakEditorEntityId id,
                                              u32 component_id,
                                              u32 field_index, u8 want_type,
                                              const BreakEditorComponentReg **out_reg) {
    if (!doc || !break_editor_doc_has_entity(doc, id)) return NULL;
    const BreakEditorComponentReg *reg =
        break_editor_doc_find_component(doc, component_id);
    if (!reg) return NULL;
    if (field_index >= reg->field_count) return NULL;
    const BreakEditorField *field = &reg->fields[field_index];
    if (field->type != want_type) return NULL;
    /* Defensive bound: the field (4 bytes for every type) must lie fully
     * inside the component. */
    if (field->offset > reg->size ||
        (usize)field->offset + sizeof(u32) > (usize)reg->size) {
        return NULL;
    }
    *out_reg = reg;
    return field;
}

bool break_editor_doc_get_field_f32(const BreakEditorDoc *doc,
                                    BreakEditorEntityId id, u32 component_id,
                                    u32 field_index, f32 *out) {
    if (!out) return false;
    const BreakEditorComponentReg *reg = NULL;
    const BreakEditorField *field =
        validate_field(doc, id, component_id, field_index,
                       BREAK_EDITOR_FIELD_F32, &reg);
    if (!field) return false;
    const u8 *base = world_get_component(
        break_editor_doc_world_raw((BreakEditorDoc *)doc), ecs_id(id),
        component_id);
    if (!base) return false; /* entity lacks the component */
    memcpy(out, base + field->offset, sizeof(f32));
    return true;
}

/* ---------------------------------------------------------------- */
/* Component commands                                               */
/* ---------------------------------------------------------------- */

static u8 *component_ptr(BreakEditorDoc *doc, BreakEditorEntityId id,
                         u32 component_id) {
    return (u8 *)world_get_component(break_editor_doc_world_raw(doc),
                                     ecs_id(id), component_id);
}

u8 *break_editor_doc_component_bytes(BreakEditorDoc *doc,
                                     BreakEditorEntityId id,
                                     u32 component_id) {
    if (!doc || !break_editor_doc_has_entity(doc, id)) return NULL;
    if (!break_editor_doc_find_component(doc, component_id)) return NULL;
    return component_ptr(doc, id, component_id);
}

static void component_cmd_destroy(BreakEditorCmd *self) {
    free(self);
}

/* ---- set_field_f32 ---- */

static bool set_field_apply(BreakEditorCmd *self, BreakEditorDoc *doc) {
    BreakEditorComponentCmd *c = (BreakEditorComponentCmd *)self;
    u8 *base = component_ptr(doc, self->id, c->component_id);
    if (!base) return false; /* entity/component gone: bounded failure */
    memcpy(base + c->field_offset, &c->new_bits, sizeof(u32));
    return true;
}

static bool set_field_revert(BreakEditorCmd *self, BreakEditorDoc *doc) {
    BreakEditorComponentCmd *c = (BreakEditorComponentCmd *)self;
    u8 *base = component_ptr(doc, self->id, c->component_id);
    if (!base) return false;
    memcpy(base + c->field_offset, &c->old_bits, sizeof(u32));
    return true;
}

static void set_field_describe(const BreakEditorCmd *self, char buf[128]) {
    const BreakEditorComponentCmd *c = (const BreakEditorComponentCmd *)self;
    f32 old_v, new_v;
    memcpy(&old_v, &c->old_bits, sizeof(old_v));
    memcpy(&new_v, &c->new_bits, sizeof(new_v));
    /* Precision-bounded: worst case provably < 128 bytes. */
    snprintf(buf, 128, "set %.24s.%.24s = %.6g -> %.6g (%u:%u)",
             c->display_name, c->field_name, (double)old_v, (double)new_v,
             self->id.index, self->id.generation);
}

static void set_field_bool_describe(const BreakEditorCmd *self, char buf[128]) {
    const BreakEditorComponentCmd *c = (const BreakEditorComponentCmd *)self;
    snprintf(buf, 128, "set %.24s.%.24s = %s -> %s (%u:%u)",
             c->display_name, c->field_name, c->old_bits ? "true" : "false",
             c->new_bits ? "true" : "false", self->id.index,
             self->id.generation);
}

/* Records an undoable 4-byte field write. Bitwise-identical bits are a
 * no-op success: no command, dirty unchanged. */
static bool push_set_bits(BreakEditorDoc *doc, BreakEditorEntityId id,
                          const BreakEditorComponentReg *reg,
                          const BreakEditorField *field, u32 new_bits,
                          void (*describe)(const BreakEditorCmd *, char[128])) {
    u8 *base = component_ptr(doc, id, reg->component_id);
    if (!base) return false; /* entity lacks the component */

    u32 old_bits;
    memcpy(&old_bits, base + field->offset, sizeof(u32));
    if (old_bits == new_bits) return true;

    BreakEditorComponentCmd *c = break_editor_test_calloc(sizeof(*c));
    if (!c) return false; /* OOM: bounded false, doc unchanged */
    c->base.apply = set_field_apply;
    c->base.revert = set_field_revert;
    c->base.destroy = component_cmd_destroy;
    c->base.describe = describe;
    c->base.kind = BREAK_EDITOR_CMD_KIND_SET_FIELD_F32;
    c->base.id = id;
    c->component_id = reg->component_id;
    c->field_offset = field->offset;
    c->old_bits = old_bits;
    c->new_bits = new_bits;
    memcpy(c->display_name, reg->display_name, sizeof(c->display_name));
    memcpy(c->field_name, field->name, sizeof(c->field_name));

    if (!c->base.apply(&c->base, doc)) {
        c->base.destroy(&c->base);
        return false;
    }
    break_editor_cmd_stack_push_applied(doc, &c->base);
    doc->dirty = true;
    return true;
}

bool break_editor_doc_set_field_f32(BreakEditorDoc *doc,
                                    BreakEditorEntityId id, u32 component_id,
                                    u32 field_index, f32 value) {
    const BreakEditorComponentReg *reg = NULL;
    const BreakEditorField *field =
        validate_field(doc, id, component_id, field_index,
                       BREAK_EDITOR_FIELD_F32, &reg);
    u32 bits;
    if (!field) return false;
    memcpy(&bits, &value, sizeof(bits));
    return push_set_bits(doc, id, reg, field, bits, set_field_describe);
}

bool break_editor_doc_get_field_bool(const BreakEditorDoc *doc,
                                     BreakEditorEntityId id, u32 component_id,
                                     u32 field_index, bool *out) {
    const BreakEditorComponentReg *reg = NULL;
    const BreakEditorField *field;
    const u8 *base;
    u32 bits;
    if (!out) return false;
    field = validate_field(doc, id, component_id, field_index,
                           BREAK_EDITOR_FIELD_BOOL, &reg);
    if (!field) return false;
    base = world_get_component(
        break_editor_doc_world_raw((BreakEditorDoc *)doc), ecs_id(id),
        component_id);
    if (!base) return false;
    memcpy(&bits, base + field->offset, sizeof(bits));
    *out = bits != 0u;
    return true;
}

bool break_editor_doc_set_field_bool(BreakEditorDoc *doc,
                                     BreakEditorEntityId id, u32 component_id,
                                     u32 field_index, bool value) {
    const BreakEditorComponentReg *reg = NULL;
    const BreakEditorField *field =
        validate_field(doc, id, component_id, field_index,
                       BREAK_EDITOR_FIELD_BOOL, &reg);
    bool cur = false;
    if (!field) return false;
    /* An unchanged truth value records nothing, even if the stored bits are
     * a nonzero other than 1. */
    if (!break_editor_doc_get_field_bool(doc, id, component_id, field_index,
                                         &cur)) {
        return false;
    }
    if (cur == value) return true;
    return push_set_bits(doc, id, reg, field, value ? 1u : 0u,
                         set_field_bool_describe);
}

/* ---- add_component ---- */

static bool add_component_apply(BreakEditorCmd *self, BreakEditorDoc *doc) {
    BreakEditorComponentCmd *c = (BreakEditorComponentCmd *)self;
    World *w = break_editor_doc_world_raw(doc);
    if (component_ptr(doc, self->id, c->component_id)) {
        return false; /* already present: bounded failure */
    }
    u8 *p = world_add_component(w, ecs_id(self->id), c->component_id);
    if (!p) return false; /* ECS cap/OOM: bounded failure */
    if (!c->snapshot_taken) {
        /* First apply: deterministic default bytes (the registry's
         * default_bytes, else zero — the ECS reuses chunk rows, so
         * world_add_component alone can hand back stale bytes), then
         * capture the post-add state for exact redo. */
        const BreakEditorComponentReg *reg =
            break_editor_doc_find_component(doc, c->component_id);
        if (reg != NULL && reg->default_bytes != NULL) {
            memcpy(p, reg->default_bytes, c->snapshot_size);
        } else {
            memset(p, 0, c->snapshot_size);
        }
        memcpy(c->snapshot, p, c->snapshot_size);
        c->snapshot_taken = true;
    } else {
        memcpy(p, c->snapshot, c->snapshot_size); /* redo: restore snapshot */
    }
    return true;
}

static bool add_component_revert(BreakEditorCmd *self, BreakEditorDoc *doc) {
    BreakEditorComponentCmd *c = (BreakEditorComponentCmd *)self;
    World *w = break_editor_doc_world_raw(doc);
    if (!component_ptr(doc, self->id, c->component_id)) return false;
    world_remove_component(w, ecs_id(self->id), c->component_id);
    return true;
}

static void add_component_describe(const BreakEditorCmd *self, char buf[128]) {
    const BreakEditorComponentCmd *c = (const BreakEditorComponentCmd *)self;
    snprintf(buf, 128, "add component %.32s (%u:%u)", c->display_name,
             self->id.index, self->id.generation);
}

bool break_editor_doc_add_component(BreakEditorDoc *doc,
                                    BreakEditorEntityId id,
                                    u32 component_id) {
    if (!doc || !break_editor_doc_has_entity(doc, id)) return false;
    const BreakEditorComponentReg *reg =
        break_editor_doc_find_component(doc, component_id);
    if (!reg) return false; /* unregistered id: bounded false */
    if (reg->size > BREAK_EDITOR_COMPONENT_SNAPSHOT_CAPACITY) {
        return false; /* cannot snapshot: bounded false */
    }
    if (component_ptr(doc, id, component_id)) {
        return false; /* already present: bounded false */
    }

    BreakEditorComponentCmd *c = break_editor_test_calloc(sizeof(*c));
    if (!c) return false; /* OOM: bounded false, doc unchanged */
    c->base.apply = add_component_apply;
    c->base.revert = add_component_revert;
    c->base.destroy = component_cmd_destroy;
    c->base.describe = add_component_describe;
    c->base.kind = BREAK_EDITOR_CMD_KIND_ADD_COMPONENT;
    c->base.id = id;
    c->component_id = component_id;
    c->snapshot_size = reg->size;
    memcpy(c->display_name, reg->display_name, sizeof(c->display_name));

    if (!c->base.apply(&c->base, doc)) {
        c->base.destroy(&c->base);
        return false;
    }
    break_editor_cmd_stack_push_applied(doc, &c->base);
    doc->dirty = true;
    return true;
}

/* ---- remove_component ---- */

static bool remove_component_apply(BreakEditorCmd *self, BreakEditorDoc *doc) {
    BreakEditorComponentCmd *c = (BreakEditorComponentCmd *)self;
    World *w = break_editor_doc_world_raw(doc);
    if (!component_ptr(doc, self->id, c->component_id)) return false;
    world_remove_component(w, ecs_id(self->id), c->component_id);
    return true;
}

static bool remove_component_revert(BreakEditorCmd *self, BreakEditorDoc *doc) {
    BreakEditorComponentCmd *c = (BreakEditorComponentCmd *)self;
    World *w = break_editor_doc_world_raw(doc);
    if (component_ptr(doc, self->id, c->component_id)) return false;
    u8 *p = world_add_component(w, ecs_id(self->id), c->component_id);
    if (!p) return false; /* ECS cap/OOM: bounded failure, cursor unchanged */
    memcpy(p, c->snapshot, c->snapshot_size); /* byte-exact restore */
    return true;
}

static void remove_component_describe(const BreakEditorCmd *self,
                                      char buf[128]) {
    const BreakEditorComponentCmd *c = (const BreakEditorComponentCmd *)self;
    snprintf(buf, 128, "remove component %.32s (%u:%u)", c->display_name,
             self->id.index, self->id.generation);
}

bool break_editor_doc_remove_component(BreakEditorDoc *doc,
                                       BreakEditorEntityId id,
                                       u32 component_id) {
    if (!doc || !break_editor_doc_has_entity(doc, id)) return false;
    const BreakEditorComponentReg *reg =
        break_editor_doc_find_component(doc, component_id);
    if (!reg) return false; /* unregistered id: bounded false */
    if (reg->size > BREAK_EDITOR_COMPONENT_SNAPSHOT_CAPACITY) {
        return false; /* cannot snapshot: bounded false */
    }
    const u8 *base = component_ptr(doc, id, component_id);
    if (!base) return false; /* absent: bounded false */

    BreakEditorComponentCmd *c = break_editor_test_calloc(sizeof(*c));
    if (!c) return false; /* OOM: bounded false, doc unchanged */
    c->base.apply = remove_component_apply;
    c->base.revert = remove_component_revert;
    c->base.destroy = component_cmd_destroy;
    c->base.describe = remove_component_describe;
    c->base.kind = BREAK_EDITOR_CMD_KIND_REMOVE_COMPONENT;
    c->base.id = id;
    c->component_id = component_id;
    c->snapshot_size = reg->size;
    memcpy(c->display_name, reg->display_name, sizeof(c->display_name));
    /* Snapshot the pre-remove bytes at construction: revert restores them
     * byte-exact. */
    memcpy(c->snapshot, base, reg->size);

    if (!c->base.apply(&c->base, doc)) {
        c->base.destroy(&c->base);
        return false;
    }
    break_editor_cmd_stack_push_applied(doc, &c->base);
    doc->dirty = true;
    return true;
}

/* ---------------------------------------------------------------- */
/* break_editor_parse_f32                                           */
/* ---------------------------------------------------------------- */

/* Strict string->f32 (grammar and policy in the header comment). The
 * conversion is digit-by-digit in double with a bounded power-of-ten loop;
 * strtod/strtof are never called, so the result is locale-independent. */
bool break_editor_parse_f32(const char *text, f32 *out) {
    if (!text || !out) return false;

    /* Bounded input: a NUL must appear within the first 64 bytes. */
    usize len = 0;
    while (len < BREAK_EDITOR_PARSE_F32_MAX_BYTES && text[len] != '\0') {
        len++;
    }
    if (len == 0 || len >= BREAK_EDITOR_PARSE_F32_MAX_BYTES) return false;

    usize i = 0;
    bool neg = false;
    if (text[i] == '+' || text[i] == '-') {
        neg = (text[i] == '-');
        i++;
    }

    /* Mantissa: digits with at most one '.'. At most 19 significant digits
     * are accumulated (f32 has ~7); extra integer digits contribute to the
     * scale, extra fraction digits are dropped (sub-f32-ulp, documented). */
    double mant = 0.0;
    u32 sig = 0;
    i32 exp_extra = 0;
    u32 frac = 0;
    bool dot = false;
    bool any_digit = false;
    for (; i < len; i++) {
        char ch = text[i];
        if (ch == '.' && !dot) {
            dot = true;
            continue;
        }
        if (ch < '0' || ch > '9') break;
        any_digit = true;
        if (sig < 19u) {
            mant = mant * 10.0 + (double)(ch - '0');
            sig++;
            if (dot) frac++;
        } else if (!dot) {
            exp_extra++;
        }
    }
    if (!any_digit) return false;

    /* Optional exponent. */
    i32 exp_val = 0;
    if (i < len && (text[i] == 'e' || text[i] == 'E')) {
        i++;
        bool eneg = false;
        if (i < len && (text[i] == '+' || text[i] == '-')) {
            eneg = (text[i] == '-');
            i++;
        }
        if (i >= len) return false; /* exponent marker without digits */
        u32 ev = 0;
        for (; i < len; i++) {
            char ch = text[i];
            if (ch < '0' || ch > '9') return false; /* garbage in exponent */
            ev = ev * 10u + (u32)(ch - '0');
            if (ev > 10000u) ev = 10000u; /* clamp: far past f32 range */
        }
        exp_val = eneg ? -(i32)ev : (i32)ev;
    }
    if (i != len) return false; /* trailing garbage */

    if (mant == 0.0) {
        *out = neg ? -0.0f : 0.0f; /* zero with any exponent, incl. -0 */
        return true;
    }

    /* v = mant * 10^scale. mant is an integer in [1, 1e19), so the loop
     * bounds below make a double overflow impossible (|v| < 1e59). */
    i32 scale = exp_val + exp_extra - (i32)frac;
    if (scale > 45) return false; /* certain f32 overflow (mant >= 1) */
    if (scale < -90) {            /* certain f32 underflow: flush to zero */
        *out = neg ? -0.0f : 0.0f;
        return true;
    }
    double v = mant;
    if (scale >= 0) {
        for (i32 k = 0; k < scale; k++) v *= 10.0;
    } else {
        for (i32 k = 0; k < -scale; k++) v /= 10.0;
    }

    /* Overflow: reject when v would round to f32 infinity. The rounding
     * boundary is FLT_MAX + half an f32 ulp at that magnitude (2^103);
     * values below it cast to a finite f32 (<= FLT_MAX). */
    const double boundary = (double)FLT_MAX + 0x1p103;
    if (!(v < boundary)) return false; /* includes any NaN/inf */

    f32 r = (f32)v; /* underflow to zero/subnormal is accepted (documented) */
    *out = neg ? -r : r;
    return true;
}
