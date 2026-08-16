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
 * Relative paths produced by the visitor use '/' on all platforms. */
bool platform_dir_foreach(const char *base_dir,
                          const char *rel_prefix,
                          PlatformDirVisitor visitor,
                          void *user);
