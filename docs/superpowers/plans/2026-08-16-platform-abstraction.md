# Platform Filesystem & Threading Abstraction Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use `superpowers:executing-plans` (inline execution in this session) or `superpowers:subagent-driven-development`. Tasks are sequential and tightly coupled through the new `file.h` API, so inline execution is acceptable.

**Goal:** Create a cross-platform filesystem abstraction in `engine/src/platform/file.h/.c`, migrate all unguarded POSIX/Win32 call sites, unify `task.c` on `platform_thread.h`, cover with TDD tests, update docs, and push branch `feat/platform-abstraction`.

**Architecture:** A single `platform_file.h` API hides POSIX `stat`/`mkdir`/`opendir` and Win32 `GetFileAttributes`/`FindFirstFile`/`_mkdir` behind `bool` C11 functions. `task.c` replaces its local mutex/thread wrappers with the existing header-only `platform_thread.h` primitives. Callers in `net_replication.c`, `script.c`, `test_vulkan.c`, `packer.c`, and `verify_pak.c` drop their `#ifdef` blocks.

**Tech Stack:** C11, CMake 3.20+, POSIX / Win32 APIs, engine `core/types.h`, `test_framework.h`.

## Global Constraints

- C11 standard; `-Wall -Wextra -Werror -pedantic` on GCC/Clang; `/W4 /WX` on MSVC.
- No new external dependencies.
- All new public functions live in `engine/src/platform/file.h` and are implemented in `engine/src/platform/file.c`.
- Paths produced by `platform_dir_foreach` use `/` separators on every platform.
- `platform_mkdir` is idempotent: returns `true` if the directory already exists.
- Tests must be written first (RED), then implementation (GREEN), then refactor.
- Each commit message follows the repo convention: `feat(platform): ...`, `test(platform): ...`, `docs: ...`, `refactor(task): ...`.
- Final verification: `ctest --test-dir build -LE graphics --output-on-failure` passes; `packer` and `verify_pak` build on Linux.

---

### Task 1: TDD scaffold for `platform_file`

**Files:**
- Create: `engine/tests/test_platform_file.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: `test_framework.h`, future `platform_file.h`/`file.c`.
- Produces: `test_platform_file` CMake target and CTest entry.

- [ ] **Step 1: Write the failing tests**

Create `engine/tests/test_platform_file.c`:

```c
#include "test_framework.h"
#include <platform/file.h>
#include <stdio.h>
#include <stdlib.h>

TEST(mkdir_creates_directory) {
    char path[256];
    test_tmp(path, sizeof(path), "mkdir");
    ASSERT_FALSE(platform_file_exists(path));
    ASSERT_TRUE(platform_mkdir(path));
    ASSERT_TRUE(platform_file_exists(path));
    ASSERT_TRUE(platform_file_is_directory(path));
    ASSERT_FALSE(platform_file_is_regular(path));
}

TEST(file_size_matches_written_bytes) {
    char dir[256], path[512];
    test_tmp(dir, sizeof(dir), "size");
    platform_mkdir(dir);
    snprintf(path, sizeof(path), "%s/test.bin", dir);
    const char data[] = "hello platform";
    FILE *f = fopen(path, "wb");
    ASSERT_NOT_NULL(f);
    fwrite(data, 1, sizeof(data) - 1, f);
    fclose(f);
    u64 sz = 0;
    ASSERT_TRUE(platform_file_size(path, &sz));
    ASSERT_EQ(sz, (u64)(sizeof(data) - 1));
}

TEST(file_mtime_nonzero_after_write) {
    char dir[256], path[512];
    test_tmp(dir, sizeof(dir), "mtime");
    platform_mkdir(dir);
    snprintf(path, sizeof(path), "%s/a.txt", dir);
    FILE *f = fopen(path, "wb");
    ASSERT_NOT_NULL(f);
    fwrite("x", 1, 1, f);
    fclose(f);
    u64 mt = platform_file_mtime(path);
    ASSERT_NEQ(mt, 0u);
}

static struct {
    int file_count;
    int dir_count;
    char seen_subfile;
} g_visitor_state;

