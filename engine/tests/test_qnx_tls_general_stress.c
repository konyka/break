#include "qnx_tls_general_interpose.h"

#include <dlfcn.h>
#include <openssl/evp.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NORMAL_DIGESTS 256u
#define NORMAL_ALLOCS 512u
#define REPEAT_ROUNDS 32u
#define REPEAT_DIGESTS 64u
#define REPEAT_ALLOCS 128u
#define CANCEL_ROUNDS 8u
#define DETACHED_ROUNDS 2u
#define DETACHED_DIGESTS 64u
#define DETACHED_ALLOCS 128u

static const unsigned char expected[32] = {
    0xba, 0x78, 0x16, 0xbf, 0x8f, 0x01, 0xcf, 0xea,
    0x41, 0x41, 0x40, 0xde, 0x5d, 0xae, 0x22, 0x23,
    0xb0, 0x03, 0x61, 0xa3, 0x96, 0x17, 0x7a, 0x9c,
    0xb4, 0x10, 0xff, 0x61, 0xf2, 0x00, 0x15, 0xad
};

typedef struct {
    unsigned digests;
    unsigned allocs;
    int explicit_exit;
} Work;

typedef struct {
    volatile unsigned ready;
    unsigned count;
} CancelGroup;

typedef struct {
    volatile unsigned completed;
    volatile unsigned failed;
    Work work;
} DetachedWork;

static QnxTlsGeneralStats *stats;
static pthread_key_t stress_key;
static unsigned long destructor_count;
static unsigned long expected_destructors;

static void key_destructor(void *value)
{
    (void)__atomic_add_fetch(&destructor_count, 1ul, __ATOMIC_SEQ_CST);
    free(value);
}

static int exercise(unsigned digests, unsigned allocs)
{
    unsigned char digest[32];
    unsigned i;
    void *value = malloc(32);
    if (!value) return 1;
    if (pthread_setspecific(stress_key, value) != 0) {
        free(value);
        return 2;
    }
    for (i = 0; i < digests; i++) {
        unsigned int digest_len = 0;
        if (EVP_Digest("abc", 3, digest, &digest_len, EVP_sha256(), NULL) != 1 ||
            digest_len != sizeof(digest) ||
            memcmp(digest, expected, sizeof(expected)) != 0) return 3;
    }
    for (i = 0; i < allocs; i++) {
        size_t size = (size_t)(i % 256u) + 1u;
        unsigned char *p = (unsigned char *)malloc(size);
        unsigned char *q;
        unsigned char first;
        unsigned char last;
        if (!p) return 4;
        p[0] = (unsigned char)i;
        p[size - 1u] = (unsigned char)(i + 1u);
        first = p[0];
        last = p[size - 1u];
        q = (unsigned char *)realloc(p, size + 129u);
        if (!q) {
            free(p);
            return 5;
        }
        if (q[0] != first || q[size - 1u] != last) {
            free(q);
            return 6;
        }
        q[size + 128u] = 0xa5u;
        free(q);
    }
    return 0;
}

static void *normal_worker(void *arg)
{
    Work *work = (Work *)arg;
    int rc = exercise(work->digests, work->allocs);
    if (work->explicit_exit) pthread_exit((void *)(long)rc);
    return (void *)(long)rc;
}

static int normal_batch(unsigned count, unsigned digests, unsigned allocs)
{
    pthread_t threads[16];
    Work work[16];
    unsigned created = 0;
    unsigned i;
    int failed = 0;
    for (i = 0; i < count; i++) {
        work[i].digests = digests;
        work[i].allocs = allocs;
        work[i].explicit_exit = (int)(i & 1u);
        if (pthread_create(&threads[i], NULL, normal_worker, &work[i]) != 0) {
            failed = 1;
            break;
        }
        created++;
        expected_destructors++;
    }
    for (i = 0; i < created; i++) {
        void *result = NULL;
        if (pthread_join(threads[i], &result) != 0 || result != NULL) {
            printf("normal worker=%u result=%ld\n", i, (long)result);
            failed = 1;
        }
    }
    return failed ? -1 : 0;
}

