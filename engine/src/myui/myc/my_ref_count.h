/**
 * @file my_ref_count.h
 * @brief Overflow-safe atomic reference-count helpers.
 */
#ifndef MY_REF_COUNT_H
#define MY_REF_COUNT_H

#include <limits.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdatomic.h>

/* Saturation fails closed: a saturated object is intentionally immortal. */
static inline bool my_ref_count_try_ref(atomic_uint* count) {
  unsigned int current;

  if (count == NULL) {
    return false;
  }
  current = atomic_load_explicit(count, memory_order_relaxed);
  for (;;) {
    if (current == 0u || current == UINT_MAX) {
      return false;
    }
    if (atomic_compare_exchange_weak_explicit(
            count, &current, current + 1u, memory_order_relaxed,
            memory_order_relaxed)) {
      return true;
    }
  }
}

static inline bool my_ref_count_release(atomic_uint* count) {
  unsigned int current;

  if (count == NULL) {
    return false;
  }
  current = atomic_load_explicit(count, memory_order_acquire);
  for (;;) {
    if (current == 0u || current == UINT_MAX) {
      return false;
    }
    if (atomic_compare_exchange_weak_explicit(
            count, &current, current - 1u, memory_order_acq_rel,
            memory_order_acquire)) {
      return current == 1u;
    }
  }
}

static inline bool my_ref_count_try_ref_size(atomic_size_t* count) {
  size_t current;

  if (count == NULL) {
    return false;
  }
  current = atomic_load_explicit(count, memory_order_relaxed);
  for (;;) {
    if (current == 0u || current == SIZE_MAX) {
      return false;
    }
    if (atomic_compare_exchange_weak_explicit(
            count, &current, current + 1u, memory_order_relaxed,
            memory_order_relaxed)) {
      return true;
    }
  }
}

static inline bool my_ref_count_release_size(atomic_size_t* count) {
  size_t current;

  if (count == NULL) {
    return false;
  }
  current = atomic_load_explicit(count, memory_order_acquire);
  for (;;) {
    if (current == 0u || current == SIZE_MAX) {
      return false;
    }
    if (atomic_compare_exchange_weak_explicit(
            count, &current, current - 1u, memory_order_acq_rel,
            memory_order_acquire)) {
      return current == 1u;
    }
  }
}

#endif /* MY_REF_COUNT_H */
