/**
 * @file my_ui_command.c
 * @brief Owned, loop-thread UI command submission.
 */
#include "myui/my_ui_command.h"

#include <stdatomic.h>

#include "myc/my_ref_count.h"

typedef enum my_ui_command_state_t {
  MY_UI_COMMAND_CREATED = 0,
  MY_UI_COMMAND_QUEUED,
  MY_UI_COMMAND_RUNNING,
  MY_UI_COMMAND_DONE,
  MY_UI_COMMAND_CANCELLED
} my_ui_command_state_t;

struct my_ui_command_t {
  const my_allocator_t* allocator;
  atomic_uint ref_count;
  atomic_int state;
  my_ui_command_execute_fn execute;
  void* context;
  my_ui_command_context_destroy_fn destroy_context;
  _Atomic(my_ui_command_scope_t*) scope;
  my_ui_command_t* scope_prev;
  my_ui_command_t* scope_next;
  bool scope_linked;
};

struct my_ui_command_scope_t {
  const my_allocator_t* allocator;
  atomic_uint ref_count;
  atomic_bool closed;
  atomic_flag lock;
  my_ui_command_t* head;
};

static void my_ui_command_detach_scope(my_ui_command_t* command);

static void my_ui_command_queue_release(void* data) {
  my_ui_command_t* command = (my_ui_command_t*)data;
  if (command == NULL) {
    return;
  }
  my_ui_command_detach_scope(command);
  my_ui_command_unref(command);
}

static void my_ui_command_scope_lock(my_ui_command_scope_t* scope) {
  while (atomic_flag_test_and_set_explicit(&scope->lock,
                                           memory_order_acquire)) {
  }
}

static void my_ui_command_scope_unlock(my_ui_command_scope_t* scope) {
  atomic_flag_clear_explicit(&scope->lock, memory_order_release);
}

static void my_ui_command_detach_scope(my_ui_command_t* command) {
  my_ui_command_scope_t* scope;
  if (command == NULL) {
    return;
  }
  scope = atomic_exchange_explicit(&command->scope, NULL,
                                   memory_order_acq_rel);
  if (scope == NULL) {
    return;
  }
  my_ui_command_scope_lock(scope);
  if (command->scope_linked) {
    if (command->scope_prev != NULL) {
      command->scope_prev->scope_next = command->scope_next;
    } else {
      scope->head = command->scope_next;
    }
    if (command->scope_next != NULL) {
      command->scope_next->scope_prev = command->scope_prev;
    }
    command->scope_prev = NULL;
    command->scope_next = NULL;
    command->scope_linked = false;
    my_ui_command_scope_unlock(scope);
    my_ui_command_scope_unref(scope);
    return;
  }
  my_ui_command_scope_unlock(scope);
}

my_ui_command_t* my_ui_command_create(
    const my_allocator_t* allocator, my_ui_command_execute_fn execute,
    void* context, my_ui_command_context_destroy_fn destroy_context) {
  my_ui_command_t* command;
  if (execute == NULL) {
    return NULL;
  }
  command = (my_ui_command_t*)my_mem_calloc(allocator, 1, sizeof(*command));
  if (command == NULL) {
    return NULL;
  }
  command->allocator = allocator;
  atomic_init(&command->ref_count, 1u);
  atomic_init(&command->state, MY_UI_COMMAND_CREATED);
  command->execute = execute;
  command->context = context;
  command->destroy_context = destroy_context;
  return command;
}

my_ui_command_scope_t* my_ui_command_scope_create(
    const my_allocator_t* allocator) {
  my_ui_command_scope_t* scope = (my_ui_command_scope_t*)my_mem_calloc(
      allocator, 1, sizeof(*scope));
  if (scope == NULL) {
    return NULL;
  }
  scope->allocator = allocator;
  atomic_init(&scope->ref_count, 1u);
  atomic_init(&scope->closed, false);
  atomic_flag_clear(&scope->lock);
  return scope;
}

my_ui_command_scope_t* my_ui_command_scope_ref(
    my_ui_command_scope_t* scope) {
  if (scope != NULL) {
    (void)my_ref_count_try_ref(&scope->ref_count);
  }
  return scope;
}

void my_ui_command_scope_unref(my_ui_command_scope_t* scope) {
  if (scope == NULL || !my_ref_count_release(&scope->ref_count)) {
    return;
  }
  my_ui_command_scope_close(scope);
  my_mem_free(scope->allocator, scope);
}

void my_ui_command_scope_close(my_ui_command_scope_t* scope) {
  my_ui_command_t* command;
  if (scope == NULL) {
    return;
  }
  my_ui_command_scope_lock(scope);
  atomic_store_explicit(&scope->closed, true, memory_order_release);
  for (command = scope->head; command != NULL; command = command->scope_next) {
    int state = atomic_load_explicit(&command->state, memory_order_acquire);
    while (state == MY_UI_COMMAND_CREATED ||
           state == MY_UI_COMMAND_QUEUED) {
      if (atomic_compare_exchange_weak_explicit(
              &command->state, &state, MY_UI_COMMAND_CANCELLED,
              memory_order_acq_rel, memory_order_acquire)) {
        break;
      }
    }
  }
  my_ui_command_scope_unlock(scope);
}

