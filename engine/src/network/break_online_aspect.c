#include <network/break_online_aspect.h>

#include <core/platform_thread.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct AspectObject {
    bool used;
    bool dormant;
    u32 generation;
    u64 active_mask;
    u64 revision;
    u64 record_epoch;
    u64 record_hash;
} AspectObject;

struct BreakAspectStore {
    PlatformThreadId owner;
    u32 max_objects;
    u32 value_stride;
    u32 packet_capacity;
    bool schema_locked;
    bool schema_used[BREAK_ASPECT_MAX_SCHEMAS];
    BreakAspectSchema schemas[BREAK_ASPECT_MAX_SCHEMAS];
    AspectObject *objects;
    u16 *sizes;
    u8 *values;
    u16 *staging_sizes;
    u8 *staging_values;
    u8 *packet_scratch;
};

typedef struct AspectWriter {
    u8 *data;
    usize capacity;
    usize position;
} AspectWriter;

typedef struct AspectReader {
    const u8 *data;
    usize capacity;
    usize position;
} AspectReader;

static bool aspect_owner(const BreakAspectStore *store)
{
    return store && platform_thread_id_equal(store->owner,
                                              platform_thread_current_id());
}

static u32 initial_generation(u32 generation)
{
    return generation == 0u ? 1u : generation;
}

static u32 retire_generation(u32 generation)
{
    return generation == UINT32_MAX ? generation : generation + 1u;
}

static u64 aspect_bit(u32 aspect_id)
{
    return UINT64_C(1) << (aspect_id - 1u);
}

static usize value_index(u32 object_index, u32 aspect_id)
{
    return (usize)object_index * BREAK_ASPECT_MAX_SCHEMAS + (aspect_id - 1u);
}

static u8 *value_at(BreakAspectStore *store, u32 object_index, u32 aspect_id)
{
    return store->values + value_index(object_index, aspect_id) * store->value_stride;
}

static const u8 *value_at_const(const BreakAspectStore *store,
                                u32 object_index, u32 aspect_id)
{
    return store->values + value_index(object_index, aspect_id) * store->value_stride;
}

static u8 *staging_at(BreakAspectStore *store, u32 aspect_id)
{
    return store->staging_values + (aspect_id - 1u) * store->value_stride;
}

static BreakRuntimeError find_object(const BreakAspectStore *store,
                                     BreakOnlineHandle handle,
                                     AspectObject **out)
{
    AspectObject *object;
    if (!break_online_handle_valid(handle) || handle.index >= store->max_objects) {
        return BREAK_RUNTIME_INVALID;
    }
    object = &store->objects[handle.index];
    if (!object->used || object->generation != handle.generation) {
        return BREAK_RUNTIME_STALE;
    }
    *out = object;
    return BREAK_RUNTIME_OK;
}

static const BreakAspectSchema *find_schema(const BreakAspectStore *store,
                                            u32 aspect_id, BreakAspectType type)
{
    if (!aspect_id || aspect_id > BREAK_ASPECT_MAX_SCHEMAS ||
        !store->schema_used[aspect_id - 1u]) return NULL;
    if (store->schemas[aspect_id - 1u].type != type) return NULL;
    return &store->schemas[aspect_id - 1u];
}

static void put_u32(u8 *out, u32 value)
{
    u32 i;
    for (i = 0u; i < 4u; ++i) out[i] = (u8)(value >> (i * 8u));
}

static u32 get_u32(const u8 *in)
{
    u32 value = 0u;
    u32 i;
    for (i = 0u; i < 4u; ++i) value |= (u32)in[i] << (i * 8u);
    return value;
}

static void put_u64(u8 *out, u64 value)
{
    u32 i;
    for (i = 0u; i < 8u; ++i) out[i] = (u8)(value >> (i * 8u));
}

static u64 get_u64(const u8 *in)
{
    u64 value = 0u;
    u32 i;
    for (i = 0u; i < 8u; ++i) value |= (u64)in[i] << (i * 8u);
    return value;
}