static void test_visitor(const char *rel_path, const char *abs_path,
                         bool is_directory, void *user) {
    (void)rel_path;
    (void)abs_path;
    (void)user;
    if (is_directory) {
        g_visitor_state.dir_count++;
    } else {
        g_visitor_state.file_count++;
        if (strcmp(rel_path, "sub/inner.txt") == 0)
            g_visitor_state.seen_subfile = 1;
    }
}

TEST(dir_foreach_visits_nested_entries) {
    char dir[256], sub[512], file[512];
    test_tmp(dir, sizeof(dir), "foreach");
    platform_mkdir(dir);
    snprintf(sub, sizeof(sub), "%s/sub", dir);
    platform_mkdir(sub);
    snprintf(file, sizeof(file), "%s/sub/inner.txt", sub);
    FILE *f = fopen(file, "wb");
    ASSERT_NOT_NULL(f);
    fwrite("x", 1, 1, f);
    fclose(f);
    char top[512];
    snprintf(top, sizeof(top), "%s/top.txt", dir);
    f = fopen(top, "wb");
    ASSERT_NOT_NULL(f);
    fwrite("y", 1, 1, f);
    fclose(f);

    memset(&g_visitor_state, 0, sizeof(g_visitor_state));
    ASSERT_TRUE(platform_dir_foreach(dir, "", test_visitor, NULL));
    ASSERT_EQ(g_visitor_state.file_count, 2);
    ASSERT_EQ(g_visitor_state.dir_count, 1);
    ASSERT_EQ(g_visitor_state.seen_subfile, 1);
}

TEST_MAIN_BEGIN()
RUN_TEST(mkdir_creates_directory)
RUN_TEST(file_size_matches_written_bytes)
RUN_TEST(file_mtime_nonzero_after_write)
RUN_TEST(dir_foreach_visits_nested_entries)
TEST_MAIN_END()
```

- [ ] **Step 2: Wire the target into CMake**

Add after `test_vfs` block (around line 676) in `engine/CMakeLists.txt`:

```cmake
# test_platform_file: platform filesystem abstraction
add_executable(test_platform_file tests/test_platform_file.c src/platform/file.c)
target_include_directories(test_platform_file PRIVATE ${TEST_INCLUDE_DIRS})
target_link_libraries(test_platform_file PRIVATE m)
add_test(NAME test_platform_file COMMAND test_platform_file)
```

- [ ] **Step 3: Verify the build fails for the expected reason**

Run:
```bash
cd engine
cmake -S . -B build-verify-x11-gl
cmake --build build-verify-x11-gl --target test_platform_file
```

Expected: compile failure because `platform/file.h` and `src/platform/file.c` do not exist.

- [ ] **Step 4: Commit the failing-test scaffold**

```bash
git add engine/tests/test_platform_file.c engine/CMakeLists.txt
git commit -m "test(platform): scaffold platform_file TDD tests"
```

---

### Task 2: Implement `platform_file.h` and `platform_file.c`

**Files:**
- Create: `engine/src/platform/file.h`, `engine/src/platform/file.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: `core/types.h`.
- Produces: `platform_mkdir`, `platform_file_exists`, `platform_file_is_directory`, `platform_file_is_regular`, `platform_file_size`, `platform_file_mtime`, `platform_file_remove`, `platform_dir_foreach`.

- [ ] **Step 1: Write the header**

Create `engine/src/platform/file.h`:

```c
#pragma once
#include <core/types.h>
#include <stdbool.h>

bool platform_mkdir(const char *path);
bool platform_file_exists(const char *path);
bool platform_file_is_directory(const char *path);
bool platform_file_is_regular(const char *path);
bool platform_file_size(const char *path, u64 *out_size);
u64  platform_file_mtime(const char *path); /* seconds since epoch, 0 on error */
bool platform_file_remove(const char *path);

typedef void (*PlatformDirVisitor)(const char *rel_path,
                                   const char *abs_path,
                                   bool is_directory,
                                   void *user);

/* Recursively walk base_dir/rel_prefix. Skip "." and "..".
 * Relative paths use '/' on all platforms. */
bool platform_dir_foreach(const char *base_dir,
                          const char *rel_prefix,
                          PlatformDirVisitor visitor,
                          void *user);
```

