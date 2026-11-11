#ifndef MY_COMPOSE_TREE_H
#define MY_COMPOSE_TREE_H

#include <myui/mycompose/my_compose.h>

#ifdef __cplusplus
extern "C" {
#endif

MyComposeTreeBuilder *my_compose_tree_builder_create(void);
void my_compose_tree_builder_destroy(MyComposeTreeBuilder *builder);

MyComposeStatus my_compose_tree_builder_begin(MyComposeTreeBuilder *builder);
MyComposeStatus my_compose_tree_builder_node(MyComposeTreeBuilder *builder,
    const MyComposeNodeDesc *desc, MyComposeNodeHandle *out);
MyComposeStatus my_compose_tree_builder_property(MyComposeTreeBuilder *builder,
    MyComposeNodeHandle owner, const char *name, const MyComposeValue *value);
MyComposeStatus my_compose_tree_builder_event(MyComposeTreeBuilder *builder,
    MyComposeNodeHandle owner, const char *name, const MyComposeIntent *intent);
MyComposeStatus my_compose_tree_builder_end(MyComposeTreeBuilder *builder);
MyComposeStatus my_compose_tree_builder_finalize(MyComposeTreeBuilder *builder);

const MyComposeDiff *my_compose_tree_builder_diff(
    const MyComposeTreeBuilder *builder);
uint32_t my_compose_tree_builder_current_node_count(
    const MyComposeTreeBuilder *builder);
uint32_t my_compose_tree_builder_next_node_count(
    const MyComposeTreeBuilder *builder);
MyComposeStatus my_compose_tree_builder_get_node(
    const MyComposeTreeBuilder *builder, MyComposeNodeHandle handle,
    MyComposeNodeDesc *out);
MyComposeStatus my_compose_tree_builder_get_property(
    const MyComposeTreeBuilder *builder, MyComposeNodeHandle owner,
    const char *name, MyComposeValue *out);
MyComposeStatus my_compose_tree_builder_get_event(
    const MyComposeTreeBuilder *builder, MyComposeNodeHandle owner,
    const char *name, MyComposeIntent *out);

#ifdef __cplusplus
}
#endif

#endif
