#include "test_framework.h"

#include <system/break_cvar.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static u32 callback_count;
static char callback_last[BREAK_CVAR_NAME_CAPACITY];
static BreakCVarRegistry *callback_registry;

static void changed(const char *name, void *user) {
    u32 *counter = (u32 *)user;
    (*counter)++;
    callback_count++;
    snprintf(callback_last, sizeof(callback_last), "%s", name);
    if (callback_registry) {
        BreakCVarValue value = { .integer = 1 };
        ASSERT_EQ(break_cvar_set(callback_registry, name, value, true),
                  BREAK_CVAR_REJECTED);
    }
}

static BreakCVarDesc desc(const char *name, BreakCVarType type) {
    BreakCVarDesc d;
    memset(&d, 0, sizeof(d));
    d.name = name;
    d.type = type;
    d.min_number = -1000.0;
    d.max_number = 1000.0;
    d.min_integer = -1000;
    d.max_integer = 1000;
    return d;
}

static BreakCVarStatus add_int(BreakCVarRegistry *r, const char *name,
                               i64 initial, i64 min, i64 max, u32 flags,
                               u32 *counter) {
    BreakCVarDesc d = desc(name, BREAK_CVAR_INT);
    d.default_value.integer = initial;
    d.min_integer = min;
    d.max_integer = max;
    d.flags = flags;
    if (counter) {
        d.changed = changed;
        d.changed_user = counter;
    }
    return break_cvar_register(r, &d);
}

static BreakCVarStatus add_float(BreakCVarRegistry *r, const char *name,
                                 f64 initial) {
    BreakCVarDesc d = desc(name, BREAK_CVAR_FLOAT);
    d.default_value.number = initial;
    d.min_number = -2.0;
    d.max_number = 2.0;
    return break_cvar_register(r, &d);
}

static BreakCVarStatus add_bool(BreakCVarRegistry *r, const char *name,
                                bool initial) {
    BreakCVarDesc d = desc(name, BREAK_CVAR_BOOL);
    d.default_value.boolean = initial;
    return break_cvar_register(r, &d);
}

static BreakCVarStatus add_string(BreakCVarRegistry *r, const char *name,
                                  const char *initial, u32 flags) {
    BreakCVarDesc d = desc(name, BREAK_CVAR_STRING);
    d.default_value.string = initial;
    d.flags = flags;
    return break_cvar_register(r, &d);
}

static bool write_bytes(const char *path, const void *data, usize size) {
    FILE *file = fopen(path, "wb");
    bool ok = file != NULL && (size == 0u || fwrite(data, 1u, size, file) == size);
    if (file && fclose(file) != 0) ok = false;
    return ok;
}

TEST(register_and_read_all_types) {
    BreakCVarRegistry *r = break_cvar_create(8u);
    BreakCVarValue value;
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(add_int(r, "actor.speed", 10, 0, 20, 0u, NULL), BREAK_CVAR_OK);
    ASSERT_EQ(add_float(r, "audio.volume", 0.5), BREAK_CVAR_OK);
    ASSERT_EQ(add_bool(r, "debug.draw", true), BREAK_CVAR_OK);
    ASSERT_EQ(add_string(r, "player.name", "Ada", 0u), BREAK_CVAR_OK);
    ASSERT_EQ(break_cvar_get(r, "actor.speed", BREAK_CVAR_INT, &value), BREAK_CVAR_OK);
    ASSERT_EQ(value.integer, 10);
    ASSERT_EQ(break_cvar_get(r, "audio.volume", BREAK_CVAR_FLOAT, &value), BREAK_CVAR_OK);
    ASSERT_FLOAT_EQ(value.number, 0.5, 0.0);
    ASSERT_EQ(break_cvar_get(r, "debug.draw", BREAK_CVAR_BOOL, &value), BREAK_CVAR_OK);
    ASSERT_TRUE(value.boolean);
    ASSERT_EQ(break_cvar_get(r, "player.name", BREAK_CVAR_STRING, &value), BREAK_CVAR_OK);
    ASSERT_STR_EQ(value.string, "Ada");
    break_cvar_destroy(r);
}

