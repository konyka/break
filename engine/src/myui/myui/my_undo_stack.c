/**
 * @file my_undo_stack.c
 * @brief Generic undo/redo stack (text patch model with batching).
 */
#include "myui/my_undo_stack.h"

#include <string.h>

#include "myc/my_darray.h"

typedef struct undo_entry_t {
  void* tag;        /**< owner tag (M11b; NULL = untagged) */
  size_t offset;
  char* deleted;
  size_t deleted_len;
  char* inserted;
  size_t inserted_len;
  bool batchable; /**< still open for merging */
} undo_entry_t;

struct my_undo_stack_t {
  const my_allocator_t* allocator;
  my_darray_t* entries; /**< undo_entry_t*, chronological */
  size_t capacity;
  size_t undo_pos; /**< entries[0..undo_pos) undoable; rest redoable */
};

my_undo_stack_t* my_undo_stack_create(const my_allocator_t* allocator,
                                      size_t capacity) {
  my_undo_stack_t* s =
      (my_undo_stack_t*)my_mem_calloc(allocator, 1, sizeof(my_undo_stack_t));
  if (s == NULL) {
    return NULL;
  }
  s->allocator = allocator;
  s->capacity = capacity > 0 ? capacity : MY_UNDO_STACK_DEFAULT_CAPACITY;
  s->entries = my_darray_create(allocator, 0);
  if (s->entries == NULL) {
    my_mem_free(allocator, s);
    return NULL;
  }
  return s;
}

static void entry_free(my_undo_stack_t* s, undo_entry_t* e) {
  my_mem_free(s->allocator, e->deleted);
  my_mem_free(s->allocator, e->inserted);
  my_mem_free(s->allocator, e);
}

void my_undo_stack_destroy(my_undo_stack_t* s) {
  size_t i, n;
  if (s == NULL) {
    return;
  }
  n = my_darray_size(s->entries);
  for (i = 0; i < n; i++) {
    entry_free(s, (undo_entry_t*)my_darray_get(s->entries, i));
  }
  my_darray_destroy(s->entries);
  my_mem_free(s->allocator, s);
}

size_t my_undo_stack_size(my_undo_stack_t* stack) {
  return stack != NULL ? my_darray_size(stack->entries) : 0;
}

bool my_undo_stack_can_undo(my_undo_stack_t* stack) {
  return stack != NULL && stack->undo_pos > 0;
}

bool my_undo_stack_can_redo(my_undo_stack_t* stack) {
  return stack != NULL && stack->undo_pos < my_darray_size(stack->entries);
}

void my_undo_stack_break_batch(my_undo_stack_t* stack) {
  size_t n;
  if (stack == NULL) {
    return;
  }
  n = my_darray_size(stack->entries);
  if (n > 0) {
    ((undo_entry_t*)my_darray_get(stack->entries, n - 1))->batchable = false;
  }
}

void my_undo_stack_clear(my_undo_stack_t* stack) {
  if (stack != NULL) {
    while (my_darray_size(stack->entries) > 0) {
      size_t last = my_darray_size(stack->entries) - 1;
      entry_free(stack, (undo_entry_t*)my_darray_get(stack->entries, last));
      my_darray_remove_at(stack->entries, last);
    }
    stack->undo_pos = 0;
  }
}

/** @brief Any new edit kills the redo branch. */
static void drop_redo(my_undo_stack_t* s) {
  while (my_darray_size(s->entries) > s->undo_pos) {
    size_t last = my_darray_size(s->entries) - 1;
    entry_free(s, (undo_entry_t*)my_darray_get(s->entries, last));
    my_darray_remove_at(s->entries, last);
  }
}

static undo_entry_t* new_entry(my_undo_stack_t* s) {
  undo_entry_t* e;
  /* capacity: drop the oldest */
  while (my_darray_size(s->entries) >= s->capacity) {
    undo_entry_t* old = (undo_entry_t*)my_darray_get(s->entries, 0);
    entry_free(s, old);
    my_darray_remove_at(s->entries, 0);
    if (s->undo_pos > 0) {
      s->undo_pos--;
    }
  }
  e = (undo_entry_t*)my_mem_calloc(s->allocator, 1, sizeof(undo_entry_t));
  if (e != NULL) {
    e->batchable = true;
    if (my_darray_push(s->entries, e) != MY_RET_OK) {
      my_mem_free(s->allocator, e);
      return NULL;
    }
  }
  return e;
}

static char* memdup(my_undo_stack_t* s, const char* bytes, size_t len) {
  char* p = (char*)my_mem_alloc(s->allocator, len + 1);
  if (p != NULL) {
    if (len > 0) {
      memcpy(p, bytes, len);
    }
    p[len] = '\0';
  }
  return p;
}

my_ret_t my_undo_stack_record_insert_tagged(my_undo_stack_t* stack, void* tag,
                                            size_t offset, const char* bytes,
                                            size_t len) {
  size_t n;
  undo_entry_t* last;
  if (stack == NULL || (bytes == NULL && len > 0)) {
    return MY_RET_INVALID_PARAMS;
  }
  drop_redo(stack);
  n = my_darray_size(stack->entries);
  last = n > 0 ? (undo_entry_t*)my_darray_get(stack->entries, n - 1) : NULL;
  if (last != NULL && last->batchable && last->tag == tag &&
      last->deleted_len == 0 &&
      offset == last->offset + last->inserted_len) {
    /* typing stream: append to the open batch */
    char* p = (char*)my_mem_realloc(stack->allocator, last->inserted,
                                    last->inserted_len + len + 1);
    if (p == NULL) {
      return MY_RET_OOM;
    }
    memcpy(p + last->inserted_len, bytes, len);
    last->inserted = p;
    last->inserted_len += len;
    last->inserted[last->inserted_len] = '\0';
    stack->undo_pos = my_darray_size(stack->entries);
    return MY_RET_OK;
  }
  last = new_entry(stack);
  if (last == NULL) {
    return MY_RET_OOM;
  }
  last->tag = tag;
  last->offset = offset;
  last->inserted = memdup(stack, bytes, len);
  last->inserted_len = len;
  if (len > 0 && last->inserted == NULL) {
    entry_free(stack, last);
    my_darray_remove_at(stack->entries, my_darray_size(stack->entries) - 1);
    return MY_RET_OOM;
  }
  stack->undo_pos = my_darray_size(stack->entries);
  return MY_RET_OK;
}

