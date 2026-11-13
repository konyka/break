#if !defined(_WIN32)
#define _DEFAULT_SOURCE
#endif

#include "test_framework.h"
#include "../apps/core_app/core_app_checkpoint.h"

#include <animation/anim_compression.h>
#include <game/break_flow.h>
#include <game/break_game.h>
#include <platform/platform_fs.h>
#include <scene/scene_serial.h>
#include <script/break_lua.h>

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <process.h>
#include <windows.h>
#else
#include <signal.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#ifndef CORE_APP_ASSET_BAKE_EXECUTABLE
#error "CORE_APP_ASSET_BAKE_EXECUTABLE must name the real baker"
#endif
#ifndef CORE_APP_FORMAL_ASSET_DIR
#error "CORE_APP_FORMAL_ASSET_DIR must name the formal assets"
#endif

#define TEST_COMP_TRANSFORM 1u
#define TEST_COMP_MESH_REF 3u
#define TEST_MANIFEST_CAP 2048u

typedef struct {
    f32 pos[3];
} TestTransform;

static const char *const k_asset_names[] = {
    "level.bscn", "level.fg", "actors.sidecar", "director.lua",
    "player.lua", "broken.lua", "level.banm", "tone.wav",
    "deterministic.scenario", "load_unload.scenario", "rollback.scenario"
};
static const usize k_asset_count = sizeof(k_asset_names) / sizeof(k_asset_names[0]);
static char g_assets_a[512];
static char g_assets_b[512];
static int g_bake_result = -1;

#if defined(CORE_APP_TEST_WRAP_FS)
static u32 g_file_fsync_failures;
static u32 g_file_fsync_failed;
static u32 g_dir_fsync_failures;
static u32 g_dir_fsync_failed;
static u32 g_rename_failures;
static u32 g_rename_failed;
static u32 g_rename_calls;
static u32 g_restore_write_failed;
static bool g_arm_restore_write;
static bool g_fail_next_write;

ssize_t __real_write(int fd, const void *data, usize size);
int __real_fsync(int fd);
int __real_rename(const char *old_path, const char *new_path);

ssize_t __wrap_write(int fd, const void *data, usize size) {
    if (g_fail_next_write) {
        g_fail_next_write = false;
        ++g_restore_write_failed;
        errno = EIO;
        return -1;
    }
    return __real_write(fd, data, size);
}

int __wrap_fsync(int fd) {
    struct stat status;
    if (fstat(fd, &status) != 0) return __real_fsync(fd);
    if (S_ISREG(status.st_mode) && g_file_fsync_failures > 0u) {
        --g_file_fsync_failures;
        ++g_file_fsync_failed;
        errno = EIO;
        return -1;
    }
    if (S_ISDIR(status.st_mode) && g_dir_fsync_failures > 0u) {
        --g_dir_fsync_failures;
        ++g_dir_fsync_failed;
        if (g_arm_restore_write) g_fail_next_write = true;
        errno = EIO;
        return -1;
    }
    return __real_fsync(fd);
}

int __wrap_rename(const char *old_path, const char *new_path) {
    if (g_rename_failures > 0u) {
        --g_rename_failures;
        ++g_rename_failed;
        errno = EIO;
        return -1;
    }
    int result = __real_rename(old_path, new_path);
    if (result == 0) ++g_rename_calls;
    return result;
}

static void fs_fault_reset(void) {
    g_file_fsync_failures = 0u;
    g_file_fsync_failed = 0u;
    g_dir_fsync_failures = 0u;
    g_dir_fsync_failed = 0u;
    g_rename_failures = 0u;
    g_rename_failed = 0u;
    g_rename_calls = 0u;
    g_restore_write_failed = 0u;
    g_arm_restore_write = false;
    g_fail_next_write = false;
}

static void fs_fault_post_rename(bool fail_restore_write) {
    fs_fault_reset();
    g_dir_fsync_failures = 1u;
    g_arm_restore_write = fail_restore_write;
}
#endif

static void join_path(char *out, usize cap, const char *dir, const char *name) {
    int n = snprintf(out, cap, "%s/%s", dir, name);
    if (n < 0 || (usize)n >= cap) abort();
}

typedef struct {
    unsigned long os_error;
    int crt_error;
} CoreAppTestError;

static CoreAppTestError core_app_test_os_error(void) {
    CoreAppTestError error;
    error.crt_error = errno;
#if defined(_WIN32)
    error.os_error = (unsigned long)GetLastError();
#else
    error.os_error = 0;
#endif
    return error;
}

static CoreAppTestError core_app_test_crt_error(void) {
    CoreAppTestError error = {0, errno};
    return error;
}

static void core_app_test_report(const char *stage, const char *slot, const char *step,
                                 const char *path, i64 raw_result,
                                 CoreAppTestError error) {
    if (!slot) return;
    fprintf(stderr,
            "FAIL: CORE_APP_TEST stage=%s slot=%s step=%s path=%s raw=%lld "
            "os_error=%lu errno=%d\n",
            stage, slot, step, path, (long long)raw_result, error.os_error,
            error.crt_error);
}

static void core_app_test_report_command(const char *slot, const char *step,
                                         const char *command, const char *path,
                                         i64 raw_result, CoreAppTestError error) {
    fprintf(stderr,
            "FAIL: CORE_APP_TEST stage=launch slot=%s step=%s command=%s path=%s "
            "raw=%lld os_error=%lu errno=%d\n",
            slot, step, command, path, (long long)raw_result, error.os_error,
            error.crt_error);
}

static int clear_directory(const char *dir, const char *slot) {
    PlatformDirEntry entries[32];
    u32 count = 0;
    bool list_result = platform_list_dir(dir, entries, 32, &count);
    CoreAppTestError list_error = core_app_test_os_error();
    if (!list_result) {
        core_app_test_report("prepare", slot, "prepare.clear_directory", dir,
                             (i64)list_result, list_error);
        return -1;
    }
    if (count > 32u) {
        CoreAppTestError error = {0, 0};
        core_app_test_report("prepare", slot, "prepare.clear_directory", dir, -1, error);
        return -1;
    }
    for (u32 i = 0; i < count; ++i) {
        char path[1024];
        if (entries[i].is_dir) {
            CoreAppTestError error = {0, 0};
            core_app_test_report("prepare", slot, "prepare.clear_directory", dir, -1,
                                 error);
            return -1;
        }
        join_path(path, sizeof(path), dir, entries[i].name);
        int remove_result = remove(path);
        CoreAppTestError remove_error = core_app_test_crt_error();
        if (remove_result != 0) {
            core_app_test_report("prepare", slot, "prepare.remove", path,
                                 (i64)remove_result, remove_error);
            return -1;
        }
    }
    return 0;
}

static int prepare_directory_with_slot(const char *dir, const char *slot) {
    bool file_result = platform_file_size(dir, &(u64){0u});
    if (file_result) {
        CoreAppTestError error = {0, 0};
        core_app_test_report("prepare", slot, "prepare.file_size", dir,
                             (i64)file_result, error);
        return -1;
    }
    bool mkdir_result = platform_mkdir(dir);
    if (!mkdir_result) {
        if (clear_directory(dir, slot) != 0) return -1;
        mkdir_result = platform_mkdir(dir);
        CoreAppTestError mkdir_error = core_app_test_os_error();
        if (!mkdir_result) {
            core_app_test_report("prepare", slot, "prepare.platform_mkdir", dir,
                                 (i64)mkdir_result, mkdir_error);
            return -1;
        }
    }
    return clear_directory(dir, slot);
}

static int prepare_directory(const char *dir) {
    return prepare_directory_with_slot(dir, NULL);
}

static int prepare_asset_directory(const char *dir, const char *slot) {
    return prepare_directory_with_slot(dir, slot);
}

static int test_write_checkpoint_file(const char *dir, const char *name,
                                      const void *data, usize size) {
    char path[1024];
    join_path(path, sizeof(path), dir, name);
    FILE *fp = fopen(path, "wb");
    if (!fp) return -1;
    bool ok = size == 0u || fwrite(data, 1, size, fp) == size;
    if (fclose(fp) != 0) ok = false;
    return ok ? 0 : -1;
}

