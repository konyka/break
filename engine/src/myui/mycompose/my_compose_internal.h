#ifndef MY_COMPOSE_INTERNAL_H
#define MY_COMPOSE_INTERNAL_H

#include <myui/mycompose/my_compose_tree.h>

#ifdef __cplusplus
extern "C" {
#endif

MyComposeStatus my_compose_tree_builder_internal_seed_generation(
    MyComposeTreeBuilder *builder, MyComposeNodeHandle handle,
    uint32_t generation);

#ifdef __cplusplus
}
#endif

#endif
