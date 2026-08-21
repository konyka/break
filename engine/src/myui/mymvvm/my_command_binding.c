/**
 * @file my_command_binding.c
 * @brief Command binding: target event -> vm can_exec/exec.
 */
#include "mymvvm/my_command_binding.h"

#include <stdio.h>
#include <string.h>

#include "mymvvm/my_binding_context.h"
#include "mymvvm/my_navigator.h"

/** @brief Substitute "{prop}" tokens in args with vm property values. */
static void substitute_args(my_view_model_t* vm, const char* in, char* out,
                            size_t out_size) {
  size_t oi = 0;
  const char* p = in;
  if (out_size == 0) {
    return;
  }
  while (*p != '\0' && oi + 1 < out_size) {
    if (*p == '{' && vm != NULL) {
      const char* end = strchr(p, '}');
      if (end != NULL && end > p + 1) {
        char name[MY_RULE_NAME_LEN];
        size_t len = (size_t)(end - p - 1);
        my_value_t v;
        if (len < sizeof(name)) {
          memcpy(name, p + 1, len);
          name[len] = '\0';
          my_value_init(&v, NULL);
          if (my_view_model_get_prop(vm, name, &v) == MY_RET_OK) {
            char text[32];
            const char* s = NULL;
            if (v.type == MY_VALUE_STR) {
              s = my_value_get_str(&v);
            } else if (v.type == MY_VALUE_INT32) {
              snprintf(text, sizeof(text), "%d", (int)my_value_get_int32(&v));
              s = text;
            } else if (v.type == MY_VALUE_BOOL) {
              s = my_value_get_bool(&v) ? "true" : "false";
            }
            if (s != NULL) {
              while (*s != '\0' && oi + 1 < out_size) {
                out[oi++] = *s++;
              }
            }
          }
          my_value_reset(&v);
          p = end + 1;
          continue;
        }
      }
    }
    out[oi++] = *p++;
  }
  out[oi] = '\0';
}

static void on_target_event(void* ctx, const char* event, void* data) {
  my_command_binding_t* binding = (my_command_binding_t*)ctx;
  my_view_model_t* vm = my_binding_context_get_view_model(binding->ctx);
  char args[MY_RULE_ARGS_LEN];
  const char* argp;
  (void)event;
  (void)data;

  substitute_args(vm, binding->rule.args, args, sizeof(args));
  argp = args[0] != '\0' ? args : NULL;

  /* navigator requests take precedence (ToPage=detail) */
  if (binding->rule.to_page[0] != '\0') {
    my_navigator_request_t req;
    memset(&req, 0, sizeof(req));
    req.type = MY_NAV_TO;
    snprintf(req.target, sizeof(req.target), "%s", binding->rule.to_page);
    if (argp != NULL) {
      snprintf(req.args, sizeof(req.args), "%s", argp);
    }
    my_navigator_request(&req);
    return;
  }

  if (vm != NULL && my_view_model_can_exec(vm, binding->rule.vm_prop, argp)) {
    my_view_model_exec(vm, binding->rule.vm_prop, argp);
  }
}

my_command_binding_t* my_command_binding_create(const my_allocator_t* allocator,
                                                my_binding_context_t* ctx,
                                                my_binding_target_t* target,
                                                const my_binding_rule_t* rule) {
  my_command_binding_t* b;
  char event[MY_RULE_PROP_LEN];
  if (ctx == NULL || target == NULL || rule == NULL) {
    return NULL;
  }
  b = (my_command_binding_t*)my_mem_calloc(allocator, 1,
                                           sizeof(my_command_binding_t));
  if (b == NULL) {
    return NULL;
  }
  b->ctx = ctx;
  b->allocator = allocator;
  b->target = target;
  b->rule = *rule;
  /* "on_click" -> event "click" */
  snprintf(event, sizeof(event), "%s", rule->widget_prop + 3);
  b->target_listener_id =
      my_binding_target_on_event(target, event, on_target_event, b);
  if (b->target_listener_id == 0) {
    my_mem_free(allocator, b);
    return NULL;
  }
  return b;
}

void my_command_binding_destroy(my_command_binding_t* binding) {
  if (binding == NULL) {
    return;
  }
  if (binding->target_listener_id > 0) {
    my_binding_target_off_event(binding->target, binding->target_listener_id);
  }
  my_mem_free(binding->allocator, binding);
}
