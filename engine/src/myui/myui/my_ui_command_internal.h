/**
 * @file my_ui_command_internal.h
 * @brief Internal PAL dispatch hooks for UI commands.
 */
#ifndef MY_UI_COMMAND_INTERNAL_H
#define MY_UI_COMMAND_INTERNAL_H

#include "myui/my_ui_command.h"

/* Only PAL event pumps may establish the loop-thread dispatch context. */
void my_ui_command_dispatch_context_enter(my_pal_main_loop_t* loop);
void my_ui_command_dispatch_context_leave(my_pal_main_loop_t* loop);

#endif /* MY_UI_COMMAND_INTERNAL_H */
