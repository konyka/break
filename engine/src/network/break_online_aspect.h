#pragma once

#include <network/break_online_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_ASPECT_MAX_SCHEMAS 64u
#define BREAK_ASPECT_HARD_MAX_OBJECTS 1024u
#define BREAK_ASPECT_HARD_MAX_VALUE_BYTES 256u
#define BREAK_ASPECT_HARD_MAX_PACKET_BYTES 65536u

typedef struct BreakAspectStore BreakAspectStore;

typedef enum BreakAspectType {
    BREAK_ASPECT_U32 = 1,
    BREAK_ASPECT_I32 = 2,
    BREAK_ASPECT_F32 = 3,
    BREAK_ASPECT_BYTES = 4
} BreakAspectType;

typedef enum BreakAspectRecordKind {
    BREAK_ASPECT_BASELINE = 1,
    BREAK_ASPECT_DIRTY = 2,
    BREAK_ASPECT_DESTROY = 3,
    BREAK_ASPECT_DORMANT = 4
} BreakAspectRecordKind;

typedef struct BreakAspectSchema {
    u32 aspect_id;
    u32 version;
    BreakAspectType type;
    u32 byte_capacity;
} BreakAspectSchema;

typedef struct BreakAspectStoreConfig {
    u32 max_objects;
    u32 max_value_bytes;
    u32 max_packet_bytes;
} BreakAspectStoreConfig;

BreakRuntimeError break_aspect_store_create(const BreakAspectStoreConfig *config,
                                            BreakAspectStore **out);
void break_aspect_store_destroy(BreakAspectStore *store);
BreakRuntimeError break_aspect_schema_register(BreakAspectStore *store,
                                               const BreakAspectSchema *schema);
BreakRuntimeError break_aspect_object_create(BreakAspectStore *store,
                                             BreakOnlineHandle *out);
BreakRuntimeError break_aspect_object_adopt(BreakAspectStore *store,
                                            BreakOnlineHandle remote);
BreakRuntimeError break_aspect_object_destroy(BreakAspectStore *store,
                                              BreakOnlineHandle object);
u64 break_aspect_object_revision(const BreakAspectStore *store,
                                 BreakOnlineHandle object);
u64 break_aspect_active_mask(const BreakAspectStore *store,
                             BreakOnlineHandle object);
u64 break_aspect_schema_hash(const BreakAspectStore *store);
u64 break_aspect_aoi_id(BreakOnlineHandle object);

BreakRuntimeError break_aspect_set_u32(BreakAspectStore *store,
                                       BreakOnlineHandle object, u32 aspect_id, u32 value);
BreakRuntimeError break_aspect_set_i32(BreakAspectStore *store,
                                       BreakOnlineHandle object, u32 aspect_id, i32 value);
BreakRuntimeError break_aspect_set_f32(BreakAspectStore *store,
                                       BreakOnlineHandle object, u32 aspect_id, f32 value);
BreakRuntimeError break_aspect_set_bytes(BreakAspectStore *store,
                                         BreakOnlineHandle object, u32 aspect_id,
                                         const void *data, u32 size);
BreakRuntimeError break_aspect_get_u32(const BreakAspectStore *store,
                                       BreakOnlineHandle object, u32 aspect_id, u32 *out);
BreakRuntimeError break_aspect_get_i32(const BreakAspectStore *store,
                                       BreakOnlineHandle object, u32 aspect_id, i32 *out);
BreakRuntimeError break_aspect_get_f32(const BreakAspectStore *store,
                                       BreakOnlineHandle object, u32 aspect_id, f32 *out);
BreakRuntimeError break_aspect_get_bytes(const BreakAspectStore *store,
                                         BreakOnlineHandle object, u32 aspect_id,
                                         void *out, u32 capacity, u32 *out_size);

BreakRuntimeError break_aspect_encode(BreakAspectStore *store,
                                      BreakOnlineHandle object, u64 mask, u8 kind,
                                      u8 *out, usize capacity, usize *out_size);
BreakRuntimeError break_aspect_encode_with_epoch(BreakAspectStore *store,
                                      BreakOnlineHandle object, u64 mask, u8 kind,
                                      u64 record_epoch, u8 *out, usize capacity,
                                      usize *out_size);
BreakRuntimeError break_aspect_apply(BreakAspectStore *store,
                                     const u8 *packet, usize size);

#ifdef __cplusplus
}
#endif
