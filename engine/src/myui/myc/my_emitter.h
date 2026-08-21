/**
 * @file my_emitter.h
 * @brief Event emitter: named events with multiple listeners.
 *
 * Unsubscribing inside a callback is safe: the listener is only marked
 * inactive and is physically removed after the current emit finishes
 * (mark-and-sweep). Listeners registered during an emit are not invoked
 * by that emit.
 */
#ifndef MY_EMITTER_H
#define MY_EMITTER_H

#include "myc/my_error.h"
#include "myc/my_mem.h"

/** @brief Event callback. event_data is owned by the emitter caller. */
typedef void (*my_event_callback_t)(void* ctx, const char* event, void* event_data);

/** @brief Opaque emitter handle. */
typedef struct my_emitter_t my_emitter_t;

/** @brief Create an emitter (NULL allocator = default). */
my_emitter_t* my_emitter_create(const my_allocator_t* allocator);

/** @brief Destroy the emitter and all remaining listeners. */
void my_emitter_destroy(my_emitter_t* emitter);

/**
 * @brief Subscribe to an event name.
 * @return listener id (> 0) for my_emitter_off(), 0 on failure.
 */
uint32_t my_emitter_on(my_emitter_t* emitter, const char* event,
                       my_event_callback_t callback, void* ctx);

/**
 * @brief Unsubscribe by id. Safe to call from inside a callback.
 * @return MY_RET_OK, or MY_RET_NOT_FOUND if the id is unknown.
 */
my_ret_t my_emitter_off(my_emitter_t* emitter, uint32_t id);

/**
 * @brief Emit an event: invoke all active listeners of that name in
 * subscription order. event_data is passed through untouched.
 */
my_ret_t my_emitter_emit(my_emitter_t* emitter, const char* event, void* event_data);

#endif /* MY_EMITTER_H */
