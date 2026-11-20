#ifndef TEST_QNX_SPAWN_H
#define TEST_QNX_SPAWN_H

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(_WIN32)
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
extern char **environ;
#endif

#if defined(__QNXNTO__)
#include <spawn.h>
#endif

#if defined(__GNUC__) || defined(__clang__)
#define TEST_QNX_SPAWN_MAYBE_UNUSED __attribute__((unused))
#else
#define TEST_QNX_SPAWN_MAYBE_UNUSED
#endif

#if !defined(_WIN32)
static TEST_QNX_SPAWN_MAYBE_UNUSED char **
test_qnx_spawn_child_envp(const char *normal_child)
{
    char **copy;
    size_t count = 0;
    size_t source;
    size_t destination = 0;
    if (normal_child == NULL || normal_child[0] == '\0' ||
        getenv("LD_PRELOAD") == NULL) {
        return environ;
    }
    while (environ[count] != NULL) ++count;
    copy = (char **)malloc((count + 1) * sizeof(*copy));
    if (copy == NULL) return NULL;
    for (source = 0; source < count; ++source) {
        if (strncmp(environ[source], "LD_PRELOAD=", 11) != 0) {
            copy[destination++] = environ[source];
        }
    }
    copy[destination] = NULL;
    return copy;
}

static TEST_QNX_SPAWN_MAYBE_UNUSED void
test_qnx_spawn_child_envp_destroy(char **envp)
{
    if (envp != NULL && envp != environ) free(envp);
}
#endif

#if !defined(TEST_QNX_SPAWN_HELPERS_ONLY)
#define TEST_QNX_SPAWN_CHILD_ARG "--test-qnx-death-child"

static const char *test_qnx_spawn_program_path;

static int test_qnx_spawn_death_child(int (*child_main)(void))
{
    fflush(NULL);
#if defined(__QNXNTO__)
    posix_spawnattr_t attributes;
    char *arguments[3];
    char **child_envp;
    pid_t child = -1;
    int result = posix_spawnattr_init(&attributes);
    if (result != 0) {
        printf("\n  posix_spawnattr_init failed: error=%d (%s)\n",
               result, strerror(result));
        return -1;
    }
    result = posix_spawnattr_setaslr(&attributes, POSIX_SPAWN_ASLR_DISABLE);
    if (result != 0) {
        printf("\n  posix_spawnattr_setaslr failed: error=%d (%s)\n",
               result, strerror(result));
        (void)posix_spawnattr_destroy(&attributes);
        return -1;
    }
    arguments[0] = (char *)test_qnx_spawn_program_path;
    arguments[1] = (char *)TEST_QNX_SPAWN_CHILD_ARG;
    arguments[2] = NULL;
    child_envp = test_qnx_spawn_child_envp(getenv("BREAK_QNX_DEATH_CHILD"));
    if (child_envp == NULL) {
        result = ENOMEM;
    } else {
        result = posix_spawn(&child, test_qnx_spawn_program_path, NULL, &attributes,
                             arguments, child_envp);
    }
    test_qnx_spawn_child_envp_destroy(child_envp);
    (void)posix_spawnattr_destroy(&attributes);
    if (result != 0) {
        printf("\n  posix_spawn failed: error=%d (%s)\n", result, strerror(result));
        return -1;
    }
    return child;
#elif !defined(_WIN32)
    pid_t child = fork();
    if (child < 0) {
        int fork_errno = errno;
        printf("\n  fork failed: errno=%d (%s)\n", fork_errno, strerror(fork_errno));
    }
    if (child == 0) _exit(child_main());
    return child;
#else
    (void)child_main;
    return -1;
#endif
}

#define TEST_QNX_SPAWN_MAIN_BEGIN(child_main) \
    int main(int argc, char **argv) { \
        const char *child_override = getenv("BREAK_QNX_DEATH_CHILD"); \
        test_qnx_spawn_program_path = child_override != NULL && child_override[0] != '\0' \
            ? child_override : argv[0]; \
        if (argc == 2 && strcmp(argv[1], TEST_QNX_SPAWN_CHILD_ARG) == 0) { \
            return child_main(); \
        } \
        printf("=== Running Tests ===\n");
#endif

#endif
