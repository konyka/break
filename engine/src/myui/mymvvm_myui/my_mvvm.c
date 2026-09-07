/**
 * @file my_mvvm.c
 * @brief MVVM convenience layer for myui.
 */
#include "mymvvm_myui/my_mvvm.h"

#include <stdatomic.h>
#include <string.h>

#include "myc/my_str.h"
#include "myc/my_ref_count.h"
#include "myui/my_ui_command.h"
#include "mymvvm_myui/my_widget_target.h"

/* ---------------- template registry ---------------- */

#define MY_MVVM_MAX_TEMPLATES 16
#define MY_MVVM_ASYNC_MAX_PENDING 64u
#define MY_MVVM_ASYNC_MAX_STRING 4096u

typedef struct mvvm_async_state_t {
  const my_allocator_t* allocator;
  atomic_uint ref_count;
  atomic_uint pending;
  atomic_bool closed;
} mvvm_async_state_t;

static mvvm_async_state_t* mvvm_async_state_create(
    const my_allocator_t* allocator) {
  mvvm_async_state_t* state = (mvvm_async_state_t*)my_mem_calloc(
      allocator, 1u, sizeof(*state));
  if (state == NULL) {
    return NULL;
  }
  state->allocator = allocator;
  atomic_init(&state->ref_count, 1u);
  atomic_init(&state->pending, 0u);
  atomic_init(&state->closed, false);
  return state;
}

static mvvm_async_state_t* mvvm_async_state_ref(mvvm_async_state_t* state) {
  if (state != NULL) {
    (void)my_ref_count_try_ref(&state->ref_count);
  }
  return state;
}

static void mvvm_async_state_unref(mvvm_async_state_t* state) {
  if (state != NULL && my_ref_count_release(&state->ref_count)) {
    my_mem_free(state->allocator, state);
  }
}

static void mvvm_async_state_close(mvvm_async_state_t* state) {
  if (state != NULL) {
    atomic_store_explicit(&state->closed, true, memory_order_release);
  }
}

static bool mvvm_async_state_reserve(mvvm_async_state_t* state) {
  unsigned int pending;
  if (state == NULL ||
      atomic_load_explicit(&state->closed, memory_order_acquire)) {
    return false;
  }
  pending = atomic_load_explicit(&state->pending, memory_order_relaxed);
  for (;;) {
    if (pending >= MY_MVVM_ASYNC_MAX_PENDING ||
        atomic_load_explicit(&state->closed, memory_order_acquire)) {
      return false;
    }
    if (atomic_compare_exchange_weak_explicit(
            &state->pending, &pending, pending + 1u,
            memory_order_acq_rel, memory_order_relaxed)) {
      return true;
    }
  }
}

static void mvvm_async_state_release_pending(mvvm_async_state_t* state) {
  if (state != NULL) {
    atomic_fetch_sub_explicit(&state->pending, 1u, memory_order_acq_rel);
  }
}

typedef struct close_listener_t {
  my_widget_t* widget; /**< retained by the corresponding target */
  uint32_t id;
} close_listener_t;

typedef struct mvvm_notify_command_t {
  my_view_model_t* vm;
  const my_allocator_t* allocator;
  mvvm_async_state_t* state;
  bool bulk;
  char name[MY_RULE_NAME_LEN];
} mvvm_notify_command_t;

typedef struct mvvm_set_property_command_t {
  my_view_model_t* vm;
  const my_allocator_t* allocator;
  mvvm_async_state_t* state;
  char name[MY_RULE_NAME_LEN];
  my_value_t value;
} mvvm_set_property_command_t;

static void mvvm_context_finalize(void* data);

static my_ret_t mvvm_context_finalize_execute(void* data) {
  (void)data;
  return MY_RET_OK;
}

