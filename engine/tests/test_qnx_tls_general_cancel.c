#include "qnx_tls_general_interpose.h"

#include <dlfcn.h>
#include <openssl/evp.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static QnxTlsGeneralStats *stats;
static pthread_key_t key;
static volatile unsigned ready;
static unsigned destructor_calls;

static void key_destructor(void *value)
{
    (void)__atomic_add_fetch(&destructor_calls, 1u, __ATOMIC_SEQ_CST);
    free(value);
}

static void *worker(void *arg)
{
    unsigned char digest[32];
    unsigned int digest_len = 0;
    void *value;
    (void)arg;
    (void)pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    (void)pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    value = malloc(32);
    if (!value) return (void *)1;
    if (pthread_setspecific(key, value) != 0) {
        free(value);
        return (void *)2;
    }
    if (EVP_Digest("abc", 3, digest, &digest_len, EVP_sha256(), NULL) != 1)
        return (void *)3;
    (void)__atomic_add_fetch(&ready, 1u, __ATOMIC_SEQ_CST);
    for (;;) usleep(10000u);
    return NULL;
}

int main(void)
{
    pthread_t thread;
    void *result = NULL;
    unsigned spins = 0;
    int rc = 0;
    setvbuf(stdout, NULL, _IOLBF, 0);
    stats = (QnxTlsGeneralStats *)dlsym(RTLD_DEFAULT, "qnx_tls_general_stats");
    if (!stats) return 2;
    if (pthread_key_create(&key, key_destructor) != 0) return 3;
    if (pthread_create(&thread, NULL, worker, NULL) != 0) return 4;
    while (!__atomic_load_n(&ready, __ATOMIC_SEQ_CST) && spins++ < 1000000u)
        sched_yield();
    if (!__atomic_load_n(&ready, __ATOMIC_SEQ_CST)) rc = 5;
    if (pthread_cancel(thread) != 0) rc = 6;
    if (pthread_join(thread, &result) != 0) rc = 7;
    printf("cancel result=%p expected=%p key_exit=%lu enter=%lu leave=%lu destructors=%u failures=%lu\n",
           result, PTHREAD_CANCELED,
           qnx_tls_general_load(&stats->key_exit_calls),
           qnx_tls_general_load(&stats->enter_count),
           qnx_tls_general_load(&stats->leave_count),
           __atomic_load_n(&destructor_calls, __ATOMIC_SEQ_CST),
           qnx_tls_general_load(&stats->failures));
    if (pthread_key_delete(key) != 0) rc = 8;
    if (result != PTHREAD_CANCELED ||
        __atomic_load_n(&destructor_calls, __ATOMIC_SEQ_CST) != 1 ||
        qnx_tls_general_load(&stats->key_exit_calls) == 0 ||
        qnx_tls_general_load(&stats->failures) != 0) rc = 9;
    if (rc == 0) puts("PASS qnx tls general deferred cancel");
    return rc;
}
