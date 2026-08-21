/**
 * @file my_undo_manager.c
 * @brief Window-level shared undo manager implementation (M11b).
 */
#include "myui/my_undo_manager.h"

#include "myc/my_darray.h"
#include "myc/my_str.h"
#include "myui/my_window.h"

typedef struct undo_target_t {
  void* widget;             /**< borrowed */
  my_undo_apply_fn apply;
} undo_target_t;

struct my_undo_manager_t {
  const my_allocator_t* allocator;
  my_undo_stack_t* stack;   /**< owned; entries tagged with the widget */
  my_darray_t* targets;     /**< undo_target_t* (owned per registration) */
};

my_undo_manager_t* my_undo_manager_create(const my_allocator_t* allocator,
                                          size_t capacity) {
  my_undo_manager_t* m =
      (my_undo_manager_t*)my_mem_calloc(allocator, 1, sizeof(my_undo_manager_t));
  if (m == NULL) {
    return NULL;
  }
  m->allocator = allocator;
  m->stack = my_undo_stack_create(allocator, capacity);
  m->targets = my_darray_create(allocator, 0);
  if (m->stack == NULL || m->targets == NULL) {
    my_undo_manager_destroy(m);
    return NULL;
  }
  return m;
}

void my_undo_manager_destroy(my_undo_manager_t* mgr) {
  if (mgr != NULL) {
    size_t i, n;
    my_undo_stack_destroy(mgr->stack);
    n = my_darray_size(mgr->targets);
    for (i = 0; i < n; i++) {
      my_mem_free(mgr->allocator, my_darray_get(mgr->targets, i));
    }
    my_darray_destroy(mgr->targets);
    my_mem_free(mgr->allocator, mgr);
  }
}

static undo_target_t* find_target(my_undo_manager_t* mgr, const void* widget) {
  size_t i, n = my_darray_size(mgr->targets);
  for (i = 0; i < n; i++) {
    undo_target_t* t = (undo_target_t*)my_darray_get(mgr->targets, i);
    if (t->widget == widget) {
      return t;
    }
  }
  return NULL;
}

my_ret_t my_undo_manager_register(my_undo_manager_t* mgr, void* widget,
                                  my_undo_apply_fn apply) {
  undo_target_t* t;
  if (mgr == NULL || widget == NULL || apply == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (find_target(mgr, widget) != NULL) {
    return MY_RET_OK; /* already registered */
  }
  t = (undo_target_t*)my_mem_alloc(mgr->allocator, sizeof(undo_target_t));
  if (t == NULL) {
    return MY_RET_OOM;
  }
  t->widget = widget;
  t->apply = apply;
  if (my_darray_push(mgr->targets, t) != MY_RET_OK) {
    my_mem_free(mgr->allocator, t);
    return MY_RET_OOM;
  }
  return MY_RET_OK;
}

void my_undo_manager_unregister(my_undo_manager_t* mgr, const void* widget) {
  size_t i, n;
  if (mgr == NULL) {
    return;
  }
  n = my_darray_size(mgr->targets);
  for (i = 0; i < n; i++) {
    undo_target_t* t = (undo_target_t*)my_darray_get(mgr->targets, i);
    if (t->widget == widget) {
      my_darray_remove_at(mgr->targets, i);
      my_mem_free(mgr->allocator, t);
      break;
    }
  }
}

my_ret_t my_undo_manager_record_insert(my_undo_manager_t* mgr, void* widget,
                                       size_t offset, const char* bytes,
                                       size_t len) {
  if (mgr == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  return my_undo_stack_record_insert_tagged(mgr->stack, widget, offset, bytes,
                                            len);
}

my_ret_t my_undo_manager_record_delete(my_undo_manager_t* mgr, void* widget,
                                       size_t offset, const char* bytes,
                                       size_t len) {
  if (mgr == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  return my_undo_stack_record_delete_tagged(mgr->stack, widget, offset, bytes,
                                            len);
}

void my_undo_manager_break_batch(my_undo_manager_t* mgr) {
  if (mgr != NULL) {
    my_undo_stack_break_batch(mgr->stack);
  }
}

void my_undo_manager_clear(my_undo_manager_t* mgr) {
  if (mgr != NULL) {
    my_undo_stack_clear(mgr->stack);
  }
}

void my_undo_manager_clear_widget(my_undo_manager_t* mgr, const void* widget) {
  if (mgr != NULL) {
    my_undo_stack_clear_tagged(mgr->stack, widget);
  }
}

bool my_undo_manager_can_undo(my_undo_manager_t* mgr) {
  return mgr != NULL && my_undo_stack_can_undo(mgr->stack);
}

bool my_undo_manager_can_redo(my_undo_manager_t* mgr) {
  return mgr != NULL && my_undo_stack_can_redo(mgr->stack);
}

/** @brief Focus the widget when it lives under a my_window root. */
static void focus_widget(void* widget) {
  my_widget_t* root = (my_widget_t*)widget;
  while (root->parent != NULL) {
    root = root->parent;
  }
  if (my_str_eq(root->widget_type, "window")) {
    my_event_dispatcher_set_focus(&((my_window_t*)root)->dispatcher,
                                  (my_widget_t*)widget);
  }
}

static my_ret_t apply_routed(my_undo_manager_t* mgr, bool redo) {
  my_undo_op_t op;
  void* tag = NULL;
  undo_target_t* t;
  my_ret_t r = redo ? my_undo_stack_redo_tagged(mgr->stack, &op, &tag)
                    : my_undo_stack_undo_tagged(mgr->stack, &op, &tag);
  if (r != MY_RET_OK) {
    return r;
  }
  t = find_target(mgr, tag);
  if (t == NULL) {
    return MY_RET_FAIL; /* owner gone: entry popped but cannot be applied */
  }
  focus_widget(t->widget); /* focus first: blurs the current widget */
  t->apply(t->widget, &op);
  return MY_RET_OK;
}

my_ret_t my_undo_manager_undo(my_undo_manager_t* mgr) {
  if (mgr == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  return apply_routed(mgr, false);
}

my_ret_t my_undo_manager_redo(my_undo_manager_t* mgr) {
  if (mgr == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  return apply_routed(mgr, true);
}