static bool write_bytes(AspectWriter *writer, const void *data, usize size)
{
    if (size > writer->capacity - writer->position) return false;
    if (size) memcpy(writer->data + writer->position, data, size);
    writer->position += size;
    return true;
}

static bool write_u8(AspectWriter *writer, u8 value)
{
    return write_bytes(writer, &value, 1u);
}

static bool write_u64(AspectWriter *writer, u64 value)
{
    u8 bytes[8];
    put_u64(bytes, value);
    return write_bytes(writer, bytes, sizeof(bytes));
}

static bool write_varint(AspectWriter *writer, u64 value)
{
    do {
        u8 byte = (u8)(value & 0x7fu);
        value >>= 7u;
        if (value) byte |= 0x80u;
        if (!write_u8(writer, byte)) return false;
    } while (value);
    return true;
}

static bool read_bytes(AspectReader *reader, void *out, usize size)
{
    if (size > reader->capacity - reader->position) return false;
    if (size) memcpy(out, reader->data + reader->position, size);
    reader->position += size;
    return true;
}

static bool read_u8(AspectReader *reader, u8 *out)
{
    return read_bytes(reader, out, 1u);
}

static bool read_u64(AspectReader *reader, u64 *out)
{
    u8 bytes[8];
    if (!read_bytes(reader, bytes, sizeof(bytes))) return false;
    *out = get_u64(bytes);
    return true;
}

static bool read_varint(AspectReader *reader, u64 *out)
{
    u64 value = 0u;
    u32 i;
    for (i = 0u; i < 10u; ++i) {
        u8 byte;
        if (!read_u8(reader, &byte)) return false;
        if (i == 9u && (byte & 0xfeu) != 0u) return false;
        value |= (u64)(byte & 0x7fu) << (i * 7u);
        if ((byte & 0x80u) == 0u) {
            if (i != 0u && byte == 0u) return false;
            *out = value;
            return true;
        }
    }
    return false;
}

static u64 hash_byte(u64 hash, u8 byte)
{
    return (hash ^ byte) * UINT64_C(1099511628211);
}

static u64 hash_u32(u64 hash, u32 value)
{
    u32 i;
    for (i = 0u; i < 4u; ++i) hash = hash_byte(hash, (u8)(value >> (i * 8u)));
    return hash;
}

static u64 hash_packet(const u8 *packet, usize size)
{
    u64 hash = UINT64_C(14695981039346656037);
    usize i;
    for (i = 0u; i < size; ++i) hash = hash_byte(hash, packet[i]);
    return hash;
}

BreakRuntimeError break_aspect_store_create(const BreakAspectStoreConfig *config,
                                            BreakAspectStore **out)
{
    BreakAspectStore *store;
    usize slots;
    if (!out) return BREAK_RUNTIME_INVALID;
    *out = NULL;
    if (!config || !config->max_objects ||
        config->max_objects > BREAK_ASPECT_HARD_MAX_OBJECTS ||
        config->max_value_bytes < 4u ||
        config->max_value_bytes > BREAK_ASPECT_HARD_MAX_VALUE_BYTES ||
        config->max_packet_bytes < 25u ||
        config->max_packet_bytes > BREAK_ASPECT_HARD_MAX_PACKET_BYTES) {
        return BREAK_RUNTIME_INVALID;
    }
    slots = (usize)config->max_objects * BREAK_ASPECT_MAX_SCHEMAS;
    if (slots > SIZE_MAX / config->max_value_bytes ||
        slots > SIZE_MAX / sizeof(u16)) return BREAK_RUNTIME_INVALID;
    store = (BreakAspectStore *)calloc(1u, sizeof(*store));
    if (!store) return BREAK_RUNTIME_OOM;
    store->objects = (AspectObject *)calloc(config->max_objects, sizeof(*store->objects));
    store->sizes = (u16 *)calloc(slots, sizeof(*store->sizes));
    store->values = (u8 *)calloc(slots, config->max_value_bytes);
    store->staging_sizes = (u16 *)calloc(BREAK_ASPECT_MAX_SCHEMAS,
                                         sizeof(*store->staging_sizes));
    store->staging_values = (u8 *)calloc(BREAK_ASPECT_MAX_SCHEMAS,
                                         config->max_value_bytes);
    store->packet_scratch = (u8 *)malloc(config->max_packet_bytes);
    if (!store->objects || !store->sizes || !store->values ||
        !store->staging_sizes || !store->staging_values || !store->packet_scratch) {
        free(store->packet_scratch);
        free(store->staging_values);
        free(store->staging_sizes);
        free(store->values);
        free(store->sizes);
        free(store->objects);
        free(store);
        return BREAK_RUNTIME_OOM;
    }
    store->owner = platform_thread_current_id();
    store->max_objects = config->max_objects;
    store->value_stride = config->max_value_bytes;
    store->packet_capacity = config->max_packet_bytes;
    *out = store;
    return BREAK_RUNTIME_OK;
}

