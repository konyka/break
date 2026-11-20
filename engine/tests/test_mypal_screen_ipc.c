#define _POSIX_C_SOURCE 200809L

#include "test_framework.h"
#include "mypal/screen/my_pal_screen_ipc.h"

#if defined(__QNXNTO__)
#define TEST_QNX_SPAWN_HELPERS_ONLY
#include "test_qnx_spawn.h"
#undef TEST_QNX_SPAWN_HELPERS_ONLY
#endif

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <poll.h>
#include <pthread.h>
#include <signal.h>
#include <spawn.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define TEST_HEADER_SIZE 16u
#define TEST_MAX_PAYLOAD (MY_PAL_SCREEN_IPC_MAX_TEXT_BYTES + 4u)
#define TEST_REQ_CLIPBOARD_SET 1u
#define TEST_REQ_CLIPBOARD_GET 2u
#define TEST_REQ_CLIPBOARD_CLEAR 3u
#define TEST_REQ_IME_SUBSCRIBE 4u
#define TEST_REQ_IME_PREEDIT 5u
#define TEST_REQ_IME_COMMIT 6u
#define TEST_RESPONSE 0x80u

typedef struct ipc_fixture_t {
  char path[256];
  my_pal_screen_ipc_server_t* server;
} ipc_fixture_t;

static void put16(uint8_t* p, uint16_t value) {
  p[0] = (uint8_t)(value >> 8);
  p[1] = (uint8_t)value;
}

static void put32(uint8_t* p, uint32_t value) {
  p[0] = (uint8_t)(value >> 24);
  p[1] = (uint8_t)(value >> 16);
  p[2] = (uint8_t)(value >> 8);
  p[3] = (uint8_t)value;
}

static uint32_t get32(const uint8_t* p) {
  return ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) |
         ((uint32_t)p[2] << 8) | (uint32_t)p[3];
}

static void make_frame(uint8_t* frame, uint8_t type, uint32_t id,
                       const void* payload, uint32_t length) {
  memcpy(frame, "MYIP", 4u);
  put16(frame + 4u, MY_PAL_SCREEN_IPC_PROTOCOL_VERSION);
  frame[6] = type;
  frame[7] = 0u;
  put32(frame + 8u, id);
  put32(frame + 12u, length);
  if (length > 0u) memcpy(frame + TEST_HEADER_SIZE, payload, length);
}

static int raw_connect(const char* path) {
  struct sockaddr_un address;
  int fd;
  size_t length = strlen(path);
  if (length >= sizeof(address.sun_path)) return -1;
  fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (fd < 0) return -1;
  memset(&address, 0, sizeof(address));
  address.sun_family = AF_UNIX;
  memcpy(address.sun_path, path, length + 1u);
#if defined(__QNXNTO__)
  address.sun_len = (unsigned char)sizeof(address);
#endif
  if (connect(fd, (struct sockaddr*)&address, (socklen_t)sizeof(address)) != 0) {
    close(fd);
    return -1;
  }
  return fd;
}

static bool write_all(int fd, const void* data, size_t length) {
  const uint8_t* p = (const uint8_t*)data;
  while (length > 0u) {
    ssize_t written = send(fd, p, length, MSG_NOSIGNAL);
    if (written < 0 && errno == EINTR) continue;
    if (written <= 0) return false;
    p += (size_t)written;
    length -= (size_t)written;
  }
  return true;
}

static bool read_all(int fd, void* data, size_t length) {
  uint8_t* p = (uint8_t*)data;
  while (length > 0u) {
    ssize_t count = recv(fd, p, length, 0);
    if (count < 0 && errno == EINTR) continue;
    if (count <= 0) return false;
    p += (size_t)count;
    length -= (size_t)count;
  }
  return true;
}

static bool pipe_write(int fd, char value) {
  ssize_t result;
  do {
    result = write(fd, &value, 1u);
  } while (result < 0 && errno == EINTR);
  return result == 1;
}

static bool pipe_read(int fd, char* value) {
  ssize_t result;
  do {
    result = read(fd, value, 1u);
  } while (result < 0 && errno == EINTR);
  return result == 1;
}

static bool fixture_start(ipc_fixture_t* fixture,
                          const my_allocator_t* allocator) {
  memset(fixture, 0, sizeof(*fixture));
  test_tmp(fixture->path, sizeof(fixture->path), "screen_ipc_socket");
  (void)unlink(fixture->path);
  return my_pal_screen_ipc_server_start(allocator, fixture->path,
                                        &fixture->server) == MY_RET_OK;
}

static void fixture_stop(ipc_fixture_t* fixture) {
  my_pal_screen_ipc_server_destroy(fixture->server);
  fixture->server = NULL;
  (void)unlink(fixture->path);
}