static my_ret_t mvvm_notify_execute(void* data) {
  mvvm_notify_command_t* request = (mvvm_notify_command_t*)data;
  if (request == NULL || request->vm == NULL) {
    return MY_RET_NOT_FOUND;
  }
  return my_view_model_notify_change(request->vm,
                                     request->bulk ? NULL : request->name);
}

static void mvvm_notify_destroy(void* data) {
  mvvm_notify_command_t* request = (mvvm_notify_command_t*)data;
  if (request != NULL) {
    my_view_model_unref(request->vm);
    mvvm_async_state_release_pending(request->state);
    mvvm_async_state_unref(request->state);
    my_mem_free(request->allocator, request);
  }
}

static my_ret_t mvvm_set_property_execute(void* data) {
  mvvm_set_property_command_t* request =
      (mvvm_set_property_command_t*)data;
  if (request == NULL || request->vm == NULL) {
    return MY_RET_NOT_FOUND;
  }
  return my_view_model_set_prop(request->vm, request->name, &request->value);
}

static void mvvm_set_property_destroy(void* data) {
  mvvm_set_property_command_t* request =
      (mvvm_set_property_command_t*)data;
  if (request != NULL) {
    my_value_reset(&request->value);
    my_view_model_unref(request->vm);
    mvvm_async_state_release_pending(request->state);
    mvvm_async_state_unref(request->state);
    my_mem_free(request->allocator, request);
  }
}

static void mvvm_manager_destroyed(void* ctx) {
  my_mvvm_context_t* mc = (my_mvvm_context_t*)ctx;
  if (mc == NULL) {
    return;
  }
  my_ui_command_scope_close(mc->command_scope);
  mvvm_async_state_close((mvvm_async_state_t*)mc->async_state);
  mc->wm = NULL;
  mc->wm_destroy_listener_id = 0u;
  my_widget_unref((my_widget_t*)mc->win);
  mc->win = NULL;
  my_mvvm_context_unref(mc);
}

static my_item_template_t g_templates[MY_MVVM_MAX_TEMPLATES];
static my_item_context_destroy_fn_t
    g_template_destroy[MY_MVVM_MAX_TEMPLATES];
static size_t g_template_count = 0;

my_ret_t my_mvvm_register_template(const char* name, my_item_builder_fn_t fn,
                                   void* ctx) {
  return my_mvvm_register_template_owned(name, fn, ctx, NULL);
}

my_ret_t my_mvvm_register_template_owned(
    const char* name, my_item_builder_fn_t fn, void* ctx,
    my_item_context_destroy_fn_t destroy_ctx) {
  size_t i;
  if (name == NULL || fn == NULL || strlen(name) >= 32) {
    return MY_RET_INVALID_PARAMS;
  }
  for (i = 0; i < g_template_count; i++) {
    if (my_str_eq(g_templates[i].name, name)) {
      my_item_context_destroy_fn_t old_destroy = g_template_destroy[i];
      void* old_ctx = g_templates[i].ctx;
      g_templates[i].build = fn;
      g_templates[i].ctx = ctx;
      g_template_destroy[i] = destroy_ctx;
      if (old_destroy != NULL) {
        old_destroy(old_ctx);
      }
      return MY_RET_OK;
    }
  }
  if (g_template_count >= MY_MVVM_MAX_TEMPLATES) {
    return MY_RET_OOM;
  }
  strncpy(g_templates[g_template_count].name, name, 31);
  g_templates[g_template_count].build = fn;
  g_templates[g_template_count].ctx = ctx;
  g_template_destroy[g_template_count] = destroy_ctx;
  g_template_count++;
  return MY_RET_OK;
}

