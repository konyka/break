#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>

#define CRY_CHECKPOINT_VERSION 1u
#define CRY_CHECKPOINT_MAX_FILES 16u
#define CRY_CHECKPOINT_MAX_FILE_BYTES (64u << 20)
#define CRY_CHECKPOINT_MANIFEST_NAME "manifest.cry"

typedef struct CryCheckpointFile {
    u32 kind;
    u64 size;
    u64 hash;
    char name[64];
} CryCheckpointFile;

BreakRuntimeError cry_checkpoint_write_manifest(const char *directory,
                                                 const CryCheckpointFile *files,
                                                 u32 file_count, u64 generation);
BreakRuntimeError cry_checkpoint_probe(const char *directory);
u64 cry_checkpoint_manifest_hash(const char *directory);
