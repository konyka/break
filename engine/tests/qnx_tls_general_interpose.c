#include "qnx_tls_general_interpose.h"

#include <dlfcn.h>
#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/nto_version.h>
#include <sys/storage.h>

#if !defined(__QNXNTO__) || _NTO_VERSION != 800 || !defined(__x86_64__)
#error "qnx_tls_general_interpose requires QNX SDP 8.0 x86_64"
#endif

#define QNX_TLS_GENERAL_CAPACITY 128u

_Static_assert(offsetof(struct _thread_local_storage, __numkeys) == 60u,
               "QNX SDP 8.0 x86_64 TLS numkeys ABI");
_Static_assert(offsetof(struct _thread_local_storage, __keydata) == 64u,
               "QNX SDP 8.0 x86_64 TLS keydata ABI");
_Static_assert(PTHREAD_KEYS_MAX == QNX_TLS_GENERAL_CAPACITY,
               "QNX SDP 8.0 pthread key capacity");

typedef struct {
    void **old_data;
    unsigned old_count;
    void **replacement;
    unsigned entering;
    int active;
} QnxTlsGeneralScope;

QnxTlsGeneralStats qnx_tls_general_stats;

static __thread QnxTlsGeneralScope current_scope;
static int (*next_setspecific)(pthread_key_t, const void *);
static void (*next_key_exit)(void);

static void stats_inc(unsigned long *value)
{
    (void)__atomic_add_fetch(value, 1ul, __ATOMIC_SEQ_CST);
}

static void resolve_next(void)
{
    void *symbol;
    if (!next_setspecific) {
        symbol = dlsym(RTLD_NEXT, "pthread_setspecific");
        memcpy(&next_setspecific, &symbol, sizeof(symbol));
    }
    if (!next_key_exit) {
        symbol = dlsym(RTLD_NEXT, "__pthread_key_exit");
        memcpy(&next_key_exit, &symbol, sizeof(symbol));
    }
}

static int enter_current_thread(void)
{
    struct _thread_local_storage *tls = __tls();
    void **replacement;
    if (current_scope.active || tls->__numkeys >= QNX_TLS_GENERAL_CAPACITY) return 0;
    if (current_scope.entering) {
        stats_inc(&qnx_tls_general_stats.failures);
        return EDEADLK;
    }
    current_scope.entering = 1;
    replacement = (void **)malloc(QNX_TLS_GENERAL_CAPACITY * sizeof(*replacement));
    if (!replacement) {
        current_scope.entering = 0;
        stats_inc(&qnx_tls_general_stats.failures);
        return ENOMEM;
    }
    if (tls->__numkeys) {
        memcpy(replacement, tls->__keydata,
               tls->__numkeys * sizeof(*replacement));
    }
    memset(replacement + tls->__numkeys, 0,
           (QNX_TLS_GENERAL_CAPACITY - tls->__numkeys) * sizeof(*replacement));
    current_scope.old_data = tls->__keydata;
    current_scope.old_count = tls->__numkeys;
    current_scope.replacement = replacement;
    tls->__keydata = replacement;
    tls->__numkeys = QNX_TLS_GENERAL_CAPACITY;
    current_scope.active = 1;
    current_scope.entering = 0;
    stats_inc(&qnx_tls_general_stats.enter_count);
    return 0;
}

static void leave_current_thread(void)
{
    struct _thread_local_storage *tls = __tls();
    void **replacement;
    if (!current_scope.active) return;
    if (tls->__keydata != current_scope.replacement ||
        tls->__numkeys != QNX_TLS_GENERAL_CAPACITY) {
        stats_inc(&qnx_tls_general_stats.failures);
        abort();
    }
    if (current_scope.old_count && current_scope.old_data) {
        memcpy(current_scope.old_data, current_scope.replacement,
               current_scope.old_count * sizeof(*current_scope.old_data));
    }
    replacement = current_scope.replacement;
    tls->__keydata = current_scope.old_data;
    tls->__numkeys = current_scope.old_count;
    current_scope.old_data = NULL;
    current_scope.old_count = 0;
    current_scope.replacement = NULL;
    current_scope.active = 0;
    free(replacement);
    stats_inc(&qnx_tls_general_stats.leave_count);
}

int pthread_setspecific(pthread_key_t key, const void *value)
{
    int rc;
    resolve_next();
    if (!next_setspecific) {
        stats_inc(&qnx_tls_general_stats.failures);
        return ENOSYS;
    }
    stats_inc(&qnx_tls_general_stats.setspecific_calls);
    if (current_scope.entering) return next_setspecific(key, value);
    rc = enter_current_thread();
    if (rc != 0) return rc;
    return next_setspecific(key, value);
}

void __pthread_key_exit(void)
{
    resolve_next();
    if (!next_key_exit) {
        stats_inc(&qnx_tls_general_stats.failures);
        abort();
    }
    stats_inc(&qnx_tls_general_stats.key_exit_calls);
    next_key_exit();
    leave_current_thread();
    qnx_tls_general_store(&qnx_tls_general_stats.last_event, 3);
}

static void main_leave(void)
{
    leave_current_thread();
    stats_inc(&qnx_tls_general_stats.main_leave_calls);
    qnx_tls_general_store(&qnx_tls_general_stats.last_event, 4);
}

__attribute__((constructor)) static void interpose_construct(void)
{
    resolve_next();
    if (!next_setspecific || !next_key_exit) {
        stats_inc(&qnx_tls_general_stats.failures);
        abort();
    }
    if (enter_current_thread() != 0) abort();
}

__attribute__((destructor)) static void interpose_destruct(void)
{
    main_leave();
    stats_inc(&qnx_tls_general_stats.dso_fini_calls);
    qnx_tls_general_store(&qnx_tls_general_stats.last_event, 5);
}
