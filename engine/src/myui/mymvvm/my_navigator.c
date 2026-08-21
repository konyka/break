/**
 * @file my_navigator.c
 * @brief Navigator default-handle registry.
 */
#include "mymvvm/my_navigator.h"

static my_navigator_t* g_default_navigator = NULL;

void my_navigator_set_default(my_navigator_t* nav) {
  g_default_navigator = nav;
}

my_ret_t my_navigator_request(const my_navigator_request_t* request) {
  if (request == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (g_default_navigator == NULL || g_default_navigator->handle_request == NULL) {
    return MY_RET_NOT_FOUND;
  }
  return g_default_navigator->handle_request(g_default_navigator, request);
}
