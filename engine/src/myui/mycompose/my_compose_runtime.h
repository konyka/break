#ifndef MY_COMPOSE_RUNTIME_H
#define MY_COMPOSE_RUNTIME_H

#include <myui/mycompose/my_compose_store.h>
#include <myui/mycompose/my_compose_tree.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MyComposeRuntime MyComposeRuntime;

typedef MyComposeStatus (*MyComposeView)(void *,
    MyComposeTreeBuilder *, const void *, uint32_t);

typedef struct MyComposeSinkOps {
    void *context;
    MyComposeStore *store;
    MyComposeStatus (*stage)(void *, const MyComposeDiff *);
    void (*commit)(void *);
    void (*rollback)(void *);
} MyComposeSinkOps;

typedef struct MyComposeRuntimeConfig {
    MyComposeStore *store;
    MyComposeView view;
    void *view_context;
    MyComposeSinkOps sink;
} MyComposeRuntimeConfig;

MyComposeRuntime *my_compose_runtime_create(MyComposeTreeBuilder *builder,
    const MyComposeRuntimeConfig *config);
void my_compose_runtime_destroy(MyComposeRuntime *runtime);
MyComposeStatus my_compose_runtime_pump(MyComposeRuntime *runtime);
MyComposeStatus my_compose_runtime_restart(MyComposeRuntime *runtime);

#ifdef __cplusplus
}
#endif

#endif