#if !defined(_WIN32)
static int test_hard_link_checkpoint_file(const char *dir, const char *name,
                                          const char *alias) {
    char path[1024];
    char alias_path[1024];
    struct stat file_status;
    struct stat alias_status;
    join_path(path, sizeof(path), dir, name);
    join_path(alias_path, sizeof(alias_path), dir, alias);
    if (stat(path, &file_status) != 0) return -1;
    if (stat(alias_path, &alias_status) != 0) {
        if (errno != ENOENT) return -1;
        if (link(path, alias_path) != 0 && errno != EEXIST) return -1;
        if (stat(alias_path, &alias_status) != 0) return -1;
    }
    return file_status.st_dev == alias_status.st_dev &&
                   file_status.st_ino == alias_status.st_ino ? 0 : -1;
}
#endif

static u8 *test_read_file(const char *dir, const char *name, usize cap,
                          usize *out_size) {
    char path[1024];
    join_path(path, sizeof(path), dir, name);
    u64 size = 0;
    *out_size = 0u;
    if (!platform_file_size(path, &size) || size > (u64)cap) return NULL;
    u8 *bytes = (u8 *)malloc(size ? (usize)size : 1u);
    if (!bytes) return NULL;
    FILE *fp = fopen(path, "rb");
    if (!fp) {
        free(bytes);
        return NULL;
    }
    usize got = size ? fread(bytes, 1, (usize)size, fp) : 0u;
    int extra = fgetc(fp);
    bool ok = got == (usize)size && extra == EOF;
    if (fclose(fp) != 0) ok = false;
    if (!ok) {
        free(bytes);
        return NULL;
    }
    *out_size = (usize)size;
    return bytes;
}

static int test_copy_file(const char *src_dir, const char *dst_dir,
                          const char *name) {
    usize size = 0;
    u8 *bytes = test_read_file(src_dir, name, TEST_MANIFEST_CAP, &size);
    if (!bytes) return -1;
    int result = test_write_checkpoint_file(dst_dir, name, bytes, size);
    free(bytes);
    return result;
}

static int test_copy_checkpoint(const char *src_dir, const char *dst_dir) {
    PlatformDirEntry entries[16];
    u32 count = 0;
    if (!platform_list_dir(src_dir, entries, 16, &count) || count > 16u) return -1;
    for (u32 i = 0; i < count; ++i) {
        if (entries[i].is_dir || test_copy_file(src_dir, dst_dir, entries[i].name) != 0)
            return -1;
    }
    return 0;
}

static u64 test_fnv1a64(const void *data, usize size) {
    const u8 *bytes = (const u8 *)data;
    u64 hash = 14695981039346656037ULL;
    for (usize i = 0; i < size; ++i) {
        hash ^= bytes[i];
        hash *= 1099511628211ULL;
    }
    return hash;
}

static int test_checkpoint_corrupt_payload_for_fixture(const char *dir,
                                                       const char *prefix) {
    PlatformDirEntry entries[16];
    u32 count = 0;
    if (!platform_list_dir(dir, entries, 16, &count) || count > 16u) return -1;
    const char *selected = NULL;
    usize prefix_len = strlen(prefix);
    for (u32 i = 0; i < count; ++i) {
        if (!entries[i].is_dir && strncmp(entries[i].name, prefix, prefix_len) == 0 &&
            (!selected || strcmp(entries[i].name, selected) > 0))
            selected = entries[i].name;
    }
    if (!selected) return -1;
    char path[1024];
    join_path(path, sizeof(path), dir, selected);
    FILE *fp = fopen(path, "r+b");
    if (!fp) return -1;
    int value = fgetc(fp);
    bool ok = value != EOF;
    if (ok) {
        rewind(fp);
        ok = fputc(value ^ 0x01, fp) != EOF && fflush(fp) == 0;
    }
    if (fclose(fp) != 0) ok = false;
    return ok ? 0 : -1;
}

static int file_exists(const char *dir, const char *name) {
    char path[1024];
    join_path(path, sizeof(path), dir, name);
    FILE *fp = fopen(path, "rb");
    if (!fp) return 0;
    fclose(fp);
    return 1;
}

static int run_baker(const char *output, const char *slot) {
    char command[1600];
    command[0] = '\0';
    int n = snprintf(command, sizeof(command), "\"%s\" --output \"%s\"",
                     CORE_APP_ASSET_BAKE_EXECUTABLE, output);
    if (n < 0 || (usize)n >= sizeof(command)) {
        CoreAppTestError error = core_app_test_os_error();
        core_app_test_report_command(slot, "launch.command", command, output, (i64)n,
                                     error);
        return -1;
    }
#if defined(_WIN32)
    char executable_arg[1024];
    char output_arg[1024];
    int executable_length = snprintf(executable_arg, sizeof(executable_arg), "\"%s\"",
                                     CORE_APP_ASSET_BAKE_EXECUTABLE);
    int output_length = snprintf(output_arg, sizeof(output_arg), "\"%s\"", output);
    if (executable_length < 0 || (usize)executable_length >= sizeof(executable_arg) ||
        output_length < 0 || (usize)output_length >= sizeof(output_arg)) {
        int length_result =
            executable_length < 0 || (usize)executable_length >= sizeof(executable_arg)
                ? executable_length
                : output_length;
        CoreAppTestError error = core_app_test_os_error();
        core_app_test_report_command(slot, "launch.command", command, output,
                                     (i64)length_result, error);
        return -1;
    }
    const char *argv[] = {executable_arg, "--output", output_arg, NULL};
    int result = (int)_spawnv(_P_WAIT, CORE_APP_ASSET_BAKE_EXECUTABLE, argv);
    CoreAppTestError error = core_app_test_os_error();
    if (result != 0)
        core_app_test_report_command(slot, "launch.spawnv", command, output,
                                     (i64)result, error);
#else
    int result = system(command);
    CoreAppTestError error = core_app_test_os_error();
    if (result != 0)
        core_app_test_report_command(slot, "launch.system", command, output,
                                     (i64)result, error);
#endif
    return result;
}

static int ensure_baked(void) {
    if (g_bake_result >= 0) return g_bake_result;
    test_tmp(g_assets_a, sizeof(g_assets_a), "core_app_assets_a");
    test_tmp(g_assets_b, sizeof(g_assets_b), "core_app_assets_b");
    int prepare_result = prepare_asset_directory(g_assets_a, "A");
    if (prepare_result != 0) {
        g_bake_result = 1;
        return g_bake_result;
    }
    prepare_result = prepare_asset_directory(g_assets_b, "B");
    if (prepare_result != 0) {
        g_bake_result = 1;
        return g_bake_result;
    }
    g_bake_result = run_baker(g_assets_a, "A");
    if (g_bake_result == 0) g_bake_result = run_baker(g_assets_b, "B");
    return g_bake_result;
}

static int files_equal(const char *dir_a, const char *dir_b, const char *name) {
    char path_a[1024];
    char path_b[1024];
    join_path(path_a, sizeof(path_a), dir_a, name);
    join_path(path_b, sizeof(path_b), dir_b, name);
    u64 size_a = 0, size_b = 0;
    if (!platform_file_size(path_a, &size_a) || size_a == 0u ||
        !platform_file_size(path_b, &size_b) || size_a != size_b)
        return 0;
    FILE *a = fopen(path_a, "rb");
    FILE *b = fopen(path_b, "rb");
    if (!a || !b) {
        if (a) fclose(a);
        if (b) fclose(b);
        return 0;
    }
    int equal = 1;
    for (;;) {
        u8 bytes_a[4096];
        u8 bytes_b[4096];
        usize got_a = fread(bytes_a, 1, sizeof(bytes_a), a);
        usize got_b = fread(bytes_b, 1, sizeof(bytes_b), b);
        if (got_a != got_b || memcmp(bytes_a, bytes_b, got_a) != 0) {
            equal = 0;
            break;
        }
        if (got_a < sizeof(bytes_a)) {
            if (ferror(a) || ferror(b)) equal = 0;
            break;
        }
    }
    if (fclose(a) != 0) equal = 0;
    if (fclose(b) != 0) equal = 0;
    return equal;
}

