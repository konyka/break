#ifndef MY_PAL_SCREEN_IPC_H
#define MY_PAL_SCREEN_IPC_H

#include "myc/my_error.h"
#include "myc/my_mem.h"

#include <stddef.h>
#include <stdint.h>

#define MY_PAL_SCREEN_IPC_PROTOCOL_VERSION 1u
#define MY_PAL_SCREEN_IPC_MAX_TEXT_BYTES 4096u

typedef struct my_pal_screen_ipc_server_t my_pal_screen_ipc_server_t;
typedef struct my_pal_screen_ipc_client_t my_pal_screen_ipc_client_t;

typedef enum my_pal_screen_ipc_ime_event_type_t {
  MY_PAL_SCREEN_IPC_IME_PREEDIT = 1,
  MY_PAL_SCREEN_IPC_IME_COMMIT = 2
} my_pal_screen_ipc_ime_event_type_t;

typedef struct my_pal_screen_ipc_ime_event_t {
  my_pal_screen_ipc_ime_event_type_t type;
  uint32_t source_client_id;
  int32_t cursor;
  size_t length;
  char text[MY_PAL_SCREEN_IPC_MAX_TEXT_BYTES + 1u];
} my_pal_screen_ipc_ime_event_t;

/* Explicit application-local test service; never an OS clipboard/IME endpoint. */
my_ret_t my_pal_screen_ipc_server_start(
    const my_allocator_t* allocator, const char* socket_path,
    my_pal_screen_ipc_server_t** out_server);
void my_pal_screen_ipc_server_destroy(my_pal_screen_ipc_server_t* server);

my_ret_t my_pal_screen_ipc_client_open(
    const my_allocator_t* allocator, const char* socket_path,
    my_pal_screen_ipc_client_t** out_client);
void my_pal_screen_ipc_client_destroy(my_pal_screen_ipc_client_t* client);

my_ret_t my_pal_screen_ipc_clipboard_set(my_pal_screen_ipc_client_t* client,
                                         const char* utf8);
/* out_length excludes the NUL. A small buffer returns INVALID_PARAMS and still
 * reports the required text length. text=NULL with capacity=0 queries length. */
my_ret_t my_pal_screen_ipc_clipboard_get(my_pal_screen_ipc_client_t* client,
                                         char* text, size_t capacity,
                                         size_t* out_length);
my_ret_t my_pal_screen_ipc_clipboard_clear(my_pal_screen_ipc_client_t* client);

/* Preedit/commit events go to every other subscribed client on this service. */
my_ret_t my_pal_screen_ipc_ime_set_subscribed(
    my_pal_screen_ipc_client_t* client, bool subscribed);
my_ret_t my_pal_screen_ipc_ime_preedit(my_pal_screen_ipc_client_t* client,
                                       const char* utf8, int32_t cursor);
my_ret_t my_pal_screen_ipc_ime_commit(my_pal_screen_ipc_client_t* client,
                                      const char* utf8);
/* PENDING means the bounded wait expired. Client calls are serialized internally;
 * destroy must run only after all calls using that client have returned. */
my_ret_t my_pal_screen_ipc_ime_next_event(
    my_pal_screen_ipc_client_t* client, my_pal_screen_ipc_ime_event_t* out_event,
    uint32_t timeout_ms);

#endif
