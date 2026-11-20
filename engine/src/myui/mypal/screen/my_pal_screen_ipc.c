#define _POSIX_C_SOURCE 200809L

#include "mypal/screen/my_pal_screen_ipc.h"

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <poll.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <unistd.h>

#define IPC_HEADER_SIZE 16u
#define IPC_MAX_PAYLOAD (MY_PAL_SCREEN_IPC_MAX_TEXT_BYTES + 4u)
#define IPC_MAX_FRAME (IPC_HEADER_SIZE + IPC_MAX_PAYLOAD)
#define IPC_MAX_CLIENTS 8u
#define IPC_OUT_QUEUE 8u
#define IPC_CLIENT_EVENTS 8u
#define IPC_RPC_TIMEOUT_MS 5000u
#define IPC_WORKER_POLL_MS 50

typedef enum ipc_kind_t {
  IPC_CLIPBOARD_SET = 1,
  IPC_CLIPBOARD_GET = 2,
  IPC_CLIPBOARD_CLEAR = 3,
  IPC_IME_SUBSCRIBE = 4,
  IPC_IME_PREEDIT = 5,
  IPC_IME_COMMIT = 6,
  IPC_EVENT_PREEDIT = 0x21,
  IPC_EVENT_COMMIT = 0x22,
  IPC_RESPONSE = 0x80
} ipc_kind_t;

typedef struct ipc_connection_t ipc_connection_t;

struct my_pal_screen_ipc_server_t {
  const my_allocator_t* allocator;
  char path[sizeof(((struct sockaddr_un*)0)->sun_path)];
  int listen_fd;
  int wake_fds[2];
  pthread_t accept_thread;
  bool accept_started;
  bool bound;
  bool mutex_initialized;
  atomic_bool stopping;
  pthread_mutex_t mutex;
  char* clipboard;
  size_t clipboard_length;
  uint32_t next_client_id;
  ipc_connection_t* connections[IPC_MAX_CLIENTS];
};

struct ipc_connection_t {
  my_pal_screen_ipc_server_t* server;
  pthread_t thread;
  int local_fd;
  atomic_int fd;
  atomic_bool closing;
  atomic_bool finished;
  bool subscribed;
  uint32_t id;
  pthread_mutex_t out_mutex;
  uint8_t out_frames[IPC_OUT_QUEUE][IPC_MAX_FRAME];
  size_t out_lengths[IPC_OUT_QUEUE];
  size_t out_offsets[IPC_OUT_QUEUE];
  uint32_t out_head;
  uint32_t out_count;
  uint8_t input[IPC_MAX_FRAME];
  size_t input_length;
};

struct my_pal_screen_ipc_client_t {
  const my_allocator_t* allocator;
  pthread_mutex_t mutex;
  int fd;
  uint32_t next_request_id;
  uint8_t input[IPC_MAX_FRAME];
  size_t input_length;
  my_pal_screen_ipc_ime_event_t events[IPC_CLIENT_EVENTS];
  uint32_t event_head;
  uint32_t event_count;
};

static void ipc_put16(uint8_t* p, uint16_t value) {
  p[0] = (uint8_t)(value >> 8);
  p[1] = (uint8_t)value;
}

static void ipc_put32(uint8_t* p, uint32_t value) {
  p[0] = (uint8_t)(value >> 24);
  p[1] = (uint8_t)(value >> 16);
  p[2] = (uint8_t)(value >> 8);
  p[3] = (uint8_t)value;
}

static uint16_t ipc_get16(const uint8_t* p) {
  return (uint16_t)((uint16_t)((uint16_t)p[0] << 8) | (uint16_t)p[1]);
}

static uint32_t ipc_get32(const uint8_t* p) {
  return ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) |
         ((uint32_t)p[2] << 8) | (uint32_t)p[3];
}

static int32_t ipc_get_i32(const uint8_t* p) {
  uint32_t value = ipc_get32(p);
  if (value <= (uint32_t)INT32_MAX) return (int32_t)value;
  return -1 - (int32_t)(UINT32_MAX - value);
}

static void ipc_make_frame(uint8_t* frame, uint8_t kind, uint32_t id,
                           const uint8_t* payload, uint32_t length) {
  memcpy(frame, "MYIP", 4u);
  ipc_put16(frame + 4u, MY_PAL_SCREEN_IPC_PROTOCOL_VERSION);
  frame[6] = kind;
  frame[7] = 0u;
  ipc_put32(frame + 8u, id);
  ipc_put32(frame + 12u, length);
  if (length > 0u) memcpy(frame + IPC_HEADER_SIZE, payload, length);
}

static bool ipc_header_valid(const uint8_t* frame, uint32_t* payload_length) {
  if (memcmp(frame, "MYIP", 4u) != 0 ||
      ipc_get16(frame + 4u) != MY_PAL_SCREEN_IPC_PROTOCOL_VERSION ||
      frame[7] != 0u) {
    return false;
  }
  *payload_length = ipc_get32(frame + 12u);
  return *payload_length <= IPC_MAX_PAYLOAD;
}