static const char *formal_asset_dir(void) {
    const char *override = getenv("CORE_APP_FORMAL_ASSET_DIR");
    return override && override[0] != '\0' ? override : CORE_APP_FORMAL_ASSET_DIR;
}

TEST(formal_assets_match_fresh_baker) {
    ASSERT_EQ(ensure_baked(), 0);
    PlatformDirEntry entries[16];
    u32 count = 0;
    ASSERT_TRUE(platform_list_dir(formal_asset_dir(), entries, 16, &count));
    ASSERT_EQ(count, k_asset_count);
    for (usize i = 0; i < k_asset_count; ++i) {
        bool found = false;
        for (u32 n = 0; n < count && n < 16u; ++n) {
            if (strcmp(entries[n].name, k_asset_names[i]) == 0) found = true;
        }
        ASSERT_TRUE(found);
        ASSERT_TRUE(files_equal(formal_asset_dir(), g_assets_a, k_asset_names[i]));
    }
}

static u16 read_u16(const u8 *p) {
    return (u16)((u16)p[0] | ((u16)p[1] << 8));
}

static u32 read_u32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) |
           ((u32)p[3] << 24);
}

static u64 read_u64(const u8 *p) {
    return (u64)read_u32(p) | ((u64)read_u32(p + 4) << 32);
}

TEST(baker_emits_every_formal_asset_byte_identically) {
    ASSERT_EQ(ensure_baked(), 0);
    for (usize i = 0; i < k_asset_count; ++i)
        ASSERT_TRUE(files_equal(g_assets_a, g_assets_b, k_asset_names[i]));
}

TEST(baker_supports_spaces_in_output_path) {
    ASSERT_EQ(ensure_baked(), 0);
    char output[512];
    join_path(output, sizeof(output), g_assets_a, "directory with spaces");
    ASSERT_EQ(prepare_asset_directory(output, "space"), 0);
    ASSERT_EQ(run_baker(output, "space"), 0);
    for (usize i = 0; i < k_asset_count; ++i)
        ASSERT_TRUE(files_equal(g_assets_b, output, k_asset_names[i]));
    ASSERT_EQ(clear_directory(output, "space"), 0);
    ASSERT_EQ(TEST_RMDIR(output), 0);
}

typedef struct {
    Scene scene;
} SceneHook;

static BreakGameError load_baked_scene(void *user, World *world, const char *path) {
    SceneHook *hook = (SceneHook *)user;
    return scene_load_binary(world, &hook->scene, path) ? BREAK_GAME_OK
                                                       : BREAK_GAME_FAILED;
}

static void unload_baked_scene(void *user, World *world) {
    (void)world;
    SceneHook *hook = (SceneHook *)user;
    free(hook->scene.materials);
    hook->scene.materials = NULL;
    hook->scene.material_count = 0u;
    scene_serial_free(&hook->scene);
}

static void count_actor_tick(BreakGame *app, Entity entity, f32 dt, void *user) {
    (void)app;
    (void)entity;
    (void)dt;
    ++*(u32 *)user;
}

TEST(scene_and_actor_sidecar_roundtrip_through_p1_reader) {
    ASSERT_EQ(ensure_baked(), 0);
    char scene_path[1024];
    char sidecar_path[1024];
    join_path(scene_path, sizeof(scene_path), formal_asset_dir(), "level.bscn");
    join_path(sidecar_path, sizeof(sidecar_path), formal_asset_dir(), "actors.sidecar");
    ASSERT_TRUE(scene_probe_binary(scene_path));

    World *world = world_create();
    ASSERT_NOT_NULL(world);
    world_register_component(world, BREAK_GAME_POSITION_COMPONENT, sizeof(Vec3));
    world_register_component(world, TEST_COMP_TRANSFORM, sizeof(TestTransform));
    world_register_component(world, TEST_COMP_MESH_REF, sizeof(u32));
    BreakGameConfig config = {8u, 8u};
    BreakGame *app = break_game_create(world, &config);
    ASSERT_NOT_NULL(app);
    static const char *const class_names[] = {
        "Ground", "Player", "Enemy", "DynamicWall", "Vehicle",
        "VisibleColor", "HiddenColor"
    };
    u32 tick = 0;
    for (u32 i = 0; i < 7u; ++i) {
        BreakGameClassDesc desc;
        memset(&desc, 0, sizeof(desc));
        desc.name = class_names[i];
        u32 class_id = 0;
        ASSERT_EQ(break_game_register_class(app, &desc, &class_id), BREAK_GAME_OK);
        break_game_set_tick(app, class_id, count_actor_tick, &tick);
    }
    SceneHook hook;
    memset(&hook, 0, sizeof(hook));
    BreakGameLevelHooks hooks = {load_baked_scene, unload_baked_scene, &hook};
    ASSERT_EQ(break_game_level_open(app, &hooks, scene_path, sidecar_path),
              BREAK_GAME_OK);
    ASSERT_EQ(world->entity_count, 8u);
    for (u32 i = 1; i <= 7u; ++i) {
        ASSERT_TRUE(world_entity_exists(world, world->entities[i]));
        ASSERT_TRUE(world->entities[i].generation != 0u);
        ASSERT_NOT_NULL(world_get_component(world, world->entities[i],
                                            TEST_COMP_TRANSFORM));
        u32 *mesh = (u32 *)world_get_component(world, world->entities[i],
                                               TEST_COMP_MESH_REF);
        ASSERT_NOT_NULL(mesh);
        ASSERT_EQ(*mesh, 0u);
    }
    break_game_tick(app, 1.0f / 60.0f);
    ASSERT_EQ(tick, 7u);

    ASSERT_EQ(hook.scene.node_count, 7u);
    ASSERT_EQ(hook.scene.mesh_geometry_count, 1u);
    ASSERT_EQ(hook.scene.mesh_geometry[0].vertex_count, 24u);
    ASSERT_EQ(hook.scene.mesh_geometry[0].index_count, 36u);
    ASSERT_EQ(hook.scene.resource_count, 8u);
    ASSERT_FLOAT_EQ(hook.scene.nodes[0].local_transform.e[0][0], 16.0f, 0.0f);
    ASSERT_TRUE(hook.scene.nodes[5].has_mesh);
    ASSERT_FALSE(hook.scene.nodes[6].has_mesh);
    ASSERT_EQ(hook.scene.nodes[5].mesh_index, 0u);
    ASSERT_EQ(hook.scene.nodes[6].mesh_index, 0u);
    ASSERT_EQ(hook.scene.nodes[5].material_idx, 5u);
    ASSERT_EQ(hook.scene.nodes[6].material_idx, 6u);
    ASSERT_TRUE(scene_rebuild_materials_from_manifest(&hook.scene));
    ASSERT_EQ(hook.scene.material_count, 7u);
    ASSERT_TRUE(hook.scene.materials[5].base_color[0] >
                hook.scene.materials[5].base_color[2]);
    ASSERT_TRUE(hook.scene.materials[6].base_color[2] >
                hook.scene.materials[6].base_color[0]);

    ASSERT_EQ(break_game_level_close(app), BREAK_GAME_OK);
    break_game_destroy(app);
    world_destroy(world);
}

