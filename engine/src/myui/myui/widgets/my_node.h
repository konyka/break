/**
 * @file my_node.h
 * @brief Node widget for the node editor (M19b): category-colored title
 * bar + socket rows (left inputs, right outputs) + rounded body;
 * draggable by its title bar (dispatcher grab). Socket hit zones are
 * the view's business (bubbling).
 *
 * Theming (CSS, M18/M19): `node { background-color }` (body),
 * `node.<category> .header { background-color }` (title bar),
 * `node_socket.input/.output { background-color }` (socket dots; falls
 * back to the socket's model type color).
 */
#ifndef MY_NODE_H
#define MY_NODE_H

#include "myui/my_widget.h"

#define MY_NODE_HEADER_H 24
#define MY_NODE_ROW_H 20
#define MY_NODE_SOCKET_R 5    /**< dot radius */
#define MY_NODE_SOCKET_HIT 10 /**< hit zone radius (easy to click) */

typedef enum my_socket_dir_t {
  MY_SOCKET_IN = 0,
  MY_SOCKET_OUT
} my_socket_dir_t;

/** @brief Create a node (id/title/category copied; category doubles as
 * the node's style_class for CSS). The view weak-ref is used to
 * invalidate links while dragging. */
my_widget_t* my_node_create(const my_allocator_t* allocator,
                            my_widget_t* view, const char* id,
                            const char* title, const char* category);

/** @brief Add a socket (name copied; type_color = rgba32 fallback).
 * Triggers an auto-size recompute on auto-sized nodes (M21b). */
my_ret_t my_node_add_socket(my_widget_t* node, my_socket_dir_t dir,
                            const char* name, uint32_t type_color);

/** @brief Number of sockets of one direction. */
size_t my_node_socket_count(const my_widget_t* node, my_socket_dir_t dir);

/** @brief Socket dot center in canvas (= view-local) coordinates. */
bool my_node_socket_center(const my_widget_t* node, my_socket_dir_t dir,
                           size_t slot, int32_t* out_x, int32_t* out_y);

/** @brief The model type color of a socket (M21b: links tint themselves
 * from their source output socket). 0 when node/slot is invalid. */
uint32_t my_node_socket_type_color(const my_widget_t* node,
                                   my_socket_dir_t dir, size_t slot);

/**
 * @brief Mark which dimensions auto-size to the content (M21b). Set by
 * my_node_view_add_node when the caller passes w/h == 0; explicit
 * dimensions always win. Auto width = max(80, title text + 2*margin,
 * widest socket row, widest embedded child + margin); auto height =
 * header + max(input,output rows)*row height (or the lowest embedded
 * child bottom, whichever is lower) + margin.
 */
void my_node_set_auto_size(my_widget_t* node, bool auto_w, bool auto_h);

/** @brief Recompute and apply the auto-sized dimensions (M21b; no-op on
 * explicitly sized nodes). Runs on add_socket and at paint time (late
 * embedded children); invalidates the node when the size changed. */
void my_node_auto_size(my_widget_t* node);

/** @brief The node's id (static after create). */
const char* my_node_get_id(const my_widget_t* node);

/** @brief Append a circle path via 4 cubic arcs (kappa = 0.5523;
 * vgcanvas has no arc primitive — M19a curve_to). Caller does
 * begin_path/fill or stroke. */
void my_node_path_circle(my_vgcanvas_t* vg, float cx, float cy, float r);

#endif /* MY_NODE_H */
