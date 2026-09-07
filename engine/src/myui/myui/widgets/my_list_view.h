/**
 * @file my_list_view.h
 * @brief Virtualized list view: only visible rows (+1 buffer) are built;
 * scrolled-out rows are recycled into a pool and rebound.
 *
 * Data comes from a my_list_adapter_t (create_row/bind_row/get_count).
 * The MVVM items binding installs an adapter automatically when its
 * target is a list_view. Rows may use a lazy prefix-sum height index when
 * the adapter supplies row_height(); fixed-height mode remains the fast path.
 * Scroll: POINTER_WHEEL, drag (grab), right-side scrollbar indicator.
 */
#ifndef MY_LIST_VIEW_H
#define MY_LIST_VIEW_H

#include "myui/my_widget.h"

typedef struct my_list_adapter_t my_list_adapter_t;
typedef struct my_list_adapter_lease_t my_list_adapter_lease_t;

/** @brief Releases an adapter after the last lease reference is dropped. */
typedef void (*my_list_adapter_destroy_fn)(my_list_adapter_t* adapter,
                                           void* context);

/** @brief List adapter vtable. */
typedef struct my_list_adapter_vtable_t {
  size_t (*get_count)(my_list_adapter_t* adapter);
  /** @brief Create a NEW row widget (called rarely; rows are recycled). */
  my_widget_t* (*create_row)(my_list_adapter_t* adapter);
  /** @brief (Re)bind an existing row widget to a data index. */
  void (*bind_row)(my_list_adapter_t* adapter, my_widget_t* row, size_t index);
  /**
   * @brief Variable row height in px (M9c). NULL = fixed row_height
   * mode (identical to M8b behavior).
   */
  int32_t (*row_height)(my_list_adapter_t* adapter, size_t index);
} my_list_adapter_vtable_t;

/** @brief List adapter base "class". */
struct my_list_adapter_t {
  const my_list_adapter_vtable_t* vtable;
};

/**
 * @brief Reference-counted lifetime token for an adapter.
 *
 * The adapter vtable and instance must remain immutable while leased. The
 * destroy callback runs on the thread that drops the final reference.
 */
my_list_adapter_lease_t* my_list_adapter_lease_create(
    const my_allocator_t* allocator, my_list_adapter_t* adapter,
    void* context, my_list_adapter_destroy_fn destroy);
my_list_adapter_lease_t* my_list_adapter_lease_ref(
    my_list_adapter_lease_t* lease);
void my_list_adapter_lease_unref(my_list_adapter_lease_t* lease);

/** @brief Virtualized list view (IS-A widget). */
typedef struct my_list_view_t {
  my_widget_t base;
  const my_allocator_t* allocator;
  my_list_adapter_t* adapter;  /**< borrowed, or protected by adapter_lease */
  int32_t row_height;          /**< fixed row height (default 24) */
  int32_t scroll_offset;       /**< px, clamped */
  my_darray_t* active;         /**< row_slot_t* currently visible */
  my_darray_t* pool;           /**< my_widget_t* recycled rows (owned) */
  size_t rows_created_total;   /**< diagnostics: create_row call count */
  int32_t drag_y;              /**< drag scroll tracking (-1 = off) */
  int32_t drag_start_offset;
  my_widget_t* scroll_bar;     /**< owned link reference (M9c) */
  uint32_t scroll_bar_listener_id;
  my_darray_t* psum;           /**< reserved for ABI compatibility */
  bool psum_all;               /**< psum filled to the end */
  int64_t* psum_values;        /**< explicit 64-bit prefix sums */
  size_t psum_count;
  size_t psum_capacity;
  bool syncing;
  bool syncing_scroll_bar;
  my_list_adapter_lease_t* adapter_lease; /**< owned lease, if installed */
} my_list_view_t;

my_widget_t* my_list_view_create(const my_allocator_t* allocator);
bool my_list_view_is_instance(const my_widget_t* widget);
my_ret_t my_list_view_set_row_height(my_widget_t* list_view, int32_t height);
/** @brief Install an adapter (borrowed) and refresh. */
my_ret_t my_list_view_set_adapter(my_widget_t* list_view,
                                  my_list_adapter_t* adapter);
/**
 * @brief Install an adapter while retaining a reference to its lifetime
 * token. The view acquires a lease reference on success; the caller may
 * release its reference immediately. NULL clears the current adapter.
 *
 * Unlike the legacy borrowed API, this prevents adapter destruction while
 * rows are owned by the view. On failure the current adapter is unchanged.
 */
my_ret_t my_list_view_set_adapter_lease(
    my_widget_t* list_view, my_list_adapter_lease_t* lease);
/** @brief Re-read the adapter and refresh visible rows (data changed). */
my_ret_t my_list_view_refresh(my_widget_t* list_view);
/**
 * @brief Variable-height mode: forget ALL measured row heights (M10d).
 * The prefix-sum cache is dropped and refilled lazily from row 0; the
 * visible range, scroll offset (clamped to the new content height) and
 * scroll bar are refreshed immediately. Harmless in fixed-height mode.
 */
my_ret_t my_list_view_invalidate_row_heights(my_widget_t* list_view);
/**
 * @brief Variable-height mode: forget measured heights from `index`
 * onward (e.g. the row at `index` changed height, M10d). The prefix-sum
 * cache keeps rows < index and refills the tail lazily; visible range,
 * scroll clamp and scroll bar refresh immediately.
 */
my_ret_t my_list_view_invalidate_row_height(my_widget_t* list_view,
                                            size_t index);
/** @brief Scroll offset in px (clamped to content). */
my_ret_t my_list_view_set_scroll_offset(my_widget_t* list_view, int32_t offset);
int32_t my_list_view_get_scroll_offset(my_widget_t* list_view);
/** @brief Diagnostics: total rows ever created via the adapter. */
size_t my_list_view_rows_created_total(my_widget_t* list_view);

/** @brief Link a scroll_bar (owned link reference): kept in sync with scroll_offset and
 * content/viewport size; dragging the bar scrolls the list. Rebinding is
 * idempotent and destruction removes the active listener and link reference. */
my_ret_t my_list_view_set_scroll_bar(my_widget_t* list_view,
                                     my_widget_t* bar);

#endif /* MY_LIST_VIEW_H */