TEST(flow_deserializes_enter_delay_add_item_chain) {
    ASSERT_EQ(ensure_baked(), 0);
    usize size = 0;
    u8 *bytes = test_read_file(formal_asset_dir(), "level.fg", 4096u, &size);
    ASSERT_NOT_NULL(bytes);
    BreakFlowGraph *graph = NULL;
    ASSERT_EQ(break_flow_deserialize(bytes, size, &graph), BREAK_FLOW_OK);
    free(bytes);
    ASSERT_NOT_NULL(graph);
    ASSERT_EQ(break_flow_graph_node_count(graph), 3u);
    ASSERT_EQ(break_flow_graph_link_count(graph), 2u);
    BreakFlowNodeDesc nodes[3];
    for (u32 i = 0; i < 3u; ++i) {
        u32 id = 0;
        ASSERT_EQ(break_flow_node_at(graph, i, &id, &nodes[i]), BREAK_FLOW_OK);
        ASSERT_EQ(id, i + 1u);
    }
    ASSERT_EQ(nodes[0].type, BREAK_FLOW_NODE_EVENT);
    ASSERT_STR_EQ(nodes[0].name, "enter");
    ASSERT_EQ(nodes[0].event_key, 1u);
    ASSERT_EQ(nodes[1].type, BREAK_FLOW_NODE_DELAY);
    ASSERT_STR_EQ(nodes[1].name, "delay");
    ASSERT_EQ(nodes[1].delay_ticks, 30u);
    ASSERT_EQ(nodes[2].type, BREAK_FLOW_NODE_ENTITY_ADD_ITEM);
    ASSERT_STR_EQ(nodes[2].name, "add-item");
    ASSERT_EQ(nodes[2].entity.index, 2u);
    ASSERT_TRUE(nodes[2].entity.generation != 0u);
    ASSERT_EQ(nodes[2].item_id, 1u);
    for (u32 i = 0; i < 2u; ++i) {
        u32 id = 0;
        BreakFlowLinkDesc link;
        ASSERT_EQ(break_flow_link_at(graph, i, &id, &link), BREAK_FLOW_OK);
        ASSERT_EQ(link.kind, BREAK_FLOW_PORT_EXEC);
        ASSERT_EQ(link.source_node, i + 1u);
        ASSERT_EQ(link.target_node, i + 2u);
        ASSERT_EQ(link.target_port, BREAK_FLOW_EXEC_IN);
    }
    break_flow_graph_destroy(graph);
}

static f32 quaternion_angle(const f32 *a, const f32 *b) {
    f32 dot = fabsf(a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3]);
    if (dot > 1.0f) dot = 1.0f;
    return 2.0f * acosf(dot);
}

TEST(animation_decodes_within_public_error_bounds) {
    ASSERT_EQ(ensure_baked(), 0);
    usize size = 0;
    u8 *bytes = test_read_file(formal_asset_dir(), "level.banm", ANIM_CODEC_MAX_BYTES,
                               &size);
    ASSERT_NOT_NULL(bytes);
    static AnimClip decoded;
    ASSERT_EQ(anim_codec_decode(bytes, size, &decoded), ANIM_CODEC_OK);
    free(bytes);
    static const f32 times[3] = {0.0f, 0.5f, 1.0f};
    static const f32 translation[3][4] = {
        {0.0f, 0.0f, 0.0f, 0.0f},
        {1.0f, 2.0f, 3.0f, 0.0f},
        {2.0f, 0.0f, -1.0f, 0.0f}
    };
    static const f32 rotation[3][4] = {
        {0.0f, 0.0f, 0.0f, 1.0f},
        {0.0f, 0.6f, 0.0f, 0.8f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
    static const f32 scale[3][4] = {
        {1.0f, 1.0f, 1.0f, 0.0f},
        {2.0f, 3.0f, 4.0f, 0.0f},
        {1.0f, 1.0f, 1.0f, 0.0f}
    };
    const f32 (*expected[3])[4] = {translation, rotation, scale};
    ASSERT_FLOAT_EQ(decoded.duration, 1.0f, 0.0f);
    ASSERT_TRUE(decoded.loop);
    ASSERT_EQ(decoded.channel_count, 3u);
    f32 time_bound = anim_codec_time_error_bound(1.0f);
    for (u32 c = 0; c < 3u; ++c) {
        const AnimChannel *channel = &decoded.channels[c];
        ASSERT_EQ(channel->joint_index, c);
        ASSERT_EQ(channel->keyframe_count, 3u);
        ASSERT_EQ(channel->path, (AnimPathType)c);
        for (u32 k = 0; k < 3u; ++k) {
            ASSERT_FLOAT_EQ(channel->times[k], times[k], time_bound);
            if (c == 1u) {
                ASSERT_TRUE(quaternion_angle(rotation[k], channel->values[k]) <=
                            ANIM_CODEC_ROTATION_ERROR_BOUND);
            } else {
                f32 min_value[3] = {expected[c][0][0], expected[c][0][1],
                                    expected[c][0][2]};
                f32 max_value[3] = {min_value[0], min_value[1], min_value[2]};
                for (u32 other = 1; other < 3u; ++other) {
                    for (u32 a = 0; a < 3u; ++a) {
                        f32 value = expected[c][other][a];
                        if (value < min_value[a]) min_value[a] = value;
                        if (value > max_value[a]) max_value[a] = value;
                    }
                }
                for (u32 a = 0; a < 3u; ++a) {
                    f32 bound = anim_codec_scalar_error_bound(min_value[a], max_value[a]);
                    ASSERT_FLOAT_EQ(channel->values[k][a], expected[c][k][a], bound);
                }
            }
        }
    }
}

TEST(wav_is_canonical_44100_hz_mono_pcm16) {
    ASSERT_EQ(ensure_baked(), 0);
    usize size = 0;
    u8 *bytes = test_read_file(formal_asset_dir(), "tone.wav", 65536u, &size);
    ASSERT_NOT_NULL(bytes);
    ASSERT_EQ(size, 44u + 4410u * 2u);
    ASSERT_TRUE(memcmp(bytes, "RIFF", 4) == 0);
    ASSERT_TRUE(memcmp(bytes + 8, "WAVEfmt ", 8) == 0);
    ASSERT_TRUE(memcmp(bytes + 36, "data", 4) == 0);
    ASSERT_EQ(read_u32(bytes + 4), (u32)size - 8u);
    ASSERT_EQ(read_u32(bytes + 16), 16u);
    ASSERT_EQ(read_u16(bytes + 20), 1u);
    ASSERT_EQ(read_u16(bytes + 22), 1u);
    ASSERT_EQ(read_u32(bytes + 24), 44100u);
    ASSERT_EQ(read_u32(bytes + 28), 88200u);
    ASSERT_EQ(read_u16(bytes + 32), 2u);
    ASSERT_EQ(read_u16(bytes + 34), 16u);
    ASSERT_EQ(read_u32(bytes + 40), 4410u * 2u);
    free(bytes);
}

TEST(lua_assets_execute_and_broken_source_is_rejected) {
    ASSERT_EQ(ensure_baked(), 0);
    usize director_size = 0, player_size = 0, broken_size = 0;
    u8 *director = test_read_file(formal_asset_dir(), "director.lua", 4096u, &director_size);
    u8 *player = test_read_file(formal_asset_dir(), "player.lua", 4096u, &player_size);
    u8 *broken = test_read_file(formal_asset_dir(), "broken.lua", 4096u, &broken_size);
    ASSERT_NOT_NULL(director);
    ASSERT_NOT_NULL(player);
    ASSERT_NOT_NULL(broken);
    BreakLuaRuntime *runtime = break_lua_runtime_create(NULL);
    ASSERT_NOT_NULL(runtime);
    ASSERT_EQ(break_lua_runtime_load_module(runtime, "director", director,
                                            director_size), BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(runtime, "player", player,
                                            player_size), BREAK_LUA_OK);
    BreakLuaValue results[2];
    memset(results, 0, sizeof(results));
    ASSERT_EQ(break_lua_runtime_call(runtime, "director", "on_enter", NULL, 0u,
                                     results, 2u), BREAK_LUA_OK);
    ASSERT_EQ(results[0].type, BREAK_LUA_VALUE_NUMBER);
    ASSERT_EQ(results[1].type, BREAK_LUA_VALUE_NUMBER);
    ASSERT_FLOAT_EQ(results[0].as.n, 30.0, 0.0);
    ASSERT_FLOAT_EQ(results[1].as.n, 1.0, 0.0);
    ASSERT_EQ(break_lua_runtime_load_module(runtime, "broken", broken,
                                            broken_size), BREAK_LUA_FAILED);
    break_lua_runtime_destroy(runtime);
    free(director);
    free(player);
    free(broken);
}

TEST(checkpoint_manifest_is_versioned_little_endian_and_detects_corruption) {
    static const u8 expected_magic[8] = {
        'C', 'O', 'R', 'E', 'C', 'K', 'P', 'T'
    };
    char dir[512], backup[512];
    test_tmp(dir, sizeof(dir), "core_app_checkpoint_current");
    test_tmp(backup, sizeof(backup), "core_app_checkpoint_backup");
    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(prepare_directory(backup), 0);
    const u8 payload[] = {1u, 2u, 3u, 4u};
    CoreAppCheckpointFile file = {.kind = 1u, .size = sizeof(payload),
                              .hash = 0u, .name = "runtime_1.bin"};
    file.hash = test_fnv1a64(payload, sizeof(payload));
    ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
    CoreAppCheckpointCommitResult initial_commit = CORE_APP_CHECKPOINT_COMMIT_NOT_COMMITTED;
    ASSERT_EQ(core_app_checkpoint_write_manifest_ex(dir, &file, 1u, 1u, &initial_commit),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(initial_commit, CORE_APP_CHECKPOINT_COMMIT_DURABLE);
    ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_OK);
    u64 before_hash = core_app_checkpoint_manifest_hash(dir);
    ASSERT_TRUE(before_hash != 0u);
    ASSERT_EQ(test_copy_checkpoint(dir, backup), 0);

    usize manifest_size = 0;
    u8 *manifest = test_read_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                  TEST_MANIFEST_CAP, &manifest_size);
    ASSERT_NOT_NULL(manifest);
    ASSERT_EQ(manifest_size, 40u + 88u);
    ASSERT_TRUE(memcmp(manifest, expected_magic, sizeof(expected_magic)) == 0);
    ASSERT_EQ(read_u32(manifest + 8), 1u);
    ASSERT_EQ(read_u32(manifest + 12), 40u);
    ASSERT_EQ(read_u64(manifest + 16), (u64)manifest_size);
    ASSERT_EQ(read_u64(manifest + 24), 1u);
    ASSERT_EQ(read_u32(manifest + 32), 1u);
    ASSERT_EQ(read_u32(manifest + 36), 0u);
    ASSERT_EQ(read_u32(manifest + 40), 1u);
    ASSERT_EQ(read_u32(manifest + 44), 13u);
    ASSERT_EQ(read_u64(manifest + 48), sizeof(payload));
    ASSERT_EQ(read_u64(manifest + 56), file.hash);
    ASSERT_STR_EQ((const char *)manifest + 64, "runtime_1.bin");
    free(manifest);

    strcpy(file.name, "runtime_2.bin");
    ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 1u, 2u), BREAK_RUNTIME_OK);
    ASSERT_TRUE(before_hash != core_app_checkpoint_manifest_hash(dir));
    ASSERT_EQ(test_checkpoint_corrupt_payload_for_fixture(dir, "runtime"), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(core_app_checkpoint_probe(backup), BREAK_RUNTIME_OK);

    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(test_copy_checkpoint(backup, dir), 0);
    char manifest_path[1024];
    join_path(manifest_path, sizeof(manifest_path), dir, CORE_APP_CHECKPOINT_MANIFEST_NAME);
    FILE *damaged = fopen(manifest_path, "ab");
    ASSERT_NOT_NULL(damaged);
    ASSERT_EQ(fputc(0u, damaged), 0);
    ASSERT_EQ(fclose(damaged), 0);
    ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(core_app_checkpoint_probe(backup), BREAK_RUNTIME_OK);
    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(prepare_directory(backup), 0);
    ASSERT_EQ(TEST_RMDIR(dir), 0);
    ASSERT_EQ(TEST_RMDIR(backup), 0);
}

