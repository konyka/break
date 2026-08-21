/**
 * @file my_navigator.h
 * @brief Navigator: GUI-free page navigation requests.
 *
 * Ports/adapters register one default navigator (my_navigator_set_default);
 * command bindings with ToPage=... build a request and call
 * my_navigator_request().
 */
#ifndef MY_NAVIGATOR_H
#define MY_NAVIGATOR_H

#include "myc/my_error.h"
#include "myc/my_types.h"

#define MY_NAV_TARGET_LEN 32
#define MY_NAV_ARGS_LEN 64

/** @brief Navigation request kind. */
typedef enum my_nav_request_type_t {
  MY_NAV_TO = 0,   /**< open target page on top */
  MY_NAV_BACK,     /**< close the top page */
  MY_NAV_REPLACE,  /**< replace the top page */
  MY_NAV_HOME      /**< back to the first page */
} my_nav_request_type_t;

/** @brief Navigation request. */
typedef struct my_navigator_request_t {
  my_nav_request_type_t type;
  char target[MY_NAV_TARGET_LEN]; /**< page name for TO/REPLACE */
  char args[MY_NAV_ARGS_LEN];     /**< free-form args ("K=V" pairs) */
} my_navigator_request_t;

/** @brief Navigator handle (implemented by the UI adapter). */
typedef struct my_navigator_t {
  my_ret_t (*handle_request)(struct my_navigator_t* nav,
                             const my_navigator_request_t* request);
} my_navigator_t;

/** @brief Install the process-wide default navigator (weak ref). */
void my_navigator_set_default(my_navigator_t* nav);

/** @brief Dispatch a request to the default navigator. */
my_ret_t my_navigator_request(const my_navigator_request_t* request);

#endif /* MY_NAVIGATOR_H */