void my_ui_command_scope_reopen(my_ui_command_scope_t* scope) {
  if (scope != NULL) {
    my_ui_command_scope_lock(scope);
    atomic_store_explicit(&scope->closed, false, memory_order_release);
    my_ui_command_scope_unlock(scope);
  }
}

bool my_ui_command_scope_is_closed(const my_ui_command_scope_t* scope) {
  return scope != NULL &&
         atomic_load_explicit(&scope->closed, memory_order_acquire);
}

my_ui_command_t* my_ui_command_ref(my_ui_command_t* command) {
  if (command != NULL) {
    (void)my_ref_count_try_ref(&command->ref_count);
  }
  return command;
}

void my_ui_command_unref(my_ui_command_t* command) {
  if (command == NULL || !my_ref_count_release(&command->ref_count)) {
    return;
  }
  if (command->destroy_context != NULL) {
    command->destroy_context(command->context);
  }
  my_mem_free(command->allocator, command);
}

my_ret_t my_ui_command_submit_scoped(my_pal_main_loop_t* loop,
                                     my_ui_command_scope_t* scope,
                                     my_ui_command_t* command) {
  my_event_t event;
  int expected = MY_UI_COMMAND_CREATED;
  my_ret_t ret;
  if (loop == NULL || command == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (scope != NULL) {
    my_ui_command_scope_lock(scope);
    if (atomic_load_explicit(&scope->closed, memory_order_acquire) ||
        !atomic_compare_exchange_strong_explicit(
            &command->state, &expected, MY_UI_COMMAND_QUEUED,
            memory_order_acq_rel, memory_order_acquire)) {
      my_ui_command_scope_unlock(scope);
      return MY_RET_PENDING;
    }
    atomic_store_explicit(&command->scope, my_ui_command_scope_ref(scope),
                          memory_order_release);
    command->scope_prev = NULL;
    command->scope_next = scope->head;
    if (scope->head != NULL) {
      scope->head->scope_prev = command;
    }
    scope->head = command;
    command->scope_linked = true;
    my_ui_command_scope_unlock(scope);
  } else if (!atomic_compare_exchange_strong_explicit(
                 &command->state, &expected, MY_UI_COMMAND_QUEUED,
                 memory_order_acq_rel, memory_order_acquire)) {
    return MY_RET_PENDING;
  }
  my_ui_command_ref(command);
  event = my_event_init(MY_EVENT_COMMAND);
  event.u.command.data = command;
  event.u.command.destroy = my_ui_command_queue_release;
  ret = my_pal_main_loop_post_event(loop, &event);
  if (ret != MY_RET_OK) {
    expected = MY_UI_COMMAND_QUEUED;
    (void)atomic_compare_exchange_strong_explicit(
        &command->state, &expected, MY_UI_COMMAND_CREATED,
        memory_order_acq_rel, memory_order_acquire);
    my_event_release_payload(&event);
    my_ui_command_detach_scope(command);
    return ret;
  }
  return MY_RET_OK;
}

my_ret_t my_ui_command_submit(my_pal_main_loop_t* loop,
                              my_ui_command_t* command) {
  return my_ui_command_submit_scoped(loop, NULL, command);
}

my_ret_t my_ui_command_cancel(my_ui_command_t* command) {
  int state;
  if (command == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  state = atomic_load_explicit(&command->state, memory_order_acquire);
  for (;;) {
    if (state != MY_UI_COMMAND_CREATED && state != MY_UI_COMMAND_QUEUED) {
      return state == MY_UI_COMMAND_RUNNING ? MY_RET_PENDING
                                             : MY_RET_NOT_FOUND;
    }
    if (atomic_compare_exchange_weak_explicit(
            &command->state, &state, MY_UI_COMMAND_CANCELLED,
            memory_order_acq_rel, memory_order_acquire)) {
      return MY_RET_OK;
    }
  }
}

bool my_ui_command_is_cancelled(const my_ui_command_t* command) {
  return command != NULL &&
         atomic_load_explicit(&command->state, memory_order_acquire) ==
             MY_UI_COMMAND_CANCELLED;
}

void my_ui_command_dispatch(my_ui_command_t* command) {
  int expected = MY_UI_COMMAND_QUEUED;
  if (command == NULL ||
      !atomic_compare_exchange_strong_explicit(
          &command->state, &expected, MY_UI_COMMAND_RUNNING,
          memory_order_acq_rel, memory_order_acquire)) {
    return;
  }
  my_ui_command_detach_scope(command);
  (void)command->execute(command->context);
  atomic_store_explicit(&command->state, MY_UI_COMMAND_DONE,
                        memory_order_release);
}