void break_aspect_store_destroy(BreakAspectStore *store)
{
    if (!aspect_owner(store)) return;
    free(store->packet_scratch);
    free(store->staging_values);
    free(store->staging_sizes);
    free(store->values);
    free(store->sizes);
    free(store->objects);
    free(store);
}

BreakRuntimeError break_aspect_schema_register(BreakAspectStore *store,
                                               const BreakAspectSchema *schema)
{
    if (!aspect_owner(store)) return BREAK_RUNTIME_REJECTED;
    if (!schema || !schema->aspect_id || schema->aspect_id > BREAK_ASPECT_MAX_SCHEMAS ||
        !schema->version || schema->type < BREAK_ASPECT_U32 ||
        schema->type > BREAK_ASPECT_BYTES) return BREAK_RUNTIME_INVALID;
    if (schema->type == BREAK_ASPECT_BYTES) {
        if (!schema->byte_capacity || schema->byte_capacity > store->value_stride) {
            return BREAK_RUNTIME_INVALID;
        }
    } else if (schema->byte_capacity != 4u) {
        return BREAK_RUNTIME_INVALID;
    }
    if (store->schema_locked || store->schema_used[schema->aspect_id - 1u]) {
        return BREAK_RUNTIME_REJECTED;
    }
    store->schemas[schema->aspect_id - 1u] = *schema;
    store->schema_used[schema->aspect_id - 1u] = true;
    return BREAK_RUNTIME_OK;
}

static void clear_object_storage(BreakAspectStore *store, u32 object_index)
{
    memset(store->sizes + (usize)object_index * BREAK_ASPECT_MAX_SCHEMAS, 0,
           BREAK_ASPECT_MAX_SCHEMAS * sizeof(*store->sizes));
    memset(value_at(store, object_index, 1u), 0,
           BREAK_ASPECT_MAX_SCHEMAS * (usize)store->value_stride);
}

BreakRuntimeError break_aspect_object_create(BreakAspectStore *store,
                                             BreakOnlineHandle *out)
{
    u32 i;
    if (!aspect_owner(store)) return BREAK_RUNTIME_REJECTED;
    if (!out) return BREAK_RUNTIME_INVALID;
    for (i = 0u; i < store->max_objects; ++i) {
        AspectObject *object = &store->objects[i];
        if (!object->used && object->generation != UINT32_MAX) {
            BreakOnlineHandle handle = {i, initial_generation(object->generation)};
            memset(object, 0, sizeof(*object));
            object->used = true;
            object->generation = handle.generation;
            clear_object_storage(store, i);
            store->schema_locked = true;
            *out = handle;
            return BREAK_RUNTIME_OK;
        }
    }
    return BREAK_RUNTIME_OVERLOAD;
}