static bool ipc_utf8_valid(const uint8_t* text, size_t length,
                           size_t* codepoints) {
  size_t i = 0u;
  size_t count = 0u;
  if (length > MY_PAL_SCREEN_IPC_MAX_TEXT_BYTES) return false;
  while (i < length) {
    uint8_t a = text[i];
    size_t width;
    if (a == 0u) return false;
    if (a <= 0x7fu) {
      width = 1u;
    } else if (a >= 0xc2u && a <= 0xdfu) {
      if (length - i < 2u || (text[i + 1u] & 0xc0u) != 0x80u) return false;
      width = 2u;
    } else if (a >= 0xe0u && a <= 0xefu) {
      uint8_t b;
      if (length - i < 3u) return false;
      b = text[i + 1u];
      if ((text[i + 2u] & 0xc0u) != 0x80u ||
          (a == 0xe0u ? (b < 0xa0u || b > 0xbfu)
                      : a == 0xedu ? (b < 0x80u || b > 0x9fu)
                                   : (b & 0xc0u) != 0x80u)) {
        return false;
      }
      width = 3u;
    } else if (a >= 0xf0u && a <= 0xf4u) {
      uint8_t b;
      if (length - i < 4u || (text[i + 2u] & 0xc0u) != 0x80u ||
          (text[i + 3u] & 0xc0u) != 0x80u) {
        return false;
      }
      b = text[i + 1u];
      if (a == 0xf0u ? (b < 0x90u || b > 0xbfu)
                     : a == 0xf4u ? (b < 0x80u || b > 0x8fu)
                                  : (b & 0xc0u) != 0x80u) {
        return false;
      }
      width = 4u;
    } else {
      return false;
    }
    i += width;
    count++;
  }
  if (codepoints != NULL) *codepoints = count;
  return true;
}

static bool ipc_cstr_valid(const char* text, size_t* length,
                           size_t* codepoints) {
  size_t size = 0u;
  if (text == NULL) return false;
  while (size <= MY_PAL_SCREEN_IPC_MAX_TEXT_BYTES && text[size] != '\0') size++;
  if (size > MY_PAL_SCREEN_IPC_MAX_TEXT_BYTES ||
      !ipc_utf8_valid((const uint8_t*)text, size, codepoints)) {
    return false;
  }
  *length = size;
  return true;
}

static bool ipc_ime_payload_valid(const uint8_t* payload, size_t length,
                                  bool preedit) {
  size_t codepoints;
  int32_t cursor;
  if (length < 4u ||
      !ipc_utf8_valid(payload + 4u, length - 4u, &codepoints)) {
    return false;
  }
  cursor = ipc_get_i32(payload);
  if (preedit) return cursor >= 0 && (size_t)cursor <= codepoints;
  return cursor == 0;
}

static int ipc_set_nonblocking(int fd) {
  int flags = fcntl(fd, F_GETFL, 0);
  if (flags < 0 || fcntl(fd, F_SETFL, flags | O_NONBLOCK) != 0) return -1;
  flags = fcntl(fd, F_GETFD, 0);
  if (flags >= 0) (void)fcntl(fd, F_SETFD, flags | FD_CLOEXEC);
  return 0;
}

static uint64_t ipc_now_ms(void) {
  struct timespec now;
  if (clock_gettime(CLOCK_MONOTONIC, &now) != 0) return 0u;
  return (uint64_t)now.tv_sec * 1000u + (uint64_t)now.tv_nsec / 1000000u;
}

static void ipc_wake(int fd) {
  uint8_t value = 1u;
  ssize_t result;
  if (fd < 0) return;
  do {
    result = write(fd, &value, 1u);
  } while (result < 0 && errno == EINTR);
  (void)result;
}

static bool ipc_connection_queue(ipc_connection_t* connection,
                                 const uint8_t* frame, size_t length) {
  uint32_t slot;
  bool ok = true;
  pthread_mutex_lock(&connection->out_mutex);
  if (connection->out_count == IPC_OUT_QUEUE ||
      atomic_load_explicit(&connection->closing, memory_order_acquire)) {
    ok = false;
  } else {
    slot = (connection->out_head + connection->out_count) % IPC_OUT_QUEUE;
    memcpy(connection->out_frames[slot], frame, length);
    connection->out_lengths[slot] = length;
    connection->out_offsets[slot] = 0u;
    connection->out_count++;
  }
  pthread_mutex_unlock(&connection->out_mutex);
  if (!ok) atomic_store_explicit(&connection->closing, true, memory_order_release);
  return ok;
}

static bool ipc_connection_flush(ipc_connection_t* connection) {
  bool ok = true;
  pthread_mutex_lock(&connection->out_mutex);
  if (connection->out_count > 0u) {
    uint32_t head = connection->out_head;
    size_t offset = connection->out_offsets[head];
    size_t remaining = connection->out_lengths[head] - offset;
    ssize_t written = send(connection->local_fd,
                           connection->out_frames[head] + offset, remaining,
                           MSG_NOSIGNAL);
    if (written > 0) {
      offset += (size_t)written;
      if (offset == connection->out_lengths[head]) {
        connection->out_head = (head + 1u) % IPC_OUT_QUEUE;
        connection->out_count--;
        connection->out_offsets[head] = 0u;
      } else {
        connection->out_offsets[head] = offset;
      }
    } else if (written < 0 &&
               (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)) {
      ok = true;
    } else {
      ok = false;
    }
  }
  pthread_mutex_unlock(&connection->out_mutex);
  return ok;
}