static int test_write_single_file_checkpoint(const char *dir) {
    const u8 payload[] = {1u, 2u, 3u, 4u};
    CoreAppCheckpointFile file = {.kind = 1u, .size = sizeof(payload),
                                  .hash = 0u, .name = "runtime_1.bin"};
    file.hash = test_fnv1a64(payload, sizeof(payload));
    if (test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)) != 0)
        return -1;
    return core_app_checkpoint_write_manifest(dir, &file, 1u, 1u) == BREAK_RUNTIME_OK
        ? 0 : -1;
}

TEST(checkpoint_rejects_legacy_magic) {
    static const u8 old_magic[8] = {
        'G', 'A', 'M', 'E', 'C', 'K', 'P', 'T'
    };
    char dir[512];
    test_tmp(dir, sizeof(dir), "core_app_checkpoint_old_magic");
    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(test_write_single_file_checkpoint(dir), 0);
    usize size = 0;
    u8 *manifest = test_read_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                  TEST_MANIFEST_CAP, &size);
    ASSERT_NOT_NULL(manifest);
    ASSERT_TRUE(size >= sizeof(old_magic));
    memcpy(manifest, old_magic, sizeof(old_magic));
    ASSERT_EQ(test_write_checkpoint_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                         manifest, size), 0);
    free(manifest);
    ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(TEST_RMDIR(dir), 0);
}

TEST(checkpoint_rejects_legacy_manifest_name) {
    static const char old_manifest_name[] = {
        'm', 'a', 'n', 'i', 'f', 'e', 's', 't', '.', 'g', 'a', 'm', 'e', '\0'
    };
    char dir[512];
    test_tmp(dir, sizeof(dir), "core_app_checkpoint_old_manifest");
    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(test_write_single_file_checkpoint(dir), 0);
    usize size = 0;
    u8 *manifest = test_read_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                  TEST_MANIFEST_CAP, &size);
    ASSERT_NOT_NULL(manifest);
    ASSERT_EQ(test_write_checkpoint_file(dir, old_manifest_name, manifest, size), 0);
    free(manifest);
    if (strcmp(CORE_APP_CHECKPOINT_MANIFEST_NAME, old_manifest_name) != 0) {
        char current_path[1024];
        join_path(current_path, sizeof(current_path), dir,
                  CORE_APP_CHECKPOINT_MANIFEST_NAME);
        ASSERT_EQ(remove(current_path), 0);
    }
    ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_FAILED);
    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(TEST_RMDIR(dir), 0);
}

TEST(checkpoint_rejects_unsafe_names_and_overflow_before_commit) {
    char dir[512];
    test_tmp(dir, sizeof(dir), "core_app_checkpoint_invalid");
    ASSERT_EQ(prepare_directory(dir), 0);
    const u8 payload[] = {4u, 3u, 2u, 1u};
    CoreAppCheckpointFile file = {.kind = 1u, .size = sizeof(payload),
                              .hash = 0u, .name = "state_1.bin"};
    file.hash = test_fnv1a64(payload, sizeof(payload));
    ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 1u, 1u), BREAK_RUNTIME_OK);
    u64 old_hash = core_app_checkpoint_manifest_hash(dir);
    static const char *const bad_names[] = {
        "../escape", "/absolute", "folder\\escape", "bad..name"
    };
    for (usize i = 0; i < sizeof(bad_names) / sizeof(bad_names[0]); ++i) {
        strcpy(file.name, bad_names[i]);
        ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 1u, 2u),
                  BREAK_RUNTIME_INVALID);
        ASSERT_EQ(core_app_checkpoint_manifest_hash(dir), old_hash);
    }
    strcpy(file.name, "state_2.bin");
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, NULL, 1u, 2u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 0u, 2u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file,
              CORE_APP_CHECKPOINT_MAX_FILES + 1u, 2u), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 1u, 0u),
              BREAK_RUNTIME_INVALID);
    file.size = (u64)CORE_APP_CHECKPOINT_MAX_FILE_BYTES + 1u;
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 1u, 2u),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(core_app_checkpoint_manifest_hash(dir), old_hash);
    ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_OK);
    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(TEST_RMDIR(dir), 0);
}

