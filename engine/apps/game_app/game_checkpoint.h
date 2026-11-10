#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>

#define GAME_CHECKPOINT_VERSION 1u
#define GAME_CHECKPOINT_MAX_FILES 16u
#define GAME_CHECKPOINT_MAX_FILE_BYTES (64u << 20)
#define GAME_CHECKPOINT_MANIFEST_NAME "manifest.game"

typedef struct GameCheckpointFile {
    u32 kind;
    u64 size;
    u64 hash;
    char name[64];
} GameCheckpointFile;

typedef enum GameCheckpointCommitResult {
    GAME_CHECKPOINT_COMMIT_NOT_COMMITTED = 0,
    GAME_CHECKPOINT_COMMIT_DURABLE,
    GAME_CHECKPOINT_COMMIT_VISIBLE_DURABILITY_UNKNOWN
} GameCheckpointCommitResult;

/* OK with DURABLE means file and directory commits completed. OK with
 * VISIBLE_DURABILITY_UNKNOWN means the new generation is visible but a
 * post-rename directory sync failed; it is not a crash-durability guarantee.
 * Other errors leave out_result as NOT_COMMITTED. */
BreakRuntimeError game_checkpoint_write_manifest_ex(const char *directory,
                                                    const GameCheckpointFile *files,
                                                    u32 file_count, u64 generation,
                                                    GameCheckpointCommitResult *out_result);
/* Legacy logical-commit API: OK can also mean VISIBLE_DURABILITY_UNKNOWN;
 * callers requiring the durability distinction must use the _ex form. */
BreakRuntimeError game_checkpoint_write_manifest(const char *directory,
                                                 const GameCheckpointFile *files,
                                                 u32 file_count, u64 generation);
BreakRuntimeError game_checkpoint_probe(const char *directory);
u64 game_checkpoint_manifest_hash(const char *directory);