static bool ipc_connection_respond(ipc_connection_t* connection, uint32_t id,
                                   my_ret_t status, const uint8_t* text,
                                   size_t text_length) {
  uint8_t frame[IPC_MAX_FRAME];
  uint8_t payload[4u];
  uint32_t length = 4u;
  ipc_put32(payload, (uint32_t)status);
  ipc_make_frame(frame, IPC_RESPONSE, id, payload, length);
  if (text_length > 0u) {
    memcpy(frame + IPC_HEADER_SIZE + length, text, text_length);
    length += (uint32_t)text_length;
    ipc_put32(frame + 12u, length);
  }
  return ipc_connection_queue(connection, frame, IPC_HEADER_SIZE + length);
}

static void ipc_broadcast_ime(ipc_connection_t* source, uint8_t kind,
                              const uint8_t* payload, size_t length) {
  my_pal_screen_ipc_server_t* server = source->server;
  uint8_t frame[IPC_MAX_FRAME];
  uint32_t i;
  ipc_make_frame(frame, kind, source->id, payload, (uint32_t)length);
  pthread_mutex_lock(&server->mutex);
  for (i = 0u; i < IPC_MAX_CLIENTS; ++i) {
    ipc_connection_t* connection = server->connections[i];
    if (connection != NULL && connection != source && connection->subscribed &&
        !atomic_load_explicit(&connection->closing, memory_order_acquire)) {
      (void)ipc_connection_queue(connection, frame, IPC_HEADER_SIZE + length);
    }
  }
  pthread_mutex_unlock(&server->mutex);
}

static bool ipc_connection_request(ipc_connection_t* connection,
                                   const uint8_t* frame) {
  my_pal_screen_ipc_server_t* server = connection->server;
  uint8_t kind = frame[6];
  uint32_t id = ipc_get32(frame + 8u);
  uint32_t length = ipc_get32(frame + 12u);
  const uint8_t* payload = frame + IPC_HEADER_SIZE;
  size_t codepoints;
  if (id == 0u) return false;
  if (kind == IPC_CLIPBOARD_SET) {
    char* copy;
    char* old;
    if (!ipc_utf8_valid(payload, length, NULL)) return false;
    pthread_mutex_lock(&server->mutex);
    copy = (char*)my_mem_alloc(server->allocator, (size_t)length + 1u);
    if (copy == NULL) {
      pthread_mutex_unlock(&server->mutex);
      return ipc_connection_respond(connection, id, MY_RET_OOM, NULL, 0u);
    }
    memcpy(copy, payload, length);
    copy[length] = '\0';
    old = server->clipboard;
    server->clipboard = copy;
    server->clipboard_length = length;
    my_mem_free(server->allocator, old);
    pthread_mutex_unlock(&server->mutex);
    return ipc_connection_respond(connection, id, MY_RET_OK, NULL, 0u);
  }
  if (kind == IPC_CLIPBOARD_GET) {
    my_ret_t status = MY_RET_OK;
    size_t text_length;
    if (length != 0u) return false;
    pthread_mutex_lock(&server->mutex);
    if (server->clipboard == NULL) {
      status = MY_RET_NOT_FOUND;
      text_length = 0u;
    } else {
      text_length = server->clipboard_length;
    }
    if (!ipc_connection_respond(connection, id, status,
                                (const uint8_t*)server->clipboard, text_length)) {
      pthread_mutex_unlock(&server->mutex);
      return false;
    }
    pthread_mutex_unlock(&server->mutex);
    return true;
  }
  if (kind == IPC_CLIPBOARD_CLEAR) {
    char* old;
    if (length != 0u) return false;
    pthread_mutex_lock(&server->mutex);
    old = server->clipboard;
    server->clipboard = NULL;
    server->clipboard_length = 0u;
    my_mem_free(server->allocator, old);
    pthread_mutex_unlock(&server->mutex);
    return ipc_connection_respond(connection, id, MY_RET_OK, NULL, 0u);
  }
  if (kind == IPC_IME_SUBSCRIBE) {
    if (length != 1u || payload[0] > 1u) return false;
    pthread_mutex_lock(&server->mutex);
    connection->subscribed = payload[0] != 0u;
    pthread_mutex_unlock(&server->mutex);
    return ipc_connection_respond(connection, id, MY_RET_OK, NULL, 0u);
  }
  if (kind == IPC_IME_PREEDIT || kind == IPC_IME_COMMIT) {
    bool preedit = kind == IPC_IME_PREEDIT;
    if (!ipc_ime_payload_valid(payload, length, preedit)) return false;
    if (preedit) {
      (void)ipc_utf8_valid(payload + 4u, length - 4u, &codepoints);
    }
    ipc_broadcast_ime(connection,
                      preedit ? IPC_EVENT_PREEDIT : IPC_EVENT_COMMIT, payload,
                      length);
    return ipc_connection_respond(connection, id, MY_RET_OK, NULL, 0u);
  }
  return false;
}

