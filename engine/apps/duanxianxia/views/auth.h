/**
 * @file auth.h
 * @brief duanxianxia clone: login/register dialog (M14d) — demonstrates
 * edit + MVVM (TwoWay text bindings, command, not_empty validator).
 */
#ifndef DXX_AUTH_H
#define DXX_AUTH_H

#include "myui/my_window_manager.h"

/** @brief Open the login (is_register=false, 360x260) or register
 * (360x320) dialog. The dialog is modal; everything is cleaned up on
 * close. A successful submit logs to stdout (no backend). */
void dxx_show_auth_dialog(my_window_manager_t* wm, bool is_register);

#endif /* DXX_AUTH_H */
