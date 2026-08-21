/**
 * @file my_undo_stack.h
 * @brief Generic undo/redo stack for text editing widgets.
 *
 * Each entry is a text patch: {offset, deleted, inserted} — the edit
 * replaced `deleted` (was at offset) with `inserted`. Undo removes
 * `inserted` and puts `deleted` back; redo replays the edit.
 *
 * Batching: consecutive INSERTS at continuously-advancing offsets
 * (a typing stream) merge into one entry; consecutive DELETES with
 * adjacently-decreasing offsets (backspace stream) merge likewise.
 * Anything else starts a new entry. Call my_undo_stack_break_batch()
 * on focus loss / explicit cursor moves so undo granularity matches
 * user intuition.
 *
 * The stack does NOT own the document: undo/redo return an operation
 * {offset, remove_len, bytes} that the caller applies (without
 * re-recording).
 */
#ifndef MY_UNDO_STACK_H
#define MY_UNDO_STACK_H

#include "myc/my_error.h"
#include "myc/my_mem.h"

#define MY_UNDO_STACK_DEFAULT_CAPACITY 100

/** @brief One undoable patch (caller-applied operation form). */
typedef struct my_undo_op_t {
  size_t offset;      /**< where to apply */
  size_t remove_len;  /**< bytes to remove at offset */
  const char* bytes;  /**< bytes to insert afterwards (borrowed) */
  size_t bytes_len;
} my_undo_op_t;

/** @brief Undo stack (opaque). */
typedef struct my_undo_stack_t my_undo_stack_t;

my_undo_stack_t* my_undo_stack_create(const my_allocator_t* allocator,
                                      size_t capacity);
void my_undo_stack_destroy(my_undo_stack_t* stack);

/** @brief Record an insertion of `len` bytes at `offset` (may batch). */
my_ret_t my_undo_stack_record_insert(my_undo_stack_t* stack, size_t offset,
                                     const char* bytes, size_t len);

/** @brief Record a deletion of `len` bytes at `offset` (may batch). */
my_ret_t my_undo_stack_record_delete(my_undo_stack_t* stack, size_t offset,
                                     const char* bytes, size_t len);

/**
 * @brief Tagged variants (M11b): entries carry an opaque owner tag (e.g.
 * the editing widget). A tag change breaks the open batch naturally --
 * interleaved edits of two owners never merge. Untagged calls behave as
 * tag = NULL.
 */
my_ret_t my_undo_stack_record_insert_tagged(my_undo_stack_t* stack, void* tag,
                                            size_t offset, const char* bytes,
                                            size_t len);
my_ret_t my_undo_stack_record_delete_tagged(my_undo_stack_t* stack, void* tag,
                                            size_t offset, const char* bytes,
                                            size_t len);

/** @brief Drop all entries owned by `tag` (undo_pos adjusted). */
void my_undo_stack_clear_tagged(my_undo_stack_t* stack, const void* tag);

/** @brief Tagged undo/redo: also return the entry's owner tag. */
my_ret_t my_undo_stack_undo_tagged(my_undo_stack_t* stack, my_undo_op_t* op,
                                   void** tag);
my_ret_t my_undo_stack_redo_tagged(my_undo_stack_t* stack, my_undo_op_t* op,
                                   void** tag);

/** @brief Close the current batch (focus loss, cursor jumps, etc). */
void my_undo_stack_break_batch(my_undo_stack_t* stack);

/** @brief Drop everything (document replaced programmatically). */
void my_undo_stack_clear(my_undo_stack_t* stack);

bool my_undo_stack_can_undo(my_undo_stack_t* stack);
bool my_undo_stack_can_redo(my_undo_stack_t* stack);

/**
 * @brief Undo: op removes op.remove_len bytes at op.offset and inserts
 * op.bytes there. @return MY_RET_OK, or MY_RET_NOT_FOUND when empty.
 */
my_ret_t my_undo_stack_undo(my_undo_stack_t* stack, my_undo_op_t* op);

/** @brief Redo: same apply form as undo. */
my_ret_t my_undo_stack_redo(my_undo_stack_t* stack, my_undo_op_t* op);

/** @brief Current entry count (diagnostics). */
size_t my_undo_stack_size(my_undo_stack_t* stack);

#endif /* MY_UNDO_STACK_H */
