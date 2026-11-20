/* QNX SDP 8.0 ASan test support. Reserve TLS keydata capacity before
 * OpenSSL expands it: libc reallocates the old array while ASan still expects
 * to read its thread context from that array. The old allocation remains owned
 * by libc and is restored before process teardown. Automatic reservation is
 * main-thread only; workers require explicit scoped enter/leave after their
 * TLS cleanup. This is not a product runtime patch or a generic worker fix. */
#include <stdlib.h>
#include <string.h>
#include <sys/nto_version.h>
#include <sys/storage.h>

#if !defined(__QNXNTO__) || _NTO_VERSION != 800
#error "qnx_asan_tls_capacity requires the QNX SDP 8.0 TLS layout"
#endif

#define QNX_ASAN_TEST_TLS_CAPACITY 128u

typedef struct {
  void** old_data;
  unsigned old_count;
  void** replacement;
} tls_scope_t;

static int tls_scope_enter(tls_scope_t* scope) {
  struct _thread_local_storage* tls = __tls();
  memset(scope, 0, sizeof(*scope));
  if (tls->__numkeys >= QNX_ASAN_TEST_TLS_CAPACITY) return 0;
  scope->replacement =
      (void**)malloc(QNX_ASAN_TEST_TLS_CAPACITY * sizeof(*scope->replacement));
  if (scope->replacement == NULL) return -1;
  if (tls->__numkeys != 0u) {
    memcpy(scope->replacement, tls->__keydata,
           tls->__numkeys * sizeof(*scope->replacement));
  }
  memset(scope->replacement + tls->__numkeys, 0,
         (QNX_ASAN_TEST_TLS_CAPACITY - tls->__numkeys) *
             sizeof(*scope->replacement));
  scope->old_data = tls->__keydata;
  scope->old_count = tls->__numkeys;
  tls->__keydata = scope->replacement;
  tls->__numkeys = QNX_ASAN_TEST_TLS_CAPACITY;
  return 0;
}

static void tls_scope_leave(tls_scope_t* scope) {
  struct _thread_local_storage* tls;
  if (scope->replacement == NULL) return;
  tls = __tls();
  if (tls->__keydata != scope->replacement ||
      tls->__numkeys != QNX_ASAN_TEST_TLS_CAPACITY)
    abort();
  tls->__keydata = scope->old_data;
  tls->__numkeys = scope->old_count;
  free(scope->replacement);
  memset(scope, 0, sizeof(*scope));
}

static tls_scope_t main_scope;

static void restore_main_tls(void) {
  tls_scope_leave(&main_scope);
}

static void reserve_main_tls(void) {
  if (tls_scope_enter(&main_scope) != 0) abort();
  if (atexit(restore_main_tls) != 0) {
    restore_main_tls();
    abort();
  }
}

__attribute__((section(".preinit_array"), used))
static void (*const reserve_main_tls_entry)(void) = reserve_main_tls;

#if defined(QNX_ASAN_TLS_CAPACITY_TEST)
#include "test_framework.h"

#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <pthread.h>

#define TLS_TEST_THREAD_COUNT 8u
#define TLS_TEST_DIGEST_LOOPS 64u

static void* tls_test_worker(void* arg) {
  static const unsigned char expected[32] = {
      0xba, 0x78, 0x16, 0xbf, 0x8f, 0x01, 0xcf, 0xea,
      0x41, 0x41, 0x40, 0xde, 0x5d, 0xae, 0x22, 0x23,
      0xb0, 0x03, 0x61, 0xa3, 0x96, 0x17, 0x7a, 0x9c,
      0xb4, 0x10, 0xff, 0x61, 0xf2, 0x00, 0x15, 0xad};
  tls_scope_t scope;
  unsigned char digest[32];
  unsigned int digest_len;
  void* allocation;
  void* resized;
  unsigned i;
  int result = 0;
  (void)arg;
  if (tls_scope_enter(&scope) != 0) return (void*)1;
  allocation = malloc(8u);
  if (allocation == NULL) {
    result = 2;
  } else {
    resized = realloc(allocation, 64u);
    if (resized == NULL) {
      free(allocation);
      result = 2;
    } else {
      free(resized);
    }
  }
  for (i = 0u; result == 0 && i < TLS_TEST_DIGEST_LOOPS; i++) {
    digest_len = 0u;
    if (EVP_Digest("abc", 3u, digest, &digest_len, EVP_sha256(), NULL) != 1 ||
        digest_len != sizeof(digest) ||
        memcmp(digest, expected, sizeof(expected)) != 0)
      result = 3;
  }
  OPENSSL_thread_stop();
  tls_scope_leave(&scope);
  return (void*)(long)result;
}

TEST(main_thread_tls_capacity_is_reserved) {
  ASSERT_TRUE(__tls()->__numkeys >= QNX_ASAN_TEST_TLS_CAPACITY);
}

TEST(scoped_worker_tls_capacity_supports_openssl_and_allocations) {
  pthread_t threads[TLS_TEST_THREAD_COUNT];
  size_t created = 0u;
  size_t i;
  int failed = 0;
  for (i = 0u; i < TLS_TEST_THREAD_COUNT; i++) {
    if (pthread_create(&threads[i], NULL, tls_test_worker, NULL) != 0) {
      failed = 1;
      break;
    }
    created++;
  }
  for (i = 0u; i < created; i++) {
    void* result = NULL;
    if (pthread_join(threads[i], &result) != 0 || result != NULL)
      failed = 1;
  }
  ASSERT_FALSE(failed);
}

TEST_MAIN_BEGIN()
  RUN_TEST(main_thread_tls_capacity_is_reserved);
  RUN_TEST(scoped_worker_tls_capacity_supports_openssl_and_allocations);
TEST_MAIN_END()
#endif