static bool ipc_connection_input(ipc_connection_t* connection) {
  ssize_t count;
  size_t used = 0u;
  if (connection->input_length == sizeof(connection->input)) return false;
  do {
    count = recv(connection->local_fd,
                 connection->input + connection->input_length,
                 sizeof(connection->input) - connection->input_length, 0);
  } while (count < 0 && errno == EINTR);
  if (count == 0) return false;
  if (count < 0) return errno == EAGAIN || errno == EWOULDBLOCK;
  connection->input_length += (size_t)count;
  while (connection->input_length - used >= IPC_HEADER_SIZE) {
    uint32_t payload_length;
    size_t frame_length;
    if (!ipc_header_valid(connection->input + used, &payload_length)) return false;
    frame_length = IPC_HEADER_SIZE + payload_length;
    if (connection->input_length - used < frame_length) break;
    if (!ipc_connection_request(connection, connection->input + used)) return false;
    used += frame_length;
  }
  if (used > 0u) {
    connection->input_length -= used;
    if (connection->input_length > 0u) {
      memmove(connection->input, connection->input + used,
              connection->input_length);
    }
  }
  return true;
}

static void* ipc_connection_main(void* opaque) {
  ipc_connection_t* connection = (ipc_connection_t*)opaque;
  my_pal_screen_ipc_server_t* server = connection->server;
  while (!atomic_load_explicit(&connection->closing, memory_order_acquire) &&
         !atomic_load_explicit(&server->stopping, memory_order_acquire)) {
    struct pollfd pfd;
    bool has_output;
    int result;
    pthread_mutex_lock(&connection->out_mutex);
    has_output = connection->out_count > 0u;
    pthread_mutex_unlock(&connection->out_mutex);
    pfd.fd = connection->local_fd;
    pfd.events = POLLIN | (has_output ? POLLOUT : 0);
    pfd.revents = 0;
    do {
      result = poll(&pfd, 1u, IPC_WORKER_POLL_MS);
    } while (result < 0 && errno == EINTR &&
             !atomic_load_explicit(&server->stopping, memory_order_acquire));
    if (result < 0) break;
    if (result > 0 && (pfd.revents & POLLOUT) != 0 &&
        !ipc_connection_flush(connection)) {
      break;
    }
    if (result > 0 && (pfd.revents & POLLIN) != 0 &&
        !ipc_connection_input(connection)) {
      break;
    }
    if (result > 0 && (pfd.revents & (POLLERR | POLLHUP | POLLNVAL)) != 0) break;
  }
  close(connection->local_fd);
  atomic_store_explicit(&connection->fd, -1, memory_order_release);
  pthread_mutex_lock(&server->mutex);
  connection->subscribed = false;
  pthread_mutex_unlock(&server->mutex);
  pthread_mutex_destroy(&connection->out_mutex);
  atomic_store_explicit(&connection->finished, true, memory_order_release);
  return NULL;
}

static void ipc_connection_free(ipc_connection_t* connection) {
  my_pal_screen_ipc_server_t* server;
  if (connection == NULL) return;
  server = connection->server;
  pthread_join(connection->thread, NULL);
  pthread_mutex_lock(&server->mutex);
  my_mem_free(server->allocator, connection);
  pthread_mutex_unlock(&server->mutex);
}

static void ipc_server_reap(my_pal_screen_ipc_server_t* server) {
  uint32_t i;
  for (i = 0u; i < IPC_MAX_CLIENTS; ++i) {
    ipc_connection_t* connection = NULL;
    pthread_mutex_lock(&server->mutex);
    if (server->connections[i] != NULL &&
        atomic_load_explicit(&server->connections[i]->finished,
                             memory_order_acquire)) {
      connection = server->connections[i];
      server->connections[i] = NULL;
    }
    pthread_mutex_unlock(&server->mutex);
    ipc_connection_free(connection);
  }
}

static void ipc_server_accept(my_pal_screen_ipc_server_t* server) {
  uint32_t slot;
  int fd = accept(server->listen_fd, NULL, NULL);
  ipc_connection_t* connection;
  if (fd < 0) return;
  if (ipc_set_nonblocking(fd) != 0) {
    close(fd);
    return;
  }
  pthread_mutex_lock(&server->mutex);
  for (slot = 0u; slot < IPC_MAX_CLIENTS; ++slot) {
    if (server->connections[slot] == NULL) break;
  }
  if (slot == IPC_MAX_CLIENTS) {
    pthread_mutex_unlock(&server->mutex);
    close(fd);
    return;
  }
  connection = (ipc_connection_t*)my_mem_calloc(server->allocator, 1u,
                                                sizeof(*connection));
  if (connection == NULL || pthread_mutex_init(&connection->out_mutex, NULL) != 0) {
    my_mem_free(server->allocator, connection);
    pthread_mutex_unlock(&server->mutex);
    close(fd);
    return;
  }
  connection->server = server;
  connection->local_fd = fd;
  atomic_init(&connection->fd, fd);
  atomic_init(&connection->closing, false);
  atomic_init(&connection->finished, false);
  server->next_client_id++;
  if (server->next_client_id == 0u) server->next_client_id = 1u;
  connection->id = server->next_client_id;
  server->connections[slot] = connection;
  pthread_mutex_unlock(&server->mutex);
  if (pthread_create(&connection->thread, NULL, ipc_connection_main, connection) !=
      0) {
    pthread_mutex_lock(&server->mutex);
    server->connections[slot] = NULL;
    close(fd);
    pthread_mutex_destroy(&connection->out_mutex);
    my_mem_free(server->allocator, connection);
    pthread_mutex_unlock(&server->mutex);
  }
}