static void *cancel_worker(void *arg)
{
    CancelGroup *group = (CancelGroup *)arg;
    (void)pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    (void)pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    if (exercise(8u, 16u) != 0) return (void *)1;
    (void)__atomic_add_fetch(&group->ready, 1u, __ATOMIC_SEQ_CST);
    for (;;) usleep(10000u);
    return NULL;
}

static int cancel_batch(void)
{
    CancelGroup group;
    pthread_t threads[8];
    unsigned created = 0;
    unsigned i;
    unsigned spins = 0;
    int failed = 0;
    group.ready = 0;
    group.count = 8;
    for (i = 0; i < group.count; i++) {
        if (pthread_create(&threads[i], NULL, cancel_worker, &group) != 0) {
            failed = 1;
            break;
        }
        created++;
        expected_destructors++;
    }
    while (!failed && __atomic_load_n(&group.ready, __ATOMIC_SEQ_CST) < created &&
           spins++ < 1000000u) sched_yield();
    if (__atomic_load_n(&group.ready, __ATOMIC_SEQ_CST) != created) failed = 1;
    for (i = 0; i < created; i++) (void)pthread_cancel(threads[i]);
    for (i = 0; i < created; i++) {
        void *result = NULL;
        if (pthread_join(threads[i], &result) != 0 || result != PTHREAD_CANCELED) {
            printf("cancel worker=%u result=%p expected=%p\n",
                   i, result, PTHREAD_CANCELED);
            failed = 1;
        }
    }
    return failed ? -1 : 0;
}

static void *detached_worker(void *arg)
{
    DetachedWork *work = (DetachedWork *)arg;
    int rc = exercise(work->work.digests, work->work.allocs);
    if (rc != 0) (void)__atomic_add_fetch(&work->failed, 1u, __ATOMIC_SEQ_CST);
    (void)__atomic_add_fetch(&work->completed, 1u, __ATOMIC_SEQ_CST);
    if (work->work.explicit_exit) pthread_exit(NULL);
    return NULL;
}

static int detached_batch(unsigned count)
{
    pthread_attr_t attr;
    DetachedWork work[16];
    unsigned created = 0;
    unsigned i;
    unsigned spins = 0;
    if (pthread_attr_init(&attr) != 0) return -1;
    if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0) {
        pthread_attr_destroy(&attr);
        return -1;
    }
    for (i = 0; i < count; i++) {
        work[i].completed = 0;
        work[i].failed = 0;
        work[i].work.digests = DETACHED_DIGESTS;
        work[i].work.allocs = DETACHED_ALLOCS;
        work[i].work.explicit_exit = (int)(i & 1u);
        if (pthread_create(&(pthread_t){0}, &attr, detached_worker, &work[i]) != 0) {
            (void)__atomic_add_fetch(&work[i].failed, 1u, __ATOMIC_SEQ_CST);
            break;
        }
        created++;
        expected_destructors++;
    }
    pthread_attr_destroy(&attr);
    while (spins++ < 30000u) {
        unsigned done = 0;
        unsigned long key_exits;
        for (i = 0; i < created; i++) {
            if (__atomic_load_n(&work[i].completed, __ATOMIC_SEQ_CST)) done++;
        }
        key_exits = qnx_tls_general_load(&stats->key_exit_calls);
        if (done == created && key_exits >= expected_destructors &&
            qnx_tls_general_load(&stats->leave_count) >= expected_destructors &&
            __atomic_load_n(&destructor_count, __ATOMIC_SEQ_CST) >= expected_destructors)
            break;
        usleep(1000u);
    }
    if (created != count) return -1;
    for (i = 0; i < created; i++) {
        if (!__atomic_load_n(&work[i].completed, __ATOMIC_SEQ_CST) ||
            __atomic_load_n(&work[i].failed, __ATOMIC_SEQ_CST)) {
            printf("detached worker=%u completed=%u failed=%u\n", i,
                   __atomic_load_n(&work[i].completed, __ATOMIC_SEQ_CST),
                   __atomic_load_n(&work[i].failed, __ATOMIC_SEQ_CST));
            return -1;
        }
    }
    if (__atomic_load_n(&destructor_count, __ATOMIC_SEQ_CST) < expected_destructors ||
        qnx_tls_general_load(&stats->key_exit_calls) < expected_destructors ||
        qnx_tls_general_load(&stats->leave_count) < expected_destructors) {
        printf("detached timeout created=%u destructors=%lu expected=%lu\n",
               created, __atomic_load_n(&destructor_count, __ATOMIC_SEQ_CST),
               expected_destructors);
        return -1;
    }
    return 0;
}

