#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>

#define CORE_APP_CHECKPOINT_VERSION 1u
#define CORE_APP_CHECKPOINT_MAX_FILES 16u
#define CORE_APP_CHECKPOINT_MAX_FILE_BYTES (64u << 20)
#define CORE_APP_CHECKPOINT_MANIFEST_NAME "manifest.core"

typedef enum CoreAppCheckpointKind {
    CORE_APP_CHECKPOINT_SCENE = 1,
    CORE_APP_CHECKPOINT_FLOW,
    CORE_APP_CHECKPOINT_ACTORS,
    CORE_APP_CHECKPOINT_STATE,
    CORE_APP_CHECKPOINT_RUNTIME
} CoreAppCheckpointKind;

typedef struct CoreAppCheckpointFile {
    u32 kind;
    u64 size;
    u64 hash;
    char name[64];
} CoreAppCheckpointFile;

typedef enum CoreAppCheckpointCommitResult {
    CORE_APP_CHECKPOINT_COMMIT_NOT_COMMITTED = 0,
    CORE_APP_CHECKPOINT_COMMIT_DURABLE,
    CORE_APP_CHECKPOINT_COMMIT_VISIBLE_DURABILITY_UNKNOWN
} CoreAppCheckpointCommitResult;

/* OK with DURABLE means file and directory commits completed. OK with
 * VISIBLE_DURABILITY_UNKNOWN means the new generation is visible but a
 * post-rename directory sync failed; it is not a crash-durability guarantee.
 * Other errors leave out_result as NOT_COMMITTED. */
BreakRuntimeError core_app_checkpoint_write_manifest_ex(const char *directory,
                                                    const CoreAppCheckpointFile *files,
                                                    u32 file_count, u64 generation,
                                                    CoreAppCheckpointCommitResult *out_result);
/* Legacy logical-commit API: OK can also mean VISIBLE_DURABILITY_UNKNOWN;
 * callers requiring the durability distinction must use the _ex form. */
BreakRuntimeError core_app_checkpoint_write_manifest(const char *directory,
                                                 const CoreAppCheckpointFile *files,
                                                 u32 file_count, u64 generation);
BreakRuntimeError core_app_checkpoint_probe(const char *directory);
u64 core_app_checkpoint_manifest_hash(const char *directory);
/* Reads the manifest, probes every payload, and returns the single record of
 * `kind` with the manifest generation. A missing kind, a duplicate kind or any
 * payload that fails its size/hash check is rejected. */
BreakRuntimeError core_app_checkpoint_find(const char *directory, u32 kind,
                                           CoreAppCheckpointFile *out_file,
                                           u64 *out_generation);