TEST(api_rejects_invalid_arguments_and_unknown_endpoint)
{
  my_pal_screen_ipc_server_t* server = NULL;
  my_pal_screen_ipc_client_t* client = NULL;
  my_pal_screen_ipc_ime_event_t event;
  char path[256];
  char output[8];
  size_t length = 99u;
  char long_path[sizeof(((struct sockaddr_un*)0)->sun_path) + 2u];
  memset(long_path, 'x', sizeof(long_path) - 1u);
  long_path[sizeof(long_path) - 1u] = '\0';
  test_tmp(path, sizeof(path), "screen_ipc_missing");
  (void)unlink(path);
  ASSERT_EQ(my_pal_screen_ipc_server_start(NULL, NULL, &server),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_screen_ipc_server_start(NULL, path, NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_screen_ipc_server_start(NULL, long_path, &server),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_screen_ipc_client_open(NULL, path, &client), MY_RET_FAIL);
  ASSERT_TRUE(client == NULL);
  ASSERT_EQ(my_pal_screen_ipc_client_open(NULL, path, NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_screen_ipc_clipboard_set(NULL, "x"),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_screen_ipc_clipboard_get(NULL, output, sizeof(output), &length),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_screen_ipc_clipboard_clear(NULL), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_screen_ipc_ime_set_subscribed(NULL, true),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_screen_ipc_ime_preedit(NULL, "x", 1),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_screen_ipc_ime_commit(NULL, "x"), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_screen_ipc_ime_next_event(NULL, &event, 0u),
            MY_RET_INVALID_PARAMS);
  my_pal_screen_ipc_server_destroy(NULL);
  my_pal_screen_ipc_client_destroy(NULL);
}

TEST(clipboard_round_trip_boundaries_and_utf8)
{
  static const char* invalid[] = {
      "\x80", "\xc0\xaf", "\xe0\x80\xaf", "\xf0\x80\x80\xaf",
      "\xed\xa0\x80", "\xf4\x90\x80\x80", "\xf5\x80\x80\x80",
      "\xe2\x82", ("a\x80" "b")};
  ipc_fixture_t fixture;
  my_pal_screen_ipc_client_t* first = NULL;
  my_pal_screen_ipc_client_t* second = NULL;
  char* maximum;
  char small[4];
  char output[64];
  size_t length;
  size_t i;
  ASSERT_TRUE(fixture_start(&fixture, NULL));
  ASSERT_EQ(my_pal_screen_ipc_client_open(NULL, fixture.path, &first), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_client_open(NULL, fixture.path, &second), MY_RET_OK);
  length = 99u;
  ASSERT_EQ(my_pal_screen_ipc_clipboard_get(first, output, sizeof(output), &length),
            MY_RET_NOT_FOUND);
  ASSERT_EQ(length, 0u);
  ASSERT_EQ(my_pal_screen_ipc_clipboard_set(first, NULL), MY_RET_INVALID_PARAMS);
  for (i = 0u; i < sizeof(invalid) / sizeof(invalid[0]); ++i) {
    ASSERT_EQ(my_pal_screen_ipc_clipboard_set(first, invalid[i]),
              MY_RET_INVALID_PARAMS);
  }
  ASSERT_EQ(my_pal_screen_ipc_clipboard_set(first, "\xf4\x8f\xbf\xbf"), MY_RET_OK);
  length = 0u;
  ASSERT_EQ(my_pal_screen_ipc_clipboard_get(second, small, sizeof(small), &length),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(length, 4u);
  ASSERT_EQ(my_pal_screen_ipc_clipboard_get(second, NULL, 0u, &length), MY_RET_OK);
  ASSERT_EQ(length, 4u);
  ASSERT_EQ(my_pal_screen_ipc_clipboard_get(second, output, sizeof(output), &length),
            MY_RET_OK);
  ASSERT_EQ(length, 4u);
  ASSERT_STR_EQ(output, "\xf4\x8f\xbf\xbf");
  ASSERT_EQ(my_pal_screen_ipc_clipboard_clear(second), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_clipboard_get(first, output, sizeof(output), &length),
            MY_RET_NOT_FOUND);
  ASSERT_EQ(my_pal_screen_ipc_clipboard_set(first, ""), MY_RET_OK);
  output[0] = 'x';
  ASSERT_EQ(my_pal_screen_ipc_clipboard_get(second, output, sizeof(output), &length),
            MY_RET_OK);
  ASSERT_EQ(length, 0u);
  ASSERT_STR_EQ(output, "");
  maximum = (char*)malloc(MY_PAL_SCREEN_IPC_MAX_TEXT_BYTES + 2u);
  ASSERT_NOT_NULL(maximum);
  memset(maximum, 'q', MY_PAL_SCREEN_IPC_MAX_TEXT_BYTES);
  maximum[MY_PAL_SCREEN_IPC_MAX_TEXT_BYTES] = '\0';
  maximum[MY_PAL_SCREEN_IPC_MAX_TEXT_BYTES + 1u] = '\0';
  ASSERT_EQ(my_pal_screen_ipc_clipboard_set(first, maximum), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_clipboard_get(second, NULL, 0u, &length), MY_RET_OK);
  ASSERT_EQ(length, MY_PAL_SCREEN_IPC_MAX_TEXT_BYTES);
  maximum[MY_PAL_SCREEN_IPC_MAX_TEXT_BYTES] = 'x';
  ASSERT_EQ(my_pal_screen_ipc_clipboard_set(first, maximum),
            MY_RET_INVALID_PARAMS);
  free(maximum);
  ASSERT_EQ(my_pal_screen_ipc_ime_preedit(first, "\xe4\xb8\xad", 2),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_screen_ipc_ime_preedit(first, "\xe4\xb8\xad", -1),
            MY_RET_INVALID_PARAMS);
  my_pal_screen_ipc_client_destroy(second);
  my_pal_screen_ipc_client_destroy(first);
  fixture_stop(&fixture);
}

static bool raw_expect_closed(const char* path, const uint8_t* frame,
                              size_t length, bool truncate) {
  struct pollfd pfd;
  uint8_t response[16];
  ssize_t count;
  int fd = raw_connect(path);
  int result;
  if (fd < 0) return false;
  if (!write_all(fd, frame, length)) {
    close(fd);
    return false;
  }
  if (truncate && shutdown(fd, SHUT_WR) != 0) {
    close(fd);
    return false;
  }
  pfd.fd = fd;
  pfd.events = POLLIN;
  pfd.revents = 0;
  do {
    result = poll(&pfd, 1u, 2000);
  } while (result < 0 && errno == EINTR);
  if (result <= 0) {
    close(fd);
    return false;
  }
  do {
    count = recv(fd, response, sizeof(response), 0);
  } while (count < 0 && errno == EINTR);
  close(fd);
  return count == 0 || (count < 0 && errno == ECONNRESET);
}

static bool raw_reject(const char* path, uint8_t type, const void* payload,
                       uint32_t length) {
  uint8_t frame[TEST_HEADER_SIZE + TEST_MAX_PAYLOAD];
  make_frame(frame, type, 7u, payload, length);
  return raw_expect_closed(path, frame, TEST_HEADER_SIZE + length, false);
}

TEST(wire_rejects_bad_headers_lengths_types_and_payloads)
{
  static const char* invalid[] = {
      "\x80", "\xc0\xaf", "\xe0\x80\xaf", "\xf0\x80\x80\xaf",
      "\xed\xa0\x80", "\xf4\x90\x80\x80", "\xf5\x80\x80\x80",
      "\xe2\x82"};
  ipc_fixture_t fixture;
  my_pal_screen_ipc_client_t* client = NULL;
  uint8_t frame[TEST_HEADER_SIZE + TEST_MAX_PAYLOAD];
  uint8_t payload[8];
  char output[32];
  size_t length;
  size_t i;
  ASSERT_TRUE(fixture_start(&fixture, NULL));
  make_frame(frame, TEST_REQ_CLIPBOARD_GET, 1u, NULL, 0u);
  frame[0] ^= 1u;
  ASSERT_TRUE(raw_expect_closed(fixture.path, frame, TEST_HEADER_SIZE, false));
  make_frame(frame, TEST_REQ_CLIPBOARD_GET, 1u, NULL, 0u);
  put16(frame + 4u, MY_PAL_SCREEN_IPC_PROTOCOL_VERSION + 1u);
  ASSERT_TRUE(raw_expect_closed(fixture.path, frame, TEST_HEADER_SIZE, false));
  make_frame(frame, TEST_REQ_CLIPBOARD_GET, 1u, NULL, 0u);
  frame[7] = 1u;
  ASSERT_TRUE(raw_expect_closed(fixture.path, frame, TEST_HEADER_SIZE, false));
  make_frame(frame, TEST_REQ_CLIPBOARD_GET, 1u, NULL, 0u);
  put32(frame + 12u, TEST_MAX_PAYLOAD + 1u);
  ASSERT_TRUE(raw_expect_closed(fixture.path, frame, TEST_HEADER_SIZE, false));
  ASSERT_TRUE(raw_reject(fixture.path, 0x7fu, NULL, 0u));
  ASSERT_TRUE(raw_reject(fixture.path, TEST_REQ_CLIPBOARD_GET, "x", 1u));
  ASSERT_TRUE(raw_reject(fixture.path, TEST_REQ_IME_PREEDIT, "x", 1u));
  memcpy(payload, "a\0b", 3u);
  ASSERT_TRUE(raw_reject(fixture.path, TEST_REQ_CLIPBOARD_SET, payload, 3u));
  for (i = 0u; i < sizeof(invalid) / sizeof(invalid[0]); ++i) {
    ASSERT_TRUE(raw_reject(fixture.path, TEST_REQ_CLIPBOARD_SET, invalid[i],
                           (uint32_t)strlen(invalid[i])));
  }
  put32(payload, 2u);
  payload[4] = 'a';
  ASSERT_TRUE(raw_reject(fixture.path, TEST_REQ_IME_PREEDIT, payload, 5u));
  put32(payload, 1u);
  ASSERT_TRUE(raw_reject(fixture.path, TEST_REQ_IME_COMMIT, payload, 5u));
  make_frame(frame, TEST_REQ_CLIPBOARD_SET, 9u, "abcd", 4u);
  ASSERT_TRUE(raw_expect_closed(fixture.path, frame, TEST_HEADER_SIZE + 2u, true));
  ASSERT_EQ(my_pal_screen_ipc_client_open(NULL, fixture.path, &client), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_clipboard_set(client, "still-alive"), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_clipboard_get(client, output, sizeof(output), &length),
            MY_RET_OK);
  ASSERT_STR_EQ(output, "still-alive");
  my_pal_screen_ipc_client_destroy(client);
  fixture_stop(&fixture);
}

TEST(two_clients_exchange_ime_in_both_directions)
{
  ipc_fixture_t fixture;
  my_pal_screen_ipc_client_t* first = NULL;
  my_pal_screen_ipc_client_t* second = NULL;
  my_pal_screen_ipc_ime_event_t event;
  ASSERT_TRUE(fixture_start(&fixture, NULL));
  ASSERT_EQ(my_pal_screen_ipc_client_open(NULL, fixture.path, &first), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_client_open(NULL, fixture.path, &second), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_ime_preedit(first, "not-subscribed", 3u), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_ime_set_subscribed(first, true), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_ime_set_subscribed(second, true), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_ime_preedit(first, "\xe4\xb8\xad", 1u), MY_RET_OK);
  memset(&event, 0, sizeof(event));
  ASSERT_EQ(my_pal_screen_ipc_ime_next_event(second, &event, 2000u), MY_RET_OK);
  ASSERT_EQ(event.type, MY_PAL_SCREEN_IPC_IME_PREEDIT);
  ASSERT_EQ(event.cursor, 1);
  ASSERT_EQ(event.length, 3u);
  ASSERT_STR_EQ(event.text, "\xe4\xb8\xad");
  ASSERT_TRUE(event.source_client_id != 0u);
  ASSERT_EQ(my_pal_screen_ipc_ime_next_event(first, &event, 0u), MY_RET_PENDING);
  ASSERT_EQ(my_pal_screen_ipc_ime_commit(second, "done"), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_ime_next_event(first, &event, 2000u), MY_RET_OK);
  ASSERT_EQ(event.type, MY_PAL_SCREEN_IPC_IME_COMMIT);
  ASSERT_EQ(event.cursor, 0);
  ASSERT_STR_EQ(event.text, "done");
  ASSERT_EQ(my_pal_screen_ipc_ime_set_subscribed(first, false), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_ime_preedit(second, "ignored", 2u), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_ime_next_event(first, &event, 0u), MY_RET_PENDING);
  my_pal_screen_ipc_client_destroy(second);
  my_pal_screen_ipc_client_destroy(first);
  fixture_stop(&fixture);
}

static const char* ipc_program_path;

#if defined(__QNXNTO__)
extern char** environ;
#endif

static int ipc_process_child_main(const char* path, int read_fd, int write_fd) {
  my_pal_screen_ipc_client_t* client = NULL;
  my_pal_screen_ipc_ime_event_t event;
  char output[64];
  size_t length;
  char stage;
  int result = 10;
  if (my_pal_screen_ipc_client_open(NULL, path, &client) != MY_RET_OK) goto done;
  result = 11;
  if (my_pal_screen_ipc_clipboard_set(client, "from-child") != MY_RET_OK ||
      my_pal_screen_ipc_ime_set_subscribed(client, true) != MY_RET_OK ||
      !pipe_write(write_fd, 'R')) {
    goto done;
  }
  result = 12;
  if (!pipe_read(read_fd, &stage) || stage != 'G') goto done;
  memset(&event, 0, sizeof(event));
  result = 13;
  if (my_pal_screen_ipc_ime_next_event(client, &event, 3000u) != MY_RET_OK ||
      event.type != MY_PAL_SCREEN_IPC_IME_PREEDIT || event.cursor != 1 ||
      strcmp(event.text, "\xe4\xb8\xad") != 0) {
    goto done;
  }
  result = 14;
  if (my_pal_screen_ipc_ime_commit(client, "child-commit") != MY_RET_OK ||
      !pipe_write(write_fd, 'C')) {
    goto done;
  }
  result = 15;
  if (!pipe_read(read_fd, &stage) || stage != 'X') goto done;
  result = 16;
  if (my_pal_screen_ipc_clipboard_get(client, output, sizeof(output), &length) !=
      MY_RET_NOT_FOUND) {
    goto done;
  }
  result = 0;
done:
  my_pal_screen_ipc_client_destroy(client);
  close(read_fd);
  close(write_fd);
  if (result != 0) fprintf(stderr, "IPC child failed at stage %d\n", result);
  return result;
}

static bool ipc_parse_fd(const char* text, int* out_fd) {
  char* end = NULL;
  long value;
  errno = 0;
  value = strtol(text, &end, 10);
  if (errno != 0 || end == text || *end != '\0' || value < 0 || value > INT_MAX) {
    return false;
  }
  *out_fd = (int)value;
  return true;
}

#if defined(__QNXNTO__)
static int ipc_spawn_child(pid_t* child, const char* path, int read_fd,
                           int write_fd, int parent_write_fd,
                           int child_read_fd) {
  posix_spawn_file_actions_t actions;
  posix_spawnattr_t attributes;
  const char* program = getenv("BREAK_MYPAL_IPC_CHILD_EXECUTABLE");
  char read_text[16];
  char write_text[16];
  char* arguments[6];
  char** child_envp;
  int result;
  if (program == NULL || program[0] == '\0') program = ipc_program_path;
  (void)snprintf(read_text, sizeof(read_text), "%d", read_fd);
  (void)snprintf(write_text, sizeof(write_text), "%d", write_fd);
  arguments[0] = (char*)program;
  arguments[1] = (char*)"--ipc-process-child";
  arguments[2] = (char*)path;
  arguments[3] = read_text;
  arguments[4] = write_text;
  arguments[5] = NULL;
  result = posix_spawnattr_init(&attributes);
  if (result != 0) return result;
  result = posix_spawnattr_setaslr(&attributes, POSIX_SPAWN_ASLR_DISABLE);
  if (result != 0) {
    (void)posix_spawnattr_destroy(&attributes);
    return result;
  }
  result = posix_spawn_file_actions_init(&actions);
  if (result != 0) {
    (void)posix_spawnattr_destroy(&attributes);
    return result;
  }
  result = posix_spawn_file_actions_addclose(&actions, parent_write_fd);
  if (result == 0) {
    result = posix_spawn_file_actions_addclose(&actions, child_read_fd);
  }
  if (result == 0) {
    child_envp =
        test_qnx_spawn_child_envp(getenv("BREAK_MYPAL_IPC_CHILD_EXECUTABLE"));
    if (child_envp == NULL) {
      result = ENOMEM;
    } else {
      result = posix_spawn(child, program, &actions, &attributes, arguments, child_envp);
    }
    test_qnx_spawn_child_envp_destroy(child_envp);
  }
  (void)posix_spawn_file_actions_destroy(&actions);
  (void)posix_spawnattr_destroy(&attributes);
  return result;
}
#endif

TEST(forked_clients_share_clipboard_and_ime)
{
  ipc_fixture_t fixture;
  int parent_to_child[2];
  int child_to_parent[2];
  pid_t child;
  char stage;
  int status;
  my_pal_screen_ipc_client_t* parent = NULL;
  my_pal_screen_ipc_ime_event_t event;
  char output[64];
  size_t length;
  ASSERT_TRUE(fixture_start(&fixture, NULL));
  ASSERT_EQ(pipe(parent_to_child), 0);
  ASSERT_EQ(pipe(child_to_parent), 0);
#if defined(__QNXNTO__)
  {
    int spawn_error = ipc_spawn_child(&child, fixture.path, parent_to_child[0],
                                      child_to_parent[1], parent_to_child[1],
                                      child_to_parent[0]);
    if (spawn_error != 0) {
      printf("\n  posix_spawn failed: error=%d (%s)\n", spawn_error,
             strerror(spawn_error));
    }
    ASSERT_EQ(spawn_error, 0);
  }
#else
  child = fork();
  if (child < 0) {
    int fork_errno = errno;
    printf("\n  fork failed: errno=%d (%s)\n", fork_errno, strerror(fork_errno));
  }
  ASSERT_TRUE(child >= 0);
  if (child == 0) {
    close(parent_to_child[1]);
    close(child_to_parent[0]);
    _exit(ipc_process_child_main(fixture.path, parent_to_child[0],
                                 child_to_parent[1]));
  }
#endif
  close(parent_to_child[0]);
  close(child_to_parent[1]);
  ASSERT_EQ(my_pal_screen_ipc_client_open(NULL, fixture.path, &parent), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_ime_set_subscribed(parent, true), MY_RET_OK);
  ASSERT_TRUE(pipe_read(child_to_parent[0], &stage));
  ASSERT_EQ(stage, 'R');
  ASSERT_EQ(my_pal_screen_ipc_clipboard_get(parent, output, sizeof(output), &length),
            MY_RET_OK);
  ASSERT_STR_EQ(output, "from-child");
  ASSERT_EQ(my_pal_screen_ipc_clipboard_clear(parent), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_ime_preedit(parent, "\xe4\xb8\xad", 1), MY_RET_OK);
  ASSERT_TRUE(pipe_write(parent_to_child[1], 'G'));
  ASSERT_TRUE(pipe_read(child_to_parent[0], &stage));
  ASSERT_EQ(stage, 'C');
  ASSERT_EQ(my_pal_screen_ipc_ime_next_event(parent, &event, 3000u), MY_RET_OK);
  ASSERT_EQ(event.type, MY_PAL_SCREEN_IPC_IME_COMMIT);
  ASSERT_STR_EQ(event.text, "child-commit");
  ASSERT_TRUE(pipe_write(parent_to_child[1], 'X'));
  ASSERT_EQ(waitpid(child, &status, 0), child);
  ASSERT_TRUE(WIFEXITED(status));
  ASSERT_EQ(WEXITSTATUS(status), 0);
  close(parent_to_child[1]);
  close(child_to_parent[0]);
  my_pal_screen_ipc_client_destroy(parent);
  fixture_stop(&fixture);
}

typedef struct stress_args_t {
  my_pal_screen_ipc_client_t* shared;
  const char* path;
  atomic_int* failures;
  uint32_t id;
} stress_args_t;

static void* stress_main(void* opaque) {
  static const char* values[] = {"alpha", "beta", "gamma", "delta"};
  stress_args_t* args = (stress_args_t*)opaque;
  my_pal_screen_ipc_client_t* client = args->shared;
  char output[32];
  size_t length;
  uint32_t i;
  if (client == NULL &&
      my_pal_screen_ipc_client_open(NULL, args->path, &client) != MY_RET_OK) {
    atomic_fetch_add(args->failures, 1);
    return NULL;
  }
  for (i = 0u; i < 40u; ++i) {
    const char* expected = values[(args->id + i) % 4u];
    my_ret_t set_result = my_pal_screen_ipc_clipboard_set(client, expected);
    my_ret_t get_result = MY_RET_FAIL;
    my_ret_t clear_result;
    size_t j;
    bool matches = false;
    if (set_result == MY_RET_OK) {
      get_result =
          my_pal_screen_ipc_clipboard_get(client, output, sizeof(output), &length);
    }
    if (set_result != MY_RET_OK ||
        (get_result != MY_RET_OK && get_result != MY_RET_NOT_FOUND)) {
      printf("\n  stress id=%u iteration=%u set=%d get=%d\n", args->id, i,
             set_result, get_result);
      atomic_fetch_add(args->failures, 1);
      break;
    }
    if (get_result == MY_RET_OK) {
      for (j = 0u; j < 4u; ++j) {
        if (strcmp(output, values[j]) == 0 && length == strlen(values[j])) {
          matches = true;
        }
      }
      if (!matches) atomic_fetch_add(args->failures, 1);
    }
    clear_result = my_pal_screen_ipc_clipboard_clear(client);
    if (clear_result != MY_RET_OK) {
      printf("\n  stress id=%u iteration=%u clear=%d\n", args->id, i,
             clear_result);
      atomic_fetch_add(args->failures, 1);
      break;
    }
  }
  if (args->shared == NULL) my_pal_screen_ipc_client_destroy(client);
  return NULL;
}

static void run_stress(bool shared, const my_allocator_t* server_allocator) {
  ipc_fixture_t fixture;
  my_pal_screen_ipc_client_t* client = NULL;
  pthread_t threads[4];
  stress_args_t args[4];
  atomic_int failures;
  uint32_t created = 0u;
  uint32_t i;
  ASSERT_TRUE(fixture_start(&fixture, server_allocator));
  if (shared) {
    ASSERT_EQ(my_pal_screen_ipc_client_open(NULL, fixture.path, &client), MY_RET_OK);
  }
  atomic_init(&failures, 0);
  for (i = 0u; i < 4u; ++i) {
    args[i].shared = client;
    args[i].path = fixture.path;
    args[i].failures = &failures;
    args[i].id = i;
    if (pthread_create(&threads[i], NULL, stress_main, &args[i]) != 0) break;
    created++;
  }
  for (i = 0u; i < created; ++i) pthread_join(threads[i], NULL);
  my_pal_screen_ipc_client_destroy(client);
  fixture_stop(&fixture);
  ASSERT_EQ(created, 4u);
  ASSERT_EQ(atomic_load(&failures), 0);
}

TEST(concurrent_clients_and_shared_client_are_serialized)
{
  run_stress(false, NULL);
  run_stress(true, NULL);
}

TEST(concurrent_server_allocator_is_serialized)
{
  my_allocator_t* debug = my_allocator_debug_create(NULL);
  ASSERT_NOT_NULL(debug);
  run_stress(false, debug);
  ASSERT_EQ(my_allocator_debug_leak_count(debug), 0);
  my_allocator_debug_destroy(debug);
}

typedef struct signal_stress_args_t {
  pthread_t target;
  atomic_bool wait_returned;
  atomic_bool returned_while_signaling;
  int error;
} signal_stress_args_t;

static volatile sig_atomic_t test_signal_count;

static void test_signal_handler(int signal_number) {
  (void)signal_number;
  test_signal_count++;
}

static void* signal_stress_main(void* opaque) {
  signal_stress_args_t* args = (signal_stress_args_t*)opaque;
  struct timespec delay;
  uint32_t i;
  delay.tv_sec = 0;
  delay.tv_nsec = 1000000L;
  for (i = 0u; i < 300u; ++i) {
    while (nanosleep(&delay, &delay) != 0 && errno == EINTR) {
    }
    delay.tv_sec = 0;
    delay.tv_nsec = 1000000L;
    if (atomic_load_explicit(&args->wait_returned, memory_order_acquire)) {
      atomic_store_explicit(&args->returned_while_signaling, true,
                            memory_order_release);
      break;
    }
    args->error = pthread_kill(args->target, SIGUSR1);
    if (args->error != 0) break;
  }
  return NULL;
}

TEST(client_wait_eintr_keeps_original_deadline)
{
  ipc_fixture_t fixture;
  my_pal_screen_ipc_client_t* client = NULL;
  my_pal_screen_ipc_ime_event_t event;
  struct sigaction action;
  struct sigaction previous;
  signal_stress_args_t args;
  pthread_t signal_thread;
  my_ret_t result;
  ASSERT_TRUE(fixture_start(&fixture, NULL));
  ASSERT_EQ(my_pal_screen_ipc_client_open(NULL, fixture.path, &client), MY_RET_OK);
  memset(&action, 0, sizeof(action));
  action.sa_handler = test_signal_handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  test_signal_count = 0;
  ASSERT_EQ(sigaction(SIGUSR1, &action, &previous), 0);
  args.target = pthread_self();
  args.error = 0;
  atomic_init(&args.wait_returned, false);
  atomic_init(&args.returned_while_signaling, false);
  ASSERT_EQ(pthread_create(&signal_thread, NULL, signal_stress_main, &args), 0);
  result = my_pal_screen_ipc_ime_next_event(client, &event, 40u);
  atomic_store_explicit(&args.wait_returned, true, memory_order_release);
  pthread_join(signal_thread, NULL);
  ASSERT_EQ(sigaction(SIGUSR1, &previous, NULL), 0);
  my_pal_screen_ipc_client_destroy(client);
  fixture_stop(&fixture);
  ASSERT_EQ(result, MY_RET_PENDING);
  ASSERT_EQ(args.error, 0);
  ASSERT_TRUE(test_signal_count > 0);
  ASSERT_TRUE(atomic_load_explicit(&args.returned_while_signaling,
                                   memory_order_acquire));
}

typedef struct fake_server_args_t {
  int listen_fd;
  uint32_t mode;
  int result;
} fake_server_args_t;

static void* fake_server_main(void* opaque) {
  fake_server_args_t* args = (fake_server_args_t*)opaque;
  uint8_t header[TEST_HEADER_SIZE];
  uint8_t response[TEST_HEADER_SIZE + 8u];
  uint8_t payload[TEST_MAX_PAYLOAD];
  uint32_t length;
  uint32_t id;
  int fd = accept(args->listen_fd, NULL, NULL);
  if (fd < 0) {
    args->result = 1;
    return NULL;
  }
  if (!read_all(fd, header, sizeof(header))) {
    args->result = 2;
    close(fd);
    return NULL;
  }
  length = get32(header + 12u);
  id = get32(header + 8u);
  if (length > sizeof(payload) || !read_all(fd, payload, length)) {
    args->result = 3;
    close(fd);
    return NULL;
  }
  put32(payload, 0u);
  if (args->mode == 1u) {
    payload[4] = 0xc0u;
    payload[5] = 0xafu;
    length = 6u;
  } else {
    length = 4u;
  }
  make_frame(response, TEST_RESPONSE, args->mode == 2u ? id + 1u : id,
             payload, length);
  if (args->mode == 0u) {
    put16(response + 4u, MY_PAL_SCREEN_IPC_PROTOCOL_VERSION + 1u);
  } else if (args->mode == 3u) {
    put32(response + 12u, TEST_MAX_PAYLOAD + 1u);
  }
  if (!write_all(fd, response, TEST_HEADER_SIZE +
                                (args->mode == 3u ? 0u : length))) {
    args->result = 4;
  }
  close(fd);
  return NULL;
}

TEST(client_rejects_malformed_server_responses)
{
  uint32_t mode;
  for (mode = 0u; mode < 4u; ++mode) {
    char path[256];
    struct sockaddr_un address;
    fake_server_args_t args;
    pthread_t thread;
    my_pal_screen_ipc_client_t* client = NULL;
    size_t length;
    size_t path_length;
    test_tmp(path, sizeof(path), "screen_ipc_fake");
    (void)unlink(path);
    args.listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    args.mode = mode;
    args.result = 0;
    ASSERT_TRUE(args.listen_fd >= 0);
    memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;
    path_length = strlen(path);
    memcpy(address.sun_path, path, path_length + 1u);
#if defined(__QNXNTO__)
    address.sun_len = (unsigned char)sizeof(address);
#endif
    ASSERT_EQ(bind(args.listen_fd, (struct sockaddr*)&address,
                   (socklen_t)sizeof(address)), 0);
    ASSERT_EQ(listen(args.listen_fd, 1), 0);
    ASSERT_EQ(pthread_create(&thread, NULL, fake_server_main, &args), 0);
    ASSERT_EQ(my_pal_screen_ipc_client_open(NULL, path, &client), MY_RET_OK);
    ASSERT_EQ(my_pal_screen_ipc_clipboard_get(client, NULL, 0u, &length),
              MY_RET_FAIL);
    my_pal_screen_ipc_client_destroy(client);
    pthread_join(thread, NULL);
    ASSERT_EQ(args.result, 0);
    close(args.listen_fd);
    (void)unlink(path);
  }
}

TEST(shutdown_reclaims_clients_paths_and_allocations)
{
  my_allocator_t* debug = my_allocator_debug_create(NULL);
  ipc_fixture_t fixture;
  my_pal_screen_ipc_client_t* first = NULL;
  my_pal_screen_ipc_client_t* second = NULL;
  char output[32];
  size_t length;
  uint32_t i;
  ASSERT_NOT_NULL(debug);
  ASSERT_TRUE(fixture_start(&fixture, debug));
  ASSERT_EQ(my_pal_screen_ipc_client_open(debug, fixture.path, &first), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_clipboard_set(first, "allocated"), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_clipboard_get(first, output, sizeof(output), &length),
            MY_RET_OK);
  ASSERT_STR_EQ(output, "allocated");
  my_pal_screen_ipc_client_destroy(first);
  first = NULL;
  fixture_stop(&fixture);
  ASSERT_EQ(my_allocator_debug_leak_count(debug), 0);
  ASSERT_EQ(access(fixture.path, F_OK), -1);
  ASSERT_EQ(my_pal_screen_ipc_client_open(NULL, fixture.path, &first), MY_RET_FAIL);
  my_allocator_debug_destroy(debug);
  ASSERT_TRUE(fixture_start(&fixture, NULL));
  for (i = 0u; i < 24u; ++i) {
    ASSERT_EQ(my_pal_screen_ipc_client_open(NULL, fixture.path, &first), MY_RET_OK);
    ASSERT_EQ(my_pal_screen_ipc_clipboard_set(first, "recycle"), MY_RET_OK);
    my_pal_screen_ipc_client_destroy(first);
    first = NULL;
  }
  ASSERT_EQ(my_pal_screen_ipc_client_open(NULL, fixture.path, &first), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_ipc_client_open(NULL, fixture.path, &second), MY_RET_OK);
  fixture_stop(&fixture);
  ASSERT_EQ(my_pal_screen_ipc_clipboard_set(first, "closed"), MY_RET_FAIL);
  ASSERT_EQ(my_pal_screen_ipc_clipboard_set(second, "closed"), MY_RET_FAIL);
  my_pal_screen_ipc_client_destroy(second);
  my_pal_screen_ipc_client_destroy(first);
}

int main(int argc, char** argv) {
  setvbuf(stdout, NULL, _IONBF, 0);
  if (argc == 5 && strcmp(argv[1], "--ipc-process-child") == 0) {
    int read_fd;
    int write_fd;
    if (!ipc_parse_fd(argv[3], &read_fd) || !ipc_parse_fd(argv[4], &write_fd)) {
      return 64;
    }
    return ipc_process_child_main(argv[2], read_fd, write_fd);
  }
  ipc_program_path = argv[0];
  printf("=== Running Tests ===\n");
  RUN_TEST(api_rejects_invalid_arguments_and_unknown_endpoint);
  RUN_TEST(clipboard_round_trip_boundaries_and_utf8);
  RUN_TEST(wire_rejects_bad_headers_lengths_types_and_payloads);
  RUN_TEST(two_clients_exchange_ime_in_both_directions);
  RUN_TEST(forked_clients_share_clipboard_and_ime);
  RUN_TEST(concurrent_clients_and_shared_client_are_serialized);
  RUN_TEST(concurrent_server_allocator_is_serialized);
  RUN_TEST(client_wait_eintr_keeps_original_deadline);
  RUN_TEST(client_rejects_malformed_server_responses);
  RUN_TEST(shutdown_reclaims_clients_paths_and_allocations);
  printf("\n=== Results: %d passed, %d failed, %d total ===\n",
         g_test_pass, g_test_fail, g_test_count);
  return g_test_fail > 0 ? 1 : 0;
}