- [ ] **Step 2: Write the implementation**

Create `engine/src/platform/file.c`:

```c
#include "platform/file.h"
#include <stdio.h>
#include <string.h>

#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
    #include <direct.h>
#else
    #include <sys/stat.h>
    #include <dirent.h>
    #include <errno.h>
    #include <unistd.h>
#endif

static bool join_path(char *out, size_t cap,
                      const char *a, const char *b, const char *c) {
    int n;
    if (b && b[0]) {
        if (c && c[0])
            n = snprintf(out, cap, "%s/%s/%s", a, b, c);
        else
            n = snprintf(out, cap, "%s/%s", a, b);
    } else {
        if (c && c[0])
            n = snprintf(out, cap, "%s/%s", a, c);
        else
            n = snprintf(out, cap, "%s", a);
    }
    return n >= 0 && (size_t)n < cap;
}

bool platform_mkdir(const char *path) {
#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    int rc = _mkdir(path);
    if (rc == 0) return true;
    return platform_file_is_directory(path);
#else
    if (mkdir(path, 0755) == 0) return true;
    if (errno == EEXIST)
        return platform_file_is_directory(path);
    return false;
#endif
}

bool platform_file_exists(const char *path) {
#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    DWORD attr = GetFileAttributesA(path);
    return attr != INVALID_FILE_ATTRIBUTES;
#else
    struct stat st;
    return stat(path, &st) == 0;
#endif
}

bool platform_file_is_directory(const char *path) {
#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    DWORD attr = GetFileAttributesA(path);
    return attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY);
#else
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
#endif
}

bool platform_file_is_regular(const char *path) {
#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    DWORD attr = GetFileAttributesA(path);
    return attr != INVALID_FILE_ATTRIBUTES &&
           !(attr & FILE_ATTRIBUTE_DIRECTORY);
#else
    struct stat st;
    return stat(path, &st) == 0 && S_ISREG(st.st_mode);
#endif
}

bool platform_file_size(const char *path, u64 *out_size) {
#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    WIN32_FILE_ATTRIBUTE_DATA attr;
    if (!GetFileAttributesExA(path, GetFileExInfoStandard, &attr))
        return false;
    *out_size = ((u64)attr.nFileSizeHigh << 32) | (u64)attr.nFileSizeLow;
    return true;
#else
    struct stat st;
    if (stat(path, &st) != 0) return false;
    *out_size = (u64)st.st_size;
    return true;
#endif
}

u64 platform_file_mtime(const char *path) {
#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    WIN32_FILE_ATTRIBUTE_DATA attr;
    if (!GetFileAttributesExA(path, GetFileExInfoStandard, &attr))
        return 0;
    u64 ft = ((u64)attr.ftLastWriteTime.dwHighDateTime << 32) |
             (u64)attr.ftLastWriteTime.dwLowDateTime;
    /* FILETIME is 100-ns intervals since 1601-01-01. Convert to Unix seconds. */
    if (ft < 116444736000000000ULL) return 0;
    return (ft - 116444736000000000ULL) / 10000000ULL;
#else
    struct stat st;
    if (stat(path, &st) != 0) return 0;
    return (u64)st.st_mtime;
#endif
}

bool platform_file_remove(const char *path) {
    return remove(path) == 0;
}

bool platform_dir_foreach(const char *base_dir,
                          const char *rel_prefix,
                          PlatformDirVisitor visitor,
                          void *user) {
    char dir_path[1024];
    if (!join_path(dir_path, sizeof(dir_path), base_dir, rel_prefix, NULL))
        return false;

#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    char pattern[1024];
    if (!join_path(pattern, sizeof(pattern), dir_path, "", "*"))
        return false;

    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pattern, &fd);
    if (h == INVALID_HANDLE_VALUE) return false;

    bool ok = true;
    do {
        if (fd.cFileName[0] == '.') continue;

        char rel[1024], abs[1024];
        if (!join_path(rel, sizeof(rel), rel_prefix, "", fd.cFileName) ||
            !join_path(abs, sizeof(abs), base_dir, rel, NULL)) {
            ok = false;
            break;
        }

        bool is_dir = (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
        visitor(rel, abs, is_dir, user);
        if (is_dir) {
            if (!platform_dir_foreach(base_dir, rel, visitor, user)) {
                ok = false;
                break;
            }
        }
    } while (FindNextFileA(h, &fd));

    FindClose(h);
    return ok;
#else
    DIR *d = opendir(dir_path);
    if (!d) return false;

    bool ok = true;
    struct dirent *ent;
    while ((ent = readdir(d)) != NULL) {
        if (ent->d_name[0] == '.') continue;

        char rel[1024], abs[1024];
        if (!join_path(rel, sizeof(rel), rel_prefix, "", ent->d_name) ||
            !join_path(abs, sizeof(abs), base_dir, rel, NULL)) {
            ok = false;
            break;
        }

        bool is_dir = platform_file_is_directory(abs);
        visitor(rel, abs, is_dir, user);
        if (is_dir) {
            if (!platform_dir_foreach(base_dir, rel, visitor, user)) {
                ok = false;
                break;
            }
        }
    }
    closedir(d);
    return ok;
#endif
}
```

