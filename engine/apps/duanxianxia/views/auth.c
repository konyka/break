/**
 * @file auth.c
 * @brief Login/register dialog implementation (M14d).
 *
 * MVVM wiring: both edits bind v:text TwoWay with the not_empty
 * validator (rejects empty write-back); the submit button binds
 * v:on_click={submit}; the command validates non-empty fields and shows
 * the error via the "error" property (bound to a red label).
 */
#include "auth.h"

#include <stdio.h>
#include <stdlib.h>

#include "../dxx_theme.h"
#include "myc/my_darray.h"
#include "myc/my_str.h"
#include "mymvvm/my_view_model.h"
#include "mymvvm_myui/my_mvvm.h"
#include "myui/my_layout.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_dialog.h"
#include "myui/widgets/my_edit.h"
#include "myui/widgets/my_label.h"

typedef struct auth_ctx_t {
  my_dialog_t* dlg;
  my_view_model_t* vm;
  my_mvvm_context_t* mc;
  bool is_register;
} auth_ctx_t;

/** @brief Read a string vm prop into buf ("" when unset). */
static void vm_get_str(my_view_model_t* vm, const char* name, char* buf,
                       size_t cap) {
  my_value_t v;
  const char* s;
  my_value_init(&v, NULL);
  buf[0] = '\0';
  if (my_view_model_get_prop(vm, name, &v) == MY_RET_OK &&
      (s = my_value_get_str(&v)) != NULL) {
    snprintf(buf, cap, "%s", s);
  }
  my_value_reset(&v);
}

static void vm_set_str(my_view_model_t* vm, const char* name,
                       const char* str) {
  my_value_t v;
  my_value_init(&v, NULL);
  my_value_set_str(&v, str);
  my_view_model_set_prop(vm, name, &v);
  my_value_reset(&v);
}

static my_ret_t on_submit(void* ctx, const char* args) {
  auth_ctx_t* ac = (auth_ctx_t*)ctx;
  char user[64], pass[64], confirm[64];
  (void)args;
  vm_get_str(ac->vm, "username", user, sizeof(user));
  vm_get_str(ac->vm, "password", pass, sizeof(pass));
  if (user[0] == '\0') {
    vm_set_str(ac->vm, "error", "用户名不能为空");
    return MY_RET_OK;
  }
  if (pass[0] == '\0') {
    vm_set_str(ac->vm, "error", "密码不能为空");
    return MY_RET_OK;
  }
  if (ac->is_register) {
    vm_get_str(ac->vm, "confirm", confirm, sizeof(confirm));
    if (!my_str_eq(pass, confirm)) {
      vm_set_str(ac->vm, "error", "两次密码不一致");
      return MY_RET_OK;
    }
  }
  printf("dxx: %s submit user='%s' (no backend, demo)\n",
         ac->is_register ? "register" : "login", user);
  my_dialog_close(ac->dlg, 1);
  return MY_RET_OK;
}

/** @brief Dialog closed: destroy mvvm ctx + vm + dialog + ctx. */
static void on_result(void* ctx, int32_t result) {
  auth_ctx_t* ac = (auth_ctx_t*)ctx;
  (void)result;
  my_mvvm_context_destroy(ac->mc);
  my_view_model_unref(ac->vm);
  my_dialog_destroy(ac->dlg);
  free(ac);
}

void dxx_show_auth_dialog(my_window_manager_t* wm, bool is_register) {
  auth_ctx_t* ac;
  my_widget_t* content;
  my_widget_t* edit;
  my_widget_t* err;
  my_widget_t* submit;
  if (wm == NULL) {
    return;
  }
  ac = (auth_ctx_t*)calloc(1, sizeof(auth_ctx_t));
  if (ac == NULL) {
    return;
  }
  ac->is_register = is_register;
  ac->dlg = my_dialog_create(NULL, wm->pal, is_register ? "注册" : "登录",
                             360, is_register ? 320 : 260);
  if (ac->dlg == NULL) {
    free(ac);
    return;
  }
  ac->vm = my_view_model_dummy_create(NULL);
  content = my_dialog_content(ac->dlg);
  /* dialog windows get no font by default: inherit the main window's */
  if (my_darray_size(wm->windows) > 0) {
    my_window_t* main_win =
        (my_window_t*)my_darray_get(wm->windows, 0);
    if (main_win->font != NULL) {
      my_window_set_font(ac->dlg->win, main_win->font, main_win->font_size);
    }
  }

  edit = my_edit_create(NULL);
  my_edit_set_hint(edit, "请输入用户名");
  my_widget_set_layout_params(edit, "h:36");
  my_widget_set_bind_rules(edit,
                           "v:text={username, Mode=TwoWay, Validator=not_empty}");
  my_widget_add_child(content, edit);
  my_widget_unref(edit);

  edit = my_edit_create(NULL);
  my_edit_set_hint(edit, "请输入密码");
  my_edit_set_password(edit, true);
  my_widget_set_layout_params(edit, "h:36");
  my_widget_set_bind_rules(edit,
                           "v:text={password, Mode=TwoWay, Validator=not_empty}");
  my_widget_add_child(content, edit);
  my_widget_unref(edit);

  if (is_register) {
    edit = my_edit_create(NULL);
    my_edit_set_hint(edit, "请再次输入密码");
    my_edit_set_password(edit, true);
    my_widget_set_layout_params(edit, "h:36");
    my_widget_set_bind_rules(edit, "v:text={confirm, Mode=TwoWay}");
    my_widget_add_child(content, edit);
    my_widget_unref(edit);
  }

  err = my_label_create(NULL, "");
  my_widget_set_layout_params(err, "h:24");
  my_widget_set_bind_rules(err, "v:text={error}");
  {
    /* error label in red */
    my_value_t v;
    my_value_init(&v, NULL);
    my_value_set_uint32(&v, DXX_COLOR_UP);
    my_widget_style_set(err, MY_STATE_NORMAL, "fg_color", &v);
    my_value_reset(&v);
  }
  my_widget_add_child(content, err);
  my_widget_unref(err);

  submit = my_button_create(NULL, is_register ? "注册" : "登录");
  my_widget_set_layout_params(submit, "h:36");
  my_widget_set_bind_rules(submit, "v:on_click={submit}");
  {
    my_value_t v;
    my_value_init(&v, NULL);
    my_value_set_uint32(&v, DXX_COLOR_BTN_BLUE);
    my_widget_style_set(submit, MY_STATE_NORMAL, "bg_color", &v);
    my_widget_style_set(submit, MY_STATE_HOVER, "bg_color", &v);
    my_widget_style_set(submit, MY_STATE_PRESSED, "bg_color", &v);
    my_value_set_uint32(&v, DXX_COLOR_WHITE);
    my_widget_style_set(submit, MY_STATE_NORMAL, "fg_color", &v);
    my_value_reset(&v);
  }
  my_widget_add_child(content, submit);
  my_widget_unref(submit);

  my_view_model_dummy_add_command(ac->vm, "submit", on_submit, ac);
  my_dialog_add_button(ac->dlg, "取消", 0);
  ac->mc = my_mvvm_bind(wm, ac->dlg->win, ac->vm);
  my_dialog_open(ac->dlg, wm, on_result, ac);
}