TEST(checkpoint_basename_63_is_valid_and_64_is_overload) {
    char dir[512];
    test_tmp(dir, sizeof(dir), "core_app_checkpoint_name_length_api");
    ASSERT_EQ(prepare_directory(dir), 0);
    const u8 payload[] = {1u, 2u, 3u, 4u};
    CoreAppCheckpointFile file = {.kind = 1u, .size = sizeof(payload),
                              .hash = 0u, .name = "state_1.bin"};
    file.hash = test_fnv1a64(payload, sizeof(payload));
    ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 1u, 1u), BREAK_RUNTIME_OK);
    u64 old_hash = core_app_checkpoint_manifest_hash(dir);

    memset(file.name, 'x', sizeof(file.name));
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 1u, 2u),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(core_app_checkpoint_manifest_hash(dir), old_hash);
    ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_OK);

    memset(file.name, 0, sizeof(file.name));
    memset(file.name, 'y', 63u);
    ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 1u, 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_OK);
    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(TEST_RMDIR(dir), 0);
}

TEST(checkpoint_manifest_name_length_overload_is_distinct_from_corruption) {
    char dir[512];
    test_tmp(dir, sizeof(dir), "core_app_checkpoint_name_length_disk");
    ASSERT_EQ(prepare_directory(dir), 0);
    const u8 payload[] = {1u, 2u, 3u, 4u};
    CoreAppCheckpointFile file = {.kind = 1u, .size = sizeof(payload),
                              .hash = 0u, .name = "state_1.bin"};
    file.hash = test_fnv1a64(payload, sizeof(payload));
    ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 1u, 1u), BREAK_RUNTIME_OK);
    usize size = 0;
    u8 *manifest = test_read_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                  TEST_MANIFEST_CAP, &size);
    ASSERT_NOT_NULL(manifest);
    ASSERT_EQ(size, 128u);
    static const u32 lengths[] = {64u, UINT32_MAX};
    for (usize i = 0; i < sizeof(lengths) / sizeof(lengths[0]); ++i) {
        u32 length = lengths[i];
        for (u32 byte = 0; byte < 4u; ++byte)
            manifest[44u + byte] = (u8)(length >> (byte * 8u));
        ASSERT_EQ(test_write_checkpoint_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                             manifest, size), 0);
        ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_OVERLOAD);
        manifest[44] = 11u;
        manifest[45] = 0u;
        manifest[46] = 0u;
        manifest[47] = 0u;
        ASSERT_EQ(test_write_checkpoint_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                             manifest, size), 0);
        ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_OK);
    }
    manifest[64 + 13 + 1] = 1u;
    ASSERT_EQ(test_write_checkpoint_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                         manifest, size), 0);
    ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_INVALID);
    manifest[64 + 13 + 1] = 0u;
    manifest[64 + 2] = 0u;
    ASSERT_EQ(test_write_checkpoint_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                         manifest, size), 0);
    ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_INVALID);
    free(manifest);
    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(TEST_RMDIR(dir), 0);
}

static void test_assert_reserved_manifest_alias(const char *dir,
        CoreAppCheckpointFile *file, u64 old_hash, const u8 *old_manifest,
        usize old_manifest_size, const u8 *payload, u8 **new_manifest) {
    *new_manifest = NULL;
#if !defined(_WIN32)
    ASSERT_EQ(test_hard_link_checkpoint_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                             file->name), 0);
    ASSERT_EQ(test_write_checkpoint_file(dir, file->name, payload, file->size), 0);
#else
    (void)payload;
#endif
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, file, 1u, 2u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(core_app_checkpoint_manifest_hash(dir), old_hash);
    usize new_manifest_size = 0u;
    *new_manifest = test_read_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                   TEST_MANIFEST_CAP, &new_manifest_size);
    ASSERT_NOT_NULL(*new_manifest);
    ASSERT_EQ(new_manifest_size, old_manifest_size);
    ASSERT_EQ(memcmp(*new_manifest, old_manifest, old_manifest_size), 0);
}

TEST(checkpoint_reserved_manifest_aliases_are_rejected_without_touching_old_generation) {
    static const char *const aliases[] = {"MANIFEST.CORE", "manifest.core."};
    const u8 payload[] = {1u, 2u, 3u, 4u};
    for (usize i = 0; i < sizeof(aliases) / sizeof(aliases[0]); ++i) {
        char dir[512];
        test_tmp(dir, sizeof(dir), "core_app_checkpoint_manifest_alias");
        ASSERT_EQ(prepare_directory(dir), 0);
        CoreAppCheckpointFile file = {.kind = 1u, .size = sizeof(payload),
                                  .hash = 0u, .name = "runtime_1.bin"};
        file.hash = test_fnv1a64(payload, sizeof(payload));
        ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
        ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 1u, 1u), BREAK_RUNTIME_OK);
        u64 old_hash = core_app_checkpoint_manifest_hash(dir);
        usize old_manifest_size = 0u;
        u8 *old_manifest = test_read_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                          TEST_MANIFEST_CAP, &old_manifest_size);
        ASSERT_NOT_NULL(old_manifest);
        strcpy(file.name, aliases[i]);
        u8 *new_manifest = NULL;
        int failures_before = g_test_fail;
        test_assert_reserved_manifest_alias(dir, &file, old_hash, old_manifest,
                                            old_manifest_size, payload, &new_manifest);
        free(new_manifest);
        free(old_manifest);
        if (g_test_fail != failures_before) return;
        ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_OK);
        ASSERT_TRUE(file_exists(dir, "runtime_1.bin"));
        ASSERT_EQ(prepare_directory(dir), 0);
        ASSERT_EQ(TEST_RMDIR(dir), 0);
    }
}

TEST(checkpoint_old_payload_case_and_trailing_dot_aliases_are_rejected) {
    static const char *const aliases[] = {"RUNTIME_1.BIN", "runtime_1.bin."};
    const u8 payload[] = {1u, 2u, 3u, 4u};
    for (usize i = 0; i < sizeof(aliases) / sizeof(aliases[0]); ++i) {
        char dir[512];
        test_tmp(dir, sizeof(dir), "core_app_checkpoint_payload_alias");
        ASSERT_EQ(prepare_directory(dir), 0);
        CoreAppCheckpointFile file = {.kind = 1u, .size = sizeof(payload),
                                  .hash = 0u, .name = "runtime_1.bin"};
        file.hash = test_fnv1a64(payload, sizeof(payload));
        ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
        ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 1u, 1u), BREAK_RUNTIME_OK);
        u64 old_hash = core_app_checkpoint_manifest_hash(dir);
        strcpy(file.name, aliases[i]);
#if !defined(_WIN32)
        ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
#endif
        ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 1u, 2u),
                  BREAK_RUNTIME_INVALID);
        ASSERT_EQ(core_app_checkpoint_manifest_hash(dir), old_hash);
        ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_OK);
        ASSERT_TRUE(file_exists(dir, "runtime_1.bin"));
        ASSERT_TRUE(file_exists(dir, aliases[i]));
        ASSERT_EQ(prepare_directory(dir), 0);
        ASSERT_EQ(TEST_RMDIR(dir), 0);
    }
}

TEST(checkpoint_duplicate_names_use_case_insensitive_comparison) {
    char dir[512];
    test_tmp(dir, sizeof(dir), "core_app_checkpoint_duplicate_alias");
    ASSERT_EQ(prepare_directory(dir), 0);
    const u8 payload[] = {1u, 2u, 3u, 4u};
    CoreAppCheckpointFile old = {.kind = 1u, .size = sizeof(payload),
                             .hash = 0u, .name = "runtime_1.bin"};
    old.hash = test_fnv1a64(payload, sizeof(payload));
    ASSERT_EQ(test_write_checkpoint_file(dir, old.name, payload, sizeof(payload)), 0);
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &old, 1u, 1u), BREAK_RUNTIME_OK);
    u64 old_hash = core_app_checkpoint_manifest_hash(dir);
    CoreAppCheckpointFile files[2];
    memset(files, 0, sizeof(files));
    for (u32 i = 0; i < 2u; ++i) {
        files[i].kind = 1u;
        files[i].size = sizeof(payload);
        files[i].hash = old.hash;
    }
    strcpy(files[0].name, "state_2.bin");
    strcpy(files[1].name, "STATE_2.BIN");