- [ ] **Step 3: Add `file.c` to the engine library and tools**

In `engine/CMakeLists.txt`, add `src/platform/file.c` to the `add_library(engine STATIC ...)` list (near `src/platform/time.c`).

For `packer`, change:
```cmake
add_executable(packer tools/packer.c src/platform/file.c)
```
and add:
```cmake
target_include_directories(packer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)
```

For `verify_pak`, change:
```cmake
add_executable(verify_pak tools/verify_pak.c src/asset/vfs.c src/core/log.c src/platform/file.c)
```

- [ ] **Step 4: Run the new tests**

```bash
cd engine
cmake -S . -B build-verify-x11-gl
cmake --build build-verify-x11-gl --target test_platform_file
./build-verify-x11-gl/test_platform_file
```

Expected: all 4 tests pass.

- [ ] **Step 5: Commit**

```bash
git add engine/src/platform/file.h engine/src/platform/file.c engine/CMakeLists.txt
git commit -m "feat(platform): add cross-platform file abstraction"
```

---

### Task 3: Migrate `net_replication.c` to `platform_file`

**Files:**
- Modify: `engine/src/network/net_replication.c`

**Interfaces:**
- Consumes: `platform_file.h`.
- Produces: `net_repl_mkdir_p`, `net_repl_peer_remove_stale_files` with no platform `#ifdef`.

- [ ] **Step 1: Replace the platform-specific file I/O**

Replace the includes at the top:
```c
#include <platform/file.h>
```
Remove:
```c
#if !defined(ENGINE_PLATFORM_WINDOWS)
#  include <dirent.h>
#  include <sys/stat.h>
#endif
```

Replace `net_repl_mkdir_p` (lines 273-283) with:
```c
static bool net_repl_mkdir_p(const char *dir) {
    if (!dir || !dir[0]) return false;
    return platform_mkdir(dir);
}
```

Replace `net_repl_peer_remove_stale_files` (lines 295-337) with:
```c
typedef struct {
    const NetReplicator *rep;
    const char *dir;
    bool ok;
} NetReplStaleCtx;

static void net_repl_stale_visitor(const char *rel_path, const char *abs_path,
                                   bool is_directory, void *user) {
    NetReplStaleCtx *ctx = (NetReplStaleCtx *)user;
    if (!ctx->ok || is_directory) return;

    size_t name_len = strlen(rel_path);
    if (name_len < 10u || strncmp(rel_path, "peer_", 5u) != 0 ||
        strcmp(rel_path + name_len - 5u, ".peer") != 0)
        return;

    bool current = false;
    for (u32 i = 0u; i < ctx->rep->peer_count; i++) {
        char current_path[512];
        if (!net_repl_peer_file_path(current_path, sizeof(current_path), ctx->dir,
                                     i, &ctx->rep->peers[i])) {
            ctx->ok = false;
            return;
        }
        const char *current_name = strrchr(current_path, '/');
        current_name = current_name ? current_name + 1 : current_path;
        if (strcmp(rel_path, current_name) == 0) {
            current = true;
            break;
        }
    }
    if (current) return;

    if (platform_file_remove(abs_path) != 0)
        ctx->ok = false;
}

static bool net_repl_peer_remove_stale_files(const NetReplicator *rep, const char *dir) {
    NetReplStaleCtx ctx = { rep, dir, true };
    if (!platform_dir_foreach(dir, "", net_repl_stale_visitor, &ctx))
        return false;
    return ctx.ok;
}
```