static void* ipc_server_accept_main(void* opaque) {
  my_pal_screen_ipc_server_t* server = (my_pal_screen_ipc_server_t*)opaque;
  while (!atomic_load_explicit(&server->stopping, memory_order_acquire)) {
    struct pollfd fds[2];
    int result;
    ipc_server_reap(server);
    fds[0].fd = server->listen_fd;
    fds[0].events = POLLIN;
    fds[0].revents = 0;
    fds[1].fd = server->wake_fds[0];
    fds[1].events = POLLIN;
    fds[1].revents = 0;
    do {
      result = poll(fds, 2u, IPC_WORKER_POLL_MS);
    } while (result < 0 && errno == EINTR &&
             !atomic_load_explicit(&server->stopping, memory_order_acquire));
    if (result < 0) break;
    if (result > 0 && (fds[1].revents & POLLIN) != 0) {
      uint8_t buffer[16];
      while (read(server->wake_fds[0], buffer, sizeof(buffer)) > 0) {
      }
    }
    if (result > 0 && (fds[0].revents & POLLIN) != 0 &&
        !atomic_load_explicit(&server->stopping, memory_order_acquire)) {
      ipc_server_accept(server);
    }
    if (result > 0 && (fds[0].revents & (POLLERR | POLLNVAL)) != 0) break;
  }
  ipc_server_reap(server);
  return NULL;
}

my_ret_t my_pal_screen_ipc_server_start(
    const my_allocator_t* allocator, const char* socket_path,
    my_pal_screen_ipc_server_t** out_server) {
  my_pal_screen_ipc_server_t* server;
  struct sockaddr_un address;
  size_t path_length;
  int result = MY_RET_FAIL;
  if (out_server == NULL) return MY_RET_INVALID_PARAMS;
  *out_server = NULL;
  if (socket_path == NULL || socket_path[0] == '\0') return MY_RET_INVALID_PARAMS;
  path_length = strlen(socket_path);
  if (path_length >= sizeof(address.sun_path)) return MY_RET_INVALID_PARAMS;
  server = (my_pal_screen_ipc_server_t*)my_mem_calloc(allocator, 1u,
                                                      sizeof(*server));
  if (server == NULL) return MY_RET_OOM;
  server->allocator = allocator;
  server->listen_fd = -1;
  server->wake_fds[0] = -1;
  server->wake_fds[1] = -1;
  server->next_client_id = 0u;
  memcpy(server->path, socket_path, path_length + 1u);
  atomic_init(&server->stopping, false);
  if (pthread_mutex_init(&server->mutex, NULL) != 0) goto cleanup;
  server->mutex_initialized = true;
  if (pipe(server->wake_fds) != 0) goto cleanup;
  if (ipc_set_nonblocking(server->wake_fds[0]) != 0 ||
      ipc_set_nonblocking(server->wake_fds[1]) != 0) {
    goto cleanup;
  }
  server->listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (server->listen_fd < 0 || ipc_set_nonblocking(server->listen_fd) != 0) {
    goto cleanup;
  }
  memset(&address, 0, sizeof(address));
  address.sun_family = AF_UNIX;
  memcpy(address.sun_path, socket_path, path_length + 1u);
#if defined(__QNXNTO__)
  address.sun_len = (unsigned char)sizeof(address);
#endif
  if (bind(server->listen_fd, (struct sockaddr*)&address,
           (socklen_t)sizeof(address)) != 0) {
    goto cleanup;
  }
  server->bound = true;
  if (listen(server->listen_fd, IPC_MAX_CLIENTS) != 0) goto cleanup;
  if (pthread_create(&server->accept_thread, NULL, ipc_server_accept_main, server) !=
      0) {
    goto cleanup;
  }
  server->accept_started = true;
  *out_server = server;
  return MY_RET_OK;
cleanup:
  if (server->accept_started) {
    atomic_store_explicit(&server->stopping, true, memory_order_release);
    ipc_wake(server->wake_fds[1]);
    pthread_join(server->accept_thread, NULL);
  }
  if (server->listen_fd >= 0) close(server->listen_fd);
  if (server->wake_fds[0] >= 0) close(server->wake_fds[0]);
  if (server->wake_fds[1] >= 0) close(server->wake_fds[1]);
  if (server->bound) (void)unlink(server->path);
  if (server->mutex_initialized) pthread_mutex_destroy(&server->mutex);
  my_mem_free(allocator, server);
  return result;
}

void my_pal_screen_ipc_server_destroy(my_pal_screen_ipc_server_t* server) {
  uint32_t i;
  if (server == NULL) return;
  atomic_store_explicit(&server->stopping, true, memory_order_release);
  ipc_wake(server->wake_fds[1]);
  if (server->accept_started) pthread_join(server->accept_thread, NULL);
  for (i = 0u; i < IPC_MAX_CLIENTS; ++i) {
    ipc_connection_t* connection = server->connections[i];
    if (connection != NULL) {
      atomic_store_explicit(&connection->closing, true, memory_order_release);
    }
  }
  for (i = 0u; i < IPC_MAX_CLIENTS; ++i) {
    ipc_connection_t* connection;
    pthread_mutex_lock(&server->mutex);
    connection = server->connections[i];
    server->connections[i] = NULL;
    pthread_mutex_unlock(&server->mutex);
    ipc_connection_free(connection);
  }
  close(server->listen_fd);
  close(server->wake_fds[0]);
  close(server->wake_fds[1]);
  if (server->bound) (void)unlink(server->path);
  my_mem_free(server->allocator, server->clipboard);
  pthread_mutex_destroy(&server->mutex);
  my_mem_free(server->allocator, server);
}

