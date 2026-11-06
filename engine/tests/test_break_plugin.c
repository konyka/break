#include "test_framework.h"

#include <system/break_plugin.h>
#include <platform/platform_dynamic.h>
#include <crypto/break_crypto.h>
#include "fixtures/break_system_test_plugin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if (defined(__linux__) || defined(_WIN32)) && !defined(BREAK_SYSTEM_TEST_UNSUPPORTED)
#define BREAK_TEST_PLUGIN_SUPPORTED 1
#else
#define BREAK_TEST_PLUGIN_SUPPORTED 0
#endif

static bool hash_file(const char *path, u8 out[32]) {
    FILE *file = fopen(path, "rb");
    BreakCryptoSha256Ctx *ctx = NULL;
    u8 buffer[4096];
    bool ok = false;
    if (!file) return false;
    ctx = break_crypto_sha256_ctx_create();
    if (!ctx) {
        fclose(file);
        return false;
    }
    ok = true;
    for (;;) {
        usize count = fread(buffer, 1u, sizeof(buffer), file);
        if (count && !break_crypto_sha256_update(ctx, buffer, count)) ok = false;
        if (!ok || count < sizeof(buffer)) break;
    }
    if (ferror(file) || !break_crypto_sha256_final(ctx, out)) ok = false;
    break_crypto_sha256_ctx_destroy(ctx);
    if (fclose(file) != 0) ok = false;
    return ok;
}

static bool file_exists(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) return false;
    fclose(file);
    return true;
}

#if BREAK_TEST_PLUGIN_SUPPORTED
static bool copy_with_extra_byte(const char *source, const char *target) {
    FILE *in = fopen(source, "rb");
    FILE *out = fopen(target, "wb");
    u8 buffer[4096];
    bool ok = in && out;
    while (ok) {
        usize count = fread(buffer, 1u, sizeof(buffer), in);
        if (count && fwrite(buffer, 1u, count, out) != count) ok = false;
        if (count < sizeof(buffer)) break;
    }
    if (in && ferror(in)) ok = false;
    if (ok && fputc(0x5a, out) == EOF) ok = false;
    if (in && fclose(in) != 0) ok = false;
    if (out && fclose(out) != 0) ok = false;
    return ok;
}

TEST(real_library_load_and_reference_lifetime) {
    BreakSystemTestPluginLog log;
    BreakPluginManager *manager;
    BreakPluginHandle handle;
    u8 digest[32];
    memset(&log, 0, sizeof(log));
    ASSERT_TRUE(hash_file(BREAK_TEST_PLUGIN_A_PATH, digest));
    manager = break_plugin_create(2u, &log);
    ASSERT_NOT_NULL(manager);
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_A_PATH,
                                "system-test-a", digest, &handle), BREAK_PLUGIN_OK);
    ASSERT_EQ(handle.index, 0u);
    ASSERT_TRUE(handle.generation != 0u);
    ASSERT_EQ(log.count, 1u);
    ASSERT_EQ(log.events[0], 11);
    ASSERT_EQ(break_plugin_acquire(manager, handle), BREAK_PLUGIN_OK);
    ASSERT_EQ(break_plugin_unload(manager, handle), BREAK_PLUGIN_REJECTED);
    ASSERT_EQ(log.count, 1u);
    ASSERT_EQ(break_plugin_release(manager, handle), BREAK_PLUGIN_OK);
    ASSERT_EQ(break_plugin_release(manager, handle), BREAK_PLUGIN_REJECTED);
    ASSERT_EQ(break_plugin_unload(manager, handle), BREAK_PLUGIN_OK);
    ASSERT_EQ(log.count, 2u);
    ASSERT_EQ(log.events[1], -11);
    ASSERT_EQ(break_plugin_unload(manager, handle), BREAK_PLUGIN_STALE);
    ASSERT_EQ(break_plugin_acquire(manager, handle), BREAK_PLUGIN_STALE);
    ASSERT_EQ(break_plugin_release(manager, handle), BREAK_PLUGIN_STALE);
    ASSERT_EQ(break_plugin_destroy(manager), BREAK_PLUGIN_OK);
}

TEST(hash_allowlist_rejects_wrong_digest_and_tampered_file) {
    BreakSystemTestPluginLog log;
    BreakPluginManager *manager;
    BreakPluginHandle handle;
    u8 digest[32];
    u8 zero[32];
    char tampered[512];
    memset(&log, 0, sizeof(log));
    memset(zero, 0, sizeof(zero));
    ASSERT_TRUE(hash_file(BREAK_TEST_PLUGIN_A_PATH, digest));
    manager = break_plugin_create(2u, &log);
    ASSERT_NOT_NULL(manager);
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_A_PATH,
                                "system-test-a", zero, &handle), BREAK_PLUGIN_REJECTED);
    ASSERT_EQ(handle.generation, 0u);
    ASSERT_EQ(log.count, 0u);