BreakRuntimeError break_aspect_object_adopt(BreakAspectStore *store,
                                            BreakOnlineHandle remote)
{
    AspectObject *object;
    if (!aspect_owner(store)) return BREAK_RUNTIME_REJECTED;
    if (!break_online_handle_valid(remote) || remote.index >= store->max_objects) {
        return BREAK_RUNTIME_INVALID;
    }
    object = &store->objects[remote.index];
    if (object->used) return BREAK_RUNTIME_REJECTED;
    if (object->generation != 0u && remote.generation < object->generation) {
        return BREAK_RUNTIME_STALE;
    }
    memset(object, 0, sizeof(*object));
    object->used = true;
    object->generation = remote.generation;
    clear_object_storage(store, remote.index);
    store->schema_locked = true;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_aspect_object_destroy(BreakAspectStore *store,
                                              BreakOnlineHandle handle)
{
    AspectObject *object;
    BreakRuntimeError result;
    if (!aspect_owner(store)) return BREAK_RUNTIME_REJECTED;
    result = find_object(store, handle, &object);
    if (result != BREAK_RUNTIME_OK) return result;
    object->used = false;
    object->generation = retire_generation(object->generation);
    object->active_mask = 0u;
    object->revision = 0u;
    return BREAK_RUNTIME_OK;
}

u64 break_aspect_object_revision(const BreakAspectStore *store,
                                 BreakOnlineHandle handle)
{
    AspectObject *object;
    if (!aspect_owner(store) || find_object(store, handle, &object) != BREAK_RUNTIME_OK) {
        return 0u;
    }
    return object->revision;
}

u64 break_aspect_active_mask(const BreakAspectStore *store,
                             BreakOnlineHandle handle)
{
    AspectObject *object;
    if (!aspect_owner(store) || find_object(store, handle, &object) != BREAK_RUNTIME_OK) {
        return 0u;
    }
    return object->active_mask;
}

u64 break_aspect_schema_hash(const BreakAspectStore *store)
{
    u64 hash = UINT64_C(14695981039346656037);
    u32 i;
    if (!aspect_owner(store)) return 0u;
    for (i = 1u; i <= BREAK_ASPECT_MAX_SCHEMAS; ++i) {
        if (!store->schema_used[i - 1u]) continue;
        hash = hash_u32(hash, i);
        hash = hash_u32(hash, store->schemas[i - 1u].version);
        hash = hash_u32(hash, (u32)store->schemas[i - 1u].type);
        hash = hash_u32(hash, store->schemas[i - 1u].byte_capacity);
    }
    return hash;
}

u64 break_aspect_aoi_id(BreakOnlineHandle handle)
{
    return ((u64)handle.generation << 32u) | handle.index;
}

static BreakRuntimeError set_encoded(BreakAspectStore *store,
                                     BreakOnlineHandle handle, u32 aspect_id,
                                     BreakAspectType type, const void *data, u32 size)
{
    const BreakAspectSchema *schema;
    AspectObject *object;
    BreakRuntimeError result;
    u8 *destination;
    if (!aspect_owner(store)) return BREAK_RUNTIME_REJECTED;
    schema = find_schema(store, aspect_id, type);
    if (!schema || (size && !data) || size > schema->byte_capacity ||
        (type != BREAK_ASPECT_BYTES && size != 4u)) return BREAK_RUNTIME_INVALID;
    result = find_object(store, handle, &object);
    if (result != BREAK_RUNTIME_OK) return result;
    if (object->revision == UINT64_MAX || object->record_epoch == UINT64_MAX) {
        return BREAK_RUNTIME_OVERLOAD;
    }
    destination = value_at(store, handle.index, aspect_id);
    if ((object->active_mask & aspect_bit(aspect_id)) != 0u &&
        store->sizes[value_index(handle.index, aspect_id)] == size &&
        (size == 0u || memcmp(destination, data, size) == 0)) {
        return BREAK_RUNTIME_OK;
    }
    if (size) memcpy(destination, data, size);
    store->sizes[value_index(handle.index, aspect_id)] = (u16)size;
    object->active_mask |= aspect_bit(aspect_id);
    object->revision++;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_aspect_set_u32(BreakAspectStore *store,
                                       BreakOnlineHandle object, u32 aspect_id, u32 value)
{
    u8 bytes[4];
    put_u32(bytes, value);
    return set_encoded(store, object, aspect_id, BREAK_ASPECT_U32, bytes, sizeof(bytes));
}

BreakRuntimeError break_aspect_set_i32(BreakAspectStore *store,
                                       BreakOnlineHandle object, u32 aspect_id, i32 value)
{
    u8 bytes[4];
    put_u32(bytes, (u32)value);
    return set_encoded(store, object, aspect_id, BREAK_ASPECT_I32, bytes, sizeof(bytes));
}

BreakRuntimeError break_aspect_set_f32(BreakAspectStore *store,
                                       BreakOnlineHandle object, u32 aspect_id, f32 value)
{
    u8 bytes[4];
    u32 bits;
    if (!isfinite((double)value)) return BREAK_RUNTIME_INVALID;
    memcpy(&bits, &value, sizeof(bits));
    put_u32(bytes, bits);
    return set_encoded(store, object, aspect_id, BREAK_ASPECT_F32, bytes, sizeof(bytes));
}

BreakRuntimeError break_aspect_set_bytes(BreakAspectStore *store,
                                         BreakOnlineHandle object, u32 aspect_id,
                                         const void *data, u32 size)
{
    return set_encoded(store, object, aspect_id, BREAK_ASPECT_BYTES, data, size);
}

static BreakRuntimeError get_encoded(const BreakAspectStore *store,
                                     BreakOnlineHandle handle, u32 aspect_id,
                                     BreakAspectType type, const u8 **out, u32 *out_size)
{
    const BreakAspectSchema *schema;
    AspectObject *object;
    BreakRuntimeError result;
    if (!aspect_owner(store)) return BREAK_RUNTIME_REJECTED;
    schema = find_schema(store, aspect_id, type);
    if (!schema || !out || !out_size) return BREAK_RUNTIME_INVALID;
    result = find_object(store, handle, &object);
    if (result != BREAK_RUNTIME_OK) return result;
    if ((object->active_mask & aspect_bit(aspect_id)) == 0u) return BREAK_RUNTIME_FAILED;
    *out = value_at_const(store, handle.index, aspect_id);
    *out_size = store->sizes[value_index(handle.index, aspect_id)];
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_aspect_get_u32(const BreakAspectStore *store,
                                       BreakOnlineHandle object, u32 aspect_id, u32 *out)
{
    const u8 *bytes;
    u32 size;
    BreakRuntimeError result;
    if (!out) return BREAK_RUNTIME_INVALID;
    result = get_encoded(store, object, aspect_id, BREAK_ASPECT_U32, &bytes, &size);
    if (result == BREAK_RUNTIME_OK) *out = get_u32(bytes);
    return result;
}

BreakRuntimeError break_aspect_get_i32(const BreakAspectStore *store,
                                       BreakOnlineHandle object, u32 aspect_id, i32 *out)
{
    const u8 *bytes;
    u32 size;
    u32 bits;
    BreakRuntimeError result;
    if (!out) return BREAK_RUNTIME_INVALID;
    result = get_encoded(store, object, aspect_id, BREAK_ASPECT_I32, &bytes, &size);
    if (result != BREAK_RUNTIME_OK) return result;
    bits = get_u32(bytes);
    *out = bits <= INT32_MAX ? (i32)bits : (i32)(-1 - (i64)(UINT32_MAX - bits));
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_aspect_get_f32(const BreakAspectStore *store,
                                       BreakOnlineHandle object, u32 aspect_id, f32 *out)
{
    const u8 *bytes;
    u32 size;
    u32 bits;
    BreakRuntimeError result;
    if (!out) return BREAK_RUNTIME_INVALID;
    result = get_encoded(store, object, aspect_id, BREAK_ASPECT_F32, &bytes, &size);
    if (result != BREAK_RUNTIME_OK) return result;
    bits = get_u32(bytes);
    memcpy(out, &bits, sizeof(bits));
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_aspect_get_bytes(const BreakAspectStore *store,
                                         BreakOnlineHandle object, u32 aspect_id,
                                         void *out, u32 capacity, u32 *out_size)
{
    const u8 *bytes;
    u32 size;
    BreakRuntimeError result;
    if (!out_size) return BREAK_RUNTIME_INVALID;
    result = get_encoded(store, object, aspect_id, BREAK_ASPECT_BYTES, &bytes, &size);
    if (result != BREAK_RUNTIME_OK) return result;
    if (capacity < size || (size && !out)) return BREAK_RUNTIME_OVERLOAD;
    if (size) memcpy(out, bytes, size);
    *out_size = size;
    return BREAK_RUNTIME_OK;
}

static bool encode_aspect(BreakAspectStore *store, AspectWriter *writer,
                          BreakOnlineHandle object, u32 aspect_id)
{
    const BreakAspectSchema *schema = &store->schemas[aspect_id - 1u];
    const u8 *bytes = value_at_const(store, object.index, aspect_id);
    u32 bits;
    switch (schema->type) {
    case BREAK_ASPECT_U32:
        return write_varint(writer, get_u32(bytes));
    case BREAK_ASPECT_I32:
        bits = get_u32(bytes);
        {
            i32 value = bits <= INT32_MAX ? (i32)bits : (i32)(-1 - (i64)(UINT32_MAX - bits));
            u32 zigzag = value >= 0 ? (u32)value * 2u
                                    : (u32)(-(i64)value) * 2u - 1u;
            return write_varint(writer, zigzag);
        }
    case BREAK_ASPECT_F32:
        return write_bytes(writer, bytes, 4u);
    case BREAK_ASPECT_BYTES:
        return write_varint(writer, store->sizes[value_index(object.index, aspect_id)]) &&
               write_bytes(writer, bytes, store->sizes[value_index(object.index, aspect_id)]);
    default:
        return false;
    }
}

BreakRuntimeError break_aspect_encode_with_epoch(BreakAspectStore *store,
                                      BreakOnlineHandle handle, u64 mask, u8 kind,
                                      u64 record_epoch, u8 *out, usize capacity,
                                      usize *out_size)
{
    AspectObject *object;
    BreakRuntimeError result;
    AspectWriter writer;
    u32 aspect_id;
    if (!aspect_owner(store)) return BREAK_RUNTIME_REJECTED;
    if (!out || !out_size || !record_epoch || kind < BREAK_ASPECT_BASELINE ||
        kind > BREAK_ASPECT_DORMANT) return BREAK_RUNTIME_INVALID;
    result = find_object(store, handle, &object);
    if (result != BREAK_RUNTIME_OK) return result;
    if (record_epoch < object->record_epoch) return BREAK_RUNTIME_STALE;
    if ((kind == BREAK_ASPECT_BASELINE && mask != object->active_mask) ||
        (kind == BREAK_ASPECT_DIRTY &&
         (!mask || (mask & object->active_mask) != mask)) ||
        ((kind == BREAK_ASPECT_DESTROY || kind == BREAK_ASPECT_DORMANT) && mask)) {
        return BREAK_RUNTIME_INVALID;
    }
    for (aspect_id = 1u; aspect_id <= BREAK_ASPECT_MAX_SCHEMAS; ++aspect_id) {
        if ((mask & aspect_bit(aspect_id)) != 0u && !store->schema_used[aspect_id - 1u]) {
            return BREAK_RUNTIME_INVALID;
        }
    }
    writer.data = store->packet_scratch;
    writer.capacity = store->packet_capacity;
    writer.position = 0u;
    if (!write_bytes(&writer, "BRA1", 4u) ||
        !write_u64(&writer, break_aspect_schema_hash(store)) ||
        !write_u64(&writer, break_aspect_aoi_id(handle)) ||
        !write_varint(&writer, record_epoch) || !write_u8(&writer, kind) ||
        !write_varint(&writer, mask)) return BREAK_RUNTIME_OVERLOAD;
    if (kind == BREAK_ASPECT_BASELINE || kind == BREAK_ASPECT_DIRTY) {
        for (aspect_id = 1u; aspect_id <= BREAK_ASPECT_MAX_SCHEMAS; ++aspect_id) {
            if ((mask & aspect_bit(aspect_id)) != 0u &&
                !encode_aspect(store, &writer, handle, aspect_id)) {
                return BREAK_RUNTIME_OVERLOAD;
            }
        }
    }
    if (capacity < writer.position) return BREAK_RUNTIME_OVERLOAD;
    if (record_epoch == object->record_epoch &&
        object->record_hash != hash_packet(writer.data, writer.position)) {
        return BREAK_RUNTIME_STALE;
    }
    memcpy(out, writer.data, writer.position);
    *out_size = writer.position;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_aspect_encode(BreakAspectStore *store,
                                      BreakOnlineHandle handle, u64 mask, u8 kind,
                                      u8 *out, usize capacity, usize *out_size)
{
    AspectObject *object;
    BreakRuntimeError result;
    u64 epoch;
    if (!aspect_owner(store)) return BREAK_RUNTIME_REJECTED;
    result = find_object(store, handle, &object);
    if (result != BREAK_RUNTIME_OK) return result;
    if (kind == BREAK_ASPECT_DESTROY || kind == BREAK_ASPECT_DORMANT) {
        if (object->revision == UINT64_MAX) return BREAK_RUNTIME_OVERLOAD;
        epoch = object->revision + 1u;
    } else {
        epoch = object->revision;
    }
    return break_aspect_encode_with_epoch(store, handle, mask, kind, epoch,
                                          out, capacity, out_size);
}

static bool decode_aspect(BreakAspectStore *store, AspectReader *reader,
                          BreakOnlineHandle handle, u32 aspect_id)
{
    const BreakAspectSchema *schema = &store->schemas[aspect_id - 1u];
    u64 value;
    u8 *destination = staging_at(store, aspect_id);
    (void)handle;
    switch (schema->type) {
    case BREAK_ASPECT_U32:
        if (!read_varint(reader, &value) || value > UINT32_MAX) return false;
        put_u32(destination, (u32)value);
        store->staging_sizes[aspect_id - 1u] = 4u;
        return true;
    case BREAK_ASPECT_I32:
        if (!read_varint(reader, &value) || value > UINT32_MAX) return false;
        {
            u32 zigzag = (u32)value;
            i32 signed_value = (zigzag & 1u)
                ? (i32)(-(i64)((zigzag >> 1u) + 1u))
                : (i32)(zigzag >> 1u);
            put_u32(destination, (u32)signed_value);
            store->staging_sizes[aspect_id - 1u] = 4u;
        }
        return true;
    case BREAK_ASPECT_F32:
        if (!read_bytes(reader, destination, 4u)) return false;
        {
            u32 bits = get_u32(destination);
            f32 float_value;
            memcpy(&float_value, &bits, sizeof(float_value));
            if (!isfinite((double)float_value)) return false;
        }
        store->staging_sizes[aspect_id - 1u] = 4u;
        return true;
    case BREAK_ASPECT_BYTES:
        if (!read_varint(reader, &value) || value > schema->byte_capacity ||
            value > reader->capacity - reader->position ||
            !read_bytes(reader, destination, (usize)value)) return false;
        store->staging_sizes[aspect_id - 1u] = (u16)value;
        return true;
    default:
        return false;
    }
}

BreakRuntimeError break_aspect_apply(BreakAspectStore *store,
                                     const u8 *packet, usize size)
{
    AspectReader reader;
    BreakOnlineHandle handle;
    AspectObject *object;
    BreakRuntimeError result;
    u64 schema_hash;
    u64 object_id;
    u64 revision;
    u64 mask;
    u64 new_active;
    u64 packet_hash;
    u8 kind;
    u32 aspect_id;
    if (!aspect_owner(store)) return BREAK_RUNTIME_REJECTED;
    if (!packet) return BREAK_RUNTIME_INVALID;
    reader.data = packet;
    reader.capacity = size;
    reader.position = 0u;
    {
        char magic[4];
        if (!read_bytes(&reader, magic, sizeof(magic)) ||
            memcmp(magic, "BRA1", sizeof(magic)) != 0 ||
            !read_u64(&reader, &schema_hash) ||
            schema_hash != break_aspect_schema_hash(store) ||
            !read_u64(&reader, &object_id) || !read_varint(&reader, &revision) ||
            !read_u8(&reader, &kind) || !read_varint(&reader, &mask)) {
            return BREAK_RUNTIME_INVALID;
        }
    }
    if (kind != BREAK_ASPECT_BASELINE && kind != BREAK_ASPECT_DIRTY &&
        kind != BREAK_ASPECT_DESTROY && kind != BREAK_ASPECT_DORMANT) {
        return BREAK_RUNTIME_INVALID;
    }
    handle.index = (u32)object_id;
    handle.generation = (u32)(object_id >> 32u);
    result = find_object(store, handle, &object);
    if (result != BREAK_RUNTIME_OK) return result;
    packet_hash = hash_packet(packet, size);
    if (revision < object->record_epoch) return BREAK_RUNTIME_STALE;
    if (revision == object->record_epoch) {
        if (object->record_hash == packet_hash) return BREAK_RUNTIME_OK;
        return BREAK_RUNTIME_STALE;
    }
    if (kind == BREAK_ASPECT_DESTROY || kind == BREAK_ASPECT_DORMANT) {
        if (mask) return BREAK_RUNTIME_INVALID;
        if (reader.position != reader.capacity) return BREAK_RUNTIME_INVALID;
        object->active_mask = 0u;
        object->dormant = true;
        object->record_epoch = revision;
        object->record_hash = packet_hash;
        return BREAK_RUNTIME_OK;
    }
    if (kind == BREAK_ASPECT_DIRTY && !mask) return BREAK_RUNTIME_STALE;
    for (aspect_id = 1u; aspect_id <= BREAK_ASPECT_MAX_SCHEMAS; ++aspect_id) {
        if ((mask & aspect_bit(aspect_id)) != 0u && !store->schema_used[aspect_id - 1u]) {
            return BREAK_RUNTIME_INVALID;
        }
    }
    memcpy(store->staging_values, value_at(store, handle.index, 1u),
           BREAK_ASPECT_MAX_SCHEMAS * (usize)store->value_stride);
    memcpy(store->staging_sizes, store->sizes + (usize)handle.index * BREAK_ASPECT_MAX_SCHEMAS,
           BREAK_ASPECT_MAX_SCHEMAS * sizeof(*store->staging_sizes));
    for (aspect_id = 1u; aspect_id <= BREAK_ASPECT_MAX_SCHEMAS; ++aspect_id) {
        if ((mask & aspect_bit(aspect_id)) != 0u &&
            !decode_aspect(store, &reader, handle, aspect_id)) {
            return BREAK_RUNTIME_INVALID;
        }
    }
    if (reader.position != reader.capacity) return BREAK_RUNTIME_INVALID;
    for (aspect_id = 1u; aspect_id <= BREAK_ASPECT_MAX_SCHEMAS; ++aspect_id) {
        if ((mask & aspect_bit(aspect_id)) != 0u) {
            usize index = value_index(handle.index, aspect_id);
            memcpy(value_at(store, handle.index, aspect_id), staging_at(store, aspect_id),
                   store->staging_sizes[aspect_id - 1u]);
            store->sizes[index] = store->staging_sizes[aspect_id - 1u];
        }
    }
    new_active = kind == BREAK_ASPECT_BASELINE ? mask : object->active_mask | mask;
    object->dormant = false;
    object->active_mask = new_active;
    object->record_epoch = revision;
    object->record_hash = packet_hash;
    return BREAK_RUNTIME_OK;
}
