#ifndef MY_COMPOSE_MYUI_H
#define MY_COMPOSE_MYUI_H

#include <myui/mycompose/my_compose_runtime.h>
#include <myui/my_widget.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MyComposeMyui MyComposeMyui;
typedef struct my_window_t my_window_t;

MyComposeMyui *my_compose_myui_create(my_window_t *window,
    MyComposeTreeBuilder *builder, MyComposeStore *store);
void my_compose_myui_destroy(MyComposeMyui *adapter);

MyComposeStatus my_compose_myui_stage(MyComposeMyui *adapter,
    const MyComposeDiff *diff);
void my_compose_myui_commit(MyComposeMyui *adapter);
void my_compose_myui_rollback(MyComposeMyui *adapter);
MyComposeSinkOps my_compose_myui_sink(MyComposeMyui *adapter);
MyComposeStatus my_compose_myui_pump(MyComposeMyui *adapter,
    MyComposeRuntime *runtime);
my_widget_t *my_compose_myui_widget(const MyComposeMyui *adapter,
    MyComposeNodeHandle node);

#ifdef __cplusplus
}
#endif

#endif