#if defined(_WIN32)
    test_tmp(tampered, sizeof(tampered), "system_plugin_tampered.dll");
#else
    test_tmp(tampered, sizeof(tampered), "system_plugin_tampered.so");
#endif
    ASSERT_TRUE(copy_with_extra_byte(BREAK_TEST_PLUGIN_A_PATH, tampered));
    ASSERT_EQ(break_plugin_load(manager, tampered, "system-test-a", digest, &handle),
              BREAK_PLUGIN_REJECTED);
    ASSERT_EQ(log.count, 0u);
    ASSERT_EQ(break_plugin_load(manager, "/definitely/not/a/plugin.so",
                                "system-test-a", digest, &handle), BREAK_PLUGIN_FAILED);
    ASSERT_EQ(break_plugin_destroy(manager), BREAK_PLUGIN_OK);
    remove(tampered);
}

static bool write_oversized_file(const char *path) {
    FILE *file = fopen(path, "wb");
    bool ok = file != NULL;
    if (ok && fseek(file, (long)PLATFORM_DYNAMIC_MAX_FILE_BYTES, SEEK_SET) != 0) ok = false;
    if (ok && fputc(0x5a, file) == EOF) ok = false;
    if (file && fclose(file) != 0) ok = false;
    return ok;
}

TEST(oversized_file_is_overload_not_io_failure) {
    BreakSystemTestPluginLog log;
    BreakPluginManager *manager;
    BreakPluginHandle handle;
    u8 digest[32] = {0};
    char path[512];
    memset(&log, 0, sizeof(log));
    test_tmp(path, sizeof(path), "system_plugin_oversized.so");
    ASSERT_TRUE(write_oversized_file(path));
    manager = break_plugin_create(1u, &log);
    ASSERT_NOT_NULL(manager);
    ASSERT_EQ(break_plugin_load(manager, path, "system-test-a", digest, &handle),
              BREAK_PLUGIN_OVERLOAD);
    ASSERT_EQ(handle.index, 0u);
    ASSERT_EQ(handle.generation, 0u);
    ASSERT_EQ(log.count, 0u);
    ASSERT_EQ(break_plugin_load(manager, "/definitely/not/a/plugin.so",
                                "system-test-a", digest, &handle), BREAK_PLUGIN_FAILED);
    ASSERT_EQ(break_plugin_destroy(manager), BREAK_PLUGIN_OK);
    remove(path);
}

TEST(abi_build_entry_and_registration_fail_closed) {
    BreakSystemTestPluginLog log;
    BreakPluginManager *manager;
    BreakPluginHandle handle;
    u8 digest[32];
    memset(&log, 0, sizeof(log));
    manager = break_plugin_create(2u, &log);
    ASSERT_NOT_NULL(manager);
    ASSERT_TRUE(hash_file(BREAK_TEST_PLUGIN_BAD_ABI_PATH, digest));
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_BAD_ABI_PATH,
                                "system-test-bad-abi", digest, &handle), BREAK_PLUGIN_REJECTED);
    ASSERT_EQ(log.count, 0u);
    ASSERT_TRUE(hash_file(BREAK_TEST_PLUGIN_A_PATH, digest));
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_A_PATH,
                                "wrong-build", digest, &handle), BREAK_PLUGIN_REJECTED);
    ASSERT_EQ(log.count, 0u);
    ASSERT_TRUE(hash_file(BREAK_TEST_PLUGIN_NO_ENTRY_PATH, digest));
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_NO_ENTRY_PATH,
                                "system-test-no-entry", digest, &handle), BREAK_PLUGIN_FAILED);
    ASSERT_EQ(log.count, 0u);
    ASSERT_TRUE(hash_file(BREAK_TEST_PLUGIN_REGISTER_FAIL_PATH, digest));
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_REGISTER_FAIL_PATH,
                                "system-test-register-fail", digest, &handle), BREAK_PLUGIN_FAILED);
    ASSERT_EQ(handle.generation, 0u);
    ASSERT_EQ(log.count, 1u);
    ASSERT_EQ(log.events[0], 44);
    ASSERT_TRUE(hash_file(BREAK_TEST_PLUGIN_A_PATH, digest));
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_A_PATH,
                                "system-test-a", digest, &handle), BREAK_PLUGIN_OK);
    ASSERT_EQ(log.count, 2u);
    ASSERT_EQ(log.events[1], 11);
    ASSERT_EQ(break_plugin_destroy(manager), BREAK_PLUGIN_OK);
    ASSERT_EQ(log.count, 3u);
    ASSERT_EQ(log.events[2], -11);
}

