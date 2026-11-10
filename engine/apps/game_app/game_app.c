#include "game_app.h"

BreakRuntimeError game_app_run(const GameAppConfig *config, int *out_exit_code) {
    if (out_exit_code == NULL) return BREAK_RUNTIME_INVALID;
    *out_exit_code = 2;
    if (config == NULL) return BREAK_RUNTIME_INVALID;
    return BREAK_RUNTIME_FAILED;
}
