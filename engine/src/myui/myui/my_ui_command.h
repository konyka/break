/**
 * @file my_ui_command.h
 * @brief Owned, loop-thread UI command submission.
 */
#ifndef MY_UI_COMMAND_H
#define MY_UI_COMMAND_H

#include "myc/my_error.h"
#include "myc/my_mem.h"
#include "mypal/my_pal.h"

typedef struct my_ui_command_t my_ui_command_t;
typedef struct my_ui_command_scope_t my_ui_command_scope_t;

/** @brief Command body; called only on the target loop thread. */
typedef my_ret_t (*my_ui_command_execute_fn)(void* context);

/** @brief Releases the command context exactly once. */
typedef void (*my_ui_command_context_destroy_fn)(void* context);

/** @brief Create a pending command with one caller-owned reference. */
my_ui_command_t* my_ui_command_create(
    const my_allocator_t* allocator, my_ui_command_execute_fn execute,
    void* context, my_ui_command_context_destroy_fn destroy_context);

/** @brief Retain a command reference. NULL-safe. */
my_ui_command_t* my_ui_command_ref(my_ui_command_t* command);

/** @brief Release a command reference. NULL-safe. */
void my_ui_command_unref(my_ui_command_t* command);

/** @brief Create a cancellation scope for a window or manager lifetime. */
my_ui_command_scope_t* my_ui_command_scope_create(
    const my_allocator_t* allocator);

/** @brief Retain a command scope. NULL-safe. */
my_ui_command_scope_t* my_ui_command_scope_ref(
    my_ui_command_scope_t* scope);

/** @brief Release a command scope. NULL-safe. */
void my_ui_command_scope_unref(my_ui_command_scope_t* scope);

/** @brief Cancel all queued commands currently owned by the scope. */
void my_ui_command_scope_close(my_ui_command_scope_t* scope);

/** @brief Reopen a scope for a new window lifetime. */
void my_ui_command_scope_reopen(my_ui_command_scope_t* scope);

/** @brief Return whether the scope rejects new submissions. */
bool my_ui_command_scope_is_closed(const my_ui_command_scope_t* scope);

/**
 * @brief Submit a command to a PAL loop without changing its vtable ABI.
 *
 * The caller keeps its reference and may unref immediately after this call.
 * The command runs at most once on the loop thread. Queue discard during loop
 * destruction releases the queue reference without invoking the command.
 */
my_ret_t my_ui_command_submit(my_pal_main_loop_t* loop,
                              my_ui_command_t* command);

/** @brief Submit a command tied to a scope's cancellation lifetime. */
my_ret_t my_ui_command_submit_scoped(my_pal_main_loop_t* loop,
                                     my_ui_command_scope_t* scope,
                                     my_ui_command_t* command);

/** @brief Cancel before execution; returns PENDING when already running. */
my_ret_t my_ui_command_cancel(my_ui_command_t* command);

/** @brief Return whether the command has been cancelled. */
bool my_ui_command_is_cancelled(const my_ui_command_t* command);

/** @brief Execute once from the target loop's event handler. */
void my_ui_command_dispatch(my_ui_command_t* command);

#endif /* MY_UI_COMMAND_H */