- [ ] **Step 2: Run the relevant test**

```bash
cd engine
cmake --build build-verify-x11-gl --target test_net_replication
./build-verify-x11-gl/test_net_replication
```

Expected: passes.

- [ ] **Step 3: Commit**

```bash
git add engine/src/network/net_replication.c
git commit -m "refactor(platform): use platform_file in net_replication"
```

---

### Task 4: Migrate `script.c` `file_mtime` to `platform_file`

**Files:**
- Modify: `engine/src/script/script.c`

**Interfaces:**
- Consumes: `platform_file.h`.
- Produces: `script_reload_if_changed` no longer includes `<sys/stat.h>` directly.

- [ ] **Step 1: Replace the mtime helper**

Change includes:
```c
#include <platform/file.h>
```
Remove:
```c
#include <sys/stat.h>
```

Replace `file_mtime` (lines 245-249) with:
```c
static u32 file_mtime(const char *path) {
    return (u32)platform_file_mtime(path);
}
```

- [ ] **Step 2: Run the relevant test**

```bash
cd engine
cmake --build build-verify-x11-gl --target test_script
./build-verify-x11-gl/test_script
```

Expected: passes.

- [ ] **Step 3: Commit**

```bash
git add engine/src/script/script.c
git commit -m "refactor(platform): use platform_file_mtime in script hot-reload"
```

---

### Task 5: Migrate `test_vulkan.c` `mkdir` usage

**Files:**
- Modify: `engine/src/test_vulkan.c`

**Interfaces:**
- Consumes: `platform_file.h`.

- [ ] **Step 1: Replace the inline platform split**

Remove:
```c
#ifdef _WIN32
#include <direct.h>
#define tv_mkdir(p) _mkdir(p)
#else
#include <sys/stat.h>
#define tv_mkdir(p) mkdir(p, 0755)
#endif
```

Add with the other engine includes:
```c
#include <platform/file.h>
```

Replace `tv_mkdir("tests");` and `tv_mkdir("tests/golden");` (around lines 121-122) with:
```c
platform_mkdir("tests");
platform_mkdir("tests/golden");
```

- [ ] **Step 2: Verify it still compiles**

```bash
cd engine
cmake --build build-verify-x11-gl --target test_vulkan
```

Expected: builds successfully (the test itself needs a GPU/graphics environment to run).

- [ ] **Step 3: Commit**

```bash
git add engine/src/test_vulkan.c
git commit -m "refactor(platform): use platform_mkdir in test_vulkan"
```

---

### Task 6: Migrate `packer.c` to `platform_file`

**Files:**
- Modify: `engine/tools/packer.c`

**Interfaces:**
- Consumes: `platform_file.h`.

- [ ] **Step 1: Remove conflicting local types and platform splits**

Remove the local `typedef unsigned int u32;` etc. block (lines 18-20) and replace with:
```c
#include <core/types.h>
#include <platform/file.h>
```

Remove the `#ifdef _WIN32` includes block (lines 5-16) since `file.c` handles it. Keep `<stdio.h>`, `<stdlib.h>`, `<string.h>`.

Remove `get_file_size`, `is_directory`, `is_regular_file`, and the `#ifdef _WIN32` body of `scan_dir`. Replace `scan_dir` with a visitor:

```c
typedef struct {
    const char *base_dir;
} PackerCtx;

static void packer_visitor(const char *rel_path, const char *abs_path,
                           bool is_directory, void *user) {
    (void)user;
    if (!is_directory)
        add_file(rel_path, abs_path);
}

static void scan_dir(const char *base_dir, const char *rel_prefix) {
    (void)rel_prefix;
    platform_dir_foreach(base_dir, "", packer_visitor, NULL);
}
```

In `main`, the call `scan_dir(argv[i], "");` is still valid.