TEST(registration_is_validated_and_capacity_is_fixed) {
    BreakCVarRegistry *r = break_cvar_create(2u);
    BreakCVarDesc d;
    char long_name[BREAK_CVAR_NAME_CAPACITY + 1u];
    char long_string[BREAK_CVAR_STRING_CAPACITY + 1u];
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(add_int(r, "one", 1, 0, 2, 0u, NULL), BREAK_CVAR_OK);
    ASSERT_EQ(add_int(r, "one", 1, 0, 2, 0u, NULL), BREAK_CVAR_REJECTED);
    ASSERT_EQ(add_int(r, "bad name", 1, 0, 2, 0u, NULL), BREAK_CVAR_INVALID);
    ASSERT_EQ(add_int(r, "", 1, 0, 2, 0u, NULL), BREAK_CVAR_INVALID);
    memset(long_name, 'a', sizeof(long_name) - 1u);
    long_name[sizeof(long_name) - 1u] = '\0';
    ASSERT_EQ(add_int(r, long_name, 1, 0, 2, 0u, NULL), BREAK_CVAR_INVALID);
    ASSERT_EQ(add_int(r, "range", 3, 0, 2, 0u, NULL), BREAK_CVAR_INVALID);
    ASSERT_EQ(add_int(r, "inverted", 1, 2, 0, 0u, NULL), BREAK_CVAR_INVALID);
    memset(long_string, 's', sizeof(long_string) - 1u);
    long_string[sizeof(long_string) - 1u] = '\0';
    ASSERT_EQ(add_string(r, "long", long_string, 0u), BREAK_CVAR_INVALID);
    ASSERT_EQ(add_string(r, "utf8", "\xC0\x80", 0u), BREAK_CVAR_INVALID);
    d = desc("nan", BREAK_CVAR_FLOAT);
    d.default_value.number = NAN;
    ASSERT_EQ(break_cvar_register(r, &d), BREAK_CVAR_INVALID);
    d = desc("flags", BREAK_CVAR_BOOL);
    d.default_value.boolean = false;
    d.flags = 4u;
    ASSERT_EQ(break_cvar_register(r, &d), BREAK_CVAR_INVALID);
    ASSERT_EQ(add_int(r, "two", 2, 0, 2, 0u, NULL), BREAK_CVAR_OK);
    ASSERT_EQ(add_int(r, "three", 2, 0, 2, 0u, NULL), BREAK_CVAR_OVERLOAD);
    break_cvar_destroy(r);
    ASSERT_TRUE(break_cvar_create(0u) == NULL);
    ASSERT_TRUE(break_cvar_create(BREAK_CVAR_HARD_MAX + 1u) == NULL);
}

TEST(set_enforces_type_range_permissions_and_callback) {
    BreakCVarRegistry *r = break_cvar_create(5u);
    BreakCVarValue value;
    u32 speed_changes = 0u;
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(add_int(r, "speed", 10, 0, 20, 0u, &speed_changes), BREAK_CVAR_OK);
    ASSERT_EQ(add_int(r, "locked", 4, 0, 20, BREAK_CVAR_READONLY, NULL), BREAK_CVAR_OK);
    ASSERT_EQ(add_int(r, "god", 0, 0, 1, BREAK_CVAR_CHEAT, NULL), BREAK_CVAR_OK);
    value.integer = 11;
    ASSERT_EQ(break_cvar_set(r, "speed", value, false), BREAK_CVAR_OK);
    ASSERT_EQ(speed_changes, 1u);
    ASSERT_EQ(callback_count, 1u);
    ASSERT_STR_EQ(callback_last, "speed");
    ASSERT_EQ(break_cvar_get(r, "speed", BREAK_CVAR_INT, &value), BREAK_CVAR_OK);
    ASSERT_EQ(value.integer, 11);
    value.integer = 21;
    ASSERT_EQ(break_cvar_set(r, "speed", value, false), BREAK_CVAR_OVERLOAD);
    ASSERT_EQ(speed_changes, 1u);
    ASSERT_EQ(break_cvar_get(r, "speed", BREAK_CVAR_INT, &value), BREAK_CVAR_OK);
    ASSERT_EQ(value.integer, 11);
    ASSERT_EQ(break_cvar_get(r, "speed", BREAK_CVAR_FLOAT, &value), BREAK_CVAR_INVALID);
    value.integer = 2;
    ASSERT_EQ(break_cvar_set(r, "locked", value, true), BREAK_CVAR_REJECTED);
    value.integer = 1;
    ASSERT_EQ(break_cvar_set(r, "god", value, false), BREAK_CVAR_REJECTED);
    ASSERT_EQ(break_cvar_set(r, "god", value, true), BREAK_CVAR_OK);
    value.integer = 99;
    ASSERT_EQ(break_cvar_set(r, "missing", value, true), BREAK_CVAR_FAILED);
    break_cvar_destroy(r);
}