static void print_stats(const char *phase)
{
    printf("%s set=%lu key_exit=%lu enter=%lu leave=%lu destructors=%lu failures=%lu\n",
           phase, qnx_tls_general_load(&stats->setspecific_calls),
           qnx_tls_general_load(&stats->key_exit_calls),
           qnx_tls_general_load(&stats->enter_count),
           qnx_tls_general_load(&stats->leave_count),
           __atomic_load_n(&destructor_count, __ATOMIC_SEQ_CST),
           qnx_tls_general_load(&stats->failures));
}

int main(void)
{
    unsigned char digest[32];
    unsigned int digest_len = 0;
    unsigned round;
    setvbuf(stdout, NULL, _IOLBF, 0);
    stats = (QnxTlsGeneralStats *)dlsym(RTLD_DEFAULT, "qnx_tls_general_stats");
    if (!stats) return 2;
    if (pthread_key_create(&stress_key, key_destructor) != 0) return 3;
    if (EVP_Digest("abc", 3, digest, &digest_len, EVP_sha256(), NULL) != 1)
        return 4;
    if (normal_batch(8, NORMAL_DIGESTS, NORMAL_ALLOCS) != 0) return 10;
    print_stats("normal-8");
    if (normal_batch(16, NORMAL_DIGESTS, NORMAL_ALLOCS) != 0) return 11;
    print_stats("normal-16");
    for (round = 0; round < REPEAT_ROUNDS; round++) {
        unsigned count = (round & 1u) ? 16u : 8u;
        if (normal_batch(count, REPEAT_DIGESTS, REPEAT_ALLOCS) != 0) return 12;
    }
    print_stats("repeat-32-rounds");
    for (round = 0; round < CANCEL_ROUNDS; round++) {
        if (cancel_batch() != 0) return 13;
    }
    print_stats("cancel-8x8");
    for (round = 0; round < DETACHED_ROUNDS; round++) {
        if (detached_batch(8) != 0 || detached_batch(16) != 0) return 14;
    }
    print_stats("detached-2x8-plus-16");
    if (pthread_key_delete(stress_key) != 0) return 15;
    if (qnx_tls_general_load(&stats->failures) != 0 ||
        __atomic_load_n(&destructor_count, __ATOMIC_SEQ_CST) != expected_destructors ||
        qnx_tls_general_load(&stats->key_exit_calls) < expected_destructors ||
        qnx_tls_general_load(&stats->enter_count) < expected_destructors ||
        qnx_tls_general_load(&stats->enter_count) !=
            qnx_tls_general_load(&stats->leave_count) + 1ul) {
        printf("final mismatch destructors=%lu expected=%lu enter=%lu leave=%lu key_exit=%lu failures=%lu\n",
               __atomic_load_n(&destructor_count, __ATOMIC_SEQ_CST),
               expected_destructors, qnx_tls_general_load(&stats->enter_count),
               qnx_tls_general_load(&stats->leave_count),
               qnx_tls_general_load(&stats->key_exit_calls),
               qnx_tls_general_load(&stats->failures));
        return 20;
    }
    printf("PASS threads=%lu digests=%u alloc_pairs=%u destructors=%lu\n",
           expected_destructors,
           24u * NORMAL_DIGESTS + 384u * REPEAT_DIGESTS + 64u * 8u +
               48u * DETACHED_DIGESTS,
           24u * NORMAL_ALLOCS + 384u * REPEAT_ALLOCS + 64u * 16u +
               48u * DETACHED_ALLOCS,
           __atomic_load_n(&destructor_count, __ATOMIC_SEQ_CST));
    return 0;
}
