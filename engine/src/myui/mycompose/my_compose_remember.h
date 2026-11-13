#ifndef MY_COMPOSE_REMEMBER_H
#define MY_COMPOSE_REMEMBER_H

#include <myui/mycompose/my_compose.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MY_COMPOSE_MAX_REMEMBER_SLOTS 64u
#define MY_COMPOSE_REMEMBER_BYTES 256u
#define MY_COMPOSE_REMEMBER_SLOTS_PER_NODE 4u

/* MSVC's C mode has no max_align_t; this union has the same alignment on
 * every supported ABI and is the largest alignment remember and state storage provide. */
typedef union MyComposeMaxAlign {
    long double long_double_value;
    long long long_long_value;
    double double_value;
    void *pointer_value;
    void (*function_value)(void);
} MyComposeMaxAlign;

#ifdef __cplusplus
#define MY_COMPOSE_MAX_ALIGNMENT ((uint32_t)alignof(MyComposeMaxAlign))
#else
#define MY_COMPOSE_MAX_ALIGNMENT ((uint32_t)_Alignof(MyComposeMaxAlign))
#endif

typedef struct MyComposeRememberOps {
    void *context;
    void (*dispose)(void *context, void *storage, uint32_t size);
} MyComposeRememberOps;

MyComposeStatus my_compose_tree_builder_remember(
    MyComposeTreeBuilder *builder, MyComposeNodeHandle owner,
    uint32_t local_slot, uint64_t type_tag, uint32_t size, uint32_t alignment,
    const MyComposeRememberOps *ops, void **out_storage);
MyComposeStatus my_compose_tree_builder_remember_get(
    const MyComposeTreeBuilder *builder, MyComposeNodeHandle owner,
    uint32_t local_slot, void **out_storage);

#ifdef __cplusplus
}
#endif

#endif