TEST(callbacks_cannot_reenter_mutation) {
    BreakCVarRegistry *r = break_cvar_create(1u);
    BreakCVarValue value = { .integer = 1 };
    u32 count = 0u;
    ASSERT_NOT_NULL(r);
    callback_registry = r;
    ASSERT_EQ(add_int(r, "reentrant", 0, 0, 2, 0u, &count), BREAK_CVAR_OK);
    ASSERT_EQ(break_cvar_set(r, "reentrant", value, false), BREAK_CVAR_OK);
    ASSERT_EQ(count, 1u);
    callback_registry = NULL;
    break_cvar_destroy(r);
}

TEST(config_roundtrip_preserves_types_and_notifies_changes_once) {
    char path[256];
    char loaded_path[256];
    BreakCVarRegistry *source = break_cvar_create(8u);
    BreakCVarRegistry *loaded = break_cvar_create(8u);
    BreakCVarValue value;
    u32 speed_changes = 0u;
    test_tmp(path, sizeof(path), "cvar_roundtrip.cfg");
    test_tmp(loaded_path, sizeof(loaded_path), "cvar_roundtrip_saved.cfg");
    ASSERT_NOT_NULL(source);
    ASSERT_NOT_NULL(loaded);
    ASSERT_EQ(add_int(source, "speed", 10, 0, 20, 0u, NULL), BREAK_CVAR_OK);
    ASSERT_EQ(add_float(source, "volume", 0.5), BREAK_CVAR_OK);
    ASSERT_EQ(add_bool(source, "draw", false), BREAK_CVAR_OK);
    ASSERT_EQ(add_string(source, "name", "Ada", 0u), BREAK_CVAR_OK);
    ASSERT_EQ(add_int(source, "god", 0, 0, 1, BREAK_CVAR_CHEAT, NULL), BREAK_CVAR_OK);
    ASSERT_EQ(add_int(source, "fixed", 7, 0, 7, BREAK_CVAR_READONLY, NULL), BREAK_CVAR_OK);
    ASSERT_EQ(add_int(loaded, "speed", 0, 0, 20, 0u, &speed_changes), BREAK_CVAR_OK);
    ASSERT_EQ(add_float(loaded, "volume", 0.0), BREAK_CVAR_OK);
    ASSERT_EQ(add_bool(loaded, "draw", false), BREAK_CVAR_OK);
    ASSERT_EQ(add_string(loaded, "name", "", 0u), BREAK_CVAR_OK);
    ASSERT_EQ(add_int(loaded, "god", 0, 0, 1, BREAK_CVAR_CHEAT, NULL), BREAK_CVAR_OK);
    ASSERT_EQ(add_int(loaded, "fixed", 7, 0, 7, BREAK_CVAR_READONLY, NULL), BREAK_CVAR_OK);
    {
        const char *config = "speed=11\nvolume=1.25\ndraw=true\nname=Grace Hopper\ngod=1\nfixed=7\n";
        ASSERT_TRUE(write_bytes(path, config, strlen(config)));
    }
    ASSERT_EQ(break_cvar_load(loaded, path, false), BREAK_CVAR_REJECTED);
    ASSERT_EQ(break_cvar_load(loaded, path, true), BREAK_CVAR_OK);
    ASSERT_EQ(speed_changes, 1u);
    ASSERT_EQ(break_cvar_get(loaded, "speed", BREAK_CVAR_INT, &value), BREAK_CVAR_OK);
    ASSERT_EQ(value.integer, 11);
    ASSERT_EQ(break_cvar_get(loaded, "volume", BREAK_CVAR_FLOAT, &value), BREAK_CVAR_OK);
    ASSERT_FLOAT_EQ(value.number, 1.25, 0.0);
    ASSERT_EQ(break_cvar_get(loaded, "draw", BREAK_CVAR_BOOL, &value), BREAK_CVAR_OK);
    ASSERT_TRUE(value.boolean);
    ASSERT_EQ(break_cvar_get(loaded, "name", BREAK_CVAR_STRING, &value), BREAK_CVAR_OK);
    ASSERT_STR_EQ(value.string, "Grace Hopper");
    ASSERT_EQ(break_cvar_save(loaded, loaded_path), BREAK_CVAR_OK);
    ASSERT_EQ(break_cvar_load(source, loaded_path, true), BREAK_CVAR_OK);
    ASSERT_EQ(break_cvar_get(source, "speed", BREAK_CVAR_INT, &value), BREAK_CVAR_OK);
    ASSERT_EQ(value.integer, 11);
    ASSERT_EQ(break_cvar_get(source, "name", BREAK_CVAR_STRING, &value), BREAK_CVAR_OK);
    ASSERT_STR_EQ(value.string, "Grace Hopper");
    break_cvar_destroy(source);
    break_cvar_destroy(loaded);
    remove(path);
    remove(loaded_path);
}

