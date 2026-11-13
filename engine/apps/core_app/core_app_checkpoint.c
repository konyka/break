#include "core_app_checkpoint.h"

#include <core/log.h>
#include <platform/platform_fs.h>

#include <stdio.h>
#include <string.h>

#define CORE_APP_CHECKPOINT_HEADER_BYTES 40u
#define CORE_APP_CHECKPOINT_RECORD_BYTES 88u
#define CORE_APP_CHECKPOINT_MANIFEST_MAX_BYTES \
    (CORE_APP_CHECKPOINT_HEADER_BYTES + CORE_APP_CHECKPOINT_MAX_FILES * CORE_APP_CHECKPOINT_RECORD_BYTES)

static const u8 k_magic[8] = {'C', 'O', 'R', 'E', 'C', 'K', 'P', 'T'};

typedef struct {
    u64 generation;
    u32 file_count;
    CoreAppCheckpointFile files[CORE_APP_CHECKPOINT_MAX_FILES];
    u8 raw[CORE_APP_CHECKPOINT_MANIFEST_MAX_BYTES];
    usize raw_size;
} CoreAppCheckpointManifest;

static void put32(u8 *p, u32 value) {
    p[0] = (u8)value;
    p[1] = (u8)(value >> 8);
    p[2] = (u8)(value >> 16);
    p[3] = (u8)(value >> 24);
}

static void put64(u8 *p, u64 value) {
    put32(p, (u32)value);
    put32(p + 4, (u32)(value >> 32));
}

static u32 get32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) |
           ((u32)p[3] << 24);
}

static u64 get64(const u8 *p) {
    return (u64)get32(p) | ((u64)get32(p + 4) << 32);
}

static u64 hash_update(u64 hash, const u8 *bytes, usize size) {
    for (usize i = 0; i < size; ++i) {
        hash ^= bytes[i];
        hash *= 1099511628211ULL;
    }
    return hash;
}

static bool join_path(char out[PLATFORM_FS_PATH_CAPACITY], const char *directory,
                      const char *name) {
    if (!directory || directory[0] == '\0' || !name) return false;
    int written = snprintf(out, PLATFORM_FS_PATH_CAPACITY, "%s/%s", directory, name);
    return written > 0 && (usize)written < PLATFORM_FS_PATH_CAPACITY;
}

static bool name_equal(const char *a, const char *b) {
    usize i = 0;
    for (;;) {
        unsigned char ac = (unsigned char)a[i];
        unsigned char bc = (unsigned char)b[i];
        if (ac >= (unsigned char)'A' && ac <= (unsigned char)'Z')
            ac = (unsigned char)(ac + ((unsigned char)'a' - (unsigned char)'A'));
        if (bc >= (unsigned char)'A' && bc <= (unsigned char)'Z')
            bc = (unsigned char)(bc + ((unsigned char)'a' - (unsigned char)'A'));
        if (ac != bc) return false;
        if (ac == 0u) return true;
        ++i;
    }
}

static bool valid_basename(const char name[64]) {
    if (!name) return false;
    usize length = 0;
    while (length < 64u && name[length] != '\0') ++length;
    if (length == 0u || length == 64u || name[length - 1u] == '.' ||
        name_equal(name, CORE_APP_CHECKPOINT_MANIFEST_NAME))
        return false;
    for (usize i = 0; i < length; ++i) {
        unsigned char ch = (unsigned char)name[i];
        bool alpha_numeric = (ch >= (unsigned char)'a' && ch <= (unsigned char)'z') ||
                             (ch >= (unsigned char)'A' && ch <= (unsigned char)'Z') ||
                             (ch >= (unsigned char)'0' && ch <= (unsigned char)'9');
        if (!alpha_numeric && ch != (unsigned char)'_' && ch != (unsigned char)'.' &&
            ch != (unsigned char)'-')
            return false;
        if (ch == (unsigned char)'.' && i > 0u && name[i - 1u] == '.') return false;
    }
    return true;
}

static BreakRuntimeError validate_file(const CoreAppCheckpointFile *file) {
    if (!file) return BREAK_RUNTIME_INVALID;
    if (!memchr(file->name, '\0', sizeof(file->name))) return BREAK_RUNTIME_OVERLOAD;
    if (file->kind == 0u || !valid_basename(file->name))
        return BREAK_RUNTIME_INVALID;
    if (file->size > (u64)CORE_APP_CHECKPOINT_MAX_FILE_BYTES)
        return BREAK_RUNTIME_OVERLOAD;
    return BREAK_RUNTIME_OK;
}

