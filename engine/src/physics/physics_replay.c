#include <physics/physics_replay.h>
#include <math.h>
#include <string.h>

#define PHYSICS_REPLAY_MAGIC 0x4c505250u /* "PRPL" little-endian */
#define PHYSICS_REPLAY_VERSION 1u

static void put_u32(u8 *out, u32 v) {
    out[0] = (u8)(v & 0xffu);
    out[1] = (u8)((v >> 8) & 0xffu);
    out[2] = (u8)((v >> 16) & 0xffu);
    out[3] = (u8)((v >> 24) & 0xffu);
}

static u32 get_u32(const u8 *in) {
    return (u32)in[0] | ((u32)in[1] << 8) | ((u32)in[2] << 16) | ((u32)in[3] << 24);
}

static void put_u64(u8 *out, u64 v) {
    put_u32(out, (u32)(v & 0xffffffffu));
    put_u32(out + 4, (u32)(v >> 32));
}

static u64 get_u64(const u8 *in) {
    return (u64)get_u32(in) | ((u64)get_u32(in + 4) << 32);
}

static u32 f32_bits(f32 v) {
    u32 bits;
    memcpy(&bits, &v, sizeof(bits));
    return bits;
}

static f32 bits_f32(u32 bits) {
    f32 v;
    memcpy(&v, &bits, sizeof(v));
    return v;
}

static bool replay_dt_valid(f32 dt) {
    return isfinite(dt) && dt > 0.0f;
}

bool physics_replay_init(PhysicsReplay *replay, PhysicsReplayRecord *storage, u32 capacity) {
    if (!replay || !storage) return false;
    replay->records = storage;
    replay->count = 0u;
    replay->capacity = capacity;
    return true;
}

bool physics_replay_impulse(PhysicsReplay *replay, PhysicsWorld *pw, PhysicsBodyHandle body,
                            Vec3 impulse) {
    if (!replay || !pw || replay->count >= replay->capacity) return false;
    if (!isfinite(impulse.e[0]) || !isfinite(impulse.e[1]) || !isfinite(impulse.e[2])) return false;
    if (!physics_body_resolve(pw, body)) return false;
    physics_body_apply_impulse(pw, body, impulse);
    PhysicsReplayRecord *r = &replay->records[replay->count++];
    memset(r, 0, sizeof(*r));
    r->op = PHYSICS_REPLAY_OP_IMPULSE;
    r->body = body;
    r->value[0] = impulse.e[0];
    r->value[1] = impulse.e[1];
    r->value[2] = impulse.e[2];
    return true;
}

bool physics_replay_step(PhysicsReplay *replay, PhysicsWorld *pw, f32 dt) {
    if (!replay || !pw || replay->count >= replay->capacity || !replay_dt_valid(dt)) return false;
    physics_step(pw, dt);
    PhysicsReplayRecord *r = &replay->records[replay->count++];
    memset(r, 0, sizeof(*r));
    r->op = PHYSICS_REPLAY_OP_STEP;
    r->body = PHYSICS_BODY_HANDLE_INVALID;
    r->value[0] = dt;
    r->hash_after = physics_state_hash(pw);
    return true;
}

bool physics_replay_encode(const PhysicsReplay *replay, u8 *buffer, usize capacity,
                           usize *out_size) {
    if (!replay) return false;
    usize size = PHYSICS_REPLAY_HEADER_BYTES + (usize)replay->count * PHYSICS_REPLAY_RECORD_BYTES;
    if (out_size) *out_size = size;
    if (!buffer || capacity < size) return false;
    put_u32(buffer, PHYSICS_REPLAY_MAGIC);
    put_u32(buffer + 4, PHYSICS_REPLAY_VERSION);
    put_u32(buffer + 8, replay->count);
    u8 *out = buffer + PHYSICS_REPLAY_HEADER_BYTES;
    for (u32 i = 0; i < replay->count; i++, out += PHYSICS_REPLAY_RECORD_BYTES) {
        const PhysicsReplayRecord *r = &replay->records[i];
        put_u32(out, r->op);
        put_u32(out + 4, r->body.index);
        put_u32(out + 8, r->body.generation);
        put_u32(out + 12, f32_bits(r->value[0]));
        put_u32(out + 16, f32_bits(r->value[1]));
        put_u32(out + 20, f32_bits(r->value[2]));
        put_u64(out + 24, r->hash_after);
    }
    return true;
}

static bool replay_record_valid(const u8 *in) {
    u32 op = get_u32(in);
    f32 v0 = bits_f32(get_u32(in + 12));
    f32 v1 = bits_f32(get_u32(in + 16));
    f32 v2 = bits_f32(get_u32(in + 20));
    if (op == PHYSICS_REPLAY_OP_STEP) return replay_dt_valid(v0);
    if (op == PHYSICS_REPLAY_OP_IMPULSE) return isfinite(v0) && isfinite(v1) && isfinite(v2);
    return false;
}

bool physics_replay_decode(PhysicsReplay *replay, const u8 *data, usize size) {
    if (!replay || !data || size < PHYSICS_REPLAY_HEADER_BYTES) return false;
    u32 count = get_u32(data + 8);
    if (get_u32(data) != PHYSICS_REPLAY_MAGIC || get_u32(data + 4) != PHYSICS_REPLAY_VERSION ||
        count > replay->capacity ||
        size != PHYSICS_REPLAY_HEADER_BYTES + (usize)count * PHYSICS_REPLAY_RECORD_BYTES) {
        return false;
    }
    const u8 *records = data + PHYSICS_REPLAY_HEADER_BYTES;
    for (u32 i = 0; i < count; i++) {
        if (!replay_record_valid(records + (usize)i * PHYSICS_REPLAY_RECORD_BYTES)) return false;
    }
    for (u32 i = 0; i < count; i++) {
        const u8 *in = records + (usize)i * PHYSICS_REPLAY_RECORD_BYTES;
        PhysicsReplayRecord *r = &replay->records[i];
        r->op = get_u32(in);
        r->body.index = get_u32(in + 4);
        r->body.generation = get_u32(in + 8);
        r->value[0] = bits_f32(get_u32(in + 12));
        r->value[1] = bits_f32(get_u32(in + 16));
        r->value[2] = bits_f32(get_u32(in + 20));
        r->hash_after = get_u64(in + 24);
    }
    replay->count = count;
    return true;
}

PhysicsReplayResult physics_replay_run(const PhysicsReplay *replay, PhysicsWorld *pw,
                                       u32 *out_divergent) {
    if (out_divergent) *out_divergent = UINT32_MAX;
    if (!replay || !pw || (replay->count != 0u && !replay->records)) return PHYSICS_REPLAY_INVALID;
    for (u32 i = 0; i < replay->count; i++) {
        const PhysicsReplayRecord *r = &replay->records[i];
        if (r->op == PHYSICS_REPLAY_OP_IMPULSE) {
            if (!physics_body_resolve(pw, r->body)) return PHYSICS_REPLAY_INVALID;
            physics_body_apply_impulse(pw, r->body, vec3(r->value[0], r->value[1], r->value[2]));
        } else if (r->op == PHYSICS_REPLAY_OP_STEP) {
            physics_step(pw, r->value[0]);
            if (physics_state_hash(pw) != r->hash_after) {
                if (out_divergent) *out_divergent = i;
                return PHYSICS_REPLAY_DIVERGED;
            }
        } else {
            return PHYSICS_REPLAY_INVALID;
        }
    }
    return PHYSICS_REPLAY_OK;
}