TEST(failed_config_load_is_atomic) {
    char path[256];
    BreakCVarRegistry *r = break_cvar_create(4u);
    BreakCVarValue value;
    u32 speed_changes = 0u;
    const char *bad_documents[] = {
        "speed=20\nvolume=not-a-number\n",
        "speed=20\nspeed=12\n",
        "speed=20\nunknown=1\n",
        "speed=20\nlocked=8\n",
        "speed 20\n",
        "speed=21\n"
    };
    const BreakCVarStatus expected[] = {
        BREAK_CVAR_INVALID, BREAK_CVAR_INVALID, BREAK_CVAR_FAILED,
        BREAK_CVAR_REJECTED, BREAK_CVAR_INVALID, BREAK_CVAR_OVERLOAD
    };
    test_tmp(path, sizeof(path), "cvar_atomic.cfg");
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(add_int(r, "speed", 10, 0, 20, 0u, &speed_changes), BREAK_CVAR_OK);
    ASSERT_EQ(add_float(r, "volume", 0.5), BREAK_CVAR_OK);
    ASSERT_EQ(add_int(r, "locked", 7, 0, 7, BREAK_CVAR_READONLY, NULL), BREAK_CVAR_OK);
    value.integer = 11;
    ASSERT_EQ(break_cvar_set(r, "speed", value, false), BREAK_CVAR_OK);
    ASSERT_EQ(speed_changes, 1u);
    for (u32 i = 0u; i < sizeof(bad_documents) / sizeof(bad_documents[0]); i++) {
        ASSERT_TRUE(write_bytes(path, bad_documents[i], strlen(bad_documents[i])));
        ASSERT_EQ(break_cvar_load(r, path, false), expected[i]);
        ASSERT_EQ(break_cvar_get(r, "speed", BREAK_CVAR_INT, &value), BREAK_CVAR_OK);
        ASSERT_EQ(value.integer, 11);
        ASSERT_EQ(speed_changes, 1u);
    }
    break_cvar_destroy(r);
    remove(path);
}

TEST(config_rejects_nul_and_excessive_size) {
    char path[256];
    BreakCVarRegistry *r = break_cvar_create(1u);
    const char nul_document[] = { 's', 'p', 'e', 'e', 'd', '=', '1', '\0', '\n' };
    char *large;
    test_tmp(path, sizeof(path), "cvar_bounded.cfg");
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(add_int(r, "speed", 1, 0, 20, 0u, NULL), BREAK_CVAR_OK);
    ASSERT_TRUE(write_bytes(path, nul_document, sizeof(nul_document)));
    ASSERT_EQ(break_cvar_load(r, path, false), BREAK_CVAR_INVALID);
    large = (char *)malloc(BREAK_CVAR_CONFIG_MAX_BYTES + 1u);
    ASSERT_NOT_NULL(large);
    memset(large, '#', BREAK_CVAR_CONFIG_MAX_BYTES + 1u);
    ASSERT_TRUE(write_bytes(path, large, BREAK_CVAR_CONFIG_MAX_BYTES + 1u));
    ASSERT_EQ(break_cvar_load(r, path, false), BREAK_CVAR_OVERLOAD);
    free(large);
    break_cvar_destroy(r);
    remove(path);
}

TEST(config_io_failures_do_not_replace_values) {
    char path[256];
    BreakCVarRegistry *r = break_cvar_create(1u);
    test_tmp(path, sizeof(path), "cvar_missing.cfg");
    remove(path);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(add_int(r, "speed", 1, 0, 20, 0u, NULL), BREAK_CVAR_OK);
    ASSERT_EQ(break_cvar_load(r, path, false), BREAK_CVAR_FAILED);
    ASSERT_EQ(break_cvar_save(r, "/definitely/not/a/real/directory/config.cfg"),
              BREAK_CVAR_FAILED);
    break_cvar_destroy(r);
}

TEST_MAIN_BEGIN()
    callback_count = 0u;
    RUN_TEST(register_and_read_all_types);
    RUN_TEST(registration_is_validated_and_capacity_is_fixed);
    RUN_TEST(set_enforces_type_range_permissions_and_callback);
    RUN_TEST(callbacks_cannot_reenter_mutation);
    RUN_TEST(config_roundtrip_preserves_types_and_notifies_changes_once);
    RUN_TEST(failed_config_load_is_atomic);
    RUN_TEST(config_rejects_nul_and_excessive_size);
    RUN_TEST(config_io_failures_do_not_replace_values);
TEST_MAIN_END()