#if !defined(_WIN32)
    for (u32 i = 0; i < 2u; ++i)
        ASSERT_EQ(test_write_checkpoint_file(dir, files[i].name, payload,
                                             sizeof(payload)), 0);
#endif
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, files, 2u, 2u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(core_app_checkpoint_manifest_hash(dir), old_hash);
    ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_OK);
    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(TEST_RMDIR(dir), 0);
}

#if !defined(_WIN32)
static volatile sig_atomic_t g_sigxfsz_seen;
static void on_sigxfsz(int signal_number) {
    (void)signal_number;
    g_sigxfsz_seen = 1;
}

TEST(checkpoint_mid_write_failure_preserves_old_manifest_and_removes_new_payload) {
    char dir[512];
    test_tmp(dir, sizeof(dir), "core_app_checkpoint_write_failure");
    ASSERT_EQ(prepare_directory(dir), 0);
    const u8 payload[] = {1u, 2u, 3u, 4u};
    CoreAppCheckpointFile file = {.kind = 1u, .size = sizeof(payload),
                              .hash = 0u, .name = "runtime_1.bin"};
    file.hash = test_fnv1a64(payload, sizeof(payload));
    ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 1u, 1u), BREAK_RUNTIME_OK);
    usize before_size = 0;
    u8 *before = test_read_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                TEST_MANIFEST_CAP, &before_size);
    ASSERT_NOT_NULL(before);
    ASSERT_TRUE(before_size > 1u);
    strcpy(file.name, "runtime_2.bin");
    ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);

    struct sigaction action, previous_action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = on_sigxfsz;
    sigemptyset(&action.sa_mask);
    ASSERT_EQ(sigaction(SIGXFSZ, &action, &previous_action), 0);
    struct rlimit previous_limit;
    ASSERT_EQ(getrlimit(RLIMIT_FSIZE, &previous_limit), 0);
    struct rlimit limit = previous_limit;
    limit.rlim_cur = (rlim_t)(before_size - 1u);
    g_sigxfsz_seen = 0;
    int limited = setrlimit(RLIMIT_FSIZE, &limit) == 0;
    CoreAppCheckpointCommitResult commit = CORE_APP_CHECKPOINT_COMMIT_NOT_COMMITTED;
    BreakRuntimeError result = limited
        ? core_app_checkpoint_write_manifest_ex(dir, &file, 1u, 2u, &commit)
        : BREAK_RUNTIME_FAILED;
    int restored = setrlimit(RLIMIT_FSIZE, &previous_limit);
    sigaction(SIGXFSZ, &previous_action, NULL);

    ASSERT_TRUE(limited);
    ASSERT_EQ(restored, 0);
    ASSERT_TRUE(g_sigxfsz_seen);
    ASSERT_EQ(result, BREAK_RUNTIME_FAILED);
    ASSERT_EQ(commit, CORE_APP_CHECKPOINT_COMMIT_NOT_COMMITTED);
    usize after_size = 0;
    u8 *after = test_read_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                               TEST_MANIFEST_CAP, &after_size);
    ASSERT_NOT_NULL(after);
    ASSERT_EQ(after_size, before_size);
    ASSERT_TRUE(memcmp(after, before, before_size) == 0);
    ASSERT_FALSE(file_exists(dir, "runtime_2.bin"));
    ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_OK);
    free(before);
    free(after);
    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(TEST_RMDIR(dir), 0);
}

#if defined(CORE_APP_TEST_WRAP_FS)
TEST(checkpoint_directory_failure_reports_visible_durability_unknown) {
    char dir[512];
    test_tmp(dir, sizeof(dir), "core_app_checkpoint_post_rename_restore");
    ASSERT_EQ(prepare_directory(dir), 0);
    const u8 payload[] = {1u, 2u, 3u, 4u};
    CoreAppCheckpointFile file = {.kind = 1u, .size = sizeof(payload),
                              .hash = 0u, .name = "runtime_1.bin"};
    file.hash = test_fnv1a64(payload, sizeof(payload));
    ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 1u, 1u), BREAK_RUNTIME_OK);
    usize before_size = 0;
    u8 *before = test_read_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                TEST_MANIFEST_CAP, &before_size);
    ASSERT_NOT_NULL(before);
    strcpy(file.name, "runtime_2.bin");
    ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
    fs_fault_post_rename(false);
    CoreAppCheckpointCommitResult commit = CORE_APP_CHECKPOINT_COMMIT_NOT_COMMITTED;
    BreakRuntimeError result = core_app_checkpoint_write_manifest_ex(dir, &file, 1u, 2u,
                                                                 &commit);
    u32 injected = g_dir_fsync_failed;
    u32 renames = g_rename_calls;
    u32 restore_writes = g_restore_write_failed;
    fs_fault_reset();
    ASSERT_EQ(injected, 1u);
    ASSERT_EQ(renames, 1u);
    ASSERT_EQ(restore_writes, 0u);
    ASSERT_EQ(result, BREAK_RUNTIME_OK);
    ASSERT_EQ(commit, CORE_APP_CHECKPOINT_COMMIT_VISIBLE_DURABILITY_UNKNOWN);
    usize after_size = 0;
    u8 *after = test_read_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                               TEST_MANIFEST_CAP, &after_size);
    ASSERT_NOT_NULL(after);
    ASSERT_EQ(after_size, before_size);
    ASSERT_TRUE(memcmp(after, before, before_size) != 0);
    ASSERT_EQ(read_u64(after + 24), 2u);
    ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_OK);
    ASSERT_TRUE(file_exists(dir, "runtime_2.bin"));
    free(before);
    free(after);
    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(TEST_RMDIR(dir), 0);
}

TEST(checkpoint_legacy_directory_failure_returns_logical_ok_and_keeps_payload) {
    char dir[512], backup[512];
    test_tmp(dir, sizeof(dir), "core_app_checkpoint_restore_write_failure");
    test_tmp(backup, sizeof(backup), "core_app_checkpoint_restore_failure_backup");
    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(prepare_directory(backup), 0);
    const u8 payload[] = {1u, 2u, 3u, 4u};
    CoreAppCheckpointFile file = {.kind = 1u, .size = sizeof(payload),
                              .hash = 0u, .name = "runtime_1.bin"};
    file.hash = test_fnv1a64(payload, sizeof(payload));
    ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 1u, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(test_copy_checkpoint(dir, backup), 0);
    usize before_size = 0;
    u8 *before = test_read_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                TEST_MANIFEST_CAP, &before_size);
    ASSERT_NOT_NULL(before);
    strcpy(file.name, "runtime_2.bin");
    ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
    fs_fault_post_rename(true);
    BreakRuntimeError result = core_app_checkpoint_write_manifest(dir, &file, 1u, 2u);
    u32 dir_injected = g_dir_fsync_failed;
    u32 write_injected = g_restore_write_failed;
    u32 renames = g_rename_calls;
    fs_fault_reset();
    ASSERT_EQ(dir_injected, 1u);
    ASSERT_EQ(write_injected, 0u);
    ASSERT_EQ(renames, 1u);
    ASSERT_EQ(result, BREAK_RUNTIME_OK);
    usize after_size = 0;
    u8 *after = test_read_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                               TEST_MANIFEST_CAP, &after_size);
    ASSERT_NOT_NULL(after);
    ASSERT_EQ(after_size, before_size);
    ASSERT_TRUE(memcmp(after, before, before_size) != 0);
    ASSERT_EQ(read_u64(after + 24), 2u);
    ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_OK);
    ASSERT_TRUE(file_exists(dir, "runtime_2.bin"));
    ASSERT_EQ(core_app_checkpoint_probe(backup), BREAK_RUNTIME_OK);
    free(before);
    free(after);
    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(prepare_directory(backup), 0);
    ASSERT_EQ(TEST_RMDIR(dir), 0);
    ASSERT_EQ(TEST_RMDIR(backup), 0);
}

