#pragma once
#include <core/types.h>

typedef void (*TaskFn)(void *ctx);

typedef struct Task Task;

struct Task {
    TaskFn  fn;
    void   *ctx;
    Task   *next;
};

typedef struct {
    Task  *head;
    Task  *tail;
} TaskQueue;

typedef struct {
    TaskQueue  queues[64];
    i32        worker_count;
    bool       running;
    void     **threads;
    TaskQueue *local_queues;
    i32       *worker_ids;
    u64        completed_tasks;
} TaskSystem;

TaskSystem *task_system_create(i32 worker_count);
void        task_system_destroy(TaskSystem *ts);
void        task_submit(TaskSystem *ts, TaskFn fn, void *ctx);
void        task_submit_n(TaskSystem *ts, TaskFn fn, void **ctxs, i32 count);
void        task_wait(TaskSystem *ts);
i32         task_worker_id(TaskSystem *ts);