my_ret_t my_pal_screen_ipc_client_open(
    const my_allocator_t* allocator, const char* socket_path,
    my_pal_screen_ipc_client_t** out_client) {
  my_pal_screen_ipc_client_t* client;
  struct sockaddr_un address;
  size_t path_length;
  int fd;
  if (out_client == NULL) return MY_RET_INVALID_PARAMS;
  *out_client = NULL;
  if (socket_path == NULL || socket_path[0] == '\0') return MY_RET_INVALID_PARAMS;
  path_length = strlen(socket_path);
  if (path_length >= sizeof(address.sun_path)) return MY_RET_INVALID_PARAMS;
  client = (my_pal_screen_ipc_client_t*)my_mem_calloc(allocator, 1u,
                                                      sizeof(*client));
  if (client == NULL) return MY_RET_OOM;
  client->allocator = allocator;
  client->fd = -1;
  client->next_request_id = 1u;
  if (pthread_mutex_init(&client->mutex, NULL) != 0) {
    my_mem_free(allocator, client);
    return MY_RET_FAIL;
  }
  fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (fd < 0) goto failure;
  memset(&address, 0, sizeof(address));
  address.sun_family = AF_UNIX;
  memcpy(address.sun_path, socket_path, path_length + 1u);
#if defined(__QNXNTO__)
  address.sun_len = (unsigned char)sizeof(address);
#endif
  if (connect(fd, (struct sockaddr*)&address, (socklen_t)sizeof(address)) != 0 ||
      ipc_set_nonblocking(fd) != 0) {
    close(fd);
    goto failure;
  }
  client->fd = fd;
  *out_client = client;
  return MY_RET_OK;
failure:
  pthread_mutex_destroy(&client->mutex);
  my_mem_free(allocator, client);
  return MY_RET_FAIL;
}

void my_pal_screen_ipc_client_destroy(my_pal_screen_ipc_client_t* client) {
  if (client == NULL) return;
  if (client->fd >= 0) close(client->fd);
  pthread_mutex_destroy(&client->mutex);
  my_mem_free(client->allocator, client);
}

static my_ret_t ipc_client_failure(my_pal_screen_ipc_client_t* client) {
  if (client->fd >= 0) close(client->fd);
  client->fd = -1;
  client->input_length = 0u;
  client->event_head = 0u;
  client->event_count = 0u;
  return MY_RET_FAIL;
}

typedef enum ipc_wait_result_t {
  IPC_WAIT_READY = 1,
  IPC_WAIT_TIMEOUT = 0,
  IPC_WAIT_ERROR = -1
} ipc_wait_result_t;

static ipc_wait_result_t ipc_client_wait(my_pal_screen_ipc_client_t* client,
                                         short events, uint64_t deadline) {
  struct pollfd pfd;
  int result;
  pfd.fd = client->fd;
  pfd.events = events;
  pfd.revents = 0;
  for (;;) {
    uint64_t now = ipc_now_ms();
    uint64_t remaining = now >= deadline ? 0u : deadline - now;
    int timeout = remaining > (uint64_t)INT_MAX ? INT_MAX : (int)remaining;
    result = poll(&pfd, 1u, timeout);
    if (result >= 0 || errno != EINTR) break;
  }
  if (result < 0) return IPC_WAIT_ERROR;
  if (result == 0) return IPC_WAIT_TIMEOUT;
  if ((pfd.revents & POLLNVAL) != 0) return IPC_WAIT_ERROR;
  return IPC_WAIT_READY;
}

static bool ipc_client_send(my_pal_screen_ipc_client_t* client,
                            const uint8_t* frame, size_t length,
                            uint64_t deadline) {
  size_t offset = 0u;
  while (offset < length) {
    ssize_t written = send(client->fd, frame + offset, length - offset,
                           MSG_NOSIGNAL);
    if (written > 0) {
      offset += (size_t)written;
    } else if (written < 0 && errno == EINTR) {
      continue;
    } else if (written < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
      if (ipc_client_wait(client, POLLOUT, deadline) != IPC_WAIT_READY) return false;
    } else {
      return false;
    }
  }
  return true;
}

typedef enum ipc_read_result_t {
  IPC_READ_OK = 1,
  IPC_READ_TIMEOUT = 0,
  IPC_READ_ERROR = -1
} ipc_read_result_t;

