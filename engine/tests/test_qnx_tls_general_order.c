#include "qnx_tls_general_interpose.h"

#include <dlfcn.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

extern int __cxa_thread_atexit(void (*)(void *), void *, void *);
extern void *__dso_handle;

typedef struct {
    QnxTlsGeneralStats *stats;
    pthread_key_t key;
    int cxa_calls;
    int destructor_calls;
    int explicit_exit;
} ThreadInfo;

typedef struct {
    ThreadInfo *info;
} KeyValue;

static void cxa_callback(void *arg)
{
    ThreadInfo *info = (ThreadInfo *)arg;
    info->cxa_calls++;
    qnx_tls_general_store(&info->stats->last_event, 1);
}

static void key_destructor(void *arg)
{
    KeyValue *value = (KeyValue *)arg;
    value->info->destructor_calls++;
    qnx_tls_general_store(&value->info->stats->last_event, 2);
    free(value);
}

static void *worker(void *arg)
{
    ThreadInfo *info = (ThreadInfo *)arg;
    KeyValue *value = (KeyValue *)malloc(sizeof(*value));
    int key_created = 0;
    int installed = 0;
    if (!value) return NULL;
    value->info = info;
    if (pthread_key_create(&info->key, key_destructor) != 0) goto fail;
    key_created = 1;
    if (pthread_setspecific(info->key, value) != 0) goto fail;
    installed = 1;
    if (__cxa_thread_atexit(cxa_callback, info, __dso_handle) != 0) goto fail;
    if (info->explicit_exit) pthread_exit(info);
    return info;
fail:
    if (installed) (void)pthread_setspecific(info->key, NULL);
    if (key_created) (void)pthread_key_delete(info->key);
    free(value);
    return NULL;
}

static int run_one(QnxTlsGeneralStats *stats, int explicit_exit)
{
    pthread_t thread;
    ThreadInfo *info = (ThreadInfo *)calloc(1, sizeof(*info));
    void *result = NULL;
    int rc = 0;
    if (!info) return 10;
    info->stats = stats;
    info->explicit_exit = explicit_exit;
    qnx_tls_general_store(&stats->last_event, 0);
    if (pthread_create(&thread, NULL, worker, info) != 0 ||
        pthread_join(thread, &result) != 0 || result != info) {
        free(info);
        return 11;
    }
    printf("order explicit=%d cxa=%d destructor=%d last=%lu key_exit=%lu enter=%lu leave=%lu failures=%lu\n",
           explicit_exit, info->cxa_calls, info->destructor_calls,
           qnx_tls_general_load(&stats->last_event),
           qnx_tls_general_load(&stats->key_exit_calls),
           qnx_tls_general_load(&stats->enter_count),
           qnx_tls_general_load(&stats->leave_count),
           qnx_tls_general_load(&stats->failures));
    if (info->cxa_calls != 1 || info->destructor_calls != 1 ||
        qnx_tls_general_load(&stats->last_event) != 3 ||
        qnx_tls_general_load(&stats->failures) != 0) rc = 12;
    if (pthread_key_delete(info->key) != 0) rc = 13;
    free(info);
    return rc;
}

int main(void)
{
    QnxTlsGeneralStats *stats = (QnxTlsGeneralStats *)dlsym(
        RTLD_DEFAULT, "qnx_tls_general_stats");
    pthread_key_t key;
    int value = 11;
    int rc;
    setvbuf(stdout, NULL, _IOLBF, 0);
    if (!stats) return 2;
    if (qnx_tls_general_load(&stats->enter_count) == 0) return 3;
    if (pthread_key_create(&key, NULL) != 0 ||
        pthread_setspecific(key, &value) != 0 ||
        pthread_getspecific(key) != &value ||
        pthread_key_delete(key) != 0) return 4;
    if (qnx_tls_general_load(&stats->setspecific_calls) == 0) return 5;
    rc = run_one(stats, 0);
    if (rc != 0) return rc;
    rc = run_one(stats, 1);
    if (rc != 0) return rc;
    if (qnx_tls_general_load(&stats->key_exit_calls) < 2 ||
        qnx_tls_general_load(&stats->leave_count) < 2) return 20;
    puts("PASS qnx tls general order");
    return 0;
}