- [ ] **Step 2: Build and smoke-test**

```bash
cd engine
cmake --build build-verify-x11-gl --target packer
./build-verify-x11-gl/packer /tmp/test.pak engine/assets
```

Expected: builds, produces `/tmp/test.pak`.

- [ ] **Step 3: Commit**

```bash
git add engine/tools/packer.c engine/CMakeLists.txt
git commit -m "refactor(platform): use platform_file in packer"
```

---

### Task 7: Migrate `verify_pak.c` to `platform_file`

**Files:**
- Modify: `engine/tools/verify_pak.c`

**Interfaces:**
- Consumes: `platform_file.h`.

- [ ] **Step 1: Replace the directory walk**

Remove the `#ifdef _WIN32` includes block. Add:
```c
#include <platform/file.h>
```

Replace `verify_dir` (lines 106-189) with a visitor:

```c
typedef struct {
    VFS *vfs;
    const char *base_dir;
    int all_ok;
} VerifyCtx;

static void verify_visitor(const char *rel_path, const char *abs_path,
                           bool is_directory, void *user) {
    VerifyCtx *ctx = (VerifyCtx *)user;
    if (is_directory) return;
    if (!verify_file(ctx->vfs, rel_path, abs_path))
        ctx->all_ok = 0;
}

static int verify_dir(VFS *vfs, const char *base_dir, const char *rel_prefix) {
    (void)rel_prefix;
    VerifyCtx ctx = { vfs, base_dir, 1 };
    if (!platform_dir_foreach(base_dir, "", verify_visitor, &ctx))
        return 0;
    return ctx.all_ok;
}
```

- [ ] **Step 2: Build and smoke-test**

```bash
cd engine
cmake --build build-verify-x11-gl --target verify_pak
./build-verify-x11-gl/verify_pak /tmp/test.pak engine/assets
```

Expected: builds and reports `OK:` for each file.

- [ ] **Step 3: Commit**

```bash
git add engine/tools/verify_pak.c
git commit -m "refactor(platform): use platform_file in verify_pak"
```

---

### Task 8: Unify `task.c` on `platform_thread.h`

**Files:**
- Modify: `engine/src/task/task.h`, `engine/src/task/task.c`

**Interfaces:**
- Consumes: `core/platform_thread.h`.
- Produces: `Worker` and `TaskSystem` use `PlatformThread`/`PlatformMutex` directly.

- [ ] **Step 1: Update `task.h`**

Add after `#include <core/types.h>`:
```c
#include <core/platform_thread.h>
```

Replace the `Worker` thread-storage block (lines 63-67) with:
```c
    PlatformThread thread;
```

Replace `submit_mutex_storage` and `pool_mutex_storage` declarations (lines 86 and 97) with:
```c
    PlatformMutex submit_mutex_storage;
    PlatformMutex pool_mutex_storage;
```

- [ ] **Step 2: Update `task.c`**

Remove the entire `Platform Abstraction` block (lines 16-88). Keep `#include <stdlib.h>`, `<string.h>`, `<stdatomic.h>`.

Add:
```c
#include <core/platform_thread.h>
```

Remove the duplicate `<windows.h>`, `<process.h>`, `<pthread.h>`, `<time.h>`, `<unistd.h>` includes.

Keep `platform_sleep_ns` and `platform_cpu_count` as static helpers:
```c
#ifdef ENGINE_PLATFORM_WINDOWS
static inline void platform_sleep_ns(u32 ns) {
    DWORD ms = ns / 1000000;
    if (ms == 0 && ns > 0) { SwitchToThread(); }
    else { Sleep(ms); }
}
static inline u32 platform_cpu_count(void) {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return (u32)si.dwNumberOfProcessors;
}
#else
static inline void platform_sleep_ns(u32 ns) {
    struct timespec ts = { 0, (long)ns };
    nanosleep(&ts, NULL);
}
static inline u32 platform_cpu_count(void) {
    long n = sysconf(_SC_NPROCESSORS_ONLN);
    return n > 0 ? (u32)n : 1;
}
#endif
```