static ipc_read_result_t ipc_client_read_frame(my_pal_screen_ipc_client_t* client,
                                               uint8_t* frame,
                                               uint64_t deadline) {
  for (;;) {
    if (client->input_length >= IPC_HEADER_SIZE) {
      uint32_t payload_length;
      size_t frame_length;
      if (!ipc_header_valid(client->input, &payload_length)) return IPC_READ_ERROR;
      frame_length = IPC_HEADER_SIZE + payload_length;
      if (client->input_length >= frame_length) {
        memcpy(frame, client->input, frame_length);
        client->input_length -= frame_length;
        if (client->input_length > 0u) {
          memmove(client->input, client->input + frame_length,
                  client->input_length);
        }
        return IPC_READ_OK;
      }
    }
    {
      ipc_wait_result_t wait = ipc_client_wait(client, POLLIN, deadline);
      ssize_t count;
      if (wait == IPC_WAIT_TIMEOUT) return IPC_READ_TIMEOUT;
      if (wait == IPC_WAIT_ERROR) return IPC_READ_ERROR;
      if (client->input_length == sizeof(client->input)) return IPC_READ_ERROR;
      do {
        count = recv(client->fd, client->input + client->input_length,
                     sizeof(client->input) - client->input_length, 0);
      } while (count < 0 && errno == EINTR);
      if (count > 0) {
        client->input_length += (size_t)count;
      } else if (count == 0) {
        return IPC_READ_ERROR;
      } else if (errno != EAGAIN && errno != EWOULDBLOCK) {
        return IPC_READ_ERROR;
      }
    }
  }
}

static bool ipc_client_queue_event(my_pal_screen_ipc_client_t* client,
                                   const uint8_t* frame) {
  my_pal_screen_ipc_ime_event_t event;
  uint8_t kind = frame[6];
  uint32_t length = ipc_get32(frame + 12u);
  const uint8_t* payload = frame + IPC_HEADER_SIZE;
  uint32_t slot;
  bool preedit;
  if (kind == IPC_EVENT_PREEDIT) {
    preedit = true;
  } else if (kind == IPC_EVENT_COMMIT) {
    preedit = false;
  } else {
    return false;
  }
  if (ipc_get32(frame + 8u) == 0u ||
      !ipc_ime_payload_valid(payload, length, preedit) ||
      client->event_count == IPC_CLIENT_EVENTS) {
    return false;
  }
  memset(&event, 0, sizeof(event));
  event.type = preedit ? MY_PAL_SCREEN_IPC_IME_PREEDIT
                       : MY_PAL_SCREEN_IPC_IME_COMMIT;
  event.source_client_id = ipc_get32(frame + 8u);
  event.cursor = ipc_get_i32(payload);
  event.length = length - 4u;
  memcpy(event.text, payload + 4u, event.length);
  event.text[event.length] = '\0';
  slot = (client->event_head + client->event_count) % IPC_CLIENT_EVENTS;
  client->events[slot] = event;
  client->event_count++;
  return true;
}

static void ipc_client_pop_event(my_pal_screen_ipc_client_t* client,
                                 my_pal_screen_ipc_ime_event_t* out_event) {
  *out_event = client->events[client->event_head];
  client->event_head = (client->event_head + 1u) % IPC_CLIENT_EVENTS;
  client->event_count--;
}

static bool ipc_response_status_valid(int32_t status) {
  return status == MY_RET_OK || status == MY_RET_FAIL || status == MY_RET_OOM ||
         status == MY_RET_INVALID_PARAMS || status == MY_RET_NOT_FOUND ||
         status == MY_RET_NOT_SUPPORTED || status == MY_RET_PENDING;
}

static my_ret_t ipc_client_call(my_pal_screen_ipc_client_t* client, uint8_t kind,
                                const uint8_t* request_payload,
                                uint32_t request_length, bool clipboard_get,
                                uint8_t* response_payload,
                                size_t* response_length) {
  uint8_t request[IPC_MAX_FRAME];
  uint8_t response[IPC_MAX_FRAME];
  uint64_t deadline;
  uint32_t id;
  my_ret_t result = MY_RET_FAIL;
  pthread_mutex_lock(&client->mutex);
  if (client->fd < 0 || request_length > IPC_MAX_PAYLOAD) {
    result = client->fd < 0 ? MY_RET_FAIL : MY_RET_INVALID_PARAMS;
    goto done;
  }
  id = client->next_request_id++;
  if (client->next_request_id == 0u) client->next_request_id = 1u;
  ipc_make_frame(request, kind, id, request_payload, request_length);
  deadline = ipc_now_ms() + IPC_RPC_TIMEOUT_MS;
  if (!ipc_client_send(client, request, IPC_HEADER_SIZE + request_length, deadline)) {
    result = ipc_client_failure(client);
    goto done;
  }
  for (;;) {
    ipc_read_result_t read_result = ipc_client_read_frame(client, response, deadline);
    uint32_t length;
    int32_t status;
    if (read_result != IPC_READ_OK) {
      result = ipc_client_failure(client);
      goto done;
    }
    if (response[6] != IPC_RESPONSE) {
      if (!ipc_client_queue_event(client, response)) {
        result = ipc_client_failure(client);
        goto done;
      }
      continue;
    }
    length = ipc_get32(response + 12u);
    if (ipc_get32(response + 8u) != id || length < 4u) {
      result = ipc_client_failure(client);
      goto done;
    }
    status = ipc_get_i32(response + IPC_HEADER_SIZE);
    if (!ipc_response_status_valid(status) ||
        (!clipboard_get && length != 4u) ||
        (clipboard_get && status != MY_RET_OK && length != 4u) ||
        (clipboard_get && status == MY_RET_OK &&
         !ipc_utf8_valid(response + IPC_HEADER_SIZE + 4u, length - 4u, NULL))) {
      result = ipc_client_failure(client);
      goto done;
    }
    if (response_payload != NULL && length > 0u) {
      memcpy(response_payload, response + IPC_HEADER_SIZE, length);
    }
    if (response_length != NULL) *response_length = length;
    result = status;
    goto done;
  }
done:
  pthread_mutex_unlock(&client->mutex);
  return result;
}