my_ret_t my_undo_stack_record_insert(my_undo_stack_t* stack, size_t offset,
                                     const char* bytes, size_t len) {
  return my_undo_stack_record_insert_tagged(stack, NULL, offset, bytes, len);
}

my_ret_t my_undo_stack_record_delete_tagged(my_undo_stack_t* stack, void* tag,
                                            size_t offset, const char* bytes,
                                            size_t len) {
  size_t n;
  undo_entry_t* last;
  if (stack == NULL || (bytes == NULL && len > 0) || len == 0) {
    return MY_RET_INVALID_PARAMS;
  }
  drop_redo(stack);
  n = my_darray_size(stack->entries);
  last = n > 0 ? (undo_entry_t*)my_darray_get(stack->entries, n - 1) : NULL;
  if (last != NULL && last->batchable && last->tag == tag &&
      last->inserted_len == 0 && offset + len == last->offset) {
    /* backspace stream: prepend to the open batch */
    char* p = (char*)my_mem_alloc(stack->allocator, last->deleted_len + len);
    if (p == NULL) {
      return MY_RET_OOM;
    }
    memcpy(p, bytes, len);
    memcpy(p + len, last->deleted, last->deleted_len);
    my_mem_free(stack->allocator, last->deleted);
    last->deleted = p;
    last->deleted_len += len;
    last->deleted[last->deleted_len] = '\0';
    last->offset = offset;
    stack->undo_pos = my_darray_size(stack->entries);
    return MY_RET_OK;
  }
  last = new_entry(stack);
  if (last == NULL) {
    return MY_RET_OOM;
  }
  last->tag = tag;
  last->offset = offset;
  last->deleted = memdup(stack, bytes, len);
  last->deleted_len = len;
  if (last->deleted == NULL) {
    entry_free(stack, last);
    my_darray_remove_at(stack->entries, my_darray_size(stack->entries) - 1);
    return MY_RET_OOM;
  }
  stack->undo_pos = my_darray_size(stack->entries);
  return MY_RET_OK;
}

my_ret_t my_undo_stack_record_delete(my_undo_stack_t* stack, size_t offset,
                                     const char* bytes, size_t len) {
  return my_undo_stack_record_delete_tagged(stack, NULL, offset, bytes, len);
}

void my_undo_stack_clear_tagged(my_undo_stack_t* stack, const void* tag) {
  size_t i;
  if (stack == NULL) {
    return;
  }
  /* remove tagged entries from the end, keeping order of the rest */
  for (i = my_darray_size(stack->entries); i-- > 0;) {
    undo_entry_t* e = (undo_entry_t*)my_darray_get(stack->entries, i);
    if (e->tag == tag) {
      entry_free(stack, e);
      my_darray_remove_at(stack->entries, i);
      if (stack->undo_pos > i) {
        stack->undo_pos--;
      }
    }
  }
}

my_ret_t my_undo_stack_undo_tagged(my_undo_stack_t* stack, my_undo_op_t* op,
                                   void** tag) {
  undo_entry_t* e;
  if (stack == NULL || op == NULL || !my_undo_stack_can_undo(stack)) {
    return MY_RET_NOT_FOUND;
  }
  stack->undo_pos--;
  e = (undo_entry_t*)my_darray_get(stack->entries, stack->undo_pos);
  /* inverse: remove what was inserted, re-insert what was deleted */
  op->offset = e->offset;
  op->remove_len = e->inserted_len;
  op->bytes = e->deleted != NULL ? e->deleted : "";
  op->bytes_len = e->deleted_len;
  if (tag != NULL) {
    *tag = e->tag;
  }
  return MY_RET_OK;
}

my_ret_t my_undo_stack_redo_tagged(my_undo_stack_t* stack, my_undo_op_t* op,
                                   void** tag) {
  undo_entry_t* e;
  if (stack == NULL || op == NULL || !my_undo_stack_can_redo(stack)) {
    return MY_RET_NOT_FOUND;
  }
  e = (undo_entry_t*)my_darray_get(stack->entries, stack->undo_pos);
  stack->undo_pos++;
  /* forward: remove what was deleted, re-insert what was inserted */
  op->offset = e->offset;
  op->remove_len = e->deleted_len;
  op->bytes = e->inserted != NULL ? e->inserted : "";
  op->bytes_len = e->inserted_len;
  if (tag != NULL) {
    *tag = e->tag;
  }
  return MY_RET_OK;
}

my_ret_t my_undo_stack_undo(my_undo_stack_t* stack, my_undo_op_t* op) {
  return my_undo_stack_undo_tagged(stack, op, NULL);
}

my_ret_t my_undo_stack_redo(my_undo_stack_t* stack, my_undo_op_t* op) {
  return my_undo_stack_redo_tagged(stack, op, NULL);
}