TEST(unload_all_is_reverse_load_order) {
    BreakSystemTestPluginLog log;
    BreakPluginManager *manager;
    BreakPluginHandle a;
    BreakPluginHandle b;
    u8 digest[32];
    memset(&log, 0, sizeof(log));
    manager = break_plugin_create(2u, &log);
    ASSERT_NOT_NULL(manager);
    ASSERT_TRUE(hash_file(BREAK_TEST_PLUGIN_A_PATH, digest));
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_A_PATH,
                                "system-test-a", digest, &a), BREAK_PLUGIN_OK);
    ASSERT_TRUE(hash_file(BREAK_TEST_PLUGIN_B_PATH, digest));
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_B_PATH,
                                "system-test-b", digest, &b), BREAK_PLUGIN_OK);
    ASSERT_EQ(log.count, 2u);
    ASSERT_EQ(log.events[0], 11);
    ASSERT_EQ(log.events[1], 22);
    ASSERT_EQ(break_plugin_unload_all(manager), BREAK_PLUGIN_OK);
    ASSERT_EQ(log.count, 4u);
    ASSERT_EQ(log.events[2], -22);
    ASSERT_EQ(log.events[3], -11);
    ASSERT_EQ(break_plugin_unload(manager, a), BREAK_PLUGIN_STALE);
    ASSERT_EQ(break_plugin_unload(manager, b), BREAK_PLUGIN_STALE);
    ASSERT_EQ(break_plugin_unload_all(manager), BREAK_PLUGIN_OK);
    ASSERT_EQ(log.count, 4u);
    ASSERT_EQ(break_plugin_destroy(manager), BREAK_PLUGIN_OK);
}

TEST(unload_all_preflights_every_reference) {
    BreakSystemTestPluginLog log;
    BreakPluginManager *manager;
    BreakPluginHandle a;
    BreakPluginHandle b;
    u8 digest[32];
    memset(&log, 0, sizeof(log));
    manager = break_plugin_create(2u, &log);
    ASSERT_NOT_NULL(manager);
    ASSERT_TRUE(hash_file(BREAK_TEST_PLUGIN_A_PATH, digest));
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_A_PATH,
                                "system-test-a", digest, &a), BREAK_PLUGIN_OK);
    ASSERT_TRUE(hash_file(BREAK_TEST_PLUGIN_B_PATH, digest));
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_B_PATH,
                                "system-test-b", digest, &b), BREAK_PLUGIN_OK);
    ASSERT_EQ(break_plugin_acquire(manager, a), BREAK_PLUGIN_OK);
    ASSERT_EQ(break_plugin_unload_all(manager), BREAK_PLUGIN_REJECTED);
    ASSERT_EQ(log.count, 2u);
    ASSERT_EQ(break_plugin_release(manager, a), BREAK_PLUGIN_OK);
    ASSERT_EQ(break_plugin_unload_all(manager), BREAK_PLUGIN_OK);
    ASSERT_EQ(log.events[2], -22);
    ASSERT_EQ(log.events[3], -11);
    ASSERT_EQ(break_plugin_destroy(manager), BREAK_PLUGIN_OK);
}

TEST(capacity_duplicates_and_generation_reuse_are_deterministic) {
    BreakSystemTestPluginLog log;
    BreakPluginManager *manager;
    BreakPluginHandle a;
    BreakPluginHandle b;
    u8 digest[32];
    memset(&log, 0, sizeof(log));
    manager = break_plugin_create(1u, &log);
    ASSERT_NOT_NULL(manager);
    ASSERT_TRUE(hash_file(BREAK_TEST_PLUGIN_A_PATH, digest));
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_A_PATH,
                                "system-test-a", digest, &a), BREAK_PLUGIN_OK);
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_A_PATH,
                                "system-test-a", digest, &b), BREAK_PLUGIN_REJECTED);
    ASSERT_TRUE(hash_file(BREAK_TEST_PLUGIN_B_PATH, digest));
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_B_PATH,
                                "system-test-b", digest, &b), BREAK_PLUGIN_OVERLOAD);
    ASSERT_EQ(log.count, 1u);
    ASSERT_EQ(break_plugin_unload(manager, a), BREAK_PLUGIN_OK);
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_B_PATH,
                                "system-test-b", digest, &b), BREAK_PLUGIN_OK);
    ASSERT_EQ(b.index, a.index);
    ASSERT_TRUE(b.generation != a.generation);
    ASSERT_EQ(break_plugin_unload(manager, a), BREAK_PLUGIN_STALE);
    ASSERT_EQ(break_plugin_destroy(manager), BREAK_PLUGIN_OK);
}

