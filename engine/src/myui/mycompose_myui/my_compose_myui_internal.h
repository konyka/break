#ifndef MY_COMPOSE_MYUI_INTERNAL_H
#define MY_COMPOSE_MYUI_INTERNAL_H

#include <myui/mycompose_myui/my_compose_myui.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MyComposeMyuiFault {
    uint32_t factory_call;
    uint32_t insert_call;
    uint32_t detach_call;
    my_widget_t *property_widget;
    const char *property_name;
    bool fail_after_property_error;
    bool fail_after_detach_error;
} MyComposeMyuiFault;

typedef struct MyComposeMyuiStats {
    uint32_t factory_calls;
    uint32_t property_set_calls;
    uint32_t property_captures;
    uint32_t property_restore_set_calls;
    uint32_t insert_calls;
    uint32_t detach_calls;
    uint32_t notifies;
    uint32_t rollbacks;
    uint32_t commits;
} MyComposeMyuiStats;

struct MyComposeMyui {
    MyComposeMyuiFault fault;
    MyComposeMyuiStats stats;
    void *state;
};

MyComposeStatus my_compose_myui_internal_seed_generation(
    MyComposeMyui *adapter, MyComposeNodeHandle handle, uint32_t generation);

#ifdef __cplusplus
}
#endif

#endif