my_ret_t my_mvvm_unregister_template(const char* name) {
  size_t i;
  if (name == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  for (i = 0; i < g_template_count; i++) {
    if (my_str_eq(g_templates[i].name, name)) {
      my_item_context_destroy_fn_t destroy_ctx = g_template_destroy[i];
      void* ctx = g_templates[i].ctx;
      if (destroy_ctx != NULL) {
        destroy_ctx(ctx);
      }
      if (i + 1u < g_template_count) {
        memmove(&g_templates[i], &g_templates[i + 1u],
                (g_template_count - i - 1u) * sizeof(g_templates[0]));
        memmove(&g_template_destroy[i], &g_template_destroy[i + 1u],
                (g_template_count - i - 1u) * sizeof(g_template_destroy[0]));
      }
      memset(&g_templates[g_template_count - 1u], 0,
             sizeof(g_templates[0]));
      g_template_destroy[g_template_count - 1u] = NULL;
      g_template_count--;
      return MY_RET_OK;
    }
  }
  return MY_RET_NOT_FOUND;
}

const my_item_template_t* my_mvvm_find_template(const char* name) {
  size_t i;
  if (name == NULL) {
    return NULL;
  }
  for (i = 0; i < g_template_count; i++) {
    if (my_str_eq(g_templates[i].name, name)) {
      return &g_templates[i];
    }
  }
  return NULL;
}

/* ---------------- my_mvvm_bind ---------------- */

/** @brief CloseWindow support: close the bound window after the command. */
static void on_close_window_click(void* ctx, const char* event, void* data) {
  my_mvvm_context_t* mc = (my_mvvm_context_t*)ctx;
  (void)event;
  (void)data;
  if (mc != NULL && !atomic_load_explicit(&mc->closing, memory_order_acquire) &&
      mc->wm != NULL && mc->win != NULL) {
    my_window_manager_close(mc->wm, mc->win);
  }
}

static my_ret_t bind_widget_rules(my_mvvm_context_t* mc, my_widget_t* widget) {
  char rules[512];
  char* cur;
  if (widget->bind_rules == NULL) {
    return MY_RET_OK;
  }
  if (strlen(widget->bind_rules) >= sizeof(rules)) {
    return MY_RET_INVALID_PARAMS;
  }
  {
    my_widget_target_t* target =
        my_widget_target_create(mc->allocator, widget);
    if (target == NULL) {
      return MY_RET_OOM;
    }
    if (my_darray_push(mc->targets, target) != MY_RET_OK) {
      my_widget_target_destroy(target);
      return MY_RET_OOM;
    }
    strcpy(rules, widget->bind_rules);
    cur = rules;
    while (*cur != '\0') {
      char* sep = strchr(cur, ';');
      my_binding_rule_t rule;
      my_ret_t ret;
      if (sep != NULL) {
        *sep = '\0';
      }
      ret = my_binding_rule_parse(cur, &rule);
      if (ret != MY_RET_OK) {
        return ret;
      }
      ret = my_binding_context_bind(mc->ctx, (my_binding_target_t*)target, cur);
      if (ret != MY_RET_OK) {
        return ret;
      }
      if (rule.type == MY_RULE_COMMAND && rule.close_window) {
        close_listener_t* listener;
        uint32_t id = my_widget_on(widget, "click", on_close_window_click, mc);
        if (id == 0u) {
          return MY_RET_OOM;
        }
        listener = (close_listener_t*)my_mem_calloc(
            mc->allocator, 1, sizeof(close_listener_t));
        if (listener == NULL) {
          my_widget_off(widget, id);
          return MY_RET_OOM;
        }
        listener->widget = widget;
        listener->id = id;
        if (my_darray_push(mc->close_listeners, listener) != MY_RET_OK) {
          my_widget_off(widget, id);
          my_mem_free(mc->allocator, listener);
          return MY_RET_OOM;
        }
      }
      if (sep == NULL) {
        break;
      }
      cur = sep + 1;
    }
  }
  return MY_RET_OK;
}

static my_ret_t bind_tree(my_mvvm_context_t* mc, my_widget_t* widget) {
  size_t i, n;
  my_ret_t ret = bind_widget_rules(mc, widget);
  if (ret != MY_RET_OK) {
    return ret;
  }
  n = my_widget_child_count(widget);
  for (i = 0; i < n; i++) {
    ret = bind_tree(mc, my_widget_get_child(widget, i));
    if (ret != MY_RET_OK) {
      return ret;
    }
  }
  return MY_RET_OK;
}

my_mvvm_context_t* my_mvvm_bind(my_window_manager_t* wm, my_window_t* win,
                                my_view_model_t* vm) {
  my_mvvm_context_t* mc;
  if (win == NULL || vm == NULL) {
    return NULL;
  }
  mc = (my_mvvm_context_t*)my_mem_calloc(NULL, 1, sizeof(my_mvvm_context_t));
  if (mc == NULL) {
    return NULL;
  }
  atomic_init(&mc->ref_count, 1u);
  atomic_init(&mc->closing, false);
  mc->wm = wm;
  mc->win = (my_window_t*)my_widget_ref((my_widget_t*)win);
  mc->loop = win->loop != NULL ? win->loop : (wm != NULL ? wm->loop : NULL);
  mc->ctx = my_binding_context_create(NULL, vm);
  mc->targets = my_darray_create(NULL, 0);
  mc->close_listeners = my_darray_create(NULL, 0);
  mc->command_scope = my_ui_command_scope_create(mc->allocator);
  mc->async_state = mvvm_async_state_create(mc->allocator);
  if (wm != NULL) {
    mc->wm_destroy_listener_id = my_window_manager_add_destroy_listener(
        wm, mvvm_manager_destroyed, mc);
  }
  if (mc->ctx == NULL || mc->targets == NULL || mc->close_listeners == NULL ||
      mc->command_scope == NULL || mc->async_state == NULL ||
      (wm != NULL && mc->wm_destroy_listener_id == 0u) ||
      bind_tree(mc, (my_widget_t*)win) != MY_RET_OK) {
    if (wm != NULL && mc->wm_destroy_listener_id != 0u) {
      (void)my_window_manager_remove_destroy_listener(
          wm, mc->wm_destroy_listener_id);
      mc->wm_destroy_listener_id = 0u;
    }
    my_mvvm_context_destroy(mc);
    return NULL;
  }
  if (wm != NULL) {
    my_mvvm_context_ref(mc);
  }
  return mc;
}

my_mvvm_context_t* my_mvvm_context_ref(my_mvvm_context_t* mc) {
  if (mc != NULL) {
    (void)my_ref_count_try_ref(&mc->ref_count);
  }
  return mc;
}

my_ret_t my_mvvm_context_notify_change_async(my_mvvm_context_t* mc,
                                             const char* name) {
  mvvm_notify_command_t* request;
  my_ui_command_t* command;
  my_pal_main_loop_t* loop;
  my_ret_t ret;
  if (mc == NULL || mc->command_scope == NULL || mc->async_state == NULL ||
      mc->loop == NULL || mc->ctx == NULL ||
      (name != NULL && strlen(name) >= MY_RULE_NAME_LEN)) {
    return MY_RET_INVALID_PARAMS;
  }
  loop = mc->loop;
  if (loop == NULL || my_ui_command_scope_is_closed(mc->command_scope)) {
    return MY_RET_PENDING;
  }
  if (!mvvm_async_state_reserve((mvvm_async_state_t*)mc->async_state)) {
    return MY_RET_PENDING;
  }
  request = (mvvm_notify_command_t*)my_mem_calloc(
      mc->allocator, 1u, sizeof(*request));
  if (request == NULL) {
    mvvm_async_state_release_pending((mvvm_async_state_t*)mc->async_state);
    return MY_RET_OOM;
  }
  request->vm = my_view_model_ref(my_binding_context_get_view_model(mc->ctx));
  request->allocator = mc->allocator;
  request->state = mvvm_async_state_ref(
      (mvvm_async_state_t*)mc->async_state);
  request->bulk = name == NULL;
  if (name != NULL) {
    strcpy(request->name, name);
  }
  command = my_ui_command_create(mc->allocator, mvvm_notify_execute, request,
                                 mvvm_notify_destroy);
  if (command == NULL) {
    mvvm_notify_destroy(request);
    return MY_RET_OOM;
  }
  ret = my_ui_command_submit_scoped(loop, mc->command_scope, command);
  my_ui_command_unref(command);
  return ret;
}

my_ret_t my_mvvm_context_set_property_async(my_mvvm_context_t* mc,
                                            const char* name,
                                            const my_value_t* value) {
  mvvm_set_property_command_t* request;
  my_ui_command_t* command;
  my_pal_main_loop_t* loop;
  my_ret_t ret;
  if (mc == NULL || mc->command_scope == NULL || mc->async_state == NULL ||
      mc->loop == NULL || mc->ctx == NULL || name == NULL || value == NULL ||
      strlen(name) >= MY_RULE_NAME_LEN) {
    return MY_RET_INVALID_PARAMS;
  }
  if (value->type == MY_VALUE_POINTER) {
    return MY_RET_NOT_SUPPORTED;
  }
  if (value->type == MY_VALUE_STR &&
      (my_value_get_str(value) == NULL ||
       strlen(my_value_get_str(value)) > MY_MVVM_ASYNC_MAX_STRING)) {
    return MY_RET_INVALID_PARAMS;
  }
  loop = mc->loop;
  if (loop == NULL || my_ui_command_scope_is_closed(mc->command_scope)) {
    return MY_RET_PENDING;
  }
  if (!mvvm_async_state_reserve((mvvm_async_state_t*)mc->async_state)) {
    return MY_RET_PENDING;
  }
  request = (mvvm_set_property_command_t*)my_mem_calloc(
      mc->allocator, 1u, sizeof(*request));
  if (request == NULL) {
    mvvm_async_state_release_pending((mvvm_async_state_t*)mc->async_state);
    return MY_RET_OOM;
  }
  request->vm = my_view_model_ref(my_binding_context_get_view_model(mc->ctx));
  request->allocator = mc->allocator;
  request->state = mvvm_async_state_ref(
      (mvvm_async_state_t*)mc->async_state);
  strcpy(request->name, name);
  my_value_init(&request->value, mc->allocator);
  ret = my_value_copy(&request->value, value);
  if (ret != MY_RET_OK) {
    mvvm_set_property_destroy(request);
    return ret;
  }
  command = my_ui_command_create(mc->allocator, mvvm_set_property_execute,
                                 request, mvvm_set_property_destroy);
  if (command == NULL) {
    mvvm_set_property_destroy(request);
    return MY_RET_OOM;
  }
  ret = my_ui_command_submit_scoped(loop, mc->command_scope, command);
  my_ui_command_unref(command);
  return ret;
}

static void mvvm_context_finalize(void* data) {
  my_mvvm_context_t* mc = (my_mvvm_context_t*)data;
  size_t i, n;
  if (mc == NULL) {
    return;
  }
  n = my_darray_size(mc->close_listeners);
  for (i = 0; i < n; i++) {
    close_listener_t* listener =
        (close_listener_t*)my_darray_get(mc->close_listeners, i);
    if (listener->widget != NULL && listener->id != 0u) {
      my_widget_off(listener->widget, listener->id);
    }
    my_mem_free(mc->allocator, listener);
  }
  my_darray_destroy(mc->close_listeners);
  mc->close_listeners = NULL;
  my_binding_context_destroy(mc->ctx);
  n = my_darray_size(mc->targets);
  for (i = 0; i < n; i++) {
    my_widget_target_destroy((my_widget_target_t*)my_darray_get(mc->targets, i));
  }
  my_darray_destroy(mc->targets);
  if (mc->wm != NULL && mc->wm_destroy_listener_id != 0u) {
    (void)my_window_manager_remove_destroy_listener(
        mc->wm, mc->wm_destroy_listener_id);
  }
  my_ui_command_scope_unref(mc->command_scope);
  mc->command_scope = NULL;
  mvvm_async_state_unref((mvvm_async_state_t*)mc->async_state);
  mc->async_state = NULL;
  my_widget_unref((my_widget_t*)mc->win);
  mc->win = NULL;
  my_mem_free(mc->allocator, mc);
}

static void mvvm_context_deferred_destroy(void* data) {
  mvvm_context_finalize(data);
}

void my_mvvm_context_unref(my_mvvm_context_t* mc) {
  my_ui_command_t* command;
  my_ret_t ret;
  if (mc == NULL || !my_ref_count_release(&mc->ref_count)) {
    return;
  }
  atomic_store_explicit(&mc->closing, true, memory_order_release);
  my_ui_command_scope_close(mc->command_scope);
  mvvm_async_state_close((mvvm_async_state_t*)mc->async_state);
  if (mc->loop == NULL) {
    mvvm_context_finalize(mc);
    return;
  }
  command = my_ui_command_create(NULL, mvvm_context_finalize_execute, mc,
                                 mvvm_context_deferred_destroy);
  if (command == NULL) {
    mvvm_context_finalize(mc);
    return;
  }
  ret = my_ui_command_submit(mc->loop, command);
  my_ui_command_unref(command);
  if (ret != MY_RET_OK) {
    /* submit releases the queue reference and therefore finalizes mc. */
    return;
  }
}

void my_mvvm_context_destroy(my_mvvm_context_t* mc) {
  my_mvvm_context_unref(mc);
}

/* ---------------- navigator (window manager backed) ---------------- */

static void nav_wm_manager_destroyed(void* ctx) {
  my_navigator_wm_t* nav = (my_navigator_wm_t*)ctx;
  if (nav == NULL) {
    return;
  }
  nav->wm_destroy_listener_id = 0u;
  my_ui_command_scope_close(nav->command_scope);
  nav->wm = NULL;
  nav->pal = NULL;
  my_navigator_clear_default(&nav->base);
}

typedef struct nav_async_context_t {
  my_navigator_wm_t* nav;
  my_navigator_request_t request;
} nav_async_context_t;

static my_ret_t nav_async_execute(void* context) {
  nav_async_context_t* async = (nav_async_context_t*)context;
  if (async == NULL || async->nav == NULL) {
    return MY_RET_NOT_FOUND;
  }
  return async->nav->base.handle_request(&async->nav->base,
                                         &async->request);
}

static void nav_async_destroy(void* context) {
  my_mem_free(NULL, context);
}

typedef struct page_entry_t {
  char name[32];
  my_page_factory_fn_t factory;
  void* ctx;
  my_page_context_destroy_fn_t destroy_ctx;
  my_emitter_context_lease_t* lease;
} page_entry_t;

static void nav_wm_dispose(my_navigator_wm_t* nav) {
  size_t i, count;
  if (nav == NULL) {
    return;
  }
  if (nav->wm != NULL && nav->wm_destroy_listener_id != 0u) {
    (void)my_window_manager_remove_destroy_listener(
        nav->wm, nav->wm_destroy_listener_id);
    nav->wm_destroy_listener_id = 0u;
  }
  count = my_darray_size(nav->pages);
  for (i = 0; i < count; i++) {
    page_entry_t* page = (page_entry_t*)my_darray_get(nav->pages, i);
    if (page->destroy_ctx != NULL) {
      page->destroy_ctx(page->ctx);
    }
    my_emitter_context_lease_unref(page->lease);
    my_mem_free(nav->allocator, page);
  }
  my_darray_destroy(nav->pages);
  my_ui_command_scope_unref(nav->command_scope);
  nav->command_scope = NULL;
  my_mem_free(nav->allocator, nav);
}

static my_ret_t nav_wm_handle_impl(my_navigator_wm_t* n,
                                   const my_navigator_request_t* req) {
  size_t i, count;
  if (n == NULL || req == NULL || n->destroying || n->wm == NULL ||
      n->pal == NULL ||
      n->pages == NULL) {
    return MY_RET_NOT_FOUND;
  }
  switch (req->type) {
    case MY_NAV_TO:
      count = my_darray_size(n->pages);
      for (i = 0; i < count; i++) {
        page_entry_t* p = (page_entry_t*)my_darray_get(n->pages, i);
        if (my_str_eq(p->name, req->target)) {
          void* page_context = p->lease != NULL
                                   ? my_emitter_context_lease_context(p->lease)
                                   : p->ctx;
          my_window_t* win;
          if (p->lease != NULL && page_context == NULL) {
            return MY_RET_NOT_FOUND;
          }
          win = p->factory(n->pal, req->args, page_context);
          my_ret_t open_ret;
          if (win == NULL) {
            return MY_RET_FAIL;
          }
          if (n->destroy_requested || n->destroying || n->wm == NULL ||
              n->pal == NULL) {
            my_widget_unref((my_widget_t*)win);
            return MY_RET_NOT_FOUND;
          }
          open_ret = my_window_manager_open(n->wm, win);
          my_widget_unref((my_widget_t*)win);
          return open_ret;
        }
      }
      return MY_RET_NOT_FOUND;
    case MY_NAV_BACK: {
      my_window_t* top = my_window_manager_top(n->wm);
      return top != NULL ? my_window_manager_close(n->wm, top)
                         : MY_RET_NOT_FOUND;
    }
    case MY_NAV_HOME:
      return my_window_manager_back_to_home(n->wm);
    case MY_NAV_REPLACE: {
      my_window_t* top = my_window_manager_top(n->wm);
      my_navigator_request_t to = *req;
      if (top != NULL) {
        my_window_manager_close(n->wm, top);
      }
      to.type = MY_NAV_TO;
      return nav_wm_handle_impl(n, &to);
    }
    default:
      return MY_RET_INVALID_PARAMS;
  }
}

static my_ret_t nav_wm_handle(my_navigator_t* nav,
                              const my_navigator_request_t* req) {
  my_navigator_wm_t* n = (my_navigator_wm_t*)nav;
  my_ret_t result;
  if (n == NULL || n->destroying) {
    return MY_RET_NOT_FOUND;
  }
  n->callback_depth++;
  result = nav_wm_handle_impl(n, req);
  n->callback_depth--;
  if (n->callback_depth == 0u && n->destroy_requested) {
    nav_wm_dispose(n);
  }
  return result;
}

my_navigator_wm_t* my_navigator_wm_create(const my_allocator_t* allocator,
                                          my_window_manager_t* wm,
                                          my_pal_t* pal) {
  my_navigator_wm_t* n;
  if (wm == NULL || pal == NULL) {
    return NULL;
  }
  n = (my_navigator_wm_t*)my_mem_calloc(allocator, 1, sizeof(my_navigator_wm_t));
  if (n == NULL) {
    return NULL;
  }
  n->base.handle_request = nav_wm_handle;
  n->allocator = allocator;
  n->wm = wm;
  n->pal = pal;
  n->pages = my_darray_create(allocator, 0);
  n->command_scope = my_ui_command_scope_create(allocator);
  if (n->pages == NULL || n->command_scope == NULL) {
    my_ui_command_scope_unref(n->command_scope);
    my_darray_destroy(n->pages);
    my_mem_free(allocator, n);
    return NULL;
  }
  n->wm_destroy_listener_id = my_window_manager_add_destroy_listener(
      wm, nav_wm_manager_destroyed, n);
  if (n->wm_destroy_listener_id == 0u) {
    my_ui_command_scope_unref(n->command_scope);
    my_darray_destroy(n->pages);
    my_mem_free(allocator, n);
    return NULL;
  }
  return n;
}

void my_navigator_wm_destroy(my_navigator_wm_t* nav) {
  if (nav == NULL) {
    return;
  }
  if (nav->destroying) {
    return;
  }
  nav->destroying = true;
  my_navigator_clear_default(&nav->base);
  if (nav->callback_depth != 0u) {
    nav->destroy_requested = true;
    my_ui_command_scope_close(nav->command_scope);
    return;
  }
  my_ui_command_scope_close(nav->command_scope);
  nav_wm_dispose(nav);
}

my_ret_t my_navigator_wm_add_page(my_navigator_wm_t* nav, const char* name,
                                  my_page_factory_fn_t factory, void* ctx) {
  return my_navigator_wm_add_page_owned(nav, name, factory, ctx, NULL);
}

my_ret_t my_navigator_wm_add_page_owned(
    my_navigator_wm_t* nav, const char* name, my_page_factory_fn_t factory,
    void* ctx, my_page_context_destroy_fn_t destroy_ctx) {
  page_entry_t* p;
  if (nav == NULL || name == NULL || factory == NULL || strlen(name) >= 32) {
    return MY_RET_INVALID_PARAMS;
  }
  p = (page_entry_t*)my_mem_calloc(nav->allocator, 1, sizeof(page_entry_t));
  if (p == NULL) {
    return MY_RET_OOM;
  }
  strncpy(p->name, name, 31);
  p->factory = factory;
  p->ctx = ctx;
  p->destroy_ctx = destroy_ctx;
  p->lease = NULL;
  if (my_darray_push(nav->pages, p) != MY_RET_OK) {
    my_mem_free(nav->allocator, p);
    return MY_RET_OOM;
  }
  return MY_RET_OK;
}

my_ret_t my_navigator_wm_add_page_lease(
    my_navigator_wm_t* nav, const char* name, my_page_factory_fn_t factory,
    my_emitter_context_lease_t* lease) {
  page_entry_t* p;
  if (nav == NULL || name == NULL || factory == NULL || lease == NULL ||
      strlen(name) >= 32 || !my_emitter_context_lease_is_valid(lease) ||
      nav->destroying) {
    return MY_RET_INVALID_PARAMS;
  }
  p = (page_entry_t*)my_mem_calloc(nav->allocator, 1, sizeof(*p));
  if (p == NULL) {
    return MY_RET_OOM;
  }
  p->lease = my_emitter_context_lease_ref(lease);
  if (p->lease == NULL) {
    my_mem_free(nav->allocator, p);
    return MY_RET_OOM;
  }
  strncpy(p->name, name, sizeof(p->name) - 1u);
  p->factory = factory;
  if (my_darray_push(nav->pages, p) != MY_RET_OK) {
    my_emitter_context_lease_unref(p->lease);
    my_mem_free(nav->allocator, p);
    return MY_RET_OOM;
  }
  return MY_RET_OK;
}

my_ret_t my_navigator_wm_request_async(
    my_navigator_wm_t* nav, my_pal_main_loop_t* loop,
    const my_navigator_request_t* request) {
  nav_async_context_t* context;
  my_ui_command_t* command;
  my_ret_t ret;
  if (nav == NULL || loop == NULL || request == NULL ||
      nav->command_scope == NULL || nav->wm == NULL || nav->pal == NULL ||
      loop != nav->wm->loop) {
    return MY_RET_INVALID_PARAMS;
  }
  if (request->type < MY_NAV_TO || request->type > MY_NAV_HOME) {
    return MY_RET_INVALID_PARAMS;
  }
  context = (nav_async_context_t*)my_mem_calloc(NULL, 1, sizeof(*context));
  if (context == NULL) {
    return MY_RET_OOM;
  }
  context->nav = nav;
  context->request = *request;
  command = my_ui_command_create(NULL, nav_async_execute, context,
                                 nav_async_destroy);
  if (command == NULL) {
    nav_async_destroy(context);
    return MY_RET_OOM;
  }
  ret = my_ui_command_submit_scoped(loop, nav->command_scope, command);
  my_ui_command_unref(command);
  return ret;
}