TEST(destroy_refuses_referenced_plugins) {
    BreakSystemTestPluginLog log;
    BreakPluginManager *manager;
    BreakPluginHandle handle;
    u8 digest[32];
    memset(&log, 0, sizeof(log));
    ASSERT_TRUE(hash_file(BREAK_TEST_PLUGIN_A_PATH, digest));
    manager = break_plugin_create(1u, &log);
    ASSERT_NOT_NULL(manager);
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_A_PATH,
                                "system-test-a", digest, &handle), BREAK_PLUGIN_OK);
    ASSERT_EQ(break_plugin_acquire(manager, handle), BREAK_PLUGIN_OK);
    ASSERT_EQ(break_plugin_destroy(manager), BREAK_PLUGIN_REJECTED);
    ASSERT_EQ(log.count, 1u);
    ASSERT_EQ(break_plugin_release(manager, handle), BREAK_PLUGIN_OK);
    ASSERT_EQ(break_plugin_destroy(manager), BREAK_PLUGIN_OK);
    ASSERT_EQ(log.count, 2u);
    ASSERT_EQ(log.events[1], -11);
}

TEST(manager_arguments_and_capacity_are_validated) {
    BreakPluginHandle handle = { 9u, 9u };
    BreakPluginManager *manager = break_plugin_create(1u, NULL);
    u8 digest[32] = {0};
    ASSERT_TRUE(break_plugin_create(0u, NULL) == NULL);
    ASSERT_TRUE(break_plugin_create(BREAK_PLUGIN_HARD_MAX + 1u, NULL) == NULL);
    ASSERT_NOT_NULL(manager);
    ASSERT_EQ(break_plugin_load(manager, NULL, "x", digest, &handle), BREAK_PLUGIN_INVALID);
    ASSERT_EQ(handle.index, 0u);
    ASSERT_EQ(handle.generation, 0u);
    ASSERT_EQ(break_plugin_acquire(manager, handle), BREAK_PLUGIN_STALE);
    ASSERT_EQ(break_plugin_destroy(manager), BREAK_PLUGIN_OK);
    ASSERT_EQ(break_plugin_destroy(NULL), BREAK_PLUGIN_INVALID);
}

TEST(exhausted_generation_retires_slot_without_reviving_oldest_handle) {
    BreakSystemTestPluginLog log;
    BreakPluginManager *manager;
    BreakPluginHandle oldest;
    BreakPluginHandle handle;
    u8 digest_a[32];
    u8 digest_b[32];
    memset(&log, 0, sizeof(log));
    ASSERT_TRUE(hash_file(BREAK_TEST_PLUGIN_A_PATH, digest_a));
    ASSERT_TRUE(hash_file(BREAK_TEST_PLUGIN_B_PATH, digest_b));
    manager = break_plugin_create(1u, &log);
    ASSERT_NOT_NULL(manager);
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_A_PATH,
                                "system-test-a", digest_a, &oldest), BREAK_PLUGIN_OK);
    break_plugin_test_set_generation(manager, oldest.index, UINT32_MAX - 1u);
    handle = oldest;
    handle.generation = UINT32_MAX - 1u;
    ASSERT_EQ(break_plugin_unload(manager, handle), BREAK_PLUGIN_OK);
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_B_PATH,
                                "system-test-b", digest_b, &handle), BREAK_PLUGIN_OK);
    ASSERT_EQ(handle.generation, UINT32_MAX);
    ASSERT_EQ(break_plugin_unload(manager, handle), BREAK_PLUGIN_OK);
    ASSERT_EQ(break_plugin_load(manager, BREAK_TEST_PLUGIN_A_PATH,
                                "system-test-a", digest_a, &handle), BREAK_PLUGIN_OVERLOAD);
    ASSERT_EQ(break_plugin_acquire(manager, oldest), BREAK_PLUGIN_STALE);
    ASSERT_EQ(break_plugin_destroy(manager), BREAK_PLUGIN_OK);
}

typedef struct BreakTestRace {
    const char *target;
    const char *attacker;
    bool called;
    bool replaced;
} BreakTestRace;

