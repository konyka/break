# Platform Filesystem & Threading Abstraction — Design Spec

**Scope:** First milestone of cross-platform compatibility hardening. Remove the largest unguarded POSIX surface and Windows stubs without touching the RHI monoliths.

**Goals:**
1. Provide a single `engine/src/platform/file.h` API for filesystem operations that currently require `#ifdef _WIN32` / POSIX splits.
2. Make `engine/src/task/task.c` reuse the existing `engine/src/core/platform_thread.h` abstraction instead of re-implementing mutex/thread wrappers.
3. Migrate all in-tree call sites to the new abstractions.
4. Cover new behavior with TDD unit tests.
5. Update `docs/Build_Guide.md` and `docs/Implementation_Status.md` to reflect the change.

## Non-goals

- Splitting `rhi_gl.c` / `rhi_vk.c` per platform.
- Abstracting console colors or adding a logging backend.
- Adding install/packaging targets.
- macOS Cocoa runtime validation.

## Architecture

```
engine/src/platform/file.h          ← public contract
engine/src/platform/file.c          ← POSIX + Win32 implementations
engine/src/core/platform_thread.h   ← existing header-only threading contract
engine/src/task/task.c              ← use platform_thread.h instead of local wrappers
engine/tests/test_platform_file.c   ← new TDD tests
```

## API

All functions use C11 `bool` and engine types (`u64`, `u32`).

```c
bool platform_mkdir(const char *path);
bool platform_file_exists(const char *path);
bool platform_file_is_directory(const char *path);
bool platform_file_is_regular(const char *path);
bool platform_file_size(const char *path, u64 *out_size);
u64  platform_file_mtime(const char *path);   /* seconds since epoch, 0 = missing/error */
bool platform_file_remove(const char *path);

typedef void (*PlatformDirVisitor)(const char *rel_path,
                                   const char *abs_path,
                                   bool is_directory,
                                   void *user);

/* Walks directory recursively. Returns false if dir cannot be opened.
 * Visitor is called for every entry except "." and "..".
 * Paths use '/' separators on all platforms (consistent with VFS). */
bool platform_dir_foreach(const char *base_dir,
                          const char *rel_prefix,
                          PlatformDirVisitor visitor,
                          void *user);
```

## Semantics

- `platform_mkdir(path)` creates a single directory. It is **not** `mkdir -p`.
- `platform_file_exists` returns true for files and directories.
- `platform_file_is_directory` / `platform_file_is_regular` return false on error or mismatch.
- `platform_file_size` returns false and leaves `*out_size` unchanged on error.
- `platform_file_mtime` returns 0 on error or if the path does not exist.
- `platform_dir_foreach` builds relative paths with `/` separators, matching the VFS convention used by `packer` and `verify_pak`.

## Call-site migrations

| File | Current platform split | New call |
|---|---|---|
| `engine/src/network/net_replication.c` | `net_repl_mkdir_p` POSIX-only; `net_repl_peer_remove_stale_files` no-op on Windows | `platform_mkdir`, `platform_dir_foreach`, `platform_file_is_regular`, `platform_file_remove` |
| `engine/src/script/script.c` | `file_mtime()` uses `<sys/stat.h>` unconditionally | `platform_file_mtime()` |
| `engine/src/test_vulkan.c` | inline `#ifdef _WIN32` for `mkdir`/`_mkdir` | `platform_mkdir()` |
| `engine/tools/packer.c` | `get_file_size`, `is_directory`, `is_regular_file`, `scan_dir` have `#ifdef _WIN32` blocks | `platform_file_size`, `platform_file_is_directory`, `platform_file_is_regular`, `platform_dir_foreach` |
| `engine/tools/verify_pak.c` | `verify_dir` has `#ifdef _WIN32` block | `platform_dir_foreach` |
| `engine/src/task/task.c` | local `platform_mutex_*` / `platform_thread_*` wrappers | `platform_thread.h` primitives |

## Threading changes

`task.c` currently defines its own `platform_mutex_init(void *storage)`, `platform_thread_create(void *handle_out, ...)`, etc. These duplicate `platform_thread.h`.

Change:
- Include `<core/platform_thread.h>`.
- Replace internal `Mutex` / `Thread` storage with `PlatformMutex` / `PlatformThread`.
- Replace inline wrappers with `platform_mutex_*`, `platform_thread_create`, `platform_thread_join`.
- Keep `platform_sleep_ns` and `platform_cpu_count` as small static helpers (they are not in `platform_thread.h`).

## Error handling

- All file functions return `false` / `0` on failure; callers log via `LOG_*` where appropriate.
- No exceptions, no `errno` leakage to callers.
- Internal POSIX branch may inspect `errno` to distinguish missing files from permission errors but does not expose it.

## Testing

New test file `engine/tests/test_platform_file.c` (TDD):

1. `test_mkdir_creates_directory` — RED: call `platform_mkdir` on a temp path, assert directory exists.
2. `test_file_mtime_updates_after_write` — write a temp file, get mtime, assert non-zero.
3. `test_dir_foreach_visits_files` — create nested temp dirs/files, assert visitor sees expected entries.
4. `test_file_size_matches_written_bytes` — write known bytes, assert size.

Existing tests must still pass:
- `ctest --test-dir build -LE graphics --output-on-failure`
- Build `packer` and `verify_pak` on Linux.

## Documentation updates

- `docs/Build_Guide.md`: update the “Windows 平台验证” TODO to note that filesystem and task threading abstractions are now in place.
- `docs/Implementation_Status.md`: add an entry under the current round describing the platform abstraction milestone and test coverage.

## Open questions / future work

- MSVC native runtime validation remains environment-dependent.
- RHI platform split is intentionally deferred to a later milestone.
