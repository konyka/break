#include <task/task.h>
#include <core/log.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <stdatomic.h>

static mtx_t  g_queue_mutex;
static cnd_t  g_queue_cnd;
static TaskSystem *g_task_system;

static void queue_push(TaskQueue *q, Task *t) {
    t->next = NULL;
    if (!q->tail) {
        q->head = t;
        q->tail = t;
    } else {
        q->tail->next = t;
        q->tail = t;
    }
}

static Task *queue_pop(TaskQueue *q) {
    if (!q->head) return NULL;
    Task *t = q->head;
    q->head = t->next;
    if (!q->head) q->tail = NULL;
    t->next = NULL;
    return t;
}

static Task *queue_steal(TaskQueue *q) {
    if (!q->head) return NULL;
    Task *t = q->head;
    if (q->head == q->tail) {
        q->head = NULL;
        q->tail = NULL;
    } else {
        q->head = t->next;
    }
    t->next = NULL;
    return t;
}

static i32 task_worker_thread(void *arg) {
    i32 worker_id = *(i32 *)arg;
    TaskSystem *ts = g_task_system;
    TaskQueue *local = &ts->local_queues[worker_id];

    while (ts->running) {
        Task *t = NULL;

        t = queue_pop(local);

        if (!t) {
            mtx_lock(&g_queue_mutex);
            t = queue_pop(&ts->queues[0]);
            if (!t) {
                for (i32 i = 1; i <= worker_id && !t; i++) {
                    t = queue_steal(&ts->local_queues[worker_id - i]);
                }
                for (i32 i = 1; i < ts->worker_count && !t; i++) {
                    i32 idx = (worker_id + i) % ts->worker_count;
                    t = queue_steal(&ts->local_queues[idx]);
                }
            }
            if (!t) {
                cnd_wait(&g_queue_cnd, &g_queue_mutex);
                mtx_unlock(&g_queue_mutex);
                continue;
            }
            mtx_unlock(&g_queue_mutex);
        }

        if (t) {
            t->fn(t->ctx);
            free(t);
            atomic_fetch_add(&ts->completed_tasks, 1);
        }
    }
    return 0;
}

TaskSystem *task_system_create(i32 worker_count) {
    if (worker_count <= 0) worker_count = 1;

    TaskSystem *ts = calloc(1, sizeof(TaskSystem));
    ts->worker_count = worker_count;
    ts->running = true;
    ts->local_queues = calloc(worker_count, sizeof(TaskQueue));
    ts->worker_ids = calloc(worker_count, sizeof(i32));
    ts->threads = calloc(worker_count, sizeof(void *));
    atomic_store(&ts->completed_tasks, 0);

    mtx_init(&g_queue_mutex, mtx_plain);
    cnd_init(&g_queue_cnd);
    g_task_system = ts;

    for (i32 i = 0; i < worker_count; i++) {
        ts->worker_ids[i] = i;
        thrd_t *thr = (thrd_t *)&ts->threads[i];
        thrd_create(thr, task_worker_thread, &ts->worker_ids[i]);
    }

    LOG_INFO("Task system: %d workers", worker_count);
    return ts;
}

void task_system_destroy(TaskSystem *ts) {
    ts->running = false;
    cnd_broadcast(&g_queue_cnd);
    for (i32 i = 0; i < ts->worker_count; i++) {
        thrd_t *thr = (thrd_t *)&ts->threads[i];
        thrd_join(*thr, NULL);
    }
    mtx_destroy(&g_queue_mutex);
    cnd_destroy(&g_queue_cnd);
    free(ts->local_queues);
    free(ts->worker_ids);
    free(ts->threads);
    free(ts);
}

void task_submit(TaskSystem *ts, TaskFn fn, void *ctx) {
    Task *t = calloc(1, sizeof(Task));
    t->fn = fn;
    t->ctx = ctx;

    mtx_lock(&g_queue_mutex);
    queue_push(&ts->queues[0], t);
    cnd_signal(&g_queue_cnd);
    mtx_unlock(&g_queue_mutex);
}

void task_submit_n(TaskSystem *ts, TaskFn fn, void **ctxs, i32 count) {
    mtx_lock(&g_queue_mutex);
    for (i32 i = 0; i < count; i++) {
        Task *t = calloc(1, sizeof(Task));
        t->fn = fn;
        t->ctx = ctxs[i];
        queue_push(&ts->queues[0], t);
    }
    cnd_broadcast(&g_queue_cnd);
    mtx_unlock(&g_queue_mutex);
}

void task_wait(TaskSystem *ts) {
    bool has_work = true;
    while (has_work) {
        mtx_lock(&g_queue_mutex);
        bool global_empty = (ts->queues[0].head == NULL);
        bool local_empty = true;
        for (i32 i = 0; i < ts->worker_count; i++) {
            if (ts->local_queues[i].head) { local_empty = false; break; }
        }
        has_work = !global_empty || !local_empty;
        mtx_unlock(&g_queue_mutex);
        if (has_work) {
            struct timespec ts_wait = {0, 100000};
            thrd_sleep(&ts_wait, NULL);
        }
    }
}

i32 task_worker_id(TaskSystem *ts) {
    (void)ts;
    return 0;
}
