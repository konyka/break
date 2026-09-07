/**
 * @file my_emitter.h
 * @brief Event emitter: named events with multiple listeners.
 *
 * Unsubscribing inside a callback is safe: the listener is only marked
 * inactive and is physically removed after the current emit finishes
 * (mark-and-sweep). Destroying an emitter inside a callback is also safe;
 * disposal is deferred until the outermost emit returns and the current
 * emit stops before invoking later listeners. Listeners registered during
 * an emit are not invoked by that emit.
 */
#ifndef MY_EMITTER_H
#define MY_EMITTER_H

#include "myc/my_error.h"
#include "myc/my_mem.h"

/** @brief Event callback. event_data is owned by the emitter caller. */
typedef void (*my_event_callback_t)(void* ctx, const char* event, void* event_data);

/** @brief Releases an owned listener context after listener removal. */
typedef void (*my_event_context_destroy_fn_t)(void* ctx);

/** @brief Invalidatable lifetime lease for borrowed event contexts. */
typedef struct my_emitter_context_lease_t my_emitter_context_lease_t;

/** @brief Releases a lease context after its final lease reference. */
typedef void (*my_emitter_context_lease_destroy_fn_t)(void* ctx);

/** @brief Opaque emitter handle. */
typedef struct my_emitter_t my_emitter_t;

/** @brief Create an emitter (NULL allocator = default). */
my_emitter_t* my_emitter_create(const my_allocator_t* allocator);

/**
 * @brief Create a context lease that can be invalidated before owner teardown.
 *
 * The lease keeps the context alive until the final lease reference is
 * released. Invalidating it prevents future guarded callbacks from starting;
 * a callback already admitted may finish normally.
 */
my_emitter_context_lease_t* my_emitter_context_lease_create(
    const my_allocator_t* allocator, void* ctx,
    my_emitter_context_lease_destroy_fn_t destroy_ctx);
my_emitter_context_lease_t* my_emitter_context_lease_ref(
    my_emitter_context_lease_t* lease);
void my_emitter_context_lease_unref(my_emitter_context_lease_t* lease);
void my_emitter_context_lease_invalidate(my_emitter_context_lease_t* lease);
bool my_emitter_context_lease_is_valid(
    const my_emitter_context_lease_t* lease);
/** @brief Acquire the context while holding a lease reference. */
void* my_emitter_context_lease_context(my_emitter_context_lease_t* lease);

/**
 * @brief Destroy the emitter and all remaining listeners.
 *
 * When called from a listener, disposal is deferred until the outermost
 * emit returns; the caller must not use the handle after this call.
 */
void my_emitter_destroy(my_emitter_t* emitter);

/**
 * @brief Subscribe to an event name.
 * @return listener id (> 0) for my_emitter_off(), 0 on failure.
 */
uint32_t my_emitter_on(my_emitter_t* emitter, const char* event,
                       my_event_callback_t callback, void* ctx);

/**
 * @brief Subscribe with ownership of the callback context.
 *
 * On success the emitter releases `ctx` exactly once when the listener is
 * removed or the emitter is destroyed. On failure ownership is not
 * transferred. The context destructor must not depend on the emitter being
 * usable; it may run during reentrant teardown.
 */
uint32_t my_emitter_on_owned(my_emitter_t* emitter, const char* event,
                             my_event_callback_t callback, void* ctx,
                             my_event_context_destroy_fn_t destroy_ctx);

/**
 * @brief Subscribe with an invalidatable context lease.
 *
 * The emitter retains one lease reference. Invalidated leases remain
 * registered but are skipped until removed; the caller may release its own
 * reference immediately after successful registration.
 */
uint32_t my_emitter_on_lease(my_emitter_t* emitter, const char* event,
                             my_event_callback_t callback,
                             my_emitter_context_lease_t* lease);

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