TEST(checkpoint_directory_failure_with_corrupt_old_commits_new_and_keeps_backup) {
    char dir[512], backup[512];
    test_tmp(dir, sizeof(dir), "core_app_checkpoint_corrupt_old_post_rename");
    test_tmp(backup, sizeof(backup), "core_app_checkpoint_corrupt_old_backup");
    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(prepare_directory(backup), 0);
    const u8 payload[] = {1u, 2u, 3u, 4u};
    CoreAppCheckpointFile file = {.kind = 1u, .size = sizeof(payload),
                              .hash = 0u, .name = "runtime_1.bin"};
    file.hash = test_fnv1a64(payload, sizeof(payload));
    ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 1u, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(test_copy_checkpoint(dir, backup), 0);
    usize before_size = 0;
    u8 *before = test_read_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                TEST_MANIFEST_CAP, &before_size);
    ASSERT_NOT_NULL(before);
    before[36] = 1u;
    ASSERT_EQ(test_write_checkpoint_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                         before, before_size), 0);
    ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_INVALID);
    strcpy(file.name, "runtime_2.bin");
    ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
    fs_fault_post_rename(false);
    CoreAppCheckpointCommitResult commit = CORE_APP_CHECKPOINT_COMMIT_NOT_COMMITTED;
    BreakRuntimeError result = core_app_checkpoint_write_manifest_ex(dir, &file, 1u, 2u,
                                                                 &commit);
    u32 injected = g_dir_fsync_failed;
    u32 renames = g_rename_calls;
    fs_fault_reset();
    ASSERT_EQ(injected, 1u);
    ASSERT_EQ(renames, 1u);
    ASSERT_EQ(result, BREAK_RUNTIME_OK);
    ASSERT_EQ(commit, CORE_APP_CHECKPOINT_COMMIT_VISIBLE_DURABILITY_UNKNOWN);
    usize after_size = 0;
    u8 *after = test_read_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                               TEST_MANIFEST_CAP, &after_size);
    ASSERT_NOT_NULL(after);
    ASSERT_EQ(after_size, before_size);
    ASSERT_TRUE(memcmp(after, before, before_size) != 0);
    ASSERT_EQ(read_u64(after + 24), 2u);
    ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_OK);
    ASSERT_EQ(core_app_checkpoint_probe(backup), BREAK_RUNTIME_OK);
    ASSERT_TRUE(file_exists(dir, "runtime_1.bin"));
    ASSERT_TRUE(file_exists(dir, "runtime_2.bin"));
    free(before);
    free(after);
    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(prepare_directory(backup), 0);
    ASSERT_EQ(TEST_RMDIR(dir), 0);
    ASSERT_EQ(TEST_RMDIR(backup), 0);
}

static void test_checkpoint_pre_rename_fault(bool rename_failure) {
    char dir[512];
    test_tmp(dir, sizeof(dir), rename_failure ? "core_app_checkpoint_rename_failure"
                                               : "core_app_checkpoint_file_fsync_failure");
    ASSERT_EQ(prepare_directory(dir), 0);
    const u8 payload[] = {1u, 2u, 3u, 4u};
    CoreAppCheckpointFile file = {.kind = 1u, .size = sizeof(payload),
                              .hash = 0u, .name = "runtime_1.bin"};
    file.hash = test_fnv1a64(payload, sizeof(payload));
    ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
    ASSERT_EQ(core_app_checkpoint_write_manifest(dir, &file, 1u, 1u), BREAK_RUNTIME_OK);
    usize before_size = 0;
    u8 *before = test_read_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                                TEST_MANIFEST_CAP, &before_size);
    ASSERT_NOT_NULL(before);
    strcpy(file.name, "runtime_2.bin");
    ASSERT_EQ(test_write_checkpoint_file(dir, file.name, payload, sizeof(payload)), 0);
    fs_fault_reset();
    if (rename_failure) {
        g_rename_failures = 1u;
    } else {
        g_file_fsync_failures = 1u;
    }
    CoreAppCheckpointCommitResult commit = CORE_APP_CHECKPOINT_COMMIT_NOT_COMMITTED;
    BreakRuntimeError result = core_app_checkpoint_write_manifest_ex(dir, &file, 1u, 2u,
                                                                 &commit);
    u32 injected = rename_failure ? g_rename_failed : g_file_fsync_failed;
    u32 renames = g_rename_calls;
    fs_fault_reset();
    ASSERT_EQ(injected, 1u);
    ASSERT_EQ(renames, 0u);
    ASSERT_EQ(result, BREAK_RUNTIME_FAILED);
    ASSERT_EQ(commit, CORE_APP_CHECKPOINT_COMMIT_NOT_COMMITTED);
    usize after_size = 0;
    u8 *after = test_read_file(dir, CORE_APP_CHECKPOINT_MANIFEST_NAME,
                               TEST_MANIFEST_CAP, &after_size);
    ASSERT_NOT_NULL(after);
    ASSERT_EQ(after_size, before_size);
    ASSERT_TRUE(memcmp(after, before, before_size) == 0);
    ASSERT_EQ(core_app_checkpoint_probe(dir), BREAK_RUNTIME_OK);
    ASSERT_FALSE(file_exists(dir, "runtime_2.bin"));
    free(before);
    free(after);
    ASSERT_EQ(prepare_directory(dir), 0);
    ASSERT_EQ(TEST_RMDIR(dir), 0);
}

TEST(checkpoint_file_fsync_failure_is_not_committed_and_preserves_old_generation) {
    test_checkpoint_pre_rename_fault(false);
}

TEST(checkpoint_rename_failure_is_not_committed_and_preserves_old_generation) {
    test_checkpoint_pre_rename_fault(true);
}
#endif
#endif

TEST_MAIN_BEGIN()
    RUN_TEST(baker_emits_every_formal_asset_byte_identically);
    RUN_TEST(baker_supports_spaces_in_output_path);
    RUN_TEST(formal_assets_match_fresh_baker);
    RUN_TEST(scene_and_actor_sidecar_roundtrip_through_p1_reader);
    RUN_TEST(flow_deserializes_enter_delay_add_item_chain);
    RUN_TEST(animation_decodes_within_public_error_bounds);
    RUN_TEST(wav_is_canonical_44100_hz_mono_pcm16);
    RUN_TEST(lua_assets_execute_and_broken_source_is_rejected);
    RUN_TEST(checkpoint_manifest_is_versioned_little_endian_and_detects_corruption);
    RUN_TEST(checkpoint_rejects_legacy_magic);
    RUN_TEST(checkpoint_rejects_legacy_manifest_name);
    RUN_TEST(checkpoint_basename_63_is_valid_and_64_is_overload);
    RUN_TEST(checkpoint_manifest_name_length_overload_is_distinct_from_corruption);
    RUN_TEST(checkpoint_rejects_unsafe_names_and_overflow_before_commit);
    RUN_TEST(checkpoint_reserved_manifest_aliases_are_rejected_without_touching_old_generation);
    RUN_TEST(checkpoint_old_payload_case_and_trailing_dot_aliases_are_rejected);
    RUN_TEST(checkpoint_duplicate_names_use_case_insensitive_comparison);
#if !defined(_WIN32)
    RUN_TEST(checkpoint_mid_write_failure_preserves_old_manifest_and_removes_new_payload);
#endif
#if defined(CORE_APP_TEST_WRAP_FS)
    RUN_TEST(checkpoint_directory_failure_reports_visible_durability_unknown);
    RUN_TEST(checkpoint_legacy_directory_failure_returns_logical_ok_and_keeps_payload);
    RUN_TEST(checkpoint_directory_failure_with_corrupt_old_commits_new_and_keeps_backup);
    RUN_TEST(checkpoint_file_fsync_failure_is_not_committed_and_preserves_old_generation);
    RUN_TEST(checkpoint_rename_failure_is_not_committed_and_preserves_old_generation);
#endif
TEST_MAIN_END()