static void replace_verified_path(void *user) {
    BreakTestRace *race = (BreakTestRace *)user;
    race->called = true;
#if defined(_WIN32)
    race->replaced = remove(race->target) == 0 && rename(race->attacker, race->target) == 0;
#else
    race->replaced = rename(race->attacker, race->target) == 0;
#endif
}

TEST(path_replacement_never_runs_unapproved_constructor) {
    BreakSystemTestPluginLog log;
    BreakPluginManager *manager;
    BreakPluginHandle handle;
    BreakTestRace race;
    BreakPluginStatus status;
    u8 digest[32];
    char approved[512];
    char attacker[512];
    memset(&log, 0, sizeof(log));
    memset(&race, 0, sizeof(race));
    test_tmp(approved, sizeof(approved), "system_verified_race.so");
    test_tmp(attacker, sizeof(attacker), "system_attacker_race.so");
    ASSERT_TRUE(copy_with_extra_byte(BREAK_TEST_PLUGIN_A_PATH, approved));
    ASSERT_TRUE(copy_with_extra_byte(BREAK_TEST_PLUGIN_ATTACKER_PATH, attacker));
    ASSERT_TRUE(hash_file(approved, digest));
    remove(BREAK_TEST_ATTACKER_MARK_PATH);
    race.target = approved;
    race.attacker = attacker;
    manager = break_plugin_create(1u, &log);
    ASSERT_NOT_NULL(manager);
    platform_dynamic_test_set_before_open(replace_verified_path, &race);
    status = break_plugin_load(manager, approved, "system-test-a", digest, &handle);
    platform_dynamic_test_set_before_open(NULL, NULL);
    ASSERT_TRUE(race.called);
#if !defined(_WIN32)
    ASSERT_TRUE(race.replaced);
#endif
    ASSERT_EQ(status, BREAK_PLUGIN_OK);
    ASSERT_FALSE(file_exists(BREAK_TEST_ATTACKER_MARK_PATH));
    ASSERT_EQ(log.count, 1u);
    ASSERT_EQ(log.events[0], 11);
    ASSERT_EQ(break_plugin_destroy(manager), BREAK_PLUGIN_OK);
    remove(approved);
    remove(attacker);
    remove(BREAK_TEST_ATTACKER_MARK_PATH);
}

#else
TEST(unsupported_platform_fails_closed_without_constructor_side_effect) {
    BreakSystemTestPluginLog log;
    BreakPluginManager *manager;
    BreakPluginHandle handle = { 9u, 9u };
    BreakPluginStatus status;
    u8 digest[32];
    memset(&log, 0, sizeof(log));
    ASSERT_TRUE(hash_file(BREAK_TEST_PLUGIN_ATTACKER_PATH, digest));
    remove(BREAK_TEST_ATTACKER_MARK_PATH);
    manager = break_plugin_create(1u, &log);
    ASSERT_NOT_NULL(manager);
    status = break_plugin_load(manager, BREAK_TEST_PLUGIN_ATTACKER_PATH,
                               "system-test-a", digest, &handle);
    ASSERT_FALSE(file_exists(BREAK_TEST_ATTACKER_MARK_PATH));
    ASSERT_EQ(status, BREAK_PLUGIN_FAILED);
    ASSERT_EQ(handle.index, 0u);
    ASSERT_EQ(handle.generation, 0u);
    ASSERT_EQ(log.count, 0u);
    ASSERT_EQ(break_plugin_destroy(manager), BREAK_PLUGIN_OK);
    remove(BREAK_TEST_ATTACKER_MARK_PATH);
}
#endif

TEST_MAIN_BEGIN()
#if BREAK_TEST_PLUGIN_SUPPORTED
    RUN_TEST(real_library_load_and_reference_lifetime);
    RUN_TEST(hash_allowlist_rejects_wrong_digest_and_tampered_file);
    RUN_TEST(oversized_file_is_overload_not_io_failure);
    RUN_TEST(abi_build_entry_and_registration_fail_closed);
    RUN_TEST(unload_all_is_reverse_load_order);
    RUN_TEST(unload_all_preflights_every_reference);
    RUN_TEST(capacity_duplicates_and_generation_reuse_are_deterministic);
    RUN_TEST(destroy_refuses_referenced_plugins);
    RUN_TEST(manager_arguments_and_capacity_are_validated);
    RUN_TEST(exhausted_generation_retires_slot_without_reviving_oldest_handle);
    RUN_TEST(path_replacement_never_runs_unapproved_constructor);
#else
    RUN_TEST(unsupported_platform_fails_closed_without_constructor_side_effect);
#endif
TEST_MAIN_END()