static bool duplicate_name(const CoreAppCheckpointFile *files, u32 count,
                           const char name[64]) {
    for (u32 i = 0; i < count; ++i) {
        if (name_equal(files[i].name, name)) return true;
    }
    return false;
}

static BreakRuntimeError parse_manifest(CoreAppCheckpointManifest *manifest) {
    const u8 *bytes = manifest->raw;
    usize size = manifest->raw_size;
    if (size < CORE_APP_CHECKPOINT_HEADER_BYTES) return BREAK_RUNTIME_INVALID;
    if (memcmp(bytes, k_magic, sizeof(k_magic)) != 0 ||
        get32(bytes + 8) != CORE_APP_CHECKPOINT_VERSION ||
        get32(bytes + 12) != CORE_APP_CHECKPOINT_HEADER_BYTES ||
        get64(bytes + 16) != (u64)size || get32(bytes + 36) != 0u)
        return BREAK_RUNTIME_INVALID;
    u64 generation = get64(bytes + 24);
    u32 count = get32(bytes + 32);
    if (generation == 0u || count == 0u) return BREAK_RUNTIME_INVALID;
    if (count > CORE_APP_CHECKPOINT_MAX_FILES) return BREAK_RUNTIME_OVERLOAD;
    usize expected = CORE_APP_CHECKPOINT_HEADER_BYTES + (usize)count * CORE_APP_CHECKPOINT_RECORD_BYTES;
    if (expected != size) return BREAK_RUNTIME_INVALID;
    manifest->generation = generation;
    manifest->file_count = count;
    for (u32 i = 0; i < count; ++i) {
        const u8 *record = bytes + CORE_APP_CHECKPOINT_HEADER_BYTES + (usize)i * CORE_APP_CHECKPOINT_RECORD_BYTES;
        CoreAppCheckpointFile *file = &manifest->files[i];
        memset(file, 0, sizeof(*file));
        file->kind = get32(record);
        u32 name_length = get32(record + 4);
        file->size = get64(record + 8);
        file->hash = get64(record + 16);
        if (name_length >= 64u) return BREAK_RUNTIME_OVERLOAD;
        if (name_length == 0u) return BREAK_RUNTIME_INVALID;
        for (u32 n = 0; n < 64u; ++n) {
            u8 value = record[24u + n];
            if (n > name_length && value != 0u) return BREAK_RUNTIME_INVALID;
            file->name[n] = (char)value;
        }
        if (record[24u + name_length] != 0u ||
            strlen(file->name) != (usize)name_length)
            return BREAK_RUNTIME_INVALID;
        BreakRuntimeError valid = validate_file(file);
        if (valid != BREAK_RUNTIME_OK) return valid;
        if (duplicate_name(manifest->files, i, file->name)) return BREAK_RUNTIME_INVALID;
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError read_manifest(const char *directory, CoreAppCheckpointManifest *manifest) {
    char path[PLATFORM_FS_PATH_CAPACITY];
    memset(manifest, 0, sizeof(*manifest));
    if (!join_path(path, directory, CORE_APP_CHECKPOINT_MANIFEST_NAME))
        return BREAK_RUNTIME_OVERLOAD;
    u64 size = 0;
    if (!platform_file_size(path, &size)) return BREAK_RUNTIME_FAILED;
    if (size > (u64)sizeof(manifest->raw)) return BREAK_RUNTIME_OVERLOAD;
    if (size < (u64)CORE_APP_CHECKPOINT_HEADER_BYTES) return BREAK_RUNTIME_INVALID;
    FILE *fp = fopen(path, "rb");
    if (!fp) return BREAK_RUNTIME_FAILED;
    usize got = fread(manifest->raw, 1, (usize)size, fp);
    int extra = fgetc(fp);
    bool read_ok = got == (usize)size && extra == EOF;
    if (fclose(fp) != 0) read_ok = false;
    if (!read_ok) {
        memset(manifest->raw, 0, sizeof(manifest->raw));
        return BREAK_RUNTIME_INVALID;
    }
    manifest->raw_size = (usize)size;
    return parse_manifest(manifest);
}

static BreakRuntimeError probe_payload(const char *directory,
                                       const CoreAppCheckpointFile *file) {
    char path[PLATFORM_FS_PATH_CAPACITY];
    if (!join_path(path, directory, file->name)) return BREAK_RUNTIME_OVERLOAD;
    u64 disk_size = 0;
    if (!platform_file_size(path, &disk_size) || disk_size != file->size)
        return BREAK_RUNTIME_INVALID;
    FILE *fp = fopen(path, "rb");
    if (!fp) return BREAK_RUNTIME_INVALID;
    u64 remaining = file->size;
    u64 hash = 14695981039346656037ULL;
    bool ok = true;
    while (remaining > 0u) {
        u8 buffer[4096];
        usize wanted = remaining > (u64)sizeof(buffer) ? sizeof(buffer)
                                                       : (usize)remaining;
        usize got = fread(buffer, 1, wanted, fp);
        if (got != wanted) {
            ok = false;
            break;
        }
        hash = hash_update(hash, buffer, got);
        remaining -= (u64)got;
    }
    if (ok && fgetc(fp) != EOF) ok = false;
    if (fclose(fp) != 0) ok = false;
    if (!ok || remaining != 0u || hash != file->hash) return BREAK_RUNTIME_INVALID;
    return BREAK_RUNTIME_OK;
}

static void build_manifest(const CoreAppCheckpointFile *files, u32 file_count,
                           u64 generation, u8 out[CORE_APP_CHECKPOINT_MANIFEST_MAX_BYTES],
                           usize *out_size) {
    usize size = CORE_APP_CHECKPOINT_HEADER_BYTES + (usize)file_count * CORE_APP_CHECKPOINT_RECORD_BYTES;
    memset(out, 0, size);
    memcpy(out, k_magic, sizeof(k_magic));
    put32(out + 8, CORE_APP_CHECKPOINT_VERSION);
    put32(out + 12, CORE_APP_CHECKPOINT_HEADER_BYTES);
    put64(out + 16, (u64)size);
    put64(out + 24, generation);
    put32(out + 32, file_count);
    for (u32 i = 0; i < file_count; ++i) {
        u8 *record = out + CORE_APP_CHECKPOINT_HEADER_BYTES + (usize)i * CORE_APP_CHECKPOINT_RECORD_BYTES;
        usize name_length = strlen(files[i].name);
        put32(record, files[i].kind);
        put32(record + 4, (u32)name_length);
        put64(record + 8, files[i].size);
        put64(record + 16, files[i].hash);
        memcpy(record + 24, files[i].name, name_length);
    }
    *out_size = size;
}

static void remove_new_payloads(const char *directory,
                                const CoreAppCheckpointFile *files, u32 file_count,
                                const CoreAppCheckpointManifest *old, bool old_valid) {
    for (u32 i = 0; i < file_count; ++i) {
        if (!valid_basename(files[i].name)) continue;
        if (old_valid && duplicate_name(old->files, old->file_count, files[i].name))
            continue;
        char path[PLATFORM_FS_PATH_CAPACITY];
        if (join_path(path, directory, files[i].name)) (void)remove(path);
    }
}

BreakRuntimeError core_app_checkpoint_write_manifest_ex(const char *directory,
                                                    const CoreAppCheckpointFile *files,
                                                    u32 file_count, u64 generation,
                                                    CoreAppCheckpointCommitResult *out_result) {
    if (!out_result) return BREAK_RUNTIME_INVALID;
    *out_result = CORE_APP_CHECKPOINT_COMMIT_NOT_COMMITTED;
    if (!directory || directory[0] == '\0' || !files || file_count == 0u ||
        generation == 0u)
        return BREAK_RUNTIME_INVALID;
    if (file_count > CORE_APP_CHECKPOINT_MAX_FILES) return BREAK_RUNTIME_OVERLOAD;

    char manifest_path[PLATFORM_FS_PATH_CAPACITY];
    if (!join_path(manifest_path, directory, CORE_APP_CHECKPOINT_MANIFEST_NAME))
        return BREAK_RUNTIME_OVERLOAD;
    u64 old_manifest_size = 0;
    bool old_exists = platform_file_size(manifest_path, &old_manifest_size);
    CoreAppCheckpointManifest old;
    BreakRuntimeError old_read = read_manifest(directory, &old);
    bool old_valid = old_read == BREAK_RUNTIME_OK;
    bool cleanup_safe = !old_exists || old_valid;
    BreakRuntimeError result = BREAK_RUNTIME_OK;

    for (u32 i = 0; i < file_count; ++i) {
        result = validate_file(&files[i]);
        if (result != BREAK_RUNTIME_OK) goto fail;
        if (duplicate_name(files, i, files[i].name) ||
            (old_valid && duplicate_name(old.files, old.file_count, files[i].name))) {
            result = BREAK_RUNTIME_INVALID;
            goto fail;
        }
    }
    for (u32 i = 0; i < file_count; ++i) {
        result = probe_payload(directory, &files[i]);
        if (result != BREAK_RUNTIME_OK) goto fail;
    }

    u8 bytes[CORE_APP_CHECKPOINT_MANIFEST_MAX_BYTES];
    usize size = 0;
    build_manifest(files, file_count, generation, bytes, &size);
    PlatformAtomicWriter *writer = platform_atomic_writer_open(manifest_path);
    if (!writer) {
        result = BREAK_RUNTIME_FAILED;
        goto fail;
    }
    if (!platform_atomic_writer_write(writer, bytes, size)) {
        platform_atomic_writer_abort(writer);
        result = BREAK_RUNTIME_FAILED;
        goto fail;
    }
    PlatformAtomicCommitResult committed = platform_atomic_writer_commit_status(writer);
    if (committed == PLATFORM_ATOMIC_RENAMED_DURABILITY_UNKNOWN) {
        *out_result = CORE_APP_CHECKPOINT_COMMIT_VISIBLE_DURABILITY_UNKNOWN;
        LOG_WARN("checkpoint: generation %llu is visible; directory fsync failed, "
                 "durability unknown", (unsigned long long)generation);
        return BREAK_RUNTIME_OK;
    }
    if (committed == PLATFORM_ATOMIC_SUCCESS_DURABLE) {
        *out_result = CORE_APP_CHECKPOINT_COMMIT_DURABLE;
        return BREAK_RUNTIME_OK;
    }
    result = BREAK_RUNTIME_FAILED;
    goto fail;

fail:
    if (cleanup_safe) remove_new_payloads(directory, files, file_count, &old, old_valid);
    return result;
}

BreakRuntimeError core_app_checkpoint_write_manifest(const char *directory,
                                                 const CoreAppCheckpointFile *files,
                                                 u32 file_count, u64 generation) {
    CoreAppCheckpointCommitResult commit_result;
    return core_app_checkpoint_write_manifest_ex(directory, files, file_count, generation,
                                            &commit_result);
}

BreakRuntimeError core_app_checkpoint_probe(const char *directory) {
    if (!directory || directory[0] == '\0') return BREAK_RUNTIME_INVALID;
    CoreAppCheckpointManifest manifest;
    BreakRuntimeError result = read_manifest(directory, &manifest);
    if (result != BREAK_RUNTIME_OK) return result;
    for (u32 i = 0; i < manifest.file_count; ++i) {
        result = probe_payload(directory, &manifest.files[i]);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_checkpoint_find(const char *directory, u32 kind,
                                           CoreAppCheckpointFile *out_file,
                                           u64 *out_generation) {
    if (!directory || directory[0] == '\0' || !out_file || !out_generation || kind == 0u)
        return BREAK_RUNTIME_INVALID;
    CoreAppCheckpointManifest manifest;
    BreakRuntimeError result = read_manifest(directory, &manifest);
    if (result != BREAK_RUNTIME_OK) return result;
    const CoreAppCheckpointFile *found = NULL;
    for (u32 i = 0; i < manifest.file_count; ++i) {
        result = probe_payload(directory, &manifest.files[i]);
        if (result != BREAK_RUNTIME_OK) return result;
        if (manifest.files[i].kind != kind) continue;
        if (found) return BREAK_RUNTIME_INVALID;
        found = &manifest.files[i];
    }
    if (!found) return BREAK_RUNTIME_INVALID;
    *out_file = *found;
    *out_generation = manifest.generation;
    return BREAK_RUNTIME_OK;
}

u64 core_app_checkpoint_manifest_hash(const char *directory) {
    char path[PLATFORM_FS_PATH_CAPACITY];
    if (!join_path(path, directory, CORE_APP_CHECKPOINT_MANIFEST_NAME)) return 0u;
    u64 size = 0;
    if (!platform_file_size(path, &size) || size == 0u ||
        size > (u64)CORE_APP_CHECKPOINT_MANIFEST_MAX_BYTES)
        return 0u;
    u8 bytes[CORE_APP_CHECKPOINT_MANIFEST_MAX_BYTES];
    FILE *fp = fopen(path, "rb");
    if (!fp) return 0u;
    usize got = fread(bytes, 1, (usize)size, fp);
    int extra = fgetc(fp);
    bool ok = got == (usize)size && extra == EOF;
    if (fclose(fp) != 0) ok = false;
    if (!ok) return 0u;
    return hash_update(14695981039346656037ULL, bytes, (usize)size);
}