my_ret_t my_pal_screen_ipc_clipboard_set(my_pal_screen_ipc_client_t* client,
                                         const char* utf8) {
  size_t length;
  if (client == NULL || !ipc_cstr_valid(utf8, &length, NULL)) {
    return MY_RET_INVALID_PARAMS;
  }
  return ipc_client_call(client, IPC_CLIPBOARD_SET, (const uint8_t*)utf8,
                         (uint32_t)length, false, NULL, NULL);
}

my_ret_t my_pal_screen_ipc_clipboard_get(my_pal_screen_ipc_client_t* client,
                                         char* text, size_t capacity,
                                         size_t* out_length) {
  uint8_t response[IPC_MAX_PAYLOAD];
  size_t response_length = 0u;
  size_t text_length;
  my_ret_t result;
  if (client == NULL || out_length == NULL || (text == NULL && capacity != 0u)) {
    return MY_RET_INVALID_PARAMS;
  }
  *out_length = 0u;
  result = ipc_client_call(client, IPC_CLIPBOARD_GET, NULL, 0u, true, response,
                           &response_length);
  if (result != MY_RET_OK) return result;
  text_length = response_length - 4u;
  *out_length = text_length;
  if (text == NULL) return MY_RET_OK;
  if (capacity < text_length + 1u) return MY_RET_INVALID_PARAMS;
  if (text_length > 0u) memcpy(text, response + 4u, text_length);
  text[text_length] = '\0';
  return MY_RET_OK;
}

my_ret_t my_pal_screen_ipc_clipboard_clear(my_pal_screen_ipc_client_t* client) {
  if (client == NULL) return MY_RET_INVALID_PARAMS;
  return ipc_client_call(client, IPC_CLIPBOARD_CLEAR, NULL, 0u, false, NULL, NULL);
}

my_ret_t my_pal_screen_ipc_ime_set_subscribed(
    my_pal_screen_ipc_client_t* client, bool subscribed) {
  uint8_t payload = subscribed ? 1u : 0u;
  if (client == NULL) return MY_RET_INVALID_PARAMS;
  return ipc_client_call(client, IPC_IME_SUBSCRIBE, &payload, 1u, false, NULL, NULL);
}

my_ret_t my_pal_screen_ipc_ime_preedit(my_pal_screen_ipc_client_t* client,
                                       const char* utf8, int32_t cursor) {
  uint8_t payload[IPC_MAX_PAYLOAD];
  size_t length;
  size_t codepoints;
  if (client == NULL || cursor < 0 ||
      !ipc_cstr_valid(utf8, &length, &codepoints) ||
      (size_t)cursor > codepoints) {
    return MY_RET_INVALID_PARAMS;
  }
  ipc_put32(payload, (uint32_t)cursor);
  if (length > 0u) memcpy(payload + 4u, utf8, length);
  return ipc_client_call(client, IPC_IME_PREEDIT, payload, (uint32_t)length + 4u,
                         false, NULL, NULL);
}

my_ret_t my_pal_screen_ipc_ime_commit(my_pal_screen_ipc_client_t* client,
                                      const char* utf8) {
  uint8_t payload[IPC_MAX_PAYLOAD];
  size_t length;
  if (client == NULL || !ipc_cstr_valid(utf8, &length, NULL)) {
    return MY_RET_INVALID_PARAMS;
  }
  ipc_put32(payload, 0u);
  if (length > 0u) memcpy(payload + 4u, utf8, length);
  return ipc_client_call(client, IPC_IME_COMMIT, payload, (uint32_t)length + 4u,
                         false, NULL, NULL);
}

my_ret_t my_pal_screen_ipc_ime_next_event(
    my_pal_screen_ipc_client_t* client, my_pal_screen_ipc_ime_event_t* out_event,
    uint32_t timeout_ms) {
  uint8_t frame[IPC_MAX_FRAME];
  uint64_t deadline;
  my_ret_t result = MY_RET_FAIL;
  if (client == NULL || out_event == NULL) return MY_RET_INVALID_PARAMS;
  pthread_mutex_lock(&client->mutex);
  if (client->event_count > 0u) {
    ipc_client_pop_event(client, out_event);
    result = MY_RET_OK;
    goto done;
  }
  if (client->fd < 0) {
    result = MY_RET_FAIL;
    goto done;
  }
  deadline = ipc_now_ms() + timeout_ms;
  for (;;) {
    ipc_read_result_t read_result = ipc_client_read_frame(client, frame, deadline);
    if (read_result == IPC_READ_TIMEOUT) {
      result = MY_RET_PENDING;
      goto done;
    }
    if (read_result == IPC_READ_ERROR ||
        (frame[6] != IPC_EVENT_PREEDIT && frame[6] != IPC_EVENT_COMMIT) ||
        !ipc_client_queue_event(client, frame)) {
      result = ipc_client_failure(client);
      goto done;
    }
    ipc_client_pop_event(client, out_event);
    result = MY_RET_OK;
    goto done;
  }
done:
  pthread_mutex_unlock(&client->mutex);
  return result;
}