Unify `worker_entry`:
```c
static PLATFORM_THREAD_RET worker_entry(PLATFORM_THREAD_ARG arg) {
    Worker *self = (Worker *)arg;
    ...
    return PLATFORM_THREAD_RETURN;
}
```
Remove the existing `#ifdef ENGINE_PLATFORM_WINDOWS ... #else ... #endif` duplicate definitions.

Replace thread creation (around line 602):
```c
bool thread_ok = platform_thread_create(&w->thread, worker_entry, w);
```
Remove the `#ifdef ENGINE_PLATFORM_WINDOWS` around it.

Replace thread join (around line 668):
```c
platform_thread_join(w->thread);
```
Remove the `#ifdef` around it.

- [ ] **Step 3: Run task tests**

```bash
cd engine
cmake --build build-verify-x11-gl --target test_task test_task_singleton test_ecs_system
./build-verify-x11-gl/test_task
./build-verify-x11-gl/test_task_singleton
./build-verify-x11-gl/test_ecs_system
```

Expected: all pass.

- [ ] **Step 4: Commit**

```bash
git add engine/src/task/task.h engine/src/task/task.c
git commit -m "refactor(task): reuse platform_thread.h instead of local wrappers"
```

---

### Task 9: Update documentation

**Files:**
- Modify: `docs/Build_Guide.md`, `docs/Implementation_Status.md`

**Interfaces:**
- Consumes: spec and implementation results.

- [ ] **Step 1: Update `docs/Build_Guide.md`**

In the TODO section at the bottom (around line 445), change the first paragraph to:

```markdown
### 已完成的平台兼容性收口

- **文件系统抽象** — `engine/src/platform/file.h/.c` 统一封装 `mkdir` / `stat` / `opendir` / `FindFirstFile` / `_mkdir` 等平台差异；`net_replication.c`、`script.c`、`test_vulkan.c`、`packer.c`、`verify_pak.c` 已迁移。
- **线程原语统一** — `engine/src/task/task.c` 复用 `core/platform_thread.h`，移除本地重复的 CRITICAL_SECTION / pthread 包装。

### 待验证项
```

Keep the existing Windows runtime verification list below it.

- [ ] **Step 2: Update `docs/Implementation_Status.md`**

Add a new entry near the top (after the most recent round entry) with:

```markdown
**R562 平台文件与线程抽象收口（TDD）**：新增 `engine/src/platform/file.h/.c` 统一文件/目录操作，
替代 `net_replication.c`、`script.c`、`test_vulkan.c`、`packer.c`、`verify_pak.c` 中的 POSIX/Win32 分支；
`task.c` 改为复用已有的 `platform_thread.h` 头文件封装，删除本地重复的 mutex/thread 包装。
TDD 新增 `test_platform_file` 覆盖 `mkdir`、`file_size`、`file_mtime`、`dir_foreach`；
`test_task`、`test_task_singleton`、`test_ecs_system`、`test_net_replication`、`test_script`、
`packer` / `verify_pak` 构建与运行保持通过。Windows 原生运行时验证仍待真实 Windows 环境。
```

- [ ] **Step 3: Commit**

```bash
git add docs/Build_Guide.md docs/Implementation_Status.md
git commit -m "docs: document platform file and threading abstraction milestone"
```

---

### Task 10: Final verification and push

**Files:**
- None (verification + git).

- [ ] **Step 1: Full headless test run**

```bash
cd engine
cmake --build build-verify-x11-gl
ctest --test-dir build-verify-x11-gl -LE graphics --output-on-failure
```

Expected: all non-graphics tests pass (including `test_platform_file`).

- [ ] **Step 2: Verify tool builds**

```bash
cd engine
cmake --build build-verify-x11-gl --target packer verify_pak
```

Expected: both build.

- [ ] **Step 3: Push branch**

```bash
git push -u origin feat/platform-abstraction
```

- [ ] **Step 4: Report completion**

Summarize: branch, commits, tests passed, docs updated.

---

## Self-Review Checklist

- [ ] Spec coverage: every migrated file has a task.
- [ ] No placeholders: every step contains concrete code or commands.
- [ ] Type consistency: `platform_file_mtime` returns `u64`; `script.c` casts to `u32`.
- [ ] Test-first: Task 1 writes tests before file.c exists.
